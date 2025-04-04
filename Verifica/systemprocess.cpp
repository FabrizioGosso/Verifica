#include "systemprocess.h"

SystemProcess::SystemProcess(int pid, int instructions, int priority, int arrivalTime, const std::string& name)
    : Process(pid, instructions, priority, arrivalTime, name) {}

int SystemProcess::CalculateWaitingTime() const {
    return waitingTime;
}

int SystemProcess::CalculateCompletionTime() const {
    return completionTime;
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

bool compareSystemProcesses(const SystemProcess& a, const SystemProcess& b) {
    return a.GetPriority() > b.GetPriority();
}
