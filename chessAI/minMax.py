import chess
import sys

def minimaxRoot(depth, board ,isMaximizing):
    possibleMoves = board.legal_moves
    bestMove = -9999
    secondBest = -9999
    thirdBest = -9999
    bestMoveFinal = None
    for x in possibleMoves:
        move = chess.Move.from_uci(str(x))
        board.push(move)
        value = max(bestMove, minimax(depth - 1, board, not isMaximizing))
        board.pop()
        if( value > bestMove):
            thirdBest = secondBest
            secondBest = bestMove
            bestMove = value
            bestMoveFinal = move
    return bestMoveFinal

def minimax(depth, board, is_maximizing):
    if(depth == 0):
        return -evaluation(board)
    possibleMoves = board.legal_moves
    if(is_maximizing):
        bestMove = -9999
        for x in possibleMoves:
            move = chess.Move.from_uci(str(x))
            board.push(move)
            bestMove = max(bestMove,minimax(depth - 1, board, not is_maximizing))
            board.pop()
        return bestMove
    else:
        bestMove = 9999
        for x in possibleMoves:
            move = chess.Move.from_uci(str(x))
            board.push(move)
            bestMove = min(bestMove, minimax(depth - 1, board, not is_maximizing))
            board.pop()
        return bestMove

def evaluation(board):
    i = 0
    evaluation = 0
    x = True
    try:
        x = bool(board.piece_at(i).color)
    except AttributeError as e:
        x = x
    while i < 63:
        i += 1
        evaluation = evaluation + (getPieceValue(str(board.piece_at(i))) if x else -getPieceValue(str(board.piece_at(i))))
    return evaluation


def getPieceValue(piece):
    if(piece == None):
        return 0
    value = 0
    if piece == "P" or piece == "p":
        value = 10
    if piece == "N" or piece == "n":
        value = 30
    if piece == "B" or piece == "b":
        value = 30
    if piece == "R" or piece == "r":
        value = 50
    if piece == "Q" or piece == "q":
        value = 90
    if piece == 'K' or piece == 'k':
        value = 900
    #value = value if (board.piece_at(place)).color else -value
    return value

def calcBoard (b):
	ret = ""
	temp = 0
	for i in range(len(b)):
		if (b[i].isdigit()):
			temp = temp + 1
			if (i == len(b) - 1):
				ret += str(temp)
		else:
			if (temp != 0):
				ret += str(temp)
				temp = 0
			ret += b[i]
	return ret


def main () :
	boardS = sys.argv[1]
	boardS = boardS.replace('#' , '1')
	j = 0
	nBoard = ""
	for i in range (0 , len(boardS) + 1):
		if (i%8 == 0):
			nBoard += boardS[j : i]
			nBoard += "/"
			j = i
	nBoard = nBoard [1 : -1]
	nBoard = calcBoard(nBoard)
	BoardB = chess.Board(nBoard)
	move = minimaxRoot(3 , BoardB , True)
	movs = str(move)
	print (movs)
	#BoardB.push(move)
	#print (BoardB)

if __name__ == '__main__':
	main()

