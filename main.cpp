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