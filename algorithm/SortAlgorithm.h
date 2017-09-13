#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

namespace SortAlgorithm {

	//========== 选择排序 ==========
	template <typename T>
	void selectionSort(T arr[], int n) {

		for (int i = 0; i < n; ++i) {
			//寻找[i,n)中的最小值
			int minIndex = i;
			for (int j = i + 1; j < n; ++j) {
				if (arr[j] < arr[minIndex]) {
					minIndex = j;
				}
			}
			//将当前值和最小值交换
			swap(arr[i], arr[minIndex]);
		}

	}

	//========== 插入排序(使用交换) ==========
	template <typename T>
	void insertionSort(T arr[], int n) {

		for (int i = 1; i < n; ++i) {

			//寻找arr[i]的合适插入位置
			for (int j = i; j > 0; --j) {
				//如果当期元素的值比前一个还要小,则交换位置
				if (arr[j] < arr[j - 1]) {
					swap(arr[j], arr[j - 1]);
				} else {
					//如果当前元素比前一个大,则跳出循环,继续下一个元素的插入
					break;
				}
			}

		}

	}

	//========== 改进后的插入排序(使用赋值) ==========
	template <typename T>
	void insertionSortResult(T arr[], int n) {

		for (int i = 1; i < n; ++i) {

			T e = arr[i];  //拷贝当前插入元素
			int j;  //保存元素的插入位置

			for (j = i; j > 0 && e < arr[j - 1]; --j) {
				arr[j] = arr[j - 1];
			}

			arr[j] = e;

		}

	}

	//========== 归并排序(自顶向下的递归) ==========

	//将arr[l...mid]和arr[mid+1...r]两部分进行归并
	template <typename T>
	void _merge(T arr[], int l, int mid, int r) {

		//开辟临时存储空间,并将需要归并的数组元素拷贝其中
		T aux[r - l + 1];
		for (int i = l; i <= r; ++i) {
			aux[i - l] = arr[i];
		}

		//在临时空间中,进行左右两部分的比较,选出最小的放到数组中
		int i = l, j = mid + 1;
		for (int k = l; k <= r; ++k) {
			if (i > mid) {
				arr[k] = aux[j - l];
				++j;
			} else if (j > r) {
				arr[k] = aux[i - l];
				++i;
			} else if (aux[i - l] < aux[j - l]) {
				arr[k] = aux[i - l];
				++i;
			} else {
				arr[k] = aux[j - l];
				++j;
			}
		}

	}

	//递归使用归并排序,对arr[l...r]范围内进行排序
	template <typename T>
	void _mergeSort(T arr[], int l, int r) {

		//如果左边界大于等于右边界,则代表需要不需要继续归并
		if(l >= r) {
			return;
		}

		//对左右两部分进行递归调用
		int mid = (l + r) / 2;
		_mergeSort(arr, l, mid);
		_mergeSort(arr, mid + 1, r);

		//对左右两部分进行归并,如果左部分的最大值比又部分的最小值还要小则无需排序
		if (arr[mid] > arr[mid + 1]) {
			_merge(arr, l, mid, r);
		}

	}

	template <typename T>
	void mergeSort(T arr[], int n) {
		_mergeSort(arr, 0, n - 1);
	}

	//========== 归并排序(自底向上的迭代) ==========
	
	template <typename T>
	void mergeSortBU(T arr, int n) {

		//size - 归并元素的个数(1, 2, 4, 8 ...)
		for (int size = 1; size <= n; size += size) {

			//对 arr[i...i+size-1] 和 arr[i+size...i+size+size-1]进行归并
			for (int i = 0; i + size < n; i += size + size) {
				_merge(arr, i, i + size - 1, min(i + size + size - 1, n - 1));
			}

		}

	}

	/*
		---------------------------------
		求解逆序对个数算法:
		通过归并操作,当归并右部分元素时,计算此时左部分尚未归并的元素个数
		递归累加后结果为逆序对的全部个数
		此时的算法复杂度为O(nlogn)级别
		---------------------------------
	*/

	//========== 快速排序 ==========

	//对arr[l...r]部分进行partition操作
	//返回p,使得arr[l...p-1] < arr[p] < arr[p+1...r]
	template <typename T>
	int _partition(T arr[], int l, int r) {

		//随机生成标定点
		swap(arr[rand() % (r - l + 1) + l], arr[l]);

		T v = arr[l];

		//arr[l+1...j] < v; arr[j+1...i) > v
		int j = l;
		for (int i = l + 1; i <= r; ++i) {

			if (arr[i] < v) {
				swap(arr[j + 1], arr[i]);
				++j;
			}

		}

		swap(arr[j], arr[l]);

		return j;

	}

