//as of the moment. I don't have a s_realloc implemented.
//this is going to look ugly to work my way around.
#include <stddef.h>
static int occurences(char *s, char *pat, int lenS, int *loc)
{
  int delta = 0;
  int count = 0;
  for(int i = 0; i < lenS; i++)
    {
      
      if(*pat == s[i])
	{
	  pat++;
	  delta++;
	}
      else
	{
	  pat -= delta;
	  delta = 0;
	}
      
      if(*pat == 0)
	{
	  pat -= delta;
	  *loc = i-delta+1;
	  delta = 0;
	  count++;
	  loc++;
	}
    }
  *loc = -1;
  return count;
}

static int str_len(char *s)
{
  int ret = 0;
  while(*s != 0)
    {
      s++;
      ret++;
    }
  return ret;
}

#ifdef __linux__
#include "../my_headers.h"

extern char *replace(char *s, char *pat, char *rep)
{
  if(s == NULL)
    return NULL;

  int lenS = str_len(s);
  int lenR = str_len(rep);
  int lenP = str_len(pat);
  init_heap(lenS*lenR + sizeof(int)*lenS + 100);

  int *loc = s_malloc(sizeof(int)*lenS + 1);
  int ocr = occurences(s, pat, lenS, loc);
  int retLen = ocr*lenR + lenS - ocr*lenP+1;
  char *ret = s_malloc(retLen); //char is always 1 byte in all systems yes?

  int index = 0;
  while(*s != 0)
    {
      if(index == *loc)
	{
	  for(int i = 0; i < lenR; i++)
	    {
	      *ret = rep[i];
	      ret++;
	    }
	  loc++;
	  index += lenP;
	  s += lenP;
	}
      else
	{
	  index++;
	  *ret = *s;
	  s++;
	  ret++;
	}
    }

  //my heap is already initialized with 0
  return ret+1-retLen; 
}

#else
#include <stdlib.h>

extern char *replace(char *s, char *pat, char *rep)
{
  if(s == NULL)
    return NULL;

  int lenS = str_len(s);
  int lenR = str_len(rep);
  int lenP = str_len(pat);
  
  int *loc = malloc(sizeof(int)*lenS + 1);
  int ocr = occurences(s, pat, lenS, loc);
  int retLen = ocr*lenR + lenS - ocr*lenP+1;
  char *ret = malloc(retLen); //char is always 1 byte in all systems yes?

  int index = 0;
  while(*s != 0)
    {
      if(index == *loc)
	{
	  for(int i = 0; i < lenR; i++)
	    {
	      *ret = rep[i];
	      ret++;
	    }
	  loc++;
	  index += lenP;
	  s += lenP;
	}
      else
	{
	  index++;
	  *ret = *s;
	  s++;
	  ret++;
	}
    }

  
  *ret = 0;
  return ret+1-retLen; 
}

#endif
