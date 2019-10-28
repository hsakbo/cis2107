#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_size(FILE *fp)
{
  fseek(fp, -8, SEEK_END);
  int retval = 0;

  char arr[9];
  arr[8] = 0;
  for(int i = 0; i < 8; i++)
    {
      arr[i] = fgetc(fp);      
    }

  unsigned char mask = 128;

  for(int i = 0; i < 8; i++)
    {
      if(arr[i]&1)
	retval = retval|mask;
      mask = mask>>1;
    }
  
  return retval;
}



void print_msg(FILE *fp, int size)
{
  fseek(fp, 3, SEEK_SET);
  for(int i = 0; i < 2; i++)
    while(fgetc(fp) != 0x0A);

  unsigned char c;
  unsigned char mask;
  for(int i = 0; i < size; i++)
    {
      mask = 128;
      c = 0;
      for(int j = 0; j < 8; j++)
	{
	  if(fgetc(fp)&1)
	    c = c|mask;
	    
	  mask = mask>>1;	  
	}
      printf("%c", c);
    }
  printf("\n");
}

int get_img_size(FILE *fp)
{
  fseek(fp, -24, SEEK_END);
  char arr[25];
  arr[24] = 0;
  for(int i = 0; i < 24; i++)
    arr[i] = fgetc(fp);

  int retval = 0;
  for(int i = 1; i < 24; i+=2)
    {
      retval = retval<<2;
      retval = retval|(arr[i]&3);      
    }
  return retval;
}

void handle_file(char *src, char *dest)
{
  FILE *fp = fopen(src, "r");
  FILE *des = fopen(dest, "w+");
  int len = get_img_size(fp);
  printf("%d\n", len);
}

int main(int argc, char **argv)
{
  if((argc != 4) && (argc != 2))
    {
      perror("usage: decode FILE or decode -f FILE Des");
      exit(1);
    }

  if(argc == 4)
    {
      if(strcmp(argv[1], "-f") == 0)
	handle_file(argv[2], argv[3]);
      else if(strcmp(argv[2], "-f") == 0)
	handle_file(argv[3], argv[1]);
      else
	{
	  perror("error: incorrect usage of -f flag\ndecode FILE or decode -f file des");
	  exit(5);
	}
      return 0;
    }

  FILE *fp = fopen(argv[1], "r");

  int len = get_size(fp);
  print_msg(fp, len);
  return 0;
}
