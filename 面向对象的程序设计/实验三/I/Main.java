import java.util.Scanner;

abstract class GeometricObject implements Comparable {
    private String name;

    public GeometricObject(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public abstract double getArea();

    public int compareTo(Object o) {
        return Double.compare(getArea(), ((GeometricObject) o).getArea());
    }

    public static Comparable max(Comparable o1, Comparable o2) {
        if (o1.compareTo(o2) > 0) {
            return o1;
        }
        return o2;
    }
}

class Rectangle extends GeometricObject {
    private double length;
    private double width;

    public Rectangle(String name, double length, double width) {
        super(name);
        this.length = length;
        this.width = width;
    }

    public double getArea() {
        return length * width;
    }

    public String toString() {
        return String.format("%s %.2f %.2f %.2f", getName(), length, width, getArea());
    }
}

class Circle extends GeometricObject {
    private double radius;

    public Circle(String name, double radius) {
        super(name);
        this.radius = radius;
    }

    public double getArea() {
        return Math.PI * radius * radius;
    }

    public String toString() {
        return String.format("%s %.2f %.2f", getName(), radius, getArea());
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Rectangle r1 = new Rectangle(scanner.next(), scanner.nextDouble(), scanner.nextDouble());
        Rectangle r2 = new Rectangle(scanner.next(), scanner.nextDouble(), scanner.nextDouble());
        Circle c1 = new Circle(scanner.next(), scanner.nextDouble());
        Circle c2 = new Circle(scanner.next(), scanner.nextDouble());
        System.out.println(GeometricObject.max(r1, r2));
        System.out.println(GeometricObject.max(c1, c2));
        scanner.close();
    }
}
