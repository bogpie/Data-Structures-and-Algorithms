#include <stdio.h>
#include <stdlib.h>


void aloc(int *** adr_mat,int nrLin,int nrCol)
{
    int ** mat=NULL;
    mat = calloc(nrLin,sizeof(int*));
    if (mat==NULL) return 0;
    for (int iLin=0;iLin<nrLin;++iLin)
    {
        mat[iLin]=NULL;
        mat[iLin]=calloc(nrCol,sizeof(int));
        if (mat[iLin]==NULL) return 0;

    }
    *adr_mat = mat;
}
void cit(int **mat,int nrLin,int nrCol)
{
    //printf("\nmatricea fara elem nule:");

    printf("mat:");
    for (int iLin=0;iLin<nrLin;++iLin)
    {
        //for (int iCol=iLin;iCol<nrCol;++iCol)
        for (int iCol=0;iCol<nrCol;++iCol)
        {
            scanf("%d",&mat[iLin][iCol]);
        }
    }
}
void afis(int **mat,int nrLin,int nrCol)
{

    if(mat==NULL)
    {
        printf("\nmatricea nu a putut fi declarata");
    }

    for (int iLin=0;iLin<nrLin;++iLin)
    {
        for (int iCol=0;iCol<nrCol;++iCol)
        {
            printf("%d ",mat[iLin][iCol]);
        }
        printf("\n");
    }

}

int ** fPatrat (int ** mat,int nrLin,int nrCol)
{
    int ** mat_patrat=NULL;
    aloc(&mat_patrat,nrLin,nrCol);
    if (nrLin!=nrCol) return NULL;

    for (int iLin=0;iLin<nrLin;++iLin)
    {
        for (int iCol=0;iCol<nrCol;++iCol)
        {
            for (int iOrd=0;iOrd<nrLin;++iOrd)
            {
                mat_patrat[iLin][iCol] += mat[iLin][iOrd]+mat[iOrd][iCol];
            }
        }
    }
    return mat_patrat;
}

int fUrma(int ** mat,int nrLin,int nrCol)
{
    int urma=0;
    for (int iLin=0;iLin<nrLin;++iLin)
    {
        urma+=mat[iLin][iLin];
    }
    return urma;
}

int main()
{
    int ** mat,nrLin,nrCol;

    printf("nrLin=");
    scanf("%d",&nrLin);
    printf("\nnrCol=");
    scanf("%d",&nrCol);

    mat=NULL;
    aloc (&mat,nrLin,nrCol);
    cit (mat,nrLin,nrCol);
    afis(mat,nrLin,nrCol);


    if (nrLin!=nrCol)
    {
        printf("matricea nu este patratica");
        return 0;
    }

    int ** mat_patrat = fPatrat(mat,nrLin,nrCol);
    printf("\nmat_patrat:\n");
    afis(mat_patrat,nrLin,nrCol);

    int urma = fUrma(mat,nrLin,nrCol);
    printf("\nurma=%d",urma);

    return 0;
}
