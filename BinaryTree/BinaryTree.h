//BinaryTree.h
//二叉树类

#include <iostream>
#include <stack>
#include "BTNode.h"
using namespace std;

template <class ElemType>
class BinaryTree {

public:
	//构造函数
	BinaryTree():m_root(NULL) {};
	//析构函数
	~BinaryTree();
	//先序创建二叉树接口函数; arg1:建立二叉树的各节点字符, arg2:代表空节点的字符
	void Create1(ElemType ch[], const ElemType &c);
	//输出二叉树子节点接口函数
	void Child(const ElemType &);
	//求二叉树深度接口函数
	int Depth();
	//求二叉树叶子节点数接口函数
	int Leafs();
	//利用递归先序遍历二叉树接口函数
	void PreorderTraverse();
	//利用栈中序遍历二叉树
	void InorderTraverseNonRecursive();

private:
	//二叉树根节点指针
	BTNode<ElemType> *m_root;
	//销毁二叉树
	void _Destroy(BTNode<ElemType> * &);
	//先序创建二叉树; arg1:节点引用, arg2:建立二叉树的各节点字符, arg3:代表空节点的字符, arg4:字符数组索引
	void _Create1(BTNode<ElemType> * &, ElemType ch[], const ElemType &, int &);
	//二叉树查找函数
	BTNode<ElemType> * _Locate(BTNode<ElemType> *, const ElemType &);
	//求二叉树深度
	int _Depth(BTNode<ElemType> *);
	//求二叉树叶子节点数
	int _Leafs(BTNode<ElemType> *);
	//利用递归先序遍历二叉树
	void _PreorderTraverse(BTNode<ElemType> *);
};

//先序创建二叉树实现
template <class ElemType>
void BinaryTree<ElemType>::_Create1(BTNode<ElemType> * &T, ElemType ch[], const ElemType &c, int &i) {
	if(ch[i] == c) {
		//如果当前创建的节点为空节点,则将T置空
		T = NULL;
	} else {
		//如果当前节点不为空结点,则创建BTNode,将对应字符值赋给节点的data属性
		T = new BTNode<ElemType>;
		T->data = ch[i];
		//递归创建当前节点的所有左子树
		_Create1(T->lchild, ch, c, ++i);
		//递归创建当前节点的所有右子树
		_Create1(T->rchild, ch, c, ++i);
	}
}
template <class ElemType>
void BinaryTree<ElemType>::Create1(ElemType ch[], const ElemType &c) {
	int i = 0;
	_Create1(m_root, ch, c, i);
}

//销毁二叉树实现
template <class ElemType>
void BinaryTree<ElemType>::_Destroy(BTNode<ElemType> * &T) {
	//利用后序遍历删除二叉树各节点
	if (T) {
		_Destroy(T->rchild);
		_Destroy(T->lchild);
		delete T;
	}
	T = NULL;
}
template <class ElemType>
BinaryTree<ElemType>::~BinaryTree() {
	_Destroy(m_root);
}

//输出二叉树儿子节点实现
template <class ElemType>
BTNode<ElemType> * BinaryTree<ElemType>::_Locate(BTNode<ElemType> *T, const ElemType &e) {
	//先序递归查找每个节点是否符合查找条件
	if (!T || T->data == e) {
		return T;
	}
	BTNode<ElemType> *q;
	q = _Locate(T->lchild, e);
	if (q) {
		return q;
	}
	q = _Locate(T->rchild, e);
	return q;
}
template <class ElemType>
void BinaryTree<ElemType>::Child(const ElemType &e) {
	BTNode<ElemType> * serachNode = _Locate(m_root, e);
	if (serachNode) {
		if (serachNode->lchild) {
			cout << "left child is " << serachNode->lchild->data << endl; 
		} else {
			cout << "not found left child!" << endl;
		}
		if (serachNode->rchild) {
			cout << "right child is " << serachNode->rchild->data << endl;
		} else {
			cout << "not found right child!" << endl;
		}
	} else {
		cout << "not found this node!" << endl;
	}
}

//求二叉树深度实现
template <class ElemType>
int BinaryTree<ElemType>::_Depth(BTNode<ElemType> *T) {
	if (!T) {
		return 0;
	}
	//递归计算出根节点的左子树和右子树层数
	int h1 = _Depth(T->lchild);
	int h2 = _Depth(T->rchild);
	//比较出两侧子树最大的一颗,加上根节点则为二叉树深度
	if (h1 > h2) {
		return h1 + 1;
	} else {
		return h2 + 1;
	}
}
template <class ElemType>
int BinaryTree<ElemType>::Depth() {
	return _Depth(m_root);
}

//求二叉树叶子节点数实现
template <class ElemType>
int BinaryTree<ElemType>::_Leafs(BTNode<ElemType> *T) {
	if (!T) {
		return 0;
	}
	//如果当前节点不存在左孩子和右孩子,则属于叶子节点
	if (!T->lchild && !T->rchild) {
		return 1;
	}
	int h1 = _Leafs(T->lchild);
	int h2 = _Leafs(T->rchild);
	return h1 + h2;
}
template <class ElemType>
int BinaryTree<ElemType>::Leafs() {
	return _Leafs(m_root);
}

//利用递归先序遍历二叉树实现
template <class ElemType>
void BinaryTree<ElemType>::_PreorderTraverse(BTNode<ElemType> *T) {
	if (T) {
		cout << T->data << " ";
		//先序遍历递归输出
		_PreorderTraverse(T->lchild);
		_PreorderTraverse(T->rchild);
	}
}
template <class ElemType>
void BinaryTree<ElemType>::PreorderTraverse() {
	_PreorderTraverse(m_root);
}

//利用栈中序遍历二叉树实现
template <class ElemType>
void BinaryTree<ElemType>::InorderTraverseNonRecursive() {
	stack<BTNode<ElemType> *> S;
	//根节点入栈
	S.push(m_root);
	while (!S.empty()) {
		BTNode<ElemType> *p;
		p = S.top();
		//向左走向尽头
		while (p) {
			p = p->lchild;
			S.push(p);
		}
		//空指针出栈
		S.pop();
		if (!S.empty()) {
			//访问节点
			p = S.top();
			S.pop();
			cout << p->data << " ";
			//向右一步
			S.push(p->rchild);
		}
	}
}




