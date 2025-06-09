#ifndef IED_H
#define IED_H

#include "common.h"
#include "accesspoint.h"

namespace scd {

class IED
{
public:
    IED(xml_node node, TypeDeclarations *typeDeclarations);

    TypeDeclarations *getTypeDeclarations() const;

    vector<shared_ptr<AccessPoint> > &getAccessPoints();

    AccessPoint *getAccessPointByName(const char *apName) {
        for(auto &&ap : accessPoints) {
            if(strcmp(ap->getName(), apName) == 0) {
                return ap.get();
            }
        }
        return nullptr;
    }
    const char *getName() const;

private:
    const char *name = nullptr;
    vector<shared_ptr<AccessPoint>> accessPoints;
    TypeDeclarations *typeDeclarations;
};

}
#endif // IED_H
