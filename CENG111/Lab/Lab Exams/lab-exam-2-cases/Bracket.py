def balanced_brackets(n):
    """
    Return all strings containing exactly n balanced bracket pairs. 
    No duplicates! Order does not matter.
    
    n: A non-negative integer, the number of balanced bracket pairs.
    """
    
    if n == 0:
        return []
    if n == 1:
        return ["[]"]
    # halting conditions
    before = balanced_brackets(n-1)
    # In order to make only one recursive call we set a variable to recursive call
    new = []
    for el in range(len(before)):
        for a in range((n-1)*2+1):
            new.append(before[el][:a] + "[]" + before[el][a:])
    # first for loop for iterating the function on every element of balanced_brackets(n-1)
    # second for loop works like this:
    # we take a string for example "patates"
    # it inserts a "[]" before and after each letter and appends it to our list
    # to do this we need to iterate it for letter count +1
    # letter count = (n-1)*2
    # i am not sure how but n works too
    # "[]patates" "p[]atates" "pa[]tates" "pat[]ates" "pata[]tes" "patat[]es" "patate[]s" "patates[]"
    
    new = list(set(new))
    # Given function for removing duplicates
    return new



