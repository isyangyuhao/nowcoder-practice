#include <iostream>
#include <string>
#include <stack>
using namespace std;

void Print(const char &c) {
	cout << c << " ";
}

//定义树结点
template <typename ElemType> struct BTnode {
	ElemType data;
	BTnode<ElemType> *Lchild, *Rchild;
};

//定义二叉树类
template <typename ElemType> class BinaryTree {
private :
	BTnode<ElemType> *root;  //定义根节点
	void _Create(BTnode<ElemType> * &T, ElemType ch[], const ElemType &c, int &i);
	BTnode<ElemType>* _Locate(BTnode<ElemType> *T, const ElemType e);
	int _Depth(BTnode<ElemType> *T);
	int _Leafs(BTnode<ElemType> *T);
	void _PreorderTraverse(BTnode<ElemType> *T);

public :
	void Create(ElemType ch[], const ElemType &c);
	void Child(const ElemType &e);
	int Depth();
	int Leafs();
	void PreorderTraverse();
	void InorderTraverseNonRecursive(void (*visit)(const ElemType &e));
};
////////////////////////////////////////////////////////
//创建二叉树函数
template <typename ElemType> void BinaryTree<ElemType>::_Create(BTnode<ElemType> * &T, ElemType ch[], const ElemType &c, int &i) {
	if (ch[i] == c) {
		T = NULL;
	} else {
		T = new BTnode<ElemType>;
		T->data = ch[i];
		_Create(T->Lchild, ch, c, ++i);
		_Create(T->Rchild, ch, c, ++i);
	}
}
//创建二叉树接口函数
template <typename ElemType> void BinaryTree<ElemType>::Create(ElemType ch[], const ElemType &c) {
	int i = 0;
	_Create(root, ch, c, i);
}
//////////////////////////////////////////
//创建二叉树查找函数
template <typename ElemType> BTnode<ElemType>* BinaryTree<ElemType>::_Locate(BTnode<ElemType> *T, const ElemType e) {
	if (!T || T->data == e) {
		return T;
	}
	BTnode<ElemType> *q;
	q = _Locate(T->Lchild, e);
	if (q) {
		return q;
	}
	q = _Locate(T->Rchild, e);
	return q;
}
//输出二叉树儿子结点函数
template <typename ElemType> void BinaryTree<ElemType>::Child(const ElemType &e) {
	if (_Locate(root, e)) {
		if (_Locate(root,e)->Lchild) {
			cout << "left child is " << (_Locate(root, e)->Lchild)->data << endl;
		} else {
			cout << "not found left child" << endl;
		}
		if (_Locate(root,e)->Rchild) {
			cout << "right child is " << (_Locate(root, e)->Rchild)->data << endl;
		} else {
			cout << "not found right child" << endl;
		}
	}
	else {
		cout << "not found this node" << endl;
	}
}
/////////////////////////////////////
//求二叉树深度函数
template <typename ElemType> int BinaryTree<ElemType>::_Depth(BTnode<ElemType> *T) {
	if (!T) {
		return 0;
	}
	int h1 = _Depth(T->Lchild);
	int h2 = _Depth(T->Rchild);
	return h1 > h2 ? h1+1 : h2+1;
}
//求二叉树深度接口函数
template <typename ElemType> int BinaryTree<ElemType>::Depth() {
	return _Depth(root);
}
////////////////////////////////////////
//求二叉树叶子结点个数函数
template <typename ElemType> int BinaryTree<ElemType>::_Leafs(BTnode<ElemType> *T) {
	if (!T) {
		return 0;
	}
	if (!T->Lchild && !T->Rchild) {
		return 1;
	}
	int h1 = _Leafs(T->Lchild);
	int h2 = _Leafs(T->Rchild);
	return h1 + h2;
}
//求二叉树叶子结点个数接口函数
template <typename ElemType> int BinaryTree<ElemType>::Leafs() {
	return _Leafs(root);
}
///////////////////////////////////////////
//递归先序遍历二叉树
template <typename ElemType> void BinaryTree<ElemType>::_PreorderTraverse(BTnode<ElemType> *T) {
	if (T) {
		cout << T->data << " ";
		_PreorderTraverse(T->Lchild);
		_PreorderTraverse(T->Rchild);
	}
}
//递归先序遍历二叉树接口函数
template <typename ElemType> void BinaryTree<ElemType>::PreorderTraverse() {
	_PreorderTraverse(root);
}
////////////////////////////////////////////
//利用栈中序遍历二叉树
template <class ElemType>
void BinaryTree<ElemType> ::InorderTraverseNonRecursive(void (*visit)(const ElemType &e))
{ 
    stack<BTnode<ElemType> *> S;
    S.push (root); //根指针进栈
    
    while (!S.empty ()) {
        BTnode<ElemType> *p;
        p = S.top ();

        while (p) {
            p = p->Lchild;
            S.push(p); // 向左走到尽头
        }
        
        S.pop(); // 空指针退栈
        
        if (!S.empty()){ // 访问结点,向右一步
            p = S.top ();
            S.pop();
            visit(p->data);
            S.push(p->Rchild);
        }
    }
} 

int main(void) {

	BinaryTree<char> tree;

	char ch[17] = {'a','b','d','#','#','e','g','#','h','#','#','#','c','f','#','#','#'};

	cout << "输出b结点的左右子节点 : " << endl;
	tree.Create(ch, '#');
	tree.Child('b');

	cout << endl;

	cout << "该二叉树的深度为 : ";
	cout << tree.Depth() << endl;
	
	cout << endl;

	cout << "该二叉树的叶子结点数为 : ";
	cout << tree.Leafs() << endl;
	
	cout << endl;

	cout << "递归先序遍历二叉树 : ";
	tree.PreorderTraverse();

	cout << endl;

	cout << "利用栈中序遍历二叉树 : ";
	tree.InorderTraverseNonRecursive(Print);
	
	cout << endl;

	return 0;
}