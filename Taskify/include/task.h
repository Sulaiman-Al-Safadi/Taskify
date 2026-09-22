#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>
#include "resource.h"

class Task {
private:
    int taskId;
    std::string description;
    std::string requiredSkill;
    int requiredCores;
    int requiredRam;
    int priority;

    std::vector<Resource*> assignedResources;

public:
    Task(int taskId, const std::string& description, const std::string& requiredSkill, int priority);
    Task(int taskId, const std::string& description, int requiredCores, int requiredRam, int priority);
    virtual ~Task();

    int getTaskId() const;
    std::string getDescription() const;
    std::string getRequiredSkill() const;
    int getRequiredCores() const;
    int getRequiredRam() const;
    int getPriority() const;

    void assignResource(Resource* resource);
    void displayAssignedResources() const;
};

#endif
