// semaphores

import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.*;

class Writer implements Runnable {
    Buffer buffer;

    Writer(Buffer buffer) {
        this.buffer = buffer;
    }

    @Override
    public void run() {
        String item;
        for (int value = 0; value < 10; value++)
            try {
                item = Thread.currentThread().getName() + "-" + value;
                System.out.println("Written " + item);
                buffer.write(item);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
    }
}

class Reader implements Runnable {
    Buffer buffer;

    Reader(Buffer buffer) {
        this.buffer = buffer;
    }

    @Override
    public void run() {
        String item;
        while (true)
            try {
                item = buffer.read();
                System.out.println("Read " + item);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
    }
}

class Buffer {
    private Queue<String> list;
    private int size;
    private final Semaphore sEmpty;
    private final Semaphore sFull;

    public Buffer(int size) {
        this.list = new LinkedList<>();
        this.size = size;
        sFull = new Semaphore(0);
        sEmpty = new Semaphore(size);
    }

    public void write(String item) throws InterruptedException {
        sEmpty.acquire();
        list.add(item);
        sFull.release();
        Thread.sleep(500);
    }

    public String read() throws InterruptedException {
        sFull.acquire();
        String item = list.poll();
        sEmpty.release();
        Thread.sleep(500);
        return item;
    }
}

class Main {
    public static void main(String[] args) throws InterruptedException {
        Buffer buffer = new Buffer(2);
        ExecutorService taskList = Executors.newFixedThreadPool(30);
        taskList.execute(new Writer(buffer));
        taskList.execute(new Writer(buffer));
        taskList.execute(new Reader(buffer));
        taskList.shutdown();
    }
}