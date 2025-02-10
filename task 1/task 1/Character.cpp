#include "Character.h"
#include <iostream>
#include <typeinfo>

Character::Character(const std::string& charName)
    : name(charName),
    currentState(nullptr),
    hunger(50), energy(50), money(0), socialNeed(50),
    canHangOutFlag(false) {}

void Character::changeState(std::unique_ptr<State> newState) {
    // prevent entering the same state type
    if (currentState && typeid(*currentState) == typeid(*newState)) {
        return;
    }
    // exit old state
    if (currentState) {
        currentState->exit(*this);
    }
    // enter new state
    currentState = std::move(newState);
    currentState->enter(*this);
}

void Character::update() {
    if (currentState) {
        currentState->execute(*this);
    }
}

// getter methods
int Character::getHunger() const { return hunger; }
int Character::getEnergy() const { return energy; }
int Character::getMoney() const { return money; }
int Character::getSocialNeed() const { return socialNeed; }

bool Character::getCanHangOut() const {
    return canHangOutFlag;
}
void Character::setCanHangOut(bool canHang) {
    canHangOutFlag = canHang;
}

// modifiers
void Character::increaseHunger(int value) { hunger += value; }
void Character::decreaseHunger(int value) { hunger -= value; }
void Character::increaseEnergy(int value) { energy += value; }
void Character::decreaseEnergy(int value) { energy -= value; }
void Character::increaseMoney(int value) { money += value; }
void Character::decreaseMoney(int value) { money -= value; }
void Character::increaseSocialNeed(int value) { socialNeed += value; }
void Character::decreaseSocialNeed(int value) { socialNeed -= value; }

const std::string& Character::getName() const {
    return name;
}

// message
void Character::sendMessage(std::vector<std::unique_ptr<Character>>& characters, const std::string& content) {
    for (auto& receiver : characters) {
        if (receiver->getName() != name) {
            receiver->inbox.push({ name, receiver->getName(), content });
            receiver->setCanHangOut(true);
            //std::cout << receiver->getName() << " : recived a message\n";
        }
    }
}

void Character::checkMessages() {
    while (!inbox.empty()) {
        Message msg = inbox.front();
        inbox.pop();
        std::cout <<"\033[32m" << "[message] " << msg.sender << " to " << msg.receiver
            << ": " << msg.content << "\033[32m" << "\n";
    }
}

// debug
void Character::printStatus() const {
    std::cout << "\033[34m" << "[" << name << " status] "
        << "hunger: " << hunger
        << ", energy: " << energy
        << ", money: " << money
        << ", social need: " << socialNeed
        << "\033[34m" << "\n";
}

