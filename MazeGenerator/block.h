#pragma once

#include <wx/wx.h>
#include <iostream>
#include "canvas.h"
#include "mazeenums.h"
#include "mazegenerator.h"

class Canvas;
typedef unsigned int uint;

/**
 * @class Walls
 * @author Marius Niemenmaa (GitHub/LokSrc)
 * @date 02/01/20
 * @file block.h
 * @brief Represents walls of a block.
 */
struct Walls {
	bool Top = true;
	bool Right = true;
	bool Bottom = true;
	bool Left = true;
};

/**
 * @class Block
 * @author Marius Niemenmaa (GitHub/LokSrc)
 * @date 02/01/20
 * @file block.h
 * @brief Block represents one cell in the maze.
 */
class Block
{
public:
	/**
	 * @brief Constructor for the class.
	 * @param scene parent canvas
	 * @param i x position in grid
	 * @param j y position in grid
	 */
	Block(Canvas* scene, uint i, uint j);

	/**
	 * @brief Default destructor.
	 */
	~Block();

	/**
	 * @brief Remove wall from the block and call Block::UpdateRect()
	 * @param wall to be removed (see mazeenums.h/Wall)
	 * @throws out_of_range exception
	 */
	void removeWall(int wall);

	/**
	 * @brief Draws cell to the scene.
	 *
	 *
	 * NOTE: Only scene should call this
	 *
	 *
	 * @param dc wxDeviceContext
	 */
	void Draw(wxDC& dc);

	/**
	 * @brief Sets bounding rect for block.
	 * @param bound wxRect to be set
	 */
	void setBoundingRect(wxRect bound);

	/**
	 * @brief Mark this block as visited.
	 */
	void visit();

	/**
	 * @brief Send paint event to scene.
	 */
	void UpdateRect() const;


	/**
	 * @brief Get block opening (see. mazeenums.h/blockOpening)
	 * @return int corresponding to blockOpening
	 */
	int getBlockOpening() const;

	/**
	 * @brief Get x(=i) position in grid.
	 * @return x position
	 */
	uint getX() const;

	/**
	* @brief Get y(=j) position in grid.
	* @return y position
	*/
	uint getY() const;

	/**
	 * @brief Has this block been visited.
	 * @return true: if block has been visited
	 * false: otherwise
	 */
	bool visited() const;

private:
	Canvas* _scene;
	uint _i, _j;
	Walls _walls;
	wxRect _boundingRect;
	bool _visited;

	wxColour _closedFill;
	wxColour _openFill;
	wxColour _selectedFill;
};
