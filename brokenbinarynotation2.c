#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
//ghj
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

int floor2pow(int x) //возвращается наибольшую степень двойки ex, при которой 2^ex < X используя frexp()
{
    double result;
    int ex;
    result = frexp(x, &ex);
    ex += ((int)result == 1) ? (-2) : (-1);
    return ex;
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

int brokenbinary(int *input, int length, FILE *fp) //ОСНОВНАЯ ФУНКЦИЯ. поиск альтернативных записей числа в двоичной системе с 2.
{
    int swapsn = swapsnumber(input, length); //получает число и смотрит, сколько в нем можно сделать замен по правилам
    if (swapsn <= 0)                         //если замен нет, выход
    {
        return 0;
    }
    int possibleswaps[swapsn];
    findswaps(input, length, possibleswaps); //находит индексы цифер, которые можно изменить по правилу
    int all = C(swapsn, 1);
    int results[all][length];
    int mask[all][swapsn];
    for (int i = 0; i < swapsn; i++)
    {
        combinations(swapsn, mask[i], i); //записывает в mask все возможные сочетания применения замен
    }
    for (int i = 0; i < all; i++)
    {
        makenumber(input, length, possibleswaps, mask[i], swapsn, results[i]); //применяет все замены в соответствии с маской
        brokenbinary(results[i], length, fp);                                  //результат отдается этой же функции в рекурсию
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

int filesize(FILE *file) //возвращает размер файла
{
    fseek(file, 0, SEEK_END);
    int size = (int)ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
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

void handle(int x) //подготовка, обработка входных данных для их отправки в функции brokenbinary и deletecopiesandprint, вывод.
{
    int a = blen(x); //длина числа в двоичной системе
    int b[a];
    int length = binary(x, b); //перевод в двоичную систему
    FILE *fp;
    fp = fopen("tmp.txt", "a+"); //создание пустого файла, в который будет записан результат
    fprintf(fp, " ");
    for (int i = 0; i < length; i++)
        fprintf(fp, "%d", b[i]);
    brokenbinary(b, length, fp); //поиск и вывод возможных альтернативных записей данного числа в двоичной системе с 2
    fprintf(fp, " ");
    fclose(fp);
    fp = fopen("tmp.txt", "r");
    deletecopiesandprint(fp, x, a); //вывод результата работы без повторов
    fclose(fp);                     //закрытие временного файла
    remove("tmp.txt");              //удаление временного файла
    printf("Press Enter to exit.");
    getchar();
}

int main()
{
    int x;
    printf("Input number: ");
    scanf("%d", &x); //ввод числа
    getchar();
    handle((int)x);
}

//функции не используются, остались от прошлых версий
/*
int C_all(int n) //количество всех возможных сочетаний из n (без установки определенного количества чисел в сочетаннии)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += C(n, i);
    }
    return sum;
}

// изначально думал что функция ниже - swapall(), является решением задачи
// но потом понял, что она выдаёт неполное решение.
// Оставил тут для возможной доработки программы.
int swapall(int *input, int length, int *output) //upd: заменяет сразу всё, что может, т.е. упускает варианты, где не все замены проведены
{                                                //Генерирует варианты в двоичной системе с 2
    for (int i = 0, j = 0; i < length; i++, j++) //input - массив цифр исходного числа;
    {                                            //output - массив цифр выходного числа;
        output[j] = input[i];                    //length - количество цифр исходного числа
    }                                            //Проходит по всем парам цифер входного числа и изменяет их, используя два правила:
    int changes = 0;                             //1 Правило: 10 -> 02
    for (int i = 0; i < length - 1; i++)         //2 Правило: 20 -> 12
    {                                            //Возвращает длину полученной строки
        switch (canswap(input, length, i))       //Если не было внесено ни одного изменения, то возвращает -1
        {                                        //ВАЖНО: применяет изменения разом на всю строку. !!!!!!!!!!!!!!!!!!!!!!!
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
*/
//