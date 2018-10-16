#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "Missing arguments\n";
        cout << "Correct format : ./code <p>";
    }
    else
    {
       States atof(argv[1]);
        
    }
}