#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <string>

class Process {
protected:
    int pid;
    int instructions;
    int priority;
    int arrivalTime;
    std::string name;
    int waitingTime;         // Aggiungi
    int completionTime;      // Aggiungi

public:
    Process(int pid, int instructions, int priority, int arrivalTime, const std::string& name);
    virtual ~Process();

    virtual int CalculateWaitingTime() const = 0;
    virtual int CalculateCompletionTime() const = 0;
    virtual void PrintInfo() const = 0;

    int GetInstructions() const;
    int GetPriority() const;
    int GetArrivalTime() const;
    std::string GetName() const;
    int GetPid() const;

    int GetWaitingTime() const { return waitingTime; }     // Aggiungi getter
    int GetCompletionTime() const { return completionTime; } // Aggiungi getter
    void SetWaitingTime(int wt) { waitingTime = wt; }     // Aggiungi setter
    void SetCompletionTime(int ct) { completionTime = ct; } // Aggiungi setter
};

class UserProcess : public Process {
public:
    UserProcess(int pid, int instructions, int priority, int arrivalTime, const std::string& name);

    int CalculateWaitingTime() const override;
    int CalculateCompletionTime() const override;
    void PrintInfo() const override;

    float CalculateEfficiency() const;
    bool RequiresUI() const;
};

class SystemProcess : public Process {
public:
    SystemProcess(int pid, int instructions, int priority, int arrivalTime, const std::string& name);

    int CalculateWaitingTime() const override;
    int CalculateCompletionTime() const override;
    void PrintInfo() const override;

    bool IsCritical() const;
    float CalculateCpuCost() const;
};

bool compareUserProcesses(const UserProcess& a, const UserProcess& b);
bool compareSystemProcesses(const SystemProcess& a, const SystemProcess& b);

#endif // PROCESS_H