#ifndef __HEAP_MASTER__
#define __HEAP_MASTER__

#ifdef __linux__  //heap stuff
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


extern int strmod(char *s1, char *s2);
/* this is the one I said I would overengineer the diff. */
/* turns out I don't have to apparently because I did not understand the q. */
/* however this is an advanced palindrome running O(n*logn) time */


extern int all_letters(char *);
extern int num_in_range(char *, char, char);
extern int diff(char *, char *);
extern void shorten(char *, int);
extern int len_diff(char *, char*);
extern void rm_left_space(char *);
extern void rm_right_space(char *);
extern void rm_space(char *);
extern int find(char *, char *);
extern char *ptr_to(char *, char *);
extern int is_empty(char *);
extern char *dedup(char *);
extern char *pad(char *, int);
extern int ends_with_ignore_case(char *, char *);
extern char *repeat(char *, int, char);
extern char *replace(char *, char *, char *);
extern char *str_connect(char **, int, char);
extern void rm_empties(char **);
extern char **str_chop_all(char *, char);

#endif
