//*****************************************************************************
// COMSC-210 | Lab 13 | Gabriel Marquez
// Description: this program exercises a variety of std::vector functions by
// tracking 10 kilometer run times over a span of 35 days. Modified version of
// Lab 12 code such that it uses the STD::vector rather than the STD::array.
//*****************************************************************************

#include <iostream>
#include <algorithm>  // for sort(), find()
#include <numeric>    // for accumulate()
#include <vector>
#include <fstream>
using namespace std;

const int SIZE = 35;
const int DAYS = 7;
const int WEEKS = 5;

void displayTimes(const vector<double> &);
void displayTimes(const vector<vector<double>> &);
void findTime(vector<double> &, double);
void populateVector(vector<double> &, const vector<double> &);

int main() {
    //declare std::vector of size SIZE
    //via reading data from a file, use .size() to
    //loop through the vector and .at(i) to
    //populate each element and confirming with .empty()
    cout << "Populating runTimes vector..." << endl;
    vector<double> runTimes(SIZE);
    ifstream fin("run_times.txt");
    if (fin.good()) {
        for (int i = 0; i < runTimes.size(); ++i) {
            fin >> runTimes.at(i);
        }
        fin.close();
    }
    else {
        cout << "ERROR! Please verify file name/directory and restart program.";
        return 1;
    }
    if (!runTimes.empty())
        cout << "Complete!" << endl;

    //display elements in runTimes with a function
    cout << "10 kilometer run times (in minutes) from the past 35 days:" << endl;
    displayTimes(runTimes);

    //using a 2D vector to group times by week
    //creating arrays for each week first
    vector<double> week1(DAYS);
    populateVector(week1, runTimes);
    vector<double> week2(DAYS);
    populateVector(week2, runTimes);
    vector<double> week3(DAYS);
    populateVector(week3, runTimes);
    vector<double> week4(DAYS);
    populateVector(week4, runTimes);
    vector<double> week5(DAYS);
    populateVector(week5, runTimes);

    //create and populate 2D array using week arrays
    vector<vector<double>> weeklyRunTimes = {week1, week2, week3,
                                             week4, week5};
    displayTimes(weeklyRunTimes);

    //accessing individual run times with .front(), .back(), and .at()
    cout << "Oldest run time: " <<  runTimes.front() << " minutes" << endl;
    cout << "Most recent run time: " << runTimes.back() << " minutes" << endl;
    cout << "Run time on day #10: " << runTimes.at(9) << " minutes" << endl << endl;

    //using iterators to sort and reverse runTimes
    sort(runTimes.begin(), runTimes.end());
    cout << "Run times sorted from fastest to slowest:" << endl;
    displayTimes(runTimes);
    sort(runTimes.rbegin(), runTimes.rend());
    cout << "Run times sorted from slowest to fastest:" << endl;
    displayTimes(runTimes);

    //using an iterator in a function to find a specific run time
    double time1 = 100.34;
    findTime(runTimes, time1);
    double time2 = 64.55;
    findTime(runTimes, time2);

    //finding the slowest, fastest, and sum of all run times
    cout << "Slowest run time: "
         << *max_element(runTimes.begin(), runTimes.end()) << " minutes" << endl; 
    cout << "Fastest run time: "
         << *min_element(runTimes.begin(), runTimes.end()) << " minutes" << endl;
    cout << "Total minutes run over the last " << runTimes.size() << " days: ";
    cout << accumulate(runTimes.begin(), runTimes.end(), 0.0) << " minutes" << endl;
    cout << endl;

    cout << "Summary complete.";
    return 0;
}

// displayTimes() takes an std::vector by constant reference and
// outputs its members to the console, formatted with a comma separator.
// arguments: an std::vector
// returns: n/a
void displayTimes(const vector<double> &vec) {
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i < vec.size() - 1)
            cout << ", ";
    }
    cout << endl << endl;
}

// displayTimes() takes a 2D std::vector by constant reference and
// outputs its members to the console.
// arguments: a 2D std::vector
// returns: n/a
void displayTimes(const vector<vector<double>> &vec) {
    cout << "Weekly view of run times:" << endl;
    for (int i = 0; i < vec.size(); ++i) {
        cout << "Week " << i+1 << ": ";
        for (int j = 0; j < vec[i].size(); ++j) 
            cout << vec[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

// findTime() takes an std::vector by reference and outputs the
// target's index if found and a "not found" message if not
// note: cannot pass std::vector by constant reference here
// arguments: an std::vector, a target time of type double
// returns: n/a
void findTime(vector<double> &vec, double target) {
    vector<double>::iterator it; //iterator to point to found element
    cout << "Searching for time: " << target << " minutes..." << endl;
    it = find(vec.begin(), vec.end(), target);
    cout << target;
    if (it != vec.end())
        cout << " found in position " << it - vec.begin() << endl;
    else
        cout << " was not found.\n";
    cout << endl;
}

// populateVector() takes an std::vector by reference and populates its members
// using elemens from a second std::vector of passed by constant reference.
// arguments: an std::vector passed by reference, an std::vector passed by
// constant reference
// returns: n/a
void populateVector(vector<double> &to, const vector<double> &from) {
    static int index = 0; //so that index doesn't reset after each function call
    for (int i = 0; i < to.size(); ++i) {
        to.at(i) = from.at(index);
        index++;
    }
}