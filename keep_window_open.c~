#include "core.h"

int main()
{

SDL_Init(SDL_INIT_VIDEO);

SDL_Window* window = SDL_CreateWindow("Pix", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, 0);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_RenderSetLogicalSize(renderer, 16, 16);

SDL_RenderClear(renderer);
SDL_RenderPresent(renderer);

sleep(5);


}
