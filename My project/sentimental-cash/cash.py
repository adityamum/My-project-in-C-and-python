# TODO
from  cs50 import get_float

count = 0
count1 = 0                                                                    #initializing count for each penny
count2 = 0
count3 = 0

while True:
    change = get_float("Change owned: ")                                      #checkinng if the number is valid

    if change > 0:
        break

cent = change * 100


while (cent > 0):
    if cent >= 25:
        cent = cent - 25
        count += 1

    elif cent >= 10:
        cent = cent - 10                                                      #subracting pennies until it reaches 0
        count1 += 1


    elif cent >= 5:
        cent = cent - 5
        count2 += 1

    else:
        cent = cent - 1
        count3 += 1


sum = count + count1 + count2 + count3

print(sum)