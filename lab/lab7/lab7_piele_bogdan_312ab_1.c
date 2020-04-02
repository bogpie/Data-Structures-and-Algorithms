#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>


typedef struct TreeNode TreeNode;
struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
};

int fRecursiveCheck(TreeNode* root, int* adrPrev)
{
	if (root != NULL)
	{
		if (!fRecursiveCheck(root->left, adrPrev))
		{
			return 0;
		}

		if (root->val <= *adrPrev)
		{
			return 0;
		}

		*adrPrev = root->val;

		return fRecursiveCheck(root->right, adrPrev);
	}
	return 1;
}

int fCheckBst(TreeNode* root)
{
	int prev = INT_MIN;
	return (fRecursiveCheck(root, &prev));
}

void CreateTreeNode(TreeNode** adrRoot)
{
	int val;
	char boolean;

	TreeNode* root = malloc(sizeof(TreeNode));

	root->left = NULL;
	root->right = NULL;

	printf("val="); scanf("%d", &val);
	root->val = val;


	printf("nodul cu val %d are subarb stang ?", val);
	getchar();
	scanf("%c", &boolean);
	if (boolean == 'd')
	{
		CreateTreeNode(&root->left);
	}

	printf("nodul cu val %d are subarb drept?", val);
	getchar();
	scanf("%c", &boolean);
	if (boolean == 'd')
	{
		CreateTreeNode(&root->right);
	}


	*adrRoot = root;
}

void PrintTree(TreeNode* root)
{
	if (root == NULL) return;

	PrintTree(root->left);
	printf("%d ", root->val);
	PrintTree(root->right);
}


int main()
{
	TreeNode* root;
	CreateTreeNode(&root);

	printf("\n");
	PrintTree(root);

	int minimCrt = INT_MAX;

	int isBst = fCheckBst(root); 

	if (isBst == 1)
	{
		printf("\neste BST");
	}
	else if (isBst == 0)
	{
		printf("\nnu este BST");
	}
	else exit(1);

	return 0;
}