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

    int sz = size(cntr);
    T key;

    for (int i = 1; i < sz; i++) // O(n)
    {

        key = cntr[i]; // O(1)
        int pv = i - 1; // O(1)

        while (pv >= 0 && cntr[pv] > key) // O(n)
        // BC: Array esta ordenado --> En ninguna iteracion entra al bucle
        // WC: Array esta ordenado al reves --> En cada iteracion tiene 
        //     que pasar el elemento en cntr[i] al inicio del array
        // AC: Realiza menos iteraciones que WC --> En promedio O(n)
        {

            cntr[pv + 1] = cntr[pv];
            pv -= 1;
        }

        cntr[pv + 1] = key;
    }
}

// BC: O (n * 1) --> O(n)
// AC: O(n * n) --> O(n^2)
// WC: O (n * n) --> O(n^2)

// Solo para contenedores con indice -->  Ej: Array/Vector
template<typename T, class container>
void bucketExtension(container &cntr){

    int sz = size(cntr);
    vector<T> buckets[sz];

    T max = cntr[0];

    for (auto itr : cntr) // O(n)
    {
        if (itr > max)
            max = itr;
    }

    for (int i = 0; i < sz; i++)
    { // O(n)
        int bi = (sz * abs(cntr[i])) / abs(max + 1);
        buckets[bi].push_back(cntr[i]);
    }

    for (int i = 0; i < sz; i++)
    { // O(n)
        // El sorting se puede hacer con cualquier algoritmo, pero se acostumbra con Insertion Sort: O(n^2)
        // Con Merge Sort --> (n * log(n))
        insertionSort<T>(buckets[i]); // O(n^2)
    }

    // BC: En cada bucket tenemos un elemento
    //     --> No se ordenada nada --> O(n)
    // AV: Se ordenan algunos buckets, con promedio
    //     de k elementos en cada uno --> O(n*k^2) --> O(n*k)
    // WC: Todos los elementos estan en un solo bucket --> O(n^2)

    int index = 0;
    for (int i = 0; i < sz; i++) // O(n)
        for (int j = 0; j < buckets[i].size(); j++)
            // BC: En cada bucket hay un elemento --> O(n)
            // AV: En cada bucket hay un promedio de k elementos --> O(n*k)
            // WC: Todos los elementos en un bucket --> O(n)
            cntr[index++] = buckets[i][j];
}

// BC: O(n + n + n + n) --> O(n)
// AV: O(n + n + n*k + n*k) --> O(n*k)
// WC: O(n + n + n^2 + n) --> O(n^2)


// Solo para contenedores con indice -->  Ej: Array/Vector
template<typename T, class container>
void bucketSort(container &cntr){

    T max = cntr[0];
    T min = cntr[0];

    for (auto itr : cntr){ // O(n)
        if (itr > max) max = itr;
        else min = itr;
    }

    if (min >= 0 && max >= 0){
        bucketExtension<T>(cntr);
        // BC: O(n)
        // AV: O(n*k)
        // WC: O(n^2)
    }
    else if (min < 0 && max < 0){
        vector<T> temp;

        for (auto itr : cntr)
            temp.push_back(-1*itr);

        bucketExtension<T>(temp);
        // BC: O(n)
        // AV: O(n*k)
        // WC: O(n^2)

        for (int i =0; i < size(cntr); i++){ // 0(n)
            cntr[i] = -1*temp[size(cntr) - 1 - i];
        }
    }
    else{
        vector<T> pos;
        vector<T> neg;

        for (auto itr: cntr){ // O(n)
            if (itr < 0)
                neg.push_back(-1*itr);
            else
                pos.push_back(itr);
        }

        bucketExtension<T>(pos);
        bucketExtension<T>(neg);

        // BC: O(n)
        // AV: O(n*k)
        // WC: O(n^2)

        for (int i = 0; i < neg.size(); i++){ // O(s)
            cntr[i] = -1*neg[neg.size() - 1 - i];
        }

        for (int j = neg.size(); j < size(cntr); j++){ // O(n-s)
            cntr[j] = pos[j - neg.size()];
        }

    }
}

// BC: O(n)
// AV: O(n*k)
// WC: O(n^2)

int main(){

    vector<int> arr = {1,0,-2,-1}; 
    bucketSort<int>(arr);
    cout << "1. Sorting con Bucket Sort: " << endl;
    for (auto itr : arr)
    {
        cout << itr << " ";
}

cout << endl << endl;

vector<int> vc = {2,8,5,3,9,4};
insertionSort<int>(vc);
cout << "2. Sorting con Insertion Sort: " << endl;
for (auto itr : vc){
    cout << itr << " ";
}

return 0;
}