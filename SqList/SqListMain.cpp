//SqListMain.cpp
//顺序表主函数,测试顺序表相应功能

#include <iostream>
#include "SqList.h"
using namespace std;
int main(void) {

	SqList<int> sqList(10);

	//向表尾追加5条记录
	for (int i = 0; i < 5; ++i) {
		if (!sqList.Append(i + 1)) {
			cout << "SqList APpend Error!" << endl;
		}
	}

	//循环获取顺序表中的值
	cout << "SqList GetElem: ";
	for (int j = 0; j < 5; ++j) {
		int tmp;
		if (!sqList.GetElem(tmp, j + 1)) {
			cout << "SqList GetElem Error!" << endl;
		}
		cout << tmp;
	}
	cout << endl;

	//获取顺序表的长度
	cout << "SqList Length: " << sqList.Length() << endl;

	//查找顺序表中的指定元素,如果存在则输出其位置以及对应的前驱和后继
	int searchElem = 3;
	cout << "SqList LocateElem: " << sqList.LocateElem(searchElem) << endl;
	cout << "SqList LocatePrior: " << sqList.LocatePrior(searchElem) << endl;
	cout << "SqList LocateNext: " << sqList.LocateNext(searchElem) << endl;

	//向表中的指定位置插入数据
	int insertValue = 999;
	int insertPosition = 4;
	if (sqList.Insert(insertValue, insertPosition)) {
		int tmp;
		sqList.GetElem(tmp, insertPosition);
		cout << "Insert Value: " << tmp  << " Success!" << endl;
	} else {
		cout << "SqList Insert Error!" << endl;
	}

	//删除指定位置的元素
	int deletePosition = 4;
	int deleteElem;
	if (sqList.Delete(deleteElem, deletePosition)) {
		cout << deleteElem << " Delete Success!" << endl;
	} else {
		cout << "Delete Error!" << endl;
	}

	//遍历打印顺序表
	sqList.Traverse();
	
	return 0;
}