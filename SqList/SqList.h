//SqList.h
//定义顺序表类

#include <iostream>
using namespace std;

template <class ElemType>
class SqList {

public:
	SqList(int m = 0);  //构造函数,创建顺序表 [1]
	~SqList();  //析构函数,销毁顺序表 [2]
	bool isEmpty() const;  //求顺序表是否为空表 [3]
	int Length() const;  //求顺序表长度 [4]
	void Clear();  //清空顺序表 [5]
	bool GetElem(ElemType&, int) const;  //表中取值 [6]
	bool SetElem(const ElemType&, int);  //表中存值 [7]
	int LocateElem(const ElemType&) const;  //查找表中符合条件的数据元素 [8]
	int LocatePrior(const ElemType&) const;  //查找表中符合条件的数据元素的前驱 [9]
	int LocateNext(const ElemType&) const;  //查找表中符合条件的数据元素的后继 [10]
	bool Insert(const ElemType&, int);  //在表中指定位置插入 [11]
	bool Append(const ElemType&);  //在表尾插入 [12]
	bool Delete(ElemType&, int);  //删除表中指定位置的数据元素 [13]
	void Traverse() const;  //顺序表遍历 [14]

private:
	int len;  //顺序表长度
	int size;  //顺序表容量
	ElemType *elem;  //基地址指针
	
};

//[1] 构造函数,分配m个存储单元的顺序空间,线性表为空表
template <class ElemType>
SqList<ElemType>::SqList(int m) {
	//线性表为空表,len置为0
	len = 0;  
	if (m == 0) {
		//如果参数m为默认0,则代表不开辟任何空间,即基地址指向NULL
		elem = NULL;
	} else {
		//如果参数不为0,则为顺序表开辟m个空间
		elem = new ElemType[m];
	}
	//设置顺序表的容量为开辟的空间数
	size = m;
}

//[2] 析构函数,顺序表结构销毁
template <class ElemType>
SqList<ElemType>::~SqList() {
	//删除基地址指针
	delete [] elem;
}

//[3] 判断顺序表是否为空表
template <class ElemType>
bool SqList<ElemType>::isEmpty() const {
	if (len <= 0) {
		return true;
	} else {
		return false;
	}
}

//[4] 求数据表的长度
template <class ElemType>
int SqList<ElemType>::Length() const {
	return len;
}

//[5] 清空顺序表
template <class ElemType>
void SqList<ElemType>::Clear() {
	//将表长度置位0,则代表顺序表被清空
	len = 0;
}

//[6] 取顺序表中序号为i的数据元素值,i的合法值为1<=i<=len
template <class ElemType>
bool SqList<ElemType>::GetElem(ElemType &e, int i) const {
	if(i < 1 || i > len) {
		return false;
	}
	e = elem[i - 1];
	return true;
}

//[7] 在顺序表中需要为i的位置上存入数据元素,i的合法值为1<=i<=len
template <class ElemType>
bool SqList<ElemType>::SetElem(const ElemType &e, int i) {
	//因为存放的数据元素有可能出现在最后一位,
	if (i < 1 || i > len) {
		return false;
	}
	elem[i - 1] = e;
	return true;
}

//[8] 在顺序表中查找符合条件的数据元素,如果存在返回它的位置
template <class ElemType>
int SqList<ElemType>::LocateElem(const ElemType &e) const {
	//查找指针
	ElemType *p = elem;
	int i = 1;
	//如果在顺序表所占长度内并且查找指针指向的元素不等于被查找元素,则向下移动
	while (i <= len && *p != e) {
		++p;
		++i;
	}
	//如果i的位置超出了顺序表的长度,则代表没有找到,否则返回i的位置
	if (i <= len) {
		return i;
	}
	return 0;
}

//[9] 在顺序表中查找符合条件的数据元素的前驱,如果存在返回它的位置
template <class ElemType>
int SqList<ElemType>::LocatePrior(const ElemType &e) const {
	int i = LocateElem(e);
	if (i > 1) {
		return i - 1;
	}
	return 0;
}

//[10] 在顺序表中查找符合条件的数据元素的后继,如果存在则返回它的位置
template <class ElemType>
int SqList<ElemType>::LocateNext(const ElemType &e) const {
	int i = LocateElem(e);
	if (i >= 1 && i < len) {
		return i + 1;
	}
	return 0;
}

//[11] 在表中的第i个位置插入新数据
template <class ElemType>
bool SqList<ElemType>::Insert(const ElemType &e, int i) {
	if (i < 1 || i > len + 1) {
		return false;
	}
	//如果表满则扩充控件
	if (len >= size) {
		ElemType *newbase;
		newbase = new ElemType[size + 10];
		if (!newbase) {
			return false;
		}
		for (int j = 0; j < len; ++i) {
			newbase[j] = elem[j];
		}
		delete [] elem;
		elem = newbase;
	}
	ElemType *p, *q;
	q = &elem[i - 1];  //指向插入位置的指针
	//p指针从末尾向q移动,每次将数据向右移动一格
	for (p = &elem[len - 1]; q<=p; --p) {  
		*(p + 1) = *p;
	}
	*q = e;
	++len;
	return true;
}

//[12] 在顺序表的表尾插入新的数据元素
template <class ElemType>
bool SqList<ElemType>::Append(const ElemType &e) {
	ElemType *newbase;
	//如果表满则需要扩展空间
	if (len >= size) {
		newbase = new ElemType[size + 10];
		if (!newbase) {
			return false;
		}
		for (int j = 0; j < len; ++j) {
			newbase[j] = elem[j];
		}
		delete [] elem;
		elem = newbase;
		size += 10;
	}
	elem[len] = e;
	++len;
	return true;
}

//[13] 在顺序表中删除第i个元素
template <class ElemType>
bool SqList<ElemType>::Delete(ElemType &e, int i) {
	if (i < 1 || i > len) {
		return false;
	}
	ElemType *p, *q;
	p = &elem[i - 1];  //指针p指向被删除元素
	e = *p;
	q = &elem[len - 1];  //指针q指向顺序表末尾
	for (++p; p <= q; ++p) {
		*(p - 1) = *p;
	}
	--len;
	return true;
}

//[14] 遍历输出顺序表的值
template <class ElemType>
void SqList<ElemType>::Traverse() const {
	ElemType *p = elem;
	for (int i = 0; i < len; ++i) {
		cout << *(p + i) << ",";
	}
	cout << endl;
}