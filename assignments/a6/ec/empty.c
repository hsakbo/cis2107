#include <stdio.h>

int main()
{
  FILE *fp = fopen("blank.ppm", "w+");
  fprintf(fp, "P6\n1366 768\n65535\n");
  for(unsigned long i = 0; i < 2098176ul; i++)
    fputc(0xFF, fp);
  return 0;

}
