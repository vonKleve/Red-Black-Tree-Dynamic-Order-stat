#include "RedBlackTreeExtended.h"

RBTreeExt::RBTreeExt()
{
	root = nil;
	nil = new Node(-1, 0, 0, nullptr, nullptr, nullptr);
}

void RBTreeExt::insert(Node *x)
{
	Node *p = nil, *y = root;
	while (y && y != nil)
	{
		p = y;
		p->subTreeSize++;
		if (x->key < y->key) y = y->left;
		else y = y->right;
	}
	x->parent = p;

	if (p == nil) root = x;
	else if (x->key < p->key) p->left = x;
	else p->right = x;

	x->right = x->left = nil;
	RB_insert_fixup(x);
}

void RBTreeExt::RB_insert_fixup(Node *x)
{	
	while (x->parent && x->parent->color)
	{
		if (x->parent == x->parent->parent->left)
		{
			Node *y = x->parent->parent->right;
			if (y->color)
			{
				x->parent->color = y->color = 0;
				x->parent->parent->color = 1;
				x = x->parent->parent;
			}
			else
			{
				if (x == x->parent->right)
				{
					x = x->parent;
					left_rotate(x);
				}
				x->parent->color = 0;
				x->parent->parent->color = 1;
				right_rotate(x->parent->parent);
			}
		}
		else {
			if (x->parent == x->parent->parent->right)
			{
				Node *y = x->parent->parent->left;

				if (y->color)
				{
					x->parent->color = y->color = 0;
					x->parent->parent->color = 1;
					x = x->parent->parent;
				}
				else {
					if (x == x->parent->left)
					{
						x = x->parent;
						right_rotate(x);
					}
					
					x->parent->color = 0;
					x->parent->parent->color = 1;
					left_rotate(x->parent->parent);
				}
			}
		}
	}
	nil->color = 0;
	root->color = 0;
}

void RBTreeExt::left_rotate(Node *x)
{
	Node *y = x->right;
	x->right = y->left;

	if (y->left != nil) y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == nil) root = y;
	else if (x == x->parent->left) x->parent->left = y;
	else x->parent->right = y;

	x->parent = y;
	y->left = x;

	y->subTreeSize = x->subTreeSize;
	int left = 0, right = 0;
	if (x->left) left = x->left->subTreeSize;
	if (x->right) right = x->right->subTreeSize;
	x->subTreeSize = left + right + 1;
}

void RBTreeExt::right_rotate(Node *x)
{
	Node *y = x->left;
	x->left = y->right;

	if (y->right != nil) y->right->parent = x;
	y->parent = x->parent;
	if (x->parent == nil) root = y;
	else if (x == x->parent->left) x->parent->left = y;
	else x->parent->right = y;

	x->parent = y;
	y->right = x;

	y->subTreeSize = x->subTreeSize;
	int left = 0, right = 0;
	if (x->left) left = x->left->subTreeSize;
	if (x->right) right = x->right->subTreeSize;
	x->subTreeSize = left + right + 1;
}

Node * RBTreeExt::get_element(double val)
{
	Node * temp = root;
	while (temp && temp != nil)
	{
		if (temp->key < val) 
			temp = temp->right;
		else if(temp->key > val) 
			temp = temp->left;
		else
			break;
	}
	return temp;
}

Node * RBTreeExt::get_root() const
{
	return root;
}

Node * RBTreeExt::get_nil() const
{
	return nil;
}

Node * RBTreeExt::get_minimum(Node *x)
{
	while (x->left && x->left != nil) x = x->left;
	return x;
}

void RBTreeExt::transplant(Node *x, Node *y)
{
	if (x->parent == nil) root = y;
	else if (x == x->parent->left) x->parent->left = y;
	else x->parent->right = y;
	if(y) y->parent = x->parent;
}

void RBTreeExt::delete_element(Node *x)
{
	Node *y = x;
	Node *z;
	bool yInitColor = y->color;
	if (x->left == nil)
	{
		z = x->right;
		transplant(x, x->right);
	}
	else if (x->right == nil)
	{
		z = x->left;
		transplant(x, x->left);
	}
	else
	{
		y = get_minimum(x->right);
		yInitColor = y->color;
		z = y->right;
		if (y->parent == x)
			z->parent = y;
		else
		{
			transplant(y, y->right);
			y->right = x->right;
			y->right->parent = y;
		}
		transplant(x, y);
		y->left = x->left;
		y->left->parent = y;
		y->color = x->color;
	}
	if (!yInitColor)
		delete_fixup(z);
}

void RBTreeExt::delete_fixup(Node *x)
{
	while (x != root && !x->color)
	{
		if (x == x->parent->left)
		{
			Node *w = x->parent->right;
			if (w->color)
			{
				w->color = 0;
				x->parent->color = 1;
				left_rotate(x->parent);
				w = x->parent->right;
			}
			if (!w->left->color && !w->right->color)
			{
				w->color = 1;
				x = x->parent;
			}
			else 
			{
				if (!w->right->color)
				{
					w->left->color = 0;
					w->color = 1;
					right_rotate(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = 0;
				w->right->color = 0;
				left_rotate(x->parent);
				x = root;
			}
		}
		else
		{
			Node *w = x->parent->left;
			if (w->color)
			{
				w->color = 0;
				x->parent->color = 1;
				right_rotate(x->parent);
				w = x->parent->left;
			}
			if (!w->left->color && !w->right->color)
			{
				w->color = 1;
				x = x->parent;
			}
			else
			{
				if (!w->left->color)
				{
					w->right->color = 0;
					w->color = 1;
					left_rotate(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = 0;
				w->left->color = 0;
				right_rotate(x->parent);
				x = root;
			}
		}
	}
	nil->color = 0;
	x->color = 0;
}

void RBTreeExt::show(Node *temp, int level)
{
	if (temp && temp != nil)
	{
		show(temp->left, level + 1);
		for (int i = 0; i < level; i++)
			std::cout << " ";
		std::cout << temp->key << " rank: " << temp->subTreeSize << " color: " << temp->color << "\n";
		show(temp->right, level + 1);
	}
}