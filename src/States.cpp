#include "States.h"

States::States(double p, int dealerCard)
{
    this->probability = p;
    this->dealerCard = dealerCard;
    for (int i = 5; i <= 19; ++i)
        states.push_back(State(i, false, true));
    for (int i = 13; i <= 20; ++i)
        states.push_back(State(i, true, true));
    for (int i = 2; i <= 10; ++i)
        states.push_back(State(i * 2, false, true, true));
    states.push_back(State(12, true, true, true));
    states.push_back(State(21, true, true, false, true));
    for (int i = 6; i <= 21; ++i)
        states.push_back(State(i, false, false));
    for (int i = 13; i <= 21; ++i)
        states.push_back(State(i, true, false));
    states.push_back(State(22, false, false, false, false, -1));
    states.push_back(State(21, false, false, false, false, 1));
    states.push_back(State(22, false, false, false, false, 1.5));
    states.push_back(State(22, false, false, false, false, -2));
    states.push_back(State(21, false, false, false, false, 2));
    states.push_back(State(22, false, false, false, false, 3));
}
double States::calculateUtility(State &state, int dealerValue, bool doubleValue =false , double prob = 1, bool isA = false)
{
    for (int i = 1; i <= 10; ++i)
    {
        double p = i == 10 ? probability : (1 - probability) / 9;
        dealerValue += i;
        if (dealerValue >= 17 || ((isA | (i == 1)) && dealerValue + 10 >= 17 && dealerValue + 10 <= 21))
        {
            if (dealerValue > 21)
                state.addNextState(&states[59+doubleValue*3], 'S', prob * p);
            else
            {
                if (((dealerCard == 1 && i == 10) || (dealerCard == 10 && i == 1)) && !state.isBlackjack())
                    state.addNextState(&states[59+doubleValue*3], 'S', prob * p);
                else if (!(dealerCard == 1 && i == 10) && !(dealerCard == 10 && i == 1) && state.isBlackjack())
                    state.addNextState(&states[61+doubleValue*3], 'S', prob * p);
                else
                {
                    if (dealerValue >= 17 && dealerValue > state.getHandValue())
                        state.addNextState(&states[59+doubleValue*3], 'S', prob * p);
                    else if (dealerValue >= 17 && dealerValue < state.getHandValue())
                        state.addNextState(&states[60+doubleValue*3], 'S', prob * p);
                    else if (dealerValue < 17 && dealerValue + 10 > state.getHandValue())
                        state.addNextState(&states[59+doubleValue*3], 'S', prob * p);
                    else if (dealerValue < 17 && dealerValue + 10 < state.getHandValue())
                        state.addNextState(&states[60+doubleValue*3], 'S', prob * p);
                }
            }
        }

        else
            calculateUtility(state, dealerValue,doubleValue, p * prob, isA | (i == 1));
        dealerValue -= i;
    }
}
void States::assignNextStates(char action, State &state)
{
    switch (action)
    {
    case 'H':
        for (int i = 1; i <= 10; ++i)
        {
            double prob = i == 10 ? probability : (1 - probability) / 9;
            if (state.getHandValue() + i <= 21 || (state.hasA() && state.getHandValue() + i <= 31))
            {
                if ((state.getHandValue() < 11 && i == 1))
                    state.addNextState(&states[48 + state.getHandValue()], 'H', prob);
                else if (state.hasA() && state.getHandValue() + i > 21)
                    state.addNextState(&states[18 + state.getHandValue() + i], 'H', prob);
                else if (state.hasA() && state.getHandValue() + i <= 21)
                    state.addNextState(&states[37 + state.getHandValue() + i], 'H', prob);
                else
                    state.addNextState(&states[28 + state.getHandValue() + i], 'H', prob);
            }
            else
                state.addNextState(&states[59], 'H', prob);
        }
        break;
    case 'P':
        if (state.isPair())
        {
        }
        break;
    case 'D':
        if (!state.onlyTwoCards()){
            
        }
        break;
    case 'S':
        calculateUtility(state, dealerCard);
        break;
    }
}
void States::assignNextStates()
{
    for (int i = 0; i < 59; ++i)
    {
        assignNextStates('H', states[i]);
        assignNextStates('S', states[i]);
        assignNextStates('D', states[i]);
        assignNextStates('P', states[i]);
    }
    // for (int i = 15; i < 23; ++i)
    // {
    //     findNextStates('H', states[i]);
    //     findNextStates('S', states[i]);
    //     findNextStates('D', states[i]);
    // }
    // for (int i = 23; i < 32; ++i)
    // {
    //     findNextStates('H', states[i]);
    //     findNextStates('S', states[i]);
    //     findNextStates('D', states[i]);
    //     findNextStates('P', states[i]);
    // }
    // findNextStates('H', states[32]);
    // findNextStates('P', states[32]);
    // findNextStates('S', states[32]);
    // findNextStates('D', states[32]);
    // findNextStates('H', states[33]);
    // findNextStates('P', states[33]);
    // findNextStates('S', states[33]);
    // findNextStates('D', states[33]);
    // for (int i = 34; i < 50; ++i)
    // {
    //     findNextStates('H', states[i]);
    //     findNextStates('S', states[i]);
    // }
    // for (int i = 50; i < 59; ++i)
    // {
    //     findNextStates('H', states[i]);
    //     findNextStates('S', states[i]);
    // }
}