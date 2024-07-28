import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.conf.Configured;
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
import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;

public class AverageSalaryByJobTitleAndExperience  {

    public static class SalaryMapper extends Mapper<LongWritable, Text, Text, DoubleWritable> {
        private Text jobTitleAndExperience = new Text();
        private DoubleWritable salary = new DoubleWritable();
        private static final int EXPERIENCE_LEVEL_INDEX = 1;
        private static final int JOB_TITLE_INDEX = 3;
        private static final int SALARY_IN_USD_INDEX = 6;

        @Override
        public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
            String[] fields = value.toString().split(",");
            if (fields.length == 11 && !fields[0].equals("work_year")) {
                try {
                    String experienceLevel = fields[EXPERIENCE_LEVEL_INDEX].trim();
                    if (experienceLevel.equals("SE") || experienceLevel.equals("MI") || experienceLevel.equals("EX")) {
                        String jobTitle = fields[JOB_TITLE_INDEX].trim();
                        jobTitleAndExperience.set(jobTitle + "-" + experienceLevel);
                        salary.set(Double.parseDouble(fields[SALARY_IN_USD_INDEX].trim()));
                        context.write(jobTitleAndExperience, salary);
                    }
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
            int count = 0;
            for (DoubleWritable value : values) {
                totalSalary += value.get();
                count++;
            }
            double averageSalary = totalSalary / count;
            context.write(key, new DoubleWritable(averageSalary));
        }
    }

    public static void configureJob(Job job, String inputPath, String outputPath) throws IOException {

        job.setJarByClass(AverageSalaryByJobTitleAndExperience.class);
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
