#include <stdio.h>
#include <stdlib.h>

void cit()
{
    int n;
    scanf("%d",&n);
    if (n!=-1) cit();
    printf("%d ",n);
}

int main()
{
    cit();

}
