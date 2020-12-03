#include <stdio.h>
#include <math.h>
#define MAX 10000
//asdasddfhdf
int factorial(int a)
{
    if (a == 0 || a == 1)
        return 1;

    return factorial(a - 1) * a;
}

int combinations(int n, int k)
{
    int nfac = factorial(n);
    int nkfac = factorial(n - k);
    int kfac = factorial(k);
    int result = nfac / (nkfac * kfac);
    return result;
}

int compositions(int x)
{
    int numberofcompositions = (int)pow(2, x - 1);
    int compositions[numberofcompositions][x];
    for (int j = 0; j < numberofcompositions; j++)
    {
        for (int i = 0; i < x; i++)
        {
            compositions[j][i] = 0;
        }
    }
    int counter = x;
    for (int j = 0; j < numberofcompositions; j++)
    {
        for (int i = 0; i < x; i++)
        {
            if (j == 1)
            {
                compositions[j][i] = 1;
            }
            else if (i < counter)
            {
                compositions[j][i] = compositions[j - 1][i] + compositions[j][i + 1];
                counter -= 2;
                i++;
            }
        }
    }

    for (int j = 0; j < numberofcompositions; j++)
    {
        printf("\ncomp %d: ", j);
        for (int i = 0; i < x; i++)
        {
            printf("%d ", compositions[j][i]);
        }
    }
    return 1;
}

int main()
{
    printf("%d", combinations(4, 2));
    return 0;
}