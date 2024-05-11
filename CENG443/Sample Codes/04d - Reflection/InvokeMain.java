// InvokeMain.java

// by Mark Allen Weiss, modified by Kip Irvine
// Updated 12/24/2002

// Shows how to call a method and pass a parameter list, using Method.invoke().
// Also shows how to catch an exception thrown by the invoked method.

import java.lang.reflect.*;

class InvokeMain {
    public static void main(String[] args) {
        invokeMain("Dragon", new Object[] { new String[] { "Breathing", "Fire" } });
        invokeMain("Wizard", new Object[] { new String[] { "Casting", "a", "Spell" } });
    }

    public static void invokeMain(String className, Object[] params) {
        try {
            Class cl = Class.forName(className);
            Class[] mainsParamTypes = new Class[] { String[].class };

            Method mainMethod = cl.getDeclaredMethod("main", mainsParamTypes);

            if (!Modifier.isStatic(mainMethod.getModifiers()))
                System.out.println("Oops... main is not static!");
            if (!Modifier.isPublic(mainMethod.getModifiers()))
                System.out.println("Oops... main is not public!");
            else if (mainMethod.getReturnType() != Void.TYPE)
                System.out.println("Oops... main doesn't return void!");
            else
                mainMethod.invoke(null, params);
        } catch (ClassNotFoundException e) {
            System.out.println("Class not found: " + className);
        } catch (NoSuchMethodException e) {
            System.out.println("No method named main() found in " + className);
        } catch (IllegalAccessException e) {
            System.out.println("Cannot invoke main() in " + className);
        } catch (InvocationTargetException e) {
            System.out.println(e);
            e.getTargetException().printStackTrace();
        }
    }
}

class Wizard {
    public static void main(String[] args) {
        System.out.print("Wizard.main() is running...\nParameters: ");
        for (int i = 0; i < args.length; i++)
            System.out.print(args[i] + "/");
        System.out.println("");

        // enable the following line to demonstrate exceptions
        // throw new RuntimeException( "Exception thrown by Wizard.main()" );
    }
}

class Dragon {
    public static void main(String[] args) {
        System.out.print("Dragon.main() is running...\nParameters: ");
        for (int i = 0; i < args.length; i++)
            System.out.print(args[i] + "/");
        System.out.println();
    }
}
