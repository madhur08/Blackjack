#include "State.h"

State::State(int handValue, bool ACard, bool twoCards, bool pair = false, bool blackjack = false, double utility = 0)
{
    this->handValue = handValue;
    this->ACard = ACard;
    this->onlyTwoCards = onlyTwoCards;
    this->pair = pair;
    this->blackjack = blackjack;
    utilityD = utilityH = utilityP = utilityS = 0;
    this->utility = utility;
}
char State::getAction(){
    return action;
}
int State::getHandValue(){
    return handValue;
}
void State::setHandValue(int value){
    handValue = value;
}
void State::setUtility(double utility, char action){
    switch(action){
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
    }
}
bool State::hasA(){
    return ACard;
}
bool State::isBlackjack(){
    return blackjack;
}
bool State::isPair(){
    return pair;
}
bool State::onlyTwoCards(){
    return twoCards;
}
void State::addNextState(State* state, char action, double p){
    switch(action){
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