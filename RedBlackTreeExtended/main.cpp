#include <iostream>
#include "RedBlackTreeExtended.h"

using namespace std;

int main()
{
	RBTreeExt tree;
	int number = 50;
	cout << "exit code: -666\n";
	cout << "Push numbers to the tree.\n";
	cin >> number;
	while (number != -666) 
	{
		Node *temp = new Node(number);
		tree.insert(temp);
		cin >> number;
	}
	tree.show(tree.get_root(), 0);
	cout << "Enter number(s) to delete:\n";
	cin >> number;
	Node *t;
	while (number != -666)
	{
		t = tree.get_element(number);
		if (t != tree.get_nil()) tree.delete_element(t);
		else cout << "No such element!\n";
		tree.show(tree.get_root(), 0);
		cout << "\n";
		cin >> number;
	}
	system("pause");
	return 0;
}