#include <stdio.h>
//#include <unistd.h> //wanted to remove the output file, if mismatched quotes




//this is a minor feature to remove all recurring \n
//I am unsure how gcc does but mine is straightforward.
int line_compressor(FILE *des, FILE *fp)
{
  int lines = 0;
  char c;

  while((c = fgetc(fp)) == '\n')
    {
      lines++;
    }
  if(c != EOF)
    fputc(c, des);
  
  return lines;
}

//the space handler, it will remove additional spaces but if it starts from a newline, then it will print those spaces.
//note that when this function is about to end the cursor is pulled back one byte, it is for the main loop to handle that char.
void spaces(FILE *fp, FILE *des)
{ 
  fseek(fp, -3, SEEK_CUR); //should be -2...
  
  //further gdb testing shows that the first offset is consumed for an unknown reason, as it indicates a space char ' ' appearing twice per offset -1 and -2, with 0 being the current SEEK_CUR position.

  //I will, for now, conclude that this behaviour has got something to do with file buffering. Until disproven. (scientific method)
  
   /*explanation for the hypothesis: I have called c = fgetc(fp) down in the main() and once it returns a space character, this function is called onto the stack.

   *Since our offset is +1 due to the initial call of ONE fgetc(fp) in the main loop, it will have already been advanced to the next position.

   *fseeking -1 offset will move the cursor to the initial space that called this function in the main loop. The \n before the initial space is what I want c to get matched by the if call below, which is another -1.
 
   *Thus the offset adds upto to -2 and NOT -3 for fgetc to return \n
   */

  char c = fgetc(fp);
  
  if(c == '\n')
    {      
      fseek(fp, 2, SEEK_CUR);
      while((c = fgetc(fp)) == ' ')
	{
	  fputc(' ', des);
	}
      fseek(fp, -1, SEEK_CUR);
      return;
    }
  
  fseek(fp, 1, SEEK_CUR);  //another weird interaction here as the offset can be 2 but the output will not change.

  while(fgetc(fp) == ' '); //just advance the cursor
  fseek(fp, -1, SEEK_CUR); 
}


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


/*this is a simple quote handler unlike gcc parser
 *it will not care for the escape newline\(0x0a) on purpose. It's handling is not defined in ISO IEC 9899:2011 under 6.4.5 (string literals)
 *although, section 6.11.4: "lowercase letters as escape sequences are reserved for future standardization. Other characters may be used in extensions" (179)
 *so my use of parsing \0x0a (to completely ignore escaping) is not against C
 
*come to think of it, I could have just added it 
*rather than going onto explain why not by making a tiny essay with citations... 
*/
int quote_handle(FILE *fp, FILE *des)
{
  int count = 0;
  char c;

  while((c = fgetc(fp)) != '"' && c != EOF)
    {
      if(c == '\n')
	count++;
      
      fputc(c, des);      
    }

  if(c != EOF)
    fputc('"', des);


  return count;

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
  
  int open = 0; //flag for seeing the open quote
  char c; 
  int linum = 1; //line counter
  int loc = 0; //location for open quote
  
  
  //main loop.
  //my states are in the global scope, I would have adjusted the relevant states even if I call different methods in this loop. Thus, I have respected the goals of this assignment.
  while(!feof(fp))
    {
      if((c=fgetc(fp)) == '"' && !open)
	{
	  fputc(c, des);
	  linum += quote_handle(fp, des);
	}
      
      else if(c == '/')
	{	  
	  if((c=fgetc(fp)) == '*')
	    {
	      open = 1;
	      loc = linum;
	      linum += inner_loop(fp, des, &open);     
	    }
	  else if(c == '"' && !open)
	    {//since I call fgetc above
	      fputc(c, des);
	      linum += quote_handle(fp, des);
	    }
	  else if(c == '\n')
	    {
	      linum++;
	      fputc('/', des);
	      fputc('\n', des);
	      linum += line_compressor(des, fp);
	    }

	  else if(c == ' ')
	    {
	      fputc(' ', des);
	      spaces(fp, des);
	    }
	  
	  else if(c != EOF && c != '\n')
	    {
	      fputc('/', des);
	      fputc(c, des);
	    }
	}
      else if(c == ' ')
	{
	  fputc(' ', des);
	  spaces(fp, des);
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
  fprintf(des, "\n"); //padding as done by gcc -E
  fclose(des);
  
  if(open == 1)
    {
      printf("Error, mismatched quotes\n line %d\n", loc);
      //remove(argv[2]); enable to delete the bogus file
    }

  return 0;
}
