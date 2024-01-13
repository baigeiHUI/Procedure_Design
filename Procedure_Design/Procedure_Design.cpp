#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include"OperatorStack.h"
#include"Queue.h"

/*
***
     1.本程序可对输入算式进行一定程度合法性判断.所用主要数据结构如下:
            
		1.1	操作数栈:  栈底填0,top值即代表栈中数据个数
        1.2 运算符栈:  栈底填#,top值代表栈中数据个数

	 2.本程序支持从文件读入字符串,但是只能逐行读入且不能有换行键出现.

	 3.本程序支持手动输入与直接测试.
	 
***
*/

//获取运算符优先级
int Get_Prior(char op);
//主过程
void Justice(char* fulmula);
//进行一次计算
void DealPartly(Operator_Stack* NumStack, Operator_Stack* OperatorStack);
//Justice调用,根据运算结果生成最终结果
void ResultGen(Operator_Stack *NumStack);
//括号匹配
void ParenMatching(char* S);
//获取括号优先级
int Get_ParenPrior(char op);
void Show(char* test);
//读取文件
void DocuRead();
//输入
void Input_Based();
//直接测试
void Directly_Run();

char test1[] = { "{-1+[-2-(-1)]}/[(-1-2)*(-1)]=" };
char test2[] = {"{17-[246*15+(41-6)]}/[148*(66+5)]-12+(-1)="};
char test3[] = { "[(17-5)+[36*{8*9}]]-(4+4)=" };
char test4[] = {"[18+(67*4-3)+32*5*4(])*[16+(2*4)]="};
char test5[] = {"{17-246*15+(41-6)[}/[148]*(66+5)]-12+(-1)="};
void main() {
	int flag;
	printf("请选择操作:\n输入1读取文件进行测试\n输入2进行手动算式输入测试\n输入3进行默认测试\n");
	scanf_s("%d", &flag);
	if (flag == 1)
		DocuRead();
	else if (flag == 2)
		Input_Based();
	else if (flag == 3)
		Directly_Run();
	else
		printf("输入有误!\n");



	




}
int Get_Prior(char op) {
	if (op == '/' || op == '*')
		return 2;
	else if (op == '+' || op == '-')
		return 1;
	else return 0;
}
void Justice(char* fulmula){
	Operator_Stack NumStack, OperatorStack;
	NumStack.Init();
	OperatorStack.Init();
	char* p = fulmula;
	while (*p != '\0') {
		if (isdigit(*p)) {       //如果数字匹配
			NumStack.Push('a');
			do { p++; }
			while (isdigit(*p)||*p=='.');
		}
		else {                   //如果运算符匹配
			
			if (*p == '=') {
				while (!OperatorStack.IsEmpty()) //如果运算符栈没有空,就计算下去
					DealPartly(&NumStack,&OperatorStack);
			}
			else {                //匹配正常运算符
				if (*p == '-')       //如果匹配到-号
				{
					if (p == fulmula)   //如果是一号位
						NumStack.Push('a');
					else {             //如果减号不是一号位
						char* tem = p;
						tem--;
						if (*tem == '(' || *tem == '[' || *tem == '{')//如果减号前一位置是括号
							NumStack.Push('a');      //压数
					}
				}
				if (*p == '(' || *p == '[' || *p == '{') //左括号直接压栈
					OperatorStack.Push(*p);
				else if (*p == ')')
				{
					while (OperatorStack.Get_Top() != '(')
						DealPartly(&NumStack, &OperatorStack);
					OperatorStack.Pop();
				}
				else if (*p == ']')
				{
					while (OperatorStack.Get_Top() != '[')
						DealPartly(&NumStack, &OperatorStack);
					OperatorStack.Pop();
				}
				else if (*p == '}')
				{
					while (OperatorStack.Get_Top() != '{')
						DealPartly(&NumStack, &OperatorStack);
					OperatorStack.Pop();
				}
				
				else if (Get_Prior(*p) > Get_Prior(OperatorStack.Get_Top()))    //符号:若符号优先级高于栈顶运算符
					OperatorStack.Push(*p);                                     //符号压栈
				else {
					DealPartly(&NumStack, &OperatorStack);   //否则计算一次
					OperatorStack.Push(*p); //符号入栈
				}
			}  
			p++;
		}
		
	}
	ResultGen(&NumStack);
  

}
void DealPartly(Operator_Stack *NumStack,Operator_Stack *OperatorStack) {

	if(!NumStack->IsEmpty())
	NumStack->Pop();
	if(!OperatorStack->IsEmpty())
	OperatorStack->Pop();
	
}
void ResultGen(Operator_Stack *NumStack) {
	if (NumStack->top == 1)
		printf("it's ok!\n\n");
	else {
		printf("未知错误!建议重新检查算式!\n\n");
		exit(1);
	}

}
void ParenMatching(char* S) {
	Operator_Stack ParenStack;
	ParenStack.Init();
	char* tem = S;
	while (*tem != '\0') {
		if (*tem == '{' || *tem == '[' || *tem == '(')
			if (Get_ParenPrior(*tem) >= Get_ParenPrior(ParenStack.Get_Top())) //括号级别高或者相同(同小括号)
				ParenStack.Push(*tem);
			else
			{
				printf("算式括号嵌套错误!\n");
				exit(1);
			}
		if (*tem == ')') {
			if (ParenStack.Get_Top() != '(') {
				printf("算式小括号匹配错误!\n");
				exit(1);
			}
			else
				ParenStack.Pop();

		}
		if (*tem == ']') {
			if (ParenStack.Get_Top() != '[') {
				printf("算式中括号匹配错误!\n");
				exit(1);
			}
			else
				ParenStack.Pop();

		}

		if (*tem == '}') {
			if (ParenStack.Get_Top() != '{') {
				printf("算式大括号匹配错误!\n");
				exit(1);
			}
			else
				ParenStack.Pop();

		}


		tem++;
	}
}
int Get_ParenPrior(char op) {
	if (op == '{')
		return 1;
	else if (op == '[')
		return 2;
	else if (op == '(')
		return 3;
	else return 0;
}
void Show(char* test) {
	printf("Input:\n%s\n", test);
	printf("Result:\n");
	ParenMatching(test);
	Justice(test);
}
void DocuRead() {
	char S[100];
	FILE* fptr;
	errno_t err = fopen_s(&fptr, "C:/Users/hp/Desktop/C_input.txt", "r");
	if (err != 0) {
		printf("无法打开文件!\n");
		exit(1);
	}
	else {
		fgets(S, sizeof(S), fptr);
		S[strlen(S)] = '\0';
		Show(S);

	}
}
void Input_Based() {


	char* S;
	S = (char*)malloc(sizeof(char) * 100);
	printf("Input your fulmula :\n");
	scanf_s("%s", S, 100);
	Show(S);
}
void Directly_Run() {

	Show(test1);
	Show(test2);
	Show(test3);
	Show(test4);
	Show(test5);
}






