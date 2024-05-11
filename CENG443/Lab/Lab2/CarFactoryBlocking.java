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
                if (buffer.engineList.size() == 1) {
                    Actions.startEngineProductionLine();
                }
                Actions.produceEngine();
                if (buffer.engineList.size() == buffer.maxEngineSize) {
                    Actions.stopEngineProductionLine();
                    buffer.engineProduction = true;
                }

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
                if (buffer.glassList.size() == 1) {
                    Actions.startGlassProductionLine();
                }
                Actions.produceGlass();
                if (buffer.glassList.size() == buffer.maxGlassSize) {
                    Actions.stopGlassProductionLine();
                    buffer.glassProduction = true;
                }
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
                if (buffer.wheelList.size() == 1) {
                    Actions.startWheelProductionLine();
                }
                Actions.produceWheel();
                if (buffer.wheelList.size() == buffer.maxWheelSize) {
                    Actions.stopWheelProductionLine();
                    buffer.wheelProduction = true;
                }
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
                if (buffer.engineProduction && buffer.wheelProduction && buffer.glassProduction) {
                    Actions.startAssemblyLine();
                    Actions.assemble();
                    buffer.assemble();
                    Actions.stopAssemblyLine();
                }
                Thread.sleep(500);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}

class Buffer {
    public BlockingQueue<String> engineList, wheelList, glassList;
    public int maxEngineSize, maxWheelSize, maxGlassSize;
    public boolean engineProduction = false;
    public boolean wheelProduction = false;
    public boolean glassProduction = false;

    public Buffer(int engineSize, int wheelSize, int glassSize) {
        this.maxEngineSize = engineSize;
        this.maxWheelSize = wheelSize;
        this.maxGlassSize = glassSize;
        this.engineList = new LinkedBlockingQueue(engineSize);
        this.wheelList = new LinkedBlockingQueue(wheelSize);
        this.glassList = new LinkedBlockingQueue(glassSize);

    }

    public void produceEngine() throws InterruptedException {
        engineList.put(" ");

    }

    public void produceWheel() throws InterruptedException {
        wheelList.put(" ");
    }

    public void produceGlass() throws InterruptedException {
        glassList.put(" ");
    }

    public void assemble() throws InterruptedException {
        engineList.clear();
        glassList.clear();
        wheelList.clear();
        engineProduction = false;
        wheelProduction = false;
        glassProduction = false;
    }

}

class CarFactoryBlocking {
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
