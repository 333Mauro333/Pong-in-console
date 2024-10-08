﻿#include "gameplay.h"

#include "game_object/block/destructible_block/destructible_block.h"
#include "game_object/block/indestructible_block/indestructible_block.h"
#include "laser_pooling/laser_pooling.h"
#include "managers/collision_manager/collision_manager.h"
#include "managers/controls_manager/controls_manager.h"
#include "managers/file_manager/file_manager.h"
#include "managers/level_manager/level_manager.h"
#include "managers/level_time_manager/level_time_manager.h"
#include "managers/lives_manager/lives_manager.h"
#include "managers/music_manager/music_manager.h"
#include "managers/scene_manager/scene_manager.h"
#include "managers/score_manager/score_manager.h"

using mgtv_library::console::ConsoleExt;


namespace pong_in_console
{
	Gameplay::Gameplay() : Scene(COLOR::C_BLACK)
	{
		lives = LivesManager::getLives();
		levelScore = 0;
		totalScore = ScoreManager::getTotalScore();
		level = LevelManager::getLevel();
		time = 0;
		isTimeToChangeScene = false;

		initFrame();
		initPlayer();
		initBall();
		initBlocks();
		initUI();
		setLaserLimits();

		LevelTimeManager::startCounting();
	}
	Gameplay::~Gameplay()
	{
		delete frame;
		delete ui;
		delete player;
		delete ball;

		deleteBlocks();
	}

	void Gameplay::inputUpdate(int key)
	{
		player->inputUpdate(key);

		checkMenuInput(key);
	}
	void Gameplay::update()
	{
		LevelTimeManager::updateTime();

		ball->update();
		player->update();
		updateLasers();

		if (theOneBallTouchesTheFloor())
		{
			discountALife();

			if (thereAreLives())
			{
				ui->updateStatistic(GAMEPLAY_STATISTIC::LIVES);
				putTheBallOverThePaddle();
				ball->setIsInStoppedMode(true);
			}
			else
			{
				isTimeToChangeScene = true;
			}
		}

		if (theSecondsChanged())
		{
			updateTime();
			ui->updateStatistic(GAMEPLAY_STATISTIC::TIME);
		}

		checkBallCollisions();
		checkLaserCollisions();

		if (isTimeToChangeScene)
		{
			LivesManager::setLives(lives);
			LaserPooling::deactivateAllLasers();

			if (allTheBlocksWereBroken())
			{
				SceneManager::loadScene(SCENE_TO_LOAD::LEVEL_PASSED);
			}
			else if (!thereAreLives())
			{
				LevelManager::setLevel(1);
				SceneManager::loadScene(SCENE_TO_LOAD::MAIN_MENU);
			}
		}
	}
	void Gameplay::erase()
	{
		ball->erase();
		player->erase();
		eraseLasers();
	}
	void Gameplay::draw()
	{
		frame->draw();
		ui->draw();
		ball->draw();
		player->draw();

		drawLasers();
		drawBlocks();
	}


	void Gameplay::initPlayer()
	{
		player = new Paddle(60, 24);
		player->setMovementLimits(frame);
	}
	void Gameplay::initBall()
	{
		int playerCenterX = player->getPosition().x + player->getSize().w / 2;

		ball = new Ball(playerCenterX, player->getPosition().y - 1, BALL_DIRECTION::UP_RIGHT);
		ball->setPaddleReference(player);
		ball->setIsInStoppedMode(true);
		ball->setMovementLimits(frame);
	}
	void Gameplay::initFrame()
	{
		const int frameWidth = 42;
		const int frameHeight = 24;

		frame = new Frame(ConsoleExt::getScreenWidth() / 2 - frameWidth / 2,
						  ConsoleExt::getScreenHeight() / 2 - frameHeight / 2 + 2,
						  frameWidth, frameHeight, COLOR::C_BWHITE);
	}
	void Gameplay::initBlocks()
	{
		string levelInfo = FileManager::loadLevel(level);
		int firstPositionX = frame->getLeft() + 1;
		int firstPositionY = frame->getUp() + 1;
		int x = firstPositionX;
		int y = firstPositionY;


		blocks = vector<Block*>();

		for (int i = 0; i < levelInfo.size(); i++)
		{
			Block* blockToCreate = NULL;

			if (levelInfo[i] == '\n')
			{
				x = firstPositionX;
				y++;
				continue;
			}
			else if (levelInfo[i] == '1' || levelInfo[i] == '2' || levelInfo[i] == '3' || levelInfo[i] == '4')
			{
				int foundNumber = (int)levelInfo[i] - 48;

				blockToCreate = new DestructibleBlock(x, y, (BLOCK_TYPE)foundNumber);
				blocks.push_back(blockToCreate);
			}
			else if (levelInfo[i] == '0')
			{
				blockToCreate = new IndestructibleBlock(x, y);
				blocks.push_back(blockToCreate);
			}

			x++;
		}
	}
	void Gameplay::initUI()
	{
		ui = new GameplayUI(frame, 5);
		ui->pointToLives(lives);
		ui->pointToLevel(level);
		ui->pointToTime(time);
		ui->pointToScore(totalScore);
	}
	void Gameplay::setLaserLimits()
	{
		LaserPooling::setLasersLimits(frame);
	}

