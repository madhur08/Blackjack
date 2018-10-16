#ifndef STATES_H
#define STATES_H
#include "State.h"

class States
{
private:
  vector<State> states;
  int dealerCard;
  double probability;
public:
  States(double, int);
  State &getState(int);
  void assignNextStates();
  void assignNextStates(char, State &);
  void valueIteration();
  void calculateUtility(State &, State &, int, bool, bool doubleValue = false, double prob = 1, char action = 'S', int cardNumber = 2);
};

#endif