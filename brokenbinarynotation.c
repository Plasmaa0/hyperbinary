#include <stdio.h>
#include <math.h>

int factorial(int a)
{
    if (a == 0 || a == 1)
        return 1;

    return factorial(a - 1) * a;
}

int numberofcombinations(int n, int k)
{
    int nfac = factorial(n);
    int nkfac = factorial(n - k);
    int kfac = factorial(k);
    int result = nfac / (nkfac * kfac);
    return result;
}

int combinations(int *input, int length, int k)//////////////////////////////////////
{
    for(int i = 0; i < numberofcombinations(length, k); i++){
        ///////////////////////////////////////////////////////////////////////////
    }
}

int floor2pow(int x) //возвращается наибольшую степень двойки ex, при которой 2^ex < X используя frexp()
{
    double result;
    int ex;
    result = frexp(x, &ex);
    ex += ((int)result == 1) ? (-2) : (-1);
    return ex;
}

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

int binary(int x, int *bin) //записывает в массив цифры двоичного представления числа Х
{
    int len = 0;
    for (int i = floor2pow(x); x != 0; i--)
    {
        bin[i] = x % 2;
        x -= x % 2;
        x /= 2;
        len++;
    }
    return len;
}

int canswap(int *input, int length, int position) //Проверяет, возможна ли замена цифер с индексами position и position+1
{                                                 //Возвращает 0, если нет, 2, если замена: 20->12, 1 ,если замена: 10->02
    switch (input[position])
    {
    case 1:
        if (input[position + 1] == 0 && position + 1 < length)
        {
            return 1;
        }
        return 0;
        break;
    case 2:
        if (input[position + 1] == 0 && position + 1 < length)
        {
            return 2;
        }
        return 0;
        break;
    default:
        break;
    }
    return 0;
}

void findswaps(int *input, int length, int *output) //Возвращает индексы цифер, которые можно заменить
{
    int j = 0;
    for (int i = 0; i < length; i++)
    {
        int pass = canswap(input, length, i);
        if (pass != 0)
        {
            output[j] = i;
            j++;
        }
    }
}

int swapsnumber(int *input, int length)
{
    int j = 0;
    for (int i = 0; i < length; i++)
    {
        int pass = canswap(input, length, i);
        if (pass != 0)
        {
            j++;
        }
    }
    return j;
}

int swapall(int *input, int length, int *output) //Генерирует варианты в двоичной системе с 2
{                                                //input - массив цифр исходного числа;
    for (int i = 0, j = 0; i < length; i++, j++) //output - массив цифр выходного числа;
    {                                            //length - количество цифр исходного числа
        output[j] = input[i];                    //Проходит по всем парам цифер входного числа и изменяет их, используя два правила:
    }                                            //1 Правило: 10 -> 02
    int changes = 0;                             //2 Правило: 20 -> 12
    for (int i = 0; i < length - 1; i++)         //Возвращает длину полученной строки
    {                                            //Если не было внесено ни одного изменения, то возвращает -1

        switch (canswap(input, length, i))
        {
        case 1:
            if (input[i + 1] == 0)
            {
                output[i] = 0;
                i++;
                output[i] = 2;
                changes = 1;
            }
            break;
        case 2:
            if (input[i + 1] == 0)
            {
                output[i] = 1;
                i++;
                output[i] = 2;
                changes = 1;
            }
            break;
        default:
            break;
        }
    }
    if (changes == 0)
    {
        return -1;
    }
    return length;
}

int cutzero(int *input, int length) //возвращает индекс первой ненулевой цифры в числе
{
    for (int i = 0; i < length; i++)
    {
        if (input[i] != 0)
        {
            return i;
        }
    }
    return 0;
}



int brokenbinary(int *input, int length)
{
    int swapsn = swapsnumber(input, length);
    int possibleswaps[swapsn];
    findswaps(input, length, possibleswaps);
}

int main()
{
    printf("Do you want to cut zeros? (Y-1, N-0): "); //если ввести 1, то, например, вместо 01221 будет выведено 1221
    char cutzeros;                                    //если ввести 0, то числа будут выводиться с нулями в начале, если такие будут
    cutzeros = getchar();
    while (1)
    {
        int x;
        printf("Input number: ");
        scanf("%d", &x); //ввод числа
        getchar();
        int a = blen(x);
        int b[a];
        int length = binary(x, b);
        brokenbinary(b, length);
        printf("\nExit? (Y-1, N-0): "); //выход из программы если введено 1, ожидание ввода нового числа если введено 0
        if (getchar() == '1')
        {
            return 0;
        }
        else
        {
            printf("\n");
        }
    }
    return 0;
}