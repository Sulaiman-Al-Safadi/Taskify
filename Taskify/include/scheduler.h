#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include "resource.h"
#include "task.h"

class Scheduler {
private:
    std::vector<Resource*> resources;

    std::vector<Task*> highPriorityTasks;
    std::vector<Task*> mediumPriorityTasks;
    std::vector<Task*> lowPriorityTasks;

    void processQueue(std::vector<Task*>& taskQueue);

public:
    void addResource(Resource* resource);
    void addTask(Task* task);
    void scheduleTasks();
};

#endif
