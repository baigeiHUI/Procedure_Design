#include"OperatorStack.h"
void Operator_Stack::Init() {
    for (int i = 0; i < maxsize; i++)
        this->Data[i] = '\0';
    this->Data[0] = '#';
    this->top = 0;
}
void  Operator_Stack::Pop() {
    if (this->top == 0) {
        printf("%s\n", "栈已为空!");
        return;
    }
    this->Data[this->top--] = '\0';


}
void  Operator_Stack::Push(char elem) {
    if (this->top + 1 == maxsize) {
        printf("%s\n", "此栈已满!");
        return;
    }
    this->Data[++this->top] = elem;
}
int Operator_Stack::IsFull() {
    if (this->top + 1 == maxsize)
        return 1;
    else
        return 0;
}
char  Operator_Stack::Get_Top() {
    return this->Data[this->top];
}
void Operator_Stack::Clear() {
    for (int i = 0; i < maxsize; i++)
        this->Data[i] = '\0';
    this->top = 0;

}
int Operator_Stack::IsEmpty() {
    if (this->Data[top] == '#')
        return 1;
    else
        return 0;
}


