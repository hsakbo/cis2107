#include <stddef.h>

static int str_len(char *s1)
{
  int ret = 0;
  while(*s1 != 0)
    {
      s1++;
      ret++;
    }
  return ret;
}

extern void rm_empties(char **words)
{
  int count = 0;
  while(*words != NULL)
    {
      if(!str_len(*words))
	{
	  while(*words != NULL)
	    {
	      *words = *(words+1);
	      words++;
	      count++;
	    }
	  *words = NULL;
	  words -= count;
	}
      else
	words++;
    }
}
