#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <iomanip>
using namespace std;
using namespace std::chrono;

const int WIDTH = 10, TESTS = 4, CONTAINER_TYPES = 3, SIMS = 15;

struct Times {
    int read, sort, ins, del;
};

int main() {
    int times[CONTAINER_TYPES][TESTS][SIMS];
    ifstream fin("codes.txt");
    vector<string> vec;
    list<string> list;
    set<string> set;
    string temp;

    //READING FILE
    auto start = high_resolution_clock::now();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);
    auto it = list.begin();
    auto it2 = set.begin();


    for (int i = 0; i < 15; i++) {
        //READING FILE
        start = high_resolution_clock::now();                   //vector read
        while (fin >> temp) {
            vec.push_back(temp);
        }
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        times[0][0][i] = duration.count();

        start = high_resolution_clock::now();                   // list read
        while (fin >> temp) {
            list.push_back(temp);
        }
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        times[1][0][i] = duration.count();

        start = high_resolution_clock::now();                   // set read
        while (fin >> temp) {
            set.insert(temp);
        }
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        times[2][0][i] = duration.count();

        //SORTING FILE
        start = high_resolution_clock::now();                   // vector sort
        sort(vec.begin(), vec.end());
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        times[0][1][i] = duration.count();

        start = high_resolution_clock::now();                   // list sort
        list.sort();
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        times[1][1][i] = duration.count();

        times[2][1][i] = 0;                                    // set "sort"

        //INSERTING
        string t = "TESTCODE";

        start = high_resolution_clock::now();                   // vector insert
        vec.insert(vec.begin() + (vec.size() / 2), t);
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        times[0][2][i] = duration.count();;
        
        start = high_resolution_clock::now();                   // list insert
        it = list.begin();
        advance(it, (list.size() / 2));
        list.insert(it, t);
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        times[1][2][i] = duration.count();

        start = high_resolution_clock::now();                   // set insert
        set.insert(t);
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        times[2][2][i] = duration.count();

        //DELETING
        start = high_resolution_clock::now();                   // vector delete
        vec.erase(vec.begin() + (vec.size() / 2));
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        times[0][3][i] = duration.count();

        start = high_resolution_clock::now();                   // list delete
        it = list.begin();
        advance(it, (list.size() / 2));
        list.erase(it);
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        times[1][3][i] = duration.count();

        start = high_resolution_clock::now();                   // set delete
        it2 = set.begin();
        advance(it2, (set.size() / 2));
        set.erase(it2);
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        times[2][3][i] = duration.count();
    }
    fin.close();    // close file

    //CALCULATE AVERAGES
    Times sumVec, sumList, sumSet;

    for(int i = 0; i < 4; i++) {
        for (int j = 0; j < 15; j++) {
            if (i == 0) { sumVec.read += times[0][i][j]; }
            if (i == 1) { sumVec.sort += times[0][i][j]; }
            if (i == 2) { sumVec.ins += times[0][i][j]; }
            if (i == 0) { sumVec.del += times[0][i][j]; }
        }
    }
    for(int i = 0; i < 4; i++) {
        for (int j = 0; j < 15; j++) {
            if (i == 0) { sumList.read += times[1][i][j]; }
            if (i == 1) { sumList.sort += times[1][i][j]; }
            if (i == 2) { sumList.ins += times[1][i][j]; }
            if (i == 0) { sumList.del += times[1][i][j]; }
        }
    }
    for(int i = 0; i < 4; i++) {
        for (int j = 0; j < 15; j++) {
            if (i == 0) { sumSet.read += times[2][i][j]; }
            if (i == 1) { sumSet.sort += times[2][i][j]; }
            if (i == 2) { sumSet.ins += times[2][i][j]; }
            if (i == 0) { sumSet.del += times[2][i][j]; }
        }
    }
    

    // PRINT
    cout << "Number of simulations: " << SIMS << endl;
    cout << setw(WIDTH) << "Operation";
    cout << setw(WIDTH) << "Vector";
    cout << setw(WIDTH) << "List";
    cout << setw(WIDTH) << "Set" << endl;

    cout << setw(WIDTH) << "Read";
    cout << setw(WIDTH) << sumVec.read / SIMS;
    cout << setw(WIDTH) << sumList.read / SIMS;
    cout << setw(WIDTH) << sumSet.read / SIMS << endl;

    cout << setw(WIDTH) << "Sort";
    cout << setw(WIDTH) << sumVec.sort / SIMS;
    cout << setw(WIDTH) << sumList.sort / SIMS;
    cout << setw(WIDTH) << sumSet.sort / SIMS << endl;

    cout << setw(WIDTH) << "Insert";
    cout << setw(WIDTH) << sumVec.ins / SIMS;
    cout << setw(WIDTH) << sumList.ins / SIMS;
    cout << setw(WIDTH) << sumSet.ins / SIMS << endl;

    cout << setw(WIDTH) << "Delete";
    cout << setw(WIDTH) << sumVec.del / SIMS;
    cout << setw(WIDTH) << sumList.del / SIMS;
    cout << setw(WIDTH) << sumSet.del / SIMS;

    return 0;
}