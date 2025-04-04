#ifndef USERPROCESS_H
#define USERPROCESS_H

#include "process.h"

class UserProcess : public Process {
public:
    UserProcess(int pid, int instructions, int priority, int arrivalTime, const std::string& name);

    int CalculateWaitingTime() const override;
    int CalculateCompletionTime() const override;
    void PrintInfo() const override;

    float CalculateEfficiency() const;
    bool RequiresUI() const;
};

bool compareUserProcesses(const UserProcess& a, const UserProcess& b);

#endif // USERPROCESS_H
