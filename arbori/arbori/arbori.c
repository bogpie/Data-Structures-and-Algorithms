#include <stdio.h>
#include <stdlib.h>

int nrApeluri = 0;

typedef struct TreeNode TreeNode;
struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
};

typedef struct Tree Tree; 
struct Tree
{
	TreeNode* root;
};

int height(TreeNode* root) 
{
	int hs, hd;
	if (root == NULL) return 0;
	hs = height(root->left);
	hd = height(root->right);
	return 1 + ((hs > hd) ? hs : hd);
}


void inOrder(TreeNode* root)
{
	++nrApeluri;
	if (root == NULL)
	{
		return;
	}
	inOrder(root->left);
	printf("%d ", root->val);

	inOrder(root->right);

}

void fInitTree(Tree* tree)
{
	tree->root = malloc(sizeof(TreeNode));
	tree->root->left = NULL;
	tree->root->right = NULL;
}

void fCreateNode(TreeNode** adrTreeNode,int val)
{
	*adrTreeNode = malloc(sizeof(TreeNode));
	(*adrTreeNode)->val = val;
	(*adrTreeNode)->left = NULL;
	(*adrTreeNode)->right = NULL;
}

int main()
{
	Tree* tree = malloc(sizeof(Tree));
	fInitTree(tree);

	TreeNode* treeNode = malloc(sizeof(TreeNode));
	
	fCreateNode(&tree->root,1);
	fCreateNode(&tree->root->left,2);
	fCreateNode(&tree->root->right,3);
	fCreateNode(&tree->root->left->left,4);
	fCreateNode(&tree->root->left->left->right,17);

	inOrder(tree->root);

	printf("\n%d apeluri", nrApeluri);	
	
	printf("\ninaltimea %d", height(tree->root));
}