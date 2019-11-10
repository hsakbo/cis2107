
//I am gonna enforce a policy to ensure the best use of this function.
//since I can't exactly create a non-static array of chars and hope the memory
//does not change after the function is off the stack, I will use the 3rd parameter
//this parameter is a char array with enough memory for the output.
//other option is to hope that 1 of the 2 input strings have enough mem.
//but this is the policy I chose.
/* therefore the use:  */
/*        str_zip(string 1, string 2, output) */


extern void str_zip(char *s1, char *s2, char *output)
{
  while(*s1 != 0 || *s2 != 0)
    {
      if(*s2 == 0)
	{
	  *output = *s1;
	  s1++;
	  output++;
	}
      else if(*s1 == 0)
	{
	  *output = *s2;
	  s2++;
	  output++;	  
	}
      else
	{
	  *output = *s1;
	  output++;
	  *output = *s2;
	  output++; s1++; s2++; //looks nice and compact.	 
	}
    }
  *output = 0;
  return;
}
