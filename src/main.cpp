#include <iostream>
#include "States.h"
#include <cstdlib>
using namespace std;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cerr << "Missing arguments\n";
        cerr << "Correct format : ./code <p>";
    }
    else
    {
        vector<vector<char>> output;
        output.resize(33);
        for (int i = 1; i <= 10; ++i)
        {
            States states(atof(argv[1]), i);
            states.assignNextStates();
            states.valueIteration();
            for (size_t v = 0; v != output.size(); ++v)
                output[v].push_back(states.getState(v).getAction());
        }
        for (int i = 0; i < 15; ++i)
        {
            cout << i + 5 << "\t";
            for (int j = 1; j < 10; ++j)
                cout << output[i][j] << " ";
            cout << output[i][0] << endl;
        }
        for (int i = 15; i < 23; ++i)
        {
            cout << 'A' << i - 13 << "\t";
            for (int j = 1; j < 10; ++j)
                cout << output[i][j] << " ";
            cout << output[i][0] << endl;
        }
        for (int i = 23; i < 32; ++i)
        {
            cout << i - 21 << i - 21 << "\t";
            for (int j = 1; j < 10; ++j)
                cout << output[i][j] << " ";
            cout << output[i][0] << endl;
        }
        for (int j = 1; j < 10; ++j)
            cout << output[32][j] << " ";
        cout << output[32][0];
    }
}