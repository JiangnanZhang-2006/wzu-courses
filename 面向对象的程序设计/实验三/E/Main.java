import java.util.Scanner;
import java.util.Vector;
abstract class Person {
    private String name;
    private int age;
    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }
    public String getName() {
        return name;
    }
    public int getAge() {
        return age;
    }
    public abstract void print();
}
class Employee extends Person {
    private String empId;
    private String department;
    private int level;
    public Employee(String name, int age, String empId, String department, int level) {
        super(name, age);
        this.empId = empId;
        this.department = department;
        this.level = level;
    }
    public String getEmpId() {
        return this.empId;
    }
    public String getDepartment() {
        return this.department;
    }
    public int getLevel() {
        return this.level;
    }
    public void print() {
        System.out.printf("I am a Employee\nMy name is %s,I am %d years old.\nI am a %d level Employee.My employeeNumber is %s.I am working in %s\n", super.getName(), super.getAge(), level, empId, department);
    }
}
class Manager extends Employee {
    private Vector<Person> subordinates;
    public Manager(String name, int age) {
        this(name, age, null, null, 0);
    }
    public Manager(String name, int age, String empId, String department, int level) {
        super(name, age, empId, department, level);
        this.subordinates = new Vector<>();
    }
    public Vector<Person> getSubordinates() {
        return subordinates;
    }
    public void print() {
        System.out.printf("I am a Manager\nMy name is %s,I am %d years old.\nI am a %d level Employee.My employeeNumber is %s.I am working in %s\nMy subordinate has:\n", super.getName(), super.getAge(), super.getLevel(), super.getEmpId(), super.getDepartment());
        boolean first = true;
        for (Person subordinate : subordinates) {
            if (first) {
                System.out.printf("%s", subordinate.getName());
                first = false;
            } else {
                System.out.printf(",%s", subordinate.getName());
            }
        }
        System.out.println(".");
    }
}
public class Main {
    public static void main(String arg[]) {
        Employee e1 = new Employee("zhangsan", 20, "s101", "d01", 3);
        e1.print();
        System.out.println();

        Employee e2 = new Employee("lisi", 20, "s202", "d02", 4);
        e2.print();
        System.out.println();

        e2 = new Employee("maliu", 20, "s102", "d01", 5);

        Manager m1 = new Manager("wangwu", 30, "s100", "d01", 9);
        m1.getSubordinates().addElement(e1);
        m1.getSubordinates().addElement(e2);
        m1.print();
        System.out.println();
    }
}