#include <stdio.h>

//professor, this is not the best approach, machine states need not be explicit, especially when it comes to automata as they are abstract by nature and can take any form in the real world. They don't neccesarily have to be assigned to a variable when they can virtually exist in the control flow of the execution. My previous code is an example of it as I based my e-NFA on the code, not the other way around. These states can be implicitly defined inside if statements and so forth.



//this is a minor feature to remove all recurring \n
//I am unsure how gcc does but mine is straightforward.
int line_compressor(FILE *fp)
{
  int lines = 0;
  char c;

  
  while((c = fgetc(fp)) == '\n')    
    lines++;  

  if(c != EOF)
    fseek(fp, -1, SEEK_CUR);

  return lines;
}


void space_handle(FILE *fp, FILE *des)
{ 
  fseek(fp, -3, SEEK_CUR); //should be -2...
  char c = fgetc(fp);

  //printf("%c\n", c);
  
  if(c == '\n')
    {      
      fseek(fp, 1, SEEK_CUR);
      while((c = fgetc(fp)) == ' ')
	{	  
	  fputc(' ', des);
	}

      if(c != EOF)
	fseek(fp, -1, SEEK_CUR);
      return;
    }
  
  fseek(fp, 1, SEEK_CUR);  //another weird interaction here as the offset can be 2 but the output will not change.

  while((c = fgetc(fp)) == ' '); //just advance the cursor

  if(c != EOF)
    fseek(fp, -1, SEEK_CUR); 
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

  enum states{DEFAULT=1, OPEN_SLASH, REDACT, CLOSE_STAR, NEW_LINE, STRING_LITERAL, SPACING};

  int state = DEFAULT;

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

  
  FILE *des = fopen(argv[2], "w");
  
  int open = 0; //flag for seeing the open quote
  char c; 
  int linum = 1; //line counter
  int loc = 0; //location for open quote
  int space = 2; //padding   

  
  //main loop.
  //The states of quote redacting machine are explicit and integrated into the control flow. Other's will behave naturally inside their functions above.
  while(!feof(fp))
    {
      c = fgetc(fp);

      switch(state)
	{
	case DEFAULT:
	  if(c == '/')
	    state = OPEN_SLASH;	      
	    
	  else if(c == '"')	    
	    state = STRING_LITERAL;	    
	    
	  else if(c == ' ')	    	    
	    state = SPACING;
	    
	  else if(c == '\n')	    	    
	    state = NEW_LINE;
	    
	  else
	    fputc(c, des);
	  break;

	case OPEN_SLASH:

	  if(c == '*')
	    {
	      state = REDACT;
	      loc = linum;
	      open = 1;
	    }
	  else if(c == '"')
	    {
	      fputc('/', des);
	      state = STRING_LITERAL;
	    }
	  else if(c == '\n')
	    {
	      fputc('/', des);
	      state = NEW_LINE;
	    }
	  else if(c == ' ')
	    {
	      fputc('/', des);
	      state = SPACING;
	    }
	  else
	    {
	      fprintf(des, "/%c", c);
	      state = DEFAULT;
	    }
	  break;
	  
	case REDACT:	  
	  if(c == '\n')
	    {
	      linum++;
	      space = 0;
	    }
	  else if(c == '*')
	    {
	      space++;
	      state = CLOSE_STAR;
	    }
	  space++;
	  break;

	case CLOSE_STAR:
	  if(c == '/')
	    {
	      space++;
	      for(int i = 0; i < space; i++)
		fprintf(des, " ");
	      
	      space = 2;
	      open = 0;
	      state = DEFAULT;
	    }
	  else
	    {
	      space++;	      
	      state = REDACT;
	      if(c == '\n')
		{
		  linum++;
		  space = 0;		  
		}
	    }
	  break;
	  
	case NEW_LINE:
	  fputc('\n', des);
	  fseek(fp, -1, SEEK_CUR);
	  linum += line_compressor(fp) + 1; 
	  state = DEFAULT;
	  break;
	  
	case STRING_LITERAL:
	  fputc('"', des);
	  fseek(fp, -1, SEEK_CUR);
	  linum += quote_handle(fp, des);
	  state = DEFAULT;
	  break;

	case SPACING:	  
	  fputc(' ', des);	  
	  space_handle(fp, des);
	  state = DEFAULT;
	  break;
	}
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
