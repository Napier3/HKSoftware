#ifndef FUNCTIONCONSTRAINT_H
#define FUNCTIONCONSTRAINT_H

#include "common.h"
namespace scd {

class FunctionConstraint
{
public:
    enum FC {
        ST = 0,
        MX,
        SP,
        SV,
        CF,
        DC,
        SG,
        SE,
        SR,
        OR,
        BL,
        EX,
        CO,
        ALL = 99,
        NONE = -1,
    };
    FunctionConstraint();
    static map<string, FC> fcMap;
    static map<FC, string> fcStrMap;
    static FC createFromString(const string &fc);
    static string toString(FC fc);
};

}
#endif // FUNCTIONCONSTRAINT_H
