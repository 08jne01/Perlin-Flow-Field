#include "Program.h"

Program::Program(int width, int height, int seed, int noise, int nParticles, int trailLength, int fieldRate, int fullscreen) : w(width), h(height), s(seed), n(noise), perlin(100, 100, 100, seed, noise), scale(0.08), timeStep(10.0), x(0), y(0), z(0), boxSize(10), numParticles(nParticles), trailLen(trailLength), fRate(fieldRate)

{
	if (fullscreen == 1)

	{
		window.create(sf::VideoMode(w, h), "Perlin Flow Field <3", sf::Style::Fullscreen);
	}

	else

	{
		window.create(sf::VideoMode(w, h), "Perlin Flow Field <3", sf::Style::Default);
	}

	renderField = 0;
	force = 0.0003;

	for (int i = 0; i < numParticles; i++)

	{
		Particle p(w, h, force, timeStep);
		particle.push_back(p);
	}

	font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
}

int Program::mainLoop()

{
	sf::Event events;
	sf::Clock clockUpdate;
	makePoints(x,y,z);

	if (!window.isOpen())

	{
		std::cout << "Window could not be displayed!" << std::endl;
		system("PAUSE");
		return EXIT_FAILURE;
	}
	while (window.isOpen())

	{

		while (window.pollEvent(events))

		{
			if (events.type == sf::Event::EventType::Closed)

			{
				window.close();
			}

			else

			{
				keyBoardCallBack(events);
			}
		}
		if (clockUpdate.getElapsedTime().asMilliseconds() > 10)

		{
			update();
			tickRate = 1000 / clockUpdate.getElapsedTime().asMilliseconds();
			clockUpdate.restart();
		}
		
		window.clear(sf::Color::White);

		draw();

		if (renderField == 1)

		{
			drawVectorField();
			drawText();
		}
		window.display();

	}

	return EXIT_SUCCESS;
}

double Program::coordTransformX(double x)

{
	return x / (scale * w);
}

double Program::coordTransformY(double y)

{
	return y / (scale * h);
}

double Program::coordTransformZ(double z)

{
	return z / (scale * h * w);
}

void Program::reset()

{
	points.clear();
	particles.clear();
	particle.clear();

	for (int i = 0; i < numParticles; i++)

	{
		Particle p(w, h, force, timeStep);
		particle.push_back(p);
	}
}

void Program::update()

{
	z += fRate*timeStep;
	makePoints(x, y, z);
	for (int i = 0; i < particle.size(); i++)

	{
		particle[i].update(&scalarField, boxSize, timeStep, force);
	}
}

void Program::draw()

{
	
	for (int i = 0; i < particle.size(); i++)

	{
		particles.push_back(sf::Vertex(sf::Vector2f(particle[i].x, particle[i].y), particle[i].color));
		if (particles.size() > numParticles * 100 * trailLen)

		{
			particles.erase(particles.begin(), particles.begin() + numParticles);
			//std::cout << "Test" << std::endl;
		}
	}
	//std::cout << particles.size() / (60*numParticles) << std::endl;
	window.draw(&particles[0], particles.size(), sf::Points);
}

void Program::drawVectorField()

{
	points.clear();
	points.setPrimitiveType(sf::Lines);
	for (int i = 0; i < (w / boxSize); i++)

	{

		for (int j = 0; j < (h / boxSize); j++)

		{
			double val = scalarField[i][j];
			points.append(sf::Vertex(sf::Vector2f(i*boxSize, j*boxSize), sf::Color(0.0, 0.0, 255.0, 50)));
			points.append(sf::Vertex(sf::Vector2f(boxSize*(cos(6.0*PI*val) + i), boxSize*(-sin(6.0*PI*val) + j)), sf::Color(0.0, 0.0, 255.0, 50)));
		}
	}
	window.draw(points);
}

void Program::drawText()

{
	std::ostringstream os;
	os << "Tick rate: " << tickRate << std::endl 
	<< "Particle tail length: " << (particles.size() / (numParticles * 100))
	<< std::endl << "Timestep(pgup/pgdn): " << timeStep << std::endl
	<< "Force(left/right): " << force << std::endl
	<< "Field rate of change(up/down): " << fRate << std::endl
	<< "Backspace to reset particles!" << std::endl;
	std::string s = os.str();

	sf::Text text(s, font);
	text.setPosition(10, 10);
	text.setFillColor(sf::Color(0, 0, 255, 150));
	text.setCharacterSize(16);
	text.setStyle(sf::Text::Regular);
	window.draw(text);
}

void Program::drawPerlin()

{
	points.clear();
	for (int i = 0; i < (w / boxSize); i++)

	{

		for (int j = 0; j < (h / boxSize); j++)

		{
			double val = scalarField[i][j];
			points.append(sf::Vertex(sf::Vector2f(i*boxSize, j*boxSize), sf::Color(255.0*val, 255.0*val, 255.0*val)));
		}
	}
	window.draw(points);
}

void Program::makePoints(int x, int y, int z)

{
	scalarField.clear();
	for (int i = 0; i < (w / boxSize); i++)

	{
		std::vector<double> buff;
		for (int j = 0; j < (h / boxSize); j++)

		{
			double val = perlin.perlin(coordTransformX((double)i*boxSize + x), coordTransformY((double)j*boxSize + y), coordTransformZ(z));
			val = modVal(val);
			buff.push_back(val);
		}

		scalarField.push_back(buff);
	}
}

double Program::modVal(double val)

{
	double x = (val + 1.0) / 2.0;

	if (x > 1.0)

	{
		x = 1.0;
	}

	else if (x < 0.0)

	{
		x = 0.0;
	}

	return x;
}

void Program::keyBoardCallBack(sf::Event events)

{
	if (events.type == sf::Event::KeyPressed)

	{
		switch (events.key.code)

		{
			case sf::Keyboard::Space:

			{
				particles.clear();
				break;
			}

			case sf::Keyboard::PageUp:

			{
				timeStep *= 1.5;
				break;
			}

			case sf::Keyboard::PageDown:

			{
				timeStep /= 1.5;
				break;
			}

			case sf::Keyboard::Enter:

			{
				if (renderField == 1)

				{
					renderField = 0;
				}

				else

				{
					renderField = 1;
				}
				break;
			}

			case sf::Keyboard::Right:

			{
				force *= 1.5;
				break;
			}

			case sf::Keyboard::Left:

			{
				force /= 1.5;
				break;
			}

			case sf::Keyboard::Up:

			{
				fRate += 1;
				break;
			}

			case sf::Keyboard::Down:

			{
				fRate -= 1;
				break;
			}

			case sf::Keyboard::BackSpace:

			{
				reset();
				break;
			}
		}
	}
}