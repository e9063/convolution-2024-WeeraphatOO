#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

//For writing output to speedup_result.txt
int main(){
    // ---- input and malloc A, F, RESULT ----
    FILE *inputFile = fopen("input_billion.txt", "r");
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
    double start_seq = omp_get_wtime();
    int i, j;
    for (i = 0; i < NRES; i++) {
        int tmp = 0;
        for (j = 0; j < NF; j++) {
            tmp += F[NF-j-1] * A[i+j];
        }
        result_seq[i] = tmp;
    }
    double end_seq = omp_get_wtime();
    double time_seq = end_seq - start_seq;

    //--parallel calculation--
    double start_par = omp_get_wtime();
    #pragma omp parallel for schedule(static) num_threads(4)
    for (int i = 0; i < NRES; i++) {
        int tmp = 0;
        for (int j = 0; j < NF; j++) {
            tmp += F[NF-j-1] * A[i+j];
        }
        result_par[i] = tmp;
    }
    double end_par = omp_get_wtime();
    double time_par = end_par - start_par;

    // speedup
    double speedup = time_seq / time_par;

    // open to write file
    FILE *file = fopen("speedup_result.txt", "w");

    //writing file
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

