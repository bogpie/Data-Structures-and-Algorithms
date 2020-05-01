Programul efectueaza algoritmul lui Dijkstra pe un graf descris in fisierul input.txt sub forma:

	nr noduri nr muchii
		"nod stanga" "nod dreapta" cost
		"nod stanga" "nod dreapta" cost
		..
	nod sursa dijkstra

Pentru simplitatea inputului, un graf neorientat ar fi echivalent in programul meu cu un graf orientat cu muchii duble (stanga dreapta, dreapta stanga)

O poza cu graful ales de mine se afla in graf.png.

Complexitatea extragerii minimului dintr-un minHeap (sau, aici, a nodului pe care trebuie sa continuam parcurgerea) este O(1) (este primul element din heap). In schimb, trebuie facuta si o rearanjare a heap-ului care are complexitatea O(logn).

Intelegem ca nod de heap o structura care contine indexul unui varf si distanta (curenta) de la sursa la acel varf.