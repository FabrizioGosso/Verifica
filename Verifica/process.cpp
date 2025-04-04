#include "process.h"

Process::Process(int pid, int instructions, int priority, int arrivalTime, const std::string& name)
    : pid(pid), instructions(instructions), priority(priority),
      arrivalTime(arrivalTime), name(name), waitingTime(0), completionTime(0) {}

Process::~Process() {}

int Process::GetInstructions() const { return instructions; }
int Process::GetPriority() const { return priority; }
int Process::GetArrivalTime() const { return arrivalTime; }
std::string Process::GetName() const { return name; }
int Process::GetPid() const { return pid; }
int Process::GetWaitingTime() const { return waitingTime; }
int Process::GetCompletionTime() const { return completionTime; }
void Process::SetWaitingTime(int wt) { waitingTime = wt; }
void Process::SetCompletionTime(int ct) { completionTime = ct; }
