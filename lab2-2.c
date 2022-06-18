#include <stdio.h>
int main()
{
    int i;
    int *ptr;
    int **dptr;
    
    i = 1234;
    
    printf("[checking values before ptr = &i] \n");     // ptr�� i�� �ּҰ��� �ޱ� ��
    printf("value of i == %d\n", i);                    // i�� �� = 1234
    printf("address of i == %p\n", &i);                 // i�� �ּ�
    printf("value of ptr == %p\n", ptr);                // ptr�� �� (NULL)
    printf("address of ptr == %p\n", &ptr);             // ptr�� �ּ�
   
    ptr = &i; /* ptr is now holding the address of i */
    
    printf("\n[checking values after ptr = &i] \n");    // ptr�� i�� �ּҰ��� ����
    printf("value of i == %d\n", i);                    // i�� �� = 1234
    printf("address of i == %p\n", &i);                 // i�� �ּ�
    printf("value of ptr == %p\n", ptr);                // ptr�� �� (address of i)
    printf("address of ptr == %p\n", &ptr);             // ptr�� �ּҰ�
    printf("value of *ptr == %d\n", *ptr);              // ptr�� ������ (value of i)

    dptr = &ptr; /* dptr is now holding the address of ptr */
   
    printf("\n[checking values after dptr = &ptr] \n"); // dptr�� ptr�� �ּҰ��� ����
    printf("value of i == %d\n", i);                    // i�� �� = 1234
    printf("address of i == %p\n", &i);                 // i�� �ּ�
    printf("value of ptr == %p\n", ptr);                // ptr�� �� (address of i)  
    printf("address of ptr == %p\n", &ptr);             // ptr�� �ּҰ�
    printf("value of *ptr == %d\n", *ptr);              // ptr�� ������(value of i)
    printf("value of dptr == %p\n", dptr);              // dptr�� �� (address of ptr)
    printf("address of dptr == %p\n", &dptr);            // dptr�� �ּ�
    printf("value of *dptr == %p\n", *dptr);            // dptr�� 1�� ������(dptr->ptr)
    printf("value of **dptr == %d\n", **dptr);          // dptr�� 2�� ������(dptr->ptr->i)
    
    printf("\n\t2019038054 ����\n");

    *ptr = 7777; /* changing the value of *ptr */       // i�� 7777 ����
    
    printf("\n[after *ptr = 7777] \n");                 //ptr�� ����Ű�� i�� ���� 7777�� �ٲ� (value of i)
    printf("value of i == %d\n", i);                    // i�� ��
    printf("value of *ptr == %d\n", *ptr);              // ptr�� ������(value of i)
    printf("value of **dptr == %d\n", **dptr);          // dptr�� 2�� ������(value of i)

    **dptr = 8888; /* changing the value of **dptr */   // i�� 8888 ����

    printf("\n[after **dptr = 8888] \n");               //dptr�� ����Ű�� 2�� ������(i)�� 8888�� �ٲ� (value of i)
    printf("value of i == %d\n", i);                    // i�� ��
    printf("value of *ptr == %d\n", *ptr);              // ptr�� ������(value of i)
    printf("value of **dptr == %d\n", **dptr);          // dptr�� 2�� ������(value of i)

    return 0;
}