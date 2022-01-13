#pragma once
#include <iostream>
#include<iomanip>
#include <ostream>
#include <algorithm>

using namespace std;
int KDIMENSION;

template <class E>
class KDTree
{
private:
	struct compare
	{

		compare(int d) {
			this->d = d;
		}

		bool operator()(E a[], E b[]) {
			return a[d] < b[d];
		}

		int d;
	};


	class Node
	{
	public:
		E* data = new E(KDIMENSION);
		Node* left;
		Node* right;
		int depth;

		KDTree<E>::Node() :left(nullptr), right(nullptr)
		{

		}

		KDTree<E>::Node(E data[], int depth) : left(nullptr), right(nullptr), depth(depth)
		{
			Node* node = new Node;
			for (int i = 0; i < KDIMENSION; i++)
			{
				this->data[i] = data[i];
			}
		}

		KDTree<E>::Node(const KDTree<E>::Node& node) : left(nullptr), right(nullptr) {
			if (&node == nullptr)
				return;
			depth = node.depth;
			for (int i = 0; i < KDIMENSION; i++)
				this->data[i] = node.data[i];
			if (node.left != nullptr) {

				left = new Node(*node.left);
			}
			if (node.right != nullptr) {

				right = new Node(*node.right);
			}
		}

		KDTree<E>::Node(E data, KDTree<E>::Node left, KDTree<E>::Node right, int depth) : data(data), left(left), right(right), depth(depth) {}
		~Node() {
			delete left;
			delete right;
			left = nullptr;
			right = nullptr;
		}

	};
	Node* kdRoot;
	

public:
	KDTree();
	KDTree(const KDTree<E>& original);
	// trial
	KDTree(E data[]);
	~KDTree();
	void insertTree(E point[]);
	void neighbor(E goalPoint[]);
	void delete_point(E point[]);
	E find_min(int d);
	E find_max(int d);
	E* ranges(E max[], E min[], int& size);
	void displayTree(ostream& out);
	void balance();
	void setDimension(int dimension);
	bool isEmpty();
	
private:
	void insert(E point[], Node*& kdRoot, int depth)
	{
		if (kdRoot == nullptr)
		{
			kdRoot = new Node(point, depth);
		}

		else if (point[depth % KDIMENSION] < kdRoot->data[depth % KDIMENSION])
		{
			insert(point, kdRoot->left, depth + 1);
		}
		else
		{
			insert(point, kdRoot->right, depth + 1);
		}
	}

	Node* delete_node_rec(Node*& root, E point[], int d) //passing root by ref we are n3adel feha
	{

		if (root == nullptr)
			return nullptr;


		int cd = d % KDIMENSION;

		if (equal(root->data, root->data + KDIMENSION, point))// compare root->data with the point giving the first and last pointer of the root and pointer to the point comparing by memory 
		{

			if (root->right != nullptr)
			{

				Node* min = find_min_rec(root->right, cd, d + 1);
				copy(min->data, min->data + KDIMENSION, root->data);//copy the min element to this node
				root->right = delete_node_rec(root->right, min->data, d + 1);// delete the min node recursively 
			}
			else if (root->left != nullptr)
			{
				Node* max = find_max_rec(root->left, cd, d + 1);
				copy(max->data, max->data + KDIMENSION, root->data);
				root->left = delete_node_rec(root->left, max->data, d + 1);
			}
			else
			{
				delete root;
				root = nullptr;// point to null Because it is pointing to garbage
				return nullptr;
			}
			return root;// we return root as we are calling it recursively
		}
		if (point[cd] <= root->data[cd])
			root->left = delete_node_rec(root->left, point, d + 1);
		else
			root->right = delete_node_rec(root->right, point, d + 1);
		return root;
	}

	float distanceSquared(E a[], E b[])
	{
		float total = 0;
		for (int i = 0; i < KDIMENSION; i++)
		{
			float pointsDiff = a[i] - b[i];
			total += pow(pointsDiff, 2);
		}
		total = sqrt(total);
		return total;
	}

	KDTree::Node* closestNode(Node* a, Node* b, E targetPoint[])
	{
		if (a == 0)
			return b;
		if (b == 0)
			return a;

		float distance1 = distanceSquared(a->data, targetPoint);
		float distance2 = distanceSquared(b->data, targetPoint);

		if (distance1 < distance2)
			return a;
		else
			return b;
	}

