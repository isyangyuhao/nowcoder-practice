//BinaryTree.cpp
//二叉树主函数

#include <iostream>
#include "BinaryTree.h"
using namespace std;

int main(void) {

	BinaryTree<char> tree;

	//先序创建二叉树
	char ch[17] = {'a','b','d','#','#','e','g','#','h','#','#','#','c','f','#','#','#'};
	tree.Create1(ch, '#');

	//输出节点的子节点
	tree.Child('b');

	//输出二叉树的深度
	cout << "Tree Depth is " << tree.Depth() << endl;

	//输出二叉树的叶子节点数
	cout << "Tree Leafs is " << tree.Leafs() << endl;

	//利用递归先序遍历二叉树
	tree.PreorderTraverse();
	cout << endl;

	//利用栈中序遍历二叉树
	tree.InorderTraverseNonRecursive();
	cout << endl;

	return 0;
}