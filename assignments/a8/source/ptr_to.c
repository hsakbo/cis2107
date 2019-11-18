#include <stddef.h>

extern char *ptr_to(char *h, char *n)
{
  int count = 0;
  int delta = 0;
  while(*h != 0)
    {
      if(*h == *n)
	{
	  while(*h == *n)
	    {
	      h++;
	      n++;
	      delta++;
	      
	      if(*n == 0)
		return (h-delta);

	      else if(*h == 0)
		return NULL;
	      	      
	    }
	  h -= (delta-1);
	  n -= delta;
	  delta = 0;
	}
      else
	{
	  count++;
	  h++;
	}
    }

  return NULL;
}
