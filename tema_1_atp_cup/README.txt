Acesta este proiectul meu pentru Tema 1.

Realizarea efectiva a cerintelor se face in main.c, functiile si structurile folosite fiind incluse in "Header.h".

Pentru ca am realizat ca am un cod foarte lung, am decis sa impart si acest header in mai multe parti, pentru fiecare structura de date : ListHeader, QueueHeader, StackHeader, TreeHeader. In acestea, stochez structurile definite si functiile (cele mai) generale specifice acelor structuri:
- Initializarea structurii
- Adaugarea unui element
- Popularea structurii cu mai multe adaugari de elemente
- Cautarea unui element
- Stergerea unui element
- Distrugerea structurii

si, in functie de structura:
- Duplicarea
- Gasirea unei valori minime
- Stergerea elementului cu o valoare minima
- Numararea elementelor intre 2 valori

Extern acestor headere raman functii parinte, mai complexe:
- simulare turneu 
- simulare meci
- parsarea fisierelor de intrare

Mai folosesc UtilHeader.h si UtilHeader.c pentru constante si functii care nu necesita structurile definite. Aceste functii sunt: gasirea minimului si a maximului intre 2 numere, alocarea dinamica a unui string, gasirea celei mai mari puteri a lui 2 mai mica decat un numar ("tinta" la care trebuie sa ajunga numarul de tari).

O problema intereanta este cum sa sincronizam punctajele unor jucatori in urma modificarilor facute dupa meciuri. Exista mai multe solutii: functii de actualizare, variabile statice etc. Am realizat dupa ceva timp ca e mai simplu sa folosesc in structurile de lista, coada si stiva pointeri la jucatori, respectiv la tari. Astfel, in operatiile de actualizare vom lucra mereu cu structura ce corespunde adresei, in loc sa creem copii la structura si sa pierdem valorile modificate. De asemenea, prin aceasta metoda nu este nevoie sa modificam structurile date in enunt (de Player si de Country).





