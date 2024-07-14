#include <iostream>
#include <vector>

using namespace std;

const int BOARD_SIZE = 8;

enum Color
{
    WHITE,
    BLACK
};

class Piece
{
public:
    Color color;
    int x, y;

    Piece(Color color, int x, int y) : color(color), x(x), y(y) {}
    virtual char getSymbol() const = 0;
    virtual bool isValidMove(int destRow, int destCol, const vector<vector<Piece *>> &board) = 0;
};

class Pawn : public Piece
{
public:
    Pawn(Color color, int x, int y) : Piece(color, x, y) {}

    char getSymbol() const override
    {
        return color == WHITE ? 'P' : 'p';
    }

    bool isValidMove(int destRow, int destCol, const vector<vector<Piece *>> &board) override
    {
        // Check if destination coordinates are within bounds
        if (destRow < 0 || destRow >= BOARD_SIZE || destCol < 0 || destCol >= BOARD_SIZE)
        {
            return false;
        }

        if (color == WHITE)
        {
            if (destRow == x - 1 && destCol == y && board[destRow][destCol] == nullptr)
            {
                return true;
            }
            if (x == 6 && destRow == x - 2 && destCol == y && board[destRow][destCol] == nullptr)
            {
                return true;
            }
            if (destRow == x - 1 && (destCol == y - 1 || destCol == y + 1) && board[destRow][destCol] != nullptr)
            {
                return true;
            }
        }
        else
        {
            if (destRow == x + 1 && destCol == y && board[destRow][destCol] == nullptr)
            {
                return true;
            }
            if (x == 1 && destRow == x + 2 && destCol == y && board[destRow][destCol] == nullptr)
            {
                return true;
            }
            if (destRow == x + 1 && (destCol == y - 1 || destCol == y + 1) && board[destRow][destCol] != nullptr)
            {
                return true;
            }
        }

        return false;
    }
};

class Knight : public Piece
{
public:
    Knight(Color color, int x, int y) : Piece(color, x, y) {}

    char getSymbol() const override
    {
        return color == WHITE ? 'N' : 'n';
    }

    bool isValidMove(int destRow, int destCol, const vector<vector<Piece *>> &board) override
    {
        int dx = abs(destRow - x);
        int dy = abs(destCol - y);
        return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
    }
};

class Bishop : public Piece
{
public:
    Bishop(Color color, int x, int y) : Piece(color, x, y) {}

    char getSymbol() const override
    {
        return color == WHITE ? 'B' : 'b';
    }

    bool isValidMove(int destRow, int destCol, const vector<vector<Piece *>> &board) override
    {
        return abs(destRow - x) == abs(destCol - y);
    }
};

class Rook : public Piece
{
public:
    Rook(Color color, int x, int y) : Piece(color, x, y) {}

    char getSymbol() const override
    {
        return color == WHITE ? 'R' : 'r';
    }

    bool isValidMove(int destRow, int destCol, const vector<vector<Piece *>> &board) override
    {
        return (destRow == x) || (destCol == y);
    }
};

class Queen : public Piece
{
public:
    Queen(Color color, int x, int y) : Piece(color, x, y) {}

    char getSymbol() const override
    {
        return color == WHITE ? 'Q' : 'q';
    }

    bool isValidMove(int destRow, int destCol, const vector<vector<Piece *>> &board) override
    {
        return (destRow == x) || (destCol == y) || (abs(destRow - x) == abs(destCol - y));
    }
};

class King : public Piece
{
public:
    King(Color color, int x, int y) : Piece(color, x, y) {}

    char getSymbol() const override
    {
        return color == WHITE ? 'K' : 'k';
    }

    bool isValidMove(int destRow, int destCol, const vector<vector<Piece *>> &board) override
    {
        return abs(destRow - x) <= 1 && abs(destCol - y) <= 1;
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

    bool movePiece(int startRow, int startCol, int endRow, int endCol)
    {
        cout << "Attempting to move piece from (" << startRow << ", " << startCol << ") to (" << endRow << ", " << endCol << ")" << endl;
        Piece *piece = board[startRow][startCol];
        if (piece == nullptr || piece->color != currentPlayer)
        {
            cout << "Invalid move: No piece at start or wrong turn!" << endl;
            return false;
        }

        if (piece->isValidMove(endRow, endCol, board))
        {
            if (board[endRow][endCol] == nullptr || board[endRow][endCol]->color != currentPlayer)
            {
                board[endRow][endCol] = piece;
                board[startRow][startCol] = nullptr;
                piece->x = endRow;
                piece->y = endCol;
                currentPlayer = (currentPlayer == WHITE) ? BLACK : WHITE;
                return true;
            }
            else
            {
                cout << "Invalid move: Cannot capture your own piece." << endl;
            }
        }
        else
        {
            cout << "Invalid move: Move not valid for piece." << endl;
        }

        return false;
    }

    void printBoard()
    {
        cout << "    ";
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            cout << char('A' + i) << "   ";
        }
        cout << endl;

        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            cout << "  +---+---+---+---+---+---+---+---+" << endl;
            cout << (BOARD_SIZE - i) << " ";
            for (int j = 0; j < BOARD_SIZE; ++j)
            {
                if (board[i][j] != nullptr)
                {
                    cout << "| " << board[i][j]->getSymbol() << " ";
                }
                else
                {
                    cout << "|   ";
                }
            }
            cout << "|" << endl;
        }
        cout << "  +---+---+---+---+---+---+---+---+" << endl;
    }

    void printTurn()
    {
        cout << (currentPlayer == WHITE ? "White" : "Black") << "'s turn." << endl;
    }
};

int main()
{
    Board chessBoard;
    chessBoard.printBoard();
    chessBoard.printTurn();

    int startRow, endRow;
    char startColChar, endColChar;
    while (true)
    {
        cout << "Enter move (startRow startCol endRow endCol): ";
        cin >> startRow >> startColChar >> endRow >> endColChar;

        int startCol = startColChar - 'A';
        int endCol = endColChar - 'A';

        // Convert from 1-indexed to 0-indexed for internal representation
        startRow = BOARD_SIZE - startRow;
        endRow = BOARD_SIZE - endRow;

        if (chessBoard.movePiece(startRow, startCol, endRow, endCol))
        {
            chessBoard.printBoard();
            chessBoard.printTurn();
        }
    }

    return 0;
}
