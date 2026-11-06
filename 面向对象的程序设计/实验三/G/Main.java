// preset code start
interface Auto {
    public abstract void move();

    public abstract void stop();

    public abstract void dudu();
}

interface Sprinkler {
    public abstract void watering();
}

public class Main {
    public static void main(String args[]) {
        Car car = new Car();
        car.move();
        car.dudu();
        car.stop();

        FireTruck firetruck = new FireTruck();
        firetruck.move();
        firetruck.dudu();
        firetruck.stop();
        firetruck.watering();
    }
}
//preset code end
class Car implements Auto {
    public void move() {
        System.out.println("I am running very fast.");
    }
    public void stop() {
        System.out.println("I am stopping.");
    }
    public void dudu() {
        System.out.println("I am a car!Get out Every one!");
    }
}
class Truck implements Auto {
    public void move() {
        System.out.println("I am running very smoothly.");
    }
    public void stop() {
        System.out.println("I am slowly stopping.");
    }
    public void dudu() {
        System.out.println("I am a big Auto!Get out Every one and small car!");
    }
}
class FireTruck extends Truck implements Sprinkler {
    public void watering() {
        System.out.println("I am watering,No fire!");
    }
}