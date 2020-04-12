Realizarea efectiva a cerintelor se face in main.c, functiile si structurile folosite fiind incluse in "Header.h".

Pentru ca am realizat ca am un cod foarte lung, am decis sa impart si acest header in mai multe parti, pentru fiecare structura de date : ListHeader, QueueHeader, StackHeader, TreeHeader. In acestea, stochez structurile definite si functiile specifice acelor structuri. Aceste functii pot fi:
- initializarea structurii
- adaugarea unui element
- popularea structurii cu mai multe adaugari de elemente
- cautarea unui element
- stergerea unui element
- distrugerea structurii
- duplicarea
- gasirea unei valori minime
- stergerea elementului cu o valoare minima
- numararea elementelor intre 2 valori

Extern acestor headere de structura raman in "Header.h" functii "parinte", mai complexe:
- simulare turneu 
- simulare meci
- parsarea fisierelor de intrare

Mai folosesc UtilHeader.h si UtilHeader.c pentru:
- constante (lungimea maxima a unui sir de caractere, o valoare FLT_MAX pentru initializarea unui minim pentru scorul local ce este de tip float
- functii care nu necesita structurile definite. Aceste functii sunt: gasirea minimului si a maximului intre 2 numere, alocarea dinamica a unui string, gasirea celei mai mari puteri a lui 2 mai mica decat un numar ("tinta" la care trebuie sa ajunga numarul de tari).
- includerea bibliotecilor. <string.h> este utila in folosirea functiilor strcmp pentru compararea de texte, iar strcpy o folosesc pentru transmiterea unui sir dintr-un buffer intr-o variabila (vector) alocata dinamic

O problema intereanta este cum sa sincronizam punctajele unor jucatori in urma modificarilor facute dupa meciuri. Exista mai multe solutii: functii de actualizare, variabile statice etc. Am realizat dupa ceva timp ca e mai simplu sa folosesc in structurile de lista, coada si stiva pointeri la jucatori, respectiv la tari. Astfel, in operatiile de actualizare vom lucra mereu cu structura ce corespunde adresei, in loc sa creem copii la structura si sa pierdem valorile modificate. De asemenea, prin aceasta metoda nu este nevoie sa modificam structurile date in enunt (de Player si de Country).
O structura auxiliara importanta pe care am folosit-o este stiva ultimelor patru tari ramase in competitie. Adaugarea in momentul sferturilor de finala a adreselor la tari in aceasta stiva nu prezinta problema modificarii punctajelor din semifinala si din finala datorita lucrului fara duplicari in alte variabile ale structurilor.

Iata cum functioneaza simularea turneului, pe baza stivei de tari (stack) :
- se initializeaza stiva winner
- se scot cate 2 tari din stiva stack
- se populeaza coada de meciuri - care de fapt este o coada de jucatori (daca a joaca cu b si a joaca cu c se introduc in coada a,b,a,c)
Urmeaza simularea meciurilor:
- se scot primii 2 jucatori din coada
- se joaca meciul cu actualizarea scorurilor locale (prin folosirea adreselor in functii, deci prin transmitere prin referinta). La egalitatea scorurilor locale, aflam jucatorul cu scorul maxim. Nu este nevoie de cautarea jucatorilor cu scor maxim pentru FIECARE din cele 2 tari. Mai simplu: initializam un scor maxim cu '-1', iteram prin jucatorii din tara 1 si modificam maximul; apoi iteram prin jucatorii din tara 2, cautam daca un jucator are valoarea mai mare, si, daca da, inchidem bucla (nu este nevoie sa vedem daca este chiar cel mai mare, maximul de scor este clar in tara 2)
- am aflat tara castigatoare, o introducem in winner
- stiva de jucatori devine stiva winner - reactualizarea stivei stack(potentialii castigatori pentru runda curenta sunt cei ce au invins in runda precedenta)
- cand ajungem la sferturile de finala avem grija sa salvam tarile pentru cerinta 4 si 5 (eu le salvez in stiva fourStack)

Pentru arborele BST, este de mentionat ca afisarea se face inorder (pentru ordinea crescatoare a scorului), iar numararea elementelor intre 2 valori am decis sa o fac preorder.

