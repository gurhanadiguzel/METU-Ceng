# HADOOP-MAPREDUCE

## Operating system used for developing the homework
- **Operating System:** Windows11

## Hadoop release used for the homework
- **Hadoop Version:** Hadoop 3.4.0
  - I used the latest version of Hadoop, 3.4.0. I created a new `data` folder in Hadoop which contains two more folders: `namenode` and `datanode`.
  - In Hadoop, I adjusted the following configuration files:
    - `hadoop-env.sh` (set the `JAVA_HOME` path)
    - `core-site.xml`
    - `mapred-site.xml`
    - `yarn-site.xml`
    - `hdfs-site.xml` (specified the paths for `datanode` and `namenode` folders)
  - I started all Hadoop daemons using the `start-all.sh` script.
  - Now `localhost:9870` can be accesible.

## JDK (Java Development Kit) version used for the homework
- **JDK Version:** Java 8 (jdk1.8.0)
  - I used Java 8 as it is required for compatibility with Hadoop.

## IDE (Integrated Development Environment) used for the homework
- **IDE:** IntelliJ IDEA
  - I used IntelliJ IDEA for writing the MapReduce classes.
  - I created a Maven project in IntelliJ and imported the necessary Apache Hadoop libraries.
  - The MapReduce classes were developed and tested within this environment.

## Building & Running the Project

### Build the Project
1. **Compile the Code:**
    ```sh
    hadoop com.sun.tools.javac.Main ∗.java
    ```
2. **Create the JAR File:**
    ```sh
    jar cf Hw3.jar ∗.class
    ```
3. **Create the Input Directory:**
    ```sh
    hdfs dfs -mkdir input
    ```
4. **Put the Input File:**
    ```sh
    hdfs dfs -put <input diretory>/salaries.csv /input
    ```

### Run the Project
1. **Run the Total Salary:**
    ```sh
      hadoop jar Hw3.jar Hw3 total /input/salaries.csv /output_total
    ```
2. **Run the Average Salary by Job Title:**
    ```sh
      hadoop jar Hw3.jar Hw3 jobtitle /input/salaries.csv /output_jobtitle
    ```
3. **Run the Average Salary by Job Title and Experience:**
    ```sh
      hadoop jar Hw3.jar Hw3 titleexperince /input/salaries.csv /output_titleexperince
    ```
4. **Run the Employee Residence Salary:**
    ```sh
      hadoop jar Hw3.jar Hw3 employeeresidence /input/salaries.csv /output_employeeresidence
    ```
5. **Run the Average Salary by Work Year:**
    ```sh
      hadoop jar Hw3.jar Hw3 averageyear /input/salaries.csv /output_averageyear
    ```

### Configuration Details
- **hadoop-env.sh:** Set the `JAVA_HOME` path.
- **core-site.xml:** Basic settings for Hadoop.
- **mapred-site.xml:** Configuration for the MapReduce framework.
- **yarn-site.xml:** Settings for the YARN resource manager.
- **hdfs-site.xml:** Configuration for HDFS including paths for `datanode` and `namenode`.
- set `JAVA_HOME`,`HADOOP_HOME` and `HADOOP_CLASSPATH` in environment variables correctly.

### Notes
- Make sure all Hadoop daemons are running before executing the MapReduce job.
- Ensure that the input path and output path provided are accessible and writable by Hadoop.

By following the steps and configurations mentioned above, you should be able to build and run the Hadoop MapReduce project successfully.
