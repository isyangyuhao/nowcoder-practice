#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <assert>

using namespace std;

/////////////////////// 二分查找算法 ///////////////////////

//二分查找,在有序的数组arr中,查找target
//如果找到target,返回对应的索引index
//如果没有找到target,返回-1
template <typename T>
int binarySearch(T arr[], int n, T target) {

	//在arr[l...r]中查找target
	int l = 0, r = n - 1;

	while (l <= r) {

		//存在 (l + r) 超出了int类型的表示范围风险
		//int mid = (l + r) / 2;
		
		int mid = l + (r - l) / 2;

		//如果中间值为目标查找元素,返回其索引
		if (arr[mid] == target) {
			return mid;
		}

		//如果中间值大于目标元素,则将右边界更新为中间值的前一个
		if (target < arr[mid]) {
			r = mid - 1;
		}

		//如果中间值小于目标元素,则将左边界更新为中间值的后一个
		else {
			l = mid + 1;
		}

	}

	return -1;

}

/////////////////////// 二分搜索树 ///////////////////////

/*
	--------------------------------
	二分搜索树的特点:
		是一颗二叉树
		每个节点的键值大于左孩子
		每个节点的键值小于右孩子
		左右孩子为根的子树仍为二叉搜索树
		二分搜索树不一定是完全二叉树
	--------------------------------
*/

template <typename Key, typename Value>
class BinarySearchTree {

private:

	//BST节点结构体
	struct Node {

		Key key;  //存放建
		Value value;  //存放值
		Node *left;  //存放左孩子指针
		Node *right;  //存放右孩子指针

		//结构体构造函数
		Node(Key key, Value value) {
			this->key = key;
			this->value = value;
			this->left = this->right = NULL;
		}

		//赋值Node节点构造函数
		Node (Node *node) {
			this->key = node->key;
			this->value = node->value;
			this->left = node->left;
			this->right = node->right;
		}

	};

	Node *root;  //BST的根
	int count;  //BST中存放的数据数

	//向BST中插入元素
	//以node为根的二叉搜索树中,插入节点key-value
	//返回新插入节点后的二叉树的根
	Node* _insert(Node *node, Key key, Value value) {

		//递归停止条件: 如果当前节点为空,则最终插入的节点即为此
		if (node == NULL) {
			return new Node(key, value);
			++count;
		}

		//如果插入的键就是当前BST的根,直接更新数据
		if (key == node->key) {
			node->value = value;
		}

		//如果插入的键小于当前BST根的键,则插入到当前BST的左孩子
		else if (key < node->key) {
			node->left = _insert(node->left, key, value);
		}

		//如果插入的键大于当前BST根的键,则插入到当前BST的右孩子
		else {
			node->right = _insert(node->right, key, value);
		}

		return node;

	}

	//查看以Node为根的BST中是否包含键值为key的节点
	bool _contain(Node *node, Key key) {

		//如果递归到底,则说明并未查找该key
		if (node == NULL) {
			return false;
		}

		if (key == node->key) {
			return true;
		}

		else if (key < node->key) {
			return _contain(node->left, key);
		}

		else {
			return _contain(node->right, key);
		}

	}

	//以node为根的二叉搜索树中查找key对应的value
	Value* _search(Node *node, Key key) {

		if (node == NULL) {
			return NULL;
		}

		if (key == node->key) {
			return &(node->value);
		}

		else if (key < node->key) {
			return _search(node->left, key);
		}

		else {
			return _search(node->right, key);
		}

	}

	//对以node为根的二叉搜索树进行前序遍历
	void _preOrder(Node *node) {

		if (node != NULL) {

			cout << node->key << endl;
			_preOrder(node->left);
			_preOrder(node->right);

		}

	}

	//对以node为根的二叉搜索树进行中序遍历
	void _inOrder() {

		if (node != NULL) {

			_preOrder(node->left);
			cout << node->key << endl;
			_preOrder(node->right);

		}

	}

	//对以node为根的二叉搜索树进行后序遍历
	void _postOrder() {

		if (node != NULL) {

			_preOrder(node->left);
			_preOrder(node->right);
			cout << node->key << endl;

		}

	}

	//释放BST空间
	void _destroy(Node *node) {

		if (node != NULL) {

			_destroy(node->left);
			_destroy(node->right);

			delete node;
			--count;
	
		}

	}

	//在以node为根的二叉搜索树中,返回最小值的节点
	Node* _minimum(Node *node) {

		if (node->left == NULL) {
			return node;
		}

		return _minimum(node->left);

	}

	//在以node为根的二叉搜索树,返回最大值的节点
	Node* _maximum(Node *node) {

		if (node->right == NULL) {
			return node;
		}

		return _maximum(node->right);

	}

