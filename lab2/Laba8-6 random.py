import random

result = []
count = 0

while 1:
    count +=1
    o = random.choice(["O", "Р"])
    result.append(o)
    print(o, end="")

    if len(result) >= 3 and (result[-3:] == ["O", "O", "O"] or result[-3:] == ["Р", "Р", "Р)"]):
        break

print(f"(попыток: {count})")
