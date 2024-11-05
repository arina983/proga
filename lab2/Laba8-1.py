data = input().split()

numbers = [] 
letters = []
for i in data:

    if i.isdigit(): 
        numbers.append(int (i))
    else:
        letters.append(i)

del data

print(numbers)
print(letters)
