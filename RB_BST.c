#include <stdlib.h>
#include <stdio.h>
#include "RB_BST.h"

static void lRotate(link *tree, link x)
{
	link y = x->right;
	if(y == PNIL)
		return;

	link ylson = y->left;
	link xparent = x->parent;

	y->parent = xparent;
	if(xparent == PNIL)
		*tree = y;
	else
	{
		if(x == xparent->left)
			xparent->left = y;
		else
			xparent->right = y;
	}

	x->parent = y;
	y->left = x;

	x->right = ylson;
	if(ylson != PNIL)
		ylson->parent = x;
}

static void rRotate(link *tree, link x)
{
	link y = x->left;
	if(y == PNIL)
		return ;
	link xparent = x->parent;
	link yrson = y->right;

	y->parent = xparent;
	if(xparent == PNIL)
		*tree = y;
	else
	{
		if(x == xparent->left)
			xparent->left = y;
		else
			xparent->right = y;
	}
	
	x->parent = y;
	y->right = x;
	
	x->left = yrson;
	if(yrson != PNIL)
		yrson->parent = x;
}

static void insertFix(link *tree, link z)
{
	while(z->parent->color == RED)
	{
		if(z->parent == z->parent->parent->left)
		{
			if(z->parent->parent->right != PNIL && z->parent->parent->right->color == RED)
			{
				z->parent->color = BLACK;
				z->parent->parent->right->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else //have no uncle, or uncle is black
			{	
				if(z == z->parent->right)
				{
					z = z->parent;
					lRotate(tree, z);
				}
			
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				rRotate(tree, z->parent->parent);
			}
		}
		else 
		{
			if(z->parent->parent->left != PNIL && z->parent->parent->left->color == RED)
			{
				z->parent->color = BLACK;
				z->parent->parent->left->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else // have no uncle, or the uncle is black
			{
				if(z == z->parent->left)
				{
					z = z->parent;
					rRotate(tree, z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				lRotate(tree, z->parent->parent);
			}
		}
	}
	(*tree)->color = BLACK;
}

static void deleteFix(link *tree, link x)
{
	link w;
	while(x != *tree && x->color == BLACK)
	{
		if(x == x->parent->left)
		{
			w = x->parent->right;
			if(w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;
				lRotate(tree, x->parent);
				w = x->parent->right;
			}
			if(w->left->color == BLACK && w->right->color == BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else 
			{
				if(w->right->color == BLACK)
				{
					w->left->color = BLACK;
					w->color = RED;
					rRotate(tree, w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->parent->color = BLACK;
				w->right->color = BLACK;
				lRotate(tree, x->parent);
				x = *tree;
			}
		}
		else
		{
			w = x->parent->left;
			
			if(w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;
				rRotate(tree, x->parent);
				w = x->parent->left;
			}
			if(w->left->color == BLACK && w->right->color == BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else 
			{
				if(w->left->color == BLACK)
				{
					w->right->color = BLACK;
					w->color = RED;
					lRotate(tree, w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->parent->color = BLACK;
				w->left->color = BLACK;
				rRotate(tree, x->parent);
				x = *tree;
			}
		}
	}
	(*tree)->color = BLACK;
}

/*
 * 虽然目前这个程序在数据合理的操作下，不会出现什么问题，但是用户是调皮的，他们可不会按照规矩来
 * 所以说，这个程序还是缺少一定的鲁棒性，要是想投入到实用的地步，还得在外部加一些封装
 * */

static void swap(link lhs, link rhs)
{
	Item temp;
	temp = lhs->data;
	lhs->data = rhs->data;
	rhs->data = temp;
}

static link NEW(Item key, Colour color, link parent, link left, link right)
{
	link p = malloc(sizeof *p);
	p->data = key;
	p->color = color;
	p->parent = parent;
	p->left = left;
	p->right = right;
}

void traversal(link tree)
{
	if(tree == PNIL)
		return ;
	traversal(tree->left);
	printf("%d ", tree->data);
	traversal(tree->right);
}

/*当合法操作的时候，这个是正确的*/

link search(link tree, Item key)
{
	if(tree == PNIL)
		return PNIL;
	if(tree->data == key)
		return tree;
	else if(key > tree->data)
		return search(tree->right, key);
	else if(key < tree->data)
		return search(tree->left, key);
}

/* 
 * 当tree只有一个节点的时候，直接返回tree。
 * 当有很多个节点的时候，那么也是正确的
 * */

link min(link tree)
{
	if(tree==PNIL)
		return PNIL;
	if(tree->left == PNIL)
		return tree;
	return min(tree->left);
}

/* 
 * 当tree只有一个节点的时候，直接返回tree。
 * 当有很多个节点的时候，那么也是正确的
 * */

link max(link tree)
{
	if(tree == PNIL)
		return PNIL;
	if(tree->right == PNIL)
		return tree;
	return max(tree->right);
}

/* 
 * 当tree为空时，即没有一个节点，然后查找node，node就是一个假地址，这个肯定会出错的
 * 在这里我们只讨论正确的查找
 * 当tree只有一个节点，然后查找的就是这个节点，则返回为空，说明没有这个节点的前驱
 * */

link predecessor(link tree, link node)
{
	if(node->left != PNIL)
		return max(node->left);
	link x;
	x = node->parent;
	while(x != PNIL && node == x->left)
	{
		node = x;
		x = node->parent;
	}
	return x;
}

/* 
 * 当tree为空时，即没有一个节点，然后查找node，node就是一个假地址，这个肯定会出错的
 * 在这里我们只讨论正确的查找
 * 当tree只有一个节点，然后查找的就是这个节点，则返回为空，说明没有这个节点的前驱
 * */

link successor(link tree, link node)
{
	if(node->right != PNIL)
		return min(node->right);
	link x;
	x = node->parent;
	while( x != PNIL && node == x->right)
	{
		node = x;
		x = node->parent;
	}
	return x;
}

/* 
 * insert在树为空时，和在树有节点的时候，都能正常的工作
 * */

void insert(link *tree, Item key)
{
	link node = NEW(key, RED, PNIL, PNIL, PNIL);

/*	if( *tree == PNIL)
	{	
		*tree = node;
		return ;
	}
*/

	link x = *tree;
	link p = PNIL;
	while(x != PNIL)
	{
		if(key == x->data)
		{
			printf("The key was inserted\n");
			return ;
		}
		if(key > x->data)
		{
			p = x;
			x = x->right;
		}
		if(key < x->data)
		{
			p = x;
			x = x->left;
		}
	}
	node->parent = p;
	if(p == PNIL)
	{
		*tree = node;
	}
	else if(key > p->data)
		p->right = node;
	else
		p->left = node;
	insertFix(tree, node);
}

void delete(link *tree, link z)
{
	link x, y;	
	if(z->left == PNIL || z->right == PNIL)
		y = z;
	else 
		y = successor(*tree, z);
	if(y->left != PNIL)
		x = y->left;
	else
		x = y->right;
	
	x->parent = y->parent;
	if(y->parent == PNIL)
		*tree = x;
	else if(y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;
	if(y != z)
		swap(y, z);
	if(y->color == BLACK)
		deleteFix(tree, x);
	free(y);
}
