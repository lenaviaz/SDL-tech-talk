#include "characters.h"

struct dimentions getDimentions(char *ppm_to_read_from) {

  struct dimentions dims;

  dims.width = 0;
  dims.height = 0;

  FILE *ppm_data = fopen(ppm_to_read_from, "r");

  int max_size = 200;

  char line[max_size]; // max size
  int line_count = 0;

  while (fgets(line, max_size, ppm_data)) {

    if (line[0] == 'P') {
      line_count += 1;
      continue;
    }

    if (line_count == 1) {

      printf("printing line");
      printf(line);

      if (sscanf(line, "%d %d", &dims.width, &dims.height) == 2) {

        line_count += 1;
        continue;
      }

      else {
        // Parsing failed; the buffer does not contain two valid integers
        // Handle the error here
        printf("Error: Unable to parse width and height from the buffer.\n");
        line_count += 1;
      }

      return dims;
    }
  }
  // end of while loop

  return dims;
}

void write_ppm_data(char *ppm_file, char *textfile) {
  struct dimentions dims;

  dims.width = 0;
  dims.height = 0;

  FILE *sample_data_1 = fopen(ppm_file, "r");
  FILE *image_data = fopen(textfile, "w");

  int max_size = 200;

  char line[max_size]; // max size
  int line_count = 0;

  while (fgets(line, max_size, sample_data_1)) {

    if (line[0] == 'P') {
      line_count += 1;
      continue;
    }

    if (line[0] == '#') {
      // don't copy comments
      continue;
    }

    if (line_count == 1) {

      printf("printing line");
      printf(line);

      if (sscanf(line, "%d %d", &dims.width, &dims.height) == 2) {

        line_count += 1;
        continue;
      }

      else {
        // Parsing failed; the buffer does not contain two valid integers
        // Handle the error here
        printf("Error: Unable to parse width and height from the buffer.\n");
        line_count += 1;
      }
    }

    /* if(line[4] == '\0' && line[1] == ' ') */
    /*   { */
    /*     //set matrix width and height */
    /*     width = line[0] - '0'; */
    /*     height = line[2] - '0'; */
    /*     continue; */
    /*   } */

    if (line[4] == '\0' && line[1] != ' ') {
      // skip final line before image data
      continue;
    }

    fputs(line, image_data);
  }

  // fputc('a', image_data);
  fclose(image_data);
  fclose(sample_data_1);
}

void fill_byte_array(unsigned char *byte_values, char *dimention_data,
                     char *image_data) {

  struct dimentions thing;
  thing = getDimentions(dimention_data);

  int width = thing.width;
  int height = thing.height;

  FILE *sample_data = fopen(image_data, "rb");
  int c;
  int buffer_size = width * height * 3 * 3;
  int index = 0;

  int value = 0;
  int digit_count = 0;
  // copy to text without any spaces

  while ((c = fgetc(sample_data)) != EOF) {

    if ((c >= 48) && (c <= 57)) // check if its a digit value
    {
      value = (value * 10) + (c - '0');
      digit_count += 1;
    } else if ((c == ' ') || (c == '\t') || (c == '\n')) {
      if (digit_count > 0) {
        byte_values[index] = (unsigned char)value;
        index += 1;
        value = 0;
        digit_count = 0;
      }
    }
    // this only case is the end of the file?
    byte_values[index] = (unsigned char)value;
    // index += 1;
    // value = 0;
    //  digit_count = 0;

  } // end of while

  int rbg_bytes_total = (width * height) * 3;

  for (int i = 0; i < rbg_bytes_total; i++) {
    unsigned char a = byte_values[i];
    int b = (int)a;
    printf("\n%i", b);
  }
  printf("\n\n\n");

  fclose(sample_data);
}

void fill_pixel_array(rgb_value *pixels, unsigned char *byte_values,
                      int rgb_bytes_total) {
  int increment = 0;
  for (int i = 0; i < rgb_bytes_total; i += 3) {
    rgb_value one_pixel;
    one_pixel.r = byte_values[i];
    one_pixel.g = byte_values[i + 1];
    one_pixel.b = byte_values[i + 2];

    pixels[increment] = one_pixel;
    increment += 1;

    printf("\n\n%i\n\n", increment);
  }
} 
   
void fill_background(SDL_Window *window, SDL_Renderer *renderer, background_image* background, character* ch) {

  rgb_value** background_data = create2DArray(background->pixels, background);

  int array_position = 0;
  
  for (int i = 0; i < 70; i++) { // height
    for (int j = 0; j < 70; j++) { //width

      rgb_value draw_value = background_data[j][i];
      
      int r = (int)draw_value.r;
      int g = (int)draw_value.g;
      int b = (int)draw_value.b;

      //printf("\n\n\n\n\n\n COLORS ARE: %d %d %d \n\n\n", r, g, b);

      SDL_SetRenderDrawColor(renderer, r, g, b, 0);
      SDL_RenderDrawPoint(renderer, i, j);

      /* rgb_value draw_value = background->pixels[array_position]; */

      /* int r = (int)draw_value.r; */
      /* int g = (int)draw_value.g; */
      /* int b = (int)draw_value.b; */
    
      
      /* SDL_SetRenderDrawColor(renderer, r, g, b, 0); */
      /* SDL_RenderDrawPoint(renderer, j, i); */
      /* array_position += 1; */
    }
  }
  free2DArray(background_data, background);
  
}



void draw_to_screen(SDL_Renderer *renderer, character* ch) {

  int array_position = 0;

  for (int i = 0 + ch->pos_y; i < ch->height + ch->pos_y; i++) { 

    for (int j = 0 + ch->pos_x; j < ch->width + ch->pos_x; j++) {
      rgb_value draw_value = ch->pixels[array_position];

      int r = (int)draw_value.r;
      int g = (int)draw_value.g;
      int b = (int)draw_value.b;

      SDL_SetRenderDrawColor(renderer, r, g, b, 0);
      SDL_RenderDrawPoint(renderer, j, i);
      array_position += 1;
    }
  }

  /* SDL_RenderPresent(renderer); */
}

void move_enemy(character *ch, int *dirrection) {

  if (ch->pos_y == 40) {
    *dirrection = 1; // start moving up
  }

  if (ch->pos_y == 0) {
    *dirrection = -1; // start moving up
  }

  if (*dirrection == 1) {
    ch->pos_y = ch->pos_y - 1;
  }

  if (*dirrection == -1) {
    ch->pos_y = ch->pos_y + 1;
  }
}

void *frame_handler(void *vargp) {
  /* sleep(0.03); */
  /* :  if(is_moving) */
  /*   { */
  /*   } */
}



int collision_detected(character* ch, int** collision_map)
{

  int map_value = collision_map[ch->pos_y + 3][ch->pos_x];

  if(map_value == 88)
    {
      return 1;
    }
  
  /* printf("map value is: %i ", map_value);  */
  
  return 0;
}
