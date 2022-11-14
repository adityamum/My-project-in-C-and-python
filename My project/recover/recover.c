#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{

   typedef uint8_t BYTE;

    if(argc < 2)
    {

       printf("./recover IMAGE\n");
       return 1;

    }

    FILE *ptr = fopen(argv[1], "r");


    if(ptr == NULL)
    {
       printf("file not found");
       return 1;

    }

   BYTE buffer[512];
   int count = 0;
   FILE *img;
   char filename[8];


   while (fread(buffer, 1, 512, ptr) == 512)
   {

         if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
         {

               if (count != 0){

                   fclose(img);                  //close the jpeg excluding first
          }

          sprintf(filename, "%03i.jpg" , count);    //if found the jpegs
          img = fopen(filename, "w");
          fwrite(buffer , 1 , 512 , img);
          count++;

         }


        else if (count > 0){

               fwrite(buffer, 1, 512, img);           //write the rest block excluding header

         }
  }


     fclose(ptr);
  }




























