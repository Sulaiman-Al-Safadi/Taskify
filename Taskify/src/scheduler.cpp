#include "scheduler.h"
#include "employee_resource.h"
#include "server_resource.h"
#include <iostream>

void Scheduler::processQueue(std::vector<Task*>& taskQueue) {
    for (auto task : taskQueue) {
        for (auto res : resources) {
            if (!res->getAvailability())
                continue;

            // Employee case
            if (!task->getRequiredSkill().empty()) {
                auto emp = dynamic_cast<EmployeeResource*>(res);
                if (emp && emp->hasSkill(task->getRequiredSkill())) {
                    task->assignResource(res);
                    break;
                }
            }
            // Server case
            else if (task->getRequiredCores() > 0) {
                auto server = dynamic_cast<ServerResource*>(res);
                if (server && server->canHandleLoad(task->getRequiredCores(), task->getRequiredRam())) {
                    task->assignResource(res);
                    break;
                }
            }
        }
    }
}

void Scheduler::addResource(Resource* resource) {
    resources.push_back(resource);
}

void Scheduler::addTask(Task* task) {
    if (task->getPriority() == 3)
        highPriorityTasks.push_back(task);
    else if (task->getPriority() == 2)
        mediumPriorityTasks.push_back(task);
    else
        lowPriorityTasks.push_back(task);
}

void Scheduler::scheduleTasks() {
    processQueue(highPriorityTasks);
    processQueue(mediumPriorityTasks);
    processQueue(lowPriorityTasks);
}
