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
#define ONEREG     8          /* accumulator instructions       */
#define TWOREG     9          /* two register instructions      */


/* SIM2 skip operation codes with format 7n0r where r is a general    */
/* register and n is as follows:                                      */

#define SKIP       0          /* unconditional skip                   */
#define SKEQ       1          /* skip if acc equals 0                 */
#define SKNE       2          /* skip if acc not equal to 0           */
#define SKGT       3          /* skip if acc greater than 0           */
#define SKGE       4          /* skip if acc greater or equal to  0   */
#define SKLT       5          /* skip if acc less than 0              */
#define SKLE       6          /* skip if acc less than or equal to 0  */

/* One register operation codes (format 8n0r, where r is a general    */
/* register (%r0 to %r9) and n is as follows:                         */
#define IN         0          /* input a 4-digit number into %r       */
#define OUT        1          /* output the 4-digit number from %r    */
#define CLR        2          /* clear register r (%r = 0)            */
#define INC        3          /* increment (add 1) to %r (%r++)       */
#define DEC        4          /* decrement (subtract 1) from %r       */
#define NEG        5          /* negate %rn (%r = -%r)                */
#define SHFTL      6          /* shift %r left (%r=%r*10)             */
#define SHFTR      7          /* shift %r right (%r=%r/10)            */
                              /* return is (pop %r9)                  */

/* Two register operation codes %r0 to %r9 (%r0=acc,%r7=sp,%r8=lk,%r9=ip)  */
/* with format 9nsd, where:                                                */
                              /* s is the first (source) general register  */
                              /* d is the second (destination) register    */
                              /* n is as follows                           */
#define MVRR       0          /* load from register, Rs => Rd              */
#define MVMR       1          /* load using reg addr, memory(Rs) => Rd     */
#define MVRM       2          /* store using reg adr, Rs => memory(Rd)     */
#define EXCH       3          /* exchange values in Rs and Rd, Rs <=> Rd   */
#define ADDR       4          /* add register, Rs + Rd => Rd               */
#define SUBR       5          /* subtract register, Rd - Rs => Rd          */


int memory[MEMSIZE]; /* the ram */
int p_end; //a little optimization


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


void disas_main(int); 
char *var_gen();
char *l_gen();
int load();
void gen_symbols(int);
int disas_program(int);
sym_list *disas_data(sym_list *);
void gen_labels();
int uniqueL(int);
void handle_skip(int, char*);
void handle_1reg(int, char*);
void handle_2reg(int, char*);
void free_names();
void free_labels();



int main()
{
  
  int max = load();
  gen_symbols(max);
  gen_labels(max);
  disas_main(max);
  free_names();
  free_labels();
  return 0;
}

void free_names()
{
  sym_list *node = head;
  sym_list *temp;
  while(node != NULL)
    {
      temp = node;
      node = node->next;
      free(temp->name);
      free(temp);
    }

}

