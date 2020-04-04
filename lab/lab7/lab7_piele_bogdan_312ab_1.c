#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>


typedef struct TreeNode TreeNode;
struct TreeNode // nodul de arbore
{
	int val;
	TreeNode* left;
	TreeNode* right;
};

int fRecursiveCheck(TreeNode* root, int* adrPrev) 
// iteram recursiv arborele pt a vedea daca este bst
// transmitem radacina arborelui prin valoare si numarul anterior parcurs prin referinta
{
	if (root != NULL)
	{
		// parcurgerea este analoaga metodei "inorder"
		// un bst afisat inorder este crescator

		if (!fRecursiveCheck(root->left, adrPrev))
		{
			return 0; // returnam 0 daca nu este bst
		}

		// acum subarborele stang respecta proprietatea bst
		// cautam si daca radacina curenta o respecta (are valoarea mai mare decat cea a nodului anterior parcurs)

		if (root->val <= *adrPrev)
		{
			return 0;
		}


		*adrPrev = root->val;

		// subarborele drept

		return fRecursiveCheck(root->right, adrPrev);
	}
	return 1;
}

int fCheckBst(TreeNode* root) 
{
	int prev = INT_MIN;
	// initializam valoarea nodului parcurs anterior cu o valoare foarte mica
	// astfel valoarea urmatoare va fi clar mai mare, un eventual bst va avea toate numerele inserate mai mari decat INT_MIN

	return (fRecursiveCheck(root, &prev)); // e nevoie de o parcurgere recursiva inorder
}

void CreateTreeNode(TreeNode** adrRoot) // creem un nod (tranmis prin referinta)
{
	int val;
	char boolean; // d pentru da , n sau alt caracter pentru nu

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

	*adrRoot = root; // deoarece radacina e tranmisa prin referinta
}

void PrintTree(TreeNode* root) // afisarea elementelor arborelui prin metoda inorder
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