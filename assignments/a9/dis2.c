#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMSIZE    1000       /* 1000 words of memory                       */
#define MAXLINE     100       /* maximum line characters                    */
/* SIM1 operation codes with format naaa where                  */
/* aaa is a 3-digit address and n is as follows:                */

#define HALT       0          /* halt processor                 */
#define LD         1          /* load accumulator instruction   */
#define ST         2          /* store accumulator instruction  */
#define ADD        3          /* add (to accumulator)           */
#define SUB        4          /* subtract (from accumulator)    */
#define LDA        5          /* load address                   */
#define JMP        6          /* jump (branch) to address       */
#define SKIPSET    7          /* skip instructions              */

/* SIM2 skip operation codes with format 7n0r where r is a general    */
/* register and n is as follows:                                      */

#define SKIP       0          /* unconditional skip                   */
#define SKEQ       1          /* skip if acc equals 0                 */
#define SKNE       2          /* skip if acc not equal to 0           */
#define SKGT       3          /* skip if acc greater than 0           */
#define SKGE       4          /* skip if acc greater or equal to  0   */
#define SKLT       5          /* skip if acc less than 0              */
#define SKLE       6          /* skip if acc less than or equal to 0  */


#define R0 0       /* accumulator, eax */
/* #define R1 1       /\* ebx *\/ */
/* #define R2 2       /\* ecx *\/ */
/* #define R3 3       /\* edx *\/ */
/* #define R4 4       /\* esi *\/ */
/* #define R5 5       /\* edi *\/ */
/* #define R6 6       /\* ebp *\/ */
/* #define R7 7       /\* esp *\/ */
/* #define R8 8       /\* elr *\/ */
/* #define R9 9       /\* eip *\/ */

int memory[MEMSIZE]; /* the ram */
int p_end; //a little optimization

void disas_main(int); 
char *var_gen();
char *l_gen();
int load();
void gen_symbols(int);
void disas_program(int);
void disas_data(int);
void gen_labels();
int uniqueL(int);
void handle_skip(int, char*);

//my symbol table
typedef struct sym_list
{
  int addr;
  char *name;
  struct sym_list *next;

}sym_list;

typedef struct l_list
{
  int addr;
  char *label;
  struct l_list *next;

}l_list;

sym_list *head;
l_list *headL;


int main()
{
  
  int max = load();
  gen_symbols(max);
  gen_labels();
  disas_main(max);
  return 0;
}

int uniqueL(int addr)
{
  if (headL == NULL)
    return 1;

  l_list *node = headL;
  while (node != NULL)
    {
      if (node->addr == addr)
	return 0;
      node = node->next;
    }
  return 1;
}

void gen_labels()
{

  l_list *node;
  
  for (int i = 0; i < p_end; i++)
    {
      int val = memory[i];
      int val1 = val / 1000;
      int val234 = val % 1000;

      if (val1 == JMP)
	{
	  if(headL == NULL)
	    {
	      headL = (l_list*) malloc(sizeof(l_list));
	      headL->addr = val234;
	      headL->label = l_gen();
	      headL->next = NULL;
	      node = headL;
	    }
	  if (uniqueL(val234))
	    {
	      l_list *temp = (l_list*) malloc(sizeof(l_list));
	      temp->addr = val234;
	      temp->label = l_gen();
	      temp->next = NULL;
	      node->next = temp;
	      node = temp;
	    }
	}
    }
  
}

//generates variable names. a,b,c..ba, bb, bc...baa etc
//Perhaps when I touch info theory I can find a good encoding
//to account for that offset. key to create: (27*26^n)
char *var_gen()
{
  static int b26_alpha = -1;
  b26_alpha++;
  int temp = b26_alpha;
  int size = 1;
  do
    {
      size++;
      temp /= 26;
    }while(temp > 0);
  
  char *ret =  malloc(size);
  ret += (size-1);
  *ret = 0;
     
  temp = b26_alpha;
  do
    {
      ret--;
      *ret = (temp % 26) + 0x61;
      temp /= 26;
    }while(temp > 0); 
  
  return ret;

}

void gen_symbols(int max)
{
  int val = 1;
  int addr = 0;
  while (val != 0)
    val = memory[addr++];

  p_end = addr;
  if (addr < max)
    {
      head = (sym_list*) malloc(sizeof(sym_list));
      head->addr = addr;
      head->name = var_gen();
      head->next = NULL;
      addr++;
    }
  
  sym_list *phead = head;
  while(addr < max)
    {
      sym_list *node = (sym_list*) malloc(sizeof(sym_list));
      node->addr = addr;
      node->name = var_gen();
      node->next = NULL;
      phead->next = node;
      phead = node;
      addr++;
    }

}

