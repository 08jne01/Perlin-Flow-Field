#pragma once
#include "Header.h"

class Particle

{
public:

	Particle();
	Particle(int width, int height, double f, double time);
	void update(std::vector<std::vector<double>> *scalarField, int boxSize, double time, double f);
	int sgn(double x);
	double random(double min, double max);
	double x, y;
	std::vector<std::vector<double>> pastPos;
	sf::Color color;
private:
	double xVel, yVel, xAcc, yAcc, xForce, yForce, force, timeStep;
	int w, h;
};