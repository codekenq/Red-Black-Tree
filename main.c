#include <stdio.h>
#include "RB_BST.h"

int main()
{
	BSTtree tree = PNIL;
	int i;
	link p;

	for(i = 10; i > 0; i--)		//向红黑树插入元素
		insert(&tree, i);

	traversal(tree);			//中序遍历红黑树
	printf("\n");
	
	p = max(tree);				//查找树中的最大元素
	if(p)
		printf("max is %d\n", p->data);
	p = min(tree);				//查找树中的最小元素
	if(p)
		printf("min is %d\n", p->data);
	
	p = search(tree, 10);		//在树中寻找元素
	if(p)
	{
		printf("search 10 success\n");
		delete(&tree,p);		//从树中删除元素
	}

	traversal(tree);
	printf("\n");	
	
	p = max(tree);
	if(p)
		printf("max is %d\n", p->data);
	p = min(tree);
	if(p)
		printf("min is %d\n", p->data);

	p = search(tree, 5);
	if(p)
	{
		printf("search 5 success\n");
		delete(&tree,p);
	}

	traversal(tree);
	printf("\n");
	
	p = max(tree);
	if(p)
		printf("max is %d\n", p->data);
	p = min(tree);
	if(p)
		printf("min is %d\n", p->data);
}
