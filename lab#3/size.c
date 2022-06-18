/*******************************
프로그램명: 이중포인터 크기
작 성 자: 2019038054 김경민
작 성 일: 2022 03 23
프로그램 설명: 이중포인터의 특징을 이해하고 설명한다
********************************/ 
#include<stdio.h>

void main()
{
    char **x;   //32bit로 동작하여 x, *x, **x의 사이즈의 차이를 주기 위해 임의로 변경 
    printf("sizeof(x) = %lu\n", sizeof(x));     //주소를 저장하는 메모리 = 4byte(8byte)
    printf("sizeof(*x) = %lu\n", sizeof(*x));   //주소를 저장하는 메모리 = 4byte(8byte)
    printf("sizeof(**x) = %lu\n", sizeof(**x)); //값을 저장하는 메모리 = (char)1byte
    printf("\n2019038054 김경민\n");
}