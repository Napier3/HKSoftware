#include "functionconstraint.h"
namespace scd {

FunctionConstraint::FunctionConstraint()
{

}

map<string, FunctionConstraint::FC> FunctionConstraint::fcMap;
map<FunctionConstraint::FC, string> FunctionConstraint::fcStrMap;

FunctionConstraint::FC FunctionConstraint::createFromString(const string &fc)
{
    if(fcMap.empty())
    {
        fcMap["ST"] = ST;
        fcMap["MX"] = MX;
        fcMap["SP"] = SP;
        fcMap["SV"] = SV;
        fcMap["CF"] = CF;
        fcMap["DC"] = DC;
        fcMap["SG"] = SG;
        fcMap["SE"] = SE;
        fcMap["SR"] = SR;
        fcMap["OR"] = OR;
        fcMap["BL"] = BL;
        fcMap["EX"] = EX;
        fcMap["CO"] = CO;
        fcMap["ALL"] = ALL;
        fcMap["NONE"] = NONE;

        for(auto &i : fcMap) {
            fcStrMap[i.second] = i.first;
        }
    }

    return fcMap[fc];
}

string FunctionConstraint::toString(FunctionConstraint::FC fc) {
    if(fcStrMap.empty()) {
        createFromString("ST");
    }
    return fcStrMap[fc];
}

}
