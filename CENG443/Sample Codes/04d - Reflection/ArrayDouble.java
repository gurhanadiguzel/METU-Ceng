// ArrayDouble.java

/** Shows how the Array.newInstance() method can be used with getClass() 
	to double the size of an arbitrary array type.
	
	Array class provides static methods to dynamically create and access Java arrays.
	
*/

import java.lang.reflect.Array;

class Canine {
	public Canine(String pName) {
		name = pName;
	}

	public String toString() {
		return name;
	}

	private String name;
}

class ArrayDouble {
	/**
	 * Does not work, because the function always returns an array of
	 * Object, regardless of the argument's actual array type.
	 */
	/*
	 * public static Object[] doubleArray( Object[] arr )
	 * {
	 * int newSize = arr.length * 2;
	 * 
	 * Object[] newArray = new Object[ newSize ];
	 * 
	 * for( int i = 0; i < arr.length; i++ )
	 * newArray[ i ] = arr[ i ];
	 * 
	 * return newArray;
	 * }
	 */

	/**
	 * Using the reflection API, we can query the array type
	 * and construct a new array of the same type.
	 */

	public static Object[] doubleArray(Object[] arr) {
		Class c1 = arr.getClass();
		if (!c1.isArray())
			return null;

		int oldSize = Array.getLength(arr);
		int newSize = oldSize * 2;
		System.out.println(c1.getName());

		System.out.println(c1.getComponentType());
		Object[] newArray = (Object[]) Array.newInstance(c1.getComponentType(), newSize);

		for (int i = 0; i < arr.length; i++)
			newArray[i] = arr[i];

		return newArray;
	}

	/**
	 * Creates an array of the same type as the obj parameter.
	 */
	public static Object[] makeArray(Object obj, int arraySize) {
		Class c1 = obj.getClass();
		return (Object[]) Array.newInstance(c1, arraySize);
	}

	public static void main(String[] args) throws ClassNotFoundException {
		// call a method that creates an array from an object
		Object[] dogs = makeArray(new Canine(""), 5);
		dogs[0] = new Canine("Fluffy");

		// Use the Array.newInstance() method to dynamically
		// create an array of any known type.

		Object[] newArray = null;

		String className = "Canine"; // try "Bovine"
		try {
			Class c1 = Class.forName(className);
			newArray = (Object[]) Array.newInstance(c1, 10);
			System.out.println("Array creation successful");
		} catch (ClassNotFoundException e) {
			System.out.println(className + " class not found: cannot create newArray[]");
		}

		// Demonstrate the two versions of doubleArray():

		Canine[] kennel = new Canine[10];
		kennel[0] = new Canine("Chow");
		kennel[9] = new Canine("Boxer");

		try {
			kennel = (Canine[]) doubleArray(kennel); // double it
			kennel[19] = new Canine("Spaniel"); // test the new size
			System.out.println("Array doubling successful");
		} catch (ClassCastException e) {
			System.out.println("Error casting Object[] into kennel[]");
		}

	} // main

} // ArrayDouble