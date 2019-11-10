
extern void capitalize(char *s1)
{
  while(*s1 != 0)
    {
      while(*s1 == 0x20 && *s1 != 0) //compresses spaces
	s1++;

      //check to see the first char out of a space is a simple letter
      if(*s1 >= 0x61 && *s1 <= 0x7A && *s1 != 0)
	*s1 = *s1 - 32;      
	  	
      s1++; //2nd char After the space

      //if not a space, change capitals to simple.
      while(*s1 != 0x20 && *s1 != 0)
	{
	  if(*s1 >= 0x41 && *s1 <= 0x5A)
	    *s1 = *s1 + 32;
	  s1++;
	}

    }

}

