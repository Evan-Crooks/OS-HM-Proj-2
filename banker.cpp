//banker

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    ifstream infile("input.txt");
    if (!infile) {
        cerr << "Cannot open input.txt" << endl;
        return 1;
    }

    int n, m; // number of processes and resource types
    infile >> n >> m;

    vector<int> total_resources(m);
    for (int i = 0; i < m; ++i) {
        infile >> total_resources[i];
    }
    
    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> max(n, vector<int>(m));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            infile >> allocation[i][j];

    cout << endl;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            infile >> max[i][j];

    infile.close();

    vector<int> available(m);
    for (int j = 0; j < m; ++j) {
        int sum = 0;
        for (int i = 0; i < n; ++i)
            sum += allocation[i][j];
        available[j] = total_resources[j] - sum;
    }

    vector<vector<int>> need(n, vector<int>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            need[i][j] = max[i][j] - allocation[i][j];
    

    vector<bool> finish(n, false);
    vector<int> safeSequence;

    for (int count = 0; count < n; ++count) {
        bool found = false;
        for (int p = 0; p < n; ++p) {
            if (!finish[p]) {
                bool canAllocate = true;
                for (int j = 0; j < m; ++j) {
                    if (need[p][j] > available[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < m; ++j)
                        available[j] += allocation[p][j];
                    safeSequence.push_back(p);
                    finish[p] = true;
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            cout << "System is NOT in a safe state." << endl;
            return 0;
        }
    }

    cout << "System is in a SAFE state.\nSafe sequence is: ";
    for (int i = 0; i < safeSequence.size(); ++i) {
        cout << "P" << safeSequence[i];
        if (i != safeSequence.size() - 1) cout << " -> ";
    }
    cout << endl;

    return 0;
}
