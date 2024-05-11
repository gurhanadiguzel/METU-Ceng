import java.util.concurrent.*;

class Multiplicator implements Runnable {
    Buffer buffer;
    int rowIndex;

    Multiplicator(Buffer buffer, int rowIndex) {
        this.buffer = buffer;
        this.rowIndex = rowIndex;
    }

    @Override
    public void run() {
        try {
            buffer.multiplicate(rowIndex);

        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

class Buffer {
    public int[][] matrixA;
    public int[][] matrixB;
    public int[][] result;

    public Buffer() {
        matrixA = new int[][] {
                { 1, 2, 3, 4 },
                { 5, 6, 7, 8 },
                { 9, 10, 11, 12 },
                { 13, 14, 15, 16 },
                { 17, 18, 19, 20 }
        };
        matrixB = new int[][] {
                { 21, 22, 23, 24, 25 },
                { 26, 27, 28, 29, 30 },
                { 31, 32, 33, 34, 35 },
                { 36, 37, 38, 39, 40 }
        };
        result = new int[matrixA.length][matrixB[0].length];
    }

    void multiplicate(int rowIndex) throws InterruptedException {
        try {
            int val = 0;
            for (int i = 0; i < matrixA.length; i++) {
                for (int j = 0; j < matrixB.length; j++) {
                    val += matrixA[rowIndex][j] * matrixB[j][i];
                }
                result[rowIndex][i] = val;
                val = 0;
            }

        } catch (Exception e) {
        }

    }
}

class MatrixMultiplication {
    public static void main(String[] args) {
        Buffer buffer = new Buffer();
        ExecutorService taskList = Executors.newFixedThreadPool(buffer.result.length);
        for (int i = 0; i < buffer.result.length; i++) {
            taskList.execute(new Multiplicator(buffer, i));
        }
        taskList.shutdown();

        for (int i = 0; i < buffer.result.length; i++) {
            for (int j = 0; j < buffer.result[0].length; j++) {
                System.out.print(buffer.result[i][j] + " ");

            }
            System.out.println();
        }
    }
}
