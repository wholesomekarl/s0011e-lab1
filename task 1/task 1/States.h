#pragma once
#ifndef STATES_H
#define STATES_H

#include "State.h"
#include <string>

// forward-declare Character
class Character;

//work State
class WorkState : public State {
private:
    std::string workType;
    int moneyEarned;
    int energyUsed;
    int hungerIncrease;

public:
    WorkState(const std::string& type, int money, int energy, int hunger);
    void enter(Character& character) override;
    void execute(Character& character) override;
    void exit(Character& character) override;
};

//buy State
class BuyState : public State {
public:
    void enter(Character& character) override;
    void execute(Character& character) override;
    void exit(Character& character) override;
};

//socialize State
class SocializeState : public State {
public:
    void enter(Character& character) override;
    void execute(Character& character) override;
    void exit(Character& character) override;
};

//sleep State
class SleepState : public State {
public:
    void enter(Character& character) override;
    void execute(Character& character) override;
    void exit(Character& character) override;
};

#endif


