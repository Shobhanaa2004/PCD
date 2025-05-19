import java.util.*;

public class SimpleOptimizer {
    static class Expr {
        char left;
        String right;

        Expr(char l, String r) {
            left = l;
            right = r;
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        List<Expr> expressions = new ArrayList<>();

        System.out.print("Enter number of expressions: ");
        int n = sc.nextInt();

        for (int i = 0; i < n; i++) {
            System.out.print("Left: ");
            char left = sc.next().charAt(0);
            System.out.print("Right: ");
            String right = sc.next();
            expressions.add(new Expr(left, right));
        }

        System.out.println("\nIntermediate Code:"); 
        for (Expr e : expressions) 
            System.out.println(e.left + " = " + e.right);

        // Dead Code Elimination
        List<Expr> used = new ArrayList<>();
        for (int i = 0; i < expressions.size() - 1; i++) {
            char left = expressions.get(i).left;
            boolean isUsed = false;
            for (int j = i + 1; j < expressions.size(); j++) {
                if (expressions.get(j).right.contains(String.valueOf(left))) {
                    isUsed = true;
                    break;
                }
            }
            if (isUsed) used.add(expressions.get(i));
        }
        used.add(expressions.get(n - 1)); // last expression always used

        System.out.println("\nAfter Dead Code Elimination:");
        for (Expr e : used)
            System.out.println(e.left + " = " + e.right);

        // Common Subexpression Elimination
        for (int i = 0; i < used.size(); i++) {
            for (int j = i + 1; j < used.size(); j++) {
                if (used.get(i).right.equals(used.get(j).right)) {
                    char replaceChar = used.get(j).left;
                    char keepChar = used.get(i).left;
                    used.remove(j--); // remove duplicate
                    for (Expr e : used) {
                        e.right = e.right.replace(replaceChar, keepChar);
                    }
                }
            }
        }

        System.out.println("\nOptimized Code:");
        for (Expr e : used)
            System.out.println(e.left + " = " + e.right);
    }
}