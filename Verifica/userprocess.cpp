#include "userprocess.h"

UserProcess::UserProcess(int pid, int instructions, int priority, int arrivalTime, const std::string& name)
    : Process(pid, instructions, priority, arrivalTime, name) {}

int UserProcess::CalculateWaitingTime() const {
    return waitingTime;
}

int UserProcess::CalculateCompletionTime() const {
    return completionTime;
}

void UserProcess::PrintInfo() const {
    std::cout << "Tipo: User, PID: " << pid << ", Nome: " << name
              << ", Arrivo: " << arrivalTime;
}

float UserProcess::CalculateEfficiency() const {
    int completion = CalculateCompletionTime();
    return (completion > 0) ? static_cast<float>(instructions) / completion : 0.0f;
}

bool UserProcess::RequiresUI() const {
    return (name.find("gui") != std::string::npos ||
            name.find("window") != std::string::npos ||
            name.find("browser") != std::string::npos);
}

bool compareUserProcesses(const UserProcess& a, const UserProcess& b) {
    return a.GetInstructions() < b.GetInstructions();
}
