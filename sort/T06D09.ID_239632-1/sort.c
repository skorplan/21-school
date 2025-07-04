#include <stdio.h>

int input(int *arr);
void sort(int *arr);
void output(int *arr);

int main(void)
{
    int arr[10];
    if (input(arr) != 0)
    {
        printf("n/a");
        return 1;
    }
    sort(arr);
    output(arr);
}

int input(int *arr)
{
    int check = 0;
    for (int i = 0; i < 9; i++) // последний эдемент и так встанет на место
    {
        if (scanf("%d", &arr[i]) != 1)
        {
            return 1;
        }
        if (i > 10)
        {
            return 1;
        }
    }
    return 0;
}

void sort(int *arr)
{
    for (int i = 0; i < 10; i++)
    {
        int tmp = i;
        for (int j = i + 1; j < 10; j++)
        {
            if (arr[tmp] > arr[j])
            {
                tmp = j;
            }
        }
        if (tmp != i)
        {
            int check = arr[i];
            arr[i] = arr[tmp];
            arr[tmp] = check;
        }
    }
}

void output(int *arr)
{
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }
}