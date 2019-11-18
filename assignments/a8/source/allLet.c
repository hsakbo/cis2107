
int all_letters(char *s)
{
  while(*s != 0)
    {
      if(*s<65 || *s>122 || (*s>90 && *s<97))
	return 0;
      s++;
    }
  return 1;  
}


