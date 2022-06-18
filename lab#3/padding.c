/*******************************
프로그램명: 구조체의 공간활용(패딩)
작 성 자: 2019038054 김경민
작 성 일: 2022 03 23
프로그램 설명: 빈 공간이 생길 시 컴퓨터에서 어떻게 동작하는지 확인한다
********************************/ 
#include <stdio.h>

struct student {
    char lastName[13];  //13bytes
    int studentId;      //4bytes
    short grade;        //2bytes
};
int main()
{
    struct student pst;
    
    printf("size of student = %ld\n", sizeof(struct student));  //실제 student struct가 갖는 메모리 크기
    printf("size of int = %ld\n", sizeof(int));                 //integer 메모리 크기
    printf("size of short = %ld\n", sizeof(short));             //short 메모리 크기

    printf("\n2019038054 김경민\n");
    return 0;
}
