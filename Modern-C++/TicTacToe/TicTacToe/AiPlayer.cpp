#include "AiPlayer.h"

#include <limits>

AiPlayer::AiPlayer(const Board& board) : m_board(board)
{
	// empty
}

Board::Position AiPlayer::GetNextAction()
{
	std::vector<Board::Position> possibleActions = GetPossibleActions(m_board);

	Board::Position bestAction = possibleActions[0];
	float bestEstimation = -std::numeric_limits<float>::infinity();
	for (auto& action : possibleActions)
	{
		uint64_t actionHash = GetHash(m_board, action);
		float estimation = m_estimations[actionHash];
		if (estimation > bestEstimation)
		{
			bestAction = action;
			bestEstimation = estimation;
		}
	}

	m_previousStateActions.push_back(GetHash(m_board, bestAction));
	return bestAction;
}

const std::string& AiPlayer::GetName() const
{
	return "RL_Player";
}

void AiPlayer::FeedReward(float reward)
{
	for (auto it = m_previousStateActions.rbegin(); it != m_previousStateActions.rend(); ++it)
	{
		uint64_t hash = *it;
		float& estimation = m_estimations[hash];
		static const float learningRate = 0.1;
		estimation += learningRate * (reward - estimation);
		reward = estimation;
	}
	m_previousStateActions.clear();
}

std::vector<Board::Position> AiPlayer::GetPossibleActions(const Board& board)
{
	std::vector<Board::Position> emptyPositions;
	for (uint32_t i = 0; i < Board::kRows; ++i)
	{
		for (uint32_t j = 0; j < Board::kColumns; ++j)
		{
			Board::Position position = { i,j };
			if (!board[position].has_value())
			{
				emptyPositions.emplace_back(std::move(position));
			}
		}
	}
	return emptyPositions;
}

uint64_t AiPlayer::GetHash(const Board& state, const Board::Position& action)
{
	uint64_t hash = 0;

	for (uint32_t i = 0; i < Board::kRows; ++i)
	{
		for (uint32_t j = 0; j < Board::kColumns; ++j)
		{
			Board::Position position = { i,j };
			if (state[position].has_value())
			{
				switch (state[position].value())
				{
				case Board::Piece::Cross:
					hash += 1;
					break;
				case Board::Piece::Nought:
					hash += 2;
					break;
				default:
					hash += 0;
				}
			}
		}
		hash += 10;
	}

	auto [x, y] = action; //desc obj action (Board::Position) in 2 variabile
	hash += x;
	hash *= 10;
	hash += y;

	return hash;
}

