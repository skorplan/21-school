#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#define ROWS 25
#define COLUMNS 80
int initial_choice(char array[ROWS][COLUMNS]);
void initial_change(const char *file_name, char array[ROWS][COLUMNS]);
void do_next_step(char field_matrix[ROWS][COLUMNS]);
int count_cells(char field_matrix[ROWS][COLUMNS], int row, int col);
int predict(int cell_state, int count);
void show(char array[ROWS][COLUMNS]);

int main(void)
{
    initscr();
    char array[ROWS][COLUMNS]; // сюда записывае мзначения
    int res = initial_choice(array);
    if (res == ' ')
    {
        printw("See you!");
        refresh();
        getch();
        endwin();
        return 0;
    }
    timeout(1000);
    while (1)
    {
        clear();
        do_next_step(array); // внутри уже две функции для полдсчета соседей
        show(array);
        int res = getch();
        if (res == ' ')
        {
            break;
        }
    }
    endwin();
    return 0;
}

int initial_choice(char array[ROWS][COLUMNS])
{
    int res;
    do
    {
        printw("Choose a file ( 1 to 5)\n");
        printw("File 1 - 1\n");
        printw("File 2 - 2\n");
        printw("File 3 - 3\n");
        printw("File 4 - 4\n");
        printw("File 5 - 5\n");
        printw("Press space to exit\n");
        refresh();

        res = getch();
        cbreak();
        noecho();
        clear();
        switch (res)
        {
        case '1':
            initial_change("10_planers.txt", array);
            return res;

        case '2':

            initial_change("centrifuge.txt", array);
            return res;

        case '3':

            initial_change("growth.txt", array);
            return res;

        case '4':

            initial_change("pulsar.txt", array);
            return res;
        case '5':
            initial_change("spaceship.txt", array);
            return res;
        case ' ':
            return res;
        }
    } while (1);
    clear();
    return res;
}

void initial_change(const char *file_name, char array[ROWS][COLUMNS])
{
    clear();
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        printw("File is empty");
        refresh();
        getch();
        return;
    }
    // иы файл точками заполняем , а потом уже с помощью fgets заносим значения из file в array (виесто stdin в fgets будет file)
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            array[i][j] = '.';
        }
    }
    fclose(file);
}

void do_next_step(char field_matrix[ROWS][COLUMNS])
{
    char result[ROWS][COLUMNS] = {0};

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            int neighbors = count_cells(field_matrix, i, j);
            result[i][j] = predict(field_matrix[i][j] == 'o' ? 1 : 0, neighbors) ? 'o' : '.'; // у меня там были оч большие условия - с помощью ии вот сократил )
        }
    }
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            field_matrix[i][j] = result[i][j];
        }
    }
}

int count_cells(char field_matrix[ROWS][COLUMNS], int row, int col)
{
    static const char standard_shift_x[] = {-1, 0, 1, 1, 1, 0, -1, -1};
    static const char standard_shift_y[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int count = 0;
    for (int k = 0; k < 8; k++)
    {
        int x = col + standard_shift_x[k];
        if (x < 0)
        {
            x = COLUMNS - 1;
        }
        else if (x >= COLUMNS)
        {
            x = 0;
        }

        int y = row + standard_shift_y[k];
        if (y < 0)
        {
            y = ROWS - 1;
        }
        else if (y >= ROWS)
        {
            y = 0;
        }

        if (field_matrix[y][x] == 'o')
        {

            count++;
        }
    }
    return count;
}

int predict(int cell_state, int count)
{
    if (cell_state)
    {
        return (count == 2 || count == 3);
    }
    else
    {
        return (count == 3);
    }
}
/*функция отрисовки поля */
void show(char array[ROWS][COLUMNS])
{

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            printw("%c", array[i][j]);
        }
        printw("\n");
    }
    refresh();
}