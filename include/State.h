#ifndef STATE_H
#define STATE_H
#include <vector>
using std::vector;

class State
{
  private:
    int handValue;
    double utility, utilityH, utilityP, utilityS, utilityD;
    char action;
    bool ACard;
    bool twoCards;
    bool pair;
    bool blackjack;
    vector<State*> nextStateH, nextStateP, nextStateS, nextStateD;
    vector<double> probabilityH, probabilityP, probabilityS, probabilityD;
  public:
    State() = delete;
    State(int, bool, bool, bool pair, bool blackjack, double utility);
    char getAction();
    int getHandValue();
    void setHandValue(int);
    void setUtility(double,char);
    bool hasA();
    bool isBlackjack();
    bool isPair();
    bool onlyTwoCards();
    void addNextState(State*, char, double);
};
#endif