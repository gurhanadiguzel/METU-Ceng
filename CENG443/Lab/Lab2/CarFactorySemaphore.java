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

            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

class Buffer {
    private final Semaphore sEngine;
    private final Semaphore sWheel;
    private final Semaphore sGlass;
    private final Semaphore sAssemble1;
    private final Semaphore sAssemble2;
    private final Semaphore sAssemble3;

    public Buffer() {
        sEngine = new Semaphore(1);
        sWheel = new Semaphore(1);
        sGlass = new Semaphore(1);
        sAssemble1 = new Semaphore(0);
        sAssemble2 = new Semaphore(0);
        sAssemble3 = new Semaphore(0);

    }

    public void produceEngine() throws InterruptedException {
        sEngine.acquire();
        Actions.startEngineProductionLine();
        for (int i = 0; i < 1; i++) {
            Actions.produceEngine();
        }
        Actions.stopEngineProductionLine();
        sAssemble1.release();
    }

    public void produceWheel() throws InterruptedException {
        sWheel.acquire();
        Actions.startWheelProductionLine();
        for (int i = 0; i < 4; i++) {
            Actions.produceWheel();
        }
        Actions.stopWheelProductionLine();
        sAssemble2.release();
    }

    public void produceGlass() throws InterruptedException {
        sGlass.acquire();
        Actions.startGlassProductionLine();
        for (int i = 0; i < 6; i++) {
            Actions.produceGlass();
        }
        Actions.stopGlassProductionLine();
        sAssemble3.release();
    }

    public void assemble() throws InterruptedException {
        sAssemble1.acquire();
        sAssemble2.acquire();
        sAssemble3.acquire();

        Actions.startAssemblyLine();
        Actions.assemble();

        sEngine.release();
        sWheel.release();
        sGlass.release();

        Actions.stopAssemblyLine();
    }
}

public class CarFactorySemaphore {
    public static void main(String[] args) throws InterruptedException {
        Buffer buffer = new Buffer();
        ExecutorService taskList = Executors.newFixedThreadPool(4);
        taskList.execute(new EngineProduction(buffer));
        taskList.execute(new GlassProduction(buffer));
        taskList.execute(new WheelProduction(buffer));
        taskList.execute(new AssemleCar(buffer));

        taskList.shutdown();
    }
}
