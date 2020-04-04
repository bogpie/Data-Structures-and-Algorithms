#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef struct TreeNode TreeNode;
struct TreeNode // nod de arbore
{
	int val;
	TreeNode* left;
	TreeNode* right;
};

typedef struct StackNode StackNode; // nod de stiva
struct StackNode
{
	int val;
	StackNode* next;
};

void fPrintTree(TreeNode* root) // afisarea arborelui, parametru : radacina lui
{
	if (root == NULL) return;

	// se afiseaza parcurgandu-se inorder arborele

	fPrintTree(root->left);
	printf("%d ", root->val);
	fPrintTree(root->right);
}

void fAlocTreeNode(TreeNode** adrTreeNode) // alocarea nodului de arbore transmis prin referinta
{
	*adrTreeNode = malloc(sizeof(TreeNode));
	(*adrTreeNode)->left = NULL;
	(*adrTreeNode)->right = NULL;
}

void fInsert(int val, TreeNode** adrTreeNode) // inserarea unei valori in BST
{
	TreeNode* treeNode = *adrTreeNode;

	if (treeNode == NULL) 
	{
		
		fAlocTreeNode(&treeNode);
		//primul apel va fi chiar pentru alocarea radacinei
		//restul sunt apeluri recursive pentru alocarea celorlalte noduri

		treeNode->val = val;
		*adrTreeNode = treeNode;
		return;
	}

	if (val > treeNode->val)
	{
		fInsert(val, &treeNode->right); 
		// apelare recursiva, noua radacina este nodul din dreapta pentru ca valoarea de inserat este mai mare decat nodul curent (radacina curenta)
	}
	else
	{
		fInsert(val, &treeNode->left);
		// stanga (valoare mai mica)
	}
	
}

