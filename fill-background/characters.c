 #include "characters.h"

character *generateCharacter(char *ppm_file, char *textfile, int start_x,
                             int start_y) {

  struct dimentions player_dims;
  player_dims = getDimentions(ppm_file);

  int width = player_dims.width;
  int height = player_dims.height;

  int buffer_size = width * height * 3 * 3;

  character *player = (character *)malloc(sizeof(character));
  write_ppm_data(ppm_file, textfile);
  player->byte_values =
      (unsigned char *)malloc(buffer_size * sizeof(unsigned char));
  fill_byte_array(player->byte_values, ppm_file, textfile);
  int rgb_bytes_total = (width * height) * 3;
  player->pixels = malloc((width * height) * sizeof(rgb_value));
  fill_pixel_array(player->pixels, player->byte_values, rgb_bytes_total);

  player->width = width;
  player->height = height;
  player->pos_x = start_x;
  player->pos_y = start_y;
  player->direction = 1;
  player->jumping = 0;

  return player;
}


background_image *generateBackground(char *ppm_file, char *textfile) {

  struct dimentions background_dims;
  background_dims = getDimentions(ppm_file);

  int width = background_dims.width;
  int height = background_dims.height;

  int buffer_size = width * height * 3 * 3;

  background_image *background = (background_image *)malloc(sizeof(background_image));
  write_ppm_data(ppm_file, textfile);
 background->byte_values =
      (unsigned char *)malloc(buffer_size * sizeof(unsigned char));
  fill_byte_array(background->byte_values, ppm_file, textfile);
  int rgb_bytes_total = (width * height) * 3;
  background->pixels = malloc((width * height) * sizeof(rgb_value));
  fill_pixel_array(background->pixels, background->byte_values, rgb_bytes_total);

  background->width = width;
  background->height = height;

  return background;
}


rgb_value** create2DArray(rgb_value *pixels, background_image* background)
{

  int width = background->width;
  int height = background->height;

  rgb_value** array = (rgb_value **)malloc(height * sizeof(rgb_value*));


  int array_position = 0;					   
					   
  for (int i = 0; i < height; i++) {
    array[i] = (rgb_value *)malloc(width * sizeof(rgb_value));
  }
					   

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
	  
      rgb_value pixel = pixels[array_position];
      array[i][j] = pixel;

	  
      //printf("\n\n\n\n\n\n filling 2d array colors ARE: %d %d %d \n\n\n", pixel.r, pixel.g, pixel.b);

      array_position = array_position + 1;
      // array[i][j] = data[i][j];  // Assign values from your data to the array
	    
    }
  }

    return array;
					   
}

int** create2DCollisionMapArray(char* map_file, int width, int height)
{

  //printf("\n\n\n hiiiiiii \n\n");
  int c;
  int** collision_array = (int **)malloc(height * sizeof(int*));

  for (int i = 0; i < height; i++) {
    collision_array[i] = (int *)malloc(width * sizeof(int));
    //printf("\n\n\n hiiiiiii \n\n");
  }

   FILE *sample_data = fopen(map_file, "rb");

   // printf("\n\n\ngot here hiiiiiii \n\n");

   int i = 0;
   int j = 0;

     while ((c = fgetc(sample_data)) != EOF)
       {
	 //printf("%c", c);

	 if(c == ' ')
	   {
	     continue;
	   }
	 
	 if(c != '\n')
	   {
	     collision_array[i][j] = c;
	     if((j + 1) != 70)
	       {
	     j = j + 1;
	   }
	 }

	 if(c == '\n')
	   {
	     if((i + 1) != 70)
	       {
		 i = i + 1;
		 j = 0;
	       }
	   }
       }

     //printf("end of function");
     return collision_array;
   fclose(sample_data);  
  
}


void free2DArray(rgb_value** array, background_image* background) {

  int height = background->height;
  
    for (int i = 0; i < height; i++) {
        free(array[i]);
    }
    free(array);
}

void free2DCollisionMapArray(int** collision_array, int height)
{

  for (int i = 0; i < height; i++) {
        free(collision_array[i]);
    }
    free(collision_array);
  
}
