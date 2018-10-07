#include "Particle.h"

Particle::Particle()

{

}

Particle::Particle(int width, int height, double f, double time): w(width), h(height), force(f), xVel(0.0), yVel(0.0), xForce(0.0), yForce(0.0), timeStep(time)

{
	x = random(1, width - 1);
	y = random(1, height - 1);
}

void Particle::update(std::vector<std::vector<double>> *scalarField, int boxSize, double time, double f)

{
	force = f;
	timeStep = time;
	if (x > w)

	{
		x = 1.0;
	}

	if (x < 0)

	{
		x = w - 1;
	}

	if (y > h)

	{
		y = 1.0;
	}

	if (y < 0)

	{
		y = h - 1;
	}

	int gridX = ((int)x / boxSize) % ((w / boxSize) - 1);
	int gridY = ((int)y / boxSize) % ((h / boxSize) - 1);
	double angle = PI * 6.0 * (*scalarField)[gridX][gridY];

	double forceRatioX = cos(angle);
	double forceRatioY = sin(angle);

	xForce = force*forceRatioX;
	yForce = -force*forceRatioY;


	xAcc = xForce;
	xVel += xAcc*timeStep;


	yAcc = yForce;
	yVel += yAcc * timeStep;

	double magVel = xVel * xVel + yVel * yVel;

	if (magVel > 0.01)

	{
		double mag = sqrt(magVel);
		xVel *= 0.5;
		yVel *= 0.5;
	}

	x += xVel * timeStep;
	y += yVel * timeStep;

	//color = sf::Color(255.0 * (xVel / 0.06), 0.0, 255.0 * (1 - (yVel / 0.06)), 10);
	color = sf::Color(0.0, 0.0, 0.0, 10);

}

int Particle::sgn(double x)

{
	if (x < 0)

	{
		return -1;
	}

	else if (x > 0)

	{
		return 1;
	}

	else

	{
		return 0;
	}
}

double Particle::random(double min, double max)

{
	int val = rand() % ((int)max - (int)min + 1) + (int)min;
	return (double)val;
}