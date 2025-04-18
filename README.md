# main8.cpp

## Игра морской бой

### Условия:
Требуется реализовать упрощённую игру в морской бой:
1. Игровое поле размером 10 на 10 клеток. 
2. Участвуют два игрока.
3. В арсенале каждого из них 
    * 4 маленьких кораблика размером в одну клетку, 
    * 3 небольших корабля размером в две клетки, 
    * 2 средних корабля размером в три клетки 
    * 1 большой корабль размером в четыре клетки. 
    Для простоты клетки поля пронумерованы по вертикали от 0 до 9 и по горизонтали// от 0 до 9.
Вначале игроки по очереди расставляют корабли, начиная с самых маленьких и заканчивая большими. Маленькие корабли в одну клетку расставляются
с помощью указания одной клетки-точки на поле, к примеру 2,1. 
4. Корабли размерностью от двух клеток и выше расставляются с помощью координат их начала и конца, к примеру: 0,1–0,3. Корабли могут быть установлены только строго вертикально или горизонтально.

> Установка корабля по диагонали недопустима, об этом тоже надо сообщить пользователю. 
5. Если корабль не может быть размещён на заданных клетках из-за того, что он столкнётся с другим кораблём (окажется на его клетках) или выйдет за пределы поля, то игроку должно быть сделано предупреждение, после которого он должен переставить корабль на новые валидные координаты.
6. После того как все корабли расставлены, начинается игра. Игроки по очереди атакуют друг друга, называя координаты выстрела.
7. После выстрела в консоль выводится информация о его результате: попал или мимо. 
8. Если выстрел успешен, клетка, на которой был корабль (или его фрагмент), затирается и становится пустой. 

Игра заканчивается тогда, когда все корабли одной из сторон будут полностью уничтожены.
Как только это произойдёт, в консоль выводится информация с номером игрока, который победил.
