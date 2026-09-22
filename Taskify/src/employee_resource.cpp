#include "employee_resource.h"
#include <iostream>
#include <algorithm>

static std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return result;
}

EmployeeResource::EmployeeResource(int id, const std::string& name, const std::vector<std::string>& skills)
    : Resource(id, name), skills(skills) {}

EmployeeResource::~EmployeeResource() {
    std::cout << "EmployeeResource destroyed: " << name << std::endl;
}

void EmployeeResource::addSkill(const std::string& skill) {
    skills.push_back(skill);
}

bool EmployeeResource::hasSkill(const std::string& skill) const {
    std::string target = toLower(skill);
    for (const auto& s : skills) {
        if (toLower(s) == target) {
            return true;
        }
    }
    return false;
}

void EmployeeResource::displayInfo() const {
    std::cout << "Employee - ID: " << id << ", Name: " << name << ", Skills: ";
    for (const auto& skill : skills) {
        std::cout << skill << " ";
    }
    std::cout << "| Status: " << (isAvailable ? "Available" : "Busy") << std::endl;
}
