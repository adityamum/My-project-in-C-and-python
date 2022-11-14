#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include<math.h>
#include <stdlib.h>



int main(int argc, string argv[])
{
int key;

    if(argc!=2){

        printf("Usage: ./caesar key\n");         //will give an error when user input more than two words
        return 1;
    }

    for(int i=0,n=strlen(argv[1]); i<n;i++){
        if(isdigit(argv[1][i]) == 0 ){

            printf("Usage: ./caesar key \n");     //will check if each and every line has digit for command line input

            return 1;
        }

    }

    key = atoi(argv[1]);


    string s = get_string("plaintext: ");
    printf("ciphertext: ");

    for(int i = 0 ,n=strlen(s); i < n; i++){

            if(isupper(s[i])){

            printf("%c", (((s[i]-65) + key)%26)+65);               //calculate the cipher text for given plain text in upper case letter
    }

            else if(islower(s[i])){


            printf("%c", (((s[i] -97) + key)%26)+97);            //calculate the cipher text for given plain text in lower case letter
    }
            else{


            printf("%c",s[i]);
    }

    }

    printf("\n");



}

