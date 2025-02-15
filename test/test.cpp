#include <iostream>
#include <vector>
using namespace std;
// 不用vector要传size
// void insert_sort(int *data,int size)
// {
//     for (int i = 1;i < size;i++) {
//         int key = data[i];
//         int j = i - 1;
//         while (j >= 0 && data[j] > key) {
//             data[j + 1] = data[j];
//             j--;
//         }
//         data[j + 1] = key;
//     }
// }

// 直接插入排序，O(n^2)，稳定
void insert_sort(vector<int> &data)
{
    for (int i = 1;i < data.size();i++) {
        int key  = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > key) {
            swap(data[j],data[j+1]);
            //data[j + 1] = data[j];
            j--;
        }
        //data[j + 1] = key;
    }
}
// 希尔排序，O(n^1.3)(nlogn)，不稳定
void shell_sort(vector<int> &data)
{
    int gap = data.size() / 2;
    while (gap > 0) {
        for (int i = gap;i < data.size();i++) {
            int key = data[i];
            int j = i - gap;
            while (j >= 0 && data[j] > key) {
                data[j + gap] = data[j];
                j -= gap;
            }
            data[j + gap] = key;
        }
        gap /= 2;
    }
}
// 冒泡排序，O(n^2)，稳定
void bubble_sort(vector<int> &data)
{
    for (int i = 0;i < data.size()-1;i++) {
        for (int j = 0;j < data.size()-1-i;j++) {
            if (data[j] > data[j+1]) {
                swap(data[j],data[j+1]);
            }
        }
    }
}
// 快速排序，O(nlogn)，不稳定
void quick_sort(vector<int> &data,int left,int right)
{
    if (left >= right) return;
    int l = left,r = right,mid = left,key = data[left];
    while (l < r) {
        while (r > l && data[r] >= key) r--;
        data[l] = data[r];
        while (l < r && data[l] <= key) l++;
        data[r] = data[l];
    }
    data[l] = key;
    quick_sort(data,left,l-1);
    quick_sort(data,l+1,right);
}
// 直接选择排序，O(n^2)，不稳定
void choose_sort(vector<int> &data)
{
    for (int i = 0;i < data.size()-1;i++) {
        int min_id = i;
        for (int j = i;j < data.size();j++) {
            if (data[j] < data[min_id]) {
                min_id = j;
            }
        }
        swap(data[min_id],data[i]);
    }
}
// 堆排序，O(nlogn)，不稳定
void heap_up(vector<int> &data,int l,int r)
{
    int dad = l,son = 2 * dad + 1;
    while (son <= r) {
        if (son + 1 <= r && data[son] < data[son+1]) son++;
        if (data[dad] > data[son]) return;
        swap(data[dad],data[son]);
        dad = son;
        son = 2 * dad + 1;
    }
}
void heap_sort(vector<int> &data)
{
    for (int i = data.size() / 2 - 1;i >= 0;i--) {
        heap_up(data,i,data.size()-1);
    }
    for (int i = data.size() - 1;i > 0;i--) {
        swap(data[0],data[i]);
        heap_up(data,0,i-1);
    }
}
// 归并排序，O(nlogn)，稳定
void merge_sort(vector<int> &data,int l,int r)
{
    if (l >= r) return;
    int mid = (l + r) / 2;
    merge_sort(data,l,mid);
    merge_sort(data,mid+1,r);
    int p1 = l,p2 = mid + 1;
    int p3 = 0;
    vector<int> temp(r - l + 1);
    while (p1 <= mid && p2 <= r) {
        if (data[p1] < data[p2]) {
            temp[p3] = data[p1];
            p1++;p3++;
        } else {
            temp[p3] = data[p2];
            p2++;p3++;
        }
    }
    while (p1 <= mid) {
        temp[p3] = data[p1];
        p1++;p3++;
    }
    while (p2 <= r) {
        temp[p3] = data[p2];
        p2++;p3++;
    }
    for (int i = 0;i < r - l + 1;i++) {
        data[l + i] = temp[i];
    }
}
// 基数排序，O(n*k)，稳定
int maxbit(vector<int> &data, int n) 
{
    int maxData = data[0];             
    for (int i = 1; i < n; ++i)
    {
        if (maxData < data[i])
            maxData = data[i];
    }
    int d = 1;
    int p = 10;
    while (maxData >= p)
    {
        maxData /= 10;
        ++d;
    }
    return d;
}
void radixsort(vector<int> &data, int n) 
{
    int d = maxbit(data, n);
    vector<int> tmp(n);
    vector<int> count(10); 
    int i, j, k;
    int radix = 1;
    for(i = 1; i <= d; i++)
    {
        for(j = 0; j < 10; j++)
            count[j] = 0;
        for(j = 0; j < n; j++)
        {
            k = (data[j] / radix) % 10; 
            count[k]++;
        }
        for(j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j];
        for(j = n - 1; j >= 0; j--) 
        {
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            count[k]--;
        }
        for(j = 0; j < n; j++) 
            data[j] = tmp[j];
        radix = radix * 10;
    }
}
int main()
{
    int n;
    cin>>n;
    //int data[n];
    vector<int> data(n);
    for (int i = 0;i < n;i++) cin>>data[i];
    radixsort(data,data.size());
    for (int i = 0;i < n;i++) cout<<data[i]<<" ";
    return 0;
}