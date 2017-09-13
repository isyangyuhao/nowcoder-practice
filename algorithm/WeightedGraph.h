#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include <cmath>
#include <cassert>
#include <vector>

#include "Heap.h"
#include "UnionFind.h"

using namespace std;

/*
	-------------- 有权图相关算法 --------------
*/

/////////////// 有权图的边 ///////////////

template <typename Weight>
class Edge {

private:

	int a, b;  //边的两个顶点, a->起始点, b->终点
	Weight weight;  //边的权值

public:

	//构造函数
	Edge() {}
	Edge(int a, int b, Weight weight) {
		this->a = a;
		this->b = b;
		this->weight = weight;
	}

	//析构函数
	~Edge() {}

	//获取边的起始点
	int v() { return a; }

	//获取边的终点
	int w() { return b;}

	//获取边的权值
	weight wt() { return weight; }

	//已知两边中的一点,获取另一点
	int other(int x) {
		assert(x == a || x == b);
		return x == a ? b : a;
	}

	//重载输出, 打印边的所有信息
	friend ostream& operator <<(ostream &os, const Edge &e) {
		os << e.a << "-" << e.b << ": " << e.weight;
		return os;
	}

	//重载比较, 通过权重比较边的大小
	bool operator <(Edge<Weight> &e) {
		return weight < e.weight;
	}
	bool operator >(Edge<Weight> &e) {
		return weight > e.weight;
	}
	bool operator ==(Edge<Weight> &e) {
		return weight == e.weight;
	}
	bool operator <=(Edge<Weight> &e) {
		return weight <= e.weight;
	}
	bool operator >=(Edge<Weight> &e) {
		return weight >= e.weight;
	}

};


/////////////// 利用邻接矩阵实现有权稠密图 ///////////////

template <typename Weight>
class WeightedDenseGraph {

private:

	int n;  //节点数
	int m;  //边数
	bool directed;  //是否为有向图
	vector<vector<Edge<Weight> *>> g;  //邻接矩阵,存放边的信息

public:

	//构造函数
	DenseGraph(int n, bool directed) {

		this->n = n;
		this->m = 0;  //边数初始为0
		this->directed = directed;
		
		for (int i = 0; i < n; ++i) {
			//向vector末尾添加一个vector,其中存放n个空边
			g.push_back(vector<Edge<Weight> *>(n, NULL));
		}

	}

	//析构函数
	~DenseGraph() {
		//释放邻接矩阵中存放的边的空间
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (g[i][j] != NULL) {
					delete g[i][j];
				}
			}
		}
	}

	//返回节点数
	int V() { return m; }

	//返回边数
	int E() { return n; }

	//判断两个节点是否存在边
	bool hasEdge(int v, int w) {
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		return g[v][w] != NULL;
	}

	//为节点添加边
	void addEdge(int v, int w, Weight weight) {

		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);

		//判断是否已经存在边, 如果存在则删除掉
		if (hasEdge(v, w)) {
			delete g[v][w];
			if (!directed) {
				delete g[w][v];
			}
			--m;
		}

		g[v][w] = new Edge<Weight>(v, w, weight); 

		//判断是否是无向图,如果是则同样需要将w连接到v
		if (!directed) {
			g[w][v] = new Edge<Weight>(w, v, weight);
		}

		++m;  //边数加1

	}

	//打印邻接矩阵
	void show() {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (g[i][j] != NULL) {
					cout << g[i][j]->wt() << "\t";
				} else {
					cout << "NULL";
				}
			}
		}
	}

	//相邻节点迭代器
	class adjIterator {

	private:

		DenseGraph &G;  //存放需要迭代的图
		int v;  //存放需要迭代的节点
		int index;  //存放迭代的索引

	public:

		//构造函数
		adjIterator(DenseGraph &graph, int v): G(graph) {
			this->v = v;  
			this->index = 0;
		}

		//返回迭代的第一个节点
		Edge<Weight>* begin() {
			//第一个被迭代的节点下标不为0,因此逻辑与next()相同
			//在邻接矩阵中找到第一个相邻的节点
			index = -1;
			next();
		}

		//返回迭代的下一个节点
		Edge<Weight>*  next() {
			for (index = index + 1; index < G.V(); ++index) {
				if (G.g[v][index] == true) {
					return G.g[v][index];
				}
			}
			return NULL;
		}

		//判断是否迭代结束
		bool end() {
			return index >= G.V();
		}

	};

};



