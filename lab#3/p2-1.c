/*******************************
프로그램명: 배열 프로그램 1
작 성 자: 2019038054 김경민
작 성 일: 2022 03 22
프로그램 설명: 배열을 호출했을 때 동작 원리
********************************/ 
#include <stdio.h>
#define MAX_SIZE 100

float sum(float [], int);
float input[MAX_SIZE], answer;
int i;

void main(void)
{
    for(i=0; i < MAX_SIZE; i++)
        input[i] = i;                               //각 n번째 배열에 n을 대입

    /* for checking call by reference */
    printf("address of input = %p\n", input);       //input의 주소 출력

    answer = sum(input, MAX_SIZE);                  //input[] 배열들의 총 합 함수
    printf("The sum is: %f\n", answer);             //return 받은 tempsum의 값 출력
    printf("2019038054 김경민\n");
}

float sum(float list[], int n)                      //input배열을 list로 주소를 넘김
{
    printf("value of list = %p\n", list);           //list의 값 = input의 주소
    printf("address of list = %p\n\n", &list);      //list의 주소

    int i;
    float tempsum = 0;
    for(i = 0; i < n; i++)
        tempsum += list[i];                         //tempsum = tempsum + list[i]
    return tempsum;
}