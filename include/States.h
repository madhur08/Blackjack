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
  State &getState(int);
  void assignNextStates();
  void assignNextStates(char, State &);
  void valueIteration();
  double calculateUtility(State &, State &, int, bool, bool doubleValue, double prob, char action, int cardNumber);
};

#endif