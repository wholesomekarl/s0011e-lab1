#pragma once
#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

// Simple struct for passing messages
struct Message {
    std::string sender;
    std::string receiver;
    std::string content;
};

#endif


