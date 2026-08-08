import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Objects;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * ============================================================================
 * OOP FOUR PILLARS DEMONSTRATION - ADNU Student Records & Billing System
 * ============================================================================
 * A single-file, professional-grade Java program demonstrating all four
 * pillars of Object-Oriented Programming, hardened against common real-world
 * defects, through a student records domain modeled after Ateneo de Naga
 * University (ADNU) departments/programs.
 *
 * THE FOUR PILLARS
 * 1. ENCAPSULATION - private fields, exhaustively validated constructors
 * and mutators, immutable IDs, defensive copies,
 * unmodifiable collections exposed to callers
 * 2. INHERITANCE - Student -> RegularStudent / ScholarStudent /
 * GraduatingStudent
 * 3. POLYMORPHISM - method overriding (runtime) + method overloading
 * (compile-time) + polymorphic collections via Billable
 * 4. ABSTRACTION - abstract class Student + interfaces Billable / Promotable
 *
 * WHY THIS IS HARDENED, NOT JUST "FOUR PILLARS"
 * - Money is BigDecimal, never double/float - eliminates binary
 * floating-point rounding error in tuition and discount arithmetic.
 * - Every constructor and mutator fails fast with a precise exception
 * (IllegalArgumentException / NullPointerException / a custom checked
 * InvalidTuitionException) instead of silently accepting bad state.
 * - Student ID generation uses AtomicInteger, so it is safe under
 * concurrent construction, not just single-threaded demos.
 * - Student implements Comparable<Student> consistently with equals(),
 * so it behaves correctly inside sorted collections.
 * - Duplicate enrollment is rejected using the equals() contract, proving
 * it is actually exercised, not just present for style.
 * - promote() checks whether advanceYear() actually advanced before
 * applying any reward - no more "promoted" side effects firing on a
 * student who was already at the year-level cap.
 * - Subclasses that don't need a behavior (GraduatingStudent + Promotable)
 * simply don't implement it, rather than inheriting a method they'd
 * have to stub out or throw UnsupportedOperationException from - this
 * keeps the hierarchy honest to the Liskov Substitution Principle.
 *
 * SOLID AT A GLANCE
 * S - Registrar / Student / Department each own exactly one concern.
 * O - new Student subtypes plug in without touching Registrar.
 * L - every Student subtype is fully usable wherever a Student is expected.
 * I - Billable and Promotable are separate, minimal contracts.
 * D - Registrar depends on the Student abstraction, never a subtype.
 *
 * Kept as a single file on purpose for portability (compile-and-run in one
 * step). In a multi-developer codebase each class below would live in its
 * own file under a package, e.g. edu.adnu.students.
 *
 * Compile: javac ADNUStudentSystem.java
 * Run: java ADNUStudentSystem
 * ============================================================================
 */
public class ADNUStudentSystem {

    public static void main(String[] args) {
        Registrar registrar = new Registrar();

        RegularStudent karl = new RegularStudent("Karl Dimabayao", Department.COMPUTER_SCIENCE,
                new BigDecimal("15000.00"), 2024, 2, 21,
                List.of("Data Structures and Algorithms", "Discrete Mathematics", "Web Systems"));
        ScholarStudent ana = new ScholarStudent("Ana Reyes", Department.INFORMATION_SYSTEMS,
                new BigDecimal("15000.00"), 2023, 3, "Academic Scholarship", new BigDecimal("0.50"));
        GraduatingStudent miguel = new GraduatingStudent("Miguel Santos", Department.ACCOUNTANCY,
                new BigDecimal("15000.00"), 2022, "1st Semester, S.Y. 2026-2027", new BigDecimal("2500.00"));
        RegularStudent liza = new RegularStudent("Liza Chua", Department.NURSING,
                new BigDecimal("15000.00"), 2025, 1, 18,
                List.of("Anatomy and Physiology", "Theology 1"));

        registrar.enroll(karl);
        registrar.enroll(ana);
        registrar.enroll(miguel);
        registrar.enroll(liza);

        registrar.printRoster();
        registrar.runBilling();
        registrar.runPromotions();

        System.out.println("\n========== Guard 1: invalid mutation (checked exception) ==========");
        try {
            karl.setBaseTuition(new BigDecimal("-1000"));
        } catch (InvalidTuitionException ex) {
            System.out.println("Rejected: " + ex.getMessage());
        }
        System.out.printf("Karl's tuition is unchanged: P%,.2f%n", karl.getBaseTuition());

        System.out.println("\n========== Guard 2: invalid construction (fail fast) ==========");
        try {
            new ScholarStudent("Test Student", Department.EDUCATION, new BigDecimal("15000.00"),
                    2026, 1, "Invalid Scholarship", new BigDecimal("1.50")); // 150% is impossible
        } catch (IllegalArgumentException ex) {
            System.out.println("Rejected: " + ex.getMessage());
        }

        System.out.println("\n========== Guard 3: duplicate enrollment (equals() contract) ==========");
        try {
            registrar.enroll(karl);
        } catch (IllegalStateException ex) {
            System.out.println("Rejected: " + ex.getMessage());
        }

        System.out.println("\nTotal students enrolled: " + registrar.size());
        System.out.println("Student ID sequence position: " + Student.getStudentCount());
    }
}

