#include "State.h"
#include <iostream>
State::State(int handValue, bool ACard, bool twoCards, bool pair, bool blackjack, double utility)
{
    this->handValue = handValue;
    this->ACard = ACard;
    this->twoCards = twoCards;
    this->pair = pair;
    this->blackjack = blackjack;
    utilityD = utilityH = utilityP = utilityS = 0;
    this->utility = utility;
}
char State::getAction()
{
    return action;
}
void State::setAction(char action)
{
    this->action = action;
}
int State::getHandValue()
{
    return handValue;
}
void State::setHandValue(int value)
{
    handValue = value;
}
void State::setUtility(double utility, char action)
{
    switch (action)
    {
    case 'H':
        this->utilityH = utility;
        break;
    case 'D':
        this->utilityD = utility;
        break;
    case 'S':
        this->utilityS = utility;
        break;
    case 'P':
        this->utilityP = utility;
        break;
    default:
        this->utility = utility;
        break;
    }
}
bool State::hasA()
{
    return ACard;
}
bool State::isBlackjack()
{
    return blackjack;
}
bool State::isPair()
{
    return pair;
}
bool State::onlyTwoCards()
{
    return twoCards;
}
void State::addNextState(State *state, char action, double p)
{
    switch (action)
    {
    case 'H':
        nextStateH.push_back(state);
        probabilityH.push_back(p);
        break;
    case 'D':
        nextStateD.push_back(state);
        probabilityD.push_back(p);
        break;
    case 'S':
        nextStateS.push_back(state);
        probabilityS.push_back(p);
        break;
    case 'P':
        nextStateP.push_back(state);
        probabilityP.push_back(p);
        break;
    }
}
vector<State *> &State::getNextState(char action)
{
    static vector<State *> DEFAULT;
    switch (action)
    {
    case 'H':
        return nextStateH;
    case 'D':
        return nextStateD;
    case 'S':
        return nextStateS;
    case 'P':
        return nextStateP;
    default:
        std::cerr << "Incorrect action\n";
        return DEFAULT;
    }
}
vector<double> &State::getProbability(char action)
{
    static vector<double> DEFAULT;
    switch (action)
    {
    case 'H':
        return probabilityH;
    case 'D':
        return probabilityD;
    case 'S':
        return probabilityS;
    case 'P':
        return probabilityP;
    default:
        std::cerr << "Incorrect action\n";
        return DEFAULT;
    }
}
double State::getUtility(char action)
{
    switch (action)
    {
    case 'H':
        return utilityH;
    case 'D':
        return utilityD;
    case 'S':
        return utilityS;
    case 'P':
        return utilityP;
    default:
        return utility;
    }
}