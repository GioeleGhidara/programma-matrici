#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int calculateRank(int *matrix, int rows, int cols);
double determinant(double **matrix, int n);
int calculateRank(int *matrix, int rows, int cols);
int *add(int *m1, int *m2, int r1, int c1, int r2, int c2);
int *mult(int *m1, int *m2, int r1, int c1, int r2, int c2);
int *readMatrixFromFile(const char *filename, int *rows, int *cols);
void writeMatrixToFile(int *matrix, const char *filename, int rows, int cols);
void printMatrix(int *matrix, int rows, int cols);
int test(int *m);

int main(void)
{
    int r1, c1, r2, c2;
    char fileName1[20], fileName2[20];
    char productFile[20], sumFile[20];
    int *m1, *m2;
    int choice2 = -1;
    int choice1 = -1;

    while (choice1!= 0) {
        printf("Quali operazioni vuoi fare?\n");
        printf("1. Scrivere le matrici\n");
        printf("2. Prendere le matrici da file\n");
        printf("3. Rango\n");
        printf("0. Esci\n");

        scanf("%d", &choice1);

        switch (choice1)
        {
            //
            case 1:         /* INSERIMENTO MANUALE MATRICI */
                printf("Inserisci il numero di righe e colonne della prima matrice: ");
                scanf("%d %d", &r1, &c1);
                printf("Inserisci il numero di righe e colonne della seconda matrice: ");
                scanf("%d %d", &r2, &c2);
                m1 = malloc(r1 * c1 * sizeof(int));
                m2 = malloc(r2 * c2 * sizeof(int));
                printf("Inserisci la prima matrice:\n");
                for (int i = 0; i < r1; i++)
                {
                    for (int j = 0; j < c1; j++)
                    {
                        scanf("%d", &m1[i * c1 + j]);
                    }
                }

                writeMatrixToFile(m1, "m1.txt", r1, c1);

                printf("Inserisci la seconda matrice:\n");
                for (int i = 0; i < r2; i++)
                {
                    for (int j = 0; j < c2; j++)
                    {
                        scanf("%d", &m2[i * c2 + j]);
                    }
                }

                writeMatrixToFile(m2, "m2.txt", r2, c2);
                break;
            //
            case 2:               /* INSERIMENTO MATRICI DA FILE */
                printf("Da quale file vuoi leggere la prima matrice? ");
                scanf("%s", fileName1);

                int *mA = readMatrixFromFile(fileName1, &r1, &c1);
                if (!test(mA))
                {
                    printf("Matrice nel file '%s' non trovata o formato non valido.\n", fileName1);
                    return 1;
                }

                printf("Da quale file vuoi leggere la seconda matrice? ");
                scanf("%s", fileName2);

                int *mB = readMatrixFromFile(fileName2, &r2, &c2);
                if (!test(mB))
                {
                    printf("Matrice nel file '%s' non trovata o formato non valido.\n", fileName2);
                    free(mA);
                    return 1;
                }
                /* Assagnazione della matrici lette dai file ad m1 e m2 */
                m1 = mA;
                m2 = mB;
            case 3:
            /* RANGO */
                printf("Di quale file vuoi calcolare il rango della matrice? ");
                scanf("%s", fileName1);

                int *r = readMatrixFromFile(fileName1, &r1, &c1);

                if (!test(r))
                {
                    printf("Matrice nel file '%s' non trovata o formato non valido.\n", fileName1);
                }
                else
                {
                    int rank = calculateRank(r, r1, c1);
                    printf("\nIl rango della matrice nel file '%s' è %d.\n\n\n", fileName1, rank);
                }

                free(r);
                break;
            // 
            case 0:
                printf("Uscita dal programma.\n");
                break;
            //
            default:
                printf("Scelta non valida.\n");

            free(m1);
            free(m2);
        }    
    }
    printf("------------------------------------------------------------");

    while (choice2 != 0){
        printf("\nQuali operazioni vuoi fare?\n");
        puts("1. Somma");
        puts("2. Prodotto");
        puts("3. Stampa da file");
        puts("0. Esci");

        scanf("%d", &choice2);

        switch (choice2)
        {
            //
            case 1:
                            /* ADDIZIONE */
                int *sumPtr = add(m1, m2, r1, c1, r2, c2);
                if (sumPtr != NULL)
                {
                    printf("In quale file vuoi salvare la matrice somma? ");
                    scanf("%s", sumFile);
                    writeMatrixToFile(sumPtr, sumFile, r1, c1);
                    printf("Matrice somma salvata correttamente nel file '%s'.\n", sumFile);
                    printMatrix(sumPtr, r1, c1);
                    free(sumPtr);
                }
                else
                {
                    puts("Errore durante la somma");
                }
                break;
                //
            case 2:
                            /* MOLTIPLICAZIONE */
                int *productPtr = mult(m1, m2, r1, c1, r2, c2);
                if (productPtr != NULL)
                {
                    printf("In quale file vuoi salvare la matrice prodotto? ");
                    scanf("%s", productFile);
                    writeMatrixToFile(productPtr, productFile, r1, c2);
                    printf("Matrice prodotto salvata correttamente nel file '%s'.\n", productFile);
                    printMatrix(productPtr, r1, c2);
                    free(productPtr);
                }
                else
                {
                    puts("Errore durante la moltiplicazione");
                }
                break;
            
            //
            case 3:
                    /* STAMPA */
                puts("Da quale file vuoi stampare la matrice?");
                scanf("%s", fileName1);
                int *mS = readMatrixFromFile(fileName1, &r1, &c1);

                if (!test(mS))
                {
                    printf("Matrice nel file '%s' non trovata o formato non valido.\n", fileName1);
                    return 1;
                }
                printMatrix(mS, r1, c1);
                free(mS);
                break;
            //
            case 0:
                
                printf("Uscita dal programma.\n");
                break;
                
                //
            default:
                    printf("Scelta non valida.\n");
                
        }
    }
        free(m1);
        free(m2);
}

