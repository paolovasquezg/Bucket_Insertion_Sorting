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

    for (long long int i = 1; i < sz; i++){

        key = cntr[i];
        long long int pv = i - 1;

        while (pv >= 0 && cntr[pv] > key){ 

            cntr[pv + 1] = cntr[pv];
            pv -= 1;
        }

        cntr[pv + 1] = key;
    }
}


template<typename T, class container>
void bucketExtension(container &cntr){

    long long int sz = size(cntr);
    vector<vector<long long int>> buckets;
    buckets.resize(sz);

    T max = cntr[0];

    for (auto itr : cntr){
        if (itr > max)
            max = itr;
    }

    for (long long int i = 0; i < sz; i++){
        long long int bi = (sz * abs(cntr[i])) / abs(max + 1);
        cout << bi << "xd" << "\n";
        buckets[bi].push_back(cntr[i]);
    }

    for (long long int i = 0; i < sz; i++){
        insertionSort<T>(buckets[i]); 
    }

    long long int index = 0;
    for (long long int i = 0; i < sz; i++) // O(n)
        for (long long int j = 0; j < buckets[i].size(); j++)
            cntr[index++] = buckets[i][j];
}


// Solo para contenedores con indice -->  Ej: Array/Vector
template<typename T, class container>
void bucketSort(container &cntr){

    T max = cntr[0]; T min = cntr[0];

    for (auto itr : cntr){
        if (itr > max) max = itr;
        if (itr < min) min = itr;
    }

    if (min >= 0 && max >= 0){
        bucketExtension<T>(cntr);
    }
    else if (min < 0 && max < 0){ vector<T> temp;

        for (auto itr : cntr) temp.push_back(-1*itr);
        bucketExtension<T>(temp);

        for (long long int i =0; i < size(cntr); i++){
            cntr[i] = -1*temp[size(cntr) - 1 - i];
        }
    }
    else{
        vector<T> pos; vector<T> neg;

        for (auto itr: cntr){
            if (itr < 0)
                neg.push_back(-1*itr);
            else
                pos.push_back(itr);
        }
        bucketExtension<T>(pos);
        bucketExtension<T>(neg);
        

        for (long long int i = 0; i < neg.size(); i++){
            cntr[i] = -1*neg[neg.size() - 1 - i];}

        for (long long int j = neg.size(); j < size(cntr); j++){
            cntr[j] = pos[j - neg.size()];}
            }
}

int main(){

    vector<long long int> arr;
    long long int n = 1000000;

    for (long long int i = n; i > 0; i--){
        arr.push_back(i);
    }

    vector<long long int> arr2;

    for (long long int i = n; i > 0; i--)
    {
        arr2.push_back(i);
    }

    bucketSort<long long int>(arr);
    // insertionSort<long long int>(arr2);

    for (long long int i = 0; i < n; i++){
        cout << arr[i] << "\n";
        if (arr[i] > arr[i+1]){
            cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
            i = n;
        }
    }

return 0;
}