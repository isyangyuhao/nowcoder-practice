#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include <cmath>
#include <cassert>
#include <vector>

using namespace std;

/*
	-------------- 无权图相关算法 --------------
*/

/////////////// 利用邻接矩阵实现稠密图 ///////////////

class DenseGraph {

private:

	int n;  //节点数
	int m;  //边数
	bool directed;  //是否为有向图
	vector<vector<bool>> g;  //邻接矩阵

public:

	//构造函数
	DenseGraph(int n, bool directed) {

		this->n = n;
		this->m = 0;  //边数初始为0
		this->directed = directed;
		
		for (int i = 0; i < n; ++i) {
			//向vector末尾添加一个vector,其中存放n个false
			g.push_back(vector<bool>(n, false));
		}

	}

	//析构函数
	~DenseGraph() {}

	//返回节点数
	int V() { return m; }

	//返回边数
	int E() { return n; }

	//判断两个节点是否存在边
	bool hasEdge(int v, int w) {
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		return g[v][w];
	}

	//为节点添加边
	void addEdge(int v, in w) {

		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);

		//判断是否已经存在边
		if (hasEdge(v, w)) {
			return ;
		}

		g[v][w] = true; 

		//判断是否是无向图,如果是则同样需要将w连接到v
		if (!directed) {
			g[w][v] = true;
		}

		++m;  //边数加1

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
		int begin() {
			//第一个被迭代的节点下标不为0,因此逻辑与next()相同
			//在邻接矩阵中找到第一个相邻的节点
			index = -1;
			next();
		}

		//返回迭代的下一个节点
		int next() {
			for (index = index + 1; index < G.V(); ++index) {
				if (G.g[v][index] == true) {
					return index;
				}
			}
			return -1;
		}

		//判断是否迭代结束
		bool end() {
			return index >= G.V();
		}

	};

};



/////////////// 利用邻接矩阵实现稀疏图 ///////////////

class SparseGraph {

private:

	int n;  //存放节点数
	int m;  //存放边数
	bool directed;  //是否为有向图
	vector<vector<int>> g;  //邻接表

public:

	//构造函数
	SparseGraph(int n, directed) {

		this->n = n;
		this->m = 0;
		this->directed = directed;

		for (int i = 0; i < n; ++i) {
			g.push_back(vector<int>());
		}

	}

	//析构函数
	~SparseGraph() {}

	//获取节点数
	int V() { return n; }

	//获取边数
	int E() { return m; }

	//判断两个节点是否存在边
	bool hasEdge(int v, int w) {

		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);

		for (int i = 0; i < g[v].size(); ++i) {
			if (g[v][i] == w) {
				retrun true;
			}
		}

		return false;

	}

	//为节点添加边
	void addEdge(int v, int w) {

		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);

		g[v].push_back(w);

		//如果当前图为无向图并且不为自环边的情况下,将w连接到v
		if (!directed && v != w) {
			g[w].push_back(v);
		}

		++m;

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
		int begin() {
			//起始迭代,将索引设置为0
			index = 0;
			//在v节点存在相邻节点的情况下返回下标第0个相邻节点
			if (G.g[v].size()) {
				return G.g[v][0];
			}
			//不存在相邻节点则返回-1
			return -1;
		}

		//返回迭代的下一个元素
		int next() {
			//访问下一个元素,将索引加1
			++index;
			//在索引没有越界的情况下返回下一个索引的相邻节点
			if (index < G.g[v].size()) {
				return G.g[v][index];
			}
			return -1;
		}

		//判断是否迭代完成
		bool end() {
			return index >= G.g[v].size();
 		}

	};

};



namespace GraphAlgorithm {

	/////////////// 通过文件读取图 ///////////////

	template <typename Graph>
	class ReadGraph {

	public:

		//构造函数,通过文件读取一个图

		/*	
		 * 使用文件表示图
			-----------------
			6 3 -> 第1行表示图的节点数和边数: V & E
			1 2 -> 第1行以后每行表示两个节点连接成一条边: v & w 
			1 4
			2 5
			-----------------
		*/

