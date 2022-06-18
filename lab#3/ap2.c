/*******************************
프로그램명: 배열과 포인터 2
작 성 자: 2019038054 김경민
작 성 일: 2022 03 22
프로그램 설명: 배열의 이름에 관한 특징
********************************/ 
#include <stdio.h>

void main()
{
    int list[5];

    list[0] = 10;  

    printf("2019038054 \t\t  김경민\n");

    printf("list[0] \t\t= %d\n", list[0]);          //list[0]에 저장된 값 = 10
    printf("address of list \t= %p\n", list);       //list 주소
    printf("address of list[0] \t= %p\n", &list[0]);//list[0]주소
    printf("address of list + 0 \t= %p\n", list+0); //list+0번째 주소
    printf("address of list + 1 \t= %p\n", list+1); //lsit+1번째 주소
    printf("address of list + 2 \t= %p\n", list+2); //list+2번째 주소
    printf("address of list + 3 \t= %p\n", list+3); //list+3번째 주소
    printf("address of list + 4 \t= %p\n", list+4); //list+4번째 주소
    printf("address of list[4] \t= %p\n", &list[4]);//list[4]의 주소

}