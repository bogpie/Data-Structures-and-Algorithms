#include <stdio.h>
#include <stdlib.h>

int fFact(int n)
{
    if (n==0) return 1;
    return n*fFact(n-1);
}

int main()
{

    int n;
    scanf("%d",&n);

    int fact = fFact(n);

    printf("%d",fact);
}
