// SampleGet.java

// Example from the Java Tutorial that uses reflection to get 
// the height of a Java.awt Rectangle
// Original program by Dale Green; modified by Kip Irvine (1/14/2003)

import java.lang.reflect.Field;
import java.awt.Rectangle;

class SampleGet {

    public static void main(String[] args) {
        Rectangle r = new Rectangle(100, 325);
        printHeight(r);
    }

    static void printHeight(Rectangle r) {
        Class c = r.getClass();

        try {
            Field heightField = c.getField("height");
            Field widthField = c.getField("width");

            Integer heightValue = (Integer) heightField.get(r);
            Integer widthValue = (Integer) widthField.get(r);

            System.out.println("Height:" + heightValue + " Width:" + widthValue);
        } catch (NoSuchFieldException e) {
            System.out.println(e);
        } catch (SecurityException e) {
            System.out.println(e);
        } catch (IllegalAccessException e) {
            System.out.println(e);
        }
    }
}
