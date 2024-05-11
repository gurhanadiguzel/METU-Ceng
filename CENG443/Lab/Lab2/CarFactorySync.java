import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.*;

class EngineProduction implements Runnable {
    Buffer buffer;

    EngineProduction(Buffer buffer) {
        this.buffer = buffer;
    }

    @Override
    public void run() {
        while (true) {
            try {
                buffer.produceEngine();

            } catch (InterruptedException e) {
                e.printStackTrace();

            }
        }
    }
}

class GlassProduction implements Runnable {
    Buffer buffer;

    GlassProduction(Buffer buffer) {
        this.buffer = buffer;
    }

    @Override
    public void run() {
        while (true) {
            try {
                buffer.produceGlass();

            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

class WheelProduction implements Runnable {
    Buffer buffer;

    WheelProduction(Buffer buffer) {
        this.buffer = buffer;
    }

    @Override
    public void run() {
        while (true) {
            try {
                buffer.produceWheel();

            } catch (InterruptedException e) {
                e.printStackTrace();

            }
        }
    }
}

class AssemleCar implements Runnable {
    Buffer buffer;

    AssemleCar(Buffer buffer) {
        this.buffer = buffer;
    }

    @Override
    public void run() {
        while (true) {
            try {
                buffer.assemble();

                Thread.sleep(500);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}

class Buffer {
    public Queue<String> engineList, wheelList, glassList;
    public int maxEngineSize, maxWheelSize, maxGlassSize;
    public boolean engineProduction = false;
    public boolean wheelProduction = false;
    public boolean glassProduction = false;

    public Buffer(int engineSize, int wheelSize, int glassSize) {
        this.maxEngineSize = engineSize;
        this.maxWheelSize = wheelSize;
        this.maxGlassSize = glassSize;
        this.engineList = new LinkedList<>();
        this.wheelList = new LinkedList<>();
        this.glassList = new LinkedList<>();

    }

    public synchronized void produceEngine() throws InterruptedException {
        while (engineList.size() == maxEngineSize)
            wait();

        engineList.add(" ");
        if (engineList.size() == 1) {
            Actions.startEngineProductionLine();
        }
        Actions.produceEngine();
        if (engineList.size() == maxEngineSize) {
            Actions.stopEngineProductionLine();
            engineProduction = true;
            notifyAll();
        }
    }

    public synchronized void produceWheel() throws InterruptedException {
        while (wheelList.size() == maxWheelSize)
            wait();

        wheelList.add(" ");
        if (wheelList.size() == 1) {
            Actions.startWheelProductionLine();
        }
        Actions.produceWheel();
        if (wheelList.size() == maxWheelSize) {
            Actions.stopWheelProductionLine();
            wheelProduction = true;
            notifyAll();
        }
    }

    public synchronized void produceGlass() throws InterruptedException {
        while (glassList.size() == maxGlassSize)
            wait();

        glassList.add(" ");
        if (glassList.size() == 1) {
            Actions.startGlassProductionLine();
        }
        Actions.produceGlass();
        if (glassList.size() == maxGlassSize) {
            Actions.stopGlassProductionLine();
            glassProduction = true;
        }
    }

    public synchronized void assemble() throws InterruptedException {
        while (!engineProduction || !wheelProduction || !glassProduction) {
            wait();
        }
        Actions.startAssemblyLine();
        Actions.assemble();
        engineList.clear();
        glassList.clear();
        wheelList.clear();
        engineProduction = false;
        wheelProduction = false;
        glassProduction = false;
        notifyAll();
        Actions.stopAssemblyLine();

    }

}

class CarFactorySync {
    public static void main(String[] args) throws InterruptedException {
        Buffer buffer = new Buffer(1, 4, 6);
        ExecutorService taskList = Executors.newFixedThreadPool(4);
        taskList.execute(new EngineProduction(buffer));
        taskList.execute(new GlassProduction(buffer));
        taskList.execute(new WheelProduction(buffer));
        taskList.execute(new AssemleCar(buffer));

        taskList.shutdown();
    }
}
