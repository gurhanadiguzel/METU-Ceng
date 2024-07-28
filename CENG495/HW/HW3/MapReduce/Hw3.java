import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;

public class Hw3 extends Configured implements Tool {

    public int run(String[] args) throws Exception {
        if (args.length < 3) {
            System.err.println("Usage: Hw3 <job> <input path> <output path>");
            System.exit(-1);
        }

        String jobType = args[0];
        String inputPath = args[1];
        String outputPath = args[2];

        Job job = null;

        switch (jobType) {
            case "total":
                job = Job.getInstance(getConf(), "total");
                job.setJarByClass(TotalSalary.class);
                TotalSalary.configureJob(job, inputPath, outputPath);
                break;
            case "jobtitle":
                job = Job.getInstance(getConf(), "jobtitle");
                job.setJarByClass(AverageSalaryByJobTitle.class);
                AverageSalaryByJobTitle.configureJob(job, inputPath, outputPath);
                break;
            case "titleexperince":
                job = Job.getInstance(getConf(), "titleexperince");
                job.setJarByClass(AverageSalaryByJobTitleAndExperience.class);
                AverageSalaryByJobTitleAndExperience.configureJob(job, inputPath, outputPath);
                break;
            case "employeeresidence":
                job = Job.getInstance(getConf(), "employeeresidence");
                job.setJarByClass(EmployeeResidenceSalary.class);
                EmployeeResidenceSalary.configureJob(job, inputPath, outputPath);
                break;
            case "averageyear":
                job = Job.getInstance(getConf(), "averageyear");
                job.setJarByClass(AverageSalaryByWorkYear.class);
                AverageSalaryByWorkYear.configureJob(job, inputPath, outputPath);
                break;
            default:
                System.err.println("Unknown job type: " + jobType);
                System.exit(-1);
        }

        return job.waitForCompletion(true) ? 0 : 1;
    }

    public static void main(String[] args) throws Exception {
        int res = ToolRunner.run(new Configuration(), new Hw3(), args);
        System.exit(res);
    }
}
