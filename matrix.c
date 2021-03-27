#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{

    char command;
    printf("[----- [고승현]  [2016039086] -----]\n");

    int row, col;
    

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);
    int** matrix_a = create_matrix(row, col);
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row);

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) { return -1; }

    do {
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command) {
        case 'z': case 'Z':
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
/*인자로 열과 행을 받아서 동적할당을 통해 이차원배열을 생성하고
이중포인터를 통해 해당 이차원 배열의 주소를 저장하고 해당 이중포인터에
저장되어있는 이차원배열의 주소값을 리턴*/
int** create_matrix(int row, int col)
{
    if (row <= 0 || col <= 0)
        return NULL;

    int** matrix = (int**)malloc(sizeof(*matrix) * row);
    for (int i = 0; i < row; i++) {
        matrix[i] = (int*)malloc(sizeof(**matrix) * col);
    }
    return matrix;
}

/* print matrix whose size is row x col */
/*이중포인터를 통해 이차원배열의 주소값을 받는다-참조에의한 호출
이용해서 이차원 배열을 이중 포인터를 통해 출력한다*/
void print_matrix(int** matrix, int row, int col)
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d  ", matrix[i][j]);
        }
        printf("\n");
    }
}


/* free memory allocated by create_matrix() */
/*동적 할당을 받은 이중포인터를 해제해준다*/
int free_matrix(int** matrix, int row, int col)
{
    if (matrix == NULL || row <= 0 || col <= 0)
        return -1;

    else {
        free(matrix);
        return 0;
    }
}


/* assign random values to the given matrix */
/*rand()을 통해 이차원배열에 랜덤 값을 할당한다*/
int fill_data(int** matrix, int row, int col)
{
    if (matrix == NULL || row <= 0 || col <= 0)
        return -1;

    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrix[i][j] = (rand() % 20);
        }
    }
    return 0;
}

/* matrix_sum = matrix_a + matrix_b */
/*행렬의 덧셈을 위해 인자로 이중포인터 2개를 인자로받아서
행렬의 덧셈을 수행하고 결과를 저장할 이차원배열을 생성후 결과를 저장한다
그리고 출력까지 수행한다*/
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    if (matrix_a == NULL || matrix_b == NULL || row <= 0 || col <= 0)
        return -1;

    int** matrix_sum = (int**)malloc(sizeof(int*) * row);
    for (int i = 0; i < row; i++) {
        matrix_sum[i] = (int*)malloc(sizeof(int**) * col);
    }
    for (int j = 0; j < row; j++) {
        for (int z = 0; z < col; z++) {
            matrix_sum[j][z] = matrix_a[j][z] + matrix_b[j][z];
        }
    }
    for (int x = 0; x < row; x++) {
        for (int y = 0; y < col; y++) {
            printf("%d  ", matrix_sum[x][y]);
        }
        printf("\n");
    }
    free(matrix_sum);
    return 0;
}

/* matrix_sub = matrix_a - matrix_b */
/*행렬의 뺄셈을 위해 이중포인터 2개를 인자로 받고
행렬의 뺄셈을 수행후 결과값을 저장할 이차원배열을 생성하고
해당 결과를 출력한다*/
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    if (matrix_a == NULL || matrix_b == NULL || row <= 0 || col <= 0)
        return -1;

    int** matrix_sub = (int**)malloc(sizeof(int*) * row);
    for (int i = 0; i < row; i++) {
        matrix_sub[i] = (int*)malloc(sizeof(int**) * col);
    }
    for (int j = 0; j < row; j++) {
        for (int z = 0; z < col; z++) {
            matrix_sub[j][z] = matrix_a[j][z] - matrix_b[j][z];
        }
    }
    for (int x = 0; x < row; x++) {
        for (int y = 0; y < col; y++) {
            printf("%d  ", matrix_sub[x][y]);
        }
        printf("\n");
    }
    free(matrix_sub);
    return 0;
}

/* transpose the matrix to matrix_t */
/*일반적인 행렬의 전치연산을 수행하는 함수로
인자로받은 matrix의 이차원배열의 열을 전치행렬의 행으로 복사하는 
방식을 반복수행하는 함수*/
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    if (matrix == NULL || matrix_t == NULL || row <= 0 || col <= 0)
        return -1;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrix_t[i][j] = matrix[j][i];
        }
    }
    
    return 0;
}

/* matrix_axt - matrix_a x matrix_t */
/*행렬a와 해당행렬의 전치행렬의 곱을 수행하는 함수로서
행과열이 같은 경우와 그렇지 않은 경우로 나누어서 수행하는 함수로
행을 고정후 전치행렬의 열을 순서대로 곱셈을하여 결과값을 구해야하므로
전치행렬의 열의 값을 1씩 증가시키면서 열을 반복해서 행렬a의 행과 곱셈을 수행후
결과를 출력하는 방식으로 구현하였다*/
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    if (matrix_a == NULL || matrix_t == NULL || row <= 0 || col <= 0)
        return -1;
    if (row == col) {
        for (int i = 0; i < row; i++) {
            int z = 0;
            while (1) {
                int value = 0;
                for (int j = 0; j < col; j++) {
                    value += matrix_a[i][j] * matrix_t[j][z];

                }
                printf("%d  ", value);
                z++;
                if (z == col)
                    break;
            }
            printf("\n");
        }
    }
    else {
        for (int i = 0; i < row; i++) {
            int z = 0;
            while (1) {
                int value = 0;
                for (int j = 0; j < col; j++) {
                    value += matrix_a[i][j] * matrix_t[j][z];

                }
                printf("%d  ", value);
                z++;
                if (z == row)
                    break;
            }
            printf("\n");
        }
    }


    return 0;
}

