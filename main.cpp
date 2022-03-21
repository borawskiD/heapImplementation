#include <iostream>
//prosta funkcja do wyswietlania tablicy, analogiczna jak w poprzednim cwiczeniu
void tabDisplayer(int *tab, int size){
    for (int i = 0; i<size; i++){
        std::cout<<tab[i] << " ";
    }
}
//przestawianie okreslonego elementu tak zeby byl zgodny z zasadami kopca
//int *&values jest odpowiednikiem javowego przekazywania referencji, czyli po prostu
//chce edytowac nie tablice jako argument metody, a jako "tablice globalna"
//inna implementacja niekoniecznie chciala mi dzialac :<
void swapDown(int index,int *&heap, int size){
    //definiuje index potencjalnego lewego i prawego potomka
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    //zmienna pomocnicza do tymczasowego przechowywania wartosci zeby nie uzywac swap
    int helper;
    //domyslnie ustawiam zmienna maks na obecny index, jesli znajde element o wiekszej wartosci, tu bede przechowywal jego index
    int max = index;
    //prosta implementacja przeszukiwania potomkow, sprawdzam najpierw czy lewy potomek w ogole istnieje (left < size)
    //a pozniej sprawdzam, czy lewy potomek jest wiekszy od elementu ktory badamy
    //jesli nie to ignorujemy
    //jesli tak to zmieniamy wartosc zmiennej max na index tego potomka
    if (left < size && heap[index] < heap[left]){
        max = left;
    }
    //tu jest wazne to, ze nie robimy od razu swapa! tylko sprawdzamy, czy prawy potomek nie jest przypadkiem jeszcze wiekszy
    //w ten sposob unikamy roznych dziwnych scenariuszy, pierwsza czesc warunku analogiczna do poprzednika
    //jesli sie sprawdza oba, ponownie zmieniamy wartosc zmiennej max na index, tym razem prawy
    if (right < size && heap[max] < heap[right]){
        max = right;
    }
    //sprawdzamy czy wartosc max ma inna niz domyslna wartosc, jesli ktorys z w/w warunkow sie spelnia, to faktycznie bedzie miala
    //zatem nastapi podmiana elementow rodzic <-> potomek; ponowne przypisanie wskaznika i ponowne wywolanie
    //(rekurencyjne) tej samej metody, tym razem jednak sprawdzamy potomka pierwotnego elementu, i tak do skutku
    //czyli albo az przestaniemy zamieniac elementy, albo skonczy nam sie kopiec :-)
    if (max != index){
        helper = heap[max];
        heap[max] = heap[index];
        heap[index] = helper;
        int * tab = (int *) heap;
        swapDown(max,tab,size);
    }
}
//funkcja hepify odpowiada za tworzenie kopca z podanej tablicy
void heapify(int size,int *&heapToMade){
    //prosta petla, zaczynamy od połowy dlugosci tablicy (zgodnie z definicja jest to pierwszy rodzic), a nastepnie
    //dekrementujemy aż do zera
    //kazda iteracja petli wywoluje wykonanie metody swapDown, ktora ma za zadanie poustawiac te elementy, ktore wymagaja
    //przesuniecia (opis wyzej)
    for (int i = size/2; i>=0; i--){
        int * tab = (int *)heapToMade;
        swapDown(i,tab,size);
    }
}
//ta metoda odpowiada za ominiecie koniecznosci uzycia std::vector :-)
void tabExpander(int *&heap, int &size, int element){
    //definiujemy dwa wskazniki wskazujace na NULL
    int *tab = NULL;
    int *newTab = NULL;
    //zwiekszamy rozmiar tablicy o 1
    size++;
    //definiujemy nowa(!) tablice na wskazniku newTab, ktora zajmuje miejsce wskaznika tab, drugi argument odpowiada
    //za obliczenie, ile miejsca jest nam potrzeba - mnozymy ilosc elementow tablicy z wartoscia mowiaca ile zajmuje
    //jedna komorka typu int
    newTab = (int *) realloc(tab, size * sizeof(int));
    //klasyczna petla z przepisywaniem wartosci
    for (int i = 0; i<size-1; i++){
        newTab[i] = heap[i];
    }
    //oczywiscie ostatni element podany jako argument musimy przypisac juz poza petla
    newTab[size-1] = element;
    //przepisuje wskaznik do heap, zeby "edytowac" "glowna" tablice (drzewo)
    heap = newTab;
    //na koniec porzadkuje uzywajac heapify
    heapify(size,heap);
    //i wyswietlam
    tabDisplayer(heap,size);
    std::cout<<std::endl;
    //usuwam niepotrzebny juz wskaznik
    delete []tab;
}
void removeElement(int &size, int *&heap){
    //podmieniam ostatni z pierwszym elementem, analogicznie jak wyzej
    //poniewaz usuwac moge tylko ostatni element (!)
    int help = heap[0];
    heap[0] = heap[size-1];
    heap[size-1] = help;
    ///
    /// usuwanie elementu
    ///
    ///tabDisplayer(values, size);
    //w zasadzie analogia do dodawania elementu, jedyna roznica to zamiast inkrementacji zmiennej size, to dekrementacja
    int *tab = NULL;
    int *newTab = NULL;
    size--;
    newTab = (int *) realloc(tab, size * sizeof(int));
    for (int i = 0; i<size; i++){
        newTab[i] = heap[i];
    }
    heap = newTab;
    heapify(size,heap);
    delete []tab;

}
void heapSort(int *&heap, int size){
    //bardzo ciekawy, wydajny i jednoczesnie dosc prosty alogrytm - to sie czesto nie zdarza :-)
    //przypisuje sobie do zmiennej pomocniczej obecna wersje size
    //zasada dzialania bedzie bardzo prosta - zawsze w kopcu korzen ma najwieksza wartosc, zatem
    //chcac posortowac przez kopcowanie, przerzucamy ten korzen na sam koniec, a nastepnie
    //najpierw pozostala czesc traktujemy metoda heapify(), aby pozniej z kolejnymi elementami
    //robic tak samo, i tak az unsortedsize bedzie rowny 0
    int unsortedSize = size;
    //petla while gwarantujaca przeszukanie kazdego elementu kopca
    while (unsortedSize > 0){
        //klasyczne podmienianie bez std::vector
        int helper = heap[0];
        heap[0] = heap[unsortedSize-1];
        heap[unsortedSize-1] = helper;
        //tutaj dekrementujemy zmienna unsortedSize
        unsortedSize--;
        //a tutaj bardzo wazna linia - robimy heapify na JUZ zmniejszonej, nieposrtowanej czesci
        heapify(unsortedSize,heap);
    }
    //proste wyswietlanie
    std::cout<<"Posortowana tablica przez kopcowanie:" <<std::endl;
    tabDisplayer(heap,size);
}
int main() {
    //deklaracja tablicy
    int values[] = {2, 1, 3, 7, 6, 8, 10, 9, 11, 4, 17, 13, 5, 12};
    //obliczanie rozmiaru poprzez podzielenie ilosci pamieci zajetej przez tablice przez ilosc pamieci zajetej przez jedna komorke typu int
    int size = sizeof(values)/sizeof(int);
    //castowanie na zwykly pointer, z jakiegos powodu inna wersja niekoniecznie chce mi dzialac - tutaj jest okej
    int * tab = (int *) values;
    //ponizej obsluga "menu"
    std::cout<<"Wprowadzona tablica: " <<std::endl;
    tabDisplayer(values,size);
    bool isOver = false;
    int choice;
    int a = 0;
    while (!isOver){
        std::cout<<std::endl;
        std::cout<<"---"<<std::endl;
        std::cout<<"0. Koniec"<<std::endl;
        std::cout<<"1. Dodaj element"<<std::endl;
        std::cout<<"2. Usun element"<<std::endl;
        std::cout<<"3. Wyswietl drzewo"<<std::endl;
        std::cout<<"4. Posortuj przez kopcowanie"<<std::endl;
        std::cout<<"5. Zamien na kopiec"<<std::endl;
        std::cout<<"Wybor: ";
        std::cin >> choice;
        switch (choice){
            case 0:
                isOver = true;
                break;
            case 1:
                std::cout<<"Podaj wartosc:";
                std::cin >> a;
                tabExpander(tab,size,a);
                break;
            case 2:
                if (size > 0) removeElement(size,tab);
                else std::cout<<"Nie ma nic do usuniecia!";
                std::cout<<"Obecny wyglad kopca:" <<std::endl;
                tabDisplayer(tab,size);
                break;
            case 3:
                tabDisplayer(tab,size);
                break;
            case 4:
                heapSort(tab,size);
                break;
            case 5:
                heapify(size,tab);
                std::cout<<"Obecny wyglad kopca:" <<std::endl;
                tabDisplayer(tab,size);
                break;
            default:
                std::cout<<"Unknown option, try again!"<<std::endl;
                break;
        }
    }
    delete []tab;
    return 0;
}


