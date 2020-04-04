#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET 26 // nr literelor din alfabet
#define OFFSET 97 // 'a' - '0' = 97; 'b' - 1 = 97 , etc
#define WORDLENGTH 20 // lungimea maxima a unui cuvant

typedef struct TrieNode TrieNode;
struct TrieNode
{
	TrieNode* vLetters[ALPHABET]; // nodurile copil se asociaza literelor din alfabet
	short isEnd; // 1 daca se termina un cuvant in acea litera, incepand cu literele corespunzatoare traseului din arbore
};

void fInitNode(TrieNode** adrNode) // initializare a unui nod, cu nodul transmsis prin referinta (adica adresa nodului este un parametru)
 {
	*adrNode = malloc(sizeof(TrieNode)); // initializam dinamic nodul

	int i;
	for (i = 0; i < ALPHABET; ++i) // pentru fiecare litera din alfabet
	{
		(*adrNode)->vLetters[i] = NULL; // initializam cu NULL eventualele noduri "copil" corespunzatoare fiecarei litere
	}
	(*adrNode)->isEnd = 0; // si consideram ca, momentan, nu se termina niciun cuvant cu acea litera, incepand cu literele corespunzatoare traseului din arbore catre frunza
}

void fStrAllocCpy(char** adrWord, char aux[]) // functie de alocare dinamica a unui cuvant si a copierii sale dintr-un sir auxiliar; parametrii sunt cuvantul (prin referinta) si sirul auxiliar
{
	*adrWord = malloc(sizeof(strlen(aux))); // alocam atatia biti de char cate litere are sirul auxiliar; sizeof(char)=1
	strcpy(*adrWord, aux); // copiem sirul din vectorul de caractere auxiliar in sirul alocat dinamic 
}

void fInsert(char* word, TrieNode* trieRoot) // inserarea unui cuvant intr-un trie; parametrii sunt cuvantul si radacina trie-ului
{
	TrieNode* newNode = trieRoot, * oldNode = trieRoot; 
	// definim doua variabile utile pentru parcurgerea nodurilor in trie: una pentru nodul curent si una pentru nodul parcurs anterior

	int lg = strlen(word),i;
	for (i = 0; i < lg; ++i) // iteram prin literele cuvantului de adaugat
	{
		int key = (int)word[i];
		newNode = oldNode->vLetters[key - OFFSET]; // parcurgem trieul, pe ramura asociata literei curente din cuvant
		if (newNode == NULL)
		{
			fInitNode(&newNode); // daca nu exista nodul in initializam
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
	else
	{
		if (sizeof(word) < pos + 1)
		{
			// il realocam doar daca e nevoie de marirea dimensiunii sale
			char* aux = (char*)realloc(word, sizeof(char) * (pos + 1)); 
			if (aux)
			{
				word = aux;
			}
			else
			{
				printf("\n\nnu s-a putut realoca");
				exit(1);
			}
		}
		
		
	}
	word[pos] = car; // concatenam cuvantul cu litera
	*adrWord = word; 
}

void fPrintTrie(TrieNode* trieRoot, char* word, int pos) // afisarea cuvintelor din arbore; parametrii: radacina, un cuvant care se modifica in apel recursiv si pozitia ultimei litere
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
			fPrintTrie(trieRoot->vLetters[i], word, pos + 1); // apelam recursiv functia, avand acum ca parametrii noul nod, noul cuvant si pozitia anterioara + 1 (am adaugat o litera)
		}

	}

	if (trieRoot->isEnd == 1) // daca am ajuns la finalul cuvantului
	{
		fModifyWord(&word, '\0', pos); // adaugam si '\0' pentru afisare corecta


		// functia de afisare a cuvintelor din trie este apelata si in gasirea sufixelor
		// prin urmare, daca termenul caruia ii cautam sufix exista in trie si nu are sufixe atunci programul ar interpreta si un sufix nul pe care nu dorim sa il afisam
		// astfel:
		if (pos >= 1) 
		{
			printf("%s\n", word);
		}
	}
}


