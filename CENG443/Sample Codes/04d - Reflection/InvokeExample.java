// InvokeExample.java

// class lecture, 9/2/03

import java.lang.reflect.*;

class Sample 
{	
	public void aMethod(int x, double y )
	{
		System.out.println("hello, we're here");
		throw new NullPointerException( );		
	}	
}


class Test 
{
	static Object getObject( )
	{
		return new Sample();		
	}
		
	public static void main( String mainArgs[] )
	{
		Object s = getObject( );		
		Class c = s.getClass( );
		
		Class[] parms = new Class[] { Integer.TYPE, Double.TYPE };
		
		Method m = null;
		try {
		  m = c.getDeclaredMethod( "aMethod", parms );
		  int mods = m.getModifiers( );
		  if( Modifier.isPublic(mods))
		  	System.out.println("yes, it's public");
		}
		catch( NoSuchMethodException e )
		{
			System.out.println("Method not found");
		}	
		
		System.out.println( m.getName() );
		Object[] args = new Object[] { new Integer(5), new Double(3.5) };
		
		try {
			m.invoke( s, args );
		}
		catch( IllegalAccessException e )
		{
			System.out.println( "Error: the method is not accessible" );			
		}	
		catch( InvocationTargetException e )
		{
			System.out.println( e );
			System.out.println( e.getTargetException( ));
		}
	}	

}
	