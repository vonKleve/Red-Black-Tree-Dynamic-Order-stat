#pragma once

#include <iostream>

class Node {
public:
	double key;
	// 0 - black 1 - red
	bool color;
	int subTreeSize;
	Node *left, *right, *parent;
	Node(double _k = 0., bool _c = 1, int _sT = 1, Node *_l = nullptr, Node *_r = nullptr, Node *_p = nullptr) :
		key(_k), color(_c), subTreeSize(_sT), left(_l), right(_r), parent(_p) {};
};

class RBTreeExt {
	Node *root;
	Node *nil;
public:
	RBTreeExt();

	void insert(Node *);
	void RB_insert_fixup(Node *);
	void delete_element(Node *);
	void delete_fixup(Node *);

	void left_rotate(Node *);
	void right_rotate(Node *);

	Node *get_element(double);
	Node *get_root()const;
	Node *get_nil()const;
	Node *get_minimum(Node *);

	void transplant(Node *, Node *);

	void show(Node *,int);
};