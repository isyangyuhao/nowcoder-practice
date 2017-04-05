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

	cout << "使用先序方式所需建树的数据(空指针用#表示) : " << endl;
	cin >> ch1;
	bt1.Create1(ch1, c);
	cout << endl;
	
	char loc = 'B';
	p = bt1.Locate(loc);
	cout << "B结点左孩子的值为 : ";
	q = bt1.LeftChild(p);
	if(q) {
		cout << q->data << endl;
	} else {
		cout << "not found !" << endl;
	}
	cout << "B结点右孩子的值为 : ";
	q = bt1.RightChild(p);
	if(q) {
		cout << q->data << endl;
	} else {
		cout << "not found !" << endl;
	}

	cout << "该二叉树的深度为 : " << bt1.Depth() << endl;

	cout << "该二叉树叶子结点个数为 : " << bt1.CountLeaf() << endl;

	cout << "递归遍历 : " << endl;
	bt1.PreorderTraverse(Print);
	cout << endl;

	cout << "非递归遍历 : " << endl;
	bt1.InorderTraverseNonRecursive(Print); 

	cout << endl;

	return 0;
}