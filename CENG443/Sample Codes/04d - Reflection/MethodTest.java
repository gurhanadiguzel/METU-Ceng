// MethodTest1.java

// Demonstrate getConstructors(), getDeclaredMethods(),
// getMethods(), getParameterTypes() functions.
// Updated 1/14/2003

// Suggested practice:
// #1: Display the parameter list of each constructor in the Hero class.
// #2: When displaying a list of method names, display "package, public, 
//		or private" before each method name.
// #3: Call getDeclaredField() to access the strength field

import java.lang.reflect.Method;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;

class Hero implements Comparable {
	public Hero() {
		name = "unknown";
		strength = 0;
	}

	public Hero(String pName, int str) {
		name = pName;
		strength = str;
	}

	public int compareTo(Object rhs) {
		Hero other = (Hero) rhs;
		return getName().compareTo(other.getName());
	}

	public String getName() {
		return name + " " + strength;
	}

	void setName(String pName) {
		name = pName;
	}

	private void restoreStrength() {
		strength += (int) (java.lang.Math.random() * 10) % 5;
	}

	private String name;
	public int strength;
} // Hero

class MethodTest {
	public static void main(String[] args) {
		Class c1 = null;
		try {
			// create Class object from a class name
			c1 = Class.forName("Hero");
		} catch (ClassNotFoundException e) {
			System.out.println("Unable to find the class");
			System.exit(1);
		}

		// get and display all interfaces
		Class clArray[] = c1.getInterfaces();

		for (int i = 0; i < clArray.length; i++)
			System.out.println("Interface: " + clArray[i].getName());

		// get and display all public constructors
		Constructor[] cArray = c1.getConstructors();
		for (int i = 0; i < cArray.length; i++)
			System.out.println("Constructor: " + cArray[i].toString());

		// get inherited and current public methods
		// Method[] mArray = c1.getMethods( );

		// get only locally declared methods, possibly private.
		Method[] mArray = c1.getDeclaredMethods();

		// display the array of methods
		for (int i = 0; i < mArray.length; i++)
			System.out.println("Method: " + mArray[i].getName());

		// display parameter types for the first method in mArray
		Class parms[] = mArray[2].getParameterTypes();
		System.out.print("Parameter list for " + mArray[2].getName() + ": ( ");
		for (int i = 0; i < parms.length; i++)
			System.out.print(parms[i].getName() + " ");
		System.out.println(")");

		// get the value of a Hero field
		String fieldName = "strength";
		try {
			Object aHero = new Hero("Tuna Man", 12);
			Field f = aHero.getClass().getDeclaredField(fieldName);
			System.out.println("Tuna Man's " + fieldName + " = " + f.get(aHero));

			// demonstrate the Field.equals() method
			System.out.println(f.equals(c1.getField("strength")));

			// use the set() method to change the value of the field
			f.set(aHero, new Integer(10));
			System.out.println("Tuna Man's " + fieldName + " = " + f.get(aHero));
		} catch (NoSuchFieldException e) {
			System.out.println("No such field:" + fieldName);
		} catch (IllegalAccessException e) {
			System.out.println("Field is private:" + fieldName);
		}

	}

}