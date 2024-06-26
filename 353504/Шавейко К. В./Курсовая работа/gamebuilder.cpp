#include "gamebuilder.h"
#include "basegame.h"
#include "cueballcontrolfeature.h"

GameBuilder::GameBuilder(std::shared_ptr<AbstractFactory> factory)
	: m_balls(std::make_shared<std::vector<std::shared_ptr<Ball>>>()),
	  m_factory(factory) {}

void GameBuilder::addBall(const QJsonObject &ballJSon)
{
	m_balls->push_back(m_factory->makeBall(ballJSon));
}

void GameBuilder::buildTable(const QJsonObject &tableJSon)
{
    m_table = m_factory->makeTable(tableJSon);
}

std::unique_ptr<PoolGame> GameBuilder::getGame()
{
	std::unique_ptr<PoolGame> result = std::make_unique<CueBallControlFeature>(
		std::make_unique<BaseGame>(
			m_table, m_balls
		)
	);
	m_balls = std::make_shared<std::vector<std::shared_ptr<Ball>>>();
    return result;
}
