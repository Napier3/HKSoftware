#include "sclparser.h"
#include <cstring>
#include "types/logicnodetype.h"
#include "types/dataobjecttype.h"
#include "types/dataattributetype.h"
#include "types/enumtype.h"
#include <chrono>
#include <iostream>

namespace scd {

SclParser::SclParser(const char *filePath)
    : mFilePath(filePath)
{

}

bool SclParser::parseFile(const ScdConfig &config)
{
    mConfig = config;
    auto result = mDoc.load_file(mFilePath.c_str());
    NPRINTF("File: %s, load result: %s\n", mFilePath.c_str(), result.description());
    if(!result)
    {
        return false;
    }

    NPRINTF("parse data type templates ...\n");
    typeDeclarations = parseDataTemplates();
    NPRINTF("parse IED section ...\n");
    parseIedSections();
    NPRINTF("parse communication section ...\n");
    parseCommunication();
    return true;
}

shared_ptr<TypeDeclarations> SclParser::parseDataTemplates()
{
    shared_ptr<TypeDeclarations> td = make_shared<TypeDeclarations>();

    auto scl = mDoc.child("SCL");
    auto dt = scl.child("DataTypeTemplates");

    for(auto t : dt.children())
    {
        auto name = t.name();
        if(strcmp(name, "LNodeType") == 0)
        {
            td->addType(std::make_shared<LogicNodeType>(t));
        }
        else if(strcmp(name, "DOType") == 0)
        {
            td->addType(std::make_shared<DataObjectType>(t));
        }
        else if(strcmp(name, "DAType") == 0)
        {
            DataAttributeType dat(t);
            td->addType(std::make_shared<DataAttributeType>(t));
        }
        else if(strcmp(name, "EnumType") == 0)
        {
            td->addType(std::make_shared<EnumType>(t));
        }
    }
    return td;
}

void SclParser::parseIedSections()
{
    auto scl = mDoc.child("SCL");
    for(auto &&child : scl.children("IED")) {
        auto name = child.attribute("name").as_string("");
        if(!mConfig.ignoreIeds.count(name))
        {
            ieds.push_back(make_shared<IED>(child, typeDeclarations.get()));
        }
    }
}

void SclParser::parseCommunication()
{

}

vector<shared_ptr<IED> > &SclParser::getIeds()
{
    return ieds;
}

const char *ParseException::what() const noexcept
{
    return mError.c_str();
}

}