/////////////// 利用邻接矩阵实现稀疏图 ///////////////

template <typename Weight>
class SparseGraph {

private:

	int n;  //存放节点数
	int m;  //存放边数
	bool directed;  //是否为有向图
	vector<vector<Edge<Weight> *>> g;  //邻接表

public:

	//构造函数
	SparseGraph(int n, directed) {

		this->n = n;
		this->m = 0;
		this->directed = directed;

		for (int i = 0; i < n; ++i) {
			g.push_back(vector<Edge<Weight> *>());
		}

	}

	//析构函数
	~SparseGraph() {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < g[i].size(); ++j) {
				if (g[i][j] != NULL) {
					delete g[i][j];
				}
			}
		}
	}

	//获取节点数
	int V() { return n; }

	//获取边数
	int E() { return m; }

	//判断两个节点是否存在边
	bool hasEdge(int v, int w) {

		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);

		for (int i = 0; i < g[v].size(); ++i) {
			//如果存在点v的另一端点为w的边, 则代表存在
			if (g[v][i]->other(v) == w) {
				retrun true;
			}
		}

		return false;

	}

	//为节点添加边
	void addEdge(int v, int w, Weight weight) {

		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);

		g[v].push_back(new Edge(v, w, weight));

		//如果当前图为无向图并且不为自环边的情况下,将w连接到v
		if (!directed && v != w) {
			g[w].push_back(new Edge(w, v, weight));
		}

		++m;

	}

	//打印邻接表
	void show() {
		for (int i = 0; i < n; ++i) {
			cout << "vertex " << i << ":\t";
			for (int j = 0; j < g[i].size(); ++j) {
				if (g[i][j] != NULL) {
					cout << "to:" << g[i][j].w() << ", wt:" << g[i][j].wt();
				}
			}
			cout << endl;
		}
	}

	//相邻节点迭代器
	class adjIterator {

	/*
	 	使用相邻节点迭代器:
		SparseGraph::adjIterator iterator(g, v);
		for (int w = iterator.begin(); !iterator.end(); iterator.next()) {
			cout << w << endl;
		}
	*/
	
	private:

		SparseGraph &G;  //需要迭代的图的引用
		int v;  //需要迭代节点
		int index;  //当前迭代的索引

	public:

		//构造函数
		adjIterator(SparseGraph &graph, int v): G(graph) {
			this->v = v;
			this->index = 0;
		}

		//返回迭代的第一个元素
		Edge<Weight>* begin() {
			//起始迭代,将索引设置为0
			index = 0;
			//在v节点存在相邻节点的情况下返回下标第0个相邻节点
			if (G.g[v].size()) {
				return G.g[v][0];
			}
			//不存在相邻节点则返回-1
			return NULL;
		}

		//返回迭代的下一个元素
		Edge<Weight>* next() {
			//访问下一个元素,将索引加1
			++index;
			//在索引没有越界的情况下返回下一个索引的相邻节点
			if (index < G.g[v].size()) {
				return G.g[v][index];
			}
			return NULL;
		}

		//判断是否迭代完成
		bool end() {
			return index >= G.g[v].size();
 		}

	};

};


namespace WeightedGraphAlgorithm {

	/////////////// 通过文件读取有权图 ///////////////

	template <typename Graph, typename Weight>
	class ReadGraph {

	public:

		//构造函数,通过文件读取一个图

