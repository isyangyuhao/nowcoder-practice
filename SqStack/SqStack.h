//SqStack.h
//顺序栈类

template <class ElemType>
class SqStack {

public:
	SqStack(int m);  //构造函数 [1]
	~SqStack();  //析构函数 [2]
	void Clear();  //清空栈 [3]
	bool Empty() const;  //判栈空 [4]
	int Length() const;  //求栈长度 [5]
	ElemType & Top() const;  //取栈顶元素 [6]
	void Push(const ElemType &);  //入栈 [7]
	void Pop();  //出栈 [8]

private:
	ElemType *m_base;  //基地址指针
	int m_top;  //栈顶指针
	int m_size;  //向量空间大小

};

//[1] 栈初始化
template <class ElemType>
SqStack<ElemType>::SqStack(int m) {
	m_top = 0;
	m_base = new ElemType[m];
	m_size = m;
}

//[2] 销毁栈
template <class ElemType>
SqStack<ElemType>::~SqStack() {
	if (m_base != NULL) {
		delete [] m_base;
	}
}

//[3] 清空栈
template <class ElemType>
void SqStack<ElemType>::Clear() {
	m_top = 0;
}

//[4] 判栈空
template <class ElemType>
bool SqStack<ElemType>::Empty() const {
	if (m_top == 0) {
		return true;
	}
	return false;
}

//[5] 求栈长度
template <class ElemType>
int SqStack<ElemType>::Length() const {
	return m_top;
}

//[6] 取栈顶元素
template <class ElemType>
ElemType & SqStack<ElemType>::Top() const {
	return m_base[m_top - 1];
}

//[7] 入栈
template <class ElemType>
void SqStack<ElemType>::Push(const ElemType &e) {
	//栈满则需要扩容
	if (m_top >= m_size) {
		ElemType *newbase = new ElemType[m_size + 10];
		for (int j = 0; j < m_size; ++j) {
			newbase[j] = m_base[j];
		}
		delete [] m_base;
		m_base = newbase;
		m_size += 10;
	}
	m_base[m_top] = e;
	++m_top;
}

//[8] 出栈
template <class ElemType>
void SqStack<ElemType>::Pop() {
	--m_top;
}


