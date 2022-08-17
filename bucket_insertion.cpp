#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;


// •	BUCKET Y SORT:  Explicación teórica, ejemplo y complejidad algorítmica
// •	PROPIEDADES: Características sobre cada algoritmo: beneficios/desventajas
// •	CODIGO: Captura de desarrollo en vscode, con el cálculo de la complejidad algorítmica
// •	GRAFICAS: Respectiva gráfica de complejidad computacional de cada algoritmo
// •	PREGUNTAS: Consultas a la clase de lo expuesto
// •	BIBLIOGRAFIA: Registro de fuentes consultadas



// Solo para contenedores con indice -->  Ej: Array/Vector
template<typename T, class container>
void bucketSort(container &cntr){

    int sz = size(cntr);
    vector<float> bucket[sz];
    
    int max = cntr[0];

    for (auto itr: cntr){ // O(n)
        if (itr > max){
            max = itr; 
        }
    }

    for (int i = 0; i < sz; i++){ // O(n)
        int bi = (sz * abs(int(cntr[i])))/abs(int(max+1));
        bucket[bi].push_back(cntr[i]);
    }

    for (int i = 0; i < sz; i++){ // O(n)
        sort(bucket[i].begin(), bucket[i].end()); // O(nlog(n))
    }

    int index = 0;
    for (int i = 0; i < sz; i++) // O(n)
        for (int j = 0; j < bucket[i].size(); j++) // O(n)
            cntr[index++] = bucket[i][j];
}

// O(n + n + nlog(n)*n + n^2) --> O(n^2log(n))


// Solo para contenedores con indice -->  Ej: Array/Vector
template<typename T, class container>
void insertionSort(container &cntr){

    int sz = size(cntr);

    for (int i = 1; i < sz; i++){ // O(n)

        int j = i - 1;

        for (int a = j; a >= 0; a-- ){ // O(n)
            
            T temp = cntr[a+1];

            if (cntr[a+1] < cntr[a]){

                cntr[a+1] = cntr[a];
                cntr[a] = temp;
            }
        }
    }
}

// O(n * n) --> O(n^2)


int main(){

char arr[] = {'c','a','b'};
bucketSort<char>(arr);
cout << "1. Sorting con Bucket Sort: " << endl;
for (auto itr: arr){
    cout << itr << " ";
}

cout << endl << endl;

vector<char> vc = {'c','a','b'};
insertionSort<char>(vc);
cout << "2. Sorting con Insertion Sort: " << endl;
for (auto itr : arr){
    cout << itr << " ";
}

return 0;
}