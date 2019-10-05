#include <stdio.h>
#include <stdbool.h>

void swap(int *a, int *b)
{
  *a^=*b; // a = a xor b
  *b^=*a;
  *a^=*b;
}

bool is_odd(int x)
{
  return x&1; //the statements could be in binary
}

int div_by_8(int x)
{
  return x & 7 == 0;
}

int not(int a)
{
  return ~a;
}

int main()
{
  int prod = 200*300*400*500;
  printf("prod = %d\n", prod);

  prod = (200) * (300*400*500);
  printf("prod = %d\n", prod);

  prod = (200*300*400) * 500;
  printf("prod = %d\n", prod);

  printf("%d\n", sizeof(void*));

  printf("%d\n", not(1));
  
  return 0;

  //x is hex
}