		/*	
		 * 使用文件表示图
			-----------------
			6 3     -> 第1行表示图的节点数和边数: V & E
			1 2 .5 -> 第1行以后每行的三个值分别代表: 起始点, 终点, 权值
			1 4 2
			2 5 .25
			-----------------
		*/

		template <typename Graph>
		ReadGraph(Graph &graph, const String filename) {

			ifstream file(filename);  //获取文件输入流
			string line;  //单行信息
			int V, E;  //点数, 边数

			assert(file.is_open());  //判断文件输入流是否打开
			
			//获取第一行中的关于Graph的V和E信息
			assert(getline(file, line));  
			stringstream ss(line);
			ss >> V >> E;
			//判断读取的Graph中的V是否与文本中读取的图节点数一致
			assert(V == graph.V());

			//逐行读取图中各个
			for (int i = 0; i < E; ++i) {
				assert(getline(file, line));
				stringstream ss(line);
				int a, b;
				Weight weight;
				ss >> a >> b >> weight;
				assert(a >= 0 && a < V);
				assert(b >= 0 && b < V);
				graph.addEdge(a, b, weight);
			}

		}

	};

	/*
		-------------- 最小生成树相关算法 --------------
	*/

	/*
		-----------------------------------------
		切分定理(Cut Property): 
			给定任意切分,横切边中权值最小的边一属于最小生成树
		-----------------------------------------
	*/

	/////////////// Lazy Prim 求最短生成树 ///////////////

	template <typename Graph, typename Weight>
	class LazyPrimMST {

	private:

		Graph &G;  //需要生成树的图
		Heap<Edge<Weight>> pq;  //小顶堆,充当优先队列,存放生成树时的待选边
		bool *marked;  //该点是否已被访问
		vector<Edge<Weight>> mst;  //存放最小生成树各个路径
		Weight mstWeight;  //最小生成树权重

		//最小生成树访问函数
		void _visit(int v) {

			assert(!marked[v]);  //保证当前访问节点尚未访问

			//访问当前节点,并遍历当前节点的所有相邻节点
			marked[v] = true;  
			typename Graph::adjIterator iterator(G, v);
			for (Edge<Weight> *e = iterator.begin(); !iterator.end(); e = iterator.next()) {

				//如果当前相邻节点的另一端未被访问的情况下,则放入小顶堆中
				if (!marked[e->other(v)]) {
					pq.insert(*e);
				}

			}

		}

	public:

		//构造函数
		LazyPrimMST(Graph &graph): G(graph) {

			//算法初始化

			pq = new Heap<Edge<Weight>>(G.E());

			marked = new bool[G.E()];
			for (int i = 0; i < G.E(); ++i) {
				marked[i] = false;
			}

			mst.clear();  //保证mst初始化为空

			// Lazy Prim

			//访问节点, 从0开始访问
			_visit(0);

			//在小顶堆中找到符合要求的横切边
			while (!pq.empty()) {
				//取出权重最小的边
				Edge<weight> e = pq.extractMin();  
				//判断是两边访问状态是否一致,不一致为横切边,不是横切边直接跳过
				if (marked[e.v()] == marked[e.w()]) {
					continue;
				}
				//如果是横切便则加入mst中, 找到当期横切边中未被访问的点, 继续访问
				mst.push_back(e);
				if (!marked[e.v()]) {
					_visit(e.v());
				} else {
					_visit(e.w());
				}
			}

			//计算最小生成树权重
			mstWeight = mst[0].wt();
			for (int i = 1; i < msg.size(); ++i) {
				mstWeight += mst[i].mt();
			}

		}

		//析构函数
		~LazyPrimMST() { delete [] marked; }

		//获取最小生成树的各个边
		vector<Edge<Weight>> mst() { return mst; }

		//获取最小生成树的权重
		Weight result() { return mstWeight; }

	};


	/////////////// 优化后的Prim算法 ///////////////

	template <typename Graph, typename Weight>
	class PrimMST {

	private:

