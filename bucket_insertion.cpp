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
template <typename T, class container>
void insertionSort(container &cntr)
{

    long long int sz = size(cntr);
    T key;

    for (long long int i = 1; i < sz; i++) // O(n)
    { 

        key = cntr[i]; // O(n)
        long long int pv = i - 1; // O(n)

        while (pv >= 0 && cntr[pv] > key){
        // BC: Array esta ordenado --> En ninguna iteracion entra al bucle
        // WC: Array esta ordenado al reves --> En cada iteracion tiene
        //     que pasar el elemento en cntr[i] al inicio del array
        // AC: Realiza menos iteraciones que WC --> En promedio O(n)

            cntr[pv + 1] = cntr[pv];
            pv -= 1;
        }

        cntr[pv + 1] = key;
    }
}

// BC: O (n * 1) --> O(n)
// AC: O(n * n) --> O(n^2)
// WC: O (n * n) --> O(n^2)
// SC: Ordenamos el array pasado por referencia
//     --> No se reserva memoria extra --> O(1)

// Solo para contenedores con indice -->  Ej: Array/Vector
template<typename T, class container>
void bucketExtension(container &cntr){
// Se trabaja con k buckets --> Para nosotros k = n

    long long int sz = size(cntr);
    vector<vector<long long int>> buckets;
    buckets.resize(sz); // O(n)

    T max = cntr[0];

    for (auto itr : cntr){ // O(n)
        if (itr > max)
            max = itr;
    }

    for (long long int i = 0; i < sz; i++){ // O(n)
        long long int bi = (sz * abs(cntr[i])) / abs(max + 1);
        buckets[bi].push_back(cntr[i]);
    }

    for (long long int i = 0; i < sz; i++){ // O(n)
        // El sorting se puede hacer con cualquier algoritmo,
        // pero se acostumbra con Insertion Sort: O(n^2)
        // Con Merge Sort --> (n * log(n))
        insertionSort<T>(buckets[i]); 
    }

    // BC: En cada bucket tenemos un elemento
    //     --> No se ordenada nada --> O(n)
    // AV: Se ordenan algunos buckets 
    //     --> O(n^2/k + n) --> O(n)
    // WC: Todos los elementos estan en un solo bucket 
    //     --> Se aplica el Insertion Sort --> O(n^2)

    long long int index = 0;
    for (long long int i = 0; i < sz; i++) // O(n)
        for (long long int j = 0; j < buckets[i].size(); j++)
            cntr[index++] = buckets[i][j];
    // En todos los casos recorremos n casillas --> size(array)
    // BC: O(n) ; AC: O(n) ; WC: O(n) 
}

// BC: O(n + n + n + n) --> O(n)
// AV: O(n + n + n + n) --> O(n)
// WC: O(n + n + n^2 + n) --> O(n^2)
// SC: Reservamos un vector de n buckets
//     --> O(n)

// Solo para contenedores con indice -->  Ej: Array/Vector
template<typename T, class container>
void bucketSort(container &cntr){

    T max = cntr[0]; T min = cntr[0];

    for (auto itr : cntr){ // O(n)
        if (itr > max) max = itr;
        if (itr < min) min = itr;
    }

    if (min >= 0 && max >= 0){ // M.adicional --> O(1)
        bucketExtension<T>(cntr);
        // BC: O(n) ; AV: O(n) ; WC: O(n^2) ; SC: O(n)
    }
    else if (min < 0 && max < 0){ vector<T> temp; // M.adicional --> O(n)

        for (auto itr : cntr) temp.push_back(-1*itr);
        bucketExtension<T>(temp);
        // BC: O(n) ; AV: O(n) ; WC: O(n^2) ; SC: O(n)

        for (long long int i =0; i < size(cntr); i++){ 
            cntr[i] = -1*temp[size(cntr) - 1 - i];
        }
    }
    else{ // M.adicional --> O(n)
        vector<T> pos; vector<T> neg;

        for (auto itr: cntr){
            if (itr < 0)
                neg.push_back(-1*itr);
            else
                pos.push_back(itr);
        }
        bucketExtension<T>(pos);
        bucketExtension<T>(neg);
        // BC: O(n) ; AV: O(n) ; WC: O(n^2) ; SC: O(n)
        //      --> Ambos sumados

        for (long long int i = 0; i < neg.size(); i++){ // O(c)
            cntr[i] = -1*neg[neg.size() - 1 - i];}

        for (long long int j = neg.size(); j < size(cntr); j++){ // O(n - c) -> O(c)
            cntr[j] = pos[j - neg.size()];}
            }
}
// BC: O(n) ; AV: O(n) ; WC: O(n^2);
// SC: +: O(n) ; -/(+/-): O(2n) -> O(n)

int main(){

    vector<long long int> arr;
    long long int n = 1000;

    for (long long int i = n; i > 0; i--){
        arr.push_back(i);
    }

    vector<long long int> arr2;

    for (long long int i = n; i > 0; i--)
    {
        arr2.push_back(i);
    }

    // bucketSort<long long int>(arr);
    insertionSort<long long int>(arr2);

    for (long long int i = 0; i < n; i++){
        cout << arr2[i] << "\n";
        if (arr2[i] > arr2[i+1]){
            cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
            i = n;
        }
    }

return 0;
}