#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <mutex>
#include <list>
#include <queue>
#include <utility>
#include <functional>
#include <condition_variable>
#include <future>
#include <windows.h>
using namespace std;
/*
这篇代码是在暑假的project：并行快速排序上写的，所以只对其中一些代码进行了删减。
快速排序它的基本思想是：通过一次排序将数据分割成独立的两部分，其中一部分的所有数据都比另外一部分的所有数据都要小，
然后再按照此方法对这两部分数据分别进行快速排序，整个排序过程可以递归并行处理，以此达到整个数据变成有序序列。
其过程主要分为三个阶段:
1) 在待排序的序列中找出一个枢轴;
2) 根据枢轴将待排序的序列划分成两个不相交的子序列，其中一个子序列里的元素全部不小于枢轴，另一个子序列
里的元素全部不大于枢轴;
3) 分别对两个子序列递归进行快速排序，直到划分出的子序列的长度为1。
*/

vector<int> random_vector(size_t size);

class Task {
    public:
        Task(vector<int> &vec, int first, int last) : vec_(vec), first_(first), last_(last) {}
        vector<int> &vec_;
        int first_, last_;
    };

    void swap(int & a,int & b){
        a = a + b;
        b = a - b;
        a = a - b;
    }

    void InsertSort(vector<int> &vec, int first, int last) {
        int temp;
        int i, j;
        for (int i = first + 1; i <= last; i++)
        {
                if (vec[i] < vec[i - 1])
                {
                    temp = vec[i];
                    j = i - 1;
                    do{
                        vec[j + 1] = vec[j];
                        j--;
                    } while (j >= first && temp < vec[j]);
                    vec[j + 1] = temp;
                }
        }
    }

/*
由于采用递归来进行排序，当序列的长度较小时，频繁的递归操作也会影响排序的性能。使用“三点取中”的方法，
用序列中的头、尾和中点这三个关键字的中间值来作为枢轴，有效地避免了快速排序在最坏情况下的性能恶化。
*/

    int median3(vector<int> &vec, int first, int last)//
        {
            int mid = first+((last-first+1) >> 1);
            int k=last;
            if(vec[mid]<vec[k])
                k = mid;
                if(vec[last]<vec[k])
                    k = last;
                    if(k!=first && vec[mid]<vec[last])
                        swap(vec[mid], vec[last]);
                        return vec[last];
                
        }


    int  partition(vector<int> &vec, int first, int last){
        int i = first, j = last;
        if(first<last){
                int pivot = median3(vec, first, last); 
                for (;;){
                    while(i<j && vec[i]<pivot)
                        i++;
                    while(i<j && vec[j]>pivot)
                        j--;
                    if(i<j)
                {
                    swap(vec[i], vec[j]);
                    i++;
                    j--;
                }else
                    break;}
                
                if(vec[i]>pivot){
                    vec[last] = vec[i];
                    vec[i] = pivot;
                }
        }
        return i;
    }


    void quick_sort(vector<int> &vec, int first, int last)
    {
        if(first<last)
        {
            if((last-first)<= 16) 
            return;
            int pivotpos = partition(vec, first, last);
            quick_sort(vec, first, pivotpos - 1);
            quick_sort(vec, pivotpos + 1, last);
            }
    }
/*
快速排序的递归操作在序列长度较小时会影响排序的效率，应该使用其他非递归算法来处理小序列。直接插入排
序是对小序列进行处理的有效方法，为此设置一个阈值M，当快速排序过程中划分出的子序列的长度小于或等于M 时，不
再递归调用快速排序而使用直接插入排序，以避免对小序列排序时的频繁递归，这里的阈值为16，quick_sort中若(last-first)<= 16就return执行直插。
*/

    void HybridSort(vector<int> &vec,int first, int last)
        {
            quick_sort(vec, first, last);
            InsertSort(vec, first, last);
        }

	vector<int> random_vector(size_t size){

		vector<int> vec;

		for (int i = 0; i < size; i++)

			vec.push_back(rand() % size); //put a random number between 0 and size

		return vec;

	}


int main()
{
    std::vector<int> vec1 = random_vector(666);//随机产生具有300个随机数的向量
    std::vector<int> vec2(vec1);

    cout << "Before QuickSort:" << endl;

    //ShowVec(vec);
     cout << "-------------------" << endl;
        for(auto val : vec2){
        cout << val <<" ";
        };

    HybridSort(vec2, 0, vec2.size());

    // parallel_quick_sort(vec2, 0, vec2.size());
    cout << "" << endl;
    cout << "" << endl;
    cout << "After QuickSort:" << endl;
    cout << "-------------------" << endl;
    //ShowVec(vec);
    for (auto val : vec2)
    {
        cout << val << " ";
    }
    system("pause");
    return	0;
}