	//对 arr[l...r]部分进行排序排序
	template <typename T>
	void _quickSort(T arr[], int l, int r) {

		if (l >= r) {
			return ;
		}

		int p = _partition(arr, l, r);

		//对排序好的元素p的左右分别进行递归
		_quickSort(arr, l, p - 1);
		_quickSort(arr, p + 1, r);

	}

	template <typename T>
	void quickSort(T arr[], int n) {

		srand(time(NULL));
		_quickSort(arr, 0, n - 1);
	
	}

	//========== 双路快速排序 ==========

	template <typename T>
	int _partition2Ways(T arr[], int l, int r) {

		swap(arr[l], arr[rand() % (r - l + 1) + l]);

		T v = arr[l];

		//arr[l...i) <= v, arr(j...r] >= v
		int i = l + 1, j = r;

		while (true) {

			//如果左部分元素小于目标元素,则继续向下移动
			while (i <= r && arr[i] < v) {
				++i;
			}

			//如果右部分元素大于目标元素,则继续向前移动
			while (j >= l + 1 && arr[j] > v) {
				--j;
			}

			//如果左指针大于等于右指针,说明数组遍历完成,退出循环
			if (i >= j) {
				break;
			}

			//在左部分元素大于目标元素或右部分元素小于目标元素时,双方交换元素,然后指针继续移动
			swap(arr[i], arr[j]);
			++i;
			--j;

		}

		swap(arr[l], arr[j]);

		return j;

	}

	template <typename T>
	void _quickSort2Ways(T arr[], int l, int r) {

		if (l >= r) {
			return ;
		}

		int p = _partition2Ways(arr, l, r);

		_quickSort2Ways(arr, l, p - 1);
		_quickSort2Ways(arr, p + 1, r);

	}

	template <typename T>
	void quickSort2Ways(T arr[], int n) {

		srand(time(NULL));

		_quickSort2Ways(arr, 0, n - 1);

	}

	//========== 三路快速排序 ==========

	//将arr[l...r]分为 <v; ==v; >v 三部分
	//然后递归 <v 和 >v 部分, 继续进行三路快排
	template <typename T>
	void _quickSort3Ways(T arr[], int l, int r) {

		if (l >= r) {
			return ;
		}

		//partition部分

		swap(arr[l], arr[rand() % (r - l + 1) + l]);
		T v = arr[l];

		int lt = l;  //  arr[l+1...lt] < v
		int gt = r + 1;  //arr[gt...r] > v
		int i = l + 1;  //arr[lt+1...i) == v

		while (i < gt) {

			if (arr[i] < v) {
				swap(arr[i], arr[lt + 1]);
				++lt;
				++i;
			} else if (arr[i] > v) {
				swap(arr[i], arr[gt - 1]);
				--gt;
			} else {
				++i;
			}

		}

		swap(arr[l], arr[lt]);

		//递归部分

		_quickSort3Ways(arr, l, lt - 1);
		_quickSort3Ways(arr, gt, r);

	}

	template <typename T>
	void quickSort3Ways(T arr[], int n) {

		srand(time(NULL));
		_quickSort3Ways(arr, 0, n - 1);

	}

	/*
		---------------------------------
		求解排序好的数组中第n个元素的值算法:
		通过partition操作,返回的p为当前标定点的索引;
		求解第n个排序好的元素,只需要比较n与p的大小,然后只需要调用左右一方进行递归即可
		此时的算法复杂度为O(2n)级别
		---------------------------------
	*/

	/*
		---------------------------------
		排序算法总结:
			++++++++++++++++++++++++++++++++++++++++++++++++++
			算法名称 | 时间复杂度 | 原地排序 | 额外空间 | 稳定排序
			插入排序    O(n^2)       Y       O(1)       Y
			归并排序   O(nlogn)      N       O(n)       Y 
			快速排序   O(nlogn)      Y       O(logn)    N
			堆排序     O(nlogn)      Y       O(1)       N
			++++++++++++++++++++++++++++++++++++++++++++++++++
		算法稳定性: 对于相等的元素,排序后相等元素的相对位置没有发生改变
		---------------------------------
	*/

}
