#include <stdio.h>



int main()
{
    int max, min;
    scanf("%d %d",&max, &min);
    char buff[128] = {'\0'};
    printf("%d  .... %d\n", max, min);

    int a, b;
    sprintf(buff,"%d-%d", max, min);

    sscanf(buff, "%d-%d", &a, &b);

    printf("%d-%d\n", a, b);
}
