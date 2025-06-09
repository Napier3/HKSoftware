#ifndef SCLPARSER_H
#define SCLPARSER_H

#include <string>
#include <exception>
#include "common.h"
#include "pugixml/pugixml.hpp"
#include "types/typedeclarations.h"
#include <memory>
#include "model/ied.h"

using namespace std;
using namespace pugi;

namespace scd {

class SclParser
{
public:
    SclParser(const char *filePath);

    bool parseFile(const ScdConfig &config);

    vector<shared_ptr<IED> > &getIeds();

protected:
    shared_ptr<TypeDeclarations> parseDataTemplates();
    void parseIedSections();
    void parseCommunication();
private:
    string mFilePath;

    xml_document mDoc;
    vector<shared_ptr<IED>> ieds;
    shared_ptr<TypeDeclarations> typeDeclarations;
    ScdConfig mConfig;
};

}
#endif // SCLPARSER_H
