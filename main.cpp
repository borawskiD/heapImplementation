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
        std::cout<<"Wyglad tablicy przed ewentualnym przesunieciem: "<<std::endl;
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
            std::cout<<"Tablica po naszych działaniach wyglada następujaco:"<<std::endl;
            tabDisplayer(heap,size);
            std::cout<<std::endl<<"---"<<std::endl;
            std::cout<<std::endl;
            swapDown(max,tab,size);
        }
    }
}
void heapify(int size,int *&heapToMade){
    for (int i = size/2; i>=0; i--){
        int * tab = (int *)heapToMade;
        swapDown(i,tab,size);
    }
}
int main() {
    int values[] = {5, 17, 12, 13, 6, 9, 10, 7, 11, 4, 2, 8};
    int size = sizeof(values)/sizeof(int);
    int * tab = (int *) values;
    //tabExpander(tab,size,69);
    //swapDown(0,tab,size);
    heapify(size,tab);
    std::cout<<"Ostateczny wyglad naszego drzewa: ";
    tabDisplayer(tab,size);

    return 0;
}
