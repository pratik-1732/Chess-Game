#include <bits/stdc++.h>
using namespace std;

const int BOARD_SIZE = 8;

enum PieceType
{
    KING,
    QUEEN,
    ROOK,
    BISHOP,
    KNIGHT,
    PAWN,
    EMPTY
};
enum Color
{
    WHITE,
    BLACK,
    NONE
};

class Board
{
private:
    vector<vector<Piece *>> board;
    Color currentPlayer;

public:
    Board()
    {
        board = vector<vector<Piece *>>(BOARD_SIZE, vector<Piece *>(BOARD_SIZE, nullptr));
        currentPlayer = WHITE;
        setupPieces();
    }

    void setupPieces()
    {
        board[0][4] = new King(WHITE, 0, 4);
        board[0][3] = new Queen(WHITE, 0, 3);
        board[7][4] = new King(BLACK, 7, 4);
        board[7][3] = new Queen(BLACK, 7, 3);
    }

    bool movePiece(int startX, int startY, int endX, int endY)
    {
        Piece *piece = board[startX][startY];
        if (piece == nullptr || piece->color != currentPlayer)
        {
            cout << "Invalid move!" << endl;
            return false;
        }

        if (piece->isValidMove(endX, endY, board))
        {
            board[endX][endY] = piece;
            board[startX][startY] = nullptr;
            piece->x = endX;
            piece->y = endY;
            currentPlayer = (currentPlayer == WHITE) ? BLACK : WHITE;
            return true;
        }
        else
        {
            cout << "Invalid move!" << endl;
            return false;
        }
    }

    void printBoard()
    {
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            for (int j = 0; j < BOARD_SIZE; ++j)
            {
                if (board[i][j] != nullptr)
                {
                    cout << board[i][j]->getSymbol() << " ";
                }
                else
                {
                    cout << ". ";
                }
            }
            cout << endl;
        }
    }
};

int main()
{
    Board chessBoard;
    chessBoard.printBoard();

    int startX, startY, endX, endY;
    while (true)
    {
        cout << "Enter move (startX startY endX endY): ";
        cin >> startX >> startY >> endX >> endY;
        if (chessBoard.movePiece(startX, startY, endX, endY))
        {
            chessBoard.printBoard();
        }
    }

    return 0;
}