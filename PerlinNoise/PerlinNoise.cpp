#include "PerlinNoise.h"

PerlinNoise::PerlinNoise(int xGridSize, int yGridSize, int zGridSize, int seed, int noise): s(seed), n(noise), xSize(xGridSize), ySize(yGridSize), zSize(zGridSize)

{
	srand(seed);
	rand();

	for (int i = 0; i < xGridSize; i++)

	{
		std::vector<std::vector<std::vector<double>>> buff2;
		for (int j = 0; j < yGridSize; j++)

		{
			std::vector<std::vector<double>> buff;
			for (int k = 0; k < zGridSize; k++)

			{
				std::vector<double> coords;
				coords.push_back(random(-n, n));
				coords.push_back(random(-n, n));
				coords.push_back(random(-n, n));
				buff.push_back(coords);
			}
			buff2.push_back(buff);
		}
		vectorField.push_back(buff2);
	}
}

double PerlinNoise::lerp(double d1, double d2, double w)

{
	return d1 + w*(d2 - d1);
}

double PerlinNoise::sCurve(double x)

{
	return (x*x*x*(x*(6 * x - 15) + 10));
}

double PerlinNoise::lerpCos(double d1, double d2, double w)

{
	double w2 = (1 - cos(w*PI)) / 2.0;
	return (d1 * (1 - w2) + d2 * w2);
}

double PerlinNoise::dotGridGradient(int intX, int intY, int intZ, double x, double y, double z)

{

	double dx = x - (double)intX;
	double dy = y - (double)intY;
	double dz = z - (double)intZ;

	return (dx * vectorField[intX][intY][intZ][0] + dy * vectorField[intX][intY][intZ][1] + dz * vectorField[intX][intY][intZ][2]);
}

double PerlinNoise::perlin(double xVal, double yVal, double zVal)

{
	double x = xVal;
	double y = yVal;
	double z = zVal;
	int correction;

	correction = int(x) / (xSize - 1);
	x -= double(correction)*(double)(xSize - 1);

	correction = int(y) / (ySize - 1);
	y -= double(correction)*(double)(ySize - 1);

	correction = int(z) / (zSize - 1);
	z -= double(correction)*(double)(zSize - 1);

	int x0 = int(x);
	int y0 = int(y);
	int z0 = int(z);

	int x1 = x0 + 1;
	int y1 = y0 + 1;
	int z1 = z0 + 1;

	double sX = x - double(x0);
	double sY = y - double(y0);
	double sZ = z - double(z0);

	double n0, n1, ix0, ix1, ixy0, ixy1, value;

	//z = 0

	//(0,0) -> (1,0)
	n0 = dotGridGradient(x0, y0, z0, x, y, z);
	n1 = dotGridGradient(x1, y0, z0, x, y, z);
	//Interpolate (xInterpolated, 0)
	ix0 = lerpCos(n0, n1, sX);
	//(0,1) -> (1,1)
	n0 = dotGridGradient(x0, y1, z0, x, y, z);
	n1 = dotGridGradient(x1, y1, z0, x, y, z);
	//Interpolate (xInterpolated, 1)
	ix1 = lerpCos(n0, n1, sX);
	//Interpolate (xInterpolated, yInterpolated)
	ixy0 = lerpCos(ix0, ix1, sY);

	//z = 1

	//(0,0) -> (1,0)
	n0 = dotGridGradient(x0, y0, z1, x, y, z);
	n1 = dotGridGradient(x1, y0, z1, x, y, z);
	//Interpolate (xInterpolated, 0)
	ix0 = lerpCos(n0, n1, sX);
	//(0,1) -> (1,1)
	n0 = dotGridGradient(x0, y1, z1, x, y, z);
	n1 = dotGridGradient(x1, y1, z1, x, y, z);
	//Interpolate (xInterpolated, 1)
	ix1 = lerpCos(n0, n1, sX);
	//Interpolate (xInterpolated, yInterpolated)
	ixy1 = lerpCos(ix0, ix1, sY);

	value = lerpCos(ixy0, ixy1, sZ);

	return value;
}

double PerlinNoise::fractalNoise(double x, double y, double z, int layers)

{
	double val = perlin(x, y, z) / 2.0;

	for (int i = 1; i < layers; i++)

	{
		val += perlin(x / (double)i, y / (double)i, z / (double)i) / (0.5*(double)i);
	}
	return val;
}

double PerlinNoise::random(double min, double max)

{
	int val = rand() % ((int)max*10000 - (int)min*10000 + 1) + (int)min*10000;
	return (double)val / 10000.0;
}