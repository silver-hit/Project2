/* 
 * File:   main.cpp
 * Author: Micheal Okey-okoro
 *
 * Created on December 17, 2023, 4:32 PM
 */


/* The code defines classes and interfaces for a chess game, including a ChessBoard class and a
ChessPiece class, with each chess piece class implementing its own isValidMove() and getSymbol()
functions. */
#include <iostream>
#include <iomanip>
#include <vector>
#include <cctype> 

/* The code defines classes and interfaces for a chess game, including a ChessBoard class and a
ChessPiece class. */
// enum to represent different piece colors
enum class PieceColor {
    RED,
    BLUE
};

// Forward declaration of ChessPiece class
class ChessPiece;

/* The above class defines an interface for common chess piece behaviors. */
// Interface for common chess piece behaviors
class ChessPieceInterface {
public:
    virtual bool isValidMove(int rowFrom, int colFrom, int rowTo, int colTo) const = 0;
    virtual char getSymbol() const = 0;
    virtual PieceColor getColor() const = 0;
    virtual ~ChessPieceInterface() = default;
};

// Class to represent the ChessBoard/* The ChessBoard class represents a chess board and provides
//methods for moving pieces, checking for threats, and determining


class ChessBoard {
private:
    std::vector<std::vector<ChessPiece*>> board;
    bool gameOver;
    
   // bool isPathClear(int rowFrom, int colFrom, int rowTo, int colTo) const;

public:
    /* The above code is defining a class called ChessBoard. This class represents a chess board and
    provides various methods for manipulating and checking the state of the board. */
    ChessBoard();
    ~ChessBoard();

    void display() const;
    ChessPiece* getPiece(int row, int col) const;
    bool movePiece(int rowFrom, int colFrom, int rowTo, int colTo);
    bool isSquareUnderThreat(int row, int col, PieceColor currentPlayer) const;
    bool isCheckmate(PieceColor currentPlayer) ;
    bool canEscapeCheck(int kingRow, int kingCol, PieceColor currentPlayer) const;
    bool isMovePuttingKingInCheck(int fromRow, int fromCol, int toRow, int toCol, PieceColor currentPlayer) const;
    bool isPlayerKingCaptured(PieceColor playerColor) const;
    bool isGameOver();
};

/* The above code defines a set of classes for different chess pieces, each inheriting from a base
class, with each class implementing its own isValidMove() and getSymbol() functions. */
// Base class for ChessPiece
class ChessPiece : public ChessPieceInterface {
protected:
    PieceColor color;
    ChessBoard* board; 
    bool isPathClear(int rowFrom, int colFrom, int rowTo, int colTo) const;

public:
    ChessPiece(PieceColor pieceColor) : color(pieceColor), board(nullptr) {}

    // Setter function for the chessboard
    void setChessBoard(ChessBoard* chessBoard) {
        board = chessBoard;
    }
    
    PieceColor getColor() const override {
        return color;
    }

    bool isValidMove(int rowFrom, int colFrom, int rowTo, int colTo) const override {
        // Default implementation (can be overridden by derived classes)
        return true;
    }
};

/* The Pawn class is a derived class of ChessPiece and implements the isValidMove and getSymbol
functions. */
// Derived class for Pawn
class Pawn : public ChessPiece {
public:
    using ChessPiece::ChessPiece;

    bool isValidMove(int rowFrom, int colFrom, int rowTo, int colTo) const override;
    char getSymbol() const override;
};

/* The Rook class is a derived class of ChessPiece and overrides the isValidMove and getSymbol
functions. */
// Derived class for Rook
class Rook : public ChessPiece {
public:
    using ChessPiece::ChessPiece;

    bool isValidMove(int rowFrom, int colFrom, int rowTo, int colTo) const override;
    char getSymbol() const override;
};

/* The Knight class is a subclass of ChessPiece and overrides the isValidMove and getSymbol functions. */
class Knight : public ChessPiece {
public:
    using ChessPiece::ChessPiece;
    
    bool isValidMove(int rowFrom, int colFrom, int rowTo, int colTo) const override;
    char getSymbol() const override;
     
};

/* The Bishop class is a subclass of ChessPiece and overrides the isValidMove and getSymbol functions. */
class Bishop : public ChessPiece {
public:
    using ChessPiece::ChessPiece;
    
