#include <stddef.h>
extern int is_empty(char *s1)
{
  if(s1 == NULL)
    return 1;
  
  while(*s1 != 0)
    {
      if(*s1 != 0x20)
	return 0;
      s1++;
    }
  return 1;
}
