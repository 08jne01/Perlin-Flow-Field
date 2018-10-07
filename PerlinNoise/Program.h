#pragma once
#include "Header.h"
#include "PerlinNoise.h"
#include "Particle.h"

class Program

{
public:
	Program(int width, int height, int seed, int noise, int nParticles, int trailLength, int fieldRate, int fullscreen);
	int mainLoop();
	double coordTransformX(double x);
	double coordTransformY(double y);
	double coordTransformZ(double z);
	double modVal(double val);
	void keyBoardCallBack(sf::Event events);
	void makePoints(int x, int y, int z);
	void drawPerlin();
	void drawText();
	void draw();
	void update();
	void drawVectorField();
	void reset();

private:
	int w, h, s, n, x, y, z, boxSize, numParticles, trailLen, fRate, renderField, tickRate;
	double scale, timeStep, force;
	PerlinNoise perlin;
	sf::Font font;
	std::vector<sf::Vertex> particles;
	std::vector<Particle> particle;
	sf::VertexArray points;
	sf::RenderWindow window;
	std::vector<std::vector<double>> scalarField;
};