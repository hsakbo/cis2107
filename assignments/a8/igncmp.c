//policy:
//-1 if s1 is after s2. (s1 > s2)
//+1 if s1 is before s2. (s1 < s2)
//while there is a possibility for an infinite loop, it is pretty safe even for
//a bad usage without the terminating 0.


extern int strcmp_ign_case(char *s1, char *s2)
{
  int c_s1, c_s2;
  while(1)
    {
      //simple checks
      if(*s1 == 0 && *s2 == 0)
	return 0;
      else if(*s1 == 0)
	return 1;
      else if(*s2 == 0)
	return -1;

      else if(*s1 == *s2)
	{
	  s1++;
	  s2++;
	  continue;
	}


      
      c_s1 = *s1;
      c_s2 = *s2;
      
      if(c_s1 >= 0x41 && c_s1 <= 0x5A)
	{
	  if(c_s2 >= 0x5B && c_s2 <= 0x60)
	    return 1;
	  
	  c_s1 += 32;
	}
      
      if(c_s2 >= 0x41 && c_s2 <= 0x5A)
	{
	  if(c_s1 >= 0x5B && c_s1 <= 0x60)
	    return -1;
	  
	  c_s2 += 32;
	}


      
      if(c_s1 == c_s2)
	{
	  s1++;
	  s2++;
	}

      else if(c_s1 > c_s2)
	return -1;

      else
	return 1;
    }

}

