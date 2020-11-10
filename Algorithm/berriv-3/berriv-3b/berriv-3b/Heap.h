#pragma once
//Juan Pablo bernal & Augusto Rivas 
// Heap class definition 
#include <vector>
#include <iostream>
#include <string>

using namespace std;
//using tamplate for the heap calss 
template <typename T>
class Heap
{
public:
	Heap();
	int parent(int node);// returns parent of a given node
	int left(int node);//returns left child of a given node
	int right(int node);//returns right child of a given node 
	T getItem(int node);//returns the value of a node 
	vector<T> getTree() { return tree; };//returns the heap vector
	void maxHeapify(int node);//makes a node greater thaan all his decendence 
	void buildMaxHeap();//makes the vector a max heap 
	void initializeMaxHeap(vector<T> data);// copies the data of a given vector into the tree vector and then makes it a max heap
	void heapSort();//sort using heapsort 

private:
	vector<T> tree;// vector to store all the nodes of the heap 
	int heapSize;//size of the heap 
};

template <typename T>
Heap<T>::Heap()
{
}

// returns parent of a given node
template<typename T>
int Heap<T>::parent(int node)
{
		return (floor(node / 2));
}

// returns left child of a given node
template<typename T>
int Heap<T>::left(int node)
{
		return (node * 2);
}

// returns right child of a given node
template<typename T>
int Heap<T>::right(int node)
{
		return (node * 2 + 1);
}

//returns the value of a node 
template<typename T>
T Heap<T>::getItem(int node)
{
		return T(tree[node]);
}

//makes a node greater than all his decendence 
template<typename T>
void Heap<T>::maxHeapify(int node)
{
	int l = left(node);
	int r = right(node);
	int largest;
	T temp;//temporal value to saw elements

	//check the parent and 2 childs to see who is the largest 
	if (l <= (heapSize) && tree[l] > tree[node])
		largest = l;
	else
		largest = node;

	if (r <= (heapSize) && tree[r] > tree[largest])
		largest = r;
	//if the largest is not the parent swap parent with largest 
	if (largest != node)
	{
		temp = tree[node];
		tree[node] = tree[largest];
		tree[largest] = temp;
		maxHeapify(largest);//recursively call this function to check all the decendence to find the largest 
	}
}

//makes the vector a max heap 
template<typename T>
void Heap<T>::buildMaxHeap()
{
	for (int i = floor(heapSize / 2); i > 0; i--)// heapifies all the parent nodes 
		maxHeapify(i);
}

// copies the data of a given vector into the tree vector and then makes it a max heap
template<typename T>
void Heap<T>::initializeMaxHeap(vector<T> data)
{
	tree.resize(data.size());
	for (int i = 1; i < data.size(); i++)//copies all the values of the dictionary to the heap skiping the 0 index
		tree[i] = data[i]; 
	buildMaxHeap();//makes the heap a max heap 
	heapSize = tree.size() - 1;//sets up the size of the heap
}

//sort using heapsort 
template<typename T>
void Heap<T>::heapSort()
{
	buildMaxHeap();// makes sure id a max heap before sorting
	T temp = tree[1];//temporal value to saw elements 

	for (int i = heapSize; i > 1; i--)
	{
		// from the last index swaps first and last element 
		temp = tree[i];
		tree[i] = tree[1];
		tree[1] = temp;
		heapSize--;//reduces the size of the heap to ignore the sorted elements 
		maxHeapify(1);//make the first node the maximum again 
	}
}


