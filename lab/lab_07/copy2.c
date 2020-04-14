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


void fPrintTree(TreeNode* root)
{
	if (root == NULL) return;

	fPrintTree(root->left);
	printf("%d ", root->val);
	fPrintTree(root->right);
}


void fAlocTreeNode(TreeNode** adrTreeNode)
{
	*adrTreeNode = malloc(sizeof(TreeNode));
	(*adrTreeNode)->left = NULL;
	(*adrTreeNode)->right = NULL;
}

void fInsert(int val, TreeNode** adrTreeNode)
{
	TreeNode* treeNode = *adrTreeNode;

	if (treeNode == NULL)
	{
		fAlocTreeNode(&treeNode);
		treeNode->val = val;
		*adrTreeNode = treeNode;
		return;
	}

	if (val > treeNode->val)
	{
		fInsert(val, &treeNode->right);
	}
	else
	{
		fInsert(val, &treeNode->left);
	}
	
}

void fFindSucc(int key, TreeNode* crtNode,int * adrSucc)
{
	if (crtNode == NULL)
	{
		return;
	}
	if (crtNode->val <= key)
	{
		fFindSucc(key, crtNode->right, adrSucc);
		return;
	}
	else
	{
		int succ = *adrSucc;
		if (crtNode->val < succ)
		{
			succ = crtNode->val;
			*adrSucc = succ;
			fFindSucc(key, crtNode->left, adrSucc);
			return;
		}
	}
}

void fFindPred(int key, TreeNode* crtNode,int * adrPred)
{
	if (crtNode == NULL)
	{
		return;
	}
	if (crtNode->val >= key)
	{
		fFindPred(key, crtNode->left, adrPred);
		return;
	}
	else
	{
		int pred = *adrPred;
		if (crtNode->val > pred)
		{
			pred = crtNode->val;
			*adrPred = pred;
			fFindPred(key, crtNode->right, adrPred);
			return;
		}
	}
}

void fFind(int key, TreeNode* root, int* adrExists, TreeNode** adrKeyNode)
{
	if (root == NULL)
	{
		*adrExists = 0;
		return;
	}
	if (key == root->val)
	{
		*adrExists = 1;
		*adrKeyNode = root;
		return;
	}

	if (root->val < key)
	{
		fFind(key, root->right, adrExists, adrKeyNode);
		return;
	}

	if (root->val > key)
	{
		fFind(key, root->left, adrExists, adrKeyNode);
	}
	
}

void fSuccFunctions(int key,TreeNode* keyNode, TreeNode* root)
{
	TreeNode* crtNode = keyNode;
	if (crtNode->right == NULL)
	{
		crtNode = root;
	}
	int succ = INT_MAX;
	fFindSucc(key, crtNode, &succ);

	if (succ == INT_MAX)
	{
		printf("\nnodul cu cheia %d are deja cheia cea mai mare, deci nu are succesor",key);
	}
	else
	{
		printf("\nnodul cu cheia %d are succesorul %d", key, succ);
	}
}

void fPredFunctions(int key,TreeNode* keyNode, TreeNode* root)
{
	TreeNode* crtNode = keyNode;
	if (crtNode->left == NULL)
	{
		crtNode = root;
	}
	int pred = INT_MIN;
	fFindPred(key, crtNode, &pred);

	if (pred == INT_MIN)
	{
		printf("\nnodul cu cheia %d are deja cheia cea mai mica, deci nu are predecesor",key);
	}
	else
	{
		printf("\nnodul cu cheia %d are predecesorul %d", key, pred);
	}
}


void fKeyOperations(TreeNode* root,int key)
{
	int exists;
	TreeNode* keyNode = NULL;
	fFind(key, root, &exists, &keyNode);
	if (!exists)
	{
		printf("\nnodul cu acea cheie nu exista in arbore!");
		return;
	}

	int succ,pred;
	fSuccFunctions(key,keyNode,root);
	fPredFunctions(key, keyNode, root);

	
}

int main()
{
	
	int n;

	printf("nr de elemente:"); scanf("%d", &n);


	TreeNode* root = NULL;
	int val;
	for (int i = 0; i < n; ++i)
	{
		printf("val="); scanf("%d", &val);
		fInsert(val, &root);
	}

	printf("\narborele are valorile: ");
	fPrintTree(root);

	int key;  
	printf("\nkey="); scanf("%d", &key);
	fKeyOperations(root,key);


	return 0;
}