 
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


# SOLUTION:
def tictactoe(board):
    # check horizontals
    if board[0] == 'XXX' or board[1] == 'XXX' or board[2] == 'XXX':
        return 'X'
    if board[0] == 'OOO' or board[1] == 'OOO' or board[2] == 'OOO':
        return 'O'
    # check verticals
    if check_verticals(board, 'X'):
        return 'X'
    elif check_verticals(board, 'O'):
        return 'O'
    else:
        return 'tie'

def check_verticals(board, ch):
    return ((board[0][0] == ch and board[1][0] == ch and board[2][0] == ch) or \
        (board[0][1] == ch and board[1][1] == ch and board[2][1] == ch) or \
        (board[0][2] == ch and board[1][2] == ch and board[2][2] == ch))


# SAMPLE INPUT/OUTPUTs:
# == Input ==
print( tictactoe(['XOX', 'OOX', 'XXO']) )
# == Output ==
# 'tie'

# == Input ==
print( tictactoe(['XXO', 'OOX', 'XXX']) )
# == Output ==
# 'X'

# == Input ==
print( tictactoe(['XOO', 'XOX', 'XXO']) )
# == Output ==
# 'X'

# == Input ==
print( tictactoe(['XOO', 'XOO', 'OXO']) )
# == Output ==
# 'O'
