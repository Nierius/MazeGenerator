#include <iostream>
#include <chrono>
#include <thread>
#include "mazegenerator.h"

MazeGenerator::MazeGenerator(): _canvas(nullptr), _blocks( {}), _current(nullptr), _w(0), _h(0), _sleeptime(0)
{
	std::cout << "Maze Generator init." << std::endl;
	srand(time(NULL));
}

MazeGenerator& MazeGenerator::getInstance()
{
	static MazeGenerator instance;
	return instance;
}

void MazeGenerator::setCanvas(Canvas* canvas)
{
	_canvas = canvas;
	std::cout << "Canvas set: " << _canvas << std::endl;
}

void MazeGenerator::initBlocks(unsigned int amount, unsigned int sleeptime)
{
	if (_canvas == nullptr) {
		throw no_canvas_set();
	}
	_blocks.clear();
	_sleeptime = sleeptime;

	unsigned int perRow = floor(sqrt(amount));
	calculateAndSetWH(perRow);

	unsigned int x = 0;
	unsigned int y = 0;

	for ( unsigned int i = 0; i < amount; i++ ) {
		x = i % perRow;
		y = floor(i / perRow);
		std::shared_ptr<Block> block = std::make_shared<Block>(_canvas, x, y);
		block->setBoundingRect(calculateBoundingRect(x, y));
		_blocks.push_back(block);
	}
}

bool MazeGenerator::startGeneration()
{
	std::cout << "Starting maze generation" << std::endl;
	return RecursiveBackTracer(_blocks[0]);
}

bool MazeGenerator::RecursiveBackTracer(std::shared_ptr<Block>& block)
{
	_current = block;
	_current->visit();

	std::vector<std::shared_ptr<Block> > unvisited = getUnvisitedNeighbours(block);

	while( unvisited.size() > 0 ) {
		int randNum = rand()%(unvisited.size());
		auto& next = unvisited[randNum];
		removeWalls(block, next);
		std::this_thread::sleep_for(std::chrono::milliseconds(_sleeptime));
		_current = next;
		block->UpdateRect();
		RecursiveBackTracer(next);
		_current = block;
		unvisited = getUnvisitedNeighbours(block);
	}
	return true;
}

void MazeGenerator::removeWalls(std::shared_ptr<Block> curr, std::shared_ptr<Block> next)
{
	int x = curr->getX() - next->getX();
	int y = curr->getY() - next->getY();

	if (x == -1) {
		curr->removeWall(Wall::Right);
		next->removeWall(Wall::Left);
	} else if(x == 1) {
		curr->removeWall(Wall::Left);
		next->removeWall(Wall::Right);
	} else if(y == -1) {
		curr->removeWall(Wall::Bottom);
		next->removeWall(Wall::Top);
	} else if(y == 1) {
		curr->removeWall(Wall::Top);
		next->removeWall(Wall::Bottom);
	}
}
unsigned int MazeGenerator::getBlockIndex(std::shared_ptr<Block>& block) const
{
	unsigned int i = 0;

	while (true) {
		if (block == _blocks[i]) {
			break;
		}
		if (i >= _blocks.size()) {
			std::cout << "ERROR: Can't find block!" << std::endl;
			throw std::out_of_range("Block was not found before exceeding bounds");
		}
		i++;
	}
	return i;
}

std::vector<std::shared_ptr<Block> > MazeGenerator::getBlocksInside(wxRect& rect) const
{
	std::vector<std::shared_ptr<Block> > returnVector = {};

	for (auto& block : _blocks) {
		if (block->getX() * _w + 1 >= static_cast<unsigned int>(rect.GetLeftTop().x)
		    && block->getY() * _h  + 1>= static_cast<unsigned int>(rect.GetLeftTop().y)
		    && block->getX() * _w + _w - 1 <= static_cast<unsigned int>(rect.GetRightBottom().x)
		    && block->getY() * _h + _w - 1 <= static_cast<unsigned int>(rect.GetRightBottom().y)) {
			returnVector.push_back(block);
		}
	}
	return returnVector;
}



std::vector<std::shared_ptr<Block> > MazeGenerator::getUnvisitedNeighbours(std::shared_ptr<Block>& block) const
{
	int index = getBlockIndex(block);
	int perRow = floor(sqrt(_blocks.size()));
	std::vector<std::shared_ptr<Block> > returnVector = {};

	//TOP
	if (index - perRow >= 0) {
		if (!_blocks[index - perRow]->visited()) {
			returnVector.push_back(_blocks[index - perRow]);
		}
	}

	//BOT
	if (index + perRow < static_cast<int>(_blocks.size())) {
		if (!_blocks[index + perRow]->visited()) {
			returnVector.push_back(_blocks[index + perRow]);
		}
	}

	//RIGHT
	if (index - 1  >= 0
	    && floor(index / perRow) == floor((index - 1) / perRow)) {

		if (!_blocks[index -1]->visited()) {
			returnVector.push_back(_blocks[index - 1]);
		}
	}

	//LEFT
	if (index + 1 < static_cast<int>(_blocks.size())
	    && floor(index / perRow) == floor((index + 1) / perRow)) {

		if (!_blocks[index + 1]->visited()) {
			returnVector.push_back(_blocks[index + 1]);
		}
	}
	return returnVector;
}

bool MazeGenerator::isCurrent(Block* block) const
{
	if (_current.get() == block) {
		return true;
	}
	return false;
}

wxRect MazeGenerator::calculateBoundingRect(unsigned int x, unsigned int y) const
{
	return wxRect(x * _w, y * _h, _w, _h);
}

void MazeGenerator::calculateAndSetWH(unsigned int perRow)
{
	_w = floor(_canvas->GetSize().GetWidth() / perRow);
	_h = floor(_canvas->GetSize().GetHeight() / perRow);
}
