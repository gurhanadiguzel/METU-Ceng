def split(string, delimiters):
    result = ['']
    i = 0
    while i < len(string):
        if string[i] in delimiters:
            result.append('')
        else:
            result[-1] += string[i]
        i += 1
    return result