	//删除以root为根的BST中的最小节点
	//返回删除节点后新的BST中的根
	Node* _removeMin(Node *node) {

		//如果当前节点的左孩子为空,代表已经是最小值,需要删除
		if (node->left == NULL) {
			//存放当前需要删除的右孩子,删除掉当前节点后返回当前节点为删除前的右孩子
			Node* rightNode = node->right;
			delete node;
			--count;
			return rightNode;
		}

		//如果当前节点不是最小值,则递归删除其左孩子为根的BST,返回其左孩子的node
		node->left =  _removeMin(node->left);

		return node;

	}

	//删除以root为根的BST中的最大节点
	//返回删除节点后新的BST中的根
	Node* _removeMax(Node *node) {

		if (node->right == NULL) {
			Node *leftNode = node->left;
			delete node;
			--count;
			return leftNode;
		}

		node->right = _removeMax(node->right);

		return node;

	}

	//删除掉以node为根的BST中键值为key的节点
	//返回删除节点后新的BST的根
	Node* _remove(Node *node, Key key) {

		//没有寻找到当前键值key
		if(node->key == NULL) {
			return NULL;
		}

		//如果删除键值小于当前BST根的键值,则递归删除BST的左子树,并更新左孩子节点,返回当前节点
		if (key < node->key) {
			node->left = _remove(node->left, key);
			return node;
		}

		//如果删除键值大于当前BST的根的键值,则递归删除BST的右子树,并更新右孩子节点,返回当前节点
		else if (key > node->key) {
			node->right = _remove(node->right, key);
			return node;
		}

		//key == node->key, 删除当前节点
		else {

			// > 如果删除的节点左孩子为空
			if (node->left == NULL) {
				Node rightNode = node->right;
				delete node;
				--count;
				return rightNode;
			}

			// > 如果删除的节点右孩子为空
			if (node->right == NULL) {
				Node leftNode = node->left;
				delete node;
				--count;
				return leftNode;
			}

			// > 如果删除的节点左右孩子都不为空 (Hubbard Deletion过程)

			//替换当前删除节点的节点,是当前删除节点右子树的最小值
			//由于successor节点会被下方删除,因此需要保存备份
			Node *successor = new Node(_minimum(node->right));  
			++count;  //由于删除节点需要--count,因此提前需要++count
			
			//设置替换节点的右孩子为removeMin后更新的BST根
			successor->right = _removeMin(node->right);
			//设置替换节点的左孩子为删除节点的左孩子
			successor->left = node->leftNode;

			//删除节点
			delete node;
			--count;

			return successor;

		}

	}


public:

	//构造函数
	BinarySearchTree() {
		root = NULL;
		count = 0;
	}

	//析构函数
	~BinarySearchTree() {	
		_destroy(root);
	}

	//返回存放数据数量
	int count() {
		return count;
	}

	//判断是否为空
	bool isEmpty() {
		return count == 0;
	}

	//向BST中插入元素接口
	void insert(Key key, Value value) {
		root = _insert(root, key, value);
	}

	//判断当前二叉树中是否存在键值为key的元素接口
	bool contain(Key key) {
		return _contain(root, key);
	}

	//通过键搜索对应存储的值接口,返回类型为指向value的指针
	Value* search(Key key) {
		return _search(root, key);
	}

	//前序遍历BST接口
	void preOrder() {
		_preOrder(root);
	}

	//中序遍历BST接口
	void inOrder() {
		_inOrder(root);
	}

	//后续遍历BST接口
	void postOrder() {
		_postOrder(root);
	}

	//广度优先遍历(层序遍历)
	void levelOrder() {
		
		queue<Node*> q;
		q.push(root);

		//在队列不为空的情况下,出队首元素,然后如果含有左右孩子则分别入队
		while (!q.empty()) {

			Node *n = q.front();
			q.pop();

			cout << n->key << endl;

			if (node->left) {
				q.push(node->left);
			}
			if (node->right) {
				q.push(node->right);
			}

		}

	}

	//寻找最小值的key接口
	Key minimum() {

		assert(count != 0);

		Node* minNode = _minimum(root);
		return minNode->key;
	}

	//寻找最大值的key接口
	Key maximun() {

		assert(count != 0);

		Node* maxNode = _maximum(root);
		return maxNode->key;

	}

	//删除最小值节点接口
	void removeMin() {
		if (root) {
			root = _removeMin(root);
		}
	}

	//删除最大值节点接口
	void removeMax() {
		if (root) {
			root = _removeMax(root);
		}
	}

	//删除BST中键值为key的节点接口
	void remove(Key key) {
		_remove(root, Key key);
	} 

};