void writeMatrixToFile(int *matrix, const char *filename, int rows, int cols)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Errore nell'apertura del file '%s'.\n", filename);
        return;
    }

    fprintf(file, "%d %d\n", rows, cols);
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            fprintf(file, "%d ", matrix[r * cols + c]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

int *readMatrixFromFile(const char *filename, int *rows, int *cols)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return NULL;
    }

    fscanf(file, "%d %d", rows, cols);
    int tot = (*rows) * (*cols);
    int *matrix = (int *)malloc(tot * sizeof(int));
    for (int i = 0; i < tot; i++)
    {
        fscanf(file, "%d", &matrix[i]);
    }

    fclose(file);
    return matrix;
}

int *mult(int *m1, int *m2, int r1, int c1, int r2, int c2)
{
    if (c1 != r2)
    {
        printf("Errore: Le dimensioni delle matrici non consentono la moltiplicazione.\n");
        return NULL;
    }

    int *result = (int *)malloc(r1 * c2 * sizeof(int));
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            int sum = 0;
            for (int k = 0; k < c1; k++)
            {
                sum += m1[i * c1 + k] * m2[k * c2 + j];
            }
            result[i * c2 + j] = sum;
        }
    }
    return result;
}

int *add(int *m1, int *m2, int r1, int c1, int r2, int c2)
{
    if (r1 != r2 || c1 != c2)
    {
        printf("Errore: Le dimensioni delle matrici non consentono la somma.\n");
        return NULL;
    }

    int *result = (int *)malloc(r1 * c1 * sizeof(int));
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c1; j++)
        {
            result[i * c1 + j] = m1[i * c1 + j] + m2[i * c1 + j];
        }
    }
    return result;
}

double determinant(double **matrix, int n) {
    if (n == 1) {
        return matrix[0][0];
    }

    double det = 0;
    double **minor = (double **)malloc((n - 1) * sizeof(double *));
    for (int i = 0; i < n - 1; i++) {
        minor[i] = (double *)malloc((n - 1) * sizeof(double));
    }

    for (int i = 0; i < n; i++) {
        int minorRow = 0, minorCol = 0;
        for (int row = 1; row < n; row++) {
            for (int col = 0; col < n; col++) {
                if (col != i) {
                    minor[minorRow][minorCol++] = matrix[row][col];
                    if (minorCol == n - 1) {
                        minorRow++;
                        minorCol = 0;
                    }
                }
            }
        }
        double sign = (i % 2 == 0) ? 1.0 : -1.0;
        det += sign * matrix[0][i] * determinant(minor, n - 1);
    }

    for (int i = 0; i < n - 1; i++) {
        free(minor[i]);
    }
    free(minor);

    return det;
}

int calculateRank(int *matrix, int rows, int cols) {
    int rank = 0;

    for (int k = 1; k <= rows; k++) {
        double **tempMatrix = (double **)malloc(k * sizeof(double *));
        for (int i = 0; i < k; i++) {
            tempMatrix[i] = (double *)malloc(k * sizeof(double));
        }

        // Copy the first k rows and columns from matrix to tempMatrix
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                tempMatrix[i][j] = (double)matrix[i * cols + j];
            }
        }

        // Calculate determinant of tempMatrix
        double det = determinant(tempMatrix, k);
        // If determinant is non-zero, increment rank
        if (det != 0) {
            rank++;
        }

        // Free memory allocated for tempMatrix
        for (int i = 0; i < k; i++) {
            free(tempMatrix[i]);
        }
        free(tempMatrix);
    }

    return rank;
}

void printMatrix(int *matrix, int rows, int cols)
{
    printf("%d %d\n", rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d ", *(matrix + i * cols + j));
        }
        printf("\n");
    }
}

int test(int *m)
{
    return (m != NULL);
}
