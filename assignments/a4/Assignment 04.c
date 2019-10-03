#include <stdio.h>
#include <stdint.h>

/*

Note

Remember, that in your program, you should not assume anything about the number of bytes used by integers. Use the sizeof operator when necessary.*/

/* weatherlog_t is a "weather sensor log type"
   which is really defined as a 64-bit unsigned
   integer.  See below. */
typedef uint64_t weatherlog_t;

unsigned int add(unsigned int, unsigned int);
unsigned int sub(unsigned int, unsigned int);
unsigned int mul(unsigned int, unsigned int);

void print_half_nybbles(unsigned int);
unsigned int reverse_half_nybbles(unsigned int);

int has_odd(unsigned int);
unsigned int make_odd(unsigned int);

int is_negative(int);

weatherlog_t pack_log_entry(unsigned int, unsigned int, unsigned int, 
			    unsigned int,
			    int, int, 
			    unsigned int, unsigned int);

unsigned int get_year(weatherlog_t entry);
unsigned int get_month(weatherlog_t entry);
unsigned int get_day(weatherlog_t entry);
unsigned int get_zip(weatherlog_t entry);
unsigned int get_high(weatherlog_t entry);
unsigned int get_low(weatherlog_t entry);
unsigned int get_precip(weatherlog_t entry);
unsigned int get_wind(weatherlog_t entry);

int main(int argc, char **argv) 
{
  unsigned int i, j;
  int x, y;
  unsigned int year, month, day, 
    zip, high_temp, low_temp, precip, avg_wind_speed;
  weatherlog_t log_entry;


  
  printf("Enter an integer: ");
  scanf("%u", &i);
  printf("Enter another integer: ");
  scanf("%u", &j);
  printf("One more integer, please: ");
  scanf("%d", &x);
  printf("Please enter a positive integer: ");
  scanf("%d", &y);

  printf("i + j = %u\n", add(i,j));
  printf("i - j = %u\n", sub(i,j));
  printf("i * j = %u\n", mul(i,j));

  if (is_negative(x))
    printf("%d is negative\n", x);
  else
    printf("%d is non-negative\n", x);

  if (has_odd(y)) 
  {
    printf("%x has an odd number of bits in its binary representation\n", y);
  }
  else 
  {
    printf("%x has an even number of bits in its binary representation\n", y);
    printf("but %x has an odd number of bits in its binary representation\n", make_odd(y));
  }

  printf("The half-nybbles of %d (in hex 0x%x) are:", x, x);
  print_half_nybbles(x);
  
  printf("%x with reversed half-nybbles is %x\n", x, reverse_half_nybbles(x));

  
  printf("Enter a year: ");
  scanf("%u", &year);
  
  printf("Enter a month as an integer (1-12): ");
  scanf("%u", &month);
  
  printf("Enter a day as an integer (1-31): ");
  scanf("%u", &day);

  
  printf("Enter a zip code as an integer (0-99999), EDIT: the range should be 0-65535 as this is stored only in 16 bits: ");
  scanf("%u", &zip);

  printf("Enter a temperature as an integer: ");
  scanf("%u", &high_temp);

  printf("Enter another temperature as an integer: ");
  scanf("%u", &low_temp);


  printf("Enter rainfall amount as an integer (mm): ");
  scanf("%u", &precip);

  printf("Enter a as an integer (km/hr): ");
  scanf("%u", &avg_wind_speed);


  log_entry=pack_log_entry(year, month, day, zip, high_temp, low_temp,
			   precip, avg_wind_speed);
  printf("You entered: %u/%u/%u for zip %5d: high %d F, low %d F, precip %d mm, wind speed %d km/hr\n", 
	 get_day(log_entry), get_month(log_entry), get_year(log_entry),
	 get_zip(log_entry), get_high(log_entry), get_low(log_entry),
	 get_precip(log_entry), get_wind(log_entry));
  return 0;
}




//no worries professor, just add 10 more lines to the optimal 7 and mine is perfect too xD

//implementation: I first add i and j with XOR gate, then I handle the carrying bit if it is 1. The way I know to find a carryng 1 is by an AND gate.

//i and j are destroyed by bit-shifting to the right, as I use (var)&1 for each to determine the very last position's number. I also keep track of the position by bitshifting a 1 through each iteration of my loop. This pos variable is the key in setting up the return value called 'ret'.

