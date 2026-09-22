#include "server_resource.h"
#include <iostream>

ServerResource::ServerResource(int id, const std::string& name, int cpuCores, int ramGb)
    : Resource(id, name), cpuCores(cpuCores), ramGb(ramGb) {}

ServerResource::~ServerResource() {
    std::cout << "ServerResource destroyed: " << name << std::endl;
}

bool ServerResource::canHandleLoad(int requiredCores, int requiredRam) const {
    return (cpuCores >= requiredCores && ramGb >= requiredRam);
}

void ServerResource::displayInfo() const {
    std::cout << "Server - ID: " << id << ", Name: " << name
              << ", CPU: " << cpuCores << " Cores, RAM: " << ramGb << "GB"
              << " | Status: " << (isAvailable ? "Available" : "Busy") << std::endl;
}
