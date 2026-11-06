import java.util.Scanner;

abstract class Shape {
    final double PI = 3.14;
    abstract double area();
    abstract double volume();
}

class Cylinder extends Shape {
    private double radius;
    private double height;

    public Cylinder(double radius, double height) {
        this.radius = radius;
        this.height = height;
    }

    @Override
    double area() {
        return 2 * PI * radius * (radius + height);
    }

    @Override
    double volume() {
        return PI * radius * radius * height;
    }
}

class Sphere extends Shape {
    private double radius;

    public Sphere(double radius) {
        this.radius = radius;
    }
    @Override
    double area() {
        return 4 * PI * radius * radius;
    }
    @Override
    double volume() {
        return 4.0/3.0 * PI * radius * radius * radius;
    }
}

class Cube extends Shape {
    private double side;

    public Cube(double side) {
        this.side = side;
    }
    @Override
    double area() {
        return 6 * side * side;
    }
    @Override
    double volume() {
        return side * side * side;
    }
}

class Cuboid extends Shape {
    private double length;
    private double width;
    private double height;

    public Cuboid(double length, double width, double height) {
        this.length = length;
        this.width = width;
        this.height = height;
    }
    @Override
    double area() {
        return 2 * (length * width + length * height + width * height);
    }
    @Override
    double volume() {
        return length * width * height;
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int N = scanner.nextInt();
        for (int i = 0; i < N; i++) {
            Cylinder cylinder = new Cylinder(scanner.nextDouble(), scanner.nextDouble());
            Sphere sphere = new Sphere(scanner.nextDouble());
            Cube cube = new Cube(scanner.nextDouble());
            Cuboid cuboid = new Cuboid(scanner.nextDouble(), scanner.nextDouble(), scanner.nextDouble());
            System.out.printf("%.2f %.2f\n", cylinder.area(), cylinder.volume());
            System.out.printf("%.2f %.2f\n", sphere.area(), sphere.volume());
            System.out.printf("%.2f %.2f\n", cube.area(), cube.volume());
            System.out.printf("%.2f %.2f\n", cuboid.area(), cuboid.volume());
        }
        scanner.close();
    }
}