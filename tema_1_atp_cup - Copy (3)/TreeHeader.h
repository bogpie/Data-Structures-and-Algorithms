#pragma once

#ifndef TREEHEADER
	#define TREEHEADER
	typedef struct TreeNode TreeNode;
	struct TreeNode
	{
		TreeNode* left;
		TreeNode* right;
		Player player;
	};

	typedef struct Tree Tree;
	struct Tree
	{
		TreeNode* root;
	};

	void fInitTree(Tree** adrTree);
	void fAlocTreeNode(TreeNode** adrTreeNode);
	void fInsertInTree(Player player, TreeNode** adrTreeNode);
	void fPopulateTree(Stack* fourStack, Tree* tree);
	void fPrintTree(TreeNode* treeNode, FILE* rezultateOut);
	void fSearchInTree(Player searched, TreeNode* treeNode, int* adrFound);
	void fIdentifyAndCount(FILE* rezultateOut, Player* vTwoPlayers, Tree* tree);
	void fCount(int minScore, int maxScore, TreeNode* treeNode, int* adrNrBetween);

#endif