    bool isValidMove(int rowFrom, int colFrom, int rowTo, int colTo) const override;
    char getSymbol() const override;
};

/* The Queen class is a subclass of ChessPiece and overrides the isValidMove and getSymbol functions. */
class Queen : public ChessPiece {
public:
    using ChessPiece::ChessPiece;
    
    bool isValidMove(int rowFrom, int colFrom, int rowTo, int colTo) const override;
    char getSymbol() const override;
};

/* The King class is a subclass of ChessPiece and overrides the isValidMove and getSymbol functions. */
class King : public ChessPiece {
public:
    using ChessPiece::ChessPiece;
    
    bool isValidMove(int rowFrom, int colFrom, int rowTo, int colTo) const override;
    char getSymbol() const override;
};



/**
 * The ChessBoard constructor initializes the chessboard with pieces, including pawns, rooks, knights,
 * bishops, queens, and kings.
 */
/**
 * The ChessBoard constructor initializes the chessboard with pieces, including pawns, rooks, knights,
 * bishops, queens, and kings.
 */
// Implementation of member functions for ChessBoard
ChessBoard::ChessBoard() {
    // Initialize the chessboard with pieces
    // Initialize the chessboard with pieces
    board.resize(8, std::vector<ChessPiece*>(8, nullptr));

    // Initialize pawns
    for (int i = 0; i < 8; ++i) {
        board[1][i] = new Pawn(PieceColor::RED);
        board[6][i] = new Pawn(PieceColor::BLUE);
    }

    // Initialize rooks
    board[0][0] = new Rook(PieceColor::RED);
    board[0][7] = new Rook(PieceColor::RED);
    board[7][0] = new Rook(PieceColor::BLUE);
    board[7][7] = new Rook(PieceColor::BLUE);
    
    //Initialize Knights
    board[0][1] = new Knight(PieceColor::RED);
    board[0][6] = new Knight(PieceColor::RED);
    board[7][1] = new Knight(PieceColor::BLUE);
    board[7][6] = new Knight(PieceColor::BLUE);

   //Initialize Bishops
    board[0][2] = new Bishop(PieceColor::RED);
    board[0][5] = new Bishop(PieceColor::RED);
    board[7][2] = new Bishop(PieceColor::BLUE);
    board[7][5] = new Bishop(PieceColor::BLUE);
    
    //Initialize Queens
    board[0][3] = new Queen(PieceColor::RED);
    board[7][3] = new Queen(PieceColor::BLUE);
    
    //Initialize Kings
    board[0][4] = new King(PieceColor::RED);
    board[7][4] = new King(PieceColor::BLUE);

    

}
/**
 * The function `isPathClear` checks if the path between two positions on a chessboard is clear of
 * obstructions.
 */

/**
 * The destructor of the ChessBoard class cleans up dynamically allocated ChessPiece objects.
 */
ChessBoard::~ChessBoard() {
    // Clean up dynamically allocated ChessPiece objects
    for (auto& row : board) {
        for (auto& piece : row) {
            delete piece;
        }
    }
}

/**
 * The function displays the current state of a chessboard with colored pieces.
 */
void ChessBoard::display() const {
    std::cout << "    A  B  C  D  E  F  G  H" << std::endl;
    for (int i = 0; i < 8; ++i) {
        std::cout << i + 1 << " |";
        for (int j = 0; j < 8; ++j) {
            ChessPiece* piece = board[i][j];
            char symbol = (piece) ? piece->getSymbol() : '.';

            // Add color to the displayed piece based on its color
            if (piece) {
                std::cout << (piece->getColor() == PieceColor::RED ? "\033[1;31m" : "\033[1;34m");
                std::cout << std::setw(2) << symbol << "\033[0m" << '|';
            } else {
                std::cout << std::setw(2) << symbol << '|';
            }
        }
        std::cout << std::endl;
    }

}

/**
 * The function returns the ChessPiece object at the specified position on the chess board.
 * 
 * @param row The row parameter represents the row index of the chessboard. It specifies the vertical
 * position of the chess piece on the board. The valid range for the row parameter is from 0 to 7,
 * inclusive.
 * @param col The "col" parameter represents the column index of the chessboard. It is used to specify
 * the column position of the chess piece that we want to retrieve from the chessboard.
 * 
 * @return a pointer to a ChessPiece object.
 */
