#ifndef SYSTEMPROCESS_H
#define SYSTEMPROCESS_H

#include "process.h"

class SystemProcess : public Process {
public:
    SystemProcess(int pid, int instructions, int priority, int arrivalTime, const std::string& name);

    int CalculateWaitingTime() const override;
    int CalculateCompletionTime() const override;
    void PrintInfo() const override;

    bool IsCritical() const;
    float CalculateCpuCost() const;
};

bool compareSystemProcesses(const SystemProcess& a, const SystemProcess& b);

#endif // SYSTEMPROCESS_H
