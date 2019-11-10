/* work in progress.
 @author: Hiromitsu Arai */
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

//debug + adjustments headers
#include <string.h> 
#include <stdio.h>
#include <errno.h>
//optional stuff, but remove any calls


#define __THRESHOLD__ 64 //padding for the actual data block.

//x86_64 has cache lines of 64 bytes.
//also adds compatibility for alignments.


static void *head = NULL;
static int ENDIANNESS = 1; //don't change. 1 for big. 0 for little

static void *tail = NULL;
static unsigned int heap_size = 0;


/* the if below: */
/* first it casts the char to int ptr to fully read the header as 4 bytes */
/* then it ignores the last 3 bytes and compares it to size. */

/* after the first boolean. it then checks to see if the last byte is set to 0. */
/* 0 would mean free, 1 would mean allocated. */

static void *find_loc(unsigned int size)
{
  char *h_f = (char*) head;
  char *t = (char*) tail;

  //printf("%d %p\n", *((int*)h_f),t);
  
  
  while(h_f != t)
    {
      if((((*((unsigned int*) h_f)) & (~7u)) >= 8+size) &&
	 ((*(h_f + (3*ENDIANNESS))&1) == 0))
	{
	  return (void*) h_f;
	}
      //printf("%p\t%p\n", h_f + *((int*)h_f), t);
      h_f += (*((int*) h_f)) & (~7u); //increment to get next header
    }
  return NULL;
}

//adhering to the same optimistic strategy described in $(info sbrk)
//first fit policy
extern void *s_malloc(unsigned int size)
{
  //printf("%p\n", tail);
  
  int *ret = (int*) find_loc(size);
  if(ret != NULL)
    {      
      *ret = *ret | 1;
      *(ret+size/4) = *ret;
      ret++;
  
      return (void*) ret;
    }
  //printf("%d\n%ld\n", len, sizeof(void*));

  unsigned int d_size = 0;
  while(d_size < size)
    {
      d_size += __THRESHOLD__;
    }

  d_size += 8;
  
  char *koubi = (char*) tail;
  if(heap_size - (tail-head) >= d_size)
    {
      *((int*)koubi) = d_size | 1;
      tail = koubi + d_size;
      *((int*) (tail-4)) = d_size | 1;
  
      return (void*)(koubi+4);
    }
  
  //printf("%d\n", d_size+8);
  //ret = sbrk(d_size + 8);
  //*((int*) ret) = (d_size+8) | 1;
  //*(ret + d_size/4) =  *ret;
  //ret++;  
  return NULL;
}

//should be the  very first call.

extern void init_heap(unsigned int max)
{
  if(head == NULL) //initialize
    {
      ENDIANNESS = 1-(((char) 1u) & *((char*) &ENDIANNESS));

      long mult = max / sysconf(_SC_PAGESIZE);
      mult = (1 + mult) * sysconf(_SC_PAGESIZE);
     
      const char c = 0;
      int fd = open("/tmp/myHeap.tmpfs", O_CREAT| O_RDWR, 0741);
      //printf("%d\n", fd);
      for(long i = 0; i < mult; i++)
        write(fd, &c, 1);

      head = mmap(NULL, mult, PROT_EXEC | PROT_READ	\
		  | PROT_WRITE, MAP_SHARED, fd, 0);
      
      if(errno != 0)
	{
	  perror(strerror(errno));
	  perror("in init_heap() of myHeap.c");
	}
      //remove("/tmp/myHeap.tmpfs");
      int *init = (int*) head;
      *init = 72;
      *(init+17) = 72;
      heap_size = max;
      tail = init + 18;
    }
}

int main()
{

  init_heap(1000);
  s_malloc(1);
  printf("%d\n", errno);
  int *ptr = (int*) s_malloc(70);
  int *ptr2 = (int*) s_malloc(100);
  printf("%d\n", *(ptr+16));
  for(int i = 0; i < 70; i++)
    {
      *(ptr+i)  = i;
    }
  for(int i = 0; i < 70; i++)
    {
      printf("%d\n", *(ptr+i));
    }

  s_malloc(70);
  perror(strerror(errno));
  return 0;
}
