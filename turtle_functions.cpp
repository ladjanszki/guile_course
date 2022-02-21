#include <iostream> 
#include <cmath>


#include <SDL2/SDL.h> 


/*
 * We need another loop here because events is a list of wevents
 * we registered since the last time we processed the list
 * and multiple input could be registered
 * we don't want to check only the top one, we want to understand all
 *
 * In this example the event loop will be updated since 
 * modification of objects and redrawing of the canvas will happen there from now on
 */


// Pointer for the renderer
static SDL_Renderer* renderer = nullptr;


// Size of the window
static int WINDOW_WIDTH = 640; 
static int WINDOW_HEIGHT = 480; 

// State variables for the turtle 
static double pos_x = WINDOW_WIDTH / 2;
static double pos_y = WINDOW_HEIGHT / 2;
static double direction = 0.0;
static int pendown = 1;


static void tortoise_reset() 
{

	pos_x = WINDOW_WIDTH / 2;
	pos_y = WINDOW_HEIGHT / 2;
	direction = 0.0;
	pendown = 1;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	//SDL_RenderPresent(renderer);

}


static void tortoise_pendown()
{
	pendown = 1;
}


static void tortoise_penup()
{
	pendown = 0;
}



static void draw_line(double x0, double y0, double x1, double y1)
{
      	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
      	SDL_RenderDrawLine(renderer, x0, y0, x1, y1);
}


static void tortoise_turn(double degrees)
{
  direction += M_PI / 180.0 * degrees;
}


static void tortoise_move(double length)
{
  double new_x, new_y;

  new_x = pos_x + length * cos(direction);
  new_y = pos_y + length * sin(direction);

  if (pendown)
    draw_line(pos_x, pos_y, new_x, new_y);

  pos_x = new_x;
  pos_y = new_y;
}




int main(int argc, char* argv[])
{

	// Create a window pointer
	SDL_Window* window = nullptr;


	// Initalising the video subsystem with error handling
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}


	// Create an app window with error checking
	window = SDL_CreateWindow(
		"This is my window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN
			);

	// Check success of window creation 
	if (window == nullptr){
		std::cout << "Window creation failed" << SDL_GetError() << std::endl;
		return 1;
	}


	// creating a renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


	// Creating the event queue
	SDL_Event event;


	// THIS WILL BE THE PLACE FOR THE PROGRAM LOOP
	bool is_running = true;

	tortoise_reset(); 


	while(is_running){


		//SDL_Event event;
		SDL_Delay(16);



		// (1) Handle input (user and generated as well)
		while(SDL_PollEvent(&event)) {

			switch(event.type) {
				case SDL_QUIT:
					is_running = false;

				case SDL_KEYDOWN:
					//std::cout << "keydown" << std::endl;
					//std::cout << event.key << std::endl;
					
					tortoise_turn(-13);
					tortoise_move(100);


			}

		}

		// (2) handle updates


		// (3) Clearing and painting the background to white 
		//SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		//SDL_RenderClear(renderer);

		// Actual drawing
		//SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		//SDL_RenderDrawLine(renderer, 5, 5, 100, 100);



		tortoise_reset(); 

		tortoise_move(100);

		tortoise_turn(-90);
		tortoise_move(100);

		tortoise_turn(-90);
		tortoise_penup();
		tortoise_move(100);
		tortoise_pendown();

		tortoise_turn(-90);
		tortoise_move(100);



		SDL_RenderPresent(renderer);


	}
	


	SDL_DestroyWindow(window);

	SDL_Quit();


	return 0;
}
