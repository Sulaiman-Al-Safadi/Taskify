#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

// =================================================================
// Helper Function: String Normalization
// =================================================================
// Standardizes text input to lower-case for robust case-insensitive comparison.
string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(),
              [](unsigned char c) { return tolower(c); });
    return str;
}

// =================================================================
// 1. Abstract Base Class - Resource
// =================================================================
class Resource {
protected:
    int id;
    string name;
    bool isAvailable;

public:
    Resource(int id, const string& name)
        : id(id), name(name), isAvailable(true) {}

    // INTERVIEW QUESTION: Why is the destructor virtual?
    // Explanation: Ensures proper cleanup of derived class objects when deleted 
    // through a base class pointer, preventing memory leaks.
    virtual ~Resource() {
        cout << "Resource destroyed: " << name << endl;
    }

    int getId() const { return id; }
    string getName() const { return name; }
    bool getAvailability() const { return isAvailable; }
    void setAvailability(bool status) { isAvailable = status; }

    // INTERVIEW QUESTION: What is a Pure Virtual Function?
    // Explanation: It makes Resource an Abstract Class (cannot be instantiated directly).
    // Forces all derived classes to provide their own implementation of displayInfo().
    virtual void displayInfo() const = 0; 
};

// =================================================================
// 2. Derived Classes - EmployeeResource & ServerResource
// =================================================================
class EmployeeResource : public Resource {
private:
    vector<string> skills;

public:
    EmployeeResource(int id, const string& name, const vector<string>& skills)
        : Resource(id, name), skills(skills) {}

    ~EmployeeResource() override {
        cout << "EmployeeResource destroyed: " << name << endl;
    }

    void addSkill(const string& skill) {
        skills.push_back(skill);
    }

    // Flexible skill lookup supporting case-insensitive input matching
    bool hasSkill(const string& skill) const {
        string target = toLower(skill);
        for (const auto& s : skills) {
            if (toLower(s) == target) {
                return true;
            }
        }
        return false;
    }

    void displayInfo() const override {
        cout << "Employee - ID: " << id << ", Name: " << name << ", Skills: ";
        for (const auto& skill : skills) {
            cout << skill << " ";
        }
        cout << "| Status: " << (isAvailable ? "Available" : "Busy") << endl;
    }
};

class ServerResource : public Resource {
private:
    int cpuCores;
    int ramGb;

public:
    ServerResource(int id, const string& name, int cpuCores, int ramGb)
        : Resource(id, name), cpuCores(cpuCores), ramGb(ramGb) {}

    ~ServerResource() override {
        cout << "ServerResource destroyed: " << name << endl;
    }

    bool canHandleLoad(int requiredCores, int requiredRam) const {
        return (cpuCores >= requiredCores && ramGb >= requiredRam);
    }

    void displayInfo() const override {
        cout << "Server - ID: " << id << ", Name: " << name
             << ", CPU: " << cpuCores << " Cores, RAM: " << ramGb << "GB"
             << " | Status: " << (isAvailable ? "Available" : "Busy") << endl;
    }
};

// =================================================================
// 3. Task Class
// =================================================================
class Task {
private:
    int taskId;
    string description;
    string requiredSkill;
    int requiredCores;
    int requiredRam;
    int priority; // 3 = High, 2 = Medium, 1 = Low
    
    // NOTE: Stores non-owning raw pointers to assigned resources (Polymorphic Aggregation)
    vector<Resource*> assignedResources;

public:
    // Overloaded Constructor 1: For Human Resource Tasks
    Task(int taskId, const string& description, const string& requiredSkill, int priority)
        : taskId(taskId), description(description), requiredSkill(requiredSkill),
          requiredCores(0), requiredRam(0), priority(priority) {}

    // Overloaded Constructor 2: For Server Infrastructure Tasks
    Task(int taskId, const string& description, int requiredCores, int requiredRam, int priority)
        : taskId(taskId), description(description), requiredSkill(""),
          requiredCores(requiredCores), requiredRam(requiredRam), priority(priority) {}

    virtual ~Task() {
        cout << "Task destroyed ID: " << taskId << endl;
    }

    int getTaskId() const { return taskId; }
    string getDescription() const { return description; }
    string getRequiredSkill() const { return requiredSkill; }
    int getRequiredCores() const { return requiredCores; }
    int getRequiredRam() const { return requiredRam; }
    int getPriority() const { return priority; }

    void assignResource(Resource* resource) {
        if (resource) {
            assignedResources.push_back(resource);
            resource->setAvailability(false); // Update resource availability state
        }
    }

