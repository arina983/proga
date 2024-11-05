ns = []

while True:
    n = int(input())
    if n == 0:
        break
    ns.append(n)
andreys_n = int(input())

position = 0

for n in ns:
    if n >= andreys_n:
        position +=1
print(position)