		Graph &G;  //需要生成树的图
		IndexMinHeap<Weight> ipq;  //索引最小堆,充当优先队列,存放和每个节点相邻的横切边相应的权值
		vector<Edge<Weight> *> edgeTo;  //存储每个节点相邻的最短的横切边
		bool *marked;  //该点是否已被访问
		vector<Edge<Weight>> mst;  //存放最小生成树各个路径
		Weight mstWeight;  //最小生成树权重

		//最小生成树访问函数
		_visit(int v) {

			assert(!marked[v]);

			marked[v] = true;
			typename Graph::adjIterator iterator(G, v);
			for (Edge<Weight> *e = iterator.begin(); !iterator.end(); e = iterator.next()) {
				
				//如果当前临边的另一点未被访问,则代表为横切边
				int w = e->other(v);
				if (!marked[w]) {

					//判断当前节点是否存在横切边,如果不存在则更新edgeTo,然后插入到最小索引堆中
					if (!edgeTo[w]) {
						edgeTo[w] = e;
						ipq.insert(w, e->wt());
					}

					//如果当前节点已经存在横切边,则比较当前横切边是否比之前存放的小,如果小则更新为当前横切边
					else if (edgeTo[w].wt() > e->wt()) {
						edgeTo[w] = e;
						ipq.change(w, e->wt());
					}

				}

			}

		}

	public:

		//构造函数
		PrimMST(Graph &graph): G(graph), ipq(IndexMinHeap<double>(graph.V())) {

			//算法初始化
			marked = new bool[G.V()];
			for (int i = 0; i < G.V(); ++i) {
				marked[i] = false;
				edgeTo.push_back(NULL);
			}
			mst.clear();

			//Prim

			_visit(0);

			while (!ipq.empty()) {
				//取出当前权值最小的节点
				int v = ipq.extractMinIndex();
				//根据权值最小的节点取出权值最小的边,放入最终的生成结果中
				assert(edgeTo[v]);
				mst.push_back(*edgeTo[v]);
				visit(v);
			}

			mstWeight = mst[0].wt();
			for (int i = 1; i < mst.size(); ++i) {
				mstWeight += mst[i].wt();
			}

		}

		//析构函数
		~PrimMST() { delete [] marked; }

		//获取最小生成树的各个边
		vector<Edge<Weight>> mst() { return mst; }

		//获取最小生成树的权重
		Weight result() { return mstWeight; }

	};


	/////////////// Kruskal算法求最小生成树 ///////////////

	template <typename Graph, typename Weight>
	class KruskalMST {

	private:

		vector<Edge> mst;  //最小生成树的边集合
		Weight mstWeight;  //最小生成树的权重

	public:

		//构造函数, Krusk
		KruskalMST(Graph &graph) {

			//使用最小堆对图的所有边进行排序存储
			MinHeap<Edge<Weight>> pq(graph.E());

			//将所有的边存放到小顶堆中
			//遍历图的所有节点
			for (int i = 0; i < graph.V(); ++i) {

				//遍历当前节点的所有临边
				typename Graph::adjIterator iterator(graph, i);
				for (Edge<Weight> *e = iterator.begin(); !iterator.end(); e = iterator.next()) {

					//无向图的边在邻接表或邻接矩阵中存储了两次,取其中之1即可
					if (e->v() < e->w()) {
						//将边存放到小顶堆中
						pq.insert(*e);
					}

				}

			}

			//使用并查集存储各节点连通情况,初始化互不连通
			UnionFind uf(graph.V());

			while (!pq.empty() && mst.size() < graph.v() - 1) {

				//取出小顶堆中的最短路径
				Edge<Weight> e = pq.extractMin();

				//判断当前边的左右节点是否在图中连通,如果连通则代表当前边会构成环路,需要放弃
				if (uf.isConnected(e.v(), e.w())) {
					continue;
				}

				//否则,当前边即为最小生成树路径,存储结果并且取左右两节点并集操作
				mst.push_back(e);
				uf.unionElements(e.v(), e.w());

			}

			//计算最短权值
			mstWeight = mst[0].wt();
			for (int i = 1; i < mst.size(); ++i) {
				mstWeight += mst[i].wt();
			}

		}

