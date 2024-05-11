class Main {

    static void myMethod(int n) throws Exception {
        try {
            switch (n) {
                case 1:
                    System.out.println("1st case");
                    return;
                case 3:
                    System.out.println("3rd case");
                    throw new RuntimeException("3!");
                case 4:
                    System.out.println("4th case");
                    throw new Exception("4!");
                case 2:
                    System.out.println("2nd case");
            }
        } catch (RuntimeException e) {
            System.out.print("RuntimeException: ");
            System.out.println(e.getMessage());
        } finally {
            System.out.println("finally entered.");
        }
    }

    public static void main(String args[]) {
        for (int i = 1; i <= 4; i++) {
            try {
                myMethod(i);
            } catch (Exception e) {
                System.out.print("Exception caught: ");
                System.out.println(e.getMessage());
            }
            System.out.println();
        }
    }

}
