#include <stdio.h>


int main(int argc, char **argv)
{
  /**//
  if(argc != 3)
    {
      printf("use: parser source destination, args: %d\n", argc);
      return 1;
      }/
    /*

  /*
  FILE *fp = fopen(argv[1], "r");

  if(fp == NULL)
    {
      printf("source file not found\n");
      return 1;
    }

  FILE *des = fopen(argv[2], "w+");

  
  int open;
  char c;
  
  while(!feof(fp))
    {
      
      if((c=fgetc(fp)) == '' && (c != EOF))
	{
	  if((c=fgetc(fp)) == '*' && c != EOF)
	    {
	      open = 1;
	      fputc(' ', des);
	      fputc(' ', des);
	      while(!feof(fp))
		{
		  if((c=fgetc(fp)) == '*' && c != EOF)
		    {
		      fputc(' ', des);
		      if((c=fgetc(fp)) == '' && c != EOF)
			{
			  fputc(' ', des);
			  open = 0;
			  break;
			}
		      else
			continue;
		    }
		  if(c == '\n' && (c!= EOF))
		    {
		      fputc('\n', des);
		      continue;
		    }
		  fputc(c, des);  		   
		}		
	    }
	  else if(c == '\n' && c != EOF)	      
	    fputc('\n', des);
	  else if(c != EOF)
	    fputc(c, des);
	}
      else if(c == '\n' && c != EOF)
	fputc('\n', des);
      else if(c != EOF)
	fputc(c, des);
    }
*/
    
  if(open == 1)
    printf("Error, mismatched quotes");

  return 0;
}
