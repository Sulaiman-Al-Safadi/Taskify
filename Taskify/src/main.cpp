#include <iostream>
#include "scheduler.h"
#include "employee_resource.h"
#include "server_resource.h"

using namespace std;

int main() {
    Scheduler scheduler;

    // Create resources
    EmployeeResource* emp1 = new EmployeeResource(101, "Ahmad", {"c++", "python"});
    EmployeeResource* emp2 = new EmployeeResource(102, "Sara", {"frontend", "ui/ux"});

    ServerResource* server1 = new ServerResource(201, "Main-Cluster", 16, 64);
    ServerResource* server2 = new ServerResource(202, "Mini-Server", 4, 8);

    scheduler.addResource(emp1);
    scheduler.addResource(emp2);
    scheduler.addResource(server1);
    scheduler.addResource(server2);

    // Create tasks
    Task* task1 = new Task(1, "Build C++ Engine", "c++", 2);
    Task* task2 = new Task(2, "Train AI Model", 8, 32, 3);
    Task* task3 = new Task(3, "Design UI Dashboard", "frontend", 1);

    scheduler.addTask(task1);
    scheduler.addTask(task2);
    scheduler.addTask(task3);

    cout << "=== Starting Smart Task Scheduler Engine ===" << endl;

    scheduler.scheduleTasks();

    cout << "\n=== Scheduling Results ===" << endl;
    task1->displayAssignedResources();
    task2->displayAssignedResources();
    task3->displayAssignedResources();

    cout << "\n=== Cleaning Up Memory ===" << endl;
    delete emp1;
    delete emp2;
    delete server1;
    delete server2;
    delete task1;
    delete task2;
    delete task3;

    return 0;
}
