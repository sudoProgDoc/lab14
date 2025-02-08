#include <iostream>
using namespace std;

int main()
{
    FILE* fl = fopen("test1.txt", "rt");
    int **a, n, m, i, j, *L, *S, *D, *v1, *v2, *U;
    fscanf(fl,"%d%d", &n, &m);

    a = new int* [n];
    for (i = 0;i < n;i++)
    {
        a[i] = new int[n];
        for (j = 0;j < n;j++) a[i][j] = 0;
    }
    v1 = new int[m]; v2 = new int[m];
    for (i = 0;i < m;i++)
    {
        fscanf(fl,"%d%d", &v1[i], &v2[i]);
        a[v1[i]][v2[i]] = 1;
        a[v2[i]][v1[i]] = 1;
    }
    fclose(fl);

    FILE* fm = fopen("ou1.txt", "at");//1
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++) fprintf(fm, "%d%s", a[i][j]," ");
        fprintf(fm, "\n");
    }
    fclose(fm);

    D = new int[m + m]; S = new int[n];
    L = new int[n]; U = new int[n];

    for (i = 0;i < n;i++) L[i] = 0;
    for (i = 0;i < m;i++) {L[v1[i]]++; L[v2[i]]++;}
    S[0] = 0;
    U[0] = 0;
    for (i = 1;i < n;i++) { S[i] = S[i - 1] + L[i - 1]; U[i] = S[i]; }
    for (i = 0;i < m;i++)
    {
        D[U[v1[i]]] = v2[i];
        U[v1[i]]++;
        D[U[v2[i]]] = v1[i];
        U[v2[i]]++;
    }

    fm = fopen("ou2.txt", "at");//2
    for (i = 0; i < n; i++) fprintf(fm, "%d%s", L[i]," ");
    fprintf(fm, "\n");
    for (i = 0; i < n; i++) fprintf(fm, "%d%s", S[i]," ");
    fprintf(fm, "\n");
    for (i = 0; i < m * 2; i++) fprintf(fm, "%d%s", D[i], " ");
    fprintf(fm, "\n");
    fclose(fm);


    for (i = 0;i < n;i++) U[i] = S[i];//3
    fm = fopen("ou3.txt", "at");
    for (i = 0; i < n; i++)
        for (j = U[i]; j < S[i] + L[i]; j++)
        {
            fprintf(fm, "%d%s%d%s", i, " ",D[j],"\n");
            U[D[j]]++;
        }


    for (int i = 0; i < n; i++) {
        delete[] a[i];
    }
    delete[] a;
    delete[] v1;
    delete[] v2;
    delete[] D;
    delete[] S;
    delete[] L;
    delete[] U;
}