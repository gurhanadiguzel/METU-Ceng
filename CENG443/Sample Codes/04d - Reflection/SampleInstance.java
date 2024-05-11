// SampleInstance.java

// from The Java Tutorial, article by Dale Green

// Shows how to construct an object at runtime and pass
// arguments to its constructor. Calls the Constructor.newInstance() method.

import java.lang.reflect.*;
import java.awt.*;

class SampleInstance {
    public static void main(String[] args) {

        Rectangle rectangle;
        Class rectangleDefinition;
        Class[] intArgsClass = new Class[] { int.class, int.class, int.class, int.class };
        Integer x = 13;
        Integer y = 15;
        Integer height = 12;
        Integer width = 34;
        Object[] intArgs = new Object[] { x, y, height, width };
        Constructor intArgsConstructor;
        // Constructor[] allConstructors;

        try {
            rectangleDefinition = Class.forName("java.awt.Rectangle");
            // nonArgsConstructor = rectangleDefinition.getConstructor();
            // System.out.println(nonArgsConstructor);
            // allConstructors = rectangleDefinition.getConstructors();
            // System.out.println(allConstructors[7]);
            intArgsConstructor = rectangleDefinition.getConstructor(intArgsClass);
            rectangle = (Rectangle) createObject(intArgsConstructor, intArgs);
        } catch (ClassNotFoundException e) {
            System.out.println(e);
        } catch (NoSuchMethodException e) {
            System.out.println(e);
        }
    }

    public static Object createObject(Constructor constructor, Object[] arguments) {

        System.out.println("Constructor: " + constructor.toString());
        Object object = null;

        try {
            object = constructor.newInstance(arguments);
            System.out.println("Object: " + object.toString());
            return object;
        } catch (InstantiationException e) {
            System.out.println(e);
        } catch (IllegalAccessException e) {
            System.out.println(e);
        } catch (IllegalArgumentException e) {
            System.out.println(e);
        } catch (InvocationTargetException e) {
            System.out.println(e);
        }
        return object;
    }
}
