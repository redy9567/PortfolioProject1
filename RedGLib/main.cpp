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
	system("pause");

	gs->cleanup();
	GraphicsSystem::cleanupInstance();

}