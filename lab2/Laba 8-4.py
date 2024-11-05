numbers = []
#Запрашиваем числа пока не пропустит ввод
while 1:
    n = input(">")
    if n != '':
        if n not in numbers:
            numbers.append(n)
    else:
        break   

numbers = [int(n) for n in numbers]  #Преобразуем элементы списка в числа

avarage = sum(numbers) / len(numbers) 
print(f"Среднее значение:{avarage}")

for n in numbers:
    if n < avarage: 
        print(f"Ниже среднего: {n}")
for n in numbers:
    if n == avarage:
        print(f"Равные среднему значению:{n}")
for n in numbers:
    if n > avarage:
        print(f"Больше среднего:{n}")


