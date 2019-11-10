
extern void take_last(char *s1, int n)
{
  int len = 0;
  while(*s1 != 0) {s1++; len++;} //why waste lines.

  if(n >= len)
    return;

  s1 -= len;
  for(int i = 0; i <= n; i++)
    {
      *s1 = *(s1+len-n);
      s1++;
    }
  
}
