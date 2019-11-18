
extern int diff(char *s1, char *s2)
{
  int retVal = 0;
  while(*s1 != 0 || *s2 != 0)
    {
      if(*s1 == 0)
	{
	  retVal++;
	  s2++;
	}
      else if(*s2 == 0)
	{
	  retVal++;
	  s1++;
	}
      else if(*s1 == *s2)
	{
	  s1++;
	  s2++;
	}
      else
	{
	  retVal++;
	  s1++;
	  s2++;
	}
    }
  return retVal;
}