// gasirea succesorului; parametrii : cheia nodului caruia ii vom gasi succesorul, nodul curent din parcurgere, valoarea succesorului transmisa prin refeinta
void fFindSucc(int key, TreeNode* crtNode,int * adrSucc) 
{
	if (crtNode == NULL) // nu mai putem parcurge pe aceasta ramura
	{
		return;
	}
	if (crtNode->val <= key) 
	{
		fFindSucc(key, crtNode->right, adrSucc); // cautam in dreapta succesorul; succesorul ar trebui sa fie o valoare mai mare 
		return;
	}
	else
	{
		int succ = *adrSucc;
		if (crtNode->val < succ)
		// succesorul unui nod are CEA MAI MICA valoare MAI MARE decat cheia lui
		// asadar cautam daca putem actualiza valoarea gasita pentru succesor
		{
			succ = crtNode->val;
			*adrSucc = succ;
			fFindSucc(key, crtNode->left, adrSucc); // cautam in stanga succesorul
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
		// predecesorul ar trebui sa fie o valoare mai mica 
		fFindPred(key, crtNode->left, adrPred);
		return;
	}
	else
	{
		int pred = *adrPred;
		
		//daca putem actualiza predecesorul
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
// gasirea unei valori in BST
// parametrii: cheie,radacina, valoare "boolean" corespunzatoare existentei cheii (referinta), adresa nodului cu cheie (nodul prin referinta)
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


void fKeyFunctions(TreeNode* root, int key)
// efectuarea cerintelor referitoare la cheie
// adica gasirea succesorului si predecesorului
// functia include si afisarile acestora, daca exista, sau afisarea unor mesaje, altfel
{
	int exists;
	TreeNode* keyNode = NULL;
	fFind(key, root, &exists, &keyNode);
	if (!exists)
	{
		printf("\nnodul cu acea cheie nu exista in arbore!");
		return;
	}
	fSuccFunctions(key,keyNode,root);
	fPredFunctions(key, keyNode, root);
}

void fSwap(int * adr_x,int * adr_y)
{
	int aux = *adr_y;
	*adr_y = *adr_x;
	*adr_x = aux;
}

//se afiseaza elementele intre x si y, inclusiv x si y
//pentru a nu include x si y, se modifica "<=", respectiv ">=" cu "<", respectiv ":>"
void fPrintBetween(TreeNode* root, int x, int y)  
{
	if (root == NULL) return;

	if (root->val >= x)
	{
		fPrintBetween(root->left, x, y);
	}

	if (root->val >= x && root->val <= y)
	{
		printf("%d ", root->val);

	}
	
	if (root->val <= y)
	{
		fPrintBetween(root->right, x, y);
	}

}

void fReadTree(int * adr_n, TreeNode** adrRoot)
{
	int n;
	TreeNode* root = NULL; 
	//momentan nu avem o radacina, va fi alocata cand vom citi primul element

	printf("nr de elemente:"); scanf("%d", &n);
	int val;
	for (int i = 0; i < n; ++i)
	{
		printf("val="); scanf("%d", &val);
		fInsert(val, &root);
	}

	*adrRoot = root;
	*adr_n = n;
}

void fAlocStackNode(StackNode** adrStackNode)
{
	(*adrStackNode) = malloc(sizeof(StackNode));
	(*adrStackNode)->next = NULL;
}

void fCompareStacks(StackNode* top, StackNode* top2, short* adrEquals)
{
	while (top != NULL)
	{
		if (top->val != top2->val)
		{
			*adrEquals = 0;
			return;
		}
		top = top->next;
		top2 = top2->next;
	}
	*adrEquals = 1;
	return;
}

void fPush(StackNode** adrTop, int val)
{
	StackNode* newTop = NULL; 
	// top-ul stivei va fi alocat de fapt in functia de mai jos
	fAlocStackNode(&newTop);
	newTop->next = (*adrTop);
	newTop->val = val;
	*adrTop = newTop;
}

void fGenerateStack(TreeNode* root,StackNode** adrTop) 
// generarea unei stive cu valorile BST (stiva va avea valorile sortate descrescator; parametrii: radacina arborelui, stiva (top-ul ei - prin referinta)
{
	if (root == NULL) return;
	fGenerateStack(root->left,adrTop);
	fPush(adrTop, root->val);
	fGenerateStack(root->right, adrTop);
}

void fCompareTrees(int n,TreeNode* root,int n2,TreeNode* root2,short* adrEquals)
{
	// doi BST se compara prin compararea celor 2 stive generate dupa acestia
	// parametrii - numerele de noduri si radacinile arborilor; variabila "boolean" - au sau nu aceleasi valori
	if (n != n2)
	{
		printf("\narborii nu au acelasi nr de elemente deci");
		*adrEquals = 0;
		return ;
	}
	StackNode* top, *top2;
	fAlocStackNode(&top);
	fAlocStackNode(&top2);
	fGenerateStack(root,&top);
	fGenerateStack(root2,&top2);
	fCompareStacks(top,top2,adrEquals);
}


int main()
{

	int n;
	TreeNode* root;
	printf("-> se citeste primul arbore\n");
	fReadTree(&n,&root);

	printf("\narborele are valorile: ");
	fPrintTree(root);

	int key;  
	printf("\nkey="); scanf("%d", &key);
	fKeyFunctions(root,key);

	int x, y;
	printf("\nse vor afisa elementele intre x si y (inclusiv x si y), unde :");
	printf("\nx="); scanf("%d", &x);
	printf("\ny="); scanf("%d", &y);
	if (y < x)
	{
		fSwap(&x, &y);
	}
	printf("\n");
	fPrintBetween(root,x, y);

	int n2;
	TreeNode* root2 = NULL;
	printf("\n-> se citeste al doilea arbore\n");
	fReadTree(&n2, &root2);

	short equals=0;
	fCompareTrees(n, root, n2, root2,&equals);
	if (equals == 1)
	{
		printf("\narborii au aceleasi valori");
	}
	else
	{
		printf("\narborii nu au aceleasi valori");
	}

	return 0;
}