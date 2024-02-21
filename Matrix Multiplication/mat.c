#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>

int M,N,P;

void show(int m,int n,int A[m][n])
{
    for (int i = 0; i < m; i++) 
    {
        for (int j = 0; j < n; j++) printf("%d ", A[i][j]);
        printf("\n");
    }
}

void mul(int A[M][N], int B[N][P], int C[M][P], int start, int end)
{
    for (int i = start; i <= end; i++) 
    {
        for (int j = 0; j < P; j++) 
        {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) C[i][j] += A[i][k] * B[k][j];
        }
    }
}

int main() 
{   
    printf("Enter values of M,N, and P: ");
    scanf("%d %d %d", &M,&N,&P);
    int A[M][N],B[N][P];
    printf("\nEnter elements of matrix A:\n");
    for (int i = 0; i < M; i++) 
    {
        for (int j = 0; j < N; j++) scanf("%d", &A[i][j]);
    }
    printf("\nEnter elements of matrix B:\n");
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < P; j++) scanf("%d", &B[i][j]);
    }  
    printf("\nmatrix A:\n"); show(M,N,A);
    printf("\nmatrix B:\n"); show(N,P,B);
    
    int (*C)[P] = mmap(NULL, sizeof(int) * M * P, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    for(int i = 0; i < M; i++)
    {
        int pid = fork();
        if(pid == 0)
        {   
            mul(A, B, C, i, i);
            exit(0);     
        }
    }
    for(int i = 0; i<M; i++) wait(NULL);

    printf("\nResulting matrix C:\n");
    show(M,P,C);
}
