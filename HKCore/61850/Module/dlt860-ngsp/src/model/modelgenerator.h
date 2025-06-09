#ifndef MODELGENERATOR_H
#define MODELGENERATOR_H

#include "sclparser.h"
#include "dlt860_model.h"
#include <vector>
#include <string>
#include <set>
#include "model/dataobject.h"
#include "model/dataset.h"
#include "model/reportcontrolblock.h"
#include "model/logcontrol.h"
#include "model/log.h"

using namespace std;

class ModelGenerator
{
public:
    ModelGenerator();
    virtual ~ModelGenerator();
    static ModelGenerator *inst()
    {
        static ModelGenerator obj;
        return &obj;
    }

    vector<GspIedModel *> *generateWithConfig(const std::string &filePath, const scd::ScdConfig &config);
    vector<GspIedModel *> *generate(const std::string &filePath);


    void createDataObject(scd::DataObject *dataObject, GspModelNode *parent);
    void createDataAttribute(scd::DataAttribute *dataAttribute, GspModelNode *parent);
    void createDataSet(scd::DataSet *dataSet, GspLogicalNode *parent);
    void createReportControl(scd::ReportControlBlock *rcb, GspLogicalNode *parent, const string &index);
    void createLogControl(scd::LogControl *lcb, GspLogicalNode *parent, GspLogicalDevice *device);
    void createLog(scd::Log *log, GspLogicalNode *parent);
private:

    string toMmsString(const char *str);
    vector<GspIedModel *> _models;
    scd::IED *_currentIed = nullptr;
};

#endif // MODELGENERATOR_H
