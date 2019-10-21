#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validity_bool(FILE *fp, int char_len, FILE *des)
{
  
  if((fgetc(fp) != 0x50) && (fgetc(fp) != 0x36))
     return 0;
  
  fseek(fp, 1, SEEK_CUR);
  if(fgetc(fp) == '#')
    while(fgetc(fp) != 0xA);


  int width = 0;
  fscanf(fp, "%d", &width);
  

  int height = 0;
  fscanf(fp, "%d", &height);


  if(height*width < 8+(char_len*8))
    return 0;

  //assuming 255
  fseek(fp, 4, SEEK_CUR);

  fprintf(des, "P6\n%d %d\n255", width, height);
  int ch;
  while((ch = fgetc(fp)) != EOF)
    {
      fputc(ch, des);
    }

  return 1;

}

void hide(FILE *fp, char *str, FILE *des)
{
  
  fseek(des, -8, SEEK_END);
  
  unsigned char arr[9];
  arr[8] = 0;
  fscanf(des, "%s", arr); 

  int len = strlen(str);
  unsigned char mask1 = 1<<7;
  //unsigned char mask0 = 254;
  unsigned char one = 1;
  fseek(des, -8, SEEK_END);
  for(int i = 0; i < 8; i++)
    {
      
      if(len&mask1)
	fputc(arr[i]|one, des);
      else
	fputc(arr[i] & (~one), des);	
      mask1 = mask1 >> 1;
    }
  
  fseek(des, 3, SEEK_SET);
  for(int i = 0; i < 2; i++)    
    while(fgetc(des) != 0xA);

 

  char c = 0;
  for(int i = 0; i < strlen(str); i++)
    {
      mask1 = 128;
      for(int j = 0; j < 8; j++)
	{
	  c = fgetc(des);
	  if(str[i] & mask1)
	    c = c|1;
	    
	  else
	    c = c&(~one);
	    
	  fseek(des, -1, SEEK_CUR);
	  fputc(c, des);
	  mask1 = mask1 >> 1;
	  
	}
    }
}

int main(int argc, char **argv)
{
  
  if(argc != 3)
    {
      perror("usage: encode Picture Msg");
      exit(1);
    }

  FILE *fp = fopen(argv[1], "r");

  if(fp == NULL)
    return 1;

  char output_name[strlen(argv[1]) + 10];

  for(int i = 0; i < strlen(argv[1])-4; i++)
    {
      output_name[i] = argv[1][i];
      output_name[i+1] = 0;
    }

  char *ap = "_modified.ppm";
  strcat(output_name, ap);

  FILE *des = fopen(output_name, "w+");
  
  if(validity_bool(fp, strlen(argv[2]), des))
    {
      hide(fp, argv[2], des);      
      //return 0;
    }  
  
  return 0;
}