/*
unsigned int my_first_add(unsigned int i, unsigned int j) 
{


  /* can be done in a total of 7 lines, including one to declare an unsigned int, */
  /* two for a while loop, and one for the return
     You're not required to do it in 7 lines though . 

  
  unsigned int ret = 0;

  //these 2 don't necessarily have to be unsigned.
  int carry = 0; 
  int pos = 1;  

  //note: I haven't tested this thing on edge cases. In other words, I am unsure of the behavior of overflow)
  while(i != 0 || j != 0 || carry != 0)
    {
      if((i&1) ^ (j&1))
	ret = ret|pos;

      if(carry == 1 && (ret&pos) == 0)
	{
	  carry = 0;
	  ret = ret|pos;
	}
      if(carry == 1 && (ret&pos) == pos)  
	  ret = ret&(~pos);
	

      if((i&1) && (j&1))
	carry = 1;

      i = i>>1;
      j = j>>1;
      pos = pos<<1;
      
    }	
      
  return ret;
}
*/


//only took a few hours to arrive to this conclusion, 2 lines
unsigned int add(unsigned int i, unsigned int j)
{
  //I've seen these if statements in the linux community.
  if(!(i&j))   return i^j;  
  
  return add(i^j, (i&j)<<1);
}


  //although I never got help from the internet while completing this, I am ever so glad that I don't have a life and read wikipedia when I am bored/curious.
  //took me about 5 minutes to figure it out.
  //please explain how it works... I only got it empirically changing stuff here and there.

  //hah! I beat the 8-line man. although, the add function has 17 lines..

unsigned int sub(unsigned int i, unsigned int j) 
{ 
  return ~add(~i, j);
}



//7 lines, beat that prof!! (without counting those brackets)
unsigned int mul(unsigned int i, unsigned int j) 
{
  /* can be done in a total of 8 lines including one to declare unsigned ints */
  /* two for a for loop, and one for the return */

  unsigned int ret = 0;
  unsigned int count = 0;
  
  for(int k = j; k > 0; k = k>>1)
    {
      if(k&1)
	ret = add(i<<count, ret);

      count = add(count, 1);
    }

  return ret;
}

/* prints the half-nybbles (i.e. 2 bit values) of x,
   one half-nybble at a time */
void print_half_nybbles(unsigned int x) 
{
  unsigned int first = ~0; //~(~0 >> 1);
  first = first >> 1;
  first = ~first;
  unsigned int second = first>>1;
  for(int i = 0; i < mul(sizeof(int), 8); i=add(i, 2))
    {
      if(x&first)
	printf("1");
      else
	printf("0");

      if(x&second)
	printf("1");
      else
	printf("0");

      printf(" ");
      first = first >> 2;
      second= second >> 2;
    }
  printf("\n");
}

/* returns the reverse of the half-nybbles of i */
unsigned int reverse_half_nybbles(unsigned int i) 
{  

  unsigned int ret = 0;
  for(int j = 0; j < mul(sizeof(int), 8); j=add(j, 2))
    {            

      ret = ret << 2;
      ret = ret|(i&3);      
      i = i>>2;
    }
  
  return ret;
}

/* returns 1 if x < 0
   returns 0 otherwise

   Do not use the <, > operators. */
int is_negative(int x) 
{
  unsigned int comp = ~0;
  comp = ~(comp >> 1);

  if(x&comp)
    return 1;
  
  return 0;
}

/* returns 1 if x's binary representation
   has an odd number of 1s or 0 otherwise */
int has_odd(unsigned int x) 
{
  int ones = 0;
  //only need to check either 0s or 1s, the other follows
  print_half_nybbles(x);
  for(int i = 0; i < mul(sizeof(int), 8); i=add(i, 1))
    {
      if(x&1)
	ones = add(ones, 1);      	
      x = x>>1;
    }

  if(ones&1)
    return 1;
  
  return 0;
}

/* If x's binary representation contains an odd number of 1s, x is
   returned. Otherwise, it returns a copy of x, but with its most significant
   bit modified so that there is an odd number of 1s. */
unsigned int make_odd(unsigned int x) 
{
  unsigned int sig = ~0;
  sig = ~(sig>>1);
  if(!has_odd(x))
    {
      if((x&sig) == sig)
	{
	  x = x<<1;
	  x = x>>1;
	}
      else
	return x|sig;
    }
  
  return x;
}


