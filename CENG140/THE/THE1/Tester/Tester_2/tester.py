"""
	Tester for 2020-2021 CENG 140 THE1
	Created by 
		Burak Metehan Tunçel (Tester, Test Cases, Case Generating)
		Emre Geçit (Test Cases, Case Generating)
	
	- Check the test cases number. It should be same with the file numbers in cases folder.
	- Check the passed cases number. It should be same with test cases.
	- Dimension refers to dimension of image. If you have different dimensional image change it.
	- Error List is for errors if there is any.

	Manual to use:
	- After necessary checking, go line 41 and change the program name "./the1" if it is necessary.
"""


import os
from pathlib import Path
from platform import system

if system()=="Windows":
	windows=True
	os.chdir(f"{Path(__file__).parent.absolute()}")
else:
	windows=False

test_cases = 750
passed_cases= 750
dimension = 25
error_list = []
the1_file_name = input("THE1 File Name:")
if not windows:
	the1_file_name = "./" + the1_file_name

for i in range(test_cases): # Test case number
	# Taking Expected Results
	expected_matrix=[]
	with open(f"./results/result{i}.txt", "r") as result_file:
		expected = result_file.readlines()
		expected_length = len(expected)
		if expected_length == dimension: #Dimension of Matrix
			for j in range(expected_length):
				expected_matrix.append(expected[j].split())
		else:
			expected_count = 0
			for j in range(expected_length):
				expected_matrix.append(expected[j].split())
			expected_count = expected_matrix[-1]
			expected_matrix = expected_matrix[:-1]
	
	# Running The Code
	os.system(f"{the1_file_name} < ./cases/case{i}.txt > output.txt")

	# Taking Given Matrix by Code
	given_matrix=[]
	with open("output.txt", "r") as result:
		given = result.readlines()
		given_length = len(given)
		if given_length == dimension:
			for j in range(given_length):
				given_matrix.append(given[j].split())
		else:
			given_count = 0
			for j in range(given_length):
				given_matrix.append(given[j].split())
			given_count = given_matrix[-1]
			given_matrix = given_matrix[:-1]

	# Comparing Expected Result with Given Result
	length = expected_length
	flag = False
	if length == dimension:
		for row in range(length):
			if flag:
				break
			for col in range(length):
				if expected_matrix[row][col] != given_matrix[row][col]:
					passed_cases-=1
					error_list.append(f"Error in case{i}.")
					flag=True
					break
	else:
		for row in range(length-1):
			if flag:
				break
			for col in range(length-1):
				if expected_matrix[row][col] != given_matrix[row][col]:
					passed_cases-=1
					error_list.append(f"Error in case{i}.")
					flag=True
					break
		if (not flag) and (given_count != expected_count):
			passed_cases-=1
			error_number = i
			error_list.append(f"Error in case{i}.")
			flag=True
			break
	
	if windows:
		if not (i+1)%15:
			os.system("cls")
			print("The process is running: %","%.2f"%((i+1)/7.50))
	else:
		if not (i+1)%15:
			os.system("clear")
			print("The process is running: %","%.2f"%((i+1)/7.50))

if not error_list:
	print("All done!")
	print("Correct result percentage rate: %{}".format(format(passed_cases/750*100, ".2f")))
else:
	print("There is/are error(s).")
	print("Correct result percentage rate: %{}".format(format(passed_cases/750*100, ".2f")))
	print("Errors:")
	print("\n".join(error_list))

if windows:
	os.system("del /f output.txt")
else:
	os.system("rm -f output.txt")