/*
 * Dominik Borawski A1 215IC
 * Kopiec - implementacja, wykorzystanie do sortowania
 * Tablica dynamiczna z uzyciem wskaznikow
 */

/* Output
 *
 */


/*
Wprowadzona tablica:
2 1 3 7 6 8 10 9 11 4 17 13 5 12
---
0. Koniec
1. Dodaj element
2. Usun element
3. Wyswietl drzewo
4. Posortuj przez kopcowanie
5. Zamien na kopiec
Wybor: 5
Obecny wyglad kopca:
17 11 13 9 6 8 12 2 7 4 1 3 5 10
---
0. Koniec
1. Dodaj element
2. Usun element
3. Wyswietl drzewo
4. Posortuj przez kopcowanie
5. Zamien na kopiec
Wybor: 1
Podaj wartosc:18
18 11 17 9 6 8 13 2 7 4 1 3 5 10 12

---
0. Koniec
1. Dodaj element
2. Usun element
3. Wyswietl drzewo
4. Posortuj przez kopcowanie
5. Zamien na kopiec
Wybor: 2
Obecny wyglad kopca:
17 11 13 9 6 8 12 2 7 4 1 3 5 10
---
0. Koniec
1. Dodaj element
2. Usun element
3. Wyswietl drzewo
4. Posortuj przez kopcowanie
5. Zamien na kopiec
Wybor: 3
17 11 13 9 6 8 12 2 7 4 1 3 5 10
---
0. Koniec
1. Dodaj element
2. Usun element
3. Wyswietl drzewo
4. Posortuj przez kopcowanie
5. Zamien na kopiec
Wybor: 4
Posortowana tablica przez kopcowanie:
1 2 3 4 5 6 7 8 9 10 11 12 13 17
---
0. Koniec
1. Dodaj element
2. Usun element
3. Wyswietl drzewo
4. Posortuj przez kopcowanie
5. Zamien na kopiec
Wybor: 0

Process finished with exit code 0
 */