#include "player.h"

int main() {
    std::vector<Player> players;
    readPlayersFromFile(players, "giocatori.txt");

    std::cout << "--- Squadra ---\n\n";
    for (const auto& player : players) {
        player.print();
    }

    try {
        Player best = bestScorer(players);
        std::cout << "Il miglior marcatore della squadra è: " << best.getFullName()
                  << " con " << best.getPointsPerGame() << " punti a partita.\n";
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}