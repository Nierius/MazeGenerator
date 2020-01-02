#ifndef MAZEENUMS_H
#define MAZEENUMS_H
/**
 * @author Marius Niemenmaa (GitHub/LokSrc)
 * @date 03/01/20
 * @file mazeenums.h
 */
enum Wall {
	Top, Right, Bottom, Left
};

enum blockOpening {
	Closed,
	North,
	NorthSouth,
	NorthWest,
	NorthEast,
	South,
	SouthWest,
	SouthEast,
	West,
	WestEast,
	East
};
#endif // MAZEENUMS_H
