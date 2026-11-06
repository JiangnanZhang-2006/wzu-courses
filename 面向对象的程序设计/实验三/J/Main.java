import java.util.Scanner;
class Student {
    private String id;
    private String name;
    private Character gender;
    private double[] scores;
    private double averageScore;
    private double totalScore;
    public Student(String id, String name, Character gender, double[] scores) {
        this.id = id;
        this.name = name;
        this.gender = gender;
        this.scores = scores;
        calculateAverageScore();
        calculateTotalScore();
    }
    public void printStudent() {
        System.out.printf("%s %s %c %.2f %.2f %.2f %.2f %.2f\n", id, name, gender, scores[0], scores[1], scores[2], averageScore, totalScore);
    }
    public String getId() {
        return id;
    }
    public String getName() {
        return name;
    }
    public Character getGender() {
        return gender;
    }
    public double[] getScores() {
        return scores;
    }
    public void setId(String id) {
        this.id = id;
    }
    public void setName(String name) {
        this.name = name;
    }
    public void setGender(Character gender) {
        this.gender = gender;
    }
    public void setScores(double[] scores) {
        calculateAverageScore();
        calculateTotalScore();
        this.scores = scores;
    }
    public void calculateAverageScore() {
        double sum = 0;
        for (double score : scores) {
            sum += score;
        }
        averageScore = sum / scores.length;
    }
    public void calculateTotalScore() {
        double sum = 0;
        for (double score : scores) {
            sum += score;
        }
        totalScore = sum;
    }
    public double getAverageScore() {
        calculateAverageScore();
        return averageScore;
    }
    public double getTotalScore() {
        calculateTotalScore();
        return totalScore;
    }
}
class StudentManager {
    private Student[] students;
    public StudentManager() {
        students = new Student[100];
        for (int i = 0; i < students.length; i++) {
            students[i] = null;
        }
    }
    public void insertStudent(Student student) {
        for (int i = 0; i < students.length; i++) {
            if (students[i] == null) {
                students[i] = student;
                break;
            }
        }
        sortStudentsById();
    }
    public void sortStudentsById() {
        for (int i = 0; i < students.length; i++) {
            for (int j = i + 1; j < students.length; j++) {
                if (students[i] != null && students[j] != null && students[i].getId().compareTo(students[j].getId()) > 0) {
                    Student temp = students[i];
                    students[i] = students[j];
                    students[j] = temp;
                }
            }
        }
    }
    public void listStudents() {
        for (Student student : students) {
            if (student != null) {
                student.printStudent();
            }
        }
    }
    public void printStudent(String id) {
        for (int i = 0; i < 100; i++) {
            if (students[i] != null && students[i].getId().equals(id)) {
                students[i].printStudent();
                break;
            }
        }
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        StudentManager studentManager = new StudentManager();
        while (true) {
            String cmd = scanner.next();
            if (cmd.equals("QUIT")) {
                System.out.println("Good bye!");
                scanner.close();
                break;
            } else if (cmd.equals("INSERT")) {
                String id = scanner.next();
                String name = scanner.next();
                Character gender = scanner.next().charAt(0);
                double[] scores = new double[3];
                for (int i = 0; i < 3; i++) {
                    scores[i] = scanner.nextDouble();
                }
                studentManager.insertStudent(new Student(id, name, gender, scores));
                studentManager.printStudent(id);
            } else if (cmd.equals("LIST")) {
                studentManager.listStudents();
            }
        }
    }
}