/* combines all of the arguments into a single weatherlog_t entry as described below */
weatherlog_t pack_log_entry(unsigned int year, unsigned int month, unsigned int day, 
			    unsigned int zip, int high_temp, int low_temp,
			    unsigned int precip, unsigned int avg_wind_speed) 
{

  //is this the most efficient method? it looks cool
  
  weatherlog_t ret = 0;

  //year -6bits
  ret = ret|(year&63);

  //month-4bits
  ret = ret<<4;
  ret = ret|(month&15);

  //date -5bits
  ret = ret<<5;
  ret = ret|(day&31);

  //zip code -16bits
  ret = ret << 16;
  ret = ret|(zip&65535);

  //high temp -8bits
  ret = ret << 8;
  ret = ret|(high_temp&255);

  //low temp -8bits
  ret = ret << 8;
  ret = ret|(low_temp&255);

  //precipitation -10bits
  ret = ret<<10;
  ret = ret|(precip&1023);

  //wind speed -7bits
  ret = ret<<7;
  ret = ret|(avg_wind_speed&127);
  
  return ret;
  
}

//I'm still going to return 64 bits but I think it gets truncated to unsigned int
unsigned int get_year(weatherlog_t entry) 
{   
  return entry>>58;
}

unsigned int get_month(weatherlog_t entry) 
{
  entry = entry<<6;
  return entry>>60;
}

unsigned int get_day(weatherlog_t entry) 
{
  entry = entry<<10;
  return entry>>59;
}

unsigned int get_zip(weatherlog_t entry) 
{
  entry = entry<<15;
  return entry>>48;
}

unsigned int get_high(weatherlog_t entry)
{
  entry = entry<<31;
  return entry>>56;
}

unsigned int get_low(weatherlog_t entry) 
{
  entry = entry<<39;
  return entry>>56;
}

unsigned int get_precip(weatherlog_t entry) 
{
  entry = entry<<47;
  return entry>>54;
}

unsigned int get_wind(weatherlog_t entry) 
{
  entry = entry<<57;
  return entry>>57;
}

/* * weatherlog_t  */

/* A particular weather sensor called the WeatherJuicer 2000 TM stores a */
/* log entry each day, representing weather activity from the */
/* previous 24 hours. Each entry includes a: */

/* - year :: 6 bits -- stored as the number of years since the */
/*           year 2000. */
/* - month :: 4 bits */
/* - day :: 5 bits */
/* - zip_code :: 16 bits */
/* - high_temp :: in degrees Fahrenheit, stored as an 8-bit signed integer */
/* - low_temp :: in degrees Fahrenheit, stored as 8-bit signed integer */
/* - precipitation :: in mm. stored as a 10-bit unsigned integer. */
/* - average_wind_speed :: 7 bits. unsigned int km/hr. */

/* All of these are packed into a 64 bit unsigned integer in the above order. */

/* For example, if on September 16, 2015, on Temple's main campus, which */
/* is in zip code 19122, we have 15 mm of rain, a high temperature of 85 */
/* degrees, a low temperature of 65 degrees, and an average wind speed of */
/* 5 km/hour. */

/* We'd store: */
/* - year :: 2015, which is 15 years from 2000, so 001111 */
/* - month :: September, which is the 9th month, so 1001. */
/* - day :: 16, which is 1 0000 */
/* - zip_code :: 19122 which is 0100 1010 1011 0010 */
/* - high_temp :: 85F, so 0101 0101 */
/* - low_temp :: 65F, so 0100 0001 */
/* - precipitation :: 35 mm so 00 0010 0011 */
/* - average wind speed :: 5 km/h, so 000 0101 */

/* And all would be packed into a single 64-bit unsigned integer: */

/* 00 1111 1001 10000 0100 1010 1011 0010 0101 0101 0100 0001 00 0010 0011 000 0101 */

/* OR */

/* 0011 1110 0110 0000 1001 0101 0110 0100 1010 1010 1000 0010 0001 0001 1000 0101 */

/* OR */

/* 0x3e609564aa821185 */


/* We define this weather log as its own datatype called weatherlog_t, which */
/* under the covers is really a 64-bit unsigned int. This is done in the line: */

/* typedef uint64_t weatherlog_t; */
