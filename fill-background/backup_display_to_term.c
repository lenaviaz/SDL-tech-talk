#include <stdio.h>
#include <stdlib.h>



void print_bin(unsigned char value)
{
    for (int i = sizeof(char) * 7; i >= 0; i--)
        printf("%d", (value & (1 << i)) >> i );
    putc('\n', stdout);
}

int main()
{

  //black : (0, 0, 0)
  //white : (255, 255, 255)
  //red : (255, 0, 0)
  //green : (0,255,0)
  //blue : (0,0,255)
  //yellow : (255,255,0)
  //cyan : (0,255,255)
  //purple : (255,0,255)

  int width = 4;
  int height = 4;
  
  unsigned char rgb;
  unsigned char* pixel;

  int matrix[4][4] =
    {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  };
  
  int x = 0;
  int y = 0;

  FILE* sample_data = fopen("sample.ppm", "rb");
  FILE* image_data = fopen("image.txt", "w");

  int c;
  int line_num = 0;
  int space = 32;
  int tab = 9;
  int update = 0;
  int prev = -1;


  //copy to text without any spaces
  
   while((c = fgetc(sample_data)) !=EOF)
     {
       if(prev == -1)
	 {
	   fputc(c, image_data);
	   fputc(32, image_data);
	   prev == c;
	   continue;
	 }

       if(c == 32)
	 {
	   fputc(32, image_data);
	   continue;
	 }
       
       
       printf("%c", c);

       /* if(c == 48) */
       /* 	 { */
       /* 	   fputc(c, image_data); */
       /* 	   fputc(32, image_data); */
       /* 	 } */
       /* if(c == 50) */
       /* 	 { */
       /* 	   fputc(50, image_data); */
       /* 	   fputc(53, image_data); */
       /* 	   fputc(53, image_data); */
       /* 	   fputc(32, image_data); */
       /* 	 } */

       //fputc(c, image_data);

 
     }
  
   //image_data now has raw pixel data

  //space bar indicates a new number is coming


   
  
  fclose(sample_data);
  fclose(image_data);

  int a = 6;
  unsigned char b = (unsigned char)a;
  print_bin(b);
   
  return 0;
}
