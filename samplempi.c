#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>
#include <mpi.h> 	
#include <time.h>
 
//void search(char* pat, char* txt, char result);

int main(int argc, char argv[])
{
    double starttime, endtime;
    char pat[3];
    char txt[100];
    printf("Enter Txt\n");
    scanf("%s", txt);
    printf("Kelime %s\n",txt);
    int N = strlen(txt);
    printf("Enter Pattern\n");
    scanf("%s", pat);
    printf("Aranacak Desen %s\n",pat);
    int M = strlen(pat);
    printf("Len Txt :%u",N);
    printf("\nLen Pattern:%u",M);
    
    int nthreads , tid , i, j ;
    
    MPI_Init(0,0);


    #pragma omp parallel shared (txt,pat,nthreads ) private (i, j, tid)
    {

    starttime = MPI_Wtime();
       tid = omp_get_thread_num();

       
        if (tid == 0){
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
       
        printf("Thread %d starting...\n", tid);
        
        #pragma omp for
        
        for (int i = 0; i <= N - M; i++) {
        int j;
 
        /* For current index i, check for pattern match */
        for (j = 0; j < M; j++)
            if (txt[i + j] != pat[j])
                break;
 
        if (j == M) // if pat[0...M-1] = txt[i, i+1, ...i+M-1]
            printf("Pattern found at index %d \n", i);
        
    	}
    endtime = MPI_Wtime();
    printf("%d. thread That took %f seconds\n",tid,endtime-starttime);
    }
}
