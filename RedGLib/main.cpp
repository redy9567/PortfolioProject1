//#include "RedGLib.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include <iostream>

using namespace std;
 
LPCWSTR p = L"C:\\Users\\spyid\\Documents\\PortfolioProject1\\RedGLib\\cat.jpg";

int main()
{

	GraphicsSystem::initInstance();
	GraphicsSystem* gs = GraphicsSystem::getInstance();

	gs->init();

	//cout << "Well Well" << endl;

	//GraphicsBuffer* buf = new GraphicsBuffer(p);

	bool shouldContinue = true;
	while (shouldContinue)
	{
		shouldContinue = gs->update();
		gs->drawEllipse();
		gs->flip();
	}

	system("pause");

	//delete buf;
	//buf = nullptr;

	gs->cleanup();
	GraphicsSystem::cleanupInstance();

}