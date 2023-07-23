'''
№6 Задача о нахождении кратчайших путей
'''
#6.1
field = [[0 for j in range(17)] for i in range(12)]

for i in range(12):
    for j in range(17):
        if i == 11 or j == 0:
            field[i][j] = 1

#заполнение матрицы, каждый элемент которой - количество путей до
#определённой клетки прямоугольника

i = 10
j = 1
while j < 16:
    while i > -1:
        field[i][j] = field[i + 1][j] + field[i][j - 1]
        i -= 1
        if i == -1 and j != 16:
            i = 10
            j += 1
#вывод массива
print(*field, sep='\n')

print('\n')

ans1 = field[0][16]
#6.2
field = [[0 for j in range(17)] for i in range(12)]
#декременация с range(стартовый индекс, последний индекс - 1, -шаг) - обход в обратном порядке
for i in range(11, -1, -1):
    for j in range(17):
        field[11][0], field[11][1], field[10][0] = 1, 1, 1
        if i == 11 and 0 <= j <= 6:
            field[i][j] = 1
        elif i + j <= 9 or i + j >= 18:
            field[i][j] = 0
        else:
            field[i][j] = field[i+1][j] + field[i][j-1]
            #print(field[i][j])

print(*field, sep='\n')

ans2 = field[0][16]

print('\n')

print("Количество различных кратчайших путей, которые ведут из левого нижнего угла в правый верхний угол:", ans1)
print("Количество различных кратчайших путей такие, что два вертикальных участка не идут подряд:", ans2)

