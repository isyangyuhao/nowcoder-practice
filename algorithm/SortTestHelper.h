#include <iostream>
#include <string>
#include <ctime>
#include <cassert>

using namespace std;

namespace SortTestHelper {

	//生成n个元素的随机数组,每个元素的随机范围为[rangeL, rangeR]
	int* generatorRandomArray(int n, int rangeL, int rangeR) {

		assert(rangeL <= rangeR);  //断言rangeL<=rangeR

		int *arr = new int[n];  //开辟n个int类型的数组空间
		srand(time(NULL));  //设置随机因子
		for (int i = 0; i < n; ++i) {
			arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
		}
		
		return arr;
	}

	//遍历输出数组元素
	template <typename T>
	void printArray(T arr[], int n) {

		for (int i = 0; i < n; ++i) {
			cout << arr[i] << " ";
		}
		cout << endl;

	}

	//判断排序是否成功
	template <typename T>
	bool isSorted(T arr[], int n) {
		
		for (int i = 0; i < n - 1; ++i) {
			if (arr[i] > arr[i + 1]) {
				return false;
			}
		}

		return true;
	}

	//测试算法性能
	template <typename T>
	void testSort(string sortName, void(*sort)(T[], int), T arr[], int n) {
		
		//记录排序开始和结束的时间
		clock_t startTime = clock();
		sort(arr, n);
		clock_t endTime = clock();

		assert(isSorted(arr, n));  //验证排序是否真确

		cout << sortName << " : " << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;
		
		return ;
	}

	//拷贝整型数组
	int* copyIntArray(int a[], int n) {
		int* arr = new int[n];
		copy(a, a + n, arr);
		return arr; 
	}

	//生成排序近乎完成的数组
	int* generatorNearlyOrderedArray(int n, int swapTimes) {
		
		int* arr = new int[n];

		//生成有序数组
		for (int i = 0; i < n; ++i) {
			arr[i] = i;
		}

		srand(time(NULL));

		//随机将数组中的两个元素置换
		for (int i = 0; i < swapTimes; ++i) {
			int postX = rand() % n;
			int postY = rand() % n;
			swap(postX, postY);
		}

		return arr;

	}

}