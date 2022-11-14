# TODO
from cs50 import get_int

while True:
    height = get_int("Pyramid height: ")
    #get me a pyramid between 1 to 8
    if height >=1 and height <= 8:
        break

#logic for pyramid
for i in range(height):
    for j in range(height - i - 1):
        print(" ", end = "")
    for k in range(-1 , i):
        print("#", end = "")
    print("  ", end = "")
    for l in range(-1, i):
        print("#", end = "")
    print()
















