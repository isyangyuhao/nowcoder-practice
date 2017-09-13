#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include <cmath>
#include <cassert>
#include <typeinfo>

using namespace std;

/*
	-----------------------------
	优先队列:
		  普通的队列是一种先进先出的数据结构,元素在队列尾追加,而从队列头删除.
		在优先队列中,元素被赋予优先级.当访问元素时，具有最高优先级的元素最先删除
		优先队列具有最高级先出(first in, largest out)的行为特征.

	实现有线队列的复杂度:
		+++++++++++++++++++++++++++++++++
		实现方式 | 入队复杂度 | 出队复杂度
		普通数组     O(1)       O(n)
		有序数组     O(n)       O(1)
		堆          O(logn)    O(logn)
		+++++++++++++++++++++++++++++++++

	二叉堆: 1) 堆是一颗完全二叉树 2) 堆中某个节点的值总是不大于其父节点的值(大顶堆)
	-----------------------------
*/


/////////////////////////// 实现大顶堆类 ///////////////////////////

template <typename Item>
class MaxHeap {

private:

	Item* data;  //存放数据空间
	int count;  //存放数据个数
	int capacity;  //存放数据空间的容量

	//将k位置的元素向上移动到符合大顶堆的位置
	void _shiftUp(int k) {

		while (k > 1 && data[k] > data[k / 2]) {
			swap(data[k], data[k / 2]);
			k /= 2;
		}

	} 

	//将k位置的元素向下移动到符合大顶堆的位置
	void _shiftDown(int k) {

		while (2 * k <= count) {

			int j = 2 * k;

			if (j + 1 <= count && data[j + 1] > data[j]) {
				++j;
			}

			if (data[k] > data[j]) {
				break;
			}

			swap(data[k], data[j]);
			k = j;

		}

	} 

public:

	//构造函数,创建存储空间(通过容量创建)
	MaxHeap(int capacity) {
		data = new Item[capacity + 1];
		this->capacity = capacity;
	}

	//构造函数,通过数组创建大顶堆
	MaxHeap(Item arr[], int n) {
		
		data = new Item[n + 1];
		this->capacity = n;

		//将数组中的元素赋值到堆中
		for (int i = 0; i < n; ++i) {
			data[i + 1] = arr[i];
		}
		count = n;

		//Heapify过程 [算法复杂度为O(n)]
		//将非叶子节点的所有节点进行shiftDown操作
		for (int i = count / 2; i >= 1; --i) {
			_shiftDown(i);
		}

	}

	//析构函数,释放存储空间
	~MaxHeap() {
		delete [] data;
	}

	//返回元素个数
	int size() {
		return count;
	}

	//判断当前堆中是否为空
	bool isEmpty() {
		return count == 0;
	}

	//添加新的元素
	void insert(Item item) {

		assert(count + 1 <= capacity);

		data[count + 1] = item;
		++count;
		_shiftUp(count);  //将当前插入元素向上移动到符合大顶堆的位置

	}

	//取出最大的元素
	Item extractMax() {

		assert(count > 0);

		Item ret = data[1];
		swap(data[1], data[count]);  //将最后一个元素移动到根节点
		--count;
		_shiftDown(1);  //将根节点的元素向下移动到符合大顶堆的位置

		return ret;

	}

/////////////////////////// 打印二叉树函数 ///////////////////////////
private:
    void putNumberInLine( int num, string &line, int index_cur_level, int cur_tree_width, bool isLeft){

        int sub_tree_width = (cur_tree_width - 1) / 2;
        int offset = index_cur_level * (cur_tree_width+1) + sub_tree_width;
        assert(offset + 1 < line.size());
        if( num >= 10 ) {
            line[offset + 0] = '0' + num / 10;
            line[offset + 1] = '0' + num % 10;
        }
        else{
            if( isLeft)
                line[offset + 0] = '0' + num;
            else
                line[offset + 1] = '0' + num;
        }
    }

