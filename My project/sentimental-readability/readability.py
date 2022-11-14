# TODO

from cs50 import get_string

#initialise count
countL=0
countS=0

#last word set to  1
countW=1

#get text from user
text = get_string("Text: ")

for i in text:
    if (i == " "):
        countW += 1

    elif (i == "." or i == "?" or i == "!"):
        countS += 1

    elif (i.isalpha()):
        countL += 1

L = (countL / countW) *100
S = (countS / countW) *100

i = round(0.0588 * L - 0.296 * S - 15.8)

if (1 <= i <= 15):
    print("Grade:", i)

elif ( i >= 16 ):
    print("Grade 16+")

else:
    print("Before Grade 1")






