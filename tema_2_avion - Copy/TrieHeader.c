#include "MainHeader.h"

void fInitTrieNode(TrieNode** adrNode) // initializare a unui nod, cu nodul transmsis prin referinta (adica adresa nodului este un parametru)
{
	*adrNode = malloc(sizeof(TrieNode)); // initializam dinamic nodul

	int i;
	for (i = 0; i < ALPHABET; ++i) // pentru fiecare litera din alfabet
	{
		(*adrNode)->vLetters[i] = NULL; // initializam cu NULL eventualele noduri "copil" corespunzatoare fiecarei litere
	}
	(*adrNode)->isEnd = 0; // si consideram ca, momentan, nu se termina niciun cuvant cu acea litera, incepand cu literele corespunzatoare traseului din arbore catre frunza
}

void fInsertInTrie(char* word, TrieNode* trieRoot) // inserarea unui cuvant intr-un trie; parametrii sunt cuvantul si radacina trie-ului
{
	TrieNode* newNode = trieRoot, * oldNode = trieRoot;
	// definim doua variabile utile pentru parcurgerea nodurilor in trie: una pentru nodul curent si una pentru nodul parcurs anterior

	int lg = strlen(word), i;
	for (i = 0; i < lg; ++i) // iteram prin literele cuvantului de adaugat
	{
		int key = (int)((tolower)(word[i]));
		newNode = oldNode->vLetters[key - OFFSET]; // parcurgem trieul, pe ramura asociata literei curente din cuvant
		if (newNode == NULL)
		{
			fInitTrieNode(&newNode); // daca nu exista nodul in initializam
		}
		if (i == lg - 1)
		{
			newNode->isEnd = 1; // daca am ajuns la finalul cuvantului, marcam acest aspect prin variabila isEnd din nod
		}
		oldNode->vLetters[key - OFFSET] = newNode; // introducem noul nod in trie
		oldNode = newNode; // reinitializam nodul parcurs anterior
	}
}

void fModifyWord(char** adrWord, char car, int pos) // functie de concatenare al cuvantului cu o litera
{
	char* word = *adrWord;
	if (word == NULL)
	{
		word = malloc(sizeof(char)); // alocam cuvantul
	}
	/*
	else
	{
		if (strlen(word) < pos + 1)
		{
			// il realocam doar daca e nevoie de marirea dimensiunii sale
			char* oldWord = malloc(pos + 1);
			strcpy(oldWord, word);
			int lg = strlen(word);
			char* aux = (char*)realloc(word, (lg + 1) * sizeof(char)); //word, (lg + 1) * sizeof(char)

			if (aux)
			{
				strcpy(aux, oldWord);
				free(oldWord);
				word = aux;
			}
			else
			{
				printf("\n\nnu s-a putut realoca");
				exit(1);
			}
		}
	}
	*/

	word[pos] = car; // concatenam cuvantul cu litera
	*adrWord = word;
}

void fCountTrie(TrieNode* trieRoot, int pos, int* adrNrWords) // numararea cuvintelor din arbore; parametrii: radacina, un cuvant care se modifica in apel recursiv si pozitia ultimei litere
{
	if (trieRoot == NULL)
	{
		return; // nu parcurgem dincolo de o frunza
	}
	int i;
	for (i = 0; i < ALPHABET; ++i)  // pentru fiecare litera din alfabet
	{
		if (trieRoot->vLetters[i] != NULL) // daca sirul se continua in litera cu ordinul i 
		{
			fCountTrie(trieRoot->vLetters[i], pos + 1, adrNrWords); // apelam recursiv functia, avand acum ca parametrii noul nod, noul cuvant si pozitia anterioara + 1 (am adaugat o litera)
		}

	}
	if (trieRoot->isEnd == 1) // daca am ajuns la finalul cuvantului
	{
		++* adrNrWords;
	}
}