	KDTree::Node* nearestNeighbor(Node*& kdRoot, E targetPoint[], int depth)
	{
		Node* bestBranch;
		Node* worstBranch;

		if (kdRoot == 0)
		{
			return 0;
		}

		if (targetPoint[depth % KDIMENSION] < kdRoot->data[depth % KDIMENSION])
		{
			bestBranch = kdRoot->left;
			worstBranch = kdRoot->right;
		}
		else
		{
			bestBranch = kdRoot->right;
			worstBranch = kdRoot->left;
		}

		Node* tempNode = nearestNeighbor(bestBranch, targetPoint, depth + 1);
		Node* best = closestNode(tempNode, kdRoot, targetPoint);


		double radiusSquared = distanceSquared(targetPoint, best->data);
		if (worstBranch != 0)
		{
			float distance = distanceSquared(targetPoint, worstBranch->data);

			if (radiusSquared > distance)
			{
				tempNode = nearestNeighbor(worstBranch, targetPoint, depth + 1);
				best = closestNode(tempNode, best, targetPoint);
			}
		}
		return best;
	}

	Node* find_min_rec(Node* root, int d, int cd = 0) {// getting the minmum of dimension d , and the current dimension is cd
		if (root == nullptr)
			return nullptr;
		cd = cd % KDIMENSION;
		if (cd == d) {
			if (root->left == nullptr)
				return root;
			Node* left = find_min_rec(root->left, d, cd + 1);
			E data = (left != nullptr) ? left->data[d] : numeric_limits<E>::max();
			return (root->data[d] < data) ? root : left;

		}
		Node* left = find_min_rec(root->left, d, cd + 1);
		E dataleft = (left != nullptr) ? left->data[d] : numeric_limits<E>::max();
		Node* right = find_min_rec(root->right, d, cd + 1);
		E dataright = (right != nullptr) ? right->data[d] : numeric_limits<E>::max();
		return (root->data[d] < dataleft) ? (root->data[d] < dataright) ? root : right : (dataleft < dataright) ? left : right;
	}


	Node* find_max_rec(Node* root, int d, int cd = 0) {
		if (root == nullptr)
			return nullptr;//min size of any data type
		cd = cd % KDIMENSION;
		if (cd == d) {
			if (root->right == nullptr)
				return root;
			Node* right = find_max_rec(root->right, d, cd + 1);
			E data = (right != nullptr) ? right->data[d] : numeric_limits<E>::min();
			return (root->data[d] > data) ? root : right;
		}
		Node* left = find_max_rec(root->left, d, cd + 1);
		E dataleft = (left != nullptr) ? left->data[d] : numeric_limits<E>::min();
		Node* right = find_max_rec(root->right, d, cd + 1);
		E dataright = (right != nullptr) ? right->data[d] : numeric_limits<E>::min();
		return (root->data[d] > dataleft) ? (root->data[d] > dataright) ? root : right : (dataleft > dataright) ? left : right;

	}



	E* search_range_rec(Node* root, const E max[], const E min[], int& size) {

		bool same = true;
		if (root == nullptr) {
			return nullptr;
		}
		int cd = root->depth % KDIMENSION;
		if (root->data[cd] > max[cd]) {
			return search_range_rec(root->left, max, min, size);
		}
		else if (root->data[cd] < min[cd]) {
			return search_range_rec(root->right, max, min, size);
		}
		for (int i = 0; i < KDIMENSION; i++)
		{
			if (root->data[i] < min[i] || root->data[i] > max[i]) {
				same = false;
				break;
			}// cheking if point in range 
		}
		int size1 = 0;
		int size2 = 0;
		E* left = search_range_rec(root->left, max, min, size1);
		E* right = search_range_rec(root->right, max, min, size2);
		if (same)
			size++;
		size += size1 + size2;
		E* data = new E[size * KDIMENSION];
		if (size1 != 0) {
			copy(left, left + size1 * KDIMENSION, data);
		}
		if (size2 != 0) {
			copy(right, right + size2 * KDIMENSION, data + size1 * KDIMENSION);
		}
		if (same)
			copy(root->data, root->data + KDIMENSION, data + size * KDIMENSION - KDIMENSION);

		delete left;//free the memory after copying the data
		delete right;

		return data;

	}