		/*
	     * 调用方式:
		     ----------------------------------
		     String filename = "d:/graph.txt";
		     SparseGraph graph(6, false);
		     ReadGraph readGraph(graph, filename);
		     ----------------------------------
		*/

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
				ss >> a >> b;
				assert(a >= 0 && a < V);
				assert(b >= 0 && b < V);
				graph.addEdge(a, b);
			}

		}

	};

	/////////////// 图的深度优先遍历和连通分量算法 ///////////////

	template <typename Graph>
	class Component {

	private:

		Graph &G;  //存放遍历的图的引用
		bool *visited;  //存放每个节点是否被访问过
		int ccount;  //存放连通分量
		int *id;  //存放连通情况

		//深度优先遍历
		void _dfs(int v) {

			//将当前节点的访问状态更新为已访问
			visited[v] = true;

			//相同连通分量的id相同,值即为ccount值即可
			id[v] = ccount;

			//使用临近节点迭代器进行相邻节点的遍历
			typename Graph::adjIterator iterator(G, v);
			for (int i = iterator.begin(); !iterator.end(); i = iterator.next()) {
				//如果当前相邻节点没有被访问过,需要继续递归访问当前节点
				if (!visited[i]) {
					_dfs(i);
				}
			}

		}

	public:

		//构造函数 - 深度优先遍历当前图
		Component(Graph &graph): G(graph) {

			//初始化成员变量	
			visited = new bool[G.V()];
			id = new int[G.V()];
			ccount = 0;
			//将所有节点都设置为未访问
			for (int i = 0; i < G.V(); ++i) {
				visited[i] = false;
				id[i] = -1;
			}

			//遍历每个节点,判断当前节点是否被访问,如果没被访问则进行深度优先递归,连通分量加1
			for (int i = 0; i < G.V(); ++i) {
				if (!visited[i]) {
					_dfs(i);
					++ccount;
				}
			}

		}

		//析构函数
		~Component() {
			delete [] visited;
			delete [] id;
		}

		//获取连通分量
		int count() {
			return ccount;
		}

		//判断连通性
		bool isConnected(int v, int w) {
			assert(v >= 0 && v < G.V());
			assert(w >= 0 && w < G.V());
			return id[v] == id[w];
		}

	};

	/////////////// 寻找连通路径算法 ///////////////

	template <typename Graph>
	class Path {
	private:

		Graph &G;  //存放图的引用
		int s;  //寻找连通路径的起始点
		bool *visited;  //存放每个节点是否被访问过
		int *from;  //从哪个节点遍历到的该节点

		//深度优先遍历
		void _dfs(int v) {

			visited[v] = true;

			typename Graph::adjIterator iterator<int>(G, v);
			for (int i = iterator.begin(); !iterator.end(); i = iterator.next()) {
				if (!visited[i]) {
					//记录遍历源
					from[i] = v;
					_dfs(i);
				}
			}

		}

	public:

		//构造函数
		Path(Graph graph, int s): G(graph) {

			//算法初始化
			assert(s >= 0 && s < G.V());
			visited = new bool[G.V()];
			from = new int[G.V()]
			this->s = s;

			//将所有节点的访问状态设置为未访问,所有节点的遍历源都为-1
			for (int i = 0; i < G.V(); ++i) {
				visited[i] = false;
				from[i] = -1;
			}

			//寻路算法: 以s点开始进行深度优先遍历
			_dfs(s);

		}

		//析构函数
		~Path() {
			delete [] visited;
			delete [] from;
		}

		//判断当前节点是否和起始点存在连通路径
		bool hasPath(int w) {
			assert(w >= 0 && w < G.V());
			return visited[w];
		}

		//获取当前节点与起始节点的连通路径
		void path(int w, vector<int> &vec) {
			
			stack<int> s;  //定义存放连通路径节点的栈
			
			//由当前节点倒序添加连通节点
			int p = w;
			while (from[p] != -1) {
				s.push(p);
				p = p.from[p];
			}

			//将连通节点正序放入vector
			vec.clear();
			while (!vec.empty()) {
				vec.push_back(vec.top());
				vec.pop();
			}

		}

		//显示当前节点与起始节点的连通路径
		void showPath(int w) {
			
			//调用path方法获取连通路径
			vector<int> vec;
			path(w, vec);

			//将连通路径循环打印
			for (int i = 0; i < vec.size(); ++i) {
				cout << vec[i];
				if (i == vec.size() - 1) {
					cout << endl;
				} else {
					cout << " -> ";
				}
			}

		}

	};

	/////////////// 图的广度优先遍历和最短路径算法 ///////////////

	template <typename Graph>
	class ShortestPath {
	
	private:
		
		Graph &G;  //遍历的图
		int s;  //源节点
		bool *visited;  //存放每个节点的访问状态
		int *from;  //存放节点的遍历来源
		int *ord;  //存放从源节点到每个节点的最短路径的长度

	public:
		
		//构造函数
		ShortestPath(Graph &graph, int s): G(graph) {

			//算法初始化
			assert(s >= 0 && s < G.V());
			visited = new bool[G.V()];
			from = new int[G.V()];
			ord = new int[G.V()];
			this->s = s;

			//访问状态初始化为false,遍历来源和最短路径初始化为-1
			for (int i = 0; i < G.V(); ++i) {
				visited[i] = false;
				from[i] = -1;
				ord[i] = -1;
			}

			//无向图最短路径算法

			queue<int> q;  //存放待遍历的节点
			//首先将源节点放入队列中
			q.push(s);
			visited[s] = true;
			ord[s] = 0;

			while (!q.empty()) {

				//取出队首元素并从出队
				int v = q.top();
				q.pop();

				//遍历当前出队节点的相邻节点
				typename Graph::adjIterator iterator(G, v);
				for (int i = iterator.begin(); !iterator.end(); i = iterator.next()) {
					//如果当前节点未被访问,则加入队列当中, 并维护visited & from & order
					if (!visited[i]) {
						q.push(i);
						visited[i] = true;
						from[i] = v;
						ord[i] = ord[v] + 1;
					}
				}

			}


		}

		//析构函数
		~ShortestPath() {
			delete [] visited;
			delete [] from;
			delete [] ord;
		}

		//判断两节点是否存在路径
		bool hasPath(int w) {
			assert(w >= 0 && w < G.V());
			return visited[w];
		}

		//获取两节点最短路径
		void path(int w, vector<int> &vec) {
			
			assert(w >= 0 && w < G.V());
			stack<int> s;

			//由当前节点倒序添加连通节点
			int p = w;
			while (p != -1) {
				s.push(p);
				p = from[p];
			}

			//将连通节点正序放入vector
			vec.clear();
			while (!s.empty()) {
				vec.push_back(p.top());
				p.pop();
			}

		}

		//显示最短路径
		void showPath(int w) {

			assert(w >= 0 && w < G.V());

			vector<int> vec;
			path(w, vec);

			for (int i = 0; i < vec.size(); ++i) {
				cout << vec[i];
				if (i == vec.size() - 1) {
					cout << endl;
				} else {
					cout << " -> ";
				}
			}

		}

		//查看当前节点最短路径的长度
		int length(int w) {
			assert(w >= 0 && w < G.V());
			return ord[w];
		}

	}

}










