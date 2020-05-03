#pragma once

#ifndef TRIEHEADER

#define TRIEHEADER
#define ALPHABET 26 // nr literelor din alfabet
#define OFFSET 97 // 'a' - '0' = 97; 'b' - 1 = 97 , etc
//#define WORDLENGTH 20 // lungimea maxima a unui cuvant

typedef struct TrieNode TrieNode;
struct TrieNode
{
	TrieNode* vLetters[ALPHABET]; // nodurile copil se asociaza literelor din alfabet
	short isEnd; // 1 daca se termina un cuvant in acea litera, incepand cu literele corespunzatoare traseului din arbore
};

void fInitTrieNode(TrieNode** adrNode);
void fInsertInTrie(char* word, TrieNode* trieRoot);
void fPrintTrie(FILE* output,TrieNode* trieRoot, char* word, int pos,int* adrNrWords);
void fSearchInTrie(TrieNode* trieRoot, char* word, int* adrFound, TrieNode** adrFoundNode);
void fEraseTree(TrieNode* trieRoot);
void fModifyWord(char** adrWord, char car, int pos);

#endif // !TRIEHEADER