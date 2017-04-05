//SqQueueMain.cpp
//循环队列主函数

#include <iostream>
#include "SqQueue.h"
using namespace std;

int main(void) {

	SqQueue<int> sqQueue(5);

	//入队
	for (int i = 1; i <= 5; ++i) {
		sqQueue.Append(i);
	}

	//求队列长度
	cout << "SqQueue Length: " << sqQueue.Length() << endl;

	//出队
	sqQueue.Remove();

	//取队头元素
	int frontElem;
	frontElem = sqQueue.GetHead();
	cout << "SqQueue HeadElem: " << frontElem << endl;

	//取对尾元素
	int rearElem;
	rearElem = sqQueue.GetTail();
	cout << "SqQueue TailElem: " << rearElem << endl;

	return 0;
}