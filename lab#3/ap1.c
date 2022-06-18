/*******************************
프로그램명: 배열과 포인터 1
작 성 자: 2019038054 김경민
작 성 일: 2022 03 22
프로그램 설명: 배열과 포인터배열의 특징
********************************/ 
#include <stdio.h>
#include <stdlib.h>

void main()
{
    int list[5];
    int *plist[5] = {NULL,};

    plist[0]=(int*)malloc(sizeof(int));

    list[0]= 1;
    list[1]= 100;
    *plist[0]=200;

    printf("value of list[0] = %d\n", list[0]);     //list[0]의 값 = 1 출력
    printf("address of list[0] = %p\n", &list[0]);  //list[0]의 주소
    printf("value of list = %p\n", list);           //list의 주소
    printf("address of list (&list) = %p\n", &list);//list의 주소

    printf("\n----------------------------------------\n");
    printf("\t2019038054 김경민"); 
    printf("\n----------------------------------------\n\n");

    printf("value of list[1] = %d\n", list[1]);     //list[1]의 값 = 100
    printf("address of list[1] = %p\n", &list[1]);  //list[1]의 주소 = list[0] + 4byte(int)
    printf("value of *(list+1) = %d\n", *(list + 1));//*(list+1) = list[1] = 100
    printf("address of list+1 = %p\n", list+1);     //list+1 = &list[1] = list[1]주소

    printf("\n----------------------------------------\n\n");
    printf("value of *plist[0] = %d\n", *plist[0]); //plist[0]의 값 = 200
    printf("&plist[0] = %p\n", &plist[0]);          //plist[0]주소
    printf("&plist = %p\n", &plist);                //plist의주소
    printf("plist = %p\n", plist);                  //plist
    printf("plist[0] = %p\n", plist[0]);            //plist[0]이 가리키는 주소 = 200이 저장된 곳
    printf("plist[1] = %p\n", plist[1]);            //plist[1]이 가리키는 주소 = NULL
    printf("plist[2] = %p\n", plist[2]);            //plist[2]이 가리키는 주소 = NULL
    printf("plist[3] = %p\n", plist[3]);            //plist[3]이 가리키는 주소 = NULL
    printf("plist[4] = %p\n", plist[4]);            //plist[4]이 가리키는 주소 = NULL

    free(plist[0]);
}     