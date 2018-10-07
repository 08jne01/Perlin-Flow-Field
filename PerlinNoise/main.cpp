#include "Header.h"
#include "Program.h"

int main()

{
	sf::err().rdbuf(NULL);
	int seed, width, height, noise, numParticles, defaultSetup, trailLength, fieldRate, fullscreen;
	noise = 1;

	std::cout << "Default?: ";
	std::cin >> defaultSetup;

	if (defaultSetup == 1)

	{
		Program program(1920, 1080, 4, 1, 10000, 7, 10, 1);
		return program.mainLoop();
	}

	else

	{
		std::cout << "Number of Particles(100-10000): ";
		std::cin >> numParticles;

		std::cout << "\nWidth (width of your screen duh): ";
		std::cin >> width;

		std::cout << "\nHeight (i think you know): ";
		std::cin >> height;

		std::cout << "\nSeed (whatever even 4 ;): ";
		std::cin >> seed;

		std::cout << "\nTrail Length (7): ";
		std::cin >> trailLength;

		std::cout << "\nField rate of change (10): ";
		std::cin >> fieldRate;

		std::cout << "\nFullscreen (1): ";
		std::cin >> fullscreen;

		Program program(width, height, seed, noise, numParticles, trailLength, fieldRate, fullscreen);
		return program.mainLoop();
	}

	
	
}