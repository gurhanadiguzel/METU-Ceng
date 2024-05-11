import java.util.concurrent.*;

class WithDraw implements Runnable {
    Buffer buffer;

    public WithDraw(Buffer buffer) {
        this.buffer = buffer;
    }

    @Override
    public void run() {
        while (true) {
            try {
                buffer.withdraw(200);
                Thread.sleep(1000);

            } catch (Exception e) {
                // TODO: handle exception
            }

        }
    }
}

class Deposit implements Runnable {
    Buffer buffer;

    public Deposit(Buffer buffer) {
        this.buffer = buffer;
    }

    @Override
    public void run() {
        while (true) {
            try {
                buffer.deposit(100);
                Thread.sleep(1000);
            } catch (Exception e) {
                // TODO: handle exception
            }

        }

    }
}

class Buffer {
    private Semaphore semaphore1;
    int total;

    public Buffer() {
        total = 1000;
        semaphore1 = new Semaphore(1);
    }

    void withdraw(int money) {
        try {
            semaphore1.acquire();
            if (total >= money) {
                total -= money;
                System.out.println("Withdraw " + money + " Total  = " + total);
            } else {
                System.out.println("Cannot Withdraw " + money + " Total  = " + total);

            }
            semaphore1.release();
        } catch (Exception e) {
            // TODO: handle exception
        }

    }

    void deposit(int money) {
        try {
            semaphore1.acquire();
            total += money;
            System.out.println("Deposit " + money + " Total  = " + total);
            semaphore1.release();
        } catch (Exception e) {
            // TODO: handle exception
        }
    }

}

class Bank {
    public static void main(String[] args) {
        Buffer buffer = new Buffer();
        ExecutorService taskList = Executors.newFixedThreadPool(2);
        taskList.execute(new WithDraw(buffer));
        taskList.execute(new Deposit(buffer));
        taskList.shutdown();
    }
}
