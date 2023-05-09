# Write a function named "substr_position" which takes two strings as arguments and 
# returns the positions of the occurrences of the second string in the first string.

#>>> substr_position("bacbacbacbbab","abc")
#[]
#>>> substr_position("abababc", "aba")
#[0, 2]
#>>> substr_position("bacbacbacbbab","bac")
#[0, 3, 6]


def substr_position(S, s):
	result = []
	i = 0
	while i < len(S):
		if prefix(S[i:], s):
			result.append(i)
		i += 1
	return result

def prefix(S, s):
	if len(s) == 0:
		return True
	elif len(S) == 0:
		return False
	elif S[0] == s[0]:
		return prefix(S[1:], s[1:])
	else:
		return False

