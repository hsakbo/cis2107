#include <stdio.h>
#include <stdlib.h>
#include "my_headers.h"


extern char *dedup(char *s)
{
  int len = 0;
  init_heap(1000);
  while(*s != 0)
    {
      len++;
      s++;      
    }
  s -= len;

  char *ret = (void*) s_malloc(sizeof(char)*len +1);
  
  char map[128][1];

  for(int i = 0; i < 128; i++)
      map[i][0] = 0;

  int unique = 0;
  for(int i = 0; i <= len; i++)
    {
      if(map[*s][0] ==0)
	{
	  map[*s][0]++;
	  *ret = *s;
	  ret++;
	  unique++;
	}
      s++;
    }
  
  return ret-unique;
  
}


extern char *boring_dedup(char *s)
{
  int len = 0;
  //init_heap(1000);
  while(*s != 0)
    {
      len++;
      s++;      
    }
  s -= len;

  char *ret = (void*) malloc(sizeof(char)*len +1);
  
  char map[128][1];

  for(int i = 0; i < 128; i++)
      map[i][0] = 0;

  int unique = 0;
  for(int i = 0; i <= len; i++)
    {
      if(map[*s][0] ==0)
	{
	  map[*s][0]++;
	  *ret = *s;
	  ret++;
	  unique++;
	}
      s++;
    }  
  return ret-unique;  
}



