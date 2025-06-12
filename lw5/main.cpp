#define CALLBACK __stdcall

#include "App.h"

int main()
{
	App app(1280, 720, false);
	app.Run();
	return 0;
}
