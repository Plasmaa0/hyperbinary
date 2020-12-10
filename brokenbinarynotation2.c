#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int MAXRECURSIONDEPTH = 15; //максимальная глубина рекурсии
int MAXACTIVENUMBERS = 40;  //максимальное число одновременно обрабатываемых чисел
int MAXTIME = 10;           //максимальное время работы программы
int MAXMEMORY = 10;         //максимально задействуемая бамять в килобайтах
int x;
time_t start; //глобальная переменная времени

int factorization(int x, int *divisors, int length, int mode) //mode == 0 : разбивает число на простые множители, их записывает массив
{                                                             //mode == 1 : возвращает 1 или 0 в зависимости от простоты числа
    int divisorindex = 0;
    int i = 2;
    int isprime = 1;
    while (i <= sqrt(x) && divisorindex < length)
    {
        if (x % i == 0)
        {
            if (mode == 0)
            {
                divisors[divisorindex] = i;
                divisorindex++;
            }
            else if (mode == 1)
            {
                isprime = 0;
            }
            x = x / i;
        }
        else
        {
            i = i + 1;
        }
    }
    divisors[divisorindex] = x;
    return (mode == 1) ? isprime : divisorindex + 1;
}

int factorial(int a) //факториал числа a
{
    if (a == 0 || a == 1)
        return 1;

    return factorial(a - 1) * a;
}

int C(int n, int k) //число сочетаний из n по k
{
    return factorial(n) / factorial(n - k) / factorial(k);
}

int floor2pow(int x) //возвращается степень двойки - result, при которой 2^result < x < 2^(result+1)
{
    int result = log2(x);
    return result;
}

