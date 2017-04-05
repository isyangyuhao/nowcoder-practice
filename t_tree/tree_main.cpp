#include <iostream>
#include <string>
#include <stack>
using namespace std;

void Print(const char &c) {
	cout << c << " ";
}

//���������
template <typename ElemType> struct BTnode {
	ElemType data;
	BTnode<ElemType> *Lchild, *Rchild;
};

//�����������
template <typename ElemType> class BinaryTree {
private :
	BTnode<ElemType> *root;  //������ڵ�
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
//��������������
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
//�����������ӿں���
template <typename ElemType> void BinaryTree<ElemType>::Create(ElemType ch[], const ElemType &c) {
	int i = 0;
	_Create(root, ch, c, i);
}
//////////////////////////////////////////
//�������������Һ���
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
//������������ӽ�㺯��
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
//���������Ⱥ���
template <typename ElemType> int BinaryTree<ElemType>::_Depth(BTnode<ElemType> *T) {
	if (!T) {
		return 0;
	}
	int h1 = _Depth(T->Lchild);
	int h2 = _Depth(T->Rchild);
	return h1 > h2 ? h1+1 : h2+1;
}
//���������Ƚӿں���
template <typename ElemType> int BinaryTree<ElemType>::Depth() {
	return _Depth(root);
}
////////////////////////////////////////
//�������Ҷ�ӽ���������
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
//�������Ҷ�ӽ������ӿں���
template <typename ElemType> int BinaryTree<ElemType>::Leafs() {
	return _Leafs(root);
}
///////////////////////////////////////////
//�ݹ��������������
template <typename ElemType> void BinaryTree<ElemType>::_PreorderTraverse(BTnode<ElemType> *T) {
	if (T) {
		cout << T->data << " ";
		_PreorderTraverse(T->Lchild);
		_PreorderTraverse(T->Rchild);
	}
}
//�ݹ���������������ӿں���
template <typename ElemType> void BinaryTree<ElemType>::PreorderTraverse() {
	_PreorderTraverse(root);
}
////////////////////////////////////////////
//����ջ�������������
template <class ElemType>
void BinaryTree<ElemType> ::InorderTraverseNonRecursive(void (*visit)(const ElemType &e))
{ 
    stack<BTnode<ElemType> *> S;
    S.push (root); //��ָ���ջ
    
    while (!S.empty ()) {
        BTnode<ElemType> *p;
        p = S.top ();

        while (p) {
            p = p->Lchild;
            S.push(p); // �����ߵ���ͷ
        }
        
        S.pop(); // ��ָ����ջ
        
        if (!S.empty()){ // ���ʽ��,����һ��
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

	cout << "���b���������ӽڵ� : " << endl;
	tree.Create(ch, '#');
	tree.Child('b');

	cout << endl;

	cout << "�ö����������Ϊ : ";
	cout << tree.Depth() << endl;
	
	cout << endl;

	cout << "�ö�������Ҷ�ӽ����Ϊ : ";
	cout << tree.Leafs() << endl;
	
	cout << endl;

	cout << "�ݹ�������������� : ";
	tree.PreorderTraverse();

	cout << endl;

	cout << "����ջ������������� : ";
	tree.InorderTraverseNonRecursive(Print);
	
	cout << endl;

	return 0;
}