#ifndef STATES_H
#define STATES_H
#include "State.h"

class States
{
  private:
    vector<State> states;
    int dealerCard;
    double probability;
    States(double, int);
    void assignNextStates();
    void assignNextStates(char, State&);
    void valueIteration();
    double calculateUtility(State&,int,bool doubleValue, double prob, bool isA);
};

#endif