// cautare a unui cuvant in trie
// parametrii, in ordine : 
// cuvantul cautat  
// variabila corespunzatoare gasirii cuvantului (referinta) - valori 0 - nu exista , 1 - exista, 2 - este doar prefix pentru alt cuvant
// nodul unde l-am gasit(referinta)
void fSearch(TrieNode* trieRoot, char* word, int* adrFound, TrieNode** adrFoundNode)
{
	TrieNode* newNode = trieRoot, * oldNode = trieRoot; // variabile utile parcurgerii
	int lg = strlen(word),i;
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

void fAutocomplete(TrieNode* trieRoot, char* preffixWord) // gasirea sufixelor; parametrii: radacina arborelui, cuvantul "prefix" caruia ii cautam sufixele
{
	TrieNode* preffixNode = NULL;
	int found = 0;
	fSearch(trieRoot, preffixWord, &found, &preffixNode); // cautam cuvantul prefix si folosim variabila preffixNode (este nodul de unde vom incepe cautarea sufixelor)
	if (found == 0) // daca acest cuvant nu se afla in trie nici macar ca prefix
	{
		printf("\nacest cuvant nu are sufixe in trie"); // nu are sens sa ii cautam sufixe
		return;
	}
	char* word = NULL;
	int pos = 0;

	fPrintTrie(preffixNode, word, pos); // afisam cuvintele unui trie a carui radacina este nodului de unde incepem cautarea sufixelor - preffixNode
}

void fDeleteNodes(TrieNode* trieRoot, char* word, int iWordLetter) 
// stergerea nodurilor inutile (nu mai corespund unor alte cuvinte printr-o eventuala parcurgere in jos in urma stergerii unui cuvant
// parametrii: radacina trie-ului, cuvantul sters, indicele literei curente a cuvantului
{
	if (iWordLetter == strlen(word)) // daca am parcurs toate literele cuvantului
	{
		return;
	}

	int key = (int)word[iWordLetter];
	fDeleteNodes(trieRoot->vLetters[key - OFFSET], word, iWordLetter + 1); // apelam recursiv functia; radacina este acum nodul asociat literei urmatoare, modificam si indicele

	int isPreffix = 0, iAlphabetLetter; 
	for (iAlphabetLetter = 0; iAlphabetLetter < ALPHABET; ++iAlphabetLetter) // pentru fiecare litera din alfabet 
	{
		if (trieRoot->vLetters[iAlphabetLetter]) // in cazul in care cuvantul corespunzator parcurgerii in trie pana la nodul curent are sufixe
		{
			isPreffix = 1; // cuvantul este prefix; nu vom elibera memoria
			break;
		}
	}
	if (!isPreffix) 
	{
		free(trieRoot); // eliberam memoria doar daca nodul nu mai este util unei viitoare cautari 
		return;
	}

}


void fDeleteWord(TrieNode* trieRoot, char* word, TrieNode* foundNode)  // stergerea cuvantului; parametrii: radacina trie-ului, cuvantul, nodul corespunzator cuvantului
{
	foundNode->isEnd = 0; // cuvantul nu se mai termina in acea litera
	fDeleteNodes(trieRoot, word, 0); // daca vrem sa stergem noduri, atata timp cat trie-ul sa isi mentina utilitatea, apelam aceasta functie
}

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

int main()
{
	TrieNode* trieRoot = NULL;
	fInitNode(&trieRoot); // initializam nodul de radacina al trie-ului

	int nWords;
	printf("nr de cuvinte: ");
	scanf("%d", &nWords); // citim nr de cuvinte

	char aux[WORDLENGTH], * word = NULL; 
	// pentru a citi un sir de caractere alocat dinamic trebuie intai citit intr-un vector auxiliar de caractere si apoi copiat intr-o variabila char*
	int i;
	for (i = 0; i < nWords; ++i)
	{
		word = NULL;
		printf("\ncuvant: ");
		scanf("%s", aux);
		fStrAllocCpy(&word, aux); // alocam dinamic variabila char* cu atatia biti char cat avem nevoie si apoi copiem sirul de caractere
		fInsert(word, trieRoot); // inseram in trie cuvantul
	}

	int pos = 0; word = NULL;
	printf("\ntrie-ul contine cuvintele:\n");
	fPrintTrie(trieRoot, word, pos); // afisam cuvintele din trie

	printf("\ncuvant pe care il vom cauta: ");
	scanf("%s", aux);
	word = NULL;
	int found = 0;
	TrieNode* foundNode;
	fStrAllocCpy(&word, aux); // creem un sir de caractere alocat dinamic pentru cuvantul cautat in trie (prin aceeasi metoda)
	fSearch(trieRoot, word, &found, &foundNode); // cautam cuvantul
	if (found == 1) printf("\ncuvantul %s a fost gasit in trie", word);
	else printf("\ncuvantul %s nu a fost gasit in trie", word);


	printf("\ncuvant caruia ii vom afisa sufixele: ");
	scanf("%s", aux); word = NULL;
	fStrAllocCpy(&word, aux); // cuvant alocat dinamic
	fAutocomplete(trieRoot, word); // afisam sufixele


	printf("\ncuvant de sters: ");
	scanf("%s", aux); word = NULL;
	fStrAllocCpy(&word, aux); // cuvant alocat dinamic
	found = 0; foundNode = NULL;
	fSearch(trieRoot, word, &found, &foundNode); // cautam cuvantul

	if (found == 1) // daca este gasit in trie cuvantul
	{
		fDeleteWord(trieRoot, word, foundNode); // stergem cuvantul
		printf("\n'%s' sters; verificare: trie-ul are acum cuvintele:\n", word);
		char* word = NULL;
		int pos = 0;
		fPrintTrie(trieRoot, word, pos); // afisam cuvintele din trie pentru verificare
	}
	else // daca nu este gasit cuvantul (sau este doar un "prefix" pentru alt cuvant, nu si un cuvant in sine)
	{
		printf("\ncuvantul %s nu a fost gasit in trie, deci nu il putem sterge", word);
	}

	fEraseTree(trieRoot); // stergem trie-ul, toate nodurile vor fi eliminate
	if (word != NULL)
	{
		free(word); // stergem si cuvantul alocat dinamic
	}

	return 0;
}