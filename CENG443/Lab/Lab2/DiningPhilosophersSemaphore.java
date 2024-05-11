import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicInteger;

class Fork {
    private final int forkId;

    public Fork(int forkId) {
        this.forkId = forkId;
    }

    public int getForkId() {
        return forkId;
    }
}

class Philosopher implements Runnable {
    private final int id;
    private final Semaphore leftFork;
    private final Semaphore rightFork;
    private final AtomicInteger counter;

    public Philosopher(int id, Semaphore leftFork, Semaphore rightFork, AtomicInteger counter) {
        this.id = id;
        this.leftFork = leftFork;
        this.rightFork = rightFork;
        this.counter = counter;
    }

    @Override
    public void run() {
        try {
            while (true) {
                think();

                if (counter.incrementAndGet() % 2 == 0) {
                    // To avoid deadlock, philosophers with even IDs pick up the right fork first
                    rightFork.acquire();
                    leftFork.acquire();
                } else {
                    leftFork.acquire();
                    rightFork.acquire();
                }

                eat();

                rightFork.release();
                leftFork.release();

                counter.incrementAndGet();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    private void think() throws InterruptedException {
        System.out.println("Philosopher " + id + " is thinking");
        Thread.sleep(ThreadLocalRandom.current().nextInt(1000, 2000));
    }

    private void eat() throws InterruptedException {
        System.out.println("Philosopher " + id + " is eating");
        Thread.sleep(ThreadLocalRandom.current().nextInt(1000, 2000));
    }
}

class DiningPhilosophersSemaphore {
    public static void main(String[] args) {
        int numPhilosophers = 5;
        Semaphore[] forks = new Semaphore[numPhilosophers];
        AtomicInteger counter = new AtomicInteger(1);

        for (int i = 0; i < numPhilosophers; i++) {
            forks[i] = new Semaphore(1);
        }

        ExecutorService executorService = Executors.newFixedThreadPool(numPhilosophers);

        try {
            for (int i = 1; i <= numPhilosophers; i++) {
                executorService.execute(new Philosopher(i, forks[i - 1], forks[i % numPhilosophers], counter));
            }
        } finally {
            executorService.shutdown();
        }
    }
}
