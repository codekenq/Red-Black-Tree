#ifndef _BST_H_
#define _BST_H_

typedef int Item;
typedef char Colour;

#define	BLACK	0
#define RED		1

typedef struct node
{
	Item data;
	Colour color;
	struct node *left;
	struct node *right;
	struct node *parent;
}Node;

typedef Node *link;
typedef Node *BSTtree;

extern Node NIL;
#define PNIL &NIL

void traversal(link);
link search(link, Item);
link max(link);
link min(link);
link predecessor(link, link);
link successor(link, link);
void insert(link *, Item);
void delete(link *, link);

#endif /*_BST_H_*/
