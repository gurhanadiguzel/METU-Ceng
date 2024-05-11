import java.util.concurrent.*;
import java.util.Random;

class FindMin {
    public static void main(String[] args) {
        int[] data = new int[20];
        Random random = new Random();
        for (int i = 0; i < data.length; i++) {
            data[i] = random.nextInt(1000);
            // Let's print each subarray in a line for checking
            System.out.print(data[i] + " ");
            if ((i + 1) % 5 == 0)
                System.out.println();
        }
        ForkJoinPool pool = new ForkJoinPool();
        FindMinTask task = new FindMinTask(data, 0, data.length);
        System.out.println("Minimum is " + pool.invoke(task));
    }
}

class FindMinTask extends RecursiveTask<Integer> {
    // A thread can easily handle, let's say, five elements
    private static final int SEQUENTIAL_THRESHOLD = 5;
    // The array with the numbers(we'll pass the same array in
    // every recursive call to avoid creating a lot of arrays)
    private int[] data;
    // The index that tells use where a task starts
    private int start;
    // The index that tells use where a task ends
    private int end;

    // Since compute() doesn't take parameters, you have to
    // pass in the task's constructor the data to work
    public FindMinTask(int[] data, int start, int end) {
        this.data = data;
        this.start = start;
        this.end = end;
    }

    @Override
    // Return type matches the generic
    protected Integer compute() {
        int length = end - start;
        if (length <= SEQUENTIAL_THRESHOLD) { // base case
            return computeMinimumDirectly();
        } else { // recursive case
            // Calcuate new subtasks range
            int mid = start + length / 2;
            FindMinTask leftTask = new FindMinTask(data, start, mid);
            FindMinTask rightTask = new FindMinTask(data, mid, end);
            // queue the first task
            leftTask.fork();
            // Return the miminum of all subtasks
            return Math.min(rightTask.compute(), leftTask.join());
        }
    }

    /** Method that find the minimum value */
    private int computeMinimumDirectly() {
        int min = Integer.MAX_VALUE;
        for (int i = start; i < end; i++)
            if (data[i] < min)
                min = data[i];
        return min;
    }
}
