#include "TicTacToeGame.h"
#include "Board.h"
#include "HumanPlayer.h"
#include "ConsoleRenderer.h"
#include "AiPlayer.h"

#include <memory>

void TicTacToeGame::Run()
{
	Board board;
	std::unique_ptr<IPlayer> firstPlayer = std::make_unique<AiPlayer>(board);
	std::unique_ptr<IPlayer> secondPlayer = std::make_unique<HumanPlayer>("Player 2");

	IPlayer* currentPlayer = firstPlayer.get();
	IPlayer* nextPlayer = secondPlayer.get();
	Board::Piece currentPiece = Board::Piece::Cross;
	Board::Piece nextPiece = Board::Piece::Nought;

	ConsoleRenderer renderer;

	bool isGameActive = true;
	while (isGameActive)
	{
		renderer.Draw(board);
		bool isInputOk = false;
		while (!isInputOk)
		{
			const Board::Position& position = currentPlayer->GetNextAction();
			if (!board[position])
			{
				board[position] = currentPiece;
				isInputOk = true;
			}
		}

		auto state = board.Check();
		switch (state)
		{
		case Board::State::Win:
			renderer.ShowEndScreen(currentPlayer);
			//daca jucatorul e ai (cu dynamic_cast) sa i se ofere reward-ul
			isGameActive = false;
			break;
		case Board::State::Draw:
			renderer.ShowEndScreen();
			isGameActive = false;
			break;
		case Board::State::None:
			std::swap(currentPlayer, nextPlayer);
			std::swap(currentPiece, nextPiece);
		}
	}
}
