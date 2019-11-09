extern int find(char *h, char *n)
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
		return count;

	      else if(*h == 0)
		return -1;
	      	      
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

  return -1;
}
