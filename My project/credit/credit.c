#include <cs50.h>
#include <stdio.h>

int main(void)
{

long n = get_long("Number:");
long credit1;

long credit2;

long digit;
int digit1;
long c;
long digit2;

int sum2=0;

int sum;


int sum1 = 0;
credit1 = n/10;
while(credit1 > 0)
{

c = credit1 %10;
credit1 /= 100;
digit = c*2;

if(digit>9){
digit1 = digit%10;
digit /= digit;

digit = digit + digit1;

}

sum1 = sum1 + digit;
}
credit2 = n;

while(credit2 > 0){

digit2 = credit2%10;

  credit2 /= 100;

sum2 = sum2 + digit2;



}

sum = sum1 + sum2;

if(sum%10 !=0 ){

    printf("INVALID\n");
}

int ae;
int mc;
int vi1;
int vi2;
ae =  n/10000000000000;
mc =  n/100000000000000;
vi1 = n/1000000000000;
vi2 = n/1000000000000000;

if(ae == 34 || ae==37){

  printf("American Express\n");
}
else if(mc == 51 ||mc == 52 || mc == 53 || mc == 54 || mc == 55 ){

  printf("MasterCard\n");
}

else if(vi1 == 4 || vi2 == 4){

  printf("VISA\n");
}



}