	void Gameplay::updateLasers()
	{
		LaserPooling::updateLasers();
	}
	void Gameplay::eraseLasers()
	{
		LaserPooling::eraseLasers();
	}
	void Gameplay::drawLasers()
	{
		LaserPooling::drawLasers();
	}
	void Gameplay::drawBlocks()
	{
		for (int i = 0; i < blocks.size(); i++)
		{
			blocks[i]->draw();
		}
	}
	void Gameplay::deleteBlocks()
	{
		for (int i = 0; i < blocks.size(); i++)
		{
			delete blocks[i];
		}
	}

	void Gameplay::checkMenuInput(int key)
	{
		if (ControlsManager::isPressed(key, MENU_CONTROLS::BACK))
		{
			SceneManager::loadScene(SCENE_TO_LOAD::MAIN_MENU);
		}
		else if (ControlsManager::isPressed(key, MENU_CONTROLS::ENTER))
		{
			disappearABlock();

			if (allTheBlocksWereBroken())
			{
				isTimeToChangeScene = true;
			}
		}
	}
	void Gameplay::checkBallCollisions()
	{
		CollisionManager::applyCollisionBetweenBallAndPaddle(ball, player);
		CollisionManager::applyCollisionBetweenBallAndBullet(ball, player->getBullet());

		if (CollisionManager::applyCollisionBetweenBallAndBlocks(ball, blocks))
		{
			totalScore = ScoreManager::getTotalScore();
			ui->updateStatistic(GAMEPLAY_STATISTIC::SCORE);

			if (allTheBlocksWereBroken())
			{
				isTimeToChangeScene = true;
			}
		}
	}
	void Gameplay::checkLaserCollisions()
	{
		if (CollisionManager::applyCollisionBetweenLasersAndBlocks(LaserPooling::getActiveLasers(), blocks))
		{
			totalScore = ScoreManager::getTotalScore();
			ui->updateStatistic(GAMEPLAY_STATISTIC::SCORE);

			if (getAmountOfActiveBlocks() == 0)
			{
				isTimeToChangeScene = true;
			}
		}
	}

	int Gameplay::getAmountOfActiveBlocks()
	{
		int amountOfActiveBlocks = 0;

		for (int i = 0; i < blocks.size(); i++)
		{
			if (blocks[i]->getBlockType() != BLOCK_TYPE::B_INDESTRUCTIBLE && blocks[i]->getIsActive())
			{
				amountOfActiveBlocks++;
			}
		}

		return amountOfActiveBlocks;
	}
	void Gameplay::disappearABlock()
	{
		for (int i = 0; i < blocks.size(); i++)
		{
			if (blocks[i]->getBlockType() != BLOCK_TYPE::B_INDESTRUCTIBLE && blocks[i]->getIsActive())
			{
				blocks[i]->reactToTheBall();
				ConsoleExt::goToCoordinates(1, 1);
				ConsoleExt::writeWithColor("    ", COLOR::C_LRED);
				ConsoleExt::goToCoordinates(1, 1);
				ConsoleExt::writeWithColor(std::to_string(getAmountOfActiveBlocks()), COLOR::C_LRED);
				break;
			}
		}
	}

	bool Gameplay::theOneBallTouchesTheFloor()
	{
		return ball->getPosition().y == frame->getDown() - 1;
	}
	void Gameplay::discountALife()
	{
		LivesManager::discountALife();
		lives = LivesManager::getLives();
	}
	bool Gameplay::thereAreLives()
	{
		return LivesManager::thereAreLives();
	}
	void Gameplay::putTheBallOverThePaddle()
	{
		int playerCenterX = player->getPosition().x + player->getSize().w / 2;

		ball->setPosition(playerCenterX, player->getPosition().y - 1);
		ball->setDirection(BALL_DIRECTION::UP_RIGHT);
	}

	bool Gameplay::theSecondsChanged()
	{
		return time != LevelTimeManager::getActualTime();
	}
	void Gameplay::updateTime()
	{
		time = LevelTimeManager::getActualTime();
	}

	bool Gameplay::allTheBlocksWereBroken()
	{
		return getAmountOfActiveBlocks() == 0;
	}
}
