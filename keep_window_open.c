#include "core.h"

int main()
{

  int keep_window_open = 1;

SDL_Init(SDL_INIT_VIDEO);

SDL_Window* window = SDL_CreateWindow("Pix", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, 0);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_RenderSetLogicalSize(renderer, 16, 16);


  while(keep_window_open) {  
SDL_RenderClear(renderer);
SDL_RenderPresent(renderer);


 SDL_Event e;

 while(SDL_PollEvent(&e))
   {

     switch(e.type)
       {
       case SDL_QUIT:

	 keep_window_open = 0;
	 break;


       default:
	 break;

       }



   }

  }

}
