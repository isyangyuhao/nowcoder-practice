#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include <cmath>
#include <cassert>

using namespace std;

////////////// QuickFind方式实现并查集 //////////////

/*
	    0  1  2  3  4  5  6  7  8  9
	-------------------------------------
	id  0  1  0  1  0  1  1  0  0  1

	* id表示元素连通状态
	* id相同的元素代表处于同一集合,状态为连通
*/

class UnionFind {

private:

	int* id;  //存放元素的连通状态(相同id的元素即为连通)
	int count;  //存放元素的数量

public:

	//构造函数
	UnionFind(int count) {
		
		id = new int[count];
		this->count = count;

		//初始元素,每一个元素互不连通,因此初始化时需要为其设置为不同的id
		for (int i = 0; i < count; ++i) {
			id[i] = i;
		}

	}

	//析构函数
	~UnionFind() {
		delete [] id;
	}

	//查找函数
	int find(int p) {
		assert(p >= 0 && p < count);
		return id[p];
	}

	//判断两个元素是否连通
	bool isConnected(int p, int q) {
		return find(p) == find(q);
	}

	//取元素并集
	void unionElements(int q, int q) {
		
		int pId = find(p);
		int qId = find(q);

		//如果两个元素的id相同,表示已经属于同一集合
		if (pId == qId) {
			return ;
		}

		//如果两个元素的id不同,则需要将其中一个元素所在的id集合中的全部元素修改为另一个元素的id
		else {
			for (int i = 0; i < count; ++i) {
				if (id[i] == pId) {
					id[i] = qId;
				}
			}
		}
	
	}

};


////////////// QuickUnion方式实现并查集 [常规实现] //////////////

/*
	        0  1  2  3  4  5  6  7  8  9
	-------------------------------------
	parent  1  1  1  8  3  0  5  1  8  8

	* parent存放当前元素的父元素
	* 如果当前两个元素的根相同,说明这两个元素处于同一集合,即为连通的
*/

class UnionFind2 {

private: 

	int* parent;  //存放元素的父元素
	//int* sz;  //基于size的优化union,sz[i]存放以i为根的集合的中的元素个数
	int* rank;  //基于rank的优化union,rank[i]存放以i为根的集合中树的高度
	int count;  //存放元素的数量

public:

	//构造函数
	UnionFind2(int count) {

		parent = new int[count];
		//sz = new int[count];
		rank = new int[count];
		this->count = count;

		//初始元素,每个元素互不互通,自己的parent指向自己,sz全部为1
		for (int i = 0; i < count; ++i) {
			parent[i] = i;
			//sz[i] = 1;
			rank[i] = 1;
		}

	}

	//析构函数
	~UnionFind2() {
		delete [] parent;
		//delete [] sz;
		delete [] rank;
	}

	//查找函数 [经过路径压缩后的查询操作,时间复杂度近乎为O(1)]
	int find(int p) {
		
		assert(p >= 0 && p < count);
		
		// //在当前节点不是根节点的情况下,一直向上寻找根节点

		// while (p != parent[p]) {
		// 	//路径压缩(Path Compression)1: 将当前父亲指针的指向修改为父亲的父亲,缩短了一部分树的高度
		// 	parent[p] = parent[parent[p]];
		// 	p = parent[p];
		// }
		// return p;

		//路径压缩2: 将集合根节点的所有子元素parent全部修改为根节点,树的高度缩短为了2
		if (p != parent[p]) {
			parent[p] = find(parent[p]);
		}
		return parent[p];

	}

	//判断连通性
	bool isConnected(int p, int q) {
		return find(p) == find(q);
	}

	//取并集操作
	void unionElements(int p, int q) {

		int pRoot = find(p);
		int qRoot = find(q);

		//如果p的根节点和q的根节点相同,说明他们已经处于同一集合
		if (pRoot == qRoot) {
			return ;
		}

		//如果两个元素根节点不相同

		//将集合元素少的一方的根连接到集合元素多的一方的根
		// if (sz[pRoot] < sz[qRoot]) {
		// 	parent[pRoot] = qRoot;
		// 	sz[qRoot] += sz[pRoot];
		// } else {
		// 	parent[qRoot] = pRoot;
		// 	sz[pRoot] += sz[qRoot];
		// }

		//将集合元素树高度小的一方的根连接到集合元素树高度达的一方的根
		if (rank[pRoot] < rank[qRoot]) {
			parent[pRoot] = qRoot;
		}
		else if (rank[pRoot] > rank[qRoot]) {
			parent[qRoot] = pRoot;
		}
		//当两颗树的高度一致时,被连接的一方层数加1
		else {
			parent[pRoot] = qRoot;
			++rank[qRoot];
		}

	}

};









