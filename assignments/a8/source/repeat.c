#ifdef __linux__
#include "../my_headers.h"


extern char *repeat(char *s, int x, char sep)
{
  init_heap(7000);
  
  int len = 0;
  while(*s != 0)
    {
      s++;
      len++;
    }
  s -= len;

  char *ret = (char*) s_malloc(len*x + x);
  char *fin = ret;
  
  for(int i = 0; i < x; i++)
    {
      for(int j = 0; j < len; j++)
	{
	  *ret = s[j];
	  ret++;
	}
      *ret = sep;
      ret++;      
    }
  *(ret-1) = 0;
  return fin;
}

#else
#include <stdlib.h>

extern char *repeat(char *s, int x, char sep)
{
  if(s == NULL)
    return NULL;
  
  int len = 0;
  while(*s != 0)
    {
      s++;
      len++;
    }
  s -= len;

  char *ret = (char*) malloc(len*x + x);
  char *fin = ret;
  
  for(int i = 0; i < x; i++)
    {
      for(int j = 0; j < len; j++)
	{
	  *ret = s[j];
	  ret++;
	}
      *ret = sep;
      ret++;      
    }
  *(ret-1) = 0;
  return fin;
}

#endif
