#include <stdio.h>
int main()
{
    int i;
    int *ptr;
    int **dptr;
    
    i = 1234;
    
    printf("[checking values before ptr = &i] \n");     // ptr이 i의 주소값을 받기 전
    printf("value of i == %d\n", i);                    // i의 값 = 1234
    printf("address of i == %p\n", &i);                 // i의 주소
    printf("value of ptr == %p\n", ptr);                // ptr의 값 (NULL)
    printf("address of ptr == %p\n", &ptr);             // ptr의 주소
   
    ptr = &i; /* ptr is now holding the address of i */
    
    printf("\n[checking values after ptr = &i] \n");    // ptr이 i의 주소값을 가짐
    printf("value of i == %d\n", i);                    // i의 값 = 1234
    printf("address of i == %p\n", &i);                 // i의 주소
    printf("value of ptr == %p\n", ptr);                // ptr의 값 (address of i)
    printf("address of ptr == %p\n", &ptr);             // ptr의 주소값
    printf("value of *ptr == %d\n", *ptr);              // ptr의 참조값 (value of i)

    dptr = &ptr; /* dptr is now holding the address of ptr */
   
    printf("\n[checking values after dptr = &ptr] \n"); // dptr이 ptr의 주소값을 가짐
    printf("value of i == %d\n", i);                    // i의 값 = 1234
    printf("address of i == %p\n", &i);                 // i의 주소
    printf("value of ptr == %p\n", ptr);                // ptr의 값 (address of i)  
    printf("address of ptr == %p\n", &ptr);             // ptr의 주소값
    printf("value of *ptr == %d\n", *ptr);              // ptr의 참조값(value of i)
    printf("value of dptr == %p\n", dptr);              // dptr의 값 (address of ptr)
    printf("address of dptr == %p\n", &dptr);            // dptr의 주소
    printf("value of *dptr == %p\n", *dptr);            // dptr의 1차 참조값(dptr->ptr)
    printf("value of **dptr == %d\n", **dptr);          // dptr의 2차 참조값(dptr->ptr->i)
    
    printf("\n\t2019038054 김경민\n");

    *ptr = 7777; /* changing the value of *ptr */       // i에 7777 저장
    
    printf("\n[after *ptr = 7777] \n");                 //ptr가 가리키는 i의 값을 7777로 바꿈 (value of i)
    printf("value of i == %d\n", i);                    // i의 값
    printf("value of *ptr == %d\n", *ptr);              // ptr의 참조값(value of i)
    printf("value of **dptr == %d\n", **dptr);          // dptr의 2차 참조값(value of i)

    **dptr = 8888; /* changing the value of **dptr */   // i에 8888 저장

    printf("\n[after **dptr = 8888] \n");               //dptr가 가리키는 2차 참조값(i)을 8888로 바꿈 (value of i)
    printf("value of i == %d\n", i);                    // i의 값
    printf("value of *ptr == %d\n", *ptr);              // ptr의 참조값(value of i)
    printf("value of **dptr == %d\n", **dptr);          // dptr의 2차 참조값(value of i)

    return 0;
}