
extern void rm_left_space(char *s1)
{
  int temp = 0;
  while(*s1 != 0 && *s1 == 0x20)
    {
      temp++;
      s1++;
    }
  while(*s1 != 0)
    {
      *(s1-temp) = *s1;
      s1++;
    }
  *(s1-temp) = 0;    
}

