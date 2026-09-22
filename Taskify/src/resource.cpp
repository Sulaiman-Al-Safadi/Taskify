#include "resource.h"
#include <iostream>

Resource::Resource(int id, const std::string& name)
    : id(id), name(name), isAvailable(true) {}

Resource::~Resource() {
    std::cout << "Resource destroyed: " << name << std::endl;
}

int Resource::getId() const { return id; }
std::string Resource::getName() const { return name; }
bool Resource::getAvailability() const { return isAvailable; }
void Resource::setAvailability(bool status) { isAvailable = status; }
