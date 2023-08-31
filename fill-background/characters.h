#include "functions.h"

character *generateCharacter(char *ppm_file, char *textfile, int start_x,
                             int start_y);

background_image *generateBackground(char *ppm_file, char *textfile);



rgb_value** create2DArray(rgb_value *pixels, background_image* background);

int** create2DCollisionMapArray(char* map_file, int width, int height);

void free2DArray(rgb_value** array, background_image* background);

void free2DCollisionMapArray(int** collision_array, int height);