    void putBranchInLine( string &line, int index_cur_level, int cur_tree_width){

        int sub_tree_width = (cur_tree_width - 1) / 2;
        int sub_sub_tree_width = (sub_tree_width - 1) / 2;
        int offset_left = index_cur_level * (cur_tree_width+1) + sub_sub_tree_width;
        assert( offset_left + 1 < line.size() );
        int offset_right = index_cur_level * (cur_tree_width+1) + sub_tree_width + 1 + sub_sub_tree_width;
        assert( offset_right < line.size() );

        line[offset_left + 1] = '/';
        line[offset_right + 0] = '\\';
    }
public:
	void testPrint(){

        if( size() >= 100 ){
            cout<<"Fancy print can only work for less than 100 int";
            return;
        }

        if( typeid(Item) != typeid(int) ){
            cout <<"Fancy print can only work for int item";
            return;
        }

        cout<<"The Heap size is: "<<size()<<endl;
        cout<<"data in heap: ";
        for( int i = 1 ; i <= size() ; i ++ )
            cout<<data[i]<<" ";
        cout<<endl;
        cout<<endl;

        int n = size();
        int max_level = 0;
        int number_per_level = 1;
        while( n > 0 ) {
            max_level += 1;
            n -= number_per_level;
            number_per_level *= 2;
        }

        int max_level_number = int(pow(2, max_level-1));
        int cur_tree_max_level_number = max_level_number;
        int index = 1;
        for( int level = 0 ; level < max_level ; level ++ ){
            string line1 = string(max_level_number*3-1, ' ');

            int cur_level_number = min(count-int(pow(2,level))+1,int(pow(2,level)));
            bool isLeft = true;
            for( int index_cur_level = 0 ; index_cur_level < cur_level_number ; index ++ , index_cur_level ++ ){
                putNumberInLine( data[index] , line1 , index_cur_level , cur_tree_max_level_number*3-1 , isLeft );
                isLeft = !isLeft;
            }
            cout<<line1<<endl;

            if( level == max_level - 1 )
                break;

            string line2 = string(max_level_number*3-1, ' ');
            for( int index_cur_level = 0 ; index_cur_level < cur_level_number ; index_cur_level ++ )
                putBranchInLine( line2 , index_cur_level , cur_tree_max_level_number*3-1 );
            cout<<line2<<endl;

            cur_tree_max_level_number /= 2;
        }
    }

};

/////////////////////////// 堆排序 ///////////////////////////

namespace HeapSort {

	//最原始的堆排序
	template <typename T>
	void heapSort1(T arr[], int n) {

		MaxHeap<T> maxHeap = MaxHeap<T>(n);

		//将数组中的全部元素放到大顶堆中
		for (int i = 0; i < n; ++i) {
			maxHeap.insert(arr[i]);
		}

		//将大顶堆中的元素依次取出,因大顶堆是由大到小取出,因此需要数组倒序赋值
		for (int i = n - 1; i >= 0; --i) {
			arr[i] = maxHeap.extractMax();
		}

	}

	//使用heapify操作的堆排序
	template <typename T>
	void heapSort2(T arr[], int n) {

		//将数组直接转换为大顶堆
		MaxHeap<T> maxHeap = MaxHeap<int>(arr, n);

		for (int i = n - 1; i >= 0; --i) {
			arr[i] = maxHeap.extractMax();
		}
	
	}


	//原地堆排序
	template <typename T>
	void _shiftDown(T arr[], int n, int k) {

		while (2 * k + 1 < n) {

			int j = 2 * k + 1;

			if (j + 1 < n && arr[j] < arr[j + 1]) {
				++j;
			}

			if (arr[k] > arr[j]) {
				break;
			}

			swap(arr[k], arr[j]);
			k = j;

		}

	}

	template <typename T>
	void heapSort(T arr[], int n) {

		/*
			----------------------
			使用数组直接进行堆排序,规律会发生变化
			根节点: 1 -> 0
			左孩子: count -> count + 1
			右孩子: count + 1 -> count + 2
			最后一个节点: count -> count - 1
			最后一个非叶子节点 count / 2 -> (count - 1) / 2
			----------------------
		*/

		//heapify

		for (int i = (n - 1) / 2; i >= 0; --i) {
			_shiftDown(arr, n, i);
		}

		//将根节点与数组末尾元素交换,然后根节点执行shiftDown,依次进行直到排序结束

		for (int i = n - 1; i >= 0; --i) {
			swap(arr[i], arr[0]);
			_shiftDown(arr, i, 0);
		}

	}

}


/////////////////////////// 索引最大堆类 ///////////////////////////

/*
	索引堆: 堆中存储的是数组的下标号,而不是数据本身
	++++++++++++++++++++++++++++++++++++++++++++++
	0      1   2   3   4   5   6   7   8   9   10
	++++++++++++++++++++++++++++++++++++++++++++++
	index  10  9   7   8   5   6   3   1   4   2
	++++++++++++++++++++++++++++++++++++++++++++++
	data   34  24  56  42  79  54  21  45  64  21
	++++++++++++++++++++++++++++++++++++++++++++++
	rev    8   10  7   9   5   6   3   4   2   1
	++++++++++++++++++++++++++++++++++++++++++++++
*/

