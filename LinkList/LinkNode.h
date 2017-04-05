//LinkNode.h
//定义单链表结点

template <class ElemType>
struct LinkNode {

	ElemType data;  //当前结点存储的数据
	LinkNode<ElemType> *next;  //链接关系指针域

};