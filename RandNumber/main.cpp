#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void SortArray(int *Array, int len)
{
    for (int i = 0; i < len -1; ++i)
    {
        for (int j = i + 1; j < len; ++j)
        {
            int tmp = Array[i];
            if (Array[i] > Array[j])
            {
                Array[i] = Array[j];
                Array[j] = tmp;
            }
        }
    }
}

bool CreateNew(int *Array, int len, int cmp)
{
    for (int i = 0; i < len; ++i)
    {
        if (Array[i] == cmp)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    int result[7] = {0};
    int red_hash[33] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
                       16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
                       29, 30, 31, 32, 33};
    int blue_hash[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    srand((int)time(0));
    for (int i = 0; i < 6; ++i)
    {
        SortArray(result,i);
        int tmp = red_hash[rand() % 33];
        while (CreateNew(result,i,tmp))
        {
            tmp = red_hash[rand() % 36];
        }
        result[i] = tmp;
    }
    SortArray(result,6);
    result[6] =  blue_hash[rand() % 16];
    for (int i = 0; i < 7; ++i)
    {
        printf("%d  ", result[i]);
    }
    char str[10];
    scanf("按任意键结束%s",str);
    return 0;
}