

num = [1,2,3]
n = len(num)
k = 0
for i in range(0,n):
    for j in range(i+1,n):
        if num[i] == num[j]:
            k = 1

print(k)
