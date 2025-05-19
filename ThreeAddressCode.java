import java.util.*;

public class ThreeAddressCode {
    static int tempCount = 0;

    // Generate new temporary variable like t0, t1, etc.
    static String newTemp() {
        return "t" + (tempCount++);
    }

    // Return precedence of operators
    static int precedence(char op) {
        if (op == '*' || op == '/') return 2;
        if (op == '+' || op == '-') return 1;
        return 0;
    }

    // Convert infix to postfix and generate TAC
    static void generateTAC(char[] expr) {
        char left = expr[0];  // e.g., a in a=b+c
        List<Character> postfix = new ArrayList<>();
        Stack<Character> stack = new Stack<>();

        for (int i = 2; i < expr.length; i++) { // Start from index 2 (skip 'a=')
            char ch = expr[i];

            if (Character.isLetterOrDigit(ch)) {
                postfix.add(ch);
            } else {
                while (!stack.isEmpty() && precedence(stack.peek()) >= precedence(ch)) {
                    postfix.add(stack.pop());
                }
                stack.push(ch);
            }
        }

        // Pop remaining operators
        while (!stack.isEmpty()) {
            postfix.add(stack.pop());
        }

        // Generate TAC from postfix
        Stack<String> tempStack = new Stack<>();

        for (char token : postfix) {
            if (Character.isLetterOrDigit(token)) {
                tempStack.push(String.valueOf(token)); // push operands as Strings
            } else {
                String op2 = tempStack.pop();
                String op1 = tempStack.pop();
                String temp = newTemp();
                System.out.println(temp + " = " + op1 + " " + token + " " + op2);
                tempStack.push(temp);
            }
        }

        // Final assignment
        System.out.println(left + " = " + tempStack.peek());
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter expression (e.g. a=b+c*d): ");
        String input = sc.nextLine();
        char[] expr = input.toCharArray();
        System.out.println("\nThree Address Code:");
        generateTAC(expr);
        sc.close();
    }
}