	E* get_data(Node* root, int& size) {
		E* data;
		if (root == nullptr) {
			return nullptr;
		}
		size++;
		int size1 = 0;
		int size2 = 0;
		E* left = get_data(root->left, size1);
		E* right = get_data(root->right, size2);
		size += size1 + size2;
		data = new E[size * KDIMENSION];
		copy(left, left + size1 * KDIMENSION, data);
		copy(right, right + size2 * KDIMENSION, data + size1 * KDIMENSION);
		delete[] left;
		delete[] right;
		copy(root->data, root->data + KDIMENSION, data + size * KDIMENSION - KDIMENSION);
		return data;
	}

	

	void display(ostream& out, Node* node,int space)
	{    
		
		if (node != 0)
		{
			int count = 10;
			space += count;
			display(out, node->right,space);
			out << endl;

			for (int j = count; j < space; j++)
			{
					out << " ";
			}
			for (int i = 0; i < KDIMENSION; i++)
			{
				out << node->data[i];
				if (i < KDIMENSION - 1)
					out << ",";
			}
			out << endl;
			display(out, node->left,space);
		}   
	}
};

template<class E>
KDTree<E>::KDTree()
{
	kdRoot = nullptr;
}

template<class E>
KDTree<E>::KDTree(const KDTree<E>& original)
{
	kdRoot = new Node(*original.kdRoot);
}

//trial
template<class E>
KDTree<E>::KDTree(E data[])
{
	kdRoot = new Node();
	for (int i = 0; i < KDIMENSION; i++)
	{
		kdRoot->data[i] = data[i];
	}
}

template<class E>
KDTree<E>::~KDTree()
{
	// deleting the root calling the Node destructor which delete All the descendants
	delete(kdRoot);
	kdRoot = nullptr;
}

template<class E>
void KDTree<E>::insertTree(E point[])
{

	insert(point, kdRoot, 0);
}

template<class E>
void KDTree<E>::neighbor(E goalPoint[])
{
	Node* point = nearestNeighbor(kdRoot, goalPoint, 0);
	for (int i = 0; i < KDIMENSION; i++)
	{
		cout << point->data[i] << " ";
	}
}

template<class E>
void KDTree<E>::delete_point(E point[])
{
	delete_node_rec(kdRoot, point, 0);
}

template<class E>
E KDTree<E>::find_min(int d) {
	d = d % KDIMENSION;
	return find_min_rec(kdRoot, d, 0)->data[d];
}

template<class E>
E KDTree<E>::find_max(int d) {
	d = d % KDIMENSION;
	return find_max_rec(kdRoot, d, 0)->data[d];
}

template<class E>
E* KDTree<E>::ranges(E max[], E min[], int& size)
{
	size = 0;
	return search_range_rec(kdRoot, max, min, size);
}

template<class E>
void KDTree<E>::displayTree(ostream& out)
{
	display(out,kdRoot,0);
}

template<class E>
void KDTree<E>::balance()
{
	int size = 0;
	E* x = get_data(kdRoot, size);
	E** data = new E * [size];
	for (int i = 0; i < size; i++)
	{
		data[i] = new E[KDIMENSION];
		for (int j = 0; j < KDIMENSION; j++)
		{
			data[i][j] = x[i * KDIMENSION + j];
		}
	}
	delete kdRoot;
	kdRoot = nullptr;
	int d = 0;
	while (size > 0)
	{
		sort(data, data + size, compare(d % KDIMENSION));
		for (int i = 0; i < pow(2, d); i++) {
			int mid = (size) / 2;
			insertTree(data[mid]);
			copy(data + mid + 1, data + size, data + mid);
			size--;
			if (size == 0)
				break;
		}
		d++;
	}
	delete[] x;
}

template<class E>
void KDTree<E>::setDimension(int dimension)
{
	KDIMENSION = dimension;
}

template<class E>
bool KDTree<E>::isEmpty()
{
	return kdRoot == 0;
}

template<class E>
ostream& operator<<(ostream& out, KDTree<E>& tree)
{
	tree.displayTree(out);
	return out;
}


