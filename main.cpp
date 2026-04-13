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

        times[2][1][i] = -1;                                    // set "sort"

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

    cout << "**** DATA STRUCTURE RACE RESULTS ****" << endl;
    cout << setw(WIDTH) << "Operation";
    cout << setw(WIDTH) << "Vector";
    cout << setw(WIDTH) << "List";
    cout << setw(WIDTH) << "Set" << endl;

    cout << setw(WIDTH) << "Read";
    cout << setw(WIDTH) << times[0][0][0];
    cout << setw(WIDTH) << times[0][0][0];
    cout << setw(WIDTH) << times[0][0][0] << endl;

    cout << setw(WIDTH) << "Sort";
    cout << setw(WIDTH) << times[0][0][0];
    cout << setw(WIDTH) << times[0][0][0];
    cout << setw(WIDTH) << times[0][0][0] << endl;

    cout << setw(WIDTH) << "Delete";
    cout << setw(WIDTH) << times[0][0][0];
    cout << setw(WIDTH) << times[0][0][0];
    cout << setw(WIDTH) << times[0][0][0];

    return 0;
}