int floor3pow(int x) //возвращается степень двойки - result, при которой 2^result < x < 2^(result+1)
{
    int result = log(x) / log(3);
    return result;
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

void makenumber(int *input, int length, int *swaps, int *mask, int swapsn, int *output) //по правилам проводит замену цифер в input на позициях swaps с маской mask
{                                                                                       //1 Правило: 10 -> 02
    for (int i = 0; i < length; i++)                                                    //2 Правило: 20 -> 12
    {
        output[i] = input[i];
    }
    for (int i = 0; i < swapsn; i++)
    {
        if (mask[i] == 1)
        {
            int index = swaps[i];
            switch (input[index])
            {
            case 1:
                output[index] = 0;
                output[index + 1] = 2;
                break;
            case 2:
                output[index] = 1;
                output[index + 1] = 2;
                break;
            default:
                break;
            }
        }
    }
}

int ternary(int x, int *bin) //записывает в массив цифры двоичного представления числа Х
{
    int len = 0;
    int f2p = floor3pow(x);
    for (int i = f2p; x != 0; i--)
    {
        bin[i] = x % 3;
        x -= x % 3;
        x /= 3;
        len++;
    }
    return len;
}

int binary(int x, int *bin) //записывает в массив цифры двоичного представления числа Х
{
    int len = 0;
    int f2p = floor2pow(x);
    for (int i = f2p; x != 0; i--)
    {
        bin[i] = x % 2;
        x -= x % 2;
        x /= 2;
        len++;
    }
    return len;
}

int binary2decimal(int *bin, int length)
{
    int result = 0;
    for (int i = length - 1; i >= 0; i--)
    {
        result += bin[i] * pow(2, length - 1 - i);
    }
    return result;
}

int lastchance(int x)
{
    int bin[32];
    int len = binary(x, bin);
    // for (int i = 0; i < len; i++)
    // {
    //     printf("%d", bin[i]);
    // }
    int result = 0;
    for (int i = 0; i <= x * 3; i++)
    {
        int ternar[21];
        int length = ternary(i, ternar);
        int y = binary2decimal(ternar, length);
        if (y == x)
        {
            result = 1;
            for (int j = 0; j < length; j++)
            {
                printf("%d", ternar[j]);
            }
            printf("\n");
        }
    }
    return result;
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

int swapsnumber(int *input, int length) //Возвращает количество цифер, которые можно изменить
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

void combinations(int possibleswapscount, int *output, int i) //записывает массив чисел вроде 010, используется для перечисления сочетаний
{                                                             //например, если possibleswapscount = 3 и вызвать функцию последовательно при i=1,2,3...
    int incl[possibleswapscount + 1];                         //то на она запишет (1,0,0,0), (1,0,0,1), (1,0,1,0), (1,1,0,0), (1,1,0,1), (1,1,1,0), (1,0,1,1), (1,1,1,1)
    int number = pow(2, possibleswapscount);                  //первая цифра полученных чисел не учитывается
    number += pow(2, i);                                      //а оставшиеся 3 цифры будут значить берем ли мы объект в данном сочетании
    int len = binary(number, incl);                           //получается, что перечислены все возможные сочетания из 3х объектов
    for (int j = 1; j < len; j++)
    {
        output[j - 1] = incl[j];
    }
}

int filesize(FILE *file) //возвращает размер файла
{
    fseek(file, 0, SEEK_END);
    int size = (int)ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

void checkerrors(FILE *fp, int depth, int total, int iteration) //обработка ошибок
{
    int error = 0;
    if (depth >= MAXRECURSIONDEPTH)
        error = 1;
    if (total >= MAXACTIVENUMBERS)
        error = 2;
    if (filesize(fp) >= (MAXMEMORY * 8192))
        error = 3;
    if ((int)round(difftime(time(NULL), start)) > MAXTIME)
        error = 4;
    switch (error)
    {
    case 0:
        break;
    case 1:
        fprintf(stderr, "Recursion depth error on %d iteration.", iteration);
        break;
    case 2:
        fprintf(stderr, "Too many numbers to do error on %d iteration.\n", iteration);
        break;
    case 3:
        fprintf(stderr, "Memory overflow error on %d iteration.\n", iteration);
        break;
    case 4:
        fprintf(stderr, "Max time error on %d iteration.\n", iteration);
        break;
    }
    if (error != 0)
    {
        fclose(fp);
        remove("tmp.txt");
        printf("Trying second algorithm\n");
        int success = lastchance(x);
        if (success == 0)
        {
            printf("Failed.\nExiting.\nPress Enter to close the window");
        }
        getchar();
        exit(0);
    }
}

int brokenbinary(int *input, int length, FILE *fp, int depth, int total) //ОСНОВНАЯ ФУНКЦИЯ. поиск альтернативных записей числа в двоичной системе с 2.
{
    int swapsn = swapsnumber(input, length); //получает число и смотрит, сколько в нем можно сделать замен по правилам
    if (swapsn <= 0)                         //если замен нет, выход
    {
        //printf("depth - %d\n", depth);
        return 0;
    }
    int possibleswaps[swapsn];
    findswaps(input, length, possibleswaps); //находит индексы цифер, которые можно изменить по правилу
    int all = swapsn;                        //C(swapsn, 1);
    checkerrors(fp, depth, total, depth);
    int results[all][length];
    int mask[all][swapsn];
    for (int i = 0; i < swapsn; i++)
    {
        combinations(swapsn, mask[i], i); //записывает в mask все возможные сочетания применения замен
    }
    total += all;
    for (int i = 0; i < all; i++)
    {
        makenumber(input, length, possibleswaps, mask[i], swapsn, results[i]); //применяет все замены в соответствии с маской
        brokenbinary(results[i], length, fp, depth + 1, total);                //результат отдается этой же функции в рекурсию
    }
    for (int i = 0; i < all; i++) //печать результата
    {
        fprintf(fp, " ");
        int k = cutzero(results[i], length);
        for (int j = k; j < length; j++)
        {
            fprintf(fp, "%d", results[i][j]);
        }
    }
    return 0;
}

void deletecopiesandprint(FILE *file, int x, int binarylength) //вывод без дублирования результатов
{
    int M = filesize(file);
    char inputchar[M];
    int b = binarylength + 1;
    int a = (int)M / (binarylength);
    //printf("M - %d\na - %d\nb - %d\n", M, a, b);
    char separated[a][b];
    fgets(inputchar, M, file); //считывает все результаты из файла в виде одной строк
    char *pch = strtok(inputchar, " ");
    int f = 0;
    while (pch != NULL)
    {
        strcpy(separated[f], pch); //разбивает считанную строку на подстроки, каждая из которых - один результат
        pch = strtok(NULL, " ");
        f++;
    }

    int noSwap; //сортировка при пузырьком помощи strcmp всех полученных подстрок-результатов
    int N = f;
    for (int i = N - 1; i >= 0; i--)
    {
        noSwap = 1;
        for (int j = 0; j < i; j++)
        {
            int cmp = strcmp(separated[j], separated[j + 1]);
            if (cmp > 0)
            {
                char tmp[b];
                strcpy(tmp, separated[j]);
                strcpy(separated[j], separated[j + 1]);
                strcpy(separated[j + 1], tmp);
                noSwap = 0;
            }
        }
        if (noSwap == 1)
            break;
    }

    for (int j = 0; j < f; j++)
    {
        if (strcmp(separated[j], separated[j + 1]) == 0) //если строки повторяются, то записать "e" во все повторы после первого появления
        {
            strcpy(separated[j], "e");
        }
    }
    printf("Result:\n");
    for (int j = 0; j < f; j++)
    {
        if (strcmp(separated[j], "e") != 0) //вывод без повторов
        {
            puts(separated[j]);
        }
    }
}

double analyzedivizors(int x)
{
    int length = floor2pow(x) + 1;
    int divisors[length];
    int numberofdivisors = factorization(x, divisors, length, 0);
    float difficulty = 0;
    int total2 = 0;
    for (int i = 0; i < numberofdivisors; i++)
    {
        if (divisors[i] == 2)
        {
            total2++;
        }
    }
    difficulty = (1.0 - ((double)total2 / (double)numberofdivisors) + ((double)total2 / 31.0));
    return difficulty;
}

double analyzebinary(int x)
{
    int a = blen(x);
    int b[a];
    int length = binary(x, b);
    int swapsn = swapsnumber(b, length);
    double difficulty = (double)swapsn / ((double)length / 2.0);
    return difficulty;
}

double analyzepow2(int x)
{
    int under = floor2pow(x);
    int upper = under + 1;
    int a = pow(2, under);
    int b = pow(2, upper);
    int left = x - a;
    int right = b - x;
    if (left == 0 || right == 0)
    {
        return 0.00001;
    }
    double k = (double)left / (double)right;
    if (k > 1.0)
    {
        k = 1.0 / k;
    }
    double difficulty = 1 - k;
    return difficulty;
}

void settings(int x)
{
    double divizorsdifficulty = analyzedivizors(x);
    double binarydifficulty = analyzebinary(x);
    double pow2difficulty = analyzepow2(x);
    double difficulty = (divizorsdifficulty + binarydifficulty + pow2difficulty) / 3.0;
    MAXRECURSIONDEPTH = (int)ceil(MAXRECURSIONDEPTH / ((0.001) + (difficulty / 2)));
    MAXACTIVENUMBERS = (int)ceil(MAXACTIVENUMBERS / (difficulty + 0.001));
    MAXTIME = (int)ceil(MAXTIME * (2.0 / difficulty));
    MAXMEMORY = (int)ceil(MAXMEMORY * (5.0 / difficulty));
    if (MAXTIME > 120)
    {
        MAXTIME = 120;
    }
    if (MAXMEMORY > 1000)
    {
        MAXMEMORY = 1000;
    }
}

void handle(int x) //подготовка, обработка входных данных для их отправки в функции brokenbinary и deletecopiesandprint, вывод.
{
    start = time(NULL);
    int a = blen(x); //длина числа в двоичной системе
    int b[a];
    int length = binary(x, b); //перевод в двоичную систему
    FILE *fp;
    fp = fopen("tmp.txt", "a+"); //создание пустого файла, в который будет записан результат
    fprintf(fp, " ");
    for (int i = 0; i < length; i++)
        fprintf(fp, "%d", b[i]);
    brokenbinary(b, length, fp, 0, 0); //поиск и вывод возможных альтернативных записей данного числа в двоичной системе с 2
    fprintf(fp, " ");
    fclose(fp);
    fp = fopen("tmp.txt", "r");
    deletecopiesandprint(fp, x, a); //вывод результата работы без повторов
    fclose(fp);                     //закрытие временного файла
    remove("tmp.txt");              //удаление временного файла
    printf("Time: ~%d seconds.\nPress Enter to exit.", (int)round(difftime(time(NULL), start)));
    getchar();
}

int main()
{
    printf("Input number: ");
    scanf("%d", &x); //ввод числа
    getchar();
    settings(x);
    handle(x);
}