ChessPiece* ChessBoard::getPiece(int row, int col) const {
    // Return the ChessPiece object at the specified position
    if (row >= 0 && row < 8 && col >= 0 && col < 8) {
        return board[row][col];
    } else {
        return nullptr;
    }
}


/**
 * The function `isPathClear` checks if the path between two positions on a chessboard is clear for a
 * chess piece to move.
 * 
 * @param rowFrom The starting row of the chess piece's position.
 * @param colFrom The parameter `colFrom` represents the starting column of the chess piece's position.
 * @param rowTo The parameter "rowTo" represents the row number of the destination position on the
 * chessboard.
 * @param colTo The parameter `colTo` represents the column index of the destination position on the
 * chessboard.
 * 
 * @return a boolean value. It returns true if the path from the starting position (rowFrom, colFrom)
 * to the ending position (rowTo, colTo) is clear, and false otherwise.
 */
bool ChessPiece::isPathClear(int rowFrom, int colFrom, int rowTo, int colTo) const {
     int rowDiff = rowTo - rowFrom;
    int colDiff = colTo - colFrom;

    auto isValidPosition = [](int row, int col) {
        return row >= 0 && row < 8 && col >= 0 && col < 8;
    };

    // Check if the path is clear horizontally
    if (rowDiff == 0) {
        int colStep = (colDiff > 0) ? 1 : -1;
        for (int col = colFrom + colStep; col != colTo; col += colStep) {
            if (!isValidPosition(rowFrom, col) || board->getPiece(rowFrom, col)) {
                return false; // Obstruction in the path or out of bounds
            }
        }
    }
    // Check if the path is clear vertically
    else if (colDiff == 0) {
        int rowStep = (rowDiff > 0) ? 1 : -1;
        for (int row = rowFrom + rowStep; row != rowTo; row += rowStep) {
            if (!isValidPosition(row, colFrom) || board->getPiece(row, colFrom)) {
                return false; // Obstruction in the path or out of bounds
            }
        }
    }
    // Check if the path is clear diagonally
    else if (std::abs(rowDiff) == std::abs(colDiff)) {
        int rowStep = (rowDiff > 0) ? 1 : -1;
        int colStep = (colDiff > 0) ? 1 : -1;

        for (int i = 1; i < std::abs(rowDiff); ++i) {
            int newRow = rowFrom + i * rowStep;
            int newCol = colFrom + i * colStep;
            if (!isValidPosition(newRow, newCol) || board->getPiece(newRow, newCol)) {
                return false; // Obstruction in the path or out of bounds
            }
        }
    } else {
        // Invalid path
        return false;
    }

    // Path is clear
    return true;
}

/**
 * The movePiece function in the ChessBoard class checks if a move is valid and performs the move if it
 * is, capturing the opponent's king if necessary.
 * 
 * @param rowFrom The row index of the square from which the ChessPiece is being moved.
 * @param colFrom The parameter "colFrom" represents the column index of the square from which the
 * chess piece is being moved.
 * @param rowTo The parameter "rowTo" represents the row index of the destination square where the
 * chess piece is being moved to.
 * @param colTo The parameter "colTo" represents the column index of the destination square where the
 * ChessPiece is being moved to.
 * 
 * @return The `movePiece` function returns a boolean value indicating whether the move was successful
 * or not. The `isPlayerKingCaptured` function returns a boolean value indicating whether the player's
 * king is captured or not. The `isGameOver` function returns a boolean value indicating whether the
 * game is over or not. The `isSquareUnderThreat` function returns a boolean value indicating whether a
 * given square
 */
