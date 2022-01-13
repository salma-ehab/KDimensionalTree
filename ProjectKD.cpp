

#include <iostream>
#include "KDTree.h"
using namespace std;

int main()
{  
	KDTree<int> k;
	k.setDimension(2);
	//insert
	int points[][2] = { {10,5},{3,7},{4,9},{11,6},{17,8},{2,13},{12,6},{4,21},{15,25}};
	for (int i = 0; i < 9; i++)
	{
		k.insertTree(points[i]);
	}
	cout << "Initial tree after insertion" << endl;
	cout<<k;
	cout << "------------------------------------------------------------------------------";
	cout << endl;


	//nearest neighbor
	int point12[] = { 8,10 };
	cout << "The nearest neighbor of {8,10} is" << " ";
	k.neighbor(point12);
	cout << endl;
	cout << "------------------------------------------------------------------------------";
	cout<<endl;

	//delete
	int point1[] = { 4,9 };
	k.delete_point(point1);
	cout << "Tree after deletion" << endl;
	cout << k;
	cout << "------------------------------------------------------------------------------";
	cout << endl;

	//balance
	k.balance();
	cout << "Tree after balancing" << endl;
	cout << k;
	cout << "------------------------------------------------------------------------------";
	cout << endl;

	//copy constructor
	KDTree<int> t(k);
	cout << "Tree after copying by copy constructor" << endl;
	cout << t;
	cout << "------------------------------------------------------------------------------";
	cout << endl;

	//minimum
	int min1 = t.find_min(0);
	cout << "The minimum in x dimension is "<<min1 << endl;
	int min2 = t.find_min(1);
	cout << "The minimum in y dimension is " << min2 << endl;
	cout << "------------------------------------------------------------------------------";
	cout << endl;

	//maximum
	int max1 = t.find_max(0);
	cout << "The maximum in x dimension is " << max1 << endl;
	int max2 = t.find_max(1);
	cout << "The maximum in y dimension is " << max2 << endl;
	cout << "------------------------------------------------------------------------------";
	cout << endl;

	//range
	int maxArray[] = { 10,20 };
	int minArray[] = { 1,1 };
	int size;
    int* range = t.ranges(maxArray, minArray, size);
	cout << "The nodes between {1,1} and {10,20} are" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "x: " << range[i * 2 + 0] <<"  "<<"y: " << range[i * 2 + 1] << endl;
	}
	cout << "------------------------------------------------------------------------------";
	cout << endl;

	//deconstruct
	t.~KDTree();
	cout << t;
	cout << "deconstructing" << endl;
	if (t.isEmpty())
		cout << "The tree is empty" << endl;
	cout << "------------------------------------------------------------------------------";
	cout << endl;



	
	KDTree<float> l;
	l.setDimension(3);
	//insert
	float pointsl[][3] = { {10.5,7.1,5.2},{3.3,4.8,6.7},{4.1,1.5,9},{11.8,8.6,6.4},{17,9.3,8.2},{20.1,18.5,9.6}};
	for (int i = 0; i < 6; i++)
	{
		l.insertTree(pointsl[i]);
	}
	cout << "Initial tree after insertion" << endl;
	cout << l;
	cout << "------------------------------------------------------------------------------";
	cout << endl;


	//nearest neighbor
	float pointl[] = {10,10,10 };
	cout << "The nearest neighbor of {10,10,10} is" << " ";
	l.neighbor(pointl);
	cout << endl;
	cout << "------------------------------------------------------------------------------";
	cout << endl;

	//delete
	float point2l[] = {3.3,4.8,6.7};
	l.delete_point(point2l);
	cout << "Tree after deletion" << endl;
	cout << l;
	cout << "------------------------------------------------------------------------------";
	cout << endl;

	//balance
	l.balance();
	cout << "Tree after balancing" << endl;
	cout << l;
	cout << "------------------------------------------------------------------------------";
	cout << endl;

	//copy constructor
	KDTree<float> m(l);
	cout << "Tree after copying by copy constructor" << endl;
	cout << m;
	cout << "------------------------------------------------------------------------------";
	cout << endl;

	//minimum
	float min1f = m.find_min(0);
	cout << "The minimum in x dimension is " << min1f << endl;
	float min2f = m.find_min(1);
	cout << "The minimum in y dimension is " << min2f << endl;
	float min3f = m.find_min(2);
	cout << "The minimum in z dimension is " << min3f << endl;
	cout << "------------------------------------------------------------------------------";
	cout << endl;

	//maximum
	float max1f = m.find_max(0);
	cout << "The maximum in x dimension is " << max1f << endl;
	float max2f = m.find_max(1);
	cout << "The maximum in y dimension is " << max2f<< endl;
	float max3f = m.find_max(2);
	cout << "The maximum in z dimension is " << max3f << endl;
	cout << "------------------------------------------------------------------------------";
	cout << endl;

	//range
	float maxArrayf[] = { 10,20,30};
	float minArrayf[] = { 1,1,1 };
	int size2;
	float* range2 = m.ranges(maxArrayf, minArrayf, size2);
	cout << "The nodes between {1,1,1} and {10,20,30} are" << endl;
	for (int i = 0; i < size2; i++)
	{
		cout << "x: " << range2[i * 2 + 0] << "  " << "y: " << range2[i * 2 + 1] <<"  "<< "z:  " << range2[i * 2 + 2] << "\n"<<endl;
	}
	cout << "------------------------------------------------------------------------------";
	cout << endl;

	//deconstruct
	m.~KDTree();
	cout << m;
	cout << "deconstructing" << endl;
	if (m.isEmpty())
		cout << "The tree is empty" << endl;
	cout << "------------------------------------------------------------------------------";
	cout << endl;

	
	
	
    KDTree<char> n;
	n.setDimension(4);
	//insert
	char pointsn[][4] = { {'a','m','b','r'},{'n','g','h','y'},{'b','d','z','f'},{'t','s','o','p'},{'w','q','m','x'},{'z','k','u','j'} };
	for (int i = 0; i < 6; i++)
	{
		n.insertTree(pointsn[i]);
	}
	cout << "Initial tree after insertion" << endl;
	cout << n;
	cout << "------------------------------------------------------------------------------";
	cout << endl;


	//nearest neighbor
	char pointnn[] = { 'r','y','l','m' };
	cout << "The nearest neighbor of {'r','y','l','m'} is" << " ";
	n.neighbor(pointnn);
	cout << endl;
	cout << "------------------------------------------------------------------------------";
	cout << endl;

	//delete
	char pointc[] = { 'n','g','h','y' };
	n.delete_point(pointc);
	cout << "Tree after deletion" << endl;
	cout << n;
	cout << "------------------------------------------------------------------------------";
	cout << endl;

	//balance
	n.balance();
	cout << "Tree after balancing" << endl;
	cout << n;
	cout << "------------------------------------------------------------------------------";
	cout << endl;

	//copy constructor
	KDTree<char> r(n);
	cout << "Tree after copying by copy constructor" << endl;
	cout << r;
	cout << "------------------------------------------------------------------------------";
	cout << endl;

	//minimum
	char min1c = r.find_min(0);
	cout << "The minimum in x dimension is " << min1c << endl;
	char min2c = r.find_min(1);
	cout << "The minimum in y dimension is " << min2c << endl;
	char min3c = r.find_min(2);
	cout << "The minimum in z dimension is " << min3c << endl;
	char min4c = r.find_min(3);
	cout << "The minimum in w dimension is " << min4c << endl;
	cout << "------------------------------------------------------------------------------";
	cout << endl;

	//maximum
	char max1c = r.find_max(0);
	cout << "The maximum in x dimension is " << max1c << endl;
	char max2c = r.find_max(1);
	cout << "The maximum in y dimension is " << max2c<< endl;
	char max3c = r.find_max(2);
	cout << "The maximum in z dimension is " << max3c << endl;
	char max4c = r.find_max(3);
	cout << "The maximum in w dimension is " << max4c << endl;
	cout << "------------------------------------------------------------------------------";
	cout << endl;

	//range
	char maxArrayc[] = { 'z','x','y','z'};
	char minArrayc[] = {'a','l','m','n'};
	int size3;
	char* range3 = r.ranges(maxArrayc, minArrayc, size3);
	cout << "The nodes between {'z','x','y','z'} and {'a','l','m','n'} are" << endl;
	for (int i = 0; i < size3; i++)
	{
		cout << "x: " << range3[i * 2 + 0] << "  " << "y: " << range3[i * 2 + 1] <<"  "<< "z:  " << range3[i * 2 + 2] << "  " << "w:  " << range3[i * 2 + 3]<<"\n"<<endl;
	}
	cout << "------------------------------------------------------------------------------";
	cout << endl;

	//deconstruct
	r.~KDTree();
	cout << r;
	cout << "deconstructing" << endl;
	if (r.isEmpty())
		cout << "The tree is empty" << endl;
	cout << "------------------------------------------------------------------------------";
	cout << endl;

	return 0;
}

