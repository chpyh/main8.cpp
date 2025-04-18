#include <iostream>

void full_field(bool field[10][10])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            field[i][j] = false;
        }
    }
}


void full_opponent_field(char opponent_field[10][10]){
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            opponent_field[i][j] = '-';
        }
    }
}


void print_field(bool field[10][10])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            std::cout << field[i][j] << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}


// будем распечатывать для игроков успешность из ударов
void print_opponent_field(char field[10][10])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            std::cout << field[i][j] << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

// получение координаты для расстановки корабля или выстрела
int recive_coordinate()
{
    int coordinate;
    std::cin >> coordinate;

    while (coordinate < 0 || coordinate > 9)
    {
        std::cout << "Error: coordinate is out of bonds! Choose another coordinate: " << std::endl;
        std::cin >> coordinate;
    }

    return coordinate;
}

// проверка координат на занятость
bool is_free(bool field[10][10], int y, int x)
{
    if (field[y][x] == true)
    {
        return false;
    }

    return true;
}

// постановка корабля
void put_ship(bool field[10][10], int ship_size)
{
    int y;
    int x;
    int free_space = 0;

    // до тех пор, пока не будет достаточно места, будем запрашивать координаты и пытаться поставить корабль

    while (free_space != ship_size)
    {
        std::cout << "Choose coordinates:" << std::endl;

        // для корабля в одну клетку второй координаты не нужно, чтобы не делать лишнюю работу, сделаем его отдельно
        if (ship_size == 1)
        {
            y = recive_coordinate();
            x = recive_coordinate();
            if (is_free(field, y, x))
            {
                field[y][x] = true;
                free_space++;
                std::cout << "Ship on site." << std::endl;
            }
        }
        else
        { // для остальных кораблей будем запрашивать вторую координату
            int y1;
            int x1;

            y = recive_coordinate();
            x = recive_coordinate();
            y1 = recive_coordinate();
            x1 = recive_coordinate();

            // поскольку корабли можно ставить только вертикально или только горизонтально, координаты должны совпадать по одной из осей
            // по второй - разница между координатами должна составлять размер корабля - 1

            if ((y1 - y == ship_size - 1 & x == x1) || (x1 - x == ship_size - 1 & y == y1))
            {

                // проверяем, все ли клетки по координатам свободны

                for (int i = y; i <= y1; i++)
                {
                    for (int j = x; j <= x1; j++)
                    {
                        if (is_free(field, i, j))
                        {
                            // если клетка свободна, увеличиваем значение свободного места
                            // если он станет равным размеру корабля, значит, клеток достаточно
                            free_space++;
                        }
                    }
                }
                // если все места по коордиинатам свободны, ставим корабль
                if (free_space == ship_size)
                {
                    for (int i = y; i <= y1; i++)
                    {
                        for (int j = x; j <= x1; j++)
                        {
                            field[i][j] = true;
                        }
                    }
                    std::cout << "Ship on site." << std::endl;
                }
                else
                {
                    // если нет - пишем, что место занято, надо менять координаты
                    std::cout << "Error: the place is partially occupied! Change coordinates!" << std::endl;
                    free_space = 0;
                }
            }
            else
            {
                std::cout << "Error! These coordinates unacceptable: coordinates don't match the size or the ship is positioned diagonally." << std::endl;
            }
        }
    }

    // return field;
}

// размещение кораблей одного вида
void put_same_ships(bool field[10][10], int count, int size)
{
    while (count > 0)
    {
        put_ship(field, size);
        count--;
    }
}

// размещаем все корабли

void build_field(bool field[10][10])
{
    std::cout << "Welcome to the Sea Battle! " << std::endl;
    std::cout << "Let's arrange the ships! Please, remember: ships must be placed strictly vertically or horizontally!" << std::endl;

    std::cout << "At first put 1-cell ships." << std::endl;
    put_same_ships(field, 4, 1);
    print_field(field);

    std::cout << "Good! It's time to choose a place for 2-cell ships." << std::endl;
    put_same_ships(field, 3, 2);
    print_field(field);

    std::cout << "Genious! Now put 3-cell ships on the field." << std::endl;
    put_same_ships(field, 2, 3);
    print_field(field);

    std::cout << "Perfect! And finally put 4-cell ship on the field." << std::endl;
    put_same_ships(field, 1, 4);
    print_field(field);

    std::cout << "Congratulations! Now you can start the game!" << std::endl;
    std::cout << std::endl;
}

// ход-выстрел
void move(bool field[10][10], char opponentField[10][10])
{
    std::cout << " your move. Choose coordinates: " << std::endl;

    print_opponent_field(opponentField); 
    
    int y = recive_coordinate();
    int x = recive_coordinate();

    if (field[y][x] == true)
    {
        std::cout << "You got it!" << std::endl;
        field[y][x] = false;
        opponentField[y][x] = 'V';
    }
    else
    {
        std::cout << "Unfortunately, you missed.  " << std::endl;
        opponentField[y][x] = '!';
    }

    std::cout << std::endl;
}

// проверка поля: остались ли еще непотопленные корабли
bool is_Over(bool field[10][10])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (field[i][j] == true)
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{

    bool field1[10][10];
    bool field2[10][10];

// далее заведем еще два поля, чтобы игроки могли отслеживать ситуацию с кораблями 
// противника после каждого выстрела, особенно удачного
    char enemyField1[10][10];
    char enemyField2[10][10];

    full_field(field1);
    full_field(field2);
    full_opponent_field(enemyField1);
    full_opponent_field(enemyField2);

    std::cout << "Hello, Player1!" << std::endl;
    build_field(field1);
    std::cout << "Hello, Player2!" << std::endl;
    build_field(field2);

    // далее непосредственно бой
    bool isOver = false;
    int countTunes = 0;

    // заводим цикл: пока не конец - прокурчиваем
    while (!isOver)
    {
        countTunes++;

        std::cout << "Player1,";
        move(field2, enemyField2);
        if (countTunes >= 10 && is_Over(field2))
        {
            std::cout << "Player1! You win! Game is over!" << std::endl;
            isOver = true;
            break;
        }

        std::cout << std::endl;

        std::cout << "Player2,";
        move(field1, enemyField1);

        if (countTunes >= 10 && is_Over(field1))
        {
            std::cout << "Player2! You win! Game is over!" << std::endl;
            isOver = true;
        }
    }

}
