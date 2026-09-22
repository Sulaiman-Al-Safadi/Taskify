#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

class Resource {
protected:
    int id;
    std::string name;
    bool isAvailable;

public:
    Resource(int id, const std::string& name);
    virtual ~Resource();

    int getId() const;
    std::string getName() const;
    bool getAvailability() const;
    void setAvailability(bool status);

    virtual void displayInfo() const = 0;
};

#endif