bool ChessBoard::movePiece(int rowFrom, int colFrom, int rowTo, int colTo) {
    // Move the ChessPiece from (rowFrom, colFrom) to (rowTo, colTo) if (rowFrom >= 0 && rowFrom < 8 && colFrom >= 0 && colFrom < 8 &&
        if (rowFrom >= 0 && rowFrom < 8 && colFrom >= 0 && colFrom < 8 &&
        rowTo >= 0 && rowTo < 8 && colTo >= 0 && colTo < 8 &&
        board[rowFrom][colFrom] && board[rowFrom][colFrom]->isValidMove(rowFrom, colFrom, rowTo, colTo)) {
        
        ChessPiece* sourcePiece = board[rowFrom][colFrom];
        ChessPiece* destinationPiece = board[rowTo][colTo];

        // Check if the destination square is empty or contains a piece of the opposite color
        if (!destinationPiece || destinationPiece->getColor() != sourcePiece->getColor()) {
            // Perform the move if it's a valid move
            ChessPiece* temp = board[rowTo][colTo];
            board[rowTo][colTo] = board[rowFrom][colFrom];
            board[rowFrom][colFrom] = nullptr;
            delete temp;

            // Check if the moved piece is a king
            if (dynamic_cast<King*>(board[rowTo][colTo])) {
        // If the king is captured, end the game
        std::cout << "Player "
                  << (sourcePiece->getColor() == PieceColor::RED ? "RED" : "BLUE")
                  << " has lost the game. King is captured!" << std::endl;
        
        // Set the game state to over
        gameOver = true;
        
        
    }

            return true;
        } else {
            std::cout << "Invalid move. Cannot capture a piece of the same color." << std::endl;
            return false;
        }
    } else {
        return false;
    } 
}

/**
 * The function checks if the player's king is captured by iterating through the chess board and
 * searching for the king piece.
 * 
 * @param playerColor The parameter `playerColor` is of type `PieceColor` and represents the color of
 * the player whose king we want to check if it is captured.
 * 
 * @return a boolean value. It returns true if the player's king is captured, and false if the player's
 * king is still on the board.
 */
bool ChessBoard::isPlayerKingCaptured(PieceColor playerColor) const {
    // Iterate through the board to check if the player's king is captured
    /* The above code is checking if the player's king is still on the chess board. It iterates through
    each position on the board and checks if there is a chess piece at that position. If there is a
    piece and it is a king ('K') of the same color as the player, it returns false, indicating that
    the king is still on the board. */
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            ChessPiece* piece = board[i][j];
            if (piece && piece->getSymbol() == 'K' && piece->getColor() == playerColor) {
                // The player's king is still on the board
                return false;
            }
        }
    }
    // The player's king is not found, indicating it is captured
    return true;
}

/**
 * The function checks if the game is over by determining if either player's king has been captured.
 * 
 * @return the value of the variable "gameOver", which is a boolean value indicating whether the game
 * is over or not.
 */
bool ChessBoard::isGameOver()  {
    
    
   if (isPlayerKingCaptured(PieceColor::RED) || isPlayerKingCaptured(PieceColor::BLUE)) {
        gameOver = true;
    } else {
       
       gameOver = false;
}
   return gameOver;
   
}


bool ChessBoard::isSquareUnderThreat(int row, int col, PieceColor currentPlayer) const {
    // Check if any opponent piece can attack the given square
     /* The above code is checking if there is any valid move for the current player in a chess game.
     It iterates through each position on the chess board (8x8) and checks if there is a chess piece
     at that position. If there is a piece and it belongs to the opponent of the current player, it
     calls the `isValidMove()` function of that piece to check if it can move to the specified row
     and column. If a valid move is found, the function returns true. */
     for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            ChessPiece* piece = board[i][j];
            if (piece && piece->getColor() != currentPlayer && piece->isValidMove(i, j, row, col)) {
                return true;
            }
        }
    }
    return false;
}

bool ChessBoard::canEscapeCheck(int kingRow, int kingCol, PieceColor currentPlayer) const {
    // Check if the king can move to any square that is not under threat
   /* The above code is checking if there is at least one square on a chessboard that is not under
   threat from the current player's pieces. It does this by iterating through all the squares on the
   board and calling the function `isSquareUnderThreat` to check if each square is under threat. If
   it finds a square that is not under threat, it returns `true` indicating that the king can escape
   check. */
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (!isSquareUnderThreat(i, j, currentPlayer)) {
                // If there is at least one square not under threat, the king can escape check
                return true;
            }
        }
    }
    return false;
}

/**
 * The code checks if a move puts the king in check and if the current player is in checkmate.
 * 
 * @param fromRow The row index of the piece's current position on the chessboard.
 * @param fromCol The column index of the starting position of the piece being moved.
 * @param toRow The parameter "toRow" represents the row number of the destination square where the
 * piece is being moved to.
 * @param toCol The parameter "toCol" represents the column index of the destination square where the
 * piece is being moved to.
 * @param currentPlayer The parameter "currentPlayer" represents the color of the current player. It is
 * of type "PieceColor", which is an enumeration that can have two possible values: "White" or "Black".
 * This parameter is used to determine which player's king to check for checkmate.
 * 
 * @return The first function, `isMovePuttingKingInCheck`, returns a boolean value indicating whether a
 * move puts the king in check.
 */
