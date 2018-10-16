#include "States.h"
#include <cmath>
#include <iostream>
#define EPSILON 0.000001
using namespace std;
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
    states.push_back(State(22, false, false, false, false, -1));  //59
    states.push_back(State(22, false, false, false, false, 1));   //60
    states.push_back(State(22, false, false, false, false, 1.5)); //61
    states.push_back(State(22, false, false, false, false, -2));  //59 + 3 = 62
    states.push_back(State(22, false, false, false, false, 2));   //60 + 3 = 63
    states.push_back(State(22, false, false, false, false, 3));   //61 + 3 = 64
}
State &States::getState(size_t i)
{
    return states[i];
}
void States::calculateUtility(State &state, State &compareState, int dealer, bool isA, bool doubleValue, double prob, char action, int cardNumber)
{
    for (int i = 1; i <= 10; ++i)
    {
        double p = i == 10 ? probability : (1 - probability) / 9;
        int dealerValue = dealer + i;
        if ((isA | (i == 1)) && dealerValue <= 11)
            dealerValue += 10;
        if (dealerValue >= 17)
        {
            if (dealerValue > 21)
            {
                if (compareState.isBlackjack())
                    state.addNextState(&states[61 + doubleValue * 3], action, prob * p);
                else
                    state.addNextState(&states[60 + doubleValue * 3], action, prob * p);
            }
            else
            {
                if (!compareState.isBlackjack() && ((dealerCard == 1 && i == 10) || (dealerCard == 10 && i == 1)) && cardNumber == 2)
                    state.addNextState(&states[59 + doubleValue * 3], action, prob * p);
                else if (compareState.isBlackjack() && ((!(dealerCard == 1 && i == 10) && !(dealerCard == 10 && i == 1)) || cardNumber > 2))
                    state.addNextState(&states[61 + doubleValue * 3], action, prob * p);
                else
                {
                    if (dealerValue > compareState.getHandValue())
                        state.addNextState(&states[59 + doubleValue * 3], action, prob * p);
                    else if (dealerValue < compareState.getHandValue())
                        state.addNextState(&states[60 + doubleValue * 3], action, prob * p);
                }
            }
        }
        else
            calculateUtility(state, compareState, dealer + i, isA | (i == 1), doubleValue, p * prob, action, cardNumber + 1);
    }
}
void States::assignNextStates(char action, State &state)
{
    switch (action)
    {
    case 'H':
        if (!state.isBlackjack())
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
            if (state.hasA())
            {
                for (int i = 1; i <= 10; ++i)
                    for (int j = 1; j <= 10; ++j)
                    {
                        double prob = i == 10 ? probability : (1 - probability) / 9;
                        prob *= (j == 10 ? probability : (1 - probability) / 9);
                        calculateUtility(state, states[48 + i], dealerCard, dealerCard == 1, false, prob, 'P');
                        calculateUtility(state, states[48 + j], dealerCard, dealerCard == 1, false, prob, 'P');
                    }
            }
            else
            {
                for (int i = 1; i <= 10; ++i)
                    for (int j = 1; j <= 10; ++j)
                    {
                        double prob = i == 10 ? probability : (1 - probability) / 9;
                        prob *= (j == 10 ? probability : (1 - probability) / 9);
                        if (i == 1 && state.getHandValue() == 20)
                            state.addNextState(&states[33], 'P', prob);
                        else if (i == 1)
                            state.addNextState(&states[13 + state.getHandValue() * 0.5], 'P', prob);
                        else if (state.getHandValue() * 0.5 == i)
                            state.addNextState(&states[21 + state.getHandValue() * 0.5], 'P', prob);
                        else
                            state.addNextState(&states[state.getHandValue() * 0.5 + i - 5], 'P', prob);
                        if (j == 1 && state.getHandValue() == 20)
                            state.addNextState(&states[33], 'P', prob);
                        else if (j == 1)
                            state.addNextState(&states[13 + state.getHandValue() * 0.5], 'P', prob);
                        else if (state.getHandValue() * 0.5 == j)
                            state.addNextState(&states[21 + state.getHandValue() * 0.5], 'P', prob);
                        else
                            state.addNextState(&states[state.getHandValue() * 0.5 + j - 5], 'P', prob);
                    }
            }
        }
        break;
    case 'D':
        if (state.onlyTwoCards())
        {
            for (int i = 1; i <= 10; ++i)
            {
                double prob = i == 10 ? probability : (1 - probability) / 9;
                if (state.getHandValue() + i <= 21 || (state.hasA() && state.getHandValue() + i <= 31))
                {
                    if ((state.getHandValue() < 11 && i == 1))
                        calculateUtility(state, states[48 + state.getHandValue()], dealerCard, dealerCard == 1, true, prob, 'D');
                    else if (state.hasA() && state.getHandValue() + i > 21)
                        calculateUtility(state, states[18 + state.getHandValue() + i], dealerCard, dealerCard == 1, true, prob, 'D');
                    else if (state.hasA() && state.getHandValue() + i <= 21)
                        calculateUtility(state, states[37 + state.getHandValue() + i], dealerCard, dealerCard == 1, true, prob, 'D');
                    else
                        calculateUtility(state, states[28 + state.getHandValue() + i], dealerCard, dealerCard == 1, true, prob, 'D');
                }
                else
                    state.addNextState(&states[62], 'D', prob);
            }
        }
        break;
    case 'S':
        calculateUtility(state, state, dealerCard, dealerCard == 1);
        break;
    }
}
void States::valueIteration()
{
    while (true)
    {
        for (auto &state : states)
        {
            //For action H
            vector<State *> &nextStateH = state.getNextState('H');
            if (nextStateH.size() != 0)
            {
                double utilityH = 0;
                vector<double> &stateProbH = state.getProbability('H');
                for (size_t i = 0; i != nextStateH.size(); ++i)
                    utilityH += stateProbH[i] * nextStateH[i]->getUtility();
                state.setUtility(utilityH, 'H');
            }

            //For action S
            vector<State *> &nextStateS = state.getNextState('S');
            if (nextStateS.size() != 0)
            {
                double utilityS = 0;
                vector<double> &stateProbS = state.getProbability('S');
                for (size_t i = 0; i != nextStateS.size(); ++i)
                    utilityS += stateProbS[i] * nextStateS[i]->getUtility();
                state.setUtility(utilityS, 'S');
            }

            //For action D
            vector<State *> &nextStateD = state.getNextState('D');
            if (nextStateD.size() != 0)
            {
                double utilityD = 0;
                vector<double> &stateProbD = state.getProbability('D');
                for (size_t i = 0; i != nextStateD.size(); ++i)
                    utilityD += stateProbD[i] * nextStateD[i]->getUtility();
                state.setUtility(utilityD, 'D');
            }

            //For action P
            vector<State *> &nextStateP = state.getNextState('P');
            if (nextStateP.size() != 0)
            {
                double utilityP = 0;
                vector<double> &stateProbP = state.getProbability('P');
                for (size_t i = 0; i != nextStateP.size(); ++i)
                    utilityP += stateProbP[i] * nextStateP[i]->getUtility();
                state.setUtility(utilityP, 'P');
            }
        }
        double maxChange = -100;
        for (auto &state : states)
        {
            double max = -100;
            //For action H
            if (max < state.getUtility('H'))
            {
                state.setAction('H');
                max = state.getUtility('H');
            }

            //For action S
            if (max < state.getUtility('S'))
            {
                state.setAction('S');
                max = state.getUtility('S');
            }

            //For action D
            if (max < state.getUtility('D'))
            {
                state.setAction('D');
                max = state.getUtility('D');
            }

            //For action P
            if (max < state.getUtility('P'))
            {
                state.setAction('P');
                max = state.getUtility('P');
            }
            double change = fabs(state.getUtility() - max);
            if (change > maxChange)
                maxChange = change;
            state.setUtility(max);
        }
        if (maxChange < EPSILON)
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
}