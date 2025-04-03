#include <iostream>
#include "saluto.h"

void salutaUtente(const std::string& nome) {
    std::cout << "Ciao, " << nome << "! Benvenuto nel mondo di C++!" << std::endl;
}

int main() {
    std::string nome;
    
    std::cout << "Inserisci il tuo nome: ";
    std::getline(std::cin, nome);
    
    salutaUtente(nome);
    
    return 0;
}