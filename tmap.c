#include <stdio.h>
#include <stdlib.h>
#include <math.h>

    double randomDraw(float roughness) {
        return (2*roughness) * ((double)rand()/RAND_MAX) - roughness;

    }

    void fillMatrix(int startRow, int endRow, int startCol, int endCol, int size, double matrix[size][size], float roughness) {

        if (endRow - startRow > 1) {

            int midRow = (startRow + endRow) / 2;
            int midCol = (startCol + endCol) / 2;

            double middle = (matrix[startRow][startCol] + matrix[endRow][startCol] + matrix[startRow][endCol] + matrix[endRow][endCol])/4 + randomDraw(roughness);
            double middleTop = (matrix[startRow][startCol] + matrix[startRow][endCol] + middle)/3;
            double middleRight = (matrix[startRow][endCol] + matrix[endRow][endCol] + middle)/3;
            double middleBottom = (matrix[endRow][startCol] + matrix[endRow][endCol] + middle)/3;
            double middleLeft = (matrix[startRow][startCol] + matrix[endRow][startCol] + middle)/3;

            matrix[midRow][midCol] = middle;
            if (isnan(matrix[startRow][midCol])) matrix[startRow][midCol] = middleTop + randomDraw(roughness);
            if (isnan(matrix[midRow][endCol])) matrix[midRow][endCol] = middleRight + randomDraw(roughness);
            if (isnan(matrix[endRow][midCol])) matrix[endRow][midCol] = middleBottom + randomDraw(roughness);
            if (isnan(matrix[midRow][startCol])) matrix[midRow][startCol] = middleLeft + randomDraw(roughness);

            fillMatrix(startRow, midRow, startCol, midCol, size, matrix, roughness);
            fillMatrix(startRow, midRow, midCol, endCol, size, matrix, roughness);
            fillMatrix(midRow, endRow, startCol, midCol, size, matrix, roughness);
            fillMatrix(midRow, endRow, midCol, endCol, size, matrix, roughness);
        }
    }


int main()
{
    char fileName[256];
    char outputName[300];
    int matrixSize, seed, i, p, line = 0;
    double maxValue, minValue;
    float roughness, PA,PB,PC,PD;

    scanf("%255s", fileName);

    FILE *input = fopen(fileName, "r");
    if (input == NULL) {
        printf("Could not open file %s\n", fileName);
        return 1;
    }

    while (fscanf(input, "%i %i %f %f %f %f %f", &matrixSize, &seed, &roughness, &PA, &PB, &PC, &PD) == 7) {
        line++;

        p = 1;
        for(i=1;i<=matrixSize;i++) { p=2*p; }
        p++;
        matrixSize = p;

        double MapMatrix[matrixSize][matrixSize];
        int MapMatrix2[matrixSize][matrixSize];
        for (int i=0;i<matrixSize;i++) {
            for (int j=0;j<matrixSize;j++) {
                MapMatrix[i][j] = NAN;
            }
        }
        MapMatrix[0][0] = PA;
        MapMatrix[0][matrixSize-1] = PB;
        MapMatrix[matrixSize-1][0] = PC;
        MapMatrix[matrixSize-1][matrixSize-1] =  PD;
        srand(seed);

        fillMatrix(0, matrixSize-1, 0, matrixSize-1, matrixSize, MapMatrix, roughness);

        maxValue = MapMatrix[0][0];
        minValue = MapMatrix[0][0];
        for (int i=0;i<matrixSize;i++) {
            for (int j=0;j<matrixSize;j++) {
                if (MapMatrix[i][j] > maxValue){
                    maxValue = MapMatrix[i][j];
                }
                if (MapMatrix[i][j] < minValue){
                    minValue = MapMatrix[i][j];
                }
            }
        }

        sprintf(outputName, "output%d.txt", line);
        FILE *output = fopen(outputName, "w");
        if (output == NULL) {
            printf("Could not create file %s\n", outputName);
            continue;
        }

        fprintf(output, "P2\n%d %d\n255\n", matrixSize, matrixSize);
        for (int i=0;i<matrixSize;i++) {
            for (int j=0;j<matrixSize;j++) {
                if (maxValue == minValue) {
                    MapMatrix2[i][j] = 0;
                } else {
                    MapMatrix2[i][j] = 255 - (int)(255 * ((MapMatrix[i][j] - minValue)/(maxValue - minValue)));
                }
                fprintf(output, "%i ", MapMatrix2[i][j]);
            }
            fprintf(output, "\n");
        }
        fclose(output);
    }

    fclose(input);
    return 0;
}
