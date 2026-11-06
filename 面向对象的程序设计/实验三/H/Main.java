import java.util.Scanner;

interface Comparable<T> {
    boolean compareTo(T o);
}
class Circle {
    private int radius;
    public Circle(int radius) {
        this.radius = radius;
    }
    public int getRadius() {
        return radius;
    }
    public void setRadius(int radius) {
        this.radius = radius;
    }
    public double getArea() {
        return Math.PI * radius * radius;
    }
}

class ComparableCircle extends Circle implements Comparable<ComparableCircle> {
    public ComparableCircle(int radius) {
        super(radius);
    }
    public boolean compareTo(ComparableCircle o) {
        return this.getArea() > o.getArea();
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        ComparableCircle c1 = new ComparableCircle(scanner.nextInt());
        ComparableCircle c2 = new ComparableCircle(scanner.nextInt());
        System.out.printf("The max circle's area is %.2f", (c1.compareTo(c2) ? c1.getArea() : c2.getArea()));
        scanner.close();
    }
}