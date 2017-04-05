//LinkList.cpp
//定义单链表类

#include <iostream>
#include "LinkNode.h"
using namespace std;

template <class ElemType>
class LinkList {

public:
	LinkList();  //构造函数 [1]
	~LinkList();  //析构函数 [2]
	bool IsEmpty() const;  //判断链表是否为空表 [3]
	int Length() const;  //求链表长度 [4]
	void Clear();  //置位空表 [5]
	bool GetElem(ElemType&, int) const;  //表中取值 [6]
	bool SetElem(const ElemType&, int);  //表中存值 [7]
	int LocateElem(const ElemType&) const;  //查找表中符合条件的元素位置 [8]
	int LocatePrior(const ElemType&) const;  //查找表中符合条件的元素的前驱 [9]
	int LocateNext(const ElemType&) const;  //查找表中符合条件的元素的后继 [10]
	bool Insert(const ElemType&, int);  //在表中的指定位置插入 [11]
	bool Append(const ElemType&);  //在表尾插入 [12]
	bool Delete(ElemType &, int);  //删除表中的指定位置元素 [13]
	void Traverse() const;  //遍历输出单链表 [14]

private:
	int len;  //链表长度
	LinkNode<ElemType> *head;  //链表头指针
	LinkNode<ElemType> *tail;  //链表尾指针

};

//[1] 构造函数,单链表初始化
template <class ElemType>
LinkList<ElemType>::LinkList() {
	//链表长度为0,表头和表尾同时指向创建的空结点
	len = 0;
	head = tail = new LinkNode<ElemType>;
	head->next = NULL;
}

//[2] 析构函数,单链表结构销毁
template <class ElemType>
LinkList<ElemType>::~LinkList() {
	Clear();  //释放所有数据结点
	delete head;  //释放头结点
}

//[3] 判断链表是否为空表
template <class ElemType>
bool LinkList<ElemType>::IsEmpty() const {
	if (len > 0) {
		return true;
	}
	return false;
}

//[4] 求链表长度
template <class ElemType>
int LinkList<ElemType>::Length() const {
	return len;
}

//[5] 置单链表为空表
template <class ElemType>
void LinkList<ElemType>::Clear() {
	LinkNode<ElemType> *p, *q;
	p = head->next;
	while (p) {
		q = p->next;
		delete p;
		p = q;
	}
	tail = head;
	head->next = NULL;
	len = 0;
}

//[6] 取出单链表中序号为i的数据元素值
template <class ElemType>
bool LinkList<ElemType>::GetElem(ElemType &e, int i) const {
	if (i < 1 || i > len) {
		return false;
	}
	LinkNode<ElemType> *p = head->next;
	int k = 1;
	while (k < i) {
		p = p->next;
		++k;
	}
	e = p->data;
	return true;
}

//[7] 为单链表序号为i的数据元素赋值
template <class ElemType>
bool LinkList<ElemType>::SetElem(const ElemType &e, int i) {
	if (i < 1 || i > len) {
		return false;
	}
	LinkNode<ElemType> *p = head->next;
	int k = 1;
	while (k < i) {
		p = p->next;
		++k;
	}
	p->data = e;
	return true;
}

//[8] 在单链表中查找符合条件的元素位置
template <class ElemType>
int LinkList<ElemType>::LocateElem(const ElemType &e) const {
	LinkNode<ElemType> *p = head->next;
	int i = 1;
	while (p && p->data != e) {
		++i;
		p = p->next;
	}
	if (p) {
		return i;
	}
	return 0;
 }

 //[9] 在单链表中查找符合条件元素的前驱
 template <class ElemType>
 int LinkList<ElemType>::LocatePrior(const ElemType &e) const {
 	int i = LocateElem(e);
 	if (i > 1) {
 		return i - 1;
 	}
 	return 0;
 }

//[10] 在单链表中查找符合条件的元素的后继
 template <class ElemType>
 int LinkList<ElemType>::LocateNext(const ElemType &e) const {
 	int i = LocateElem(e);
 	if (i > 0 || i < len) {
 		return i + 1;
 	}
 	return 0;
 }

 //[11] 在单链表中第i个结点之前插入新的结点
 template <class ElemType>
 bool LinkList<ElemType>::Insert(const ElemType &e, int i) {
 	LinkNode<ElemType> *p, *q;
 	if (i < 1 || i > len + 1) {
 		return false;
 	}
 	q = new LinkNode<ElemType>;
 	q->data = e;
 	p = head;
 	int k = 1;
 	//将p指针移动到插入结点的前一个
 	while (k < i) {
 		p = p->next;
 		++k;
 	}
 	q->next = p->next;
 	p->next = q;
 	//如果在末尾插入,则将尾指针指向插入的新结点
 	if (i == len) {
 		tail = q;
 	}
 	++len;
 	return true;
 }

//[12] 在单链表结尾插入新结点
template <class ElemType>
bool LinkList<ElemType>::Append(const ElemType &e) {
	LinkNode<ElemType> *p = new LinkNode<ElemType>;
	p->data = e;
	tail->next = p;
	tail = p;
	tail->next = NULL;
	++len;
	return true;
}

//[13] 在单链表中删除指定第i个结点
template <class ElemType>
bool LinkList<ElemType>::Delete(ElemType &e, int i) {
	if (i < 1 || i > len) {
		return true;
	}
	LinkNode<ElemType> *p, *q;
	p = head;
	int k = 1;
	//将指针p移动到删除结点的前一个
	while (k < i) {
		p = p->next;
		++k;
	}
	//将指针q移动到删除的结点上
	q = p->next;
	p->next = q->next;
	e = q->data;
	if (q == tail) {
		tail = p;
	}
	--len;
	delete q;
	return true;
}

//[14] 遍历输出单链表各结点
template <class ElemType>
void LinkList<ElemType>::Traverse() const {
	LinkNode<ElemType> *p = head->next;
	while (p) {
		cout << p->data << ",";
		p = p->next;
	}
	cout << endl;
}


