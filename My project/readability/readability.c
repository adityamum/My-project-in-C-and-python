#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include<math.h>

int count_letters(string s);
int count_words(string s);
int count_sentences(string s);

float L;
float S;
int index;

int main(void)
{

string s = get_string("enter a paragraph: ");  //user enter a paragraph

printf("Text: %s\n", s);                      // print paragraph which is given by user

int count1 = count_letters(s);

int count2 = count_words(s);

int count3 = count_sentences(s);

L = (float)count1/(float)count2 *100;        // average number of letters per 100 words in the text

S = (float)count3/(float)count2 *100;       //average number of sentences per 100 words

index =round(0.0588 * L - 0.296 * S - 15.8);  //Coleman-Liau formula


if(index >= 16){

    printf("Grade 16+\n");                      // if grade is more than equal to 16

    }
else if(index <1){

    printf("Before Grade 1\n");                        // if grade is before 1

}

else{

printf("Grade %i\n", index);                      //if grade falls between 2 to 15

}


}

int count_letters(string s){

    int cl = 0;

    for(int i=0, n = strlen(s) ; i<n ; i++ ){

        if(isalpha(s[i]) ) {    //calculate the number of letter in the paragraph and return the value in int

                 cl++;
                }
            }
                return cl;

      }

int count_words(string s){

    int cw =0;

    for(int i = 0 , n= strlen(s); i <=n; i++){

        if(isspace(s[i]) || s[i] == '\0' ){      //calculate the number of words in a paragraph

            cw++;
        }

        }

            return cw;
}

 int count_sentences(string s){

    int cs =0;
    for(int i = 0 , n= strlen(s); i <=n; i++){

        if(s[i] =='.' || s[i] == '?' || s[i] =='!')         //calculate the number of sentences in a paragraph
        {

            cs++;
        }

     }
            return cs;

 }






