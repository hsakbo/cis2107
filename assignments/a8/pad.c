#include <errno.h>
#include <stddef.h>

static int multi(int sLen, int d)
{
  int ret = 2;
  while(ret*d <= sLen)
    {
      ret += 2;
    }
  return ret;
}



#ifdef __linux__
#include "my_headers.h"

extern char *pad(char *s1, int d)
{
  if(s1 == NULL)
    return NULL;
  
  int len = 0;
  while(*s1 != 0)
    {
      len++;
      s1++;     
    }
  s1 -= len;

  int even_multiple  = multi(len, d);
  
  init_heap(even_multiple*d + 1000);  

  
  char *ret = (char*) s_malloc(even_multiple*d + 1);

  if(errno != 0)
    return NULL;
  
  
  for(int i = 0; i < len; i++)
    {
      ret[i] = s1[i];
    }
  
  if(len == even_multiple * d)
    {
      *(ret+len) = 0;
      return ret;
    }

  for(int i = 0; i < (even_multiple * d) - len; i++)
    ret[len+i] = 0x20;

  *(ret + even_multiple*d) = 0;
  return ret;
}


#else
#include <stdlib.h>

extern char *pad(char *s1, int d)
{
  if(s1 == NULL)
    return NULL;
  
  int len = 0;
  while(*s1 != 0)
    {
      len++;
      s1++;     
    }
  s1 -= len;

  int even_multiple  = multi(len, d);
  
  char *ret = (char*) malloc(even_multiple*d + 1);

  if(errno != 0)
    return NULL;
  
  for(int i = 0; i < len; i++)
    {
      ret[i] = s1[i];
    }
  
  if(len == even_multiple * d)
    {
      *(ret+len) = 0;
      return ret;
    }

  for(int i = 0; i < (even_multiple * d) - len; i++)
    ret[len+i] = 0x20;

  *(ret + even_multiple*d) = 0;
  return ret;
}

#endif
