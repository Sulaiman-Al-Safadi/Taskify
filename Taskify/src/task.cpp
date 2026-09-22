#include "task.h"
#include <iostream>

Task::Task(int taskId, const std::string& description, const std::string& requiredSkill, int priority)
    : taskId(taskId), description(description), requiredSkill(requiredSkill),
      requiredCores(0), requiredRam(0), priority(priority) {}

Task::Task(int taskId, const std::string& description, int requiredCores, int requiredRam, int priority)
    : taskId(taskId), description(description), requiredSkill(""),
      requiredCores(requiredCores), requiredRam(requiredRam), priority(priority) {}

Task::~Task() {
    std::cout << "Task destroyed ID: " << taskId << std::endl;
}

int Task::getTaskId() const { return taskId; }
std::string Task::getDescription() const { return description; }
std::string Task::getRequiredSkill() const { return requiredSkill; }
int Task::getRequiredCores() const { return requiredCores; }
int Task::getRequiredRam() const { return requiredRam; }
int Task::getPriority() const { return priority; }

void Task::assignResource(Resource* resource) {
    if (resource) {
        assignedResources.push_back(resource);
        resource->setAvailability(false);
    }
}

void Task::displayAssignedResources() const {
    std::cout << "Task ID [" << taskId << "] (" << description << ") - Priority " << priority << " -> Assigned: ";
    if (assignedResources.empty()) {
        std::cout << "None (No suitable resource found)" << std::endl;
        return;
    }
    for (const auto& res : assignedResources) {
        std::cout << res->getName() << " (ID: " << res->getId() << ") ";
    }
    std::cout << std::endl;
}
