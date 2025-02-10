#pragma once
#ifndef STATE_H
#define STATE_H

// forward declaration
class Character;

// base class for all states
class State {
public:
    virtual ~State() {}
    virtual void enter(Character& character) = 0;
    virtual void execute(Character& character) = 0;
    virtual void exit(Character& character) = 0;
};

#endif


