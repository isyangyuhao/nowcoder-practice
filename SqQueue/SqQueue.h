//SqQueue.h
//循环队列类

template <class ElemType>
class SqQueue {

public:
	SqQueue(int m = 0);  //构造函数 [1]
	~SqQueue();  //析构函数 [2]
	void Clear();  //清空队列 [3]
	bool Empty() const;  //判队列空 [4]
	int Length() const;  //求队列长度 [5]
	ElemType & GetHead() const;  //求队头元素值 [6]
	ElemType & GetTail() const;  //求队尾元素值 [7]
	void Append(const ElemType &);  //入队 [8]
	void Remove();  //出队 [9]

private:
	ElemType *m_base;  //基地址指针
	int m_front;  //队头指针
	int m_rear;  //队尾指针
	int m_size;  //向量空间大小

};

//[1] 队列初始化
template <class ElemType>
SqQueue<ElemType>::SqQueue(int m) {
	m_front = m_rear = 0;
	m_base = new ElemType[m];
	m_size = m;
}

//[2] 销毁队列
template <class ElemType>
SqQueue<ElemType>::~SqQueue() {
	delete [] m_base;
}

//[3] 清空队列
template <class ElemType>
void SqQueue<ElemType>::Clear() {
	m_front = m_rear;
}

//[4] 判队列空
template <class ElemType>
bool SqQueue<ElemType>::Empty() const {
	if (m_front == m_rear) {
		return true;
	}
	return false;
}

//[5] 求队列长度
template <class ElemType>
int SqQueue<ElemType>::Length() const {
	return (m_rear - m_front + m_size) % m_size;
}

//[6] 取队头元素值
template <class ElemType>
ElemType & SqQueue<ElemType>::GetHead() const {
	return m_base[m_front];
}

//[7] 取队尾元素值
template <class ElemType>
ElemType & SqQueue<ElemType>::GetTail() const {
	//防止m_rear - 1 = -1出现错误
	return m_base[(m_rear - 1 + m_size) % m_size];
}

//[8] 入队
template <class ElemType>
void SqQueue<ElemType>::Append(const ElemType &e) {
	int j, k;
	//队满则需要扩展空间
	if (m_front == (m_rear + 1) % m_size) {
		ElemType *newbase = new ElemType[m_size + 10];
		for (j = m_front, k = 0; j != m_rear; ++k, j = (j + 1) % m_size) {
			newbase[k] = m_base[j];
 		}
 		delete [] m_base;
 		m_base = newbase;
 		m_size += 10;
	}
	m_base[m_rear] = e;
	m_rear = (m_rear + 1) % m_size;
}

//[9] 出队
template <class ElemType>
void SqQueue<ElemType>::Remove() {
	m_front = (m_front + 1) % m_size;
}