		//析构函数
		~KruskalMST() {

		}

		//获取最小生成树的各个边
		vector<Edge<Weight>> mst() { return mst; }

		//获取最小生成树的权重
		Weight result() { return mstWeight; }

	};

	/*
		-----------------------------------
		最小生成树问题各算法时间复杂度
			1)   Lazy Prim   O(ElogE)
			2)   Prim        O(ElogV)
			3)   Kruskal     O(ElogE)
		-----------------------------------
	*/



	/*
		-------------- 最短优先路径相关算法 --------------
	*/

	/////////////// dijkstra单源最短路径算法(无法处理负权边) ///////////////

	template <typename Graph, typename Weight>
	class Dijkstra {

	private:

		Graph &G;  //需要寻路的图
		int s;  //起始节点
		Weight *distTo;  //起始点到各个节点的最短路径
		bool *marked;  //各个节点寻路状态
		vector<Edge<Weight> *> from;  //记录每个节点的遍历源

	public:

		//构造函数
		Dijkstra(Graph &graph, int s): G(graph) {

			//算法初始化
			this->s = s;
			distTo = new Weight[G.V()];
			marked = new bool[G.V()];
			for (int i = 0; i < G.V(); ++i) {
				distTo[i] = Weight();
				marked[i] = false;
				from.push_back(NULL);
			}

			//声明算法需要的最小索引堆
			IndexMinHeap<Weight> ipq(G.V());

			//Dijkstra

			//源点的距离一定为0
			distTo[s] = Weight();
			marked[s] = true;
			//将源点放入最小索引堆
			ipq.insert(s, distTo[s]);

			while (!ipq.empty()) {

				//找到最小索引堆中的最小节点, 此时distTo[v]存放的就是s->v的最短路径
				int v = ipq.extractMinIndex();
				marked[v] = true;

				//对点v进行松弛操作, 查看它的临边是否有经过后路径更短的存在
				typename Graph::adjIterator iterator(G, v);
				for (Edge<Weight> *e = iterator.begin(); !iterator.end(); e = iterator.next()) {
					
					//如果当前临边的另一端节点没有寻路过,则需要进行松弛判断
					int w = e->other(v);
					if (!marked[w]) {

						//松弛判断: 1) 该点没有比访问过; 2) s->v->w的路径小于s->w的路径
						//以上两种情况下进行松弛操作
						if (from[w] == NULL || distTo[v] + e->wt() < distTo[w]) {
							//更新s->w的最短路径
							distTo[w] = distTo[v] + e->wt();
							//更新访问源
							from[w] = e;
							//更新最小索引堆
							if (ipq.continue(w)) {
								ipq.change(w, distTo[w]);
							} else {
								ipq.insert(w, distTo[w]);
							}
						}

					}

				}

			}

		}

		//析构函数
		~Dijkstra() {
			delete [] marked;
			delete [] distTo;
		}

		//获取某个节点到起始节点的最短权值
		Weight shortestPathTo(int w) {
			return distTo[w];
		}

		//判断某个节点到起始节点是否存在路径
		bool hasPathTo(int w) {
			return marked[w];
		}

		//获取某个节点到起始节点的最短路径
		void shortestPath(int w, vector<Edge<Weight>> &vec) {
			
			stack<Edge<Weight> *> s;
			
			//反向存放最短路径
			Edge<Weight *> e = from[w];
			while (e->v() != e->w()) {
				s.push(e);
				e = from[w->v()];
			}

			//正向放入向量中
			while (!s.empty()) {
				Edge<Weight> *e = s.top();
				vec.push_back(*e);
				s.pop();
			}

		}

		//打印某个节点到起始节点的最短路径
		void showPath(int w) {
			
			assert(w >= 0 && w < G.V());
			vector<Edge<Weight>> vec;
			shortestPath(w, vec);

			for (int i = 0; i < vec.size(); ++i) {
				cout << vec[i].v() << " -> ";
				if (i == vec.size() - 1) {
					cout << vec[i].w() << endl;
				}
			}

		}

	};


