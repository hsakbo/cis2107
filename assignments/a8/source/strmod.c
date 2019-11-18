//a little present prof. This is an advanced palindrome.
//I originally intended this to be diff, then I realized it was different.
//it will return the different number of characters present in str1 and str2 in
//returns 0 if same char composition.
//O(nlog n) time.
//got a big space complexity tho, so don't get caught by the oom killer.
//O(n^2) is better for small input. Only productive at higher k values.


//pivot 1st char
int partition(char *arr, int ind_end)
{
  int index = 1;
  char temp;
  for(int i = 1; i <= ind_end; i++)
    {
      if(arr[i] < *arr)
	{	  
	  temp = arr[index];
	  arr[index++] = arr[i];
	  arr[i] = temp;	  
	}
    }
  temp = *arr;
  *arr = arr[--index];
  arr[index] = temp;
  return index;
}

//quicksort, just to refresh things.
//next on the list: timsort, IN C.
void q_sort(char *arr, int a, int b)
{
  if(a>=b)
    return;

  int piv = partition(arr+a, b-a);
  q_sort(arr, a+piv+1, b);
  q_sort(arr, a, a+piv-1);
  return;
  
}

extern int strmod(char *s1, char *s2)
{
  int len1 = 0;
  int len2 = 0;
  int dif = 0;

  while(*s1 != 0)
    {
      len1++;
      s1++;
    }
  s1 -= len1;
  

  while(*s2 != 0)
    {
      len2++;
      s2++;
    }
  s2 -= len2;

  char arr1[len1+1];
  char arr2[len2+1];
  for(int i = 0; i <= len1; i++)
    arr1[i] = s1[i];
  
  for(int i = 0; i <= len2; i++)
    arr2[i] = s2[i];

  q_sort(arr1, 0, len1-1); //to preserve the 0 padding
  q_sort(arr2, 0, len2-1); //to preserve the 0 padding
  len1 = 0; //reusing these
  len2 = 0; //reusing

  //insertion and deletion.
  while(arr1[len1] != 0 || arr2[len2] != 0)
    {
      //O(n) = 3(n1+n2)
      if(arr1[len1] == arr2[len2])
	{
	  len1++;
	  len2++;
	}
      else if((arr1[len1] > arr2[len2]) && arr2[len2] != 0)
	{
	  len2++;
	  dif++;
	}
      else
	{
	  len1++;
	  dif++;
	}
    }
  
  return dif;
}
