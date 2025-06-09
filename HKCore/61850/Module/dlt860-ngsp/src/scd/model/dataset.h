#ifndef DATASET_H
#define DATASET_H

#include "common.h"
#include "functionconstraint.h"
#include "functionalconstraintdata.h"
#include <vector>
namespace scd {

using namespace std;

class DataSet
{
public:
    DataSet(xml_node node);

    const char *getName() const;

    const char *getDesc() const;

    vector<shared_ptr<FunctionalConstraintData> > &getFcda();

private:
    const char *name = nullptr;
    const char *desc = nullptr;
    vector<shared_ptr<FunctionalConstraintData>> fcda;
};

}
#endif // DATASET_H
