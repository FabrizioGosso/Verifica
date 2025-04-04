#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <iomanip> // For output formatting
#include <map>     // To keep track of process names

#include "process.h" // include the process header
#include "userprocess.h"
#include "systemprocess.h"

// 0. print info
void printHeader() {
    std::cout << "========================================================" << std::endl;
    std::cout << "           SIMULATORE DI GESTIONE DEI PROCESSI           " << std::endl;
    std::cout << "========================================================" << std::endl;
    std::cout << "Nome: Fabrizio" << std::endl;
    std::cout << "Cognome: Gosso" << std::endl;
    std::cout << "Ambiente di sviluppo: Codespaces" << std::endl;
    std::cout << "Data e Ora: Venerdì, 4 Aprile 2025, 15:45 CEST (Turin, Italy)" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
}

// Function to print the content of the file
void printFileContent(const std::string& filename) {
    std::cout << "CONTENUTO DEL FILE DATI '" << filename << "':" << std::endl;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << "  > " << line << std::endl;
        }
        file.close();
    } else {
        std::cerr << "ERRORE: Impossibile aprire il file: " << filename << std::endl;
    }
    std::cout << "--------------------------------------------------------" << std::endl;
}

int main() {
    printHeader();
    const std::string filename = "dati.txt"; 
    printFileContent(filename);

    std::vector<UserProcess> userProcesses;
    std::vector<SystemProcess> systemProcesses;
    std::map<std::string, bool> processNames; // Track process names

    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        int lineNumber = 0;
        while (std::getline(file, line)) {
            lineNumber++;
            std::istringstream iss(line);
            char type;
            int pid, instructions, priority, arrivalTime;
            std::string name;

            if (iss >> type >> pid >> instructions >> priority >> arrivalTime >> name) {
                if (instructions < 0 || priority < 0 || arrivalTime < 0) {
                    std::cerr << "AVVISO: Valori non validi nella riga " << lineNumber << ": '" << line << "'. Processo scartato." << std::endl;
                    continue;
                }
                if (processNames.count(name)) {
                    std::cerr << "AVVISO: Nome processo duplicato '" << name << "' nella riga " << lineNumber << ". Processo scartato." << std::endl;
                    continue;
                }
                processNames[name] = true;

                if (type == 'U') {
                    userProcesses.emplace_back(pid, instructions, priority, arrivalTime, name);
                } else if (type == 'S') {
                    systemProcesses.emplace_back(pid, instructions, priority, arrivalTime, name);
                } else {
                    std::cerr << "AVVISO: Tipo di processo sconosciuto nella riga " << lineNumber << ": '" << line << "'. Processo scartato." << std::endl;
                }
            } else {
                std::cerr << "AVVISO: Formato riga non valido nella riga " << lineNumber << ": '" << line << "'. Riga ignorata." << std::endl;
            }
        }
        file.close();
    } else {
        std::cerr << "ERRORE: Impossibile aprire il file: " << filename << std::endl;
        return 1;
    }
    std::cout << "--------------------------------------------------------" << std::endl;

    // Sorting
    std::sort(userProcesses.begin(), userProcesses.end(), compareUserProcesses);
    std::sort(systemProcesses.begin(), systemProcesses.end(), compareSystemProcesses);

    // Calculate waiting and completion times
    int currentTime = 0;
    float totalUserWaitingTime = 0;
    float totalSystemWaitingTime = 0; // Dichiarazione qui (corretta)
    int totalUserInstructions = 0;
    int totalSystemInstructions = 0;
    std::vector<const UserProcess*> completedUserProcesses;
    std::vector<const SystemProcess*> completedSystemProcesses;

    std::cout << "\n--- ESECUZIONE DEI PROCESSI UTENTE ---" << std::endl;
    for (auto& process : userProcesses) {
        int waitingTime = std::max(0, currentTime - process.GetArrivalTime());
        int completionTime = currentTime + process.GetInstructions();
        totalUserWaitingTime += waitingTime;
        totalUserInstructions += process.GetInstructions();
        currentTime = completionTime;
        process.SetWaitingTime(waitingTime);
        process.SetCompletionTime(completionTime);
        completedUserProcesses.push_back(&process);

        std::cout << "  [USER] PID: " << std::setw(4) << process.GetPid()
                  << ", Nome: " << std::left << std::setw(15) << process.GetName() << std::right
                  << ", Arrivo: " << std::setw(4) << process.GetArrivalTime()
                  << ", Attesa: " << std::setw(4) << process.GetWaitingTime()
                  << ", Compl: " << std::setw(5) << process.GetCompletionTime()
                  << ", Efficienza: " << std::fixed << std::setprecision(2) << process.CalculateEfficiency();
        if (process.RequiresUI()) {
            std::cout << ", [Richiede UI]";
        }
        std::cout << std::endl;
    }
    float averageUserWaitingTime = (userProcesses.empty()) ? 0 : totalUserWaitingTime / static_cast<float>(userProcesses.size());

    std::cout << "\n--- ESECUZIONE DEI PROCESSI DI SISTEMA ---" << std::endl;
    for (auto& process : systemProcesses) {
        int waitingTime = std::max(0, currentTime - process.GetArrivalTime());
        int completionTime = currentTime + process.GetInstructions();
        totalSystemWaitingTime += waitingTime;
        totalSystemInstructions += process.GetInstructions();
        currentTime = completionTime;
        process.SetWaitingTime(waitingTime);
        process.SetCompletionTime(completionTime);
        completedSystemProcesses.push_back(&process);

        std::cout << "  [SYSTEM] PID: " << std::setw(4) << process.GetPid()
                  << ", Nome: " << std::left << std::setw(15) << process.GetName() << std::right
                  << ", Priorità: " << std::setw(2) << process.GetPriority()
                  << ", Arrivo: " << std::setw(4) << process.GetArrivalTime()
                  << ", Attesa: " << std::setw(4) << process.GetWaitingTime()
                  << ", Compl: " << std::setw(5) << process.GetCompletionTime()
                  << ", Costo CPU: " << std::fixed << std::setprecision(2) << process.CalculateCpuCost();
        if (process.IsCritical()) {
            std::cout << ", [CRITICO]";
        }
        std::cout << std::endl;
    }
    float averageSystemWaitingTime = (systemProcesses.empty()) ? 0 : totalSystemWaitingTime / static_cast<float>(systemProcesses.size());

    std::cout << "\n--- RIEPILOGO ---" << std::endl;
    std::cout << "Tempo medio di attesa processi utente: " << std::fixed << std::setprecision(2) << averageUserWaitingTime << " unità di tempo." << std::endl;
    std::cout << "Tempo medio di attesa processi di sistema: " << std::fixed << std::setprecision(2) << averageSystemWaitingTime << " unità di tempo." << std::endl;

    // Calculate percentage of time occupied
    int totalTime = currentTime;
    double userTimePercentage = (totalTime > 0) ? static_cast<double>(totalUserInstructions) / totalTime * 100 : 0;
    double systemTimePercentage = (totalTime > 0) ? static_cast<double>(totalSystemInstructions) / totalTime * 100 : 0;

    std::cout << "\n--- UTILIZZO TEMPO CPU ---" << std::endl;
    std::cout << "Percentuale tempo CPU processi utente: " << std::fixed << std::setprecision(2) << userTimePercentage << "%" << std::endl;
    std::cout << "Percentuale tempo CPU processi di sistema: " << std::fixed << std::setprecision(2) << systemTimePercentage << "%" << std::endl;
    std::cout << "Percentuale tempo CPU totale utilizzata: " << std::fixed << std::setprecision(2) << userTimePercentage + systemTimePercentage << "%" << std::endl;
    std::cout << "Tempo totale di esecuzione: " << totalTime << " unità di tempo." << std::endl;

    // Identify the most efficient user process
    const UserProcess* mostEfficientUser = nullptr;
    if (!completedUserProcesses.empty()) {
        mostEfficientUser = completedUserProcesses[0];
        for (const auto* proc : completedUserProcesses) {
            if (proc->CalculateEfficiency() > mostEfficientUser->CalculateEfficiency()) {
                mostEfficientUser = proc;
            }
        }
        std::cout << "\n--- ANALISI DEI PROCESSI UTENTE ---" << std::endl;
        std::cout << "Processo utente più efficiente (istruzioni/completamento):" << std::endl;
        mostEfficientUser->PrintInfo();
        std::cout << ", Efficienza: " << std::fixed << std::setprecision(2) << mostEfficientUser->CalculateEfficiency() << std::endl;
    } else {
        std::cout << "\n--- ANALISI DEI PROCESSI UTENTE ---" << std::endl;
        std::cout << "Nessun processo utente completato." << std::endl;
    }

    // Identify the process with the maximum waiting time (among all)
    const Process* maxWaitingTimeProcess = nullptr;
    int maxWaitingTime = -1;

    for (const auto* proc : completedUserProcesses) {
        if (proc->GetWaitingTime() > maxWaitingTime) {
            maxWaitingTime = proc->GetWaitingTime();
            maxWaitingTimeProcess = proc;
        }
    }
    for (const auto* proc : completedSystemProcesses) {
        if (proc->GetWaitingTime() > maxWaitingTime) {
            maxWaitingTime = proc->GetWaitingTime();
            maxWaitingTimeProcess = proc;
        }
    }

    std::cout << "\n--- ANALISI DEI TEMPI DI ATTESA ---" << std::endl;
    if (maxWaitingTimeProcess != nullptr) {
        std::cout << "Processo con il tempo di attesa massimo (" << maxWaitingTime << " unità di tempo):" << std::endl;
        maxWaitingTimeProcess->PrintInfo();
        std::cout << std::endl;
    } else {
        std::cout << "Nessun processo completato, quindi nessun tempo di attesa da analizzare." << std::endl;
    }

    std::cout << "\n======================== FINE SIMULAZIONE ========================" << std::endl;

    return 0;
}