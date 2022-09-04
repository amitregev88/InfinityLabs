#include <stdio.h> /*printf*/
#include <string.h> /*strlen*/

void LongestPalindromic(char *str);

int main()
{
    char *s = "babdsfbaab";
    LongestPalindromic(s);

    return 0;
}




void LongestPalindromic(char *str)
{
    int max = 0;
    int counter = 0;
    int i = 0;
    int j = 0;
    int indx_left = 0;
    int indx_right = 0;




    int len = strlen(str);

    for(i = 0, j = len; i <= j; ++i, --j)
    {
    
    	if (str[i] == str[j])
        {
            counter++;
        }
        
        if (counter > max)
        {
            max = counter;
            indx_left = i - counter;
            indx_right = j + counter;
        }
        
        counter = 0;
    }
   
	for(i = indx_left; i <=indx_right; ++i)
    {
		printf("%s\n",str + i);       
	}


}
