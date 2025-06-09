#include "dataset.h"
namespace scd {

DataSet::DataSet(xml_node node)
{
    name = node.attribute("name").as_string(nullptr);
    desc = node.attribute("desc").as_string(nullptr);

    if(!name) {
        throw ParseException("Dataset misses required attribute \"name\"");
    }

    for(auto &&child : node.children()) {
        fcda.push_back(make_shared<FunctionalConstraintData>(child));
    }
}

const char *DataSet::getName() const
{
    return name;
}

const char *DataSet::getDesc() const
{
    return desc;
}

vector<shared_ptr<FunctionalConstraintData> > &DataSet::getFcda()
{
    return fcda;
}

}
