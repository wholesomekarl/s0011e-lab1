#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <cstdlib>
#include "Character.h"
#include "States.h"

enum class GameState {
    MENU,
    PLAYING,
    GAMEOVER,
    PAUSED
};

bool playing;

//characters array
std::vector<std::unique_ptr<Character>> characters;

//game-loop
void gameLoop(std::vector<std::unique_ptr<Character>>& characters) {
    int tick;
    GameState state = GameState::MENU;
    while (true) {
        switch (state) {
        case(GameState::MENU):
            std::cout << "----WELCOME TO THIS SIMULATION----\n"
                "This program simulates the life of four AI's\n"
                "Thorugh the lifetime of 20 hours\n\n"
                "Press any key to start\n";
            if (_getch()) {
                state = GameState::PLAYING;
            }

        case(GameState::PLAYING):
            playing = true;
            tick = 0;
            // Create characters
            characters.push_back(std::make_unique<Character>("John"));
            characters.push_back(std::make_unique<Character>("Alice"));
            characters.push_back(std::make_unique<Character>("Karl"));
            characters.push_back(std::make_unique<Character>("Simon"));
            while (playing) {
                
                std::cout << "\n=== Hour: " << tick << " ===\n";

                // Each character processes messages, checks status, and decides on transitions
                for (auto& character : characters) {
                    character->checkMessages();
                    character->printStatus();



                    //transition logic
                    if (character->getHunger() >= 80) {
                        //if hunger is critical, buy food, else keep working
                        character->changeState(std::make_unique<BuyState>());

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
                if (tick >= 20) {
                    std::cout << "\nGAME OVER.\n\n\n";
                    //delete characters
                    characters.clear();
                    state = GameState::GAMEOVER;
                    playing = false;
                }

            }
        case(GameState::GAMEOVER):
            std::cout << "Press any key to replay\n";
            if (_getch()) {
                system("cls");
                state = GameState::PLAYING;
            }

        }
    }
    
}

int main() {
    // start the simulation
    gameLoop(characters);
    return 0;
}
