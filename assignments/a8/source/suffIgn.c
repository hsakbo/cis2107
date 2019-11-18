extern int ends_with_ignore_case(char *s, char *suff)
{
  int delta = 0;
  int c_main = 0;
  int c_suff = 0;
  
  while(1)
    {
      if(*s >= 0x41 && *s <= 0x5A)	
	c_main = *s + 32;
	
      else
	c_main = *s;

      if(*suff >= 0x41 && *suff <= 0x5A)
	c_suff = *suff + 32;

      else
	c_suff = *suff;

      
      if(*s == 0 && *suff == 0)
	return 1;

      else if(*s == 0 && *suff != 0)
	return 0;
            
      else if(c_suff == c_main)
	{
	  s++;
	  suff++;
	  delta++;
	}
      
      else
	{
	  s++;
	  suff -= delta;
	  delta = 0;
	}
    }
  return 0;
}

