#include <iostream>
#include<SDL.h>
#include "Main.h"
#define FPS 60
#define WIDTH 1000
#define HEIGHT 768
using namespace std;

bool g_running = false;
Uint32 g_start, g_end, g_delta, g_fps;
const Uint8* g_keystates;
SDL_Window* g_pWindow;
SDL_Renderer* g_pRenderer;


// int Run(); // Function prototype.

// Init function. Sets up SDL and all subsystems and other (dynamic) memory allocation.
int Init(const char* title, int xPos, int yPos, int width, int height, int flags)
{
	{
		cout << "Initializing game..." << endl;
		if (SDL_Init(SDL_INIT_EVERYTHING) == 0) // If initialization is okay
		{
			// Try to create the SDL_Window.
			g_pWindow = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
			if (g_pWindow != nullptr) // If window creation passes.
			{
				// Try to create the SDL_Renderer. (Back Buffer)
				g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
				if (g_pRenderer != nullptr)
				{
					// Do stuff later
				}
				else return false; // Renderer Creation failed.
			}
			else return false; // Window creation failed.
		}
		else return false; // Initialization has failed.
	}
	// If everything is okay we are here...
	g_fps = (Uint32)round(1 / (double)FPS * 1000);
	g_keystates = SDL_GetKeyboardState(nullptr);
	cout << "Initialization Sucessful!" << endl;
	g_running = true;
	return true;
}

// HandleEvents function. Gets input from user, e.g. mouse/keyboard/gamepad events.
void HandleEvents()
{
	//cout << "Getting input..." << endl;
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: // Pressing 'X' button of window.
			g_running = false;
			break;
		}
	}

}

bool KeyDown(SDL_Scancode c)
{
	if (g_keystates != nullptr)
	{
		if (g_keystates[c] == 1) // Key we're testing for down.
		return true;
	}
	return false;
}

// Update function. Moves objects, performs physics, e.g. projectiles, gravity, collisions.
void Update()
{
	//cout << "Updating game..." << endl;
	if (KeyDown(SDL_SCANCODE_F))
		cout << "F key pressed! " << endl;
}

// Render function. Renders changes in game objects to window.
void Render()
{
	//cout << "Rendering changes to window..." << endl;
	SDL_SetRenderDrawColor(g_pRenderer, 0, 128, 128, 255);
	SDL_RenderClear(g_pRenderer);
	// Any drawing goes here...

	SDL_RenderPresent(g_pRenderer); // Flip buffers - send data to window.

}

// Clean function. De-initialize SDL and de-allocate memory.
void Clean()
{
	cout << "Cleaning up..." << endl;
	SDL_DestroyRenderer(g_pRenderer);
	SDL_DestroyWindow(g_pWindow);
	SDL_Quit();
}

void Wake()
{
	g_start - SDL_GetTicks(); // Gets milliseconds since SDL Initialization.
}

void Sleep()
{
	g_end = SDL_GetTicks();
	g_delta = g_end = g_start; // 1055 - 1050 = 5ms
	if (g_delta < g_fps) // If (5ms < 17ms)
		SDL_Delay(g_fps - g_delta);// Engine sleeps for 12ms
}

// Run function. Contains the primary game loop.
int Run()
{
	if (g_running == true) // If engine is running.
	{
		return 1;
	}

	if(Init("GAME1007_M1_Ricko_MyenUddinKabir", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0) == false) // If initialization failed.
	{
		return 2;
	}
	// If Initialization passes , we are here.
	while (g_running) // Primary game loop. "frame"
	{
		Wake();
		HandleEvents(); // Input.
		Update(); // Processing.
		Render(); // Output.
		if (g_running == true)
			Sleep();
	}
	Clean();
	return 0;
}

// main function. Entry point in every C++ program.
int main(int argc, char* argv[])
{
	return Run();
}

