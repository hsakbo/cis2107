static int memlength(char **strs, int n)
{
  int count = 0;
  char *s;
  for(int i = 0; i < n; i++)
    {
      s = strs[i];
      while(*s != 0)
	{
	  count++;
	  s++;
	}
    }
  return count;
}

#ifdef __linux__
#include "../my_headers.h"
extern char *str_connect(char **strs, int n, char c)
{
  int len = memlength(strs, n);

  init_heap(2 * (len+n));
  char *ret = s_malloc(len+n+1);
  char *fin = ret; //because I don't exactly wanna debug offsets

  
  char *s;
  for(int i = 0; i < n; i++)
    {
      s = strs[i];
      while(*s != 0)
	{
	  
	  *ret = *s;
	  s++;
	  ret++;
	}
      *ret = c;
      ret++;
    }
  *(ret-1) = 0;
  return fin;

}

#else
#include <stdlib.h>
extern char *str_connect(char *strs[], int n, char c)
{
  int len = memlength(strs, n);

  //init_heap(2 * (len+n));
  char *ret = malloc(len+n+1);
  char *fin = ret; //because I don't exactly wanna debug offsets

  
  char *s;
  for(int i = 0; i < n; i++)
    {
      s = strs[i];
      while(*s != 0)
	{
	  
	  *ret = *s;
	  s++;
	  ret++;
	}
      *ret = c;
      ret++;
    }
  *(ret-1) = 0;
  return fin;

}
#endif