bool ChessBoard::isMovePuttingKingInCheck(int fromRow, int fromCol, int toRow, int toCol, PieceColor currentPlayer) const {
    // Make a copy of the board and simulate the move
    ChessBoard tempBoard(*this);
    tempBoard.movePiece(fromRow, fromCol, toRow, toCol);

    // Get the king's position
    int kingRow = -1;
    int kingCol = -1;

    // Find the king's position
    /* The above code is searching for the position of the current player's king on a chessboard
    represented by the `tempBoard` object. It iterates through each cell on the board using nested
    for loops, and checks if there is a non-null chess piece at that position. If there is a piece
    and it is a king of the current player's color, the `kingRow` and `kingCol` variables are
    updated with the row and column indices of the king's position. The code then breaks out of the
    inner loop and continues with the rest of the program. */
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            ChessPiece* piece = tempBoard.getPiece(i, j);
            if (piece && piece->getColor() == currentPlayer && dynamic_cast<King*>(piece)) {
                kingRow = i;
                kingCol = j;
                break;
            }
        }
    }

    /* The above code is checking if the variables `kingRow` and `kingCol` are equal to -1. If either
    of them is -1, it means that the king was not found, and the code returns false. */
    if (kingRow == -1 || kingCol == -1) {
        // King not found
        return false;
    }

    // Check if the king is in check on the temporary board
    return tempBoard.isSquareUnderThreat(kingRow, kingCol, currentPlayer);
}


/**
 * The function `isCheckmate` checks if the current player's king is in checkmate by iterating through
 * the board, finding the king's position, checking if the king is in check, and then checking if there
 * are any legal moves to get the king out of check.
 * 
 * @param currentPlayer The parameter "currentPlayer" represents the color of the player whose turn it
 * is to move. It can be either "PieceColor::WHITE" or "PieceColor::BLACK", indicating whether it is
 * the white player or the black player's turn.
 * 
 * @return a boolean value. It returns true if the current player's king is in checkmate, and false
 * otherwise.
 */
bool ChessBoard::isCheckmate(PieceColor currentPlayer) {
    // Iterate through the board to find the current player's king
  int kingRow = -1;
    int kingCol = -1;

    // Find the king's position
   /* The above code is searching for the position of the current player's king on a chessboard. It
   iterates through each cell on the chessboard and checks if there is a piece at that position. If
   there is a piece and it is the current player's king, the code stores the row and column of the
   king's position in the variables kingRow and kingCol. */
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            ChessPiece* piece = getPiece(i, j);
            if (piece && piece->getColor() == currentPlayer && dynamic_cast<King*>(piece)) {
                kingRow = i;
                kingCol = j;
                break;
            }
        }
    }

    /* The above code is checking if the variables `kingRow` and `kingCol` are equal to -1. If either
    of them is -1, it means that the king was not found, and the code returns false. */
    if (kingRow == -1 || kingCol == -1) {
        // King not found
        return false;
    }

    // Check if the king is in check
    /* The above code is checking if the king is under threat (in check) by calling the function
    `isSquareUnderThreat` with the parameters `kingRow`, `kingCol`, and `currentPlayer`. If the king
    is not under threat, the code returns `false`, indicating that the king is not in checkmate. */
    if (!isSquareUnderThreat(kingRow, kingCol, currentPlayer)) {
        return false; // King is not in check, so not in checkmate
    }

    // Check if there are any legal moves to get the king out of check
    /* The above code is a nested loop that iterates through each square on a chessboard (8x8). It
    checks if there is a chess piece on the current square and if the piece belongs to the current
    player. If both conditions are met, it then checks all possible moves for that piece. */
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            ChessPiece* piece = getPiece(i, j);
            if (piece && piece->getColor() == currentPlayer) {
                for (int toRow = 0; toRow < 8; ++toRow) {
                    for (int toCol = 0; toCol < 8; ++toCol) {
                        if (piece->isValidMove(i, j, toRow, toCol) &&
                            movePiece(i, j, toRow, toCol) &&
                            !isSquareUnderThreat(kingRow, kingCol, currentPlayer)) {
                            // The move is legal and gets the king out of check
                            // Undo the move
                            movePiece(toRow, toCol, i, j);
                            movePiece(i, j, toRow, toCol);
                            return false;
                        }
                    }
                }
            }
        }
    }

    // No legal moves to get the king out of check, so it's checkmate
    return true;
}

