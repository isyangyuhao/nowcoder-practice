#include <iostream>
#include <string>
#include "BinaryTree.h"
using namespace std;

void Print(const char &c) {
	cout << c << " ";
}

int main(void) {

	BinaryTree<char> bt1;
	char c = '#', e, ch1[256];
	BTNode<char> *p, *q;
	int nodeNum = 0;

	cout << "ʹ������ʽ���轨��������(��ָ����#��ʾ) : " << endl;
	cin >> ch1;
	bt1.Create1(ch1, c);
	cout << endl;
	
	char loc = 'B';
	p = bt1.Locate(loc);
	cout << "B������ӵ�ֵΪ : ";
	q = bt1.LeftChild(p);
	if(q) {
		cout << q->data << endl;
	} else {
		cout << "not found !" << endl;
	}
	cout << "B����Һ��ӵ�ֵΪ : ";
	q = bt1.RightChild(p);
	if(q) {
		cout << q->data << endl;
	} else {
		cout << "not found !" << endl;
	}

	cout << "�ö����������Ϊ : " << bt1.Depth() << endl;

	cout << "�ö�����Ҷ�ӽ�����Ϊ : " << bt1.CountLeaf() << endl;

	cout << "�ݹ���� : " << endl;
	bt1.PreorderTraverse(Print);
	cout << endl;

	cout << "�ǵݹ���� : " << endl;
	bt1.InorderTraverseNonRecursive(Print); 

	cout << endl;

	return 0;
}