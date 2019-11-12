#include <stdio.h>
#ifdef __linux__
#include "my_headers.h"

extern char *str_zip(char *s1, char *s2)
{

  int len1 = 0;
  while(*s1 != 0)
    {
      s1++;
      len1++;
    }
  s1 -= len1;

  int len2 = 0;
  while(*s2 != 0)
    {
      s2++;
      len2++;
    }
  s2 -= len2;

  init_heap(len1+len2+100);
  char *output = s_malloc(len1+len2+1);
  char *ret = output;
  
  while(*s1 != 0 || *s2 != 0)
    {
      if(*s2 == 0)
	{
	  *output = *s1;
	  s1++;
	  output++;
	}
      else if(*s1 == 0)
	{
	  *output = *s2;
	  s2++;
	  output++;	  
	}
      else
	{
	  *output = *s1;
	  output++;
	  *output = *s2;
	  output++; s1++; s2++; //looks nice and compact.	 
	}
    }
  *output = 0;
  return ret;
}

#else
#include <stdlib.h>

extern char *str_zip(char *s1, char *s2)
{

  int len1 = 0;
  while(*s1 != 0)
    {
      s1++;
      len1++;
    }
  s1 -= len1;

  int len2 = 0;
  while(*s2 != 0)
    {
      s2++;
      len2++;
    }
  s2 -= len2;

  char *output = malloc(len1+len2+1);
  char *ret = output;
  while(*s1 != 0 || *s2 != 0)
    {
      if(*s2 == 0)
	{
	  *output = *s1;
	  s1++;
	  output++;
	}
      else if(*s1 == 0)
	{
	  *output = *s2;
	  s2++;
	  output++;	  
	}
      else
	{
	  *output = *s1;
	  output++;
	  *output = *s2;
	  output++; s1++; s2++; //looks nice and compact.	 
	}
    }
  *output = 0;
  return ret;
}


#endif


int main()
{
  printf("%s\n", str_zip("hello", "WORLD!"));
  kaijo();
}
