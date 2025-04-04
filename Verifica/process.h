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
    int waitingTime;
    int completionTime;

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

    int GetWaitingTime() const;
    int GetCompletionTime() const;
    void SetWaitingTime(int wt);
    void SetCompletionTime(int ct);
};

#endif // PROCESS_H
