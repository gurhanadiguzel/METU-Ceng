import numpy as np
import math


def numsArray():
    numsArray = np.array([1 + (10**6 + 1 - i) * 10 ** (-8) for i in range(1, n + 1)])
    return numsArray


# Calculate the theoretical sum using the summation formula for an arithmetic sequence.
def theoreticalSum():
    firstTerm = 1 + (10**6 + 1 - 1) * 10 ** (-8)  # Value of the first term
    lastTerm = 1 + (10**6 + 1 - n) * 10 ** (-8)  # Value of the last term
    theoreticalSum = (n * (firstTerm + lastTerm)) / 2
    return theoreticalSum


# Calculates the sum of the elements of nums using naive summation.
def naiveSum(nums, dtype):
    sum = np.zeros((), dtype=dtype)
    for num in nums:
        sum += num
    return sum


# Calculates the sum of the elements of nums using compensated summation.
def compensatedSum(nums, dtype):
    sum = np.zeros((), dtype=dtype)
    c = np.zeros((), dtype=dtype)
    for num in nums:
        t = sum + num
        if abs(sum) >= abs(num):
            c += (sum - t) + num
        sum = t
    return sum + c


# Calculates the sum of the elements of nums using pairwise summation.
def pairwiseSum(nums, dtype):
    numsLen = len(nums)
    if numsLen <= 10:
        sum = np.zeros((), dtype=dtype)
        for i in range(0, numsLen):
            sum += nums[i]

    else:
        halfIndex = math.floor(numsLen / 2)
        sumLeft = pairwiseSum(nums[0:halfIndex], dtype)
        sumRight = pairwiseSum(nums[halfIndex:], dtype)
        sum = sumLeft + sumRight
    return sum


n = 10**6
numsArrayDouble = numsArray()
numsArraySingle = np.array(numsArrayDouble, dtype=np.float32)

# Print the results.
theoreticalSum = theoreticalSum()
print("Theoretical Sum:", theoreticalSum)

# Calculate the sum of the elements of nums using naive summation in single and double precision.
naiveSumSingle = naiveSum(numsArraySingle, np.float32)
naiveSumDouble = naiveSum(numsArrayDouble, np.float64)
print("Naive Sum in single precision:", naiveSumSingle)
print("Naive Sum in double precision:", naiveSumDouble)

# Calculate the sum of the elements of nums using compensated summation in single and double precision.
compensatedSumSingle = compensatedSum(numsArraySingle, np.float32)
compensatedSumDouble = compensatedSum(numsArrayDouble, np.float64)
print("Compensated Sum in single precision:", compensatedSumSingle)
print("Compensated Sum in double precision:", compensatedSumDouble)

# Calculate the sum of the elements of nums using pairwise summation in single and double precision.
pairwiseSumSingle = pairwiseSum(numsArraySingle, np.float32)
pairwiseSumDouble = pairwiseSum(numsArrayDouble, np.float64)
print("Pairwise Sum in single precision:", pairwiseSumSingle)
print("Pairwise Sum in double precision:", pairwiseSumDouble)
