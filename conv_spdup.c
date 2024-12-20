#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include <sys/time.h>

//For writing output to speedup_result.txt
int main(){
    // ---- input and malloc A, F, RESULT ----
    FILE *inputFile = fopen("input_10m.txt", "r");
    int NA, NF;
    fscanf(inputFile,"%d %d", &NA, &NF);
    int *A = malloc(sizeof(int) * NA);
    int *F = malloc(sizeof(int) * NF);
    int NRES = NA - NF + 1;
    int *result_seq = malloc(sizeof(int) * NRES);
    int *result_par = malloc(sizeof(int) * NRES);
    for(int i = 0; i < NA; i++){
        fscanf(inputFile,"%d", &A[i]);
    }
    for(int i = 0; i < NF; i++){
        fscanf(inputFile,"%d", &F[i]);
    }
    // ---- end input and malloc----
    fclose(inputFile);

    // implement here
    //--sequential calculation--
    struct timeval start, end;
    gettimeofday(&start, NULL);
    int i, j;
    for (i = 0; i < NRES; i++) {
        int tmp = 0;
        for (j = 0; j < NF; j++) {
            tmp += F[NF-j-1] * A[i+j];
        }
        result_seq[i] = tmp;
    }
    gettimeofday(&end, NULL);
    double time_seq = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;

    //--parallel calculation--
    gettimeofday(&start, NULL);
    #pragma omp parallel for schedule(static) num_threads(4)
    for (int i = 0; i < NRES; i++) {
        int tmp = 0;
        for (int j = 0; j < NF; j++) {
            tmp += F[NF-j-1] * A[i+j];
        }
        result_par[i] = tmp;
    }
    gettimeofday(&end, NULL);
    double time_par = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;

    // speedup
    double speedup = time_seq / time_par;

    // open to write file
    FILE *file = fopen("speedup_result.txt", "w");

    //writing file
    fprintf(file,"For A Matrix length : %d\n", NA);
    fprintf(file,"And F Matrix length : %d\n", NF);
    fprintf(file, "Time taken for sequential computation: %f seconds\n", time_seq);
    fprintf(file, "Time taken for parallel computation: %f seconds\n", time_par);
    fprintf(file, "Speedup: %f\n", speedup);

    fclose(file);
    // ---- free memory ----
    free(F);
    free(A);
    free(result_par);
    free(result_seq);
    // ---- end free ----

    return 0;
}