/**
 * The above code implements the isValidMove and getSymbol functions for different chess pieces.
 * 
 * @param rowFrom The row index of the current position of the piece.
 * @param colFrom The parameter "colFrom" represents the column index of the starting position of the
 * piece.
 * @param rowTo The parameter "rowTo" represents the row index of the destination position where the
 * piece is being moved to.
 * @param colTo The parameter "colTo" represents the column index of the destination position where the
 * piece is being moved to.
 * 
 * @return In each of the member functions, a boolean value is being returned. This value represents
 * whether the move from the starting position (rowFrom, colFrom) to the destination position (rowTo,
 * colTo) is a valid move for the specific chess piece.
 */
// Implementation of member functions for Pawn
bool Pawn::isValidMove(int rowFrom, int colFrom, int rowTo, int colTo) const {
     
//Pawn movement logic
    /* The above code is calculating the difference between two rows and the absolute difference
    between two columns. */
    int rowDiff = rowTo - rowFrom;
    int colDiff = std::abs(colTo - colFrom);

    /* The above code is implementing the movement rules for a pawn in a game. It checks the color of
    the pawn and then determines if the move is valid based on the difference in rows and columns.
    If the pawn is red, it can move one step forward, two steps forward from the starting position,
    or capture diagonally. If the pawn is blue, it can move one step downward, two steps downward
    from the starting position, or capture diagonally. */
    if (getColor() == PieceColor::RED) {
        // Red pawn moves upward
        if (rowDiff == 1 && colDiff == 0) {
            return true; // Valid one-step forward move
        } else if (rowFrom == 1 && rowDiff == 2 && colDiff == 0) {
            return true; // Valid two-step forward move from the starting position
        } else if (rowDiff == 1 && colDiff == 1) {
            return true; // Valid diagonal capture
        }
    } else {
        // Blue pawn moves downward
        if (rowDiff == -1 && colDiff == 0) {
            return true; // Valid one-step forward move
        } else if (rowFrom == 6 && rowDiff == -2 && colDiff == 0) {
            return true; // Valid two-step forward move from the starting position
        } else if (rowDiff == -1 && colDiff == 1) {
            return true; // Valid diagonal capture
        }
    }

    return false;
}

/**
 * The function returns the symbol 'P' for a Pawn object.
 * 
 * @return The character 'P' is being returned.
 */
char Pawn::getSymbol() const {
    return 'P';
}

/**
 * The isValidMove function checks if a move for a Rook piece is valid by ensuring that the move is
 * either horizontal or vertical and that the path between the starting and ending positions is clear.
 * 
 * @param rowFrom The starting row of the Rook's position on the chessboard.
 * @param colFrom The column index of the starting position of the Rook.
 * @param rowTo The row index of the destination position where the Rook is being moved to.
 * @param colTo The parameter "colTo" represents the column index of the destination position where the
 * Rook is being moved to.
 * 
 * @return a boolean value.
 */
// Implementation of member functions for Rook
bool Rook::isValidMove(int rowFrom, int colFrom, int rowTo, int colTo) const {
    // Rook movement logic
      int rowDiff = rowTo - rowFrom;
      int colDiff = colTo - colFrom;

    // Rook can move horizontally or vertically
    return (rowDiff == 0 || colDiff == 0) && isPathClear(rowFrom, colFrom, rowTo, colTo);

}

/**
 * The function returns the symbol 'R' for a Rook piece.
 * 
 * @return The character 'R' is being returned.
 */
char Rook::getSymbol() const {
    return 'R';
}

/**
 * The isValidMove function checks if the move from (rowFrom, colFrom) to (rowTo, colTo) is a valid
 * move for a Knight in chess.
 * 
 * @param rowFrom The row index of the starting position of the Knight's move.
 * @param colFrom The column index of the starting position of the Knight.
 * @param rowTo The row index of the destination position where the Knight is being moved to.
 * @param colTo The parameter "colTo" represents the column index of the destination position where the
 * Knight is being moved to.
 * 
 * @return a boolean value.
 */
