#include <iostream>
void tabDisplayer(int *tab, int size){
    for (int i = 0; i<size; i++){
        std::cout<<tab[i] << " ";
    }
}
void tabExpander(int *&values, int &size, int element){
    //tabDisplayer(values, size);
    int *tab = NULL;
    int *newTab = NULL;
    size++;
    newTab = (int *) realloc(tab, size * sizeof(int));
    for (int i = 0; i<size-1; i++){
        newTab[i] = values[i];
    }
    newTab[size-1] = element;
    values = newTab;
    tabDisplayer(values,size);
    std::cout<<std::endl;
    delete []tab;
}
void swapDown(int index,int *&heap, int size){
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int helper;
    int max = index;
    if(index < size){
        std::cout<<std::endl;
        std::cout<<"\nWyglad tablicy przed ewentualnym przesunieciem: "<<std::endl;
        tabDisplayer(heap,size);
        std::cout<<std::endl;
        std::cout<<"Analizowany index: "<<index<<" (wartosc elementu: "<<heap[index]<<")"<<std::endl;
        std::cout<<"Prawdopodobny indeks lewego potomka: " << left<<std::endl;
        std::cout<<"Prawdopodobny indeks prawego potomka: " << right<<std::endl;
        if (left < size && heap[index] < heap[left]){
            std::cout<<"Lewy potomek spełnia warunki przesunięcia, bo: " <<heap[index]<<"<"<<heap[left]<<std::endl;
            max = left;
        }
        if (right < size && heap[max] < heap[right]){
            std::cout<<"Prawy potomek spełnia warunki przesunięcia, bo: " <<heap[index]<<"<"<<heap[right]<<std::endl;
            max = right;
        }
        if (max != index){
            helper = heap[max];
            heap[max] = heap[index];
            heap[index] = helper;
            int * tab = (int *) heap;
            std::cout<<" Tablica po naszych działaniach wyglada następujaco:"<<std::endl;
            tabDisplayer(heap,size);
            swapDown(max,tab,size);
            std::cout<<std::endl;
        }
    }
    std::cout<<std::endl;
}
void heapify(int size,int *&heapToMade){
    for (int i = size/2; i>=0; i--){
        int * tab = (int *)heapToMade;
        swapDown(i,tab,size);
    }
    std::cout<<"Ostateczny wyglad naszego drzewa: ";
    std::cout<<std::endl;
    tabDisplayer(heapToMade,size);
}
void removeElement(int &size, int *&heap){
    std::cout<<std::endl<<"---"<<std::endl;
    std::cout<<"Usuwanie elementu"<<std::endl;
    std::cout<<"---"<<std::endl;
    std::cout<<"Stan poczatkowy tablicy (drzewa):"<<std::endl;
    tabDisplayer(heap,size);
    std::cout<<std::endl<<"Podmieniam korzen z ostatnim elementem kopca"<<std::endl;
    std::cout<<heap[0] << " <-> " <<heap[size-1]<<std::endl;
    std::cout<<"Stan po podmianie:"<<std::endl;
    int help = heap[0];
    heap[0] = heap[size-1];
    heap[size-1] = help;
    tabDisplayer(heap,size);
    ///
    /// usuwanie elementu
    ///
    //tabDisplayer(values, size);
    int *tab = NULL;
    int *newTab = NULL;
    size--;
    newTab = (int *) realloc(tab, size * sizeof(int));
    for (int i = 0; i<size; i++){
        newTab[i] = heap[i];
    }
    heap = newTab;
    std::cout<<std::endl<<"Stan po usunieciu ostatniego elementu:" <<std::endl;
    tabDisplayer(heap,size);
    //heapify
    std::cout<<std::endl<<"Aby utrzymac strukture drzewa, nalezy ulozyc tablice metoda heapify():"<<std::endl<<std::endl;
    heapify(size,heap);
    std::cout<<"Drzewo wyglada nastepujaco:"<<std::endl;
    delete []tab;

}
void addElement(int &size, int *&heap, int value){
    int * tab = (int *) heap;
    //heapify(size,tab);
    std::cout<<std::endl<<"---"<<std::endl;
    std::cout<<"Dodanie elementu: "<<value<<std::endl;
    std::cout<<"---"<<std::endl;
    std::cout<<"Tablica przed dodaniem:";
    tabDisplayer(tab,size);
    tabExpander(tab,size,value);
    std::cout<<"Tablica po dodaniu:";
    tabDisplayer(tab,size);
    std::cout<<std::endl<<"Nalezy sprawdzic czy wymaga uporzadkowania:"<<std::endl;
    int i = size-1;
    int parent = (i/2);
    int a;
    if (tab[i] < tab[parent]){
        std::cout<<"Nasza tablica (drzewo) nie wymaga porzadkowania."<<std::endl;
    }
    while (i >= 0 && tab[i] > tab[parent]){
        std::cout<<"Element " << tab[i] << " jest wiekszy od " <<tab[parent]<<" zatem podmieniam: "<<std::endl;
        std::cout<<tab[i]<<" <-> " <<tab[parent]<<std::endl;
        a = tab[i];
        tab[i] = tab[parent];
        tab[parent] = a;
        i = parent;
        parent = (i/2);
    }
    std::cout<<"Koncowy stan tablicy (drzewa):"<<std::endl;
    tabDisplayer(tab,size);
    heap = *& tab;
}
int main() {
    int values[] = {5, 17, 12, 13, 6, 9, 10, 7, 11, 4, 2, 8};
    int size = sizeof(values)/sizeof(int);
    int * tab = (int *) values;
    //tabExpander(tab,size,69);
    //swapDown(0,tab,size);
    heapify(size,tab);
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
        std::cout<<"Wybor: ";
        std::cin >> choice;
        switch (choice){
            case 0:
                isOver = true;
                break;
            case 1:
                std::cout<<"Podaj wartosc:";
                std::cin >> a;
                addElement(size,tab,a);
                break;
            case 2:
                if (size > 0) removeElement(size,tab);
                else std::cout<<"Nie ma nic do usuniecia!";
            case 3:
                tabDisplayer(tab,size);
                break;

        }
    }

    return 0;
}
