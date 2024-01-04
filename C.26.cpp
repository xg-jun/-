#include <stdio.h>
typedef struct {
    int row;
    int col;
    int value;
} Triplet;

// 定义稀疏矩阵的类型
typedef struct {
    Triplet data[100];  // 假设稀疏矩阵最多有100个非零元素
    int rows;
    int cols;
    int num;  // 稀疏矩阵的非零元素个数
} SparseMatrix;

// 初始化稀疏矩阵
void initSparseMatrix(SparseMatrix *matrix, int rows, int cols) {
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->num = 0;
}

// 添加非零元素到稀疏矩阵
void addElement(SparseMatrix *matrix, int row, int col, int value) {
    if (matrix->num >= 100) {
        printf("稀疏矩阵已满，无法添加更多元素。\n");
        return;
    }
    
    matrix->data[matrix->num].row = row;
    matrix->data[matrix->num].col = col;
    matrix->data[matrix->num].value = value;
    matrix->num++;
}

// 稀疏矩阵相加
SparseMatrix addSparseMatrix(SparseMatrix matrixA, SparseMatrix matrixB) {
    SparseMatrix result;
    initSparseMatrix(&result, matrixA.rows, matrixA.cols);
    
    int i = 0, j = 0;
    while (i < matrixA.num && j < matrixB.num) {
        if (matrixA.data[i].row < matrixB.data[j].row || 
            (matrixA.data[i].row == matrixB.data[j].row && matrixA.data[i].col < matrixB.data[j].col)) {
            addElement(&result, matrixA.data[i].row, matrixA.data[i].col, matrixA.data[i].value);
            i++;
        } else if (matrixA.data[i].row > matrixB.data[j].row || 
                   (matrixA.data[i].row == matrixB.data[j].row && matrixA.data[i].col > matrixB.data[j].col)) {
            addElement(&result, matrixB.data[j].row, matrixB.data[j].col, matrixB.data[j].value);
            j++;
        } else {
            int sum = matrixA.data[i].value + matrixB.data[j].value;
            if (sum != 0) {
                addElement(&result, matrixA.data[i].row, matrixA.data[i].col, sum);
            }
            i++;
            j++;
        }
    }
    
    // 处理剩余的非零元素
    while (i < matrixA.num) {
        addElement(&result, matrixA.data[i].row, matrixA.data[i].col, matrixA.data[i].value);
        i++;
    }
    while (j < matrixB.num) {
        addElement(&result, matrixB.data[j].row, matrixB.data[j].col, matrixB.data[j].value);
        j++;
    }
    
    return result;
}

// 稀疏矩阵相乘
SparseMatrix multiplySparseMatrix(SparseMatrix matrixA, SparseMatrix matrixB) {
    SparseMatrix result;
    initSparseMatrix(&result, matrixA.rows, matrixB.cols);
    
    if (matrixA.cols != matrixB.rows) {
        printf("矩阵无法相乘。\n");
        return result;
    }
    
    int i, j, k;
    int temp[matrixB.cols];
    
    for (i = 0; i < matrixA.rows; i++) {
        for (k = 0; k < matrixB.cols; k++) {
            temp[k] = 0;
        }
        
        for (k = 0; k < matrixA.num; k++) {
            if (matrixA.data[k].row == i) {
                for (j = 0; j < matrixB.num; j++) {
                    if (matrixB.data[j].row == matrixA.data[k].col) {
                        temp[matrixB.data[j].col] += matrixA.data[k].value * matrixB.data[j].value;
                    }
                }
            }
        }
        
        for (j = 0; j < matrixB.cols; j++) {
            if (temp[j] != 0) {
                addElement(&result, i, j, temp[j]);
            }
        }
    }
    
    return result;
}

// 打印稀疏矩阵
void printSparseMatrix(SparseMatrix matrix) {
    int i;
    for (i = 0; i < matrix.num; i++) {
        printf("(%d, %d): %d\n", matrix.data[i].row, matrix.data[i].col, matrix.data[i].value);
    }
    printf("\n");
}

int main() {
    // 测试用例1
    SparseMatrix matrixA, matrixB;
    initSparseMatrix(&matrixA, 3, 3);
    initSparseMatrix(&matrixB, 3, 3);
    addElement(&matrixA, 0, 0, 1);
    addElement(&matrixA, 1, 1, 2);
    addElement(&matrixA, 2, 2, 3);
    addElement(&matrixB, 0, 0, 4);
    addElement(&matrixB, 1, 1, 5);
    addElement(&matrixB, 2, 2, 6);
    printf("矩阵A：\n");
    printSparseMatrix(matrixA);
    printf("矩阵B：\n");
    printSparseMatrix(matrixB);
    SparseMatrix addResult = addSparseMatrix(matrixA, matrixB);
    printf("矩阵A + B：\n");
    printSparseMatrix(addResult);
    SparseMatrix multiplyResult = multiplySparseMatrix(matrixA, matrixB);
    printf("矩阵A * B：\n");
    printSparseMatrix(multiplyResult);
    
    // 测试用例2
    SparseMatrix matrixC, matrixD;
    initSparseMatrix(&matrixC, 4, 4);
    initSparseMatrix(&matrixD, 4, 4);
    addElement(&matrixC, 0, 0, 1);
    addElement(&matrixC, 0, 1, 2);
    addElement(&matrixC, 1, 1, 3);
    addElement(&matrixC, 2, 2, 4);
    addElement(&matrixC, 3, 3, 5);
    addElement(&matrixD, 0, 0, 6);
    addElement(&matrixD, 1, 1, 7);
    addElement(&matrixD, 2, 2, 8);
    addElement(&matrixD, 2, 3, 9);
    addElement(&matrixD, 3, 3, 10);
    printf("矩阵C：\n");
    printSparseMatrix(matrixC);
    printf("矩阵D：\n");
    printSparseMatrix(matrixD);
    addResult = addSparseMatrix(matrixC, matrixD);
    printf("矩阵C + D：\n");
    printSparseMatrix(addResult);
    multiplyResult = multiplySparseMatrix(matrixC, matrixD);
    printf("矩阵C * D：\n");
    printSparseMatrix(multiplyResult);
    return 0;
}

