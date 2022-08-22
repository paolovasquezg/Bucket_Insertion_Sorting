#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

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

    long long int sz = size(cntr);
    vector<vector<long long int>> buckets;
    buckets.resize(sz);

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
        insertionSort<T>(buckets[i]); // O(n^2)
    }

    // BC: En cada bucket tenemos un elemento
    //     --> No se ordenada nada --> O(n)
    // AV: Se ordenan algunos buckets, con promedio
    //     de k elementos en cada uno --> O(n*k^2) --> O(n*k)
    // WC: Todos los elementos estan en un solo bucket --> O(n^2)

    long long int index = 0;
    for (long long int i = 0; i < sz; i++) // O(n)
        for (long long int j = 0; j < buckets[i].size(); j++)
            // BC -- AC -- BC --> En todos los casos 
            // realizamos n iteraciones: O(n)
            cntr[index++] = buckets[i][j];
}

// BC: O(n + n + n + n) --> O(n)
// AV: O(n + n + n*k + n*k) --> O(n*k)
// WC: O(n + n + n^2 + n) --> O(n^2)



// Solo para contenedores con indice -->  Ej: Array/Vector
template<typename T, class container>
void bucketSort(container &cntr){

    T max = cntr[0]; T min = cntr[0];

    for (auto itr : cntr){ // O(n)
        if (itr > max) max = itr;
        if (itr < min) min = itr;
    }

    if (min >= 0 && max >= 0){
        bucketExtension<T>(cntr);
        // BC: O(n) ; AV: O(n*k) ; WC: O(n^2)
    }
    else if (min < 0 && max < 0){ vector<T> temp;

        for (auto itr : cntr) temp.push_back(-1*itr);
        bucketExtension<T>(temp);
        // BC: O(n) ; AV: O(n*k) ; WC: O(n^2)

        for (long long int i =0; i < size(cntr); i++){ // 0(n)
            cntr[i] = -1*temp[size(cntr) - 1 - i];
        }
    }
    else{
        vector<T> pos; vector<T> neg;

        for (auto itr: cntr){ // O(n)
            if (itr < 0)
                neg.push_back(-1*itr);
            else
                pos.push_back(itr);
        }
        bucketExtension<T>(pos);
        bucketExtension<T>(neg);
        // BC: O(n) ; AV: O(n*k) ; WC: O(n^2)

        for (long long int i = 0; i < neg.size(); i++){ // O(s)
            cntr[i] = -1*neg[neg.size() - 1 - i];}

        for (long long int j = neg.size(); j < size(cntr); j++){ // O(n-s)
            cntr[j] = pos[j - neg.size()];}
            }
}
// BC: O(n) ; AV: O(n*k) ; WC: O(n^2)

template<typename T>
bool sorted(vector<T> cntr){
    for(int i = 0; i < cntr.size()-1; i++){
        if (cntr[i] > cntr[i+1]){
            return false;
        }
    }
    return true;
}

int main() {
    srand(time(NULL));
    vector<long long int> numbers;
    string filename("insertion_points_continue.txt");
    fstream file_out;

    file_out.open(filename, std::ios_base::out);
    if (!file_out.is_open()) {
        cout << "failed to open " << filename << endl;
    } else {
        for (long long int length = 10000; length <= 300000; length += 10000 ) {
        numbers.resize(0);
        for (long long int j = 0; j < length; j++) {
            numbers.push_back(rand()%(length+1) + 1);
        }

        auto inicio = clock();
        insertionSort<long long int>(numbers);
        auto fin = clock();
        auto time = fin-inicio;
        cout << sorted(numbers) << endl;
        file_out << length << ',' << (float)time/CLOCKS_PER_SEC * 1000 << endl;
        }
    }
    return 0;
}