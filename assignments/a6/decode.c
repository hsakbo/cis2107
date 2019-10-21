#include <stdio.h>
#include <stdlib.h>

int get_size(FILE *fp)
{
  fseek(fp, -8, SEEK_END);
  int retval = 0;

  char arr[9];
  arr[8] = 0;
  fscanf(fp, "%s", arr);

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
	    {
	      c = c|mask;
	    }
	  mask = mask>>1;	  
	}
      printf("%c", c);
    }
  printf("\n");
}

int main(int argc, char **argv)
{
  if(argc != 2)
    {
      perror("usage: decode FILE");
      exit(1);
    }

  FILE *fp = fopen(argv[1], "r");

  int len = get_size(fp);
  print_msg(fp, len);
  return 0;
}
