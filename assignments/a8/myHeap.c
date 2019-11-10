#include <unistd.h>
#include <stdio.h>
#define __THRESHOLD__ 64 //padding for the actual data block.
//x86_64 has cache lines of 64 bytes.
//adds compatibility for alignment.


static void *head = NULL;
static int ENDIANNESS = 1; //don't change. 1 for big. 0 for little


/* the if below: */
/* first it casts the char to int ptr to fully read the header as 4 bytes */
/* then it ignores the last 3 bytes and compares it to size. */

/* after the first boolean. it then checks to see if the last byte is set to 0. */
/* 0 would mean free, 1 would mean allocated. */
static void *find_loc(int size)
{
  char *h_f = (char*) head;
  char *tail = (char*) (sbrk(0));
  while(h_f != tail)
    {
      if((((*((int*) h_f)) & (~7u))   >=   size) &&
	 (*(h_f + (3*ENDIANNESS))&1) == 0)
	{
	  return (void*) h_f;
	}
      
      h_f += (*((int*) h_f)) & (~7u); //increment to get next header
    }
  return NULL;
}

//adhering to the same optimistic strategy described in $(info sbrk)
extern void *s_malloc(int size)
{
  
  if(head == NULL) //initialize
    {
      ENDIANNESS = (((char) 1u) & *((char*) &ENDIANNESS))^1;
      head = sbrk(__THRESHOLD__ + 8);
      int *init = (int*) head;
      *init = 72;
      *(init+17) = 72;
    }
 
  void *ret = find_loc(size);
  if(ret != NULL)
    {
      *ret = *ret | 1;
      return ret;
    }
  //printf("%d\n%ld\n", len, sizeof(void*));

  int d_size = 0;
  while(d_size >= size)
    {
      d_size += __THRESHOLD__;
    }

  ret = sbrk(d_size);
  
}

int main()
{
  //s_malloc(1);
  
  int *ptr = sbrk(4);
  *ptr = 4;
  char *d = (char*) ptr;
  printf("%d %d\n", *d, sizeof(size_t));
  return 0;
}