/**
 * ADNU academic department/program. An enum instead of a raw String makes
 * every department reference type-checked at compile time - an invalid
 * department simply cannot be constructed.
 */
enum Department {
    COMPUTER_SCIENCE("BS Computer Science"),
    INFORMATION_SYSTEMS("BS Information Systems"),
    NURSING("BS Nursing"),
    ACCOUNTANCY("BS Accountancy"),
    BUSINESS_ADMINISTRATION("BS Business Administration"),
    EDUCATION("BS Education");

    private final String displayName;

    Department(String displayName) {
        this.displayName = displayName;
    }

    @Override
    public String toString() {
        return displayName;
    }
}

/**
 * Thrown when an operation would leave a Student's tuition in an invalid state.
 */
class InvalidTuitionException extends Exception {
    private static final long serialVersionUID = 1L;

    public InvalidTuitionException(String message) {
        super(message);
    }
}

/** Contract for anything that can compute and describe a tuition bill. */
interface Billable {
    BigDecimal calculateTuition();

    String getBillingDetails();
}

/** Contract for anything that can advance to the next academic year level. */
interface Promotable {
    void promote();
}

/**
 * Base type for every kind of ADNU student. Owns identity, enrollment, and
 * tuition state; delegates the actual billing formula and student-type label
 * to subclasses via {@link Billable} and {@link #getStudentType()}.
 *
 * <p>
 * All monetary fields are {@link BigDecimal}, never {@code double} - so
 * tuition math never suffers binary floating-point rounding error.
 */
abstract class Student implements Billable, Comparable<Student> {

    // ---------------- ENCAPSULATION ----------------
    // Fields are private; every external access is mediated through methods
    private final String studentId;
    private final String name;
    private Department department;
    private int yearLevel;
    private BigDecimal baseTuition;

    // Thread-safe, monotonically increasing sequence for student IDs. Note:
    // a value can be "consumed" even if a subclass constructor later throws,
    // since its own validation runs after this superclass constructor has
    // already succeeded - the same gap-on-failure behavior a database
    // auto-increment sequence has. Documented, not hidden.
    private static final AtomicInteger STUDENT_SEQUENCE = new AtomicInteger(0);
    private static final int MAX_YEAR_LEVEL = 5;

    /**
     * @throws IllegalArgumentException if name is blank, baseTuition is
     *                                  negative, enrollmentYear is unrealistic, or
     *                                  yearLevel is out
     *                                  of range
     * @throws NullPointerException     if department or baseTuition is null
     */
    protected Student(String name, Department department, BigDecimal baseTuition,
            int enrollmentYear, int yearLevel) {
        if (name == null || name.isBlank()) {
            throw new IllegalArgumentException("Student name cannot be blank");
        }
        Objects.requireNonNull(department, "Department cannot be null");
        Objects.requireNonNull(baseTuition, "Base tuition cannot be null");
        if (baseTuition.signum() < 0) {
            throw new IllegalArgumentException("Base tuition cannot be negative");
        }
        if (enrollmentYear < 1900 || enrollmentYear > 2100) {
            throw new IllegalArgumentException("Enrollment year must be a realistic 4-digit year");
        }
        if (yearLevel < 1 || yearLevel > MAX_YEAR_LEVEL) {
            throw new IllegalArgumentException("Year level must be between 1 and " + MAX_YEAR_LEVEL);
        }
        this.studentId = String.format("%d-%05d", enrollmentYear, STUDENT_SEQUENCE.incrementAndGet());
        this.name = name;
        this.department = department;
        this.baseTuition = baseTuition;
        this.yearLevel = yearLevel;
    }

