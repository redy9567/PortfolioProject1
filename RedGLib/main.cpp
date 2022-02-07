//#include "RedGLib.h"
#include "GraphicsSystem.h"
#include <iostream>

using namespace std;
 

int main()
{

	GraphicsSystem::initInstance();
	GraphicsSystem* gs = GraphicsSystem::getInstance();

	gs->init();

	cout << "Well Well" << endl;

	bool shouldContinue = true;
	while (shouldContinue)
	{
		shouldContinue = gs->update();
		gs->drawEllipse();
		gs->flip();
	}

	system("pause");

	gs->cleanup();
	GraphicsSystem::cleanupInstance();

}