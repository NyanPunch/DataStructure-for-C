/*******************************
프로그램명: 행렬 연산 프로그램
작 성 자: 2019038054 김경민
작 성 일: 2022 03 30 ~ 2022 04 02
프로그램 설명: 동적메모리할당을 이용해 행렬을 만들고 요구사항을 만족한다
********************************/ 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);  //동적으로 행렬 생성 함수
void print_matrix(int** matrix, int row, int col);  //행렬 출력 함수
int free_matrix(int** matrix, int row, int col);    //동적 행렬 해제 함수
int fill_data(int** matrix, int row, int col);  //행렬 데이터 무작위 입력
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);  //행렬 덧셈 함수
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);   //행렬 뺄셈 함수
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);   //전치행렬 생성 함수
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);  //행렬 곱셈 함수

int main()
{

    char command;   //메뉴 이용시 명령어를 입력받을 변수
    printf("[----- [김경민]  [2019038054] -----]\n");

    int row, col;
    srand(time(NULL));

    printf("Input row and col : ");
    scanf("%d %d", &row, &col); 
    int** matrix_a = create_matrix(row, col);   //행렬 a 생성
    int** matrix_b = create_matrix(row, col);   //행렬 b 생성
    int** matrix_a_t = create_matrix(col, row); //전치행렬 행렬 t 생성 ##입력받은 행과 열이 반대

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) {return -1;}

    do{
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

        switch(command) {
        case 'z': case 'Z': //행렬 생성
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P': //행렬 출력
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A': //행렬 덧셈
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S': //행렬 뺄셈
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T': //matrix_a의 전치행렬 matrix_a_t 생성
            printf("Transpose matrix_a \n");
            printf("matrix_a_t\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': case 'M': //matrix_a 와 matrix_a_t 곱셈
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q': //동적 메모리 해제와 프로그램 종료
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default:    //주어진 명령어 이외 입력시 
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');   //'q' 또는 'Q'가 아닐 시 무한 반복

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    if (row <= 0 || col <= 0){                          //전처리검사 전달이 완벽히 왔는지 확인
        printf("Check the sizes of row and col!\n");
        return NULL;
    }
       
    int **matrix = (int**)malloc(sizeof(int *)*row);    //동적메모리 할당 row영역
    for(int i=0;i<row;i++)
        matrix[i] = (int*)malloc(sizeof(int)*col);      //동적메모리 할당 col영역
    
    /* check post conditions */
    if(matrix == NULL) {    //후처리검사 메모리할당이 제대로 되었는지 확인
        printf("Memory Allocation Failed.\n");
        return NULL;
    }
    return matrix;
}
/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
	if (row <= 0 || col <= 0) { //전처리 검사
		printf("Check the size of row and col!\n");
		return;
	}
    for(int i=0; i<row; i++){   //row x col 행렬 출력
        for(int j=0; j<col; j++)
            printf("%3d ", matrix[i][j]);
        printf("\n");   //행 바꿈
    }
    if (matrix == NULL) {   //후처리 검사
		printf("Memory Allocation Failed.\n");
		return;
	}
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col) //동적메모리 영역 해제 함수
{
    if (row <= 0 || col <= 0){  //전처리검사 전달이 완벽히 왔는지 확인
        printf("Check the sizes of row and col!\n");
        return -1;
    }
    for(int i=0;i<row;i++)
        free(matrix[i]);    //동적메모리 해제 row영역
    free(matrix);          //동적메모리 해제 col영역   

    return 1;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)   
{   
    if (row <= 0 || col <= 0) { //전처리검사
		printf("Check the size of row and col!\n");
		return -1;
	}
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++)
            matrix[i][j]=( rand() % 20 );   //0~19사이 랜덤 값
    }
    if (matrix == NULL) {   //후처리검사
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	return 1;
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{   
    int** matrix_sum = create_matrix(row, col); //덧셈연산을 저장하고 출력할 함수
    if (row <= 0 || col <= 0) { //전처리검사
		printf("Check the size of row and col!\n");
		return -1;
	}

    for(int i=0; i<row ; i++){
        for(int j=0; j<col ; j++)  //a[] + b[]
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];
    }       //행렬의 덧셈의 경우 동일 위치에 행렬의 값과 더한다.

    if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) { //후처리검사
		printf("Memory Allocation Failed.\n");
		return -1;
	}
    print_matrix(matrix_sum,row,col); //덧셈 출력함수
    free_matrix(matrix_sum,row,col);  //할당 해제
    return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sub = create_matrix(row,col); //뺄셈연산 저장 메모리 생성
    if (row <= 0 || col <= 0) { //전처리검사
		printf("Check the size of row and col!\n");
		return -1;
	}

    for(int i=0; i<row ; i++){
        for(int j=0; j<col ; j++)  //a[] - b[] 함수
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];
    }          //행렬의 뺄셈의 경우 동일 위치에 행렬의 값과 뺀다.

    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) { //후처리검사
		printf("Memory Allocation Failed.\n");
		return -1;
	}
    print_matrix(matrix_sub,row,col);
    free_matrix(matrix_sub,row,col);
    return 1;
}

/* transpose the matrix to matrix_t */                                  //int** matrix_a_t = create_matrix(col, row);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)    //if 3x2 matrix, t => 2x3 matrix   row, col
{
    if (row <= 0 || col <= 0) { //전처리검사
		printf("Check the size of row and col!\n");
		return -1;
	}
    
    for(int i=0; i<row ; i++){
        for(int j=0; j<col ; j++)           //전치행렬 생성 시 행과 열을 반대로 생성 해둠
            matrix_t[i][j] = matrix[j][i];  //행과 열이 정 반대이므로 matrix[j][i]를 기입
    }

    if (matrix == NULL || matrix_t ==NULL) {    //후처리검사
		printf("Memory Allocation Failed.\n");
		return -1;
	}

    return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)   
{   
    int** matrix_mul = create_matrix(row,col);  //행렬곱셈 메모리 할당
	if (row <= 0 || col <= 0) { //전처리검사
		printf("Check the size of row and col!\n");
		return -1;
	}

    int sum;
    for(int i=0; i<row ; i++){    //a의 행
        for(int j=0; j<row; j++) {//t의 열
            sum = 0;
            for(int k=0; k<col; k++)    //a의 열 t의 행
                sum += matrix_a[i][k] * matrix_t[k][j];
            matrix_mul[i][j] = sum;
        }
    }

    if (matrix_t == NULL || matrix_mul == NULL) { //후처리검사
		printf("Memory Allocation Failed.\n");
		return -1;
	}
    print_matrix(matrix_mul,row,row);   //첫 번째 row = matrix_a의 row 두 번째 row = matrix_t의 col인 row
    free_matrix(matrix_mul,row,row);
    return 1;
}