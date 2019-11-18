
extern void shorten(char *s1, int len)
{
  int size = 0;
  while(*s1 != 0)
    {
      size++;
      s1++;
    }
  if(len > size)
    return;

  *(s1 - len) = 0;
  return;
}

