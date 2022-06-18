/*******************************
프로그램명: 배열 프로그램 2
작 성 자: 2019038054 김경민
작 성 일: 2022 03 22
프로그램 설명: 포인터를 이용한 배열 호출
********************************/ 
#include <stdio.h>

void print1 (int *ptr, int rows);       

int main()
{
    int one[] = {0,1,2,3,4};

    printf("one     = %p\n", one);      //one 배열의 주소
    printf("&one    = %p\n", &one);     //one 배열의 주소
    printf("&one[0] = %p\n", &one[0]);  //one[0]의 주소
    printf("\n");

    print1(&one[0], 5);                 
    
    printf("2019038054 김경민\n");
    return 0;
}

void print1(int *ptr, int rows)         //one[]을 *ptr로 호출
{
    int i;
    printf("Address \t Content\n");
    for(i=0;i<rows;i++)                 //ptr + i == one + i
        printf("%p \t %5d\n", ptr + i, *(ptr + i));
    printf("\n");
}