//LinkListMain.cpp
//单链表主函数,测试单链表相关方法

#include <iostream>
#include "LinkList.h"
using namespace std;
int main(void) {

	LinkList<int> linkList;

	//向单链表的末尾追加结点
	for (int i = 1; i <= 5; ++i) {
		if (!linkList.Append(i)) {
			cout << "Append Error!" << endl;
		}
	}
	cout << "LinkList Length: " << linkList.Length() << endl;

	//设置指定位置单链表的值
	linkList.SetElem(999, 3);

	//取出单链表指定位置的值
	int searchResult;
	int searchPosition = 3;
	linkList.GetElem(searchResult, searchPosition);
	cout << "LinkList GetElem: " << searchResult << endl;

	//查找指定元素所在位置
	cout << "LinkList LocateElem: " << linkList.LocateElem(2) << endl;
	cout << "LinkList LocatePrior: " << linkList.LocatePrior(2) << endl;
	cout << "LinkList LocateNext: " << linkList.LocateNext(2) << endl;

	//在指定位置插入新结点
	if (!linkList.Insert(666, 3)) {
		cout << "LinkList Insert Error!" << endl;
	}

	//删除指定结点
	int deleteElem;
	if (linkList.Delete(deleteElem, 3)) {
		cout << deleteElem << " Delete Success!" << endl;
	} else {
		cout << "Delete Error!" << endl;
	}

	//遍历输出单链表各结点
	linkList.Traverse();

	return 0;
}