    public String getStudentId() {
        return studentId;
    }

    public String getName() {
        return name;
    }

    public Department getDepartment() {
        return department;
    }

    public int getYearLevel() {
        return yearLevel;
    }

    public BigDecimal getBaseTuition() {
        return baseTuition;
    }

    /**
     * @return the current ID sequence position (see the note on
     *         {@code STUDENT_SEQUENCE})
     */
    public static int getStudentCount() {
        return STUDENT_SEQUENCE.get();
    }

    public void setDepartment(Department department) {
        this.department = Objects.requireNonNull(department, "Department cannot be null");
    }

    /**
     * Validated mutation - encapsulation guards the invariant that tuition
     * is never null or negative.
     * 
     * @throws InvalidTuitionException if baseTuition is null or negative
     */
    public void setBaseTuition(BigDecimal baseTuition) throws InvalidTuitionException {
        if (baseTuition == null || baseTuition.signum() < 0) {
            throw new InvalidTuitionException("Tuition must be a non-null, non-negative amount for " + name);
        }
        this.baseTuition = baseTuition;
    }

    // ---------------- POLYMORPHISM (compile-time: overloading) ----------------
    // Same method name, different parameter lists - resolved at compile time
    public void applyDiscount(BigDecimal amount) {
        Objects.requireNonNull(amount, "Discount amount cannot be null");
        this.baseTuition = this.baseTuition.subtract(amount).max(BigDecimal.ZERO);
    }

    public void applyDiscount(BigDecimal amount, String reason) {
        applyDiscount(amount); // delegates instead of duplicating the clamping logic (DRY)
        System.out.printf("  -> %s received a P%,.2f discount (%s)%n", name, amount, reason);
    }

    /**
     * Advances the year level by one unless already at the cap. Protected -
     * visible to subclasses (including in other packages), never to external
     * callers, who must go through {@link Promotable#promote()} instead.
     * 
     * @return true if the year level actually advanced, false if already capped
     */
    protected boolean advanceYear() {
        if (yearLevel >= MAX_YEAR_LEVEL) {
            return false;
        }
        yearLevel++;
        return true;
    }

    /** Shared message for Promotable subclasses that hit the year-level cap. */
    protected void announceMaxYearLevel() {
        System.out.println("  -> " + name + " is already at the maximum year level ("
                + yearLevel + ") - no promotion applied.");
    }

    // ---------------- ABSTRACTION ----------------
    // Every subclass MUST define what kind of student it represents
    public abstract String getStudentType();

    // ---------------- POLYMORPHISM (runtime: overriding Object's methods) -----
    @Override
    public String toString() {
        return String.format("[%s] %-18s %-20s %-24s Yr %d",
                studentId, name, getStudentType(), department, yearLevel);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o)
            return true;
        if (!(o instanceof Student other))
            return false;
        return studentId.equals(other.studentId);
    }

    @Override
    public int hashCode() {
        return Objects.hash(studentId);
    }

    /** Natural ordering by student ID - consistent with {@link #equals(Object)}. */
    @Override
    public int compareTo(Student other) {
        return this.studentId.compareTo(other.studentId);
    }
}

// ============================================================================
// INHERITANCE - concrete subclasses extend Student, reusing its fields and
// behavior while adding their own state and fulfilling shared contracts
// ============================================================================

/**
 * A student paying standard tuition plus per-unit miscellaneous fees,
 * eligible for ordinary year-level promotion.
 */
