import java.lang.reflect.*;
import java.security.Permission;

class Test {
    private int id;

    Test(int x) {
        id = x;
    }

    private void f(int x, String s) {
        System.out.println(s + ":" + x * id);
    }
}

class Main {
    public static void main(String[] args) throws Exception {
        // System.setSecurityManager(new SecurityManager() {
        // public void checkPermission(Permission perm) {
        // if (perm instanceof ReflectPermission) { throw new SecurityException(); }
        // }
        // });

        Test t = new Test(3);
        Class c = Test.class;

        Method m = c.getDeclaredMethod("f", Integer.TYPE, String.class);
        m.setAccessible(true);
        Object[] args1 = { 11, "result" };
        m.invoke(t, args1);
    }
}
