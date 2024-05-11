import java.util.Arrays;
import java.util.List;
import java.util.concurrent.*;

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
    Buffer buffer;

    public Philosopher(int id, Buffer buffer) {
        this.id = id;
        this.buffer = buffer;
    }

    @Override
    public void run() {
        try {
            while (true) {
                buffer.think(id);

                List<Fork> forks = buffer.eat(id);

                buffer.putdown(id, forks);
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

class Buffer {
    BlockingQueue<Fork> forks;

    Buffer(int size) {
        forks = new LinkedBlockingQueue<>(size);
        for (int i = 0; i < size; i++) {
            forks.add(new Fork(i + 1));
        }
    }

    void think(int id) throws InterruptedException {
        System.out.println("Philosopher " + id + " is thinking");
        Thread.sleep(ThreadLocalRandom.current().nextInt(1000, 2000));
    }

    List<Fork> eat(int id) throws InterruptedException {
        Fork leftFork = forks.take();
        Fork rightFork = forks.take();

        System.out.println("Philosopher " + id + " " + leftFork.getForkId() + " picked up left fork");
        System.out.println("Philosopher " + id + " " + rightFork.getForkId() + " picked up right fork");

        System.out.println("Philosopher " + id + " is eating");

        Thread.sleep(ThreadLocalRandom.current().nextInt(1000, 2000));
        List<Fork> eatenForks = Arrays.asList(leftFork, rightFork);
        return eatenForks;
    }

    void putdown(int id, List<Fork> forkList) throws InterruptedException {
        // Put down forks
        forks.offer(forkList.get(0));
        forks.offer(forkList.get(1));

        System.out.println("Philosopher " + id + " " + forkList.get(0).getForkId() + " put down left fork");
        System.out.println("Philosopher " + id + " " + forkList.get(1).getForkId() + " put down right fork");
    }
}

class DiningPhilosophersBlocking {
    public static void main(String[] args) {
        int numPhilosophers = 5;
        Buffer buffer = new Buffer(numPhilosophers);
        ExecutorService executorService = Executors.newFixedThreadPool(numPhilosophers);

        try {
            for (int i = 1; i <= numPhilosophers; i++) {
                executorService.execute(new Philosopher(i, buffer));
            }
        } finally {
            executorService.shutdown();
        }
    }
}
