#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <string>

class Person {
protected:
    std::string name;
    std::string surname;

public:
    Person(const std::string& name, const std::string& surname);
    std::string getFullName() const;
};

class Player : public Person {
private:
    int number;
    float pointsPerGame;
    float reboundsPerGame;
    float assistsPerGame;
    static int totalPlayers;

public:
    Player(const std::string& name, const std::string& surname, int number, float ppg, float rpg, float apg);
    void print() const;
    float getPointsPerGame() const;
    static int getTotalPlayers();
};

int readPlayersFromFile(std::vector<Player>& players, const std::string& filename);
Player bestScorer(const std::vector<Player>& players);

#endif // PLAYER_H