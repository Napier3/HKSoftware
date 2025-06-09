#ifndef FUNCTIONALCONSTRAINTDATA_H
#define FUNCTIONALCONSTRAINTDATA_H

#include "common.h"
#include "functionconstraint.h"

namespace scd {

class FunctionalConstraintData
{
public:
    FunctionalConstraintData(xml_node node);
    const char *getLdInstance() const;

    const char *getPrefix() const;

    const char *getLnClass() const;

    const char *getLnInstance() const;

    const char *getDoName() const;

    const char *getDaName() const;

    FunctionConstraint::FC getFc() const;

    string toString();
private:
    const char *ldInstance = nullptr;
    const char *prefix = nullptr;
    const char *lnClass = nullptr;
    const char *lnInstance = nullptr;
    const char *doName = nullptr;
    const char *daName = nullptr;
    FunctionConstraint::FC fc = FunctionConstraint::NONE;
    int ix = -1;
};

}
#endif // FUNCTIONALCONSTRAINTDATA_H
