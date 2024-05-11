// blocking queue

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
    private BlockingQueue<String> list;
    private int size;

    public Buffer(int size) {
        this.list = new LinkedBlockingDeque<>(2);
        this.size = size;
    }

    public void write(String item) throws InterruptedException {
        list.put(item);
        Thread.sleep(500);
    }

    public String read() throws InterruptedException {
        String item = list.take();
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