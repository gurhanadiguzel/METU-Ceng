 
#  EXAMPLE-5 (Nihil, Lesson-3, Chapter-8)

#  Write a function named "tictactoe" that determines the outcome of the game in a given tic-tac-toe board.
#
#    The dimensions of the board is fixed and equal to three
#    The board is given as a list of strings
#    Each element of the list is a string containing three characters: 'X', 'O' or '-'
#    For instance the following board is represented as ['XOX', 'OOX', 'XXO']
#
#    XOX
#    OOX
#    XXO
#
#    The function should return 'X', 'O' or 'tie' depending on the outcome of the game
#    If there are three consecutive 'X's vertically or horizontally 'X' wins the game
#    If there are three consecutive 'O's vertically or horizontally 'O' wins the game
#    Otherwise the result is a 'tie'
#    Note that there will be no case where both players win

board = ['XOX', 'OOX', 'XXO']
def tictactoe(board):
    if board[0] == 'XXX' or board[1] == "XXX" or board[2] == "XXX":
        return "X"
    elif board[0] == 'OOO' or board[1] == "OOO" or board[2] == "OOO":
        return "O"
    
    if checkVertical("X", board):
        return "X"
    elif checkVertical("O", board):
        return "O"
    else:
        return "tie"
    
#    XOX    board[0]
#    OOX    board[1]
#    XXO    board[2]

def checkVertical(ch, board):
    return (board[0][0] == ch and board[1][0] == ch and board[2][0] == ch) or \
        (board[0][1] == ch and board[1][1] == ch and board[2][1] == ch) or \
        (board[0][2] == ch and board[1][2] == ch and board[2][2] == ch)


print(tictactoe(['--X', 'OOX', 'XXO']))
#output "tie"

print(tictactoe(['XXO','OOX',"XXX"]))
#output "X"

print(tictactoe(['XOO','XOX','XXO']))
#output "X"