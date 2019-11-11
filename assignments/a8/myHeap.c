/* work in progress.
 * a lot of redundancies in here, but this implementation
 * is for educational purposes.
 @author: Hiromitsu Arai */

/* TODO list: mprotect header and footer tags. */
/* mprotect needs memory alignment. */
/* which means a power of 2 and multiple of size(void*) */
/* this goes along with fixing all ints to longs */

#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h> 
#include <stdio.h>


//put inside paranthesis.
#define __THRESHOLD__ (64) //padding for the actual data block.  //it however can be larger than a multiple of threshold
//because of spliting and coalescing.

//x86_64 has cache lines of 64 bytes.
//also adds compatibility for alignments.


static void *head = NULL;
static int ENDIANNESS = 1; //do not change. 1 for big. 0 for little

static void *tail = NULL;
static unsigned int heap_size = 0;



static void *splitter(char *ptr, unsigned int d_size)
{
  int b_size = *((int*)ptr);
  
  if(b_size - d_size >= __THRESHOLD__ + 8)
    {
      char *next = d_size + ptr;
      *((int*) ptr) = d_size | 1;
      *((int*) (next - 4)) = d_size | 1;
      *((int*) next) = b_size - d_size;
      next = next + *((int*) next) - 4;
      *((int*) next) = b_size - d_size;
    }
  else
    {
      *((int*) (ptr+b_size-4)) = b_size | 1;
      *((int*) ptr) = b_size | 1;
    }
  return (void*)(ptr+4);
}



static void *find_loc(unsigned int size)
{
  char *h_f = (char*) head;
  char *t = (char*) tail;
  
  /* the if below: */
  /* first it casts the char to int ptr to fully read the header as 4 bytes */
  /* then it ignores the last 3 bytes and compares it to size. */
  
  /* after the first boolean. it then checks to see if the last byte is set to 0. */
  /* 0 would mean free, 1 would mean allocated. */

  while(h_f != t)
    {
      if( (((*((unsigned int*) h_f)) & (~7u)) >= size) \
	  && ((*(h_f + 3*ENDIANNESS) & 1) == 0))
	{
	  return (void*) h_f;
	}
      h_f += (*((int*) h_f)) & (~7u); //increment to get next header
    }
  return NULL;
}

//adhering to the same optimistic strategy described in $(info sbrk)
//first fit policy
extern void *s_malloc(unsigned int size)
{
  unsigned int d_size = 0;
  while(d_size < size)
    {
      d_size += __THRESHOLD__;
    }

  d_size += 8;
  
  int *ret = (int*) find_loc(d_size);

  if(ret != NULL)
    return splitter(ret, d_size);
      
  char *koubi = (char*) tail;
  if(heap_size - (tail-head) >= d_size)
    {
      *((int*)koubi) = d_size | 1;
      tail = koubi + d_size;
      *((int*) (tail) -1) = d_size | 1;

      return (void*)(koubi+4);
    }
  
  return NULL;
}


extern void s_free(void *addr)
{
  
  enum states{NONE=0, CO_UP, CO_DOWN, CO_UPDOWN};
  int state = NONE;

  char *mid = (char*) addr;
  mid -= 4;

  //could essentially oneline these, but its easy to read.
  unsigned int delta_up = 0;
  unsigned int delta_mid = *((int*)mid) & (~7u);
  unsigned int delta_down = 0;
    
  char *upper = NULL;
  
  char *lower = mid + delta_mid;

  int *int_u = NULL;
  int *int_m = (int*) mid;
  int *int_l = (int*) lower;
  
  if(mid > head)
    {
      delta_up = *((int*) (mid-4)) & (~7u);
      upper = (char*) (mid - delta_up);
      int_u = (int*) upper;
      if(!(*int_u & 1))
	state = CO_UP;
    }

  char *end_tag = NULL;
  if(lower < tail && !(*int_l & 1))
    {
      state += 2;
      delta_down = *int_l & (~7u);
      end_tag = lower + *int_l - 4;
    }
  
  
  switch(state)
    {      
    case NONE:
      *int_m = *int_m & (~(7u));
      *(int_l - 1) = *int_m;
      break;

    case CO_UP:      
      *int_m = 0; //to make my life easier debugging
      *(int_m - 1) = 0;
      *int_u = delta_up + delta_mid;
      *(int_l - 1) = delta_up + delta_mid;
      break;

    case CO_DOWN:
      *int_m =  delta_mid + delta_down;
      *((int*) end_tag) = *int_m;
      *int_l = 0;
      *(int_l - 1) = 0;
      break;

    case CO_UPDOWN:
      *int_u = delta_up + delta_mid + delta_down;
      *((int*) end_tag) = *int_u;
      *int_m = 0;
      *(int_m - 1) = 0;
      *int_l = 0;
      *(int_l - 1) = 0;
      break;
    }

}
extern void kaijo()
{
  if(head != NULL)
    {
      long mult = heap_size / sysconf(_SC_PAGESIZE);
      mult = (1 + mult) * sysconf(_SC_PAGESIZE);
      munmap(head, mult);
      head = NULL;
      tail = NULL;
      heap_size = 0;
    }
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
      int fd = open("/tmp/myHeap.tmpfs", O_CREAT| O_RDWR, 0744);
      
      for(long i = 0; i < mult; i++)
        write(fd, &c, 1);

      head = mmap(NULL, mult, PROT_EXEC | PROT_READ	\
		  | PROT_WRITE, MAP_SHARED, fd, 0);
      
      if(errno != 0)
	{
	  perror(strerror(errno));
	  perror("in init_heap() of myHeap.c");
	}
      remove("/tmp/myHeap.tmpfs");
      int *init = (int*) head;
      *init = __THRESHOLD__ + 8;
      int macro_safety = __THRESHOLD__ / 4 + 1;
      *(init+macro_safety) = 72;
      heap_size = max;
      tail = init + macro_safety + 1;      
    }
}


/*
int main()
{

  init_heap(7000);
  void* something = s_malloc(1);
  //printf("%d\n", errno);
  int *ptr = (int*) s_malloc(70);
  int *ptr2 = (int*) s_malloc(100);
  void *null = s_malloc(5000);

  for(int i = 0; i < 100; i++)
    s_malloc(70);

  
  s_free(something);
  s_free(ptr);
  s_free(ptr2);
  s_free(null);
  
  s_malloc(50);
  int *h = head;
  for(int i = 0; i < 400; i+=6)
    printf("%d\t%d\t%d\t%d\t%d\t%d\n", *(h+i), *(h+1+i), *(h+2+i), *(h+3+i), *(h+4+i), *(h+5+i));
  perror(strerror(errno));
  kaijo();
  return 0;
}

*/
