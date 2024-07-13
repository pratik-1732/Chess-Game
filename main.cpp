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

// Base class for all pieces
class Piece
{
public:
    PieceType type;
    Color color;
    int x, y;

    Piece(PieceType type, Color color, int x, int y) : type(type), color(color), x(x), y(y) {}
    virtual bool isValidMove(int newX, int newY, vector<vector<Piece *>> &board) = 0;
    virtual char getSymbol() = 0;
};

// Derived classes for each piece type
class King : public Piece
{
public:
    King(Color color, int x, int y) : Piece(KING, color, x, y) {}

    bool isValidMove(int newX, int newY, vector<vector<Piece *>> &board) override
    {
        return abs(newX - x) <= 1 && abs(newY - y) <= 1;
    }

    char getSymbol() override
    {
        return (color == WHITE) ? 'K' : 'k';
    }
};

class Queen : public Piece
{
public:
    Queen(Color color, int x, int y) : Piece(QUEEN, color, x, y) {}

    bool isValidMove(int newX, int newY, vector<vector<Piece *>> &board) override
    {
        return (newX == x || newY == y || abs(newX - x) == abs(newY - y));
    }

    char getSymbol() override
    {
        return (color == WHITE) ? 'Q' : 'q';
    }
};

class Rook : public Piece
{
public:
    Rook(Color color, int x, int y) : Piece(ROOK, color, x, y) {}

    bool isValidMove(int newX, int newY, vector<vector<Piece *>> &board) override
    {
        return (newX == x || newY == y);
    }

    char getSymbol() override
    {
        return (color == WHITE) ? 'R' : 'r';
    }
};

class Bishop : public Piece
{
public:
    Bishop(Color color, int x, int y) : Piece(BISHOP, color, x, y) {}

    bool isValidMove(int newX, int newY, vector<vector<Piece *>> &board) override
    {
        return abs(newX - x) == abs(newY - y);
    }

    char getSymbol() override
    {
        return (color == WHITE) ? 'B' : 'b';
    }
};

class Knight : public Piece
{
public:
    Knight(Color color, int x, int y) : Piece(KNIGHT, color, x, y) {}

    bool isValidMove(int newX, int newY, vector<vector<Piece *>> &board) override
    {
        int dx = abs(newX - x);
        int dy = abs(newY - y);
        return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
    }

    char getSymbol() override
    {
        return (color == WHITE) ? 'N' : 'n';
    }
};

class Pawn : public Piece
{
public:
    Pawn(Color color, int x, int y) : Piece(PAWN, color, x, y) {}

    bool isValidMove(int newX, int newY, vector<vector<Piece *>> &board) override
    {
        int direction = (color == WHITE) ? -1 : 1;
        if (newX == x + direction && newY == y && board[newX][newY] == nullptr)
        {
            return true;
        }
        else if (newX == x + direction && abs(newY - y) == 1 && board[newX][newY] != nullptr && board[newX][newY]->color != color)
        {
            return true;
        }
        return false;
    }

    char getSymbol() override
    {
        return (color == WHITE) ? 'P' : 'p';
    }
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
        // Setup White Pieces
        board[0][0] = new Rook(WHITE, 0, 0);
        board[0][1] = new Knight(WHITE, 0, 1);
        board[0][2] = new Bishop(WHITE, 0, 2);
        board[0][3] = new Queen(WHITE, 0, 3);
        board[0][4] = new King(WHITE, 0, 4);
        board[0][5] = new Bishop(WHITE, 0, 5);
        board[0][6] = new Knight(WHITE, 0, 6);
        board[0][7] = new Rook(WHITE, 0, 7);
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            board[1][i] = new Pawn(WHITE, 1, i);
        }

        // Setup Black Pieces
        board[7][0] = new Rook(BLACK, 7, 0);
        board[7][1] = new Knight(BLACK, 7, 1);
        board[7][2] = new Bishop(BLACK, 7, 2);
        board[7][3] = new Queen(BLACK, 7, 3);
        board[7][4] = new King(BLACK, 7, 4);
        board[7][5] = new Bishop(BLACK, 7, 5);
        board[7][6] = new Knight(BLACK, 7, 6);
        board[7][7] = new Rook(BLACK, 7, 7);
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            board[6][i] = new Pawn(BLACK, 6, i);
        }
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