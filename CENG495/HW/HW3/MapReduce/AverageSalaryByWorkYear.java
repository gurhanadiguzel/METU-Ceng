import java.io.IOException;

import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.DoubleWritable;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Partitioner;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;

public class AverageSalaryByWorkYear {

    public static class SalaryMapper extends Mapper<LongWritable, Text, Text, DoubleWritable> {
        private Text workYear = new Text();
        private DoubleWritable salary = new DoubleWritable();
        private static final int WORK_YEAR_INDEX = 0;
        private static final int SALARY_IN_USD_INDEX = 6;
        @Override
        public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
            String[] fields = value.toString().split(",");
            if (fields.length == 11 && !fields[0].equals("work_year")) {
                int year = Integer.parseInt(fields[WORK_YEAR_INDEX].trim());
                double salaryInUsd = Double.parseDouble(fields[SALARY_IN_USD_INDEX].trim());
                workYear.set(Integer.toString(year));
                salary.set(salaryInUsd);

                if(year<2023){
                    context.write(new Text("Before 2023"), salary);
                }else {
                    context.write(workYear, salary);
                }
            }
        }
    }

    public static class SalaryReducer extends Reducer<Text, DoubleWritable, Text, DoubleWritable> {
        @Override
        public void reduce(Text key, Iterable<DoubleWritable> values, Context context) throws IOException, InterruptedException {
            double totalSalary = 0;
            int count = 0;
            for (DoubleWritable value : values) {
                totalSalary += value.get();
                count++;
            }
            double averageSalary = totalSalary / count;
            context.write(key, new DoubleWritable(averageSalary));
        }
    }



    public static class YearPartitioner extends Partitioner<Text, DoubleWritable> {
        @Override
        public int getPartition(Text key, DoubleWritable value, int numPartitions) {
            String year = key.toString();
            if (year.equals("2024") ) {
                return 0; // Partition 0 for 2024
            } else if (year.equals("2023")) {
                return 1; // Partition 1 for 2023
            } else {
                return 2; // Partition 2 for before 2023
            }
        }
    }

    public static void configureJob(Job job, String inputPath, String outputPath) throws IOException{

        job.setJarByClass(AverageSalaryByWorkYear.class);
        job.setMapperClass(SalaryMapper.class);
        job.setReducerClass(SalaryReducer.class);
        job.setPartitionerClass(YearPartitioner.class);

        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(DoubleWritable.class);

        job.setInputFormatClass(TextInputFormat.class);
        job.setOutputFormatClass(TextOutputFormat.class);

        FileInputFormat.addInputPath(job, new Path(inputPath));
        FileOutputFormat.setOutputPath(job, new Path(outputPath));

        job.setNumReduceTasks(3);
    }
}
