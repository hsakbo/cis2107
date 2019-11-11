#ifndef __HEAP_MASTER__
#define __HEAP_MASTER__


extern void init_heap(unsigned int);
/* to initialize the heap. pass an int, this will be the */
/*   maximum size of the entire heap. The size of the heap depends */
/*   on the page size. it will allocate it to the nearest multiple. */
/* a temporary file will be created in /tmp which will get deleted */


extern void kaijo();
/* remove initialization. you can re-initialize the heap */


extern void s_free(void *addr);
/* free's a memory block and coalesces it */

extern void *s_malloc(unsigned int size);
/* allocates memory. will be padded according to the __THRESHOLD__ macro */


#endif
