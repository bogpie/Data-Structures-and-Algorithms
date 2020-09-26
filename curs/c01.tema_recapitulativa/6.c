#include <stdio.h>
#include <stdlib.h>

struct persoana
{
    char *nume;
    char *prenume;
    char cnp[14];
    int varsta;
};
typedef struct persoana PERSOANA;

int fAdauga (PERSOANA ** adr_v,int* adr_n,int poz,PERSOANA nou)
{

    int n = *adr_n;
    PERSOANA* v=*adr_v;

    if(poz>n+1 || poz<0) return -1;

    ++n;
    v=realloc(v,(n+1)*sizeof(PERSOANA));

    for (int i=poz+1;i<n+1;++i)
    {
        v[i]=v[i-1];
    }
    v[poz]=nou;

    *adr_n=n;
    *adr_v=v;

    return 0;

}

int fGaseste (PERSOANA * v,int n,int feminin)
{
    int sol=0;
    for (int i=0;i<n;++i)
    {
        if ( (v[i].cnp[0]%2==0 && feminin) || (v[i].cnp[0]%2!=0 && !feminin))
        {
            ++sol;
        }
    }
    return sol;
}

int main()
{
    int n;
    PERSOANA * v;
    scanf("%d",&n);

    v=calloc(n,sizeof(PERSOANA));

    for (int i=0;i<n;++i)
    {
        printf("\nnume prenume cnp varsta:");

        v[i].nume = calloc(20,sizeof(char));
        v[i].prenume = calloc(20,sizeof(char));

        scanf("%s%s%s%d",v[i].nume,v[i].prenume,v[i].cnp,&v[i].varsta);
    }

    int feminin;
    printf("feminin? ");
    scanf("%d",&feminin);

    fGaseste(v,n,feminin);

    return 0;
}