int load()
{
  
  int items;
  char line[MAXLINE];
  int addr, val;
  int max = 0;
  
  for (int i = 0; i < MEMSIZE; i++)
    memory[i] = 0;

  
  while (fgets(line, MAXLINE, stdin) > 0)
    {
      if (line[0] == '#')
  	continue;

      items = sscanf(line, "%d %d", &addr, &val);
      switch (items)
  	{
  	case 0:
	  printf("illegal input ignored\n");
	  continue;

	case 1:
	  if ((addr < 000) || (addr > 999))
	    {
	      printf("illegal starting address %d,  exiting\n", addr);
	      exit(1);
	    }
	  else
	    {
	      memory[max] = addr;
	      return max;
	     
	    }

	case 2:
	  if ((addr < 000) || (addr > 999))
	    {
	      printf("illegal starting address %d,  exiting\n", addr);
	      exit(1);
	    }
	  if ((val < 0000) || (val > 9999))
	    {
	      printf("illegal memory location %d, exiting\n", val);
	      exit(1);
	    }
	  memory[addr] = val;
	  max++;
	  
  	}

    }
  perror("something went horribly wrong!");
  exit(1);
}


char *l_gen()
{
  static int index = 0;
  index++;

  int digits = 0;
  int temp = index;
  while(temp != 0)
    {
      temp /= 10;
      digits++;
    }

  char *ret = malloc(digits+2);
  sprintf(ret, "L%d", index);
  return ret;

}

void handle_skip(int val, char *label)
{
  int det = val / 100;
  switch (det)
    {
    case SKIP:
      printf(" %s\t\tskip\n", label);
      return;
      
    case SKEQ:
      printf(" %s\t\tskeq, %%eax\n", label);
      return;
      
    case SKNE:
      printf(" %s\t\tskne, %%eax\n", label);
      return;
      
    case SKGT:
      printf(" %s\t\tskgt, %%eax\n", label);
      return;

    case SKGE:
      printf(" %s\t\tskne, %%eax\n", label);
      return;

    case SKLT:
      printf(" %s\t\tsklt, %%eax\n", label);
      return;

    case SKLE:
      printf(" %s\t\tskle, %%eax\n", label);
      return;
    }
}

void disas_program(int addr)
{
  int val = memory[addr];
  int val1 = val / 1000;
  int val234 = val % 1000;

  if (addr != 0)
    printf("%03d %04d", addr, val);

  else
    printf("%03d %04d start:", addr, val);

  char *name = NULL;
  if (val234 >= p_end)
    {
      sym_list *node = head;
      
      while (node != NULL)
	{
	  if (node->addr == val234)
	    {
	      name = node->name;
	      break;
	    }	  
	  node = node->next;
	}
    }

  char *label = NULL;
  l_list *pHeadL = headL;
  while(pHeadL != NULL)
    {
      if (pHeadL->addr == addr)
	{
	  label = pHeadL->label;
	  break;
	}
      pHeadL = pHeadL->next;
    }

  if(name == NULL)
    {
      char arr[4];
      sprintf(arr, "%d", val234);
      name = arr;
    }
  if(label == NULL)
    label = "";
  
  switch (val1)
    {
    case HALT:
      printf(" %s\t\thalt\n", label);
      return;

    case LD:
      printf(" %s\t\tld, %s\n", label, name);
      return;

    case ST:
      printf(" %s\t\tst, %s\n", label, name);
      return;

    case ADD:
      printf(" %s\t\tadd, %s\n", label, name);
      return;
      
    case SUB:
      printf(" %s\t\tsub, %s\n", label, name);
      return;

    case LDA:
      printf(" %s\t\tlda, %d\n", label, val234);
      return;

    case SKIPSET:
      handle_skip(val234, label);
      return;

    case JMP:
      pHeadL = headL;
      char *loc;
      while (pHeadL != NULL)
	{
	  if (pHeadL->addr == val234)
	    {
	      loc = pHeadL->label;
	      break;
	    }
	  pHeadL = pHeadL->next;
	}
      if (label == NULL)
	printf("\t\tjmp, %s\n", loc);
      else
	printf(" %s\t\tjmp, %s\n", label, loc);
      return;
      
    default:
      perror("panic exit, encountered broken stuff\n");
      exit(1);
    }

}

void disas_data(int max)
{

  sym_list *node = head;
  for (int i = p_end; i < max; i++)
    {
      printf("%03d %04d %s\t.word\n", i, memory[i], node->name);
      node = node->next;
    }
  printf("%03d\t\tend\n", memory[max]);

}

void disas_main(int max)
{
  for (int i = 0; i < p_end; i++)
    disas_program(i);

  disas_data(max);
}