    void displayAssignedResources() const {
        cout << "Task ID [" << taskId << "] (" << description << ") - Priority " << priority << " -> Assigned: ";
        if (assignedResources.empty()) {
            cout << "None (No suitable resource found)" << endl;
            return;
        }
        for (const auto& res : assignedResources) {
            cout << res->getName() << " (ID: " << res->getId() << ") ";
        }
        cout << endl;
    }
};

// =================================================================
// 4. Core Scheduler Engine (Multi-Queue Priority Architecture)
// =================================================================
class Scheduler {
private:
    vector<Resource*> resources;
    
    // Multi-Queue Priority Buckets
    vector<Task*> highPriorityTasks;   // Priority 3
    vector<Task*> mediumPriorityTasks; // Priority 2
    vector<Task*> lowPriorityTasks;    // Priority 1

    // Helper processing method for a specific priority queue
    void processQueue(vector<Task*>& taskQueue) {
        for (auto task : taskQueue) {
            for (auto res : resources) {
                // Skip if resource is already assigned to another task
                if (!res->getAvailability()) continue;

                // INTERVIEW QUESTION: How does dynamic_cast work here?
                // Explanation: Safely casts Base Class Pointer (Resource*) to Derived Class Pointer.
                // Returns nullptr if type mismatch occurs (e.g., trying to cast Server to Employee).
                
                // Case A: Task requires human employee
                if (!task->getRequiredSkill().empty()) {
                    EmployeeResource* emp = dynamic_cast<EmployeeResource*>(res);
                    if (emp && emp->hasSkill(task->getRequiredSkill())) {
                        task->assignResource(res);
                        break; // Task satisfied, move to next task
                    }
                }
                // Case B: Task requires server hardware
                else if (task->getRequiredCores() > 0) {
                    ServerResource* server = dynamic_cast<ServerResource*>(res);
                    if (server && server->canHandleLoad(task->getRequiredCores(), task->getRequiredRam())) {
                        task->assignResource(res);
                        break; // Task satisfied, move to next task
                    }
                }
            }
        }
    }

public:
    void addResource(Resource* resource) {
        resources.push_back(resource);
    }

    // Direct tasks to corresponding queues upon registration
    void addTask(Task* task) {
        if (task->getPriority() == 3) {
            highPriorityTasks.push_back(task);
        } else if (task->getPriority() == 2) {
            mediumPriorityTasks.push_back(task);
        } else {
            lowPriorityTasks.push_back(task);
        }
    }

    // Executes priority-ordered execution flow
    void scheduleTasks() {
        processQueue(highPriorityTasks);
        processQueue(mediumPriorityTasks);
        processQueue(lowPriorityTasks);
    }
};

// =================================================================
// 5. Entry Point Execution
// =================================================================
int main() {
    Scheduler scheduler;

    // 1. Instantiate Resources dynamically
    EmployeeResource* emp1 = new EmployeeResource(101, "Ahmad", {"c++", "python"});
    EmployeeResource* emp2 = new EmployeeResource(102, "Sara", {"frontend", "ui/ux"});

    ServerResource* server1 = new ServerResource(201, "Main-Cluster", 16, 64);
    ServerResource* server2 = new ServerResource(202, "Mini-Server", 4, 8);

    scheduler.addResource(emp1);
    scheduler.addResource(emp2);
    scheduler.addResource(server1);
    scheduler.addResource(server2);

    // 2. Instantiate Tasks with varied priorities
    Task* task1 = new Task(1, "Build C++ Engine", "C++", 2);           // Medium Priority
    Task* task2 = new Task(2, "Train AI Model", 8, 32, 3);             // High Priority (Hardware)
    Task* task3 = new Task(3, "Design UI Dashboard", "Frontend", 1);   // Low Priority

    scheduler.addTask(task1);
    scheduler.addTask(task2);
    scheduler.addTask(task3);

    cout << "=== Starting Smart Task Scheduler Engine ===" << endl;

    // 3. Trigger priority-based automated resolution
    scheduler.scheduleTasks();

    cout << "\n=== Scheduling Results ===" << endl;
    task1->displayAssignedResources();
    task2->displayAssignedResources();
    task3->displayAssignedResources();

    // INTERVIEW QUESTION: Who is responsible for memory cleanup?
    // Explanation: Since raw pointers were allocated via 'new', manual deletion 
    // prevents heap memory accumulation (Memory Leak).
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