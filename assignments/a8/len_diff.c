extern int len_diff(char *s1, char *s2)
{
  int len1 = 0;
  int len2 = 0;

  while(*s1 != 0)
    {
      len1++;
      s1++;
    }
  while(*s2 != 0)
    {
      len2++;
      s2++;
    }

  return len1 - len2;
  
}
