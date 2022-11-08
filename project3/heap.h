#include <vector>
#include <iostream>

using namespace std;


template <typename T> class heap {
    public:
        heap(vector<T>);
        void initializeMaxHeap(vector<T> A);
        void buildMaxHeap();
        void maxHeapify(int i);
        int parent(int i);
        int left(int i);
        int right(int i);
        T getItem(int n);
        vector<T> heapsort();

    private:
        vector<T> A;
        void exchange(int i, int j);

};



template <typename T>
heap<T>::heap(vector<T> A) {

    initializeMaxHeap(A);
}

template <typename T>
void heap<T>::initializeMaxHeap(vector<T> Array) {
    A.resize(Array.size());
    for (int i = 0; i < Array.size(); ++i) {
        A[i] = Array[i];
    }
    buildMaxHeap();
}

template <typename T>
void heap<T>::buildMaxHeap() {
    for (int i = A.size()/2; i >= 1; --i) {
        maxHeapify(i - 1);
    }
}

template <typename T>
void heap<T>::maxHeapify(int i) {
    int l = left(i);
    int r = right(i);
    int largest = -1;
    if (l < A.size() && A[l] > A[i])
        largest = l;
    else
        largest = i;
    if (r < A.size() && A[r] > A[largest])
        largest = r;

    if (largest != i) {
        exchange(i, largest);
        maxHeapify(largest);
    }
}

template <typename T>
void heap<T>::exchange(int i, int j) {
    T tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

template <typename T>
int heap<T>::parent(int i) {
    return i/2;
}

template <typename T>
int heap<T>::left(int i) {
    return 2 * i;
}

template <typename T>
int heap<T>::right(int i) {
    return 2 * i + 1;
}

template <typename T>
T heap<T>::getItem(int n) {
    return A[n];
}

template <typename T>
vector<T> heap<T>::heapsort() {
    buildMaxHeap();

    vector<T> ret;
    ret.resize(A.size());

    for (int i = A.size(); i >= 2; --i) {
        ret[i - 1] = A[0];
        exchange(0, i - 1);
        A.resize(A.size() - 1);
        maxHeapify(0);
    }
    ret[0] = A[0];

    return ret;
}