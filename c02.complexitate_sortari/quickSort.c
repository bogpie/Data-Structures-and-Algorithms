#include <stdio.h>

void split(int v[],int low,int high)
{
    int pivot = v[high];

}

void quickSort(int v[],int low,int high)
{
    if (low<high)
    {
        pivot = split(v,low,high);
        quickSort(v,low,pivot-1);
        quickSort(v,pivot+1,high);
    }
}

int main()
{
    int n,v[20];
    scanf("%d",&n);
    for (int i=0;i<n;++i)
    {
        scanf("%d",&v[i]);
    }

    quickSort(v,0,n-1);

    return 0;
}
