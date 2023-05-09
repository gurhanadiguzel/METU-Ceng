# CENG140 Section-1/2 THE2 Tester

Tester and Generator for the CENG 140 Section-1/2 Take Home Exam 2 in 2020-21 Spring Semester.

**Contributor**
- Reyhan Kalkan 
  
**Remarks:** 
- Generator and Tester are tested on Ubuntu. 
- Other linux distributions are not tested. Generator and Tester may work with other distributions.
- It will probably not work on Windows.

## Generator

Generator can be used to generate test cases randomly. It will create both test cases and their results. The number of test cases is not fixed. You will be asked to enter for case number.

### Prerequirements for Generator
- None

### Usage
1. Open your terminal.
2. Make sure that you are on right directory.
3. Run "test_case_generator".
4. Enter test case number. It needs to be an integer.

Generator will generate test cases.  

**Remark:**
If there is not "cases" or "results" directory. Before running Generator, create them.  
If you enter large number mistakenly, it will not control what number is and start creating cases. So, be careful with test case numbers.  
Also, if you enter large number, it can take a long time.

## Tester

Tester can be used to check outputs of your code and the pre-generated results.

### Prerequirements for Tester
- **GCC**:  
	Make sure that you have gcc in your system. GCC will be used to compile your code.  
  (The usage of gcc in tester (as an example): gcc functions.c ...)

### Usage
1. Extract cases.zip and results.zip in same directory.
	Prefer to use "Extract Here" option.
2. Copy your functions.c file to Tester directory.
	"functions.c" needs to be in same directory with "tester".
3. Open your terminal.
4. Make sure that you are on right directory.
5. Run "tester".

Tester will start checking your code. You should be able to see the progress on your terminal. After finishing testing, your results will be viewed on screen.  
If there is/are error(s), you should be able to see your errors in errors.txt. In errors.txt, you can see test case(s) and line(s) that error(s) occurred. You can see your output in "outputs" file.

### Reading Result/Output
There is not any indicator that shows you which lines belong to which functions. However, you can read the results/outputs by following way:
- In results, there is a block of float numbers. These are result of the function 1.
- After, there is a block of integer numbers. These are result of the function 2.
- After, there is a block of float numbers. These are result of the function 3.
- After, there is a single integer number. This is result of the function 4.
- After, there is a line of integer numbers. This is result of the function 5.
- After, there is a block of float numbers (50 lines). These are result of the function 6.
- After, there is a line of integer numbers. This is result of the function 7.
- After, there is a block of float numbers. These are result of the function 8.
- After, there is a line of integer numbers. This is result of the function 9.
- After, there is a line of integer numbers. This is result of the function 10.