void fPrintTrie(FILE* output, TrieNode* trieRoot, char* word, int pos) // afisarea cuvintelor din arbore; parametrii: radacina, un cuvant care se modifica in apel recursiv si pozitia ultimei litere
{
	if (trieRoot == NULL)
	{
		return; // nu parcurgem dincolo de o frunza
	}
	int i;
	for (i = 0; i < ALPHABET; ++i)  // pentru fiecare litera din alfabet
	{
		if (trieRoot->vLetters[i] != NULL) // daca sirul se continua in litera cu ordinul i 
		{
			char car = (char)(i + OFFSET);
			fModifyWord(&word, car, pos);  // concatenam cuvantul cu litera
			fPrintTrie(output, trieRoot->vLetters[i], word, pos + 1); // apelam recursiv functia, avand acum ca parametrii noul nod, noul cuvant si pozitia anterioara + 1 (am adaugat o litera)
		}

	}
	if (trieRoot->isEnd == 1) // daca am ajuns la finalul cuvantului
	{
		fModifyWord(&word, '\0', pos);
		// adaugam si '\0' pentru afisare corecta
		// functia de afisare a cuvintelor din trie este apelata si in gasirea sufixelor
		// prin urmare, daca termenul caruia ii cautam sufix exista in trie si nu are sufixe atunci programul ar interpreta si un sufix nul pe care nu dorim sa il afisam
		// astfel:
		if (pos >= 1)
		{
			word[0] = toupper(word[0]);
			fprintf(output, "%s ", word);
		}
	}
}

void fSearchInTrie(TrieNode* trieRoot, char* word, int* adrFound, TrieNode** adrFoundNode)
{
	// cautare a unui cuvant in trie
	// parametrii, in ordine : 
	// cuvantul cautat  
	// variabila corespunzatoare gasirii cuvantului (referinta) - valori 0 - nu exista , 1 - exista, 2 - este doar prefix pentru alt cuvant
	// nodul unde l-am gasit(referinta)
	TrieNode* newNode = trieRoot, * oldNode = trieRoot; // variabile utile parcurgerii
	int lg = strlen(word), i;
	for (i = 0; i < lg; ++i) // parcurgem literele cuvantului
	{
		int key = (int)word[i];
		newNode = oldNode->vLetters[key - OFFSET]; // in acelasi timp, parcurgem si trie-ul
		if (newNode == NULL) // daca nu am putut parcurge toate literele cuvantului in trecerea prin arbore
		{
			*adrFound = 0; // cuvantul nu exista
			return;
		}
		if (i == lg - 1) // daca am putut parcurge toate literele
		{
			*adrFoundNode = newNode;

			if (newNode->isEnd == 1) // cuvantul corespunzator parcurgerii trie-ului se termina in ultima litera a termenului cautat
			{
				*adrFound = 1; // cuvantul exista
				return;
			}
			else // nu se termina, se poate continua si pe o alta ramura copil
			{
				*adrFound = 2; // este doar prefix
				return;
			}
		}
		oldNode = newNode; // reinitializam nodul anterior
	}
}

//void fAutocomplete(TrieNode* trieRoot, char* preffixWord) // gasirea sufixelor; parametrii: radacina arborelui, cuvantul "prefix" caruia ii cautam sufixele

//void fDeleteNodes(TrieNode* trieRoot, char* word, int iWordLetter)

//void fDeleteWord(TrieNode* trieRoot, char* word, TrieNode* foundNode)  // stergerea cuvantului; parametrii: radacina trie-ului, cuvantul, nodul corespunzator cuvantului

void fEraseTree(TrieNode* trieRoot) // stergerea tuturor nodurilor trie-ului
{
	int i;
	for (i = 0; i < ALPHABET; ++i) // pentru fiecare litera din alfabet
	{
		TrieNode* newNode = trieRoot->vLetters[i];
		if (newNode) // daca putem continua parcurgerea trie-ului pe ramura literei cu ordinul i
		{
			fEraseTree(newNode); // apelam recursiv functia, alegand acum ca radacina noul nod parcurs
		}
	}

	if (trieRoot) // intai se vor sterge frunzele 
	{
		trieRoot->isEnd = 0;
		free(trieRoot);
	}

}
