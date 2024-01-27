#pragma once
#include "IPlayer.h"
#include "Board.h"
#include <vector>
#include <unordered_map>
class AiPlayer :
	public IPlayer
{
public:
	AiPlayer(const Board& board);
	~AiPlayer() override = default;

	// Inherited via IPlayer
	virtual Board::Position GetNextAction() override;
	virtual const std::string& GetName() const override;

	void FeedReward(float reward);

private:
	static std::vector<Board::Position> GetPossibleActions(const Board& board);
	static uint64_t GetHash(const Board& state, const Board::Position& action);

private:
	const Board& m_board;
	std::unordered_map < uint64_t, float> m_estimations;
	std::vector<uint64_t> m_previousStateActions;
};

