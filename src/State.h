#ifndef STATE_H
#define STATE_H
#include <vector>
using std::vector;

class state
{
    vector<vector<uint8_t>> cards;
    state() = delete;
    state(vector<vector<uint8_t>> &);
};
#endif