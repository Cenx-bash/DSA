
class Plant {
    private double aHeightInCm;

    public Plant(double aHeightInCm) {
        this.aHeightInCm = aHeightInCm;
    }

    protected void grow() {
        aHeightInCm += 1.0;
        System.out.println("Plant has grown to " + aHeightInCm + " cm.");
    }

    protected void photosynthesize() {
        System.out.println("Plant is photosynthesizing.");
    }
}

public class Flower extends Plant {
    private String aColor;

    public Flower(double aHeightInCm, String aColor) {
        super(aHeightInCm);
        this.aColor = aColor;
    }

    public void dyePetals(String aNewColor) {
        if (aColor.equalsIgnoreCase("white")) {
            aColor = aNewColor.toLowerCase();
            System.out.println(
                "The flower's petals have been dyed to " + aColor + "."
            );
        } else {
            System.out.println(
                "The flower's petals cannot be dyed because they are "
                + aColor
            );
        }
    }
}
