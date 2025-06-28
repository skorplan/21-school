#include <stdio.h>
#include <math.h>
#define VERTICAL 25
#define HORIZON 80

int racket1_y = VERTICAL / 2;
int racket2_y = VERTICAL / 2;

/*функция изменения движения мяча*/
// int ball_direction(void)
//{
// }

void racket_direction(int direction)
{
    if (direction == 1 && racket1_y > 2)
    {
        racket1_y--;
    }
    else if (direction == 2 && racket1_y < VERTICAL - 3)
    {
        racket1_y++;
    }
    else if (direction == 3 && racket2_y > 2)
    {
        racket2_y--;
    }
    else if (direction == 4 && racket2_y < VERTICAL - 3)
    {
        racket2_y++;
    }
    else if (direction == 0)
    {
        racket1_y;
        racket2_y;
    }
}

/*основная функция для поля*/
void game_pole(int start_of_ball_x, int start_of_ball_y)
{

    for (int i = 0; i < VERTICAL; ++i)
    {
        for (int j = 0; j < HORIZON; ++j)
        {
            if (i == 0 || i == VERTICAL - 1 || j == 0 || j == HORIZON - 1)
            {
                printf("*");
            }
            else if (i == start_of_ball_y && j == start_of_ball_x)
            {
                printf("o");
            }
            else if (j == 2 && (i >= racket1_y - 1 && i <= racket1_y + 1))
            {
                if (racket1_y - 1 == 1)
                {
                }

                printf("|");
            }
            else if (j == HORIZON - 3 && (i >= racket2_y - 1 && i <= racket2_y + 1))
            {
                printf("|");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main(void)
{
    int start_of_ball_x = HORIZON / 2;
    int start_of_ball_y = VERTICAL / 2;

    while (1)
    {
        game_pole(start_of_ball_x, start_of_ball_y);
        int input = getchar();

        if (input == 'a' || input == 'A')
        {
            racket_direction(1);
        }
        else if (input == 'z' || input == 'Z')
        {
            racket_direction(2);
        }
        else if (input == 'k' || input == 'K')
        {
            racket_direction(3);
        }
        else if (input == 'm' || input == 'M')
        {
            racket_direction(4);
        }
        else if (input == ' ')
        {
            racket_direction(0);
        }
    }
    return 0;
}