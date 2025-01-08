#include <stdio.h>
int main() {

float a;
char b;
float out;
printf("Input temperature: ");
scanf("%f %c", &a, &b);
if (b == 'c' || b == 'C'){
    out = (a * 9/5)+32;
    printf("Output temperature: %.1ff\n", out);
} else if (b == 'f' || b == 'F'){
    out = (a - 32)*5/9;
    printf("Output temperature: %.1fc\n", out);
} else {
    printf("Output Error\n");
}
return 0;
}