// Implementation of member functions for Knight
bool Knight::isValidMove(int rowFrom, int colFrom, int rowTo, int colTo) const {
   // Knight movement logic
    int rowDiff = std::abs(rowTo - rowFrom);
    int colDiff = std::abs(colTo - colFrom);

     return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
    
    
}

/**
 * The function returns the symbol 'N' for a Knight.
 * 
 * @return The character 'N' is being returned.
 */
char Knight::getSymbol() const {
    return 'N';
}

/**
 * The isValidMove function checks if the move for a Bishop or Queen is valid based on the movement
 * logic and if the path is clear.
 * 
 * @param rowFrom The row index of the starting position of the piece.
 * @param colFrom The column index of the starting position of the piece.
 * @param rowTo The row index of the destination position where the piece is being moved to.
 * @param colTo The parameter "colTo" represents the column index of the destination position on the
 * chessboard.
 * 
 * @return In the `isValidMove` function for both the Bishop and Queen classes, a boolean value is
 * being returned. This boolean value represents whether the move from the starting position (rowFrom,
 * colFrom) to the ending position (rowTo, colTo) is a valid move for the respective chess piece.
 */
// Implementation of member functions for Bishop
bool Bishop::isValidMove(int rowFrom, int colFrom, int rowTo, int colTo) const {
    // Bishop movement logic
    int rowDiff = rowTo - rowFrom;
    int colDiff = colTo - colFrom;

    return std::abs(rowDiff) == std::abs(colDiff) && isPathClear(rowFrom, colFrom, rowTo, colTo);
    
    
}

/**
 * The function returns the symbol 'B' for a Bishop piece.
 * 
 * @return The character 'B' is being returned.
 */
char Bishop::getSymbol() const {
    return 'B';
}

// Implementation of member functions for Queen
bool Queen::isValidMove(int rowFrom, int colFrom, int rowTo, int colTo) const {
     //Queen movement logic (combination of rook and bishop)
    int rowDiff = rowTo - rowFrom;
    int colDiff = colTo - colFrom;

    return (rowDiff == 0 || colDiff == 0 || std::abs(rowDiff) == std::abs(colDiff)) &&
           isPathClear(rowFrom, colFrom, rowTo, colTo);
    
   
}

/**
 * The function returns the symbol 'Q' for a Queen chess piece.
 * 
 * @return The character 'Q' is being returned.
 */
char Queen::getSymbol() const {
    return 'Q';
}

// Implementation of member functions for King
/**
 * The function checks if a move for a King piece in a chess game is valid by comparing the absolute
 * differences in row and column positions and returning true if both differences are less than or
 * equal to 1.
 * 
 * @param rowFrom The row index of the current position of the King piece on the chessboard.
 * @param colFrom The column index of the current position of the King.
 * @param rowTo The row index of the destination position where the King wants to move.
 * @param colTo The parameter "colTo" represents the column index of the destination position where the
 * King is being moved to.
 * 
 * @return a boolean value.
 */
bool King::isValidMove(int rowFrom, int colFrom, int rowTo, int colTo) const {
    // King movement logic
    int rowDiff = std::abs(rowTo - rowFrom);
     int colDiff = std::abs(colTo - colFrom);

   return (rowDiff <= 1 && colDiff <= 1);
    
    
}

/**
 * The function returns the symbol 'K' for the King piece.
 * 
 * @return The character 'K' is being returned.
 */
char King::getSymbol() const {
    return 'K';
}



/**
 * This is a C++ program that allows two players to play a game of chess by taking turns entering the
 * positions of the pieces they want to move.
 * 
 * @return The main function is returning an integer value of 0.
 */

