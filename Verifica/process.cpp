#include "process.h"

Process::Process(int pid, int instructions, int priority, int arrivalTime, const std::string& name)
    : pid(pid), instructions(instructions), priority(priority), arrivalTime(arrivalTime), name(name),
      waitingTime(0), completionTime(0) {} // Inizializza i nuovi membri

Process::~Process() {}

int Process::GetInstructions() const { return instructions; }
int Process::GetPriority() const { return priority; }
int Process::GetArrivalTime() const { return arrivalTime; }
std::string Process::GetName() const { return name; }
int Process::GetPid() const { return pid; }

UserProcess::UserProcess(int pid, int instructions, int priority, int arrivalTime, const std::string& name)
    : Process(pid, instructions, priority, arrivalTime, name) {}

int UserProcess::CalculateWaitingTime() const {
    return waitingTime; // Restituisce il valore memorizzato
}

int UserProcess::CalculateCompletionTime() const {
    return completionTime; // Restituisce il valore memorizzato
}

void UserProcess::PrintInfo() const {
    std::cout << "Tipo: User, PID: " << pid << ", Nome: " << name
              << ", Arrivo: " << arrivalTime;
}

float UserProcess::CalculateEfficiency() const {
    int completionTime = CalculateCompletionTime();
    return (completionTime > 0) ? static_cast<float>(instructions) / completionTime : 0.0f;
}

bool UserProcess::RequiresUI() const {
    return (name.find("gui") != std::string::npos ||
            name.find("window") != std::string::npos ||
            name.find("browser") != std::string::npos);
}

SystemProcess::SystemProcess(int pid, int instructions, int priority, int arrivalTime, const std::string& name)
    : Process(pid, instructions, priority, arrivalTime, name) {}

int SystemProcess::CalculateWaitingTime() const {
    return waitingTime; // Restituisce il valore memorizzato
}

int SystemProcess::CalculateCompletionTime() const {
    return completionTime; // Restituisce il valore memorizzato
}

void SystemProcess::PrintInfo() const {
    std::cout << "Tipo: System, PID: " << pid << ", Nome: " << name
              << ", Priorità: " << priority << ", Arrivo: " << arrivalTime;
}

bool SystemProcess::IsCritical() const {
    return (priority > 7 || name.find("kernel") != std::string::npos || name.find("system") != std::string::npos);
}

float SystemProcess::CalculateCpuCost() const {
    return static_cast<float>(instructions) * priority / 100.0f;
}

bool compareUserProcesses(const UserProcess& a, const UserProcess& b) {
    return a.GetInstructions() < b.GetInstructions();
}

bool compareSystemProcesses(const SystemProcess& a, const SystemProcess& b) {
    return a.GetPriority() > b.GetPriority();
}