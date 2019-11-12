
extern void rm_right_space(char *s)
{
  int len = 0;
  while(*s != 0)
    {
      len++;
      s++;
    }

  s--;
  for(int i = 1; i < len && *s == 0x20; i++)
    {
      *s = 0;
      s--;
    }
}

