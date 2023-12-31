#include "game.h"
using namespace Chess;
#pragma region Static member initialization
int Chess::Game::turnNum = 0;
bool Chess::Game::whitesTurn = true;
bool Chess::Game::showMode = false;
bool Chess::Game::ignoreRules = false;
std::string Chess::Game::board[BOARD_SIZE];
std::string Chess::Game::prevBoard[BOARD_SIZE];
#pragma endregion Static member initialization

// Initialize the game
void Chess::Game::init()
{
	turnNum = 0;
	whitesTurn = true;
	showMode = false;
	ignoreRules = false;

	std::string pieces = Engine::DEFAULT_BOARD;
	Engine::initBoard(pieces);
	Engine::printBoard();
}
/// @brief Make a move on the game board
/// @param from The from pos
/// @param to The to pos
/// @return Wheter there was a checkmate played
bool Chess::Game::makeMove(int from, int to)
{
	// TODO: Add impossible to not prevent chess (idk how to do that), pawn promotion

	// Check if the move is legal using the isMoveLegal function
	if (Engine::isMoveLegal(from, to) || ignoreRules)
	{
		savePrevBoardState();

		// Check and handle capturing of a piece
		if (Engine::eatsPiece(from, to))
		{
			std::cout << "  " << Engine::getPieceName(board[from]) << " captures " << Engine::getPieceName(board[to]) << std::endl;
			board[to] = "\0 ";
		}

		// Move the piece on the board
		switchArrayItems(board, from, to);

		// Pawn Promotion
		handlePawnPromotion(from, to);

		// Print the status of the kings
		printCheckedStatus();

		// Switch turns and increment the turn number
		whitesTurn = !whitesTurn;
		turnNum++;
		// Print the updated board
		Engine::printBoard();
	}
	else
	{
		std::cout << "  Invalid move." << std::endl;
	}
	return checkForCheckmate();
}

/// @brief Convert user input position to 1D array index
/// @param pos 2D index
/// @return The 1D index
int Chess::Game::convertMove(std::string pos)
{
	char x = toupper(pos[1]);
	int y = pos[0] - '0';
	int xPos = x - 'A' + 1;

	return twoDIndexTo1D(xPos - 1, y - 1, 8);
}

// Main game loop
void Chess::Game::gameLoop()
{
	std::string from, to;

	while (true)
	{
		bool isCheckmate = false;
		std::cout << std::endl
				  << "   Enter Board Positions: ";
		std::cin >> from;

		// Exit the loop if "exit" is entered
		if (from == "exit")
		{
			break;
		}

		// Handle "show" command
		else if (from == "show")
		{
			std::cin >> to;
			handleShowInput(to);
			continue;
		}

		// Toggle ignoreRules flag
		else if (from == "ignoreRules")
		{
			handleIgnoreRulesInput();
			continue;
		}
		else if (from == "clear")
		{
			system("cls");
			Engine::printBoard();
			continue;
		}
		// Get destination position
		std::cin >> to;
		std::cout << std::endl;

		// Convert positions to array indices

		int fromPosIndex = convertMove(from);
		int toPosIndex = convertMove(to);

		// Check if positions are valid and make the move
		if (isValidMoveInput(fromPosIndex, toPosIndex))
		{
			isCheckmate = makeMove(fromPosIndex, toPosIndex);
		}
		else
		{
			std::cout << "  Invalid position entered." << std::endl;
			continue;
		}
		if (isCheckmate)
		{
			break;
		}
	}
}

// Helper methods

// Save the current board state
void Chess::Game::savePrevBoardState()
{
	std::copy(std::begin(board), std::end(board), std::begin(prevBoard));
}

// Print the status of the kings
void Chess::Game::printCheckedStatus()
{
	std::cout << std::endl;

	if (Chess::Engine::isWhiteChecked())
	{
		std::cout << "  	White king is checked!";
	}

	if (Chess::Engine::isBlackChecked())
	{
		std::cout << "  	Black king is checked!";
	}

	std::cout << std::endl
			  << std::endl;
}

// Handle "show" command input
void Chess::Game::handleShowInput(const std::string &to)
{
	int toPosIndex = convertMove(to);
	std::vector<int> highlight = Engine::getPossibleMoves(toPosIndex, turnNum);
	Engine::printBoard(whitesTurn, highlight);
}

// Toggle ignoreRules flag
void Chess::Game::handleIgnoreRulesInput()
{
	ignoreRules = !ignoreRules;
}

// Check if move positions are valid
bool Chess::Game::isValidMoveInput(int from, int to)
{
	return inRange(from, 0, BOARD_SIZE) &&
		   inRange(to, 0, BOARD_SIZE) &&
		   from != -1 &&
		   to != -1;
}
bool Chess::Game::checkForCheckmate()
{
	bool whitesCheckmate = Engine::isCheckmate(true);
	bool blacksCheckmate = Engine::isCheckmate(false);
	if (whitesCheckmate || blacksCheckmate)
	{
		std::cout << std::endl;
		if (whitesCheckmate)
		{
			std::cout << "   Checkmate! Black player has won." << std::endl;
		}
		else if (blacksCheckmate)
		{
			std::cout << "   Checkmate! White player has won." << std::endl;
		}
	}
	return whitesCheckmate || blacksCheckmate;
}

void Game::handlePawnPromotion(int from, int to)
{
	std::string pieceType = Engine::getPieceType(Game::board[from]);
	bool isWhitePieceMoved = !Engine::getPieceColor(Game::board[from]);
	if (pieceType == Engine::Pieces::PAWN)
	{
		int x = to % 8;
		int y = (to - x) / 8;
		if (y == Engine::getPawnPromotionRank(isWhitePieceMoved))
		{
			Game::board[to] = isWhitePieceMoved ? "q" : "Q";
			cout << std::endl
				 << "	Pawn promoted to Queen";
		}
	}
}