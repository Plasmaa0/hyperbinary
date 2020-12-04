#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// эта программа - перевод на язык си одной строчки кода python"h=lambda x:set(int(bin(i)[2:])+int(bin(x-i)[2:])for i in range(x))"
// +небольшая оптимизация

int blen(int x) //находит длину числа X в двоичной системе, сдвигая его побитово вправо пока числе не станет равно 0
{               //количество сделанных сдвигов и будет длиной числа в двоичной системе
    int i = 0;
    while (1)
    {
        if (x == 0b0)
        {
            break;
        }
        else
        {
            x = (x >> 1);
            i++;
        }
    }
    return i;
}

int floor2pow(double x) //возвращается наибольшую степень двойки ex, при которой 2^ex < X используя frexp()
{
    double result;
    int ex;
    result = frexp(x, &ex);
    ex += ((int)result == 1) ? (-2) : (-1);
    return ex;
}

double binary(int x) //записывает в массив цифры двоичного представления числа Х
{
    char digits[blen(x)];
    int len = 0;
    double result;
    for (int i = floor2pow(x); x != 0; i--)
    {
        digits[i] = x % 2 + '0';
        x -= x % 2;
        x /= 2;
        len++;
    }
    result = round((double)atoi(digits));
    return result;
}

void sort(double *input, int length)
{
    int noSwap; //сортировка при пузырьком помощи strcmp всех полученных подстрок-результатов
    int N = length;
    for (int i = N - 1; i >= 0; i--)
    {
        noSwap = 1;
        for (int j = 0; j < i; j++)
        {
            if (input[j] > input[j + 1])
            {
                double tmp;
                tmp = input[j];
                input[j] = input[j + 1];
                input[j + 1] = tmp;
                noSwap = 0;
            }
        }
        if (noSwap == 1)
            break;
    }
}

void markcopies(double *input, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (input[i] == input[i + 1]) //если строки повторяются, то записать "-1" во все повторы после первого появления
        {
            input[i] = -1;
        }
    }
}

int main()
{
    int x;
    printf("Input number: ");
    scanf("%d", &x);
    getchar();
    double a[x];
    for (int i = 0; i < x; i++)
    {
        a[i] = (binary(i) + binary(x - i));
    }
    sort(a, x);
    markcopies(a, x);
    printf("Result:\n");
    for (int i = 0; i < x; i++)
    {
        if (a[i] != -1) //вывод без повторов
        {
            printf("%.0lf\n", a[i]);
        }
    }
    printf("Press Enter to exit.");
    getchar();
    return 0;
}