#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <memory>
#include <queue>
#include <string>
#include <vector>
#include "State.h"
#include "Message.h"

// The Character class holds references to its current state and manages its own data.
class Character {
private:
    std::string name;
    std::unique_ptr<State> currentState;

    int hunger;
    int energy;
    int money;
    int socialNeed;

    bool canHangOutFlag;
    std::queue<Message> inbox;  // Character-specific message queue

public:
    // Constructor
    Character(const std::string& charName);

    // State machine methods
    void changeState(std::unique_ptr<State> newState);
    void update();

    // Getters
    int getHunger() const;
    int getEnergy() const;
    int getMoney() const;
    int getSocialNeed() const;

    bool getCanHangOut() const;
    void setCanHangOut(bool canHang);

    // Attribute modifiers
    void increaseHunger(int value);
    void decreaseHunger(int value);
    void increaseEnergy(int value);
    void decreaseEnergy(int value);
    void increaseMoney(int value);
    void decreaseMoney(int value);
    void increaseSocialNeed(int value);
    void decreaseSocialNeed(int value);

    // Basic info
    const std::string& getName() const;

    // Messaging
    void sendMessage(std::vector<std::unique_ptr<Character>>& characters, const std::string& content);
    void checkMessages();

    // Debug
    void printStatus() const;
};

#endif

