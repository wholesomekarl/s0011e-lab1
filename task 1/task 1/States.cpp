#include "States.h"
#include "Character.h"
#include <iostream>
#include <cstdlib> 

// WorkState 
WorkState::WorkState(const std::string& type, int money, int energy, int hunger)
    : workType(type), moneyEarned(money), energyUsed(energy), hungerIncrease(hunger) {}

void WorkState::enter(Character& character) {
    std::cout << character.getName() << ": 'Lets get some dough!' -> starts working at the " << workType << ".\n";
}

void WorkState::execute(Character& character) {
    std::cout << character.getName() << ": is working at the "
        << workType << ".\n";
    character.increaseMoney(moneyEarned);
    character.decreaseEnergy(energyUsed);
    character.increaseHunger(hungerIncrease);

    //give random value to socialNeed so that the ai's dont want to hang out at the same time
    character.increaseSocialNeed(rand() % 20 + 1);
}

void WorkState::exit(Character& character) {
    std::cout << character.getName() << ": 'Working hard or hardly working?' -> leaves the " << workType << ".\n";
}

//BuyState 
void BuyState::enter(Character& character) {
    std::cout << character.getName() << ": 'Im hungry!' -> goes to the store.\n";
}

void BuyState::execute(Character& character) {
    std::cout << character.getName() << ": buys food and supplies.\n";
    character.decreaseMoney(20);
    character.decreaseHunger(20);  
}

void BuyState::exit(Character& character) {
    std::cout << character.getName() << ": 'Prices these days...' -> leaves the store.\n";
}

//SocializeState
void SocializeState::enter(Character& character) {
    
    std::cout << character.getName() << ": 'Im Bored!' -> starts socializing.\n";
}

void SocializeState::execute(Character& character) {
    std::cout << character.getName() << ": is hanging out with friends.\n";
    character.decreaseSocialNeed(30);
}

void SocializeState::exit(Character& character) {
    std::cout << character.getName() << ": 'I'v got better things to do' ->stops socializing.\n";
}

//SleepState 
void SleepState::enter(Character& character) {
    std::cout << character.getName() << ": 'Ill just close my eyes for one... Zzz...' -> goes to sleep.\n";
}

void SleepState::execute(Character& character) {
    std::cout << character.getName() << ": is sleeping to regain energy.\n";
    character.increaseEnergy(60);
}

void SleepState::exit(Character& character) {
    std::cout << character.getName() << ": 'What day is it!?' -> wakes up feeling rested.\n";
}

