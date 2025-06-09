#ifndef RPTEANBLED_H
#define RPTEANBLED_H

#include "common.h"
#include <string>
#include "clientln.h"
#include <vector>

using namespace std;

namespace scd {

class RptEnabled
{
public:
    RptEnabled(xml_node node);
    int getMaxInstances() const;

    const char *getDesc() const;

    vector<shared_ptr<ClientLN>> &getClientLNs();

private:
    int maxInstances = 0;
    const char * desc;
    vector<shared_ptr<ClientLN>> clientLNs;
};

}
#endif // RPTEANBLED_H
