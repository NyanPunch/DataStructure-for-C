#include <stdio.h>
int main()
{
    char charType;
    int integerType;
    float floatType;
    double doubleType;

    /* 선언된 변수의 크기 */
    printf("Size of char: %ld byte\n", sizeof(charType));     //변수 charType 크기
    printf("Size of int: %ld bytes\n", sizeof(integerType));  //변수 integerType 크기
    printf("Size of float: %ld bytes\n", sizeof(floatType));  //변수 floatType 크기
    printf("Size of double: %ld bytes\n", sizeof(doubleType));//변수 doubleType 크기
   
    printf("------------2019038054김경민-------------\n");
    
    /* 자료형별 크기 */
    printf("Size of char: %ld byte\n", sizeof(char));          //자료형 char 크기
    printf("Size of int: %ld bytes\n", sizeof(int));           //자료형 int 크기
    printf("Size of float: %ld bytes\n", sizeof(float));       //자료형 float 크기
    printf("Size of double: %ld bytes\n", sizeof(double));     //자료형 double 크기
    
    printf("-----------------------------------------\n");

    /* 자료형별 포인터의 크기 */
    printf("Size of char*: %ld byte\n", sizeof(char*));        //char형 포인터의 크기
    printf("Size of int*: %ld bytes\n", sizeof(int*));         //int형 포인터의 크기
    printf("Size of float*: %ld bytes\n", sizeof(float*));     //flaot형 포인터의 크기
    printf("Size of double*: %ld bytes\n", sizeof(double*));   //double형 포인터의 크기
    
    return 0;
}
