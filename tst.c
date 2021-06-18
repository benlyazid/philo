# include <stdio.h>
int main(int argc, char const *argv[])
{
    int k = 0;
    for (int i = 0; i < __INT_FAST32_MAX__; i++)
    {
        k++;
    }
    printf("done %d\n", k);
    return 0;
}
