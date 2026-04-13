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

const int WIDTH = 10;

struct Time {
    int vect, list, set;
};

int main() {
    Time read, sort1, ins, del;
    ifstream fin("codes.txt");
    vector<string> vec;
    list<string> list;
    set<string> set;
    string temp;

    //READING FILE
    auto start = high_resolution_clock::now();
    while (fin >> temp) {
        vec.push_back(temp);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);
    read.vect = duration.count();

    start = high_resolution_clock::now();
    while (fin >> temp) {
        list.push_back(temp);
    }
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);
    read.list = duration.count();
    
    start = high_resolution_clock::now();
    while (fin >> temp) {
        set.insert(temp);
    }
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);
    read.set = duration.count();

    fin.close();

    //SORTING FILE
    start = high_resolution_clock::now();
    sort(vec.begin(), vec.end());
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);
    sort1.vect = duration.count();

    start = high_resolution_clock::now();
    list.sort();
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);
    sort1.list = duration.count();

    sort1.set = -1;


    //INSERTING
    string t = "TESTCODE";

    start = high_resolution_clock::now();
    vec.insert(vec.begin() + (vec.size() / 2), t);
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);
    ins.vect = duration.count();;
    
    start = high_resolution_clock::now();
    auto it = list.begin();
    advance(it, (list.size() / 2));
    list.insert(it, t);
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);
    ins.list= duration.count();

    start = high_resolution_clock::now();
    set.insert(t);
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);
    ins.set = duration.count();

    //DELETING
    start = high_resolution_clock::now();
    vec.erase(vec.begin() + (vec.size() / 2));
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);
    del.vect = duration.count();


    start = high_resolution_clock::now();
    it = list.begin();
    advance(it, (list.size() / 2));
    list.erase(it);
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);
    del.list = duration.count();

    start = high_resolution_clock::now();
    auto it2 = set.begin();
    advance(it2, (set.size() / 2));
    set.erase(it2);
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);
    del.set = duration.count();

    cout << "**** DATA STRUCTURE RACE RESULTS ****" << endl;
    cout << setw(WIDTH) << "Operation";
    cout << setw(WIDTH) << "Vector";
    cout << setw(WIDTH) << "List";
    cout << setw(WIDTH) << "Set" << endl;

    cout << setw(WIDTH) << "Read";
    cout << setw(WIDTH) << read.vect;
    cout << setw(WIDTH) << read.list;
    cout << setw(WIDTH) << read.set << endl;

    cout << setw(WIDTH) << "Sort";
    cout << setw(WIDTH) << sort1.vect;
    cout << setw(WIDTH) << sort1.list;
    cout << setw(WIDTH) << sort1.set << endl;

    cout << setw(WIDTH) << "Delete";
    cout << setw(WIDTH) << del.vect;
    cout << setw(WIDTH) << del.list;
    cout << setw(WIDTH) << del.set;

    return 0;
}