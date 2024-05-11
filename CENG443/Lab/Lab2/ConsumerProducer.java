import java.util.concurrent.*;
import java.util.concurrent.locks.ReentrantLock;

class Consumer implements Runnable {
    Buffer buffer;

    Consumer(Buffer buffer) {
        this.buffer = buffer;
    }

    @Override
    public void run() {
        while (true) {
            try {
                buffer.consume();
                Thread.sleep((int) (Math.random() * 10000));

            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

class Producer implements Runnable {
    Buffer buffer;

    Producer(Buffer buffer) {
        this.buffer = buffer;
    }

    @Override
    public void run() {
        while (true) {
            try {
                buffer.produce();

                Thread.sleep((int) (Math.random() * 10000));

            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

class Buffer {
    private BlockingQueue<String> queue;
    ReentrantLock lock;
    int i = 0;

    public Buffer(int size) {
        queue = new LinkedBlockingQueue<>(size);
        lock = new ReentrantLock();
    }

    void produce() throws InterruptedException {
        lock.lock();
        String item = " Item: " + i++;
        System.out.println(Thread.currentThread().getName() + " Produced " + item);
        queue.put(item);
        lock.unlock();
    }

    void consume() throws InterruptedException {
        String item = queue.take();
        System.out.println(Thread.currentThread().getName() + " Consumed " + item);
    }
}

class ConsumerProducer {
    public static void main(String[] args) {
        Buffer buffer = new Buffer(5);
        ExecutorService taskList = Executors.newFixedThreadPool(3);
        taskList.execute(new Consumer(buffer));
        taskList.execute(new Producer(buffer));
        taskList.execute(new Producer(buffer));

        taskList.shutdown();
    }
}