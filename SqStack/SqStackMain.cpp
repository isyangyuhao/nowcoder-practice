//SqStackMain.cpp
//顺序栈主函数

#include <iostream>
#include "SqStack.h"
using namespace std;

int main(void) {

	SqStack<int> sqStack(5);

	//入栈
	for (int i = 1; i <= 5; ++i) {
		sqStack.Push(i);
	}

	//取栈长度
	cout << "SqStack Length: " <<sqStack.Length() << endl;

	//出栈
	sqStack.Pop();

	//取栈顶元素
	int topElem;
	topElem = sqStack.Top();
	cout << "SqStack Top: " << sqStack.Top() << endl;

	return 0;
}