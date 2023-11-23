// HumanDatabase.cpp : Defines the entry point for the application.
//

#include "HumanDatabase.h"

using namespace std;

int main()
{
	cout << "Creating Window" << endl;

	Window* pWindow = new Window();

	bool running = true;
	while (running)
	{
		if (!pWindow->ProcessMessages())
		{
			cout << "Destroying Window" << endl;
			running = false;
		}

		// Render

		Sleep(10);
	}

	delete pWindow;

	return 0;
}
