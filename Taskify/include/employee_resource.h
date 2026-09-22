#ifndef EMPLOYEE_RESOURCE_H
#define EMPLOYEE_RESOURCE_H

#include "resource.h"
#include <vector>
#include <string>

class EmployeeResource : public Resource {
private:
    std::vector<std::string> skills;

public:
    EmployeeResource(int id, const std::string& name, const std::vector<std::string>& skills);
    ~EmployeeResource() override;

    void addSkill(const std::string& skill);
    bool hasSkill(const std::string& skill) const;

    void displayInfo() const override;
};

#endif
