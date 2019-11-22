#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMSIZE    1000       /* 1000 words of memory                       */
#define MAXCNT      100       /* limit execution of 100 instructions        */
#define MAXLINE     100       /* maximum line characters                    */
/* SIM1 operation codes with format naaa where                  */
/* aaa is a 3-digit address and n is as follows:                */

#define HALT       0          /* halt processor                 */
#define LD         1          /* load accumulator instruction   */
#define ST         2          /* store accumulator instruction  */
#define ADD        3          /* add (to accumulator)           */
#define SUB        4          /* subtract (from accumulator)    */
#define LDA        5          /* load address                   */


int memory[MEMSIZE]; /* the ram */
int p_end; //a little optimization

void disas_main(int); 
char *var_gen();
int load();
void gen_symbols(int);
void disas_program(int);
void disas_data(int);

//my symbol table
typedef struct sym_list
{
  int addr;
  char *name;
  struct sym_list *next;

}sym_list;

sym_list *head;



int main()
{
  
  int max = load();
  gen_symbols(max);
  disas_main(max);
    
  
  return 0;

}

//generates variable names. a,b,c..ba, bb, bc...baa etc
//Perhaps when I touch info theory I can find a good encoding
//to account for that offset. key: (27*26^n)
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

  
  
  switch (val1)
    {
    case HALT:
      if (name == NULL)
	printf("\thalt\n");
      else
	printf("\thalt\n");
      return;

    case LD:
      if (name == NULL)
	printf("\tld, %d\n", val234);
      else
	printf("\tld, %s\n", name);
      return;

    case ST:
      if (name == NULL)
	printf("\tst, %d\n", val234);
      else
	printf("\tst, %s\n", name);
      return;

    case ADD:
      if (name == NULL)
	printf("\tadd, %d\n", val234);
      else
	printf("\tadd, %s\n", name);
      return;
      
    case SUB:
      if (name == NULL)
	printf("\tsub, %d\n", val234);
      else
	printf("\tsub, %s\n", name);
      return;

    case LDA:
      printf("\tlda, %d\n", val234);
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
