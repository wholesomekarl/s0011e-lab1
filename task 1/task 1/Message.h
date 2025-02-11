#pragma once
#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

// simple struct for passing messages
struct Message {
    std::string sender;
    std::string receiver;
    std::string content;
};

#endif


