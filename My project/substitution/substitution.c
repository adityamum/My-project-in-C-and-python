#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{

   if(argc !=2){

       printf("Usage: ./substitution key\n");          // check if user has given only two arguments
            return 1;
}





string key = argv[1];


  for(int i = 0 ,n=strlen(key) ; i<n ; i++ )

{
        if((key[i] <= 'a' && key[i]  >='z')  || (key[i]  <='A'  &&  key[i]  >='Z') ){

            printf("Key must contain 26 characters.\n");  //check if its between ATZ or a to z

            return 1;
        }

        else if(!isalpha(key[i])){
            printf("Usage: ./substitution key\n");
                return 1;
        }

        else if(!(n==26)){

            printf("Usage: ./substitution key\n");
                return 1;

          }



        for(int j = i+1  , m=strlen(key) ; j<m ; j++){

            if(toupper(key[i]) == toupper(key[j]) ){

                printf("Key must contain 26 characters.\n");   //check if no two same characters are present
                  return 1;
            }

        }

}

        string  pt = get_string("plaintext: ");

        printf("ciphertext: ");

        for(int k = 0 ; k< strlen(pt) ; k++){

          if(isupper(pt[k])){

            printf("%c", toupper(key[ pt[k] - 'A' ]));                         //plaint text will subract by 65 and then it will map with substitution key


          }

          else if(islower(pt[k])){

            printf("%c", tolower(key[pt[k]  - 'a' ]));                //plaint text will subract by 97 and then it will map with substitution key and conert to lower alphabets

          }

          else{

            printf("%c" , pt[k] );
          }


        }

        printf("\n");












}