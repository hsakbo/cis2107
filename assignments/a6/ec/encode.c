#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


void set_cursor(FILE *fp)
{
  fseek(fp, 3, SEEK_SET);
  int count = 0;
  char c;
  while(count<3)
    {
      if(fgetc(fp) == '#')
	while(fgetc(fp) != 0xA);
      
      else
	{
	  count++;
	  while((c = fgetc(fp)) != 0xA && c != ' ');
	}
    }
}


int validity_bool(FILE *src, int size, FILE *des)
{
  
  if((fgetc(src) != 0x50) || (fgetc(src) != 0x36))
      return 0;
    
  set_cursor(src);
 
  unsigned long start = ftell(src);
  fseek(src, 0, SEEK_END);
  unsigned long end = ftell(src);
  unsigned long bytes = end - start;
  fseek(src, 0, SEEK_SET);  
  unsigned long mult = size;

  //printf("bytes: %ld\nmult: %ld\n", bytes, mult);
  
  if(bytes < 24+(mult*8))
    return 0;
 
  int ch;
  while((ch = fgetc(src)) != EOF)
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
  for(int i = 0; i < 8; i++)
    {
      arr[i] = fgetc(des);
    }

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

  set_cursor(des);
  
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
	    c = c&(~one); //11111110
	    
	  fseek(des, -1, SEEK_CUR);
	  fputc(c, des);
	  mask1 = mask1 >> 1;
	  
	}
    }
}

void hide_img(FILE *des, FILE *read, unsigned int size)
{
  
  fseek(des, -24, SEEK_END);
  unsigned int temp = 0;
  unsigned char c = 0;

  
  for(int i = 0; i < 12; i++)
    {
      temp = size<<(8+2*i);
      temp = temp>>30;
      
      fseek(des, 1, SEEK_CUR);
      c = fgetc(des);
      c = ((c>>2)<<2) | temp;
      fseek(des, -1, SEEK_CUR);
      fputc(c, des);
    }
  

  
  rewind(read);
  set_cursor(des);
  
  unsigned char tmp = 0;
  unsigned char mask;
  for(int i = 0; i<size; i++)
    {
      mask = 128;
      tmp = fgetc(read);
      for(int j = 0; j < 4; j++)
	{
	  
	  fseek(des, 1, SEEK_CUR);
	  c = fgetc(des);
	  c = (c>>2)<<2;
	  if(tmp&mask)
	    c = c|2;
	  mask = mask>>1;
	  if(tmp&mask)
	    c = c|1;
	  fseek(des, -1, SEEK_CUR);
	  fputc(c, des);	  	  
	  mask = mask>>1;
	}
    }
  

}

int pic_encode(char *src, char *des)
{
  FILE *fp = fopen(des, "r");
  if(fp == NULL)
    {
      perror("error: destination not found\n");
      exit(5);
    }
  
  char output_name[strlen(des) + 10];
  for(int i = 0; i < strlen(des)-4; i++)
    {
      output_name[i] = des[i];
      output_name[i+1] = 0;
    }

  char *ap = "_modified.ppm";
  strcat(output_name, ap);
  FILE *desF = fopen(output_name, "w+");
  FILE *read = fopen(src, "r");
  if(read == NULL)
    {
      perror("error: source not found\n");
      exit(6);
    }

  
  fseek(read, 0, SEEK_END);
  unsigned int size = (unsigned int) ftell(read);

  if(validity_bool(fp, size, desF))
    {
      hide_img(desF, read, size);
      
    }
  else
    {
      perror("unsuccessful, please check if source is ppm or \nif the size of the image is smaller than 16mb");
      fclose(desF);
      remove(output_name);
      
      exit(3);
    }
  return 1;
}

int main(int argc, char **argv)
{
  
  if(argc != 3 && argc != 4)
    {
      perror("usage: encode Picture Msg or \nencode -p16 source destination\n");
      exit(1);
    }

  if(argc == 4)
    {
      if(strcmp(argv[1], "-p16") == 0)  //wow, I have a new-found appreciation for flag handling
	pic_encode(argv[2], argv[3]);
      else if(strcmp(argv[2], "-p16") == 0)
	pic_encode(argv[3], argv[1]);
      else
	{
	  perror("incorrect usage\
usage: encode Picture Msg\
or encode -p16 source destination\n");
	  exit(2);
	    
	}
      return 0;
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