	/////////////// Bellman-Ford单源最短路径算法(可以处理负权边,无法处理负权环) ///////////////

	/*
		对所有的点进行v-1次松弛操作,理论上就可以找到从源点到其他所有节点的最短路径
		如果可以继续进行松弛操作,则代表图中存在负权环
	*/

	template <typename Graph, typename Weight>
	class BellmanFord {

	private:

		Graph &G;  //需要寻路的图
		int s;  //起始点
		Weight *distTo;  //起始点到各个节点的最短路径
		vector<Edge<Weight> *> from;  //每个节点的遍历源
		bool hasNegativeCycle;  //是否存在负权环

		//判断是否存在负权环函数
		bool _detectNegativeCycle() {

			//对图中所有点再进行一轮松弛操作,如果发现还有存在最短路径则说明存在负权环
			for (int i = 0; i < G.V(); ++i) {
				typename Graph::adjIterator iterator(G, i);
				for (Edge<Weight> *e = iterator.begin(); !iterator.end(); e = iterator.next()) {
					if (from[e] == NULL || distTo[i] + e->wt() < distTo[e.w()]) {
						return true;
					} 
				}
			}

			return false;

		}

	public:

		//构造函数
		BellmanFord(Graph &graph, int s): G(graph) {

			//算法初始化
			this->s = s;
			distTo = new Weight()[G.V()];
			for (int i = 0; i < G.V(); ++i) {
				from.push_back(NULL);
			}

			//BellmanFord

			distTo[s] = Weight();

			//进行v-1次松弛操作
			for (int pass = 1; pass < G.V(); ++pass) {

				//遍历所有的点
				for (int i = 0; i < G.V(); ++i) {

					//获取当前节点的所有临边
					typename Graph::adjIterator iterator(G, v);
					for (Edge<Weight> *e = iterator.begin(); !iterator.end(); e = iterator.next()) {

						//如果当前临边的另一端没有到达过或者绕道权值更小则进行松弛操作
						if (!from[e->w()] || distTo[i] + e->wt() <  distTo[e->w()]) {
							//更新e->w的最短路径
							distTo[e->w()] = distTo[i] + e->wt();
							from[w->w()] = e;
						}

					}

				}

			}

			//进行负权环判断
			hasNegativeCycle = _detectNegativeCycle();

		} 

		//析构函数
		~BellmanFord() {
			delete [] distTo;
		}

		//是否存在负权环
		bool negativeCycle() {
			return hasNegativeCycle;
		}

		//判断某个节点到起始节点是否存在路径
		bool hasPathTo(int w) {
			assert(w >= 0 && w < G.V());
			return from[w] != NULL;
		}

		//获取最短路径权值
		Weight shortestPathTo(int w) {
			assert(w >= 0 && w < G.V());
			assert(!hasNegativeCycle);
			return distTo[w];
		}

		//获取最短路径
		void shortestPath(int w, vector<Edge<Weight>> &vec) {
			
			assert(w >= 0 && w < G.V());
			assert(!hasNegativeCycle);

			stack<Edge<Weight> *> s;
			Edge<Weight> *e = from[w];

			while (e->v() != this->s) {
				s.push(e);
				e = from[e->v()];
			}
			s.push(e);

			while (!s.empty()) {
				e = s.top();
				vec.push_back(*e);
				s.pop();
			}

		}

		//打印最短路径
		void showPath(int w) {
			
			assert(w >= 0 && w < G.V());
			assert(!hasNegativeCycle);

			vector<Edge<Weight>> vec;
			showPath(w, vec);

			for (int i = 0; i < vec.size(); ++i) {
				cout << vec[i].v() << " -> ";
				if (i == vec.size() - 1) {
					cout << vec[i].w() << endl;
				}
			}

		}

	};


}









