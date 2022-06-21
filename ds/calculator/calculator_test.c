
#include "calculator.h"
#include <stdio.h>

int main()
{
    char *exp1 = "13-3";/* 10.0 */
    char *exp2 = "13-3.14*2";/* 6.72 */
    char *exp3 = "1336.137/12.5434/437.43";/* 0.2435 */
    char *exp4 = "5 * (2 * 4 + 3)"; /* 55.0 */
    
    printf("result of the expression 1 (10.0) is: %.01f\n", calculator(exp1));
    printf("result of the expression 2 (6.72) is: %.02f\n", calculator(exp2));
    printf("result of the expression 3 (0.2435) is: %.4f\n", calculator(exp3));
    printf("result of the expression 4 (55.0) is: %.1f\n", calculator(exp4));
    
    return 0;
}
