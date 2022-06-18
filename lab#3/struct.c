/*******************************
프로그램명: 구조체
작 성 자: 2019038054 김경민
작 성 일: 2022 03 23
프로그램 설명: struct와 typedef를 이용한 구조체 특성 파악
********************************/ 
#include <stdio.h>

struct student1 {
    char lastName;
    int studentId;
    char grade;
};

typedef struct {
    char lastName;
    int studentId;
    char grade;
} student2;

int main() {
    //struct는 변수 선언 시 struct를 꼭 함께 사용
    struct student1 st1 = {'A', 100, 'A'};      //순서는 struct에서 선언한 순서대로 {lastname, studentId, grade}이다.

    printf("st1.lastName = %c\n", st1.lastName);        
    printf("st1.studentId = %d\n", st1.studentId);
    printf("st1.grade = %c\n", st1.grade);

    student2 st2 = {'B', 200, 'B'};             //typedef struct는 struct를 안 붙여도 가능

    printf("\nst2.lastName = %c\n", st2.lastName);
    printf("st2.studentId = %d\n", st2.studentId);
    printf("st2.grade = %c\n", st2.grade);

    printf("\n2019038054 김경민\n");

    student2 st3;   //typedef
    st3 = st2;      //st2의 구성을 st3에 복사 {'B', 200, 'B'}
                    //복사가 되는지 확인
    printf("\nst3.lastName = %c\n", st3.lastName);
    printf("st3.studentId = %d\n", st3.studentId);
    printf("st3.grade = %c\n", st3.grade);

    
       /* equality test */
    //if(st3 == st2) /* not working */
    //    printf("equal\n");
    //else
    //    printf("not equal\n");
        
    return 0;
}