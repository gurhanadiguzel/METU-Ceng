import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.DoubleWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;

import java.io.IOException;

public class TotalSalary {

    public static class SalaryMapper extends Mapper<LongWritable, Text, Text, DoubleWritable> {
        private static final Text OUTPUT_KEY = new Text("Total amount of salaries:");
        private DoubleWritable salary = new DoubleWritable();
        private static final int SALARY_IN_USD_INDEX = 6;

        @Override
        public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
            String[] fields = value.toString().split(",");
            if (fields.length == 11 && !fields[0].equals("work_year")) {
                try {
                    salary.set(Double.parseDouble(fields[SALARY_IN_USD_INDEX].trim()));
                    context.write(OUTPUT_KEY, salary);
                } catch (NumberFormatException e) {
                    // Skip invalid records
                }
            }
        }
    }

    public static class SalaryReducer extends Reducer<Text, DoubleWritable, Text, DoubleWritable> {
        @Override
        public void reduce(Text key, Iterable<DoubleWritable> values, Context context) throws IOException, InterruptedException {
            double totalSalary = 0;
            for (DoubleWritable value : values) {
                totalSalary += value.get();
            }
            context.write(key, new DoubleWritable(totalSalary));
        }
    }

    public static void configureJob(Job job, String inputPath, String outputPath) throws IOException {
        job.setJarByClass(TotalSalary.class);
        job.setMapperClass(SalaryMapper.class);
        job.setReducerClass(SalaryReducer.class);

        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(DoubleWritable.class);

        job.setInputFormatClass(TextInputFormat.class);
        job.setOutputFormatClass(TextOutputFormat.class);

        FileInputFormat.addInputPath(job, new Path(inputPath));
        FileOutputFormat.setOutputPath(job, new Path(outputPath));
    }
}
