#include <stdio.h>

#define VERTICAL 25
#define HORIZON 80
/*изменяем ракетки */
void racket_direction(int *racket1_y, int *racket2_y)
{
    int input;
    while (1)
    {
        input = getchar();

        if (input == '\n')
            continue;
        if ((input == 'a' || input == 'A') && *racket1_y > 2)
        {
            (*racket1_y)--;
            break;
        }
        else if ((input == 'z' || input == 'Z') && *racket1_y < VERTICAL - 3)
        {
            (*racket1_y)++;
            break;
        }
        else if ((input == 'k' || input == 'K') && *racket2_y > 2)
        {
            (*racket2_y)--;
            break;
        }
        else if ((input == 'm' || input == 'M') && *racket2_y < VERTICAL - 3)
        {
            (*racket2_y)++;
            break;
        }
        else if (input == ' ')
        {
            break;
        }
    }
    while ((input = getchar()) != '\n' && input != EOF)
    {
    }
}

/*сбрасываем игру*/
void reset_game(int *racket1_y, int *racket2_y, int *ball_x, int *ball_y, int *ball_dir_x, int *ball_dir_y)
{
    *racket1_y = VERTICAL / 2;
    *racket2_y = VERTICAL / 2;
    *ball_x = HORIZON / 2;
    *ball_y = VERTICAL / 2;
    *ball_dir_x = 1;
    *ball_dir_y = 1;
}

// Движение мяча
int move_ball(int *ball_x, int *ball_y, int *ball_dir_x, int *ball_dir_y, int racket1_x, int racket1_y,
              int racket2_x, int racket2_y)
{
    *ball_x += *ball_dir_x;
    *ball_y += *ball_dir_y;

    if (*ball_y >= VERTICAL - 2 || *ball_y <= 1)
    {
        *ball_dir_y *= -1;
    }

    if (*ball_x <= 1)
    {
        return 1;
    }

    if (*ball_x >= HORIZON - 2)
    {
        return 2;
    }

    // с левой ракеткой
    if (*ball_x == racket1_x - 1 && *ball_y <= racket1_y + 1 && *ball_y >= racket1_y - 1)
    {
        *ball_dir_x = 1;
        if (*ball_y == racket1_y + 1)
        {
            *ball_dir_y = 1;
        }
        else if (*ball_y == racket1_y - 1)
        {
            *ball_dir_y = -1;
        }
    }
    // с правой ракеткой
    if (*ball_x == racket2_x - 1 && *ball_y <= racket2_y + 1 && *ball_y >= racket2_y - 1)
    {
        *ball_dir_x = -1;
        if (*ball_y == racket2_y + 1)
        {
            *ball_dir_y = 1;
        }
        else if (*ball_y == racket2_y - 1)
        {
            *ball_dir_y = -1;
        }
    }
    return 0;
}

/*отрисовка поля*/
void game_pole(int racket1_x, int racket1_y, int racket2_x, int racket2_y, int ball_x, int ball_y, int score1,
               int score2)
{
    printf("Player 1: %d | Player 2: %d\n", score1, score2);

    for (int i = 0; i < VERTICAL; ++i)
    {
        for (int j = 0; j < HORIZON; ++j)
        {
            if (i == 0 || i == VERTICAL - 1 || j == 0 || j == HORIZON - 1)
            {
                printf("*");
            }
            else if (i == ball_y && j == ball_x)
            {
                printf("o");
            }
            else if (j == racket1_x && (i >= racket1_y - 1 && i <= racket1_y + 1))
            {
                printf("|");
            }
            else if (j == racket2_x && (i >= racket2_y - 1 && i <= racket2_y + 1))
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
    // Инициализация переменных
    int racket1_y = VERTICAL / 2;
    int racket2_y = VERTICAL / 2;
    int racket1_x = 2;
    int racket2_x = HORIZON - 3;
    int ball_x = HORIZON / 2;
    int ball_y = VERTICAL / 2;
    int ball_dir_x = 1;
    int ball_dir_y = 1;
    int score1 = 0;
    int score2 = 0;

    // Первая отрисовка
    game_pole(racket1_x, racket1_y, racket2_x, racket2_y, ball_x, ball_y, score1, score2);

    while (score1 < 2 && score2 < 2)
    {
        int res =
            move_ball(&ball_x, &ball_y, &ball_dir_x, &ball_dir_y, racket1_x, racket1_y, racket2_x, racket2_y);
        racket_direction(&racket1_y, &racket2_y);

        if (res == 1)
        {
            score2++;
            reset_game(&racket1_y, &racket2_y, &ball_x, &ball_y, &ball_dir_x, &ball_dir_y);
        }
        else if (res == 2)
        {
            score1++;
            reset_game(&racket1_y, &racket2_y, &ball_x, &ball_y, &ball_dir_x, &ball_dir_y);
        }

        printf("\033c");
        game_pole(racket1_x, racket1_y, racket2_x, racket2_y, ball_x, ball_y, score1, score2);
    }

    if (score1 == 2)
    {
        printf("Выиграл первый игрок!\n");
    }
    else
    {
        printf("Выиграл второй игрок!\n");
    }
    return 0;
}
