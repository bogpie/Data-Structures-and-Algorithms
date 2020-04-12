#include "Header.h"

void fInitTree(Tree** adrTree)
{
	//initializarea BST-ului
	Tree* tree = *adrTree;
	tree = malloc(sizeof(tree));
	tree->root = NULL;
	*adrTree = tree;
}

void fAlocTreeNode(TreeNode** adrTreeNode)
{
	//alocarea unui nod de BST
	TreeNode* treeNode;
	treeNode = malloc(sizeof(TreeNode));
	treeNode->left = treeNode->right = NULL;
	*adrTreeNode = treeNode;
}


void fInsertInTree(Player player, TreeNode** adrTreeNode)
{
	//inseram in BST un jucator, parcurgerea recursiva se face in functie de scor
	TreeNode* treeNode = *adrTreeNode;

	if (treeNode == NULL)
	{
		//nodul unde trebuie facuta inserarea, il alocam
		fAlocTreeNode(&treeNode);
		treeNode->player = player;
		*adrTreeNode = treeNode;
		return;
	}

	Player nodePlayer = treeNode->player;
	if (player.score > nodePlayer.score)
	{
		fInsertInTree(player, &treeNode->right);
	}
	else if (player.score < nodePlayer.score)
	{
		fInsertInTree(player, &treeNode->left);

	}
	else
	{
		//exista deja un jucator cu acelasi scor
		//efectuam comparatiile de nume si inlocuim, daca e cazul, nodul
		int numeFamilieCmp = strcmp(player.numeFamilie, nodePlayer.numeFamilie);
		if (numeFamilieCmp <= -1)
		{
			treeNode->player = player;
			*adrTreeNode = treeNode;
		}
		else if (numeFamilieCmp == 0)
		{
			if (strcmp(player.prenume, nodePlayer.prenume) <= -1)
			{
				treeNode->player = player;
				*adrTreeNode = treeNode;
			}
		}
	}
	return;

}


void fPrintTree(TreeNode* treeNode, FILE* rezultateOut)
{
	//parcurgere inorder
	if (treeNode == NULL) return;
	fPrintTree(treeNode->right, rezultateOut);
	fprintf(rezultateOut, "%s %s %d\n", treeNode->player.numeFamilie, treeNode->player.prenume, treeNode->player.score);
	fPrintTree(treeNode->left, rezultateOut);
}

void fSearchInTree(Player searched, TreeNode* treeNode, int* adrFound)
{
	//cautam in BST un jucator, reinitializand de fiecare data radacina BST-ului in functie de scor
	if (treeNode == NULL) return;
	Player player = treeNode->player;

	if (searched.score > player.score)
	{
		fSearchInTree(searched, treeNode->right, adrFound);
	}
	else if (searched.score < player.score)
	{
		fSearchInTree(searched, treeNode->left, adrFound);
	}
	else
	{
		//am gasit un jucator cu scor egal. are si acelasi nume ? (este acelasi jucator?) 
		int foundNume = !strcmp(searched.numeFamilie, player.numeFamilie);
		int foundPrenume = !strcmp(searched.prenume, player.prenume);
		if (foundNume && foundPrenume)
		{
			*adrFound = 1;
			return;
		}
		else
		{
			*adrFound = 0;
			return;
		}

	}

}

void fCount(int minScore, int maxScore, TreeNode* treeNode, int* adrNrBetween)
{
	//numararea jucatorilor se face printr-o parcurgere preorder
	//daca jucatorul este intre cele 2 scoruri, incrementam solutia, cautam in stanga nodului corespunzator si in dreapta
	if (treeNode == NULL) return;
	if (treeNode->player.score > minScore&& treeNode->player.score < maxScore)
	{
		++* adrNrBetween;
	}
	fCount(minScore, maxScore, treeNode->left, adrNrBetween);
	fCount(minScore, maxScore, treeNode->right, adrNrBetween);
}

void fPopulateTree(Stack* fourStack, Tree* tree)
{
	//populam BST-ul, iterand prin stiva celor 4 tari
	while (fourStack->top != NULL)
	{
		Country* adrCountry = (fourStack->top)->adrCountry;
		Country country = *adrCountry;
		int iPlayer = 0;
		for (iPlayer = 0; iPlayer < country.nrPlayers; ++iPlayer)
		{
			Player player = country.vPlayers[iPlayer];
			fInsertInTree(player, &tree->root);
		}
		fPop(&fourStack);
	}
}

void fIdentifyAndCount(FILE* rezultateOut, Player* vTwoPlayers, Tree* tree)
{
	//identificam si numaram cati sportivi se afla in BST intre cei doi jucatori din cerinte.in

	//intai vedem daca exista jucatorii in BST
	int iPlayer;
	for (iPlayer = 0; iPlayer < 2; ++iPlayer)
	{
		int found = 0;
		fSearchInTree(vTwoPlayers[iPlayer], tree->root, &found);
		if (found == 0)
		{
			fprintf(rezultateOut, "\n%s %s nu poate fi identificat!\n", vTwoPlayers[iPlayer].numeFamilie, vTwoPlayers[iPlayer].prenume);
			return;
		}
	}
	int minScore = fMin(vTwoPlayers[0].score, vTwoPlayers[1].score);
	int maxScore = fMax(vTwoPlayers[0].score, vTwoPlayers[1].score);
	int nrBetween = 0;
	//numaram in variabila nrBetween jucatorii dintre scorurile minim si maxim ale celor 2 jucatori
	fCount(minScore, maxScore, tree->root, &nrBetween);
	fprintf(rezultateOut, "\n%d", nrBetween);
}
