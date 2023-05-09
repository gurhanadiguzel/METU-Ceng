#Recall that there are two fundamental structures in a directory tree: files and folders. Folders can contain other files and folders whereas files cannot.

#In python, directory tree of file systems can be represented easily using lists. Using list convention, folders can simply be represented as lists with first element being a string, which is name of the folder. Other elements in the list can be lists representing other folders under current folder or they can be strings representing files.

#Examples:

#    Folder named 'abc' which contains no other folders or files in it:

#    ['abc']

#    Another folder named 'ceng111' which contains one file named 'hw1.pdf':

    ['ceng111', 'hw1.pdf']

#    Another folder named 'Documents' which contains folders in (1) and (2) and two files named 'deneme.py' and 'chapter3.pdf'

 #   ['Documents', ['abc'], ['ceng111', 'hw1.pdf'], 'deneme.py', 'chapter3.pdf']

#Write a function named search_file that takes a file name and a directory tree as explained above and returns a string, the path if the file exists, and empty string otherwise. 


def search_file(name, tree):
    if name == tree[0]:
        return name
    elif name in tree[1:]:
        return tree[0] + '/' + name
    else:
        temp = process_dirs(name, tree[1:])
        if temp:
            return tree[0] + '/' + temp
        else:
            return ''

def process_dirs(name, tree):
    # this helper function calls search_file with only folders (i.e. lists)
    if not tree:
        return ''
    elif type(tree[0]) == list:
        temp = search_file(name, tree[0])
        if temp:
            return temp
        else:
            return process_dirs(name, tree[1:])
    else:
        return process_dirs(name, tree[1:])