class RegularStudent extends Student implements Promotable {
    private final int unitsEnrolled;
    private final List<String> subjects;
    private static final BigDecimal MISC_FEE_PER_UNIT = new BigDecimal("150.00");
    private static final BigDecimal PROMOTION_REBATE = new BigDecimal("100.00");

    public RegularStudent(String name, Department department, BigDecimal baseTuition,
            int enrollmentYear, int yearLevel, int unitsEnrolled, List<String> subjects) {
        super(name, department, baseTuition, enrollmentYear, yearLevel);
        if (unitsEnrolled <= 0 || unitsEnrolled > 30) {
            throw new IllegalArgumentException("Units enrolled must be between 1 and 30");
        }
        Objects.requireNonNull(subjects, "Subjects list cannot be null");
        if (subjects.isEmpty()) {
            throw new IllegalArgumentException("Subjects list cannot be empty");
        }
        this.unitsEnrolled = unitsEnrolled;
        this.subjects = new ArrayList<>(subjects); // defensive copy - caller's list can't mutate ours
    }

    public int getUnitsEnrolled() {
        return unitsEnrolled;
    }

    public List<String> getSubjects() {
        return Collections.unmodifiableList(subjects); // encapsulation: no external mutation
    }

    @Override
    public String getStudentType() {
        return "Regular Student";
    }

    // ---------------- POLYMORPHISM (runtime: overriding) ----------------
    @Override
    public BigDecimal calculateTuition() {
        BigDecimal miscFees = MISC_FEE_PER_UNIT.multiply(BigDecimal.valueOf(unitsEnrolled));
        return getBaseTuition().add(miscFees).setScale(2, RoundingMode.HALF_UP);
    }

    @Override
    public String getBillingDetails() {
        BigDecimal miscFees = MISC_FEE_PER_UNIT.multiply(BigDecimal.valueOf(unitsEnrolled));
        return String.format("%-18s P%,10.2f  (tuition P%,.2f + misc. fees P%,.2f for %d units)",
                getName(), calculateTuition(), getBaseTuition(), miscFees, unitsEnrolled);
    }

    @Override
    public void promote() {
        if (advanceYear()) {
            applyDiscount(PROMOTION_REBATE, "on-time enrollment rebate");
        } else {
            announceMaxYearLevel();
        }
    }
}

/**
 * A student whose tuition is discounted by a fixed percentage under a named
 * scholarship, with the discount reinforced on each successful promotion.
 */
class ScholarStudent extends Student implements Promotable {
    private final String scholarshipType;
    private final BigDecimal discountRate; // fraction of base tuition waived, e.g. 0.50 = 50%
    private static final BigDecimal RENEWAL_BONUS_RATE = new BigDecimal("0.05");

    public ScholarStudent(String name, Department department, BigDecimal baseTuition,
            int enrollmentYear, int yearLevel, String scholarshipType, BigDecimal discountRate) {
        super(name, department, baseTuition, enrollmentYear, yearLevel);
        if (scholarshipType == null || scholarshipType.isBlank()) {
            throw new IllegalArgumentException("Scholarship type cannot be blank");
        }
        Objects.requireNonNull(discountRate, "Discount rate cannot be null");
        if (discountRate.compareTo(BigDecimal.ZERO) < 0 || discountRate.compareTo(BigDecimal.ONE) > 0) {
            throw new IllegalArgumentException("Discount rate must be between 0.0 and 1.0");
        }
        this.scholarshipType = scholarshipType;
        this.discountRate = discountRate;
    }

    public String getScholarshipType() {
        return scholarshipType;
    }

    @Override
    public String getStudentType() {
        return "Scholar Student";
    }

    @Override
    public BigDecimal calculateTuition() {
        BigDecimal multiplier = BigDecimal.ONE.subtract(discountRate);
        return getBaseTuition().multiply(multiplier).setScale(2, RoundingMode.HALF_UP);
    }

    @Override
    public String getBillingDetails() {
        BigDecimal percentage = discountRate.multiply(BigDecimal.valueOf(100));
        return String.format("%-18s P%,10.2f  (tuition P%,.2f - %.0f%% %s discount)",
                getName(), calculateTuition(), getBaseTuition(), percentage, scholarshipType);
    }

