#include <stdio.h>
int main()
{
    char charType;
    int integerType;
    float floatType;
    double doubleType;

    /* ����� ������ ũ�� */
    printf("Size of char: %ld byte\n", sizeof(charType));     //���� charType ũ��
    printf("Size of int: %ld bytes\n", sizeof(integerType));  //���� integerType ũ��
    printf("Size of float: %ld bytes\n", sizeof(floatType));  //���� floatType ũ��
    printf("Size of double: %ld bytes\n", sizeof(doubleType));//���� doubleType ũ��
   
    printf("------------2019038054����-------------\n");
    
    /* �ڷ����� ũ�� */
    printf("Size of char: %ld byte\n", sizeof(char));          //�ڷ��� char ũ��
    printf("Size of int: %ld bytes\n", sizeof(int));           //�ڷ��� int ũ��
    printf("Size of float: %ld bytes\n", sizeof(float));       //�ڷ��� float ũ��
    printf("Size of double: %ld bytes\n", sizeof(double));     //�ڷ��� double ũ��
    
    printf("-----------------------------------------\n");

    /* �ڷ����� �������� ũ�� */
    printf("Size of char*: %ld byte\n", sizeof(char*));        //char�� �������� ũ��
    printf("Size of int*: %ld bytes\n", sizeof(int*));         //int�� �������� ũ��
    printf("Size of float*: %ld bytes\n", sizeof(float*));     //flaot�� �������� ũ��
    printf("Size of double*: %ld bytes\n", sizeof(double*));   //double�� �������� ũ��
    
    return 0;
}
