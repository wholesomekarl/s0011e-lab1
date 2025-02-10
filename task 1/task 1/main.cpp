#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

#include "Character.h"
#include "States.h"

//characters array
std::vector<std::unique_ptr<Character>> characters;

//game-loop
void gameLoop(std::vector<std::unique_ptr<Character>>& characters) {
    int tick = 0;

    while (true) {
        std::cout << "\n=== tick: " << tick << " ===\n";

        // Each character processes messages, checks status, and decides on transitions
        for (auto& character : characters) {
            character->checkMessages();
            character->printStatus();

            

            //transition logic
            if (character->getHunger() >= 80) {
                //if hunger is critical, and you have enough money, buy food, else keep working
                if (character->getMoney() >= 20) {
                    character->changeState(std::make_unique<BuyState>());
                }
                else {
                    std::cout << character->getName() << ": Im hungry, but too poor! \n";
                    if (tick % 2 == 0) {
                        character->changeState(std::make_unique<WorkState>("office", rand() % 20 + 1, rand() % 25 + 1, rand() % 20 + 1));
                    }
                    else {
                        character->changeState(std::make_unique<WorkState>("farm", rand() % 20 + 1, rand() % 25 + 1, rand() % 20 + 1));
                    }

                }
                
            }
            else if (character->getEnergy() <= 10) {
                //if energy is too low, sleep
                character->changeState(std::make_unique<SleepState>());
            }
            else if (character->getSocialNeed() >= 70) {
                //if social need is high, socialize
                character->sendMessage(characters, "let's hang out!");
                character->changeState(std::make_unique<SocializeState>());
            }
            else if (character->getCanHangOut()) {
                //if we got an invite, let's hang out
                character->changeState(std::make_unique<SocializeState>());
                character->setCanHangOut(false);
            }
            else {
                //else do work at office or farm
                if (tick % 2 == 0) {
                    character->changeState(std::make_unique<WorkState>("office", rand() % 20 + 1, rand() % 25 + 1, rand() % 20 + 1));
                }
                else {
                    character->changeState(std::make_unique<WorkState>("farm", rand() % 20 + 1, rand() % 25 + 1, rand() % 20 + 1));
                }
            }

            // Execute the current state
            character->update();
        }

        // Wait a bit so we can observe the simulation
        std::this_thread::sleep_for(std::chrono::seconds(1));
        ++tick;

        // End after 15 ticks
        if (tick >= 50) {
            std::cout << "game over after 15 ticks.\n";
            break;
        }
    }
}

int main() {
    // Seed the random generator
    srand(static_cast<unsigned>(time(nullptr)));

    // Create characters
    characters.push_back(std::make_unique<Character>("john"));
    characters.push_back(std::make_unique<Character>("alice"));
    characters.push_back(std::make_unique<Character>("karl"));

    // Start the simulation
    gameLoop(characters);

    return 0;
}
