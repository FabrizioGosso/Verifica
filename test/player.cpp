#include "player.h"
#include <fstream>
#include <sstream>

Person::Person(const std::string& name, const std::string& surname) : name(name), surname(surname) {}

std::string Person::getFullName() const { return name + " " + surname; }

int Player::totalPlayers = 0;

Player::Player(const std::string& name, const std::string& surname, int number, float ppg, float rpg, float apg)
    : Person(name, surname), number(number), pointsPerGame(ppg), reboundsPerGame(rpg), assistsPerGame(apg) {
    totalPlayers++;
}

void Player::print() const {
    std::cout << "Nome: " << getFullName() << "\n";
    std::cout << "Numero di maglia: " << number << "\n";
    std::cout << "Punti per partita: " << pointsPerGame << "\n";
    std::cout << "Rimbalzi per partita: " << reboundsPerGame << "\n";
    std::cout << "Assist per partita: " << assistsPerGame << "\n\n";
}

float Player::getPointsPerGame() const { return pointsPerGame; }
int Player::getTotalPlayers() { return totalPlayers; }

int readPlayersFromFile(std::vector<Player>& players, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Errore nell'apertura del file!" << std::endl;
        return 0;
    }

    std::string line;
    int count = 0;
    while (std::getline(file, line) && count < 5) {
        std::istringstream iss(line);
        std::string name, surname;
        int number;
        float ppg, rpg, apg;
        if (iss >> name >> surname >> number >> ppg >> rpg >> apg) {
            players.emplace_back(name, surname, number, ppg, rpg, apg);
            count++;
        }
    }
    file.close();

    std::cout << "Numero totale di giocatori letti finora: " << Player::getTotalPlayers() << "\n";
    return count;
}

Player bestScorer(const std::vector<Player>& players) {
    if (players.empty()) {
        throw std::runtime_error("Nessun giocatore disponibile.");
    }

    const Player* best = &players[0];
    for (const auto& player : players) {
        if (player.getPointsPerGame() > best->getPointsPerGame()) {
            best = &player;
        }
    }
    return *best;
}
