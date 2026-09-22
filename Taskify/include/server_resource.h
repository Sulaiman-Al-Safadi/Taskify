#ifndef SERVER_RESOURCE_H
#define SERVER_RESOURCE_H

#include "resource.h"

class ServerResource : public Resource {
private:
    int cpuCores;
    int ramGb;

public:
    ServerResource(int id, const std::string& name, int cpuCores, int ramGb);
    ~ServerResource() override;

    bool canHandleLoad(int requiredCores, int requiredRam) const;
    void displayInfo() const override;
};

#endif