template <typename T>
class IndexMaxHeap {

private:

	Item* data;
	int* indexes;  //存放索引
	int* reverse;  //存放索引在堆中的位置
	int count;
	int capacity;

	_shiftUp(int k) {

		while (k > 1 && data[indexes[k]] > data[indexes[k / 2]]) {
			swap(indexes[k], indexes[k / 2]);
			reverse[indexes[k / 2]] = k / 2;
			reverse[indexes[k]] = k;
			k = k / 2;
		}

	}

	_shiftDown(int k) {

		while (2 * k <= count) {

			int j = 2 * k;

			if (data[indexes[j]] < data[indexes[j + 1]]) {
				++j;
			}

			if (data[indexes[k]] < data[indexes[j]]) {
				break;
			}

			swap(indexes[k], indexes[j]);
			reverse[indexes[k]] = k;
			reverse[indexes[j]] = j;
			k = j;

		}

	}

public:

	IndexMaxHeap(int capacity) {

		data = new Item[capacity + 1];
		indexes = new int[capacity + 1];
		reverse = new int[capacity + 1];

		//初始化reverse为0
		for (int i = 0; i <= capacity; ++i) {
			reverse[i] = 0;
		}

		this->capacity = capacity;
		count = 0;

	}

	~IndexMaxHeap() {
		delete [] data;
		delete [] indexes;
		delete [] reverse;
	}

	int size() {
		return count;
	}

	bool isEmpty() {
		return count == 0;
	}

	//对于用户而言,索引是从0开始
	void insert(int i, Item item) {

		assert(count + 1 <= capacity);
		assert(i + 1 >= 1 && i + 1 <= capacity);
		++i;

		data[i] = item;  //存储空间的下标按照索引号存储
		indexes[count + 1] = i;  //将索引记录到索引数组中
		reverse[i] = count + 1;  //将索引记录的下标存放到reverse数组中

		++count;
		_shiftUp(count);

	}

	Item extractMax() {

		assert(count >= 1);

		Item ret = data[indexes[count]];

		swap(indexes[1], indexes[count]);
		reverse[indexes[1]] = 1;
		reverse[indexes[count]] = 0;  //当前下标的元素已被删除

		--count;
		_shiftDown(1);

		return ret;

	}

	//取出最大元素,并返回其索引号
	int extractMaxIndex() {

		assert(count >= 1);

		int ret = indexes[1] - 1;

		swap(indexes[1], indexes[count]);
		reverse[indexes[1]] = 1;
		reverse[indexes[count]] = 0;  //当前下标的元素已被删除

		--count;
		_shiftDown(1);

		return ret;

	}

	//判断当前索引中是否包含元素
	bool contain(int i) {
		++i;
		assert(i >= 1 && i <= capacity);
		return reverse[i] != 0;
	}

	//通过索引号获取对应元素的值
	Item getItem(int i) {

		//断言当前索引i包含元素
		assert(contain(i));

		return data[i + 1];
	}

	//修改指定索引的元素值
	void change(int i, Item item) {

		//断言当前索引i包含元素
		assert(contain(i));

		++i;
		data[i] = item;

		//找到indexes[j] = i, j表示data[i]在堆中的位置
		//先shiftUp(j), 后shiftDown(j)

		// > 时间复杂度为O(n)

		// for (int j = 1; j <= count; ++j) {
		// 	if (indexes[j] == i) {
		// 		_shiftUp(j);
		// 		_shiftDown(j);
		// 		return ;
		// 	}
		// }

		// > 时间复杂度为O(1)

		int j = reverse[i];
		_shiftUp(j)
		_shiftDown(j);

	}

};

/*
	---------------------------------
	* 在n个元素中取出前m个元素算法:
		建立一个m容量的小顶堆,将n个元素放入其中,
		最终小顶堆中的元素就是n个元素中最小的m个,
		此时的算法复杂度为O(nlogm)
	* 可以通过堆来实现多路归并排序,每个部分装到一个小顶堆中,每次弹出最小值进行归并操作
	* 最大堆小堆: 每次可以选择最大权重出队,也可以选择最小权重出队; 通过一组数据同时构建大顶堆和小顶堆实现
	---------------------------------
*/