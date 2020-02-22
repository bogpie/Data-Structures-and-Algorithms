#include <stdio.h>
#include <stdlib.h>

void aloc (int**adr_v, int n)
{
    *adr_v = NULL;

    *adr_v = calloc(n,sizeof(int));

    if (*adr_v==NULL) exit(1);
}

void cit(int * v,int n)
{
    for (int i=0;i<n;++i)
    {
        printf("\nv[%d]= ",i);
        scanf("%d",&v[i]);
    }
}

void afis(int * v,int n)
{
    printf("\n");
    for (int i=0;i<n;++i)
    {
        printf("%d ",v[i]);
    }
}

void adauga(int** adr_v,int *adr_n,int poz,int nou)
{
    int n=*adr_n;
    ++n;

    int * v = *adr_v;

    v=realloc(v,n*sizeof(int));
    if (v==NULL) exit(1);


    for (int i=n-1;i>poz;--i)
    {
        v[i]=v[i-1];
    }

    v[poz]=nou;
    *adr_n=n;
    *adr_v=v;
}

void sterge(int** adr_v,int *adr_n,int vechi)
{
    int n=*adr_n;
    int * v = *adr_v;

    for (int i=0;i<n;++i)
    {
        if (v[i]==vechi)
        {
            for (int j=i;j<n-1;++j)
            {
                v[j]=v[j+1];
            }
            --n;
        }

    }

    v=realloc(v,n*sizeof(int));
    if (v==NULL) exit(1);

    *adr_n=n;
    *adr_v=v;
}

int main ()
{
    int *v,n;

    printf("n= ");
    scanf ("%d",&n);

    aloc(&v,n);
    cit(v,n);
    afis(v,n);

    int nou,poz;
    printf("\npoz=");
    scanf("%d",&poz);
    printf("\nnou=");
    scanf("%d",&nou);

    adauga(&v,&n,poz,nou);
    afis(v,n);

    int vechi;
    printf("\nvechi=");
    scanf("%d",&vechi);

    sterge(&v,&n,vechi);
    afis(v,n);

    free(v);

    return 0;
}
