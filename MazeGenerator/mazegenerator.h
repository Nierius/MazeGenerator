#pragma once
#include <memory>
#include "canvas.h"
#include "block.h"
#include "mazeenums.h"

class Canvas;
class Block;

/**
 * @class no_canvas_set
 * @author Marius Niemenmaa (GitHub/LokSrc)
 * @date 03/01/20
 * @file mazegenerator.h
 * @brief Custom exception
 */
struct no_canvas_set : public std::exception {
	virtual const char* what() const throw()
	{
		return "Canvas must be set!";
	}
};

/**
 * @class MazeGenerator
 * @author Marius Niemenmaa (GitHub/LokSrc)
 * @date 03/01/20
 * @file mazegenerator.h
 * @brief Singleton class to generate mazes
 */
class MazeGenerator
{
public:
	/**
	 * @brief Get instance of MazeGenerator.
	 */
	static MazeGenerator& getInstance();

	/**
	 * @brief Deleted copy.
	 */
	MazeGenerator(MazeGenerator const&) = delete;

	/**
	 * @brief Deleted copy operator.
	 */
	void operator=(MazeGenerator const&) = delete;

	/**
	 * @brief Sets canvas for MazeGenerator
	 * @param canvas
	 */
	void setCanvas(Canvas* canvas);

	/**
	 * @brief Makes new maze blocks(cells).
	 * @param amount of blocks wanted
	 * @param sleeptime amount of time(ms)
	 * slept at each block in MazeGeneration
	 */
	void initBlocks(unsigned int amount, unsigned int sleeptime);

	/**
	 * @brief Start maze generation
	 * @return true: when finished
	 */
	bool startGeneration();

	/**
	 * @brief RecursiveBackTracer algorithm
	 * @param block to handle
	 * @return true: when finished
	 */
	bool RecursiveBackTracer(std::shared_ptr<Block>& block);

	/**
	 * @brief Remove walls between two blocks.
	 * @param curr: Block1
	 * @param next: Block2
	 */
	void removeWalls(std::shared_ptr<Block> curr, std::shared_ptr<Block> next);

	/**
	 * @brief Return vector index of a block
	 * @param block
	 * @return index
	 */
	unsigned int getBlockIndex(std::shared_ptr<Block>& block) const;

	/**
	 * @brief Return blocks inside given rectangle
	 * @param rect: rectangle to check
	 * @throws out_of_range exception
	 * @return blocks inside given rectangle
	 */
	std::vector<std::shared_ptr<Block> > getBlocksInside(wxRect& rect) const;

	/**
	 * @brief Return all unvisited neighbours of a block
	 * @param block
	 * @return unvisited neighbours
	 */
	std::vector<std::shared_ptr<Block> > getUnvisitedNeighbours(std::shared_ptr<Block>& block) const;

	/**
	 * @brief Check if a block is currently handled one
	 * @param block
	 * @return true: if it is
	 * false: otherwise
	 */
	bool isCurrent(Block* block) const;

private:
	/**
	 * @brief Constructor of the class.
	 * NOTE: THIS SHOULD NOT BE CALLED OUTSIDE CLASS
	 */
	MazeGenerator();

	/**
	 * @brief Calculates rectangle for block at given position
	 * @param x coordinate in grid
	 * @param y coordinate in grid
	 * @return Rectangle for block at (x,y)
	 */
	wxRect calculateBoundingRect(unsigned int x, unsigned int y) const;

	/**
	 * @brief Calculates width and height for
			  each block and stores them
	 * @param perRow: blocks in a single row.
	 */
	void calculateAndSetWH(unsigned int perRow);

	Canvas* _canvas;

	std::vector<std::shared_ptr<Block> > _blocks;
	std::shared_ptr<Block> _current;

	unsigned int _w;
	unsigned int _h;
	unsigned int _sleeptime;

};
