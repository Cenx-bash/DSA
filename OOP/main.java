
import java.util.Scanner;


public class Surname3 {
    public static void main(String[] aArgs) {
        Scanner aScanner = new Scanner(System.in);

        System.out.print("Enter the height of the flower (cm): ");
        double aHeight = aScanner.nextDouble();

        System.out.print("Enter the color of the flower: ");
        String aColor = aScanner.next();

        Flower aFlower = new Flower(aHeight, aColor);
        int aChoice = 0;

        do {
            System.out.println("\nChoose an action:");
            System.out.println("1. Grow the flower");
            System.out.println("2. Photosynthesize");
            System.out.println("3. Dye the petals");
            System.out.println("4. Exit");

            System.out.print("Enter your choice: ");
            aChoice = aScanner.nextInt();

            switch (aChoice) {
                case 1:
                    aFlower.grow();
                    break;

                case 2:
                    aFlower.photosynthesize();
                    break;

                case 3:
                    System.out.print("Enter the new color: ");
                    String aNewColor = aScanner.next();

                    aFlower.dyePetals(aNewColor);
                    break;

                case 4:
                    break;

                default:
                    System.out.println(
                        "Invalid choice. Please try again."
                    );
            }

        } while (aChoice != 4);

        aScanner.close();
    }
}
