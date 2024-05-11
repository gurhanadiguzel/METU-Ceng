// HeroSpy.java

// Shows how to override the default access level of a 
// class member.

// COP 4338 (Irvine, Spring 2003)
// Updated 12/26/2002

import java.lang.reflect.Field;

class Person {
	public Person(String pName) {
		name = pName;
	}

	public String toString() {
		return name;
	}

	private String name;
}

class Hero extends Person {
	public Hero(String pName, String pSecretIdentity) {
		super(pName);
		secretIdentity = pSecretIdentity;
	}

	public String toString() {
		return super.toString();
	}

	private String secretIdentity;
} // Hero

class HeroSpy {
	public static void main(String args[]) {
		Hero h1 = new Hero("Superman", "Clark Kent");
		System.out.println("h1 = " + h1.toString());

		try {
			Class cl = Hero.class;
			Field f = cl.getDeclaredField("secretIdentity");
			f.setAccessible(true);
			System.out.println("Secret identity = " + f.get(h1));
			f.set(h1, new String("Lois Lane"));
			System.out.println("New secret identity = " + f.get(h1));
		} catch (NoSuchFieldException e) {
			System.out.println("No such field");
		} catch (IllegalAccessException e) {
			System.out.println("Illegal access exception");
		} catch (java.security.AccessControlException e) {
			System.out.println("Security manager objects to this!");
		}
	} // main

} // HeroSpy