    @Override
    public void promote() {
        if (advanceYear()) {
            BigDecimal bonus = getBaseTuition().multiply(RENEWAL_BONUS_RATE).setScale(2, RoundingMode.HALF_UP);
            applyDiscount(bonus, "scholarship renewed for maintaining required GPA");
        } else {
            announceMaxYearLevel();
        }
    }
}

/**
 * A fourth-year student in their terminal semester, billed an additional
 * graduation fee instead of ordinary miscellaneous fees. Deliberately does
 * NOT implement {@link Promotable} - there is no next year level to advance
 * into, and forcing the interface on would mean stubbing out or throwing
 * from promote(), which is exactly what the Liskov Substitution Principle
 * warns against.
 */
class GraduatingStudent extends Student {
    private final String expectedGraduationTerm;
    private final BigDecimal graduationFee;

    public GraduatingStudent(String name, Department department, BigDecimal baseTuition,
            int enrollmentYear, String expectedGraduationTerm, BigDecimal graduationFee) {
        super(name, department, baseTuition, enrollmentYear, 4);
        if (expectedGraduationTerm == null || expectedGraduationTerm.isBlank()) {
            throw new IllegalArgumentException("Expected graduation term cannot be blank");
        }
        Objects.requireNonNull(graduationFee, "Graduation fee cannot be null");
        if (graduationFee.signum() < 0) {
            throw new IllegalArgumentException("Graduation fee cannot be negative");
        }
        this.expectedGraduationTerm = expectedGraduationTerm;
        this.graduationFee = graduationFee;
    }

    public String getExpectedGraduationTerm() {
        return expectedGraduationTerm;
    }

    @Override
    public String getStudentType() {
        return "Graduating Student";
    }

    @Override
    public BigDecimal calculateTuition() {
        return getBaseTuition().add(graduationFee).setScale(2, RoundingMode.HALF_UP);
    }

    @Override
    public String getBillingDetails() {
        return String.format("%-18s P%,10.2f  (tuition P%,.2f + graduation fee P%,.2f, targeting %s)",
                getName(), calculateTuition(), getBaseTuition(), graduationFee, expectedGraduationTerm);
    }
}

/**
 * Coordinates the student lifecycle operations a registrar's office owns:
 * enrollment, billing, and year-level promotion. Depends only on the
 * {@code Student} abstraction, never a concrete subtype, so new student
 * types plug in without any change here (Open/Closed Principle).
 */
class Registrar {
    private final List<Student> enrolledStudents = new ArrayList<>();

    /**
     * @throws NullPointerException  if s is null
     * @throws IllegalStateException if s is already enrolled (per equals())
     */
    public void enroll(Student s) {
        Objects.requireNonNull(s, "Cannot enroll a null student");
        if (enrolledStudents.contains(s)) {
            throw new IllegalStateException(s.getName() + " (" + s.getStudentId() + ") is already enrolled");
        }
        enrolledStudents.add(s);
    }

    public int size() {
        return enrolledStudents.size();
    }

    public void printRoster() {
        System.out.println("========== ADNU Student Roster (sorted by Student ID) ==========");
        List<Student> sorted = new ArrayList<>(enrolledStudents);
        Collections.sort(sorted); // uses Student's natural ordering via Comparable<Student>
        sorted.forEach(System.out::println); // each subclass's own toString() runs
    }

    public void runBilling() {
        System.out.println("\n========== Billing (polymorphism in action) ==========");
        BigDecimal total = BigDecimal.ZERO;
        for (Student s : enrolledStudents) {
            // s is declared as Student, but calculateTuition()/getBillingDetails()
            // dynamically dispatch to whichever subclass actually created the object
            System.out.println(s.getBillingDetails());
            total = total.add(s.calculateTuition());
        }
        System.out.printf("%nTotal Tuition Collected: P%,.2f%n", total);
    }

    public void runPromotions() {
        System.out.println("\n========== Year-Level Promotions ==========");
        for (Student s : enrolledStudents) {
            if (s instanceof Promotable p) { // pattern-matching instanceof (Java 16+)
                p.promote();
            } else {
                System.out.println(s.getName() + " is graduating - no further promotion.");
            }
        }
    }
}
