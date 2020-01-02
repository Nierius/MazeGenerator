#include "block.h"

Block::Block(Canvas* scene, uint i, uint j)
	: _scene(scene)
	,_i(i)
	, _j(j)
	, _walls(Walls())
	, _boundingRect(wxRect())
	, _visited(false)
	, _closedFill(wxColour(0,0,0))
	, _openFill(wxColour(90,90,90))
	, _selectedFill(wxColour(0,75,75))
{
}

Block::~Block()
{
}

void Block::removeWall(int wall)
{
	if (wall == Wall::Bottom)
		_walls.Bottom = false;
	else if (wall == Wall::Top)
		_walls.Top = false;
	else if (wall == Wall::Left)
		_walls.Left = false;
	else if (wall == Wall::Right)
		_walls.Right = false;
	else
		throw std::out_of_range("Invalid wall to remove!");
	UpdateRect();
}

void Block::Draw(wxDC& dc)
{
	wxPoint topLeft  = _boundingRect.GetTopLeft();
	wxPoint topRight = _boundingRect.GetTopRight();
	wxPoint botLeft  = _boundingRect.GetBottomLeft();
	wxPoint botRight = _boundingRect.GetBottomRight();
	wxColour colour;
	
	// Set colour
	if (MazeGenerator::getInstance().isCurrent(this)) {
		colour = _selectedFill;
	} else if (_walls.Top && _walls.Bottom && _walls.Left && _walls.Right) {
		colour = _closedFill;
	} else {
		colour = _openFill;
	}
	
	// Draw block
	dc.GradientFillLinear(_boundingRect, colour, colour);
	if (_walls.Top) {
		dc.DrawLine(topLeft, topRight);
	}
	if (_walls.Bottom) {
		dc.DrawLine(botLeft, botRight);
	}
	if (_walls.Left) {
		dc.DrawLine(topLeft, botLeft);
	}
	if (_walls.Right) {
		dc.DrawLine(topRight, botRight);
	}
}

void Block::setBoundingRect(wxRect bound)
{
	_boundingRect = bound;
}

void Block::visit()
{
	_visited = true;
}

void Block::UpdateRect() const
{
	_scene->RefreshRect(_boundingRect);
	_scene->Update();
}

int Block::getBlockOpening() const
{
	if(!_walls.Top && _walls.Bottom && _walls.Left && _walls.Right)
		return blockOpening::North;
	else if(_walls.Top && !_walls.Bottom && _walls.Left && _walls.Right)
		return blockOpening::South;
	else if(_walls.Top && _walls.Bottom && !_walls.Left && _walls.Right)
		return blockOpening::West;
	else if(_walls.Top && _walls.Bottom && _walls.Left && !_walls.Right)
		return blockOpening::East;
	else if(!_walls.Top && !_walls.Bottom && _walls.Left && _walls.Right)
		return blockOpening::NorthSouth;
	else if(!_walls.Top && _walls.Bottom && !_walls.Left && _walls.Right)
		return blockOpening::NorthWest;
	else if(!_walls.Top && _walls.Bottom && _walls.Left && !_walls.Right)
		return blockOpening::NorthEast;
	else if(_walls.Top && !_walls.Bottom && !_walls.Left && _walls.Right)
		return blockOpening::SouthWest;
	else if(_walls.Top && !_walls.Bottom && _walls.Left && !_walls.Right)
		return blockOpening::SouthEast;
	else if(_walls.Top && _walls.Bottom && !_walls.Left && !_walls.Right)
		return blockOpening::WestEast;
	return blockOpening::Closed;
}

uint Block::getX() const
{
	return _i;
}

uint Block::getY() const
{
	return _j;
}

bool Block::visited() const
{
	return _visited;
}
