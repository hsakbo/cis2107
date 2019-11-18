#include <stddef.h>

static void export(char *src, int offset, char *des)
{
  for(int i = 0; i < offset; i++)
    {
      des[i] = src[i];
    }
  des[offset] = 0;
}


#ifdef __linux__
#include "../my_headers.h"

extern char **str_chop_all(char *s, char c)
{
  int len = 0;
  while(*s != 0)
    {
      len++;
      s++;
    }
  s -= len;

  init_heap(sizeof(char*) * len * 128 + 100); //because of padding.

  char **ret = s_malloc(sizeof(char*) * (len+1));
  char **fin = ret;
  char *word;
  int offset = 0;
  while(*s != 0)
    {
      if(*s == c)
	{
	  word = s_malloc(offset+1);
	  export(s-offset, offset, word);
	  *ret = word;
	  ret++;
	  s++;
	  offset = 0;
	}
      else
	{
	  offset++;
	  s++;
	}
    }
  word = s_malloc(offset+1);
  export(s-offset, offset, word);
  *ret = word;
  ret++;
  *ret = NULL;
  return fin;
}

#else

#include <stdlib.h>

extern char **str_chop_all(char *s, char c)
{
  int len = 0;
  while(*s != 0)
    {
      len++;
      s++;
    }
  s -= len;

  char **ret = malloc(sizeof(char*) * (len+1));
  char **fin = ret;
  char *word;
  int offset = 0;
  while(*s != 0)
    {
      if(*s == c)
	{
	  word = malloc(offset+1);
	  export(s-offset, offset, word);
	  *ret = word;
	  ret++;
	  s++;
	  offset = 0;
	}
      else
	{
	  offset++;
	  s++;
	}
    }
  word = malloc(offset+1);
  export(s-offset, offset, word);
  *ret = word;
  ret++;
  *ret = NULL;
  return fin;
}
#endif
