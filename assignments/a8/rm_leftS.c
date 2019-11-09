//"removes whitespace characters from the beginning of s" --pdf
//plural!

extern void rm_left_space(char *s1)
{
  int temp = 0;
  while(*s1 != 0)
    {
      if(*s1 == 0x20)
	{	  
	  while(*s1 != 0)
	    {
	      temp++;
	      s1++;
	      *(s1-1) = *s1;
	    }
	  
	  s1 -= temp;
	  temp = 0;
	}

      else
	s1++;
    }
}
