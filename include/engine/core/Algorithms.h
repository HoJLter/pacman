#pragma once
#include "vector"
#include "SFML/Graphics.hpp"


struct Point {
	int x;
	int y;
};


std::vector<std::vector<int>> calcShortestPath(std::vector<std::vector<int>> matrix, 
	Point start, 
	Point target);