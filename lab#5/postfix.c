/* postfix.c
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */
/*******************************
프로그램명: 후위표기법
작 성 자: 2019038054 김경민
작 성 일: 2022 04 07 ~ 2022 04 09
프로그램 설명: 스택을 활용한 후위표기법 함수
********************************/ 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixpush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	char command;
	printf("\n------------------[김경민]--------[2019038054]------------------\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

/* postfix 스택에 x를 푸쉬 */
void postfixPush(char x) {
	//postfix 탑을 증가시킨 후 x값 기입
    postfixStack[++postfixStackTop] = x;
}

/* postfix 스택에서 x를 팝 */
char postfixPop() {
    char x;
	//스택이 공백인 경우 NULL값 리턴
    if(postfixStackTop == -1)
        return '\0';
	//postfix 탑에서 x를 뺀 후 감소
    else {
    	x = postfixStack[postfixStackTop--];
    }
    return x;
}

/* evalstack에 탑에 푸쉬 */
void evalPush(int x) {
	//eval 스택의 탑을 증가시킨 후 x값 기입
    evalStack[++evalStackTop] = x;
}

/* evalstack에 탑을 팝  */
int evalPop() {
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}

/*
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix() {
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

/* symbol이 연산자인지 피연산자인지 구별*/
precedence getToken(char symbol) {
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x) {
	return getToken(x);
}

/* 문자하나를 전달받아, postfixExp에 추가 */
void charCat(char* c) {
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/*
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix() {
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0')
	{
		//피연산자일시 postfix
		if(getPriority(*exp)==operand){
			x = *exp;
			charCat(&x);
		}
		// *exp == '(' 스택에 푸쉬
		else if(getPriority(*exp)==lparen){
			postfixPush(*exp);
		}
		// *exp == ')' 스택에 푸시한 연산자들을 팝 '('를 만날때까지
		else if(getPriority(*exp)==rparen){
			while((x = postfixPop()) != '('){
				charCat(&x);
			}
		}
		else {	//스택의 탑에 있는 연산자가 *exp 문자와 같거나 클때까지 스택을 팝
			while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)){
				x = postfixPop(); 
				charCat(&x);
			}
			//스택의 탑에 연산자보다 작을 시 입력받은 문자 푸쉬
			postfixPush(*exp);
		}
		exp++;
	}
	//스택이 공백이 될때까지 팝
	while(postfixStackTop != -1){
		x = postfixPop();
		charCat(&x);
	}
}

void debug() {
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}
/* 모든 정보들을 초기화 */
void reset() {
	infixExp[0] = '\0';	
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation() {
	//피연산자1, 피연산자2
	int opr1, opr2;
	
	int length = strlen(postfixExp); //postfixExp에 저장된 문자열 만큼 길이 할당
	char symbol;	//연산자 피연산자 구별 문자
	evalStackTop = -1;

	for(int i = 0; i < length; i++)
	{
		symbol = postfixExp[i];
		if(getToken(symbol) == operand) { //symbol이 operand 경우
			evalPush(symbol - '0');	//입력받은 문자 '1'~'9'를 '0'으로 빼면 1~9가 된다.
		}
		else {	//symbol이 '+', '-', '*', '/' 경우
			opr2 = evalPop(); //evalstack 탑에 위치한 나중에 push한 피연산자2 push
			opr1 = evalPop(); //evalstack 에서 먼저 pop된 피연산자1 push

			switch(getToken(symbol)) { /* symbol값에 따라 연산 실행 */
			case plus: evalPush(opr1 + opr2); break;
			case minus: evalPush(opr1 - opr2); break;
			case times: evalPush(opr1 * opr2); break;
			case divide: evalPush(opr1 / opr2); break;
			default: break;
			}
		}
	}
	evalResult = evalPop(); //계산결과 저장
}

