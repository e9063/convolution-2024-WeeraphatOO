#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    // ---- input and malloc A, F, RESULT ----
    int NA, NF;
    scanf("%d %d", &NA, &NF);
    int *A = malloc(sizeof(int) * NA);
    int *F = malloc(sizeof(int) * NF);
    int NRES = NA - NF + 1;
    int *result = malloc(sizeof(int) * NRES);
    memset(result, 0, sizeof(int) * NRES);
    for(int i = 0; i < NA; i++){
        scanf("%d", &A[i]);
    }
    for(int i = 0; i < NF; i++){
        scanf("%d", &F[i]);
    }
    // ---- end input and malloc----

    // implement here
    int i, j;
    for (i = 0; i < NRES; i++) {
        int tmp = 0;
        for (j = 0; j < NF; j++) {
            tmp += F[NF-j-1] * A[i+j];
        }
        result[i] = tmp;
    }

    // print result
    for (i = 0; i < NRES; i++) {
        printf("%d\n",result[i]);
    }

    // ---- free memory ----
    free(F);
    free(A);
    free(result);
    // ---- end free ----

    return 0;
}

