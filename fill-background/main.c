#include "characters.h"

int thread_is_running = 1;
const int FPS = 30;
const int frameDelay = 1000 / FPS; // Maximum time for a frame in milliseconds

void print_bin(unsigned char value) {
  for (int i = sizeof(char) * 7; i >= 0; i--)
    printf("%d", (value & (1 << i)) >> i);
  putc('\n', stdout);
}

int main() {

  character *player = generateCharacter("sample.ppm", "image.txt", 0, 0);

  character *enemy = generateCharacter("other.ppm", "image_2.txt", 10, 0);

  background_image *background =
      generateBackground("background_test_platform.ppm", "image_3.txt");

  rgb_value **background_data = create2DArray(background->pixels, background);

  int **collision_map = create2DCollisionMapArray("colision_map.txt", 70, 70);

  /* for(int i = 0; i < 70; i++) */
  /*   { */
  /*     for(int j = 0; j < 70; j++) */
  /* 	 { */
  /* 	   printf("value at (%i %i) :%i \n", i, j, collision_map[i][j]); */

  /* 	 } */
  /*   } */

  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window *window = SDL_CreateWindow("Pix", SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, 600, 600, 0);
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, 0); // TODO: is -1 or 0?
  SDL_RenderSetLogicalSize(renderer, 70, 70);

  int keep_window_open = 1;
  int moving_right = 0;
  int moving_left = 0;
  int max_jump = 5;
  int jump_level = 1;
  int jumping = FALSE;

  int dirrection = -1; // start moving down

  int *val = &dirrection;

  Uint32 frameStart, frameTime;

  const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

  while (keep_window_open) {
    frameStart = SDL_GetTicks();

    move_enemy(enemy, val);
    printf("\n pos x and y : %d %d", player->pos_x, player->pos_y);

    if (moving_right) {
      player->pos_x = player->pos_x + 1;
    }

    if (moving_left) {
      player->pos_x = player->pos_x - 1;
    }

    if (player->jumping == 1) {
      player->pos_y = player->pos_y - 3;
      jump_level += 1;

      if (jump_level > MAX_JUMP) {
        player->jumping = FALSE;
      }
    }

    if ((!collision_detected(player, collision_map)) && (jumping == FALSE)) {
      player->pos_y = player->pos_y + 1;
    }

    // collision_detected(player, collision_map);
    //  Rendering the enemy and player
    fill_background(window, renderer, background, player);
    // draw_to_screen(renderer, enemy);
    //draw_to_screen(renderer, player);

    SDL_RenderPresent(renderer);

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_QUIT:
        thread_is_running = 0;
        keep_window_open = 0;
        break;

      case SDL_KEYDOWN:

        if (e.key.keysym.sym == SDLK_SPACE) {
          printf("Key press jump detected\n");

          if (collision_detected(player, collision_map)) {

            player->jumping = TRUE;
          }
        }

        if (e.key.keysym.sym == SDLK_DOWN) {
          printf("Key press down detected\n");
          player->pos_y = player->pos_y + 1;
        }

        if (e.key.keysym.sym == SDLK_RIGHT) {
          printf("Key press right detected\n");
          // player->pos_x = player->pos_x + 1;
          moving_right = TRUE;
        }

        if (e.key.keysym.sym == SDLK_LEFT) {
          printf("Key press left detected\n");

          if (player->pos_x >= 1) {
            moving_left = TRUE;
            // player->pos_x = player->pos_x - 1;
          }
        }
        // left Arrow
        break;
        ////////////////////////////////////////////

      case SDL_KEYUP:

        if (e.key.keysym.sym == SDLK_SPACE) {

          // player.pos_y = player.pos_y - 3;

          printf("Key jump was released\n");
          // player->pos_y = player->pos_y + 3;
          jump_level = FALSE;
          player->jumping = FALSE;
        }

        if (e.key.keysym.sym == SDLK_DOWN) {
          printf("Key press down released\n");
          player->pos_y = player->pos_y + 1;
        }

        if (e.key.keysym.sym == SDLK_RIGHT) {
          printf("Key press right released\n");
          moving_right = FALSE;
        }

        if (e.key.keysym.sym == SDLK_LEFT) {
          printf("Key press left released\n");
          moving_left = FALSE;
        }

        break;

      default:
        break;
      }
    }

    // Frame management
    frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime) {
      SDL_Delay(frameDelay - frameTime);
    }
  }

  free2DCollisionMapArray(collision_map, 70);

  free2DArray(background_data, background);

  free(background->byte_values);
  free(background->pixels);
  free(background);

  free(player->byte_values);
  free(player->pixels);
  free(player);

  free(enemy->byte_values);
  free(enemy->pixels);
  free(enemy);

  return 0;
}
