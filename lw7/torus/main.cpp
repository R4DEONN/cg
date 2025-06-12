#include "Application.h"

int main(int argc, char* argv[]) {
	Application app(800, 600, "Morphing: Sphere <-> Torus");
	app.Run();
	return 0;
}