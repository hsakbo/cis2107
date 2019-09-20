#include <stdio.h>
#include <unistd.h> //only uses 1 function, which I thought was neat here.


//this is a minor feature to remove all recurring \n
//I am unsure how gcc does but mine is straightforward.
int line_compressor(FILE *des, FILE *fp)
{
  int lines = 0;
  char c;

  while((c = fgetc(fp)) == '\n')
    lines++;

  if(c != EOF)
    fputc(c, des);
  
  return lines;
}


//code refactoring to make it look readable.
//I am sure there are better designs but this here I just did exactly what I was told not to do (coding before planning)

//what it does: once /* has been seen, it ignores the stuff until */
int inner_loop(FILE *fp, FILE *des, int *open)
{
  int linum = 0;
  int space = 2;
  char c;
  
  while(!feof(fp))
    {
      if((c=fgetc(fp)) == '*' && c != EOF)
	{
	  space++;
	  if((c=fgetc(fp)) == '/' && c != EOF)
	    {
	      space++;
	      for(int i = 0; i < space; i++)
		fprintf(des, " ");
			  
	      *open = 0;
	      break;
	    }
	  else if(c == '\n')
	    {
	      space = 0;
	      linum++;
	      continue;
	    }
	  else
	    {
	      space++;
	      continue;
	    }
	}
		  
      if(c == '\n' && (c!= EOF))
	{
	  space = 0;
	  linum++;
	  continue;
	}
      space++;
    }
  return linum;
}

int main(int argc, char **argv)
{
  if(argc != 3)
    {
      printf("use: parser source destination, args: %d\n", argc);
      return 1;
    }

  FILE *fp = fopen(argv[1], "r");

  if(fp == NULL)
    {
      printf("source file not found\n");
      return 1;
    }

  FILE *des = fopen(argv[2], "w+");
  
  int open; //flag for seeing the open quote
  char c; 
  int linum = 1; //line counter
  int loc = 0; //location for open quote

  //main loop
  while(!feof(fp))
    {
      if((c=fgetc(fp)) == '/' && (c != EOF))
	{
	  if((c=fgetc(fp)) == '*' && c != EOF)
	    {
	      open = 1;
	      loc = linum;
	      linum += inner_loop(fp, des, &open);     
	    }
	  else if(c != EOF && c == '\n')
	    {
	      linum++;
	      fputc('/', des);
	      fputc('\n', des);
	      linum += line_compressor(des, fp);
	    }
	  
	  else if(c != EOF && c != '\n')
	    {
	      fputc('/', des);
	      fputc(c, des);
	    }
	}
      
      else if(c == '\n')
	{
	  linum++;
	  fputc('\n', des);
	  linum += line_compressor(des, fp);	  
	}
      else
	fputc(c, des);
    }

  fclose(fp);
  fclose(des);
  
  if(open == 1)
    {
      printf("Error, mismatched quotes\n line %d\n", loc);
      remove(argv[2]); //just removes the file created
    }
  return 0;
}
