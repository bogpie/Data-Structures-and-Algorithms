#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET 26
#define OFFSET 97
#define WORDLENGTH 20

typedef struct TrieNode TrieNode;
struct TrieNode
{
	TrieNode* vLetters[ALPHABET];
	short isEnd;
};

void fInitNode(TrieNode** adrNode)
{
	*adrNode = malloc(sizeof(TrieNode));
	
	for (int i = 0; i < ALPHABET; ++i)
	{
		(*adrNode)->vLetters[i] = NULL;
	}
	(*adrNode)->isEnd = 0;
}

void fStrAllocCpy(char** adrWord, char aux[])
{
	*adrWord = malloc(sizeof(strlen(aux)));
	strcpy(*adrWord, aux);
}

void fInsert(char* word, TrieNode* trieRoot)
{
	TrieNode* newNode = trieRoot , *oldNode = trieRoot;
	int lg = strlen(word);
	for (int i = 0; i < lg; ++i)
	{
		int key = (int)word[i];
		newNode = oldNode->vLetters[key - OFFSET];
		if (newNode == NULL)
		{
			fInitNode(&newNode);
		}
		if (i == lg - 1)
		{
			newNode->isEnd = 1;
		}
		oldNode->vLetters[key - OFFSET] = newNode;
		oldNode = newNode;
	}
}

void fModifyWord(char** adrWord, char car,int pos)
{
	char* word = *adrWord;
	if (word == NULL)
	{
		word = malloc(sizeof(char)); // pt '\0'
	}
	else
	{
		word = realloc(word, sizeof(char) * (pos+1));
		if (!word)
		{
			exit(1);
		}
	}
	word[pos] = car;
	*adrWord = word;
}

void fPrintTrie(TrieNode* trieRoot,char* word, int pos)
{
	if (trieRoot->isEnd == 1)
	{
		fModifyWord(&word, '\0', pos);
	
		if (pos >= 1)
		{
			printf("%s\n", word);
		}
	}

	for (int i = 0; i < ALPHABET; ++i)
	{
		if (trieRoot->vLetters[i] != NULL)
		{
			char car = (char)(i + OFFSET);
			fModifyWord(&word, car,pos);
			fPrintTrie(trieRoot->vLetters[i], word, pos+1);
		}
		
	}
}




void fSearch(TrieNode* trieRoot, char* word, int* adrFound,TrieNode** adrFoundNode)
{
	TrieNode* newNode = trieRoot, * oldNode = trieRoot;
	int lg = strlen(word);
	for (int i = 0; i < lg; ++i)
	{
		int key = (int)word[i];
		newNode = oldNode->vLetters[key - OFFSET];
		if (newNode == NULL)
		{
			*adrFound = 0;
			return;
		}
		if (i == lg - 1)
		{
			*adrFoundNode = newNode;

			if (newNode->isEnd == 1)
			{
				*adrFound = 1;
				return;
			}
			else
			{
				*adrFound = 2;
				return;
			}
		}
		oldNode = newNode;
	}
}

void fAutocomplete(TrieNode* trieRoot, char* preffixWord)
{
	TrieNode* preffixNode = NULL;
	int found = 0;
	fSearch(trieRoot, preffixWord, &found, &preffixNode);
	if (found == 0)
	{
		printf("\nacest cuvant nu are sufixe in trie");
		return;
	}
	char* word = NULL;
	int pos = 0;
	fPrintTrie(preffixNode, word, pos);
}

void fDeleteNodes(TrieNode* trieRoot, char* word, int iWordLetter)
{
	if (iWordLetter == strlen(word))
	{
		return;
	}

	int key = (int)word[iWordLetter];
	fDeleteNodes(trieRoot->vLetters[key - OFFSET], word, iWordLetter + 1);

	int isPreffix = 0;
	for (int iAlphabetLetter = 0; iAlphabetLetter < ALPHABET; ++iAlphabetLetter)
	{
		if (trieRoot->vLetters[iAlphabetLetter])
		{
			isPreffix = 1;
			break;
		}
	}
	if (!isPreffix)
	{
		free(trieRoot);
		return;
	}	

}


void fDeleteWord(TrieNode* trieRoot, char* word, TrieNode* foundNode)
{
	foundNode->isEnd = 0;
	fDeleteNodes(trieRoot, word,0);
}

void fEraseTree(TrieNode* trieRoot)
{
	for (int iAlphabetLetter = 0; iAlphabetLetter < ALPHABET; ++iAlphabetLetter)
	{
		TrieNode* newNode = trieRoot->vLetters[iAlphabetLetter];
		if (newNode)
		{
			fEraseTree(newNode);
		}
	}

	if (trieRoot)
	{
		trieRoot->isEnd = 0;
		free(trieRoot);
	}
	
}

int main()
{
	TrieNode* trieRoot = NULL;
	fInitNode(&trieRoot);
	
	int nWords;
	printf("nr de cuvinte: "); 
	scanf("%d", &nWords);

	char aux[WORDLENGTH], * word = NULL ;

	for (int i = 0; i < nWords; ++i)
	{
		word = NULL;
		printf("\ncuvant: ");
		scanf("%s", aux);
		fStrAllocCpy(&word, aux);
		fInsert(word, trieRoot);
	}
	
	int pos = 0; word = NULL;
	printf("\ntrie-ul contine cuvintele:\n"); 
	fPrintTrie(trieRoot, word, pos);
	
	printf("\ncuvant pe care il vom cauta: ");
	scanf("%s", aux); 
	word = NULL; 
	int found = 0; 
	TrieNode* foundNode;
	fStrAllocCpy(&word, aux);
	fSearch(trieRoot, word, &found,&foundNode);
	if (found == 1) printf("\ncuvantul %s a fost gasit in trie",word);
	else printf("\ncuvantul %s nu a fost gasit in trie",word);


	printf("\ncuvant caruia ii vom afisa sufixele: ");
	scanf("%s", aux); word = NULL;
	fStrAllocCpy(&word, aux);
	fAutocomplete(trieRoot,word);

	printf("\ncuvant de sters: ");
	scanf("%s", aux); word = NULL;
	fStrAllocCpy(&word, aux);
	found = 0; foundNode = NULL;
	fSearch(trieRoot, word, &found, &foundNode);
	
	if (found==1)
	{
		fDeleteWord(trieRoot, word,foundNode);
		printf("\n'%s' sters; verificare: trie-ul are acum cuvintele:\n",word);
		char* word = NULL; 
		int pos = 0;
		fPrintTrie(trieRoot, word, pos);
	}
	else
	{
		printf("\ncuvantul %s nu a fost gasit in trie, deci nu il putem sterge", word);	
	}

	fEraseTree(trieRoot);

	return 0;
}