void free_labels()
{
  l_list *node = headL;
  l_list *temp;
  while(node != NULL)
    {
      temp = node;
      node = node->next;
      free(temp->label);
      free(temp);
    }

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

void gen_labels(int max)
{

  l_list *node;
  
  for (int i = 0; i < max; i++)
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
  if ((addr < max) && ((memory[addr] / 1000) == 0))
    {
      head = (sym_list*) malloc(sizeof(sym_list));
      head->addr = addr;
      head->name = var_gen();
      head->next = NULL;
      addr++;
    }
  
  sym_list *phead = head;
  while ((addr < max) && ((memory[addr] / 1000) == 0))
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

  char *ret = malloc(digits+3);
  sprintf(ret, "L%d", index);
  return ret;

}

void handle_skip(int val, char *label)
{
  int det = val / 100;
  int r = val % 10;
  
  switch (det)
    {
    case SKIP:
      printf("%-6sskip\n", label);
      return;
      
    case SKEQ:
      printf("%-6sskeq, %%r%d\n", label, r);
      return;
      
    case SKNE:
      printf("%-6sskne, %%r%d\n", label, r);
      return;
      
    case SKGT:
      printf("%-6sskgt, %%r%d\n", label, r);
      return;

    case SKGE:
      printf("%-6sskne, %%r%d\n", label, r);
      return;

    case SKLT:
      printf("%-6ssklt, %%r%d\n", label, r);
      return;

    case SKLE:
      printf("%-6sskle, %%r%d\n", label, r);
      return;
    }

 
}

void handle_1reg(int val234, char *label)
{
  int det = val234 / 100;
  int r = val234 % 10;
  

  switch (det)
    {
    case IN:
      printf("%-6sin, %%r%d\n", label, r);
      return;

    case OUT:
      printf("%-6sout, %%r%d\n", label, r);
      return;

    case CLR:
      printf("%-6sclr, %%r%d\n", label, r);
      return;

    case INC:
      printf("%-6sinc, %%r%d\n", label, r);
      return;

    case DEC:
      printf("%-6sdec, %%r%d\n", label, r);
      return;

    case NEG:
      printf("%-6sneg, %%r%d\n", label, r);
      return;

    case SHFTL:
      printf("%-6sshftl, %%r%d\n", label, r);
      return;

    case SHFTR:
      printf("%-6shftr, %%r%d\n", label, r);
      return;
    }
}

void handle_2reg(int val234, char *label)
{
  int reg_s = (val234 % 100) / 10;
  int reg_d = val234 % 10;
  int det = val234 / 100;

  switch (det)
    {
    case MVRR:
      printf("%-6smvrr  %%r%d, %%r%d\n", label, reg_s, reg_d);
      return;

    case MVMR:
      printf("%-6smvmr  %%r%d, %%r%d\n", label, reg_s, reg_d);
      return;

    case MVRM:
      printf("%-6smvrm  %%r%d, %%r%d\n", label, reg_s, reg_d);
      return;

    case EXCH:
      printf("%-6sexch  %%r%d, %%r%d\n", label, reg_s, reg_d);
      return;

    case ADDR:
      printf("%-6saddr  %%r%d, %%r%d\n", label, reg_s, reg_d);
      return;

    case SUBR:
      printf("%-6ssubr  %%r%d, %%r%d\n", label, reg_s, reg_d);
      return;
    }

}

int disas_program(int addr)
{

  static int counter = 0;
  counter++;
  int val = memory[addr];
  int val1 = val / 1000;
  int val234 = val % 1000;

  if (counter != 1)
    printf("%03d %04d       ", addr, val);

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
      printf("%-6shalt\n", label);
      return val1;

    case LD:
      printf("%-6sld  %s, %%r0\n", label, name);
      return val1;

    case ST:
      printf("%-6sst  %s, %%r0\n", label, name);
      return val1;

    case ADD:
      printf("%-6sadd %s, %%r0\n", label, name);
      return val1;
      
    case SUB:
      printf("%-6ssub %s, %%r0\n", label, name);
      return val1;

    case LDA:
      printf("%-6slda, %d\n", label, val234);
      return val1;

    case SKIPSET:
      handle_skip(val234, label);
      return val1;

    case ONEREG:
      handle_1reg(val234, label);
      return val1;

    case TWOREG:
      handle_2reg(val234, label);
      return val1;
      
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
	printf("         jmp, %s\n", loc);
      else
	printf("%-6sjmp, %s\n", label, loc);
      return val1;
      
    default:
      perror("panic exit, encountered broken stuff\n");
      exit(1);
    }
  
  return val1;
}

sym_list *disas_data(sym_list *node)
{
  int addr = node->addr;
  printf("%03d %04d %-6s.word\n", addr, memory[addr], node->name);
  return node->next;
}

void disas_main(int max)
{
  int i;
  for (i = 0; i < p_end ; i++)
    disas_program(i);

  sym_list *node = head;
  for (; i < max; i++)
    {
      if((memory[i] / 1000))
	disas_program(i);

      else
	node = disas_data(node);	  
    }  
  printf("%03d\t\tend\n", memory[max]);  
}