int main() {
    /* The above code is declaring a variable named "chessBoard" of type ChessBoard. */
    /* The above code is declaring a variable named "chessBoard" of type ChessBoard. */
    ChessBoard chessBoard;

    // Variables to track current player and input
    PieceColor currentPlayer = PieceColor::RED;
    std::string move;

    // Game loop
   /* The above code is implementing a game loop for a chess game. It displays the chess board, prompts
   the current player for their move, validates the input, and updates the board accordingly. It
   also checks if the game is over and displays the result. The loop continues until the game is
   over or the player chooses to exit. */
   while (true) {
        chessBoard.display();
        std::cout << "Current player: " << (currentPlayer == PieceColor::RED ? "RED" : "BLUE") << std::endl;
        
        // Check if the game is over
   /* The above code is checking if the game is over. If the game is over, it prints a message
   indicating the result of the game. If the player's king is captured, it prints the winning
   player's color. If the game is a draw, it prints "It's a draw." Finally, it prints a thank you
   message and breaks out of the loop. */
    if (chessBoard.isGameOver()) {
        std::cout << "Game over. ";
        if (chessBoard.isPlayerKingCaptured(currentPlayer)) {
            std::cout << "Player " << (currentPlayer == PieceColor::RED ? "BLUE" : "RED") << " wins!" << std::endl;
        } else {
            std::cout << "It's a draw." << std::endl;
        }
        std::cout << "Thank you for playing!" << std::endl;
        break;
    }

        // Ask for the position of the piece
        std::cout << "Enter the position of the piece (e.g., 'a2', 'EXIT' to end the game): ";
        std::getline(std::cin, move);

        // Convert input to uppercase for case-insensitivity
        /* The above code is converting each character in the string variable "move" to uppercase using
        the std::toupper() function. */
        for (char& c : move) {
            c = std::toupper(c);
        }

        // Check for exit condition
       /* The above code is checking if the value of the variable "move" is equal to the string "EXIT".
       If it is, the code will break out of the current loop or block of code. */
        if (move == "EXIT") {
            break;
        }

        // Validate input format
        /* The above code is checking if the size of the variable "move" is not equal to 2. If it is
        not equal to 2, it will print "Invalid input format. Try again." and continue to the next
        iteration of the loop. */
        if (move.size() != 2) {
            std::cout << "Invalid input format. Try again." << std::endl;
            continue;
        }

       /* The above code is converting a chess move notation into row and column indices. It is taking
       the second character of the move string and subtracting the ASCII value of '1' to get the row
       index. It is taking the first character of the move string and subtracting the ASCII value of
       'A' to get the column index. */
        int fromRow = move[1] - '1';
        int fromCol = move[0] - 'A';

        // Validate if the selected square contains a piece of the current player
        /* The above code is checking if a chess piece is selected on a chess board. It first retrieves
        the chess piece at the specified row and column coordinates using the `getPiece` function of
        the `chessBoard` object. If no piece is found at the specified coordinates or if the color
        of the selected piece does not match the current player's color, it prints an error message
        and continues to the next iteration of the loop. */
        ChessPiece* selectedPiece = chessBoard.getPiece(fromRow, fromCol);
        if (!selectedPiece || selectedPiece->getColor() != currentPlayer) {
            std::cout << "Invalid selection. Try again." << std::endl;
            continue;
        }

        // Ask for the destination to move the piece
        std::cout << "Enter the destination to move the piece (e.g., 'a4'): ";
        std::getline(std::cin, move);

        // Convert input to uppercase for case-insensitivity
        /* The above code is converting each character in the string variable "move" to uppercase using
        the std::toupper() function. */
        for (char& c : move) {
            c = std::toupper(c);
        }

        // Validate input format
        /* The above code is checking if the size of the variable "move" is not equal to 2. If it is
        not equal to 2, it will print "Invalid input format. Try again." and continue to the next
        iteration of the loop. */
        if (move.size() != 2) {
            std::cout << "Invalid input format. Try again." << std::endl;
            continue;
        }

        int toRow = move[1] - '1';
        int toCol = move[0] - 'A';

        // Check if the move is valid
        /* The above code is checking if a move on a chess board is valid. If the move is valid, it
        switches to the next player. If the move is invalid, it prints "Invalid move. Try again." */
        if (chessBoard.movePiece(fromRow, fromCol, toRow, toCol)) {
            // Switch to the next player
            currentPlayer = (currentPlayer == PieceColor::RED) ? PieceColor::BLUE : PieceColor::RED;
        } else {
            std::cout << "Invalid move. Try again." << std::endl;
        }
        
    /* The above code is checking if the game is over. If the condition `chessBoard.isGameOver()`
    evaluates to true, it will print "Game over. Thank you for playing!" and then break out of the
    current loop. */
    // Check if the game is over
    if (chessBoard.isGameOver()) {
        std::cout << "Game over. Thank you for playing!" << std::endl;
        break;
    }
        
    }

    /* The above code is using C++ to output the message "Game ended. Thank you for playing!" to the
    console. */
    std::cout << "Game ended. Thank you for playing!" << std::endl;
    
    return 0;
}








