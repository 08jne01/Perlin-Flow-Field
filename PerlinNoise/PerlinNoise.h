#pragma once
#include "Header.h"

class PerlinNoise

{
public:
	PerlinNoise(int xGridSize, int yGridSize, int zGridSize, int seed, int noise);

	double lerp(double d1, double d2, double w);
	double lerpCos(double d1, double d2, double w);
	double dotGridGradient(int intX, int intY, int intZ, double x, double y, double z);
	double perlin(double x, double y, double z);
	double random(double min, double max);
	double sCurve(double val);
	double fractalNoise(double x, double y, double z, int layers);

private:

	std::vector<std::vector<std::vector<std::vector<double>>>> vectorField;
	int s, n, xSize, ySize, zSize;
};