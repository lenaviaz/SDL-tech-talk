#include <SDL.h>
#include <png.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> //Header file for sleep(). man 3 sleep for details.
#include <zlib.h>

#define WINDOW_WIDTH 70
#define WINDOW_HEIGHT 70
#define MAX_JUMP 7
#define FALSE 0
#define TRUE 1

struct dimentions {
  int width, height;
};

typedef struct {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} rgb_value;

typedef struct {
  unsigned char *byte_values;
  rgb_value *pixels;
  int width;
  int height;
  int pos_x;
  int pos_y;
  int direction;
  int jumping;
} character;

typedef struct {
  unsigned char *byte_values;
  rgb_value *pixels;
  int width;
  int height;

} background_image;

typedef struct {
  SDL_Renderer *renderer;
  character ch;
} ThreadArgs;

struct dimentions getDimentions(char *ppm_to_read_from);

void write_ppm_data(char *ppm_file, char *textfile);

void fill_byte_array(unsigned char *byte_values, char *dimention_dat,
                     char *image__data);

void fill_pixel_array(rgb_value *pixels, unsigned char *byte_values,
                      int rgb_bytes_total);

void draw_to_screen(SDL_Renderer *renderer, character *ch);

void fill_background(SDL_Window *window, SDL_Renderer *renderer, background_image* background, character* ch);

void move_enemy(character *ch, int *dirrection);

void *frame_handler(void *vargp);

int collision_detected(character* ch, int** collision_map);
