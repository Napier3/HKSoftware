#include "modelgenerator.h"
#include "dlt860_dynamic_model.h"
#include "model/logicalnode.h"
#include "gsp_mms_value.h"
#include "nlogging.h"
#include <variant>
#include <filesystem>
#include <iomanip>
#include <sstream>

using namespace std;

ModelGenerator::ModelGenerator()
{

}

ModelGenerator::~ModelGenerator()
{
    for(auto &m : _models)
    {
        if(m)
        {
            GspIedModel_destroy(m);
        }
    }
}

vector<GspIedModel *> *ModelGenerator::generateWithConfig(const std::string &filePath, const scd::ScdConfig &config)
{
    scd::SclParser parser(filePath.c_str());
    if(!parser.parseFile(config))
    {
        return nullptr;
    }

    for(auto &ied : parser.getIeds()) {
        _currentIed = ied.get();
        GspIedModel *model = GspIedModel_create(ied->getName());
        for(auto &ap : ied->getAccessPoints()) {
            if(ap->getName()[0] == 'S') {
                auto server = ap->getServer();
                for(auto &ld : server->getLogicalDevices()) {
                    GspLogicalDevice *device = GspLogicalDevice_create(ld->getInst(), model);
                    for(auto &ln : ld->getLogicalNodes()) {

                        GspLogicalNode *node = GspLogicalNode_create(ln->getName().c_str(), device);
                        // SG create
                        for(auto &sgcb : ln->getSettingGroupControlBlocks()) {
                            GspSettingGroupControlBlock_create(node, sgcb->actSG(), sgcb->numOfSGs());
                        }

                        // DO create
                        for(auto &dataObject : ln->getDataObjects()) {
                            createDataObject(dataObject.get(), (GspModelNode *)node);
                        }

                        // Dataset create
                        for(auto &ds : ln->getDataSets()) {
                            createDataSet(ds.get(), node);
                        }

                        // report control create
                        for(auto &rcb : ln->getReportControlBlocks()) {
                            if(rcb->getIndexed())
                            {
                                int maxInst = 1;
                                if(rcb->getRptEnabled())
                                {
                                    maxInst = rcb->getRptEnabled()->getMaxInstances();
                                    for(int i = 1; i <= maxInst; ++i)
                                    {
                                        stringstream ss;
                                        ss << setw(2) << setfill('0') << i;
                                        createReportControl(rcb.get(), node, ss.str().c_str());
                                    }
                                }
                            }
                            else
                            {
                                createReportControl(rcb.get(), node, "");
                            }
                        }

                        // log control create
                        for(auto &lcb : ln->getLogControlBlocks()) {
                            createLogControl(lcb.get(), node, device);
                        }

                        // log create
                        for(auto &log : ln->getLogs()) {
                            createLog(log.get(), node);
                        }
                    }

                }
            }
        }

        _models.push_back(model);
    }
    _models.push_back(nullptr);
    return &_models;
}

vector<GspIedModel *> *ModelGenerator::generate(const std::string &filePath)
{
    scd::SclParser parser(filePath.c_str());
    if(!parser.parseFile({}))
    {
        return nullptr;
    }

    for(auto &ied : parser.getIeds()) {
        _currentIed = ied.get();
        GspIedModel *model = GspIedModel_create(ied->getName());
        for(auto &ap : ied->getAccessPoints()) {
            if(ap->getName()[0] == 'S') {
                auto server = ap->getServer();
                for(auto &ld : server->getLogicalDevices()) {
                    GspLogicalDevice *device = GspLogicalDevice_create(ld->getInst(), model);
                    for(auto &ln : ld->getLogicalNodes()) {

                        GspLogicalNode *node = GspLogicalNode_create(ln->getName().c_str(), device);
                        // SG create
                        for(auto &sgcb : ln->getSettingGroupControlBlocks()) {
                            GspSettingGroupControlBlock_create(node, sgcb->actSG(), sgcb->numOfSGs());
                        }

                        // DO create
                        for(auto &dataObject : ln->getDataObjects()) {
                            createDataObject(dataObject.get(), (GspModelNode *)node);
                        }

                        // Dataset create
                        for(auto &ds : ln->getDataSets()) {
                            createDataSet(ds.get(), node);
                        }

                        // report control create
                        for(auto &rcb : ln->getReportControlBlocks()) {
                            if(rcb->getIndexed())
                            {
                                int maxInst = 1;
                                if(rcb->getRptEnabled())
                                {
                                    maxInst = rcb->getRptEnabled()->getMaxInstances();
                                    for(int i = 1; i <= maxInst; ++i)
                                    {
                                        stringstream ss;
                                        ss << setw(2) << setfill('0') << i;
                                        createReportControl(rcb.get(), node, ss.str().c_str());
                                    }
                                }
                            }
                            else
                            {
                                createReportControl(rcb.get(), node, "");
                            }
                        }

                        // log control create
                        for(auto &lcb : ln->getLogControlBlocks()) {
                            createLogControl(lcb.get(), node, device);
                        }

                        // log create
                        for(auto &log : ln->getLogs()) {
                            createLog(log.get(), node);
                        }
                    }

                }
            }
        }

        _models.push_back(model);
    }
    _models.push_back(nullptr);
    return &_models;
}

void ModelGenerator::createDataObject(scd::DataObject *dataObject, GspModelNode *parent)
{
    GspModelNode *modelNode = (GspModelNode *)GspDataObject_create(dataObject->getName().c_str(), parent, dataObject->getCount(), dataObject->getCdcType());
    for(auto &subDo : dataObject->getSubDataObjects()) {
        createDataObject(subDo, (GspModelNode *)modelNode);
        //GspDataObject_create(subDo->getName().c_str(), modelNode, subDo->getCount());
    }

    for(auto &da : dataObject->getDataAttributes()) {
        createDataAttribute(da, modelNode);
    }
}

void ModelGenerator::createDataAttribute(scd::DataAttribute *dataAttribute, GspModelNode *parent)
{
    GspDataAttributeType daType = (GspDataAttributeType)dataAttribute->getType();
    GspDataAttribute *da = GspDataAttribute_create(dataAttribute->getName().c_str(),
                                                   parent,
                                                   daType,
                                                   (GspFunctionalConstraint)dataAttribute->getFc(),
                                                   dataAttribute->getTriggerOptions()->getIntValue(),
                                                   dataAttribute->getCount(),
                                                   0
                                                   );

    if (!da)
    {
        return;
    }
    if(dataAttribute->getIsBasicAttribute()) {
        scd::DataModelValue *value = dataAttribute->getValue();
        if(!value) {
            value = dataAttribute->getDefinition()->getValue().get();
            if(value) {
                if(value->getValue().index() == 0) {
                    value->updateEnumOrdValue(_currentIed->getTypeDeclarations());
                }
            }
        }

        if(value && value->getValue().index() != 0 ) {
            switch (daType) {

            case DLT860_UNICODE_STRING_255:
            {
                da->mmsValue = GspMmsValue_newMmsString((char *)value->getStrValue().c_str());
            }
                break;

            case DLT860_VISIBLE_STRING_255:
            case DLT860_VISIBLE_STRING_129:
            case DLT860_VISIBLE_STRING_65:
            case DLT860_VISIBLE_STRING_64:
            case DLT860_VISIBLE_STRING_32:
            case DLT860_CURRENCY:
            {
                da->mmsValue = GspMmsValue_newVisibleString((char *)value->getStrValue().c_str());
            }
                break;

            case DLT860_INT8:
            case DLT860_ENUMERATED:
            {
                da->mmsValue = GspMmsValue_newIntegerFromInt8(value->getIntValue());
                break;
            }
            case DLT860_INT16:
            {
                da->mmsValue = GspMmsValue_newIntegerFromInt16(value->getIntValue());
                break;
            }
            case DLT860_INT32:
            {
                da->mmsValue = GspMmsValue_newIntegerFromInt32(value->getIntValue());
                break;
            }
            case DLT860_INT64:
            {
                da->mmsValue = GspMmsValue_newIntegerFromInt64(value->getIntValue());
                break;
            }
            case DLT860_INT128:
                assert(0);
                break;

            case DLT860_INT8U:
            {
                da->mmsValue = GspMmsValue_newIntegerFromUint8(value->getLongValue());
                break;
            }
            case DLT860_INT16U:
            {
                da->mmsValue = GspMmsValue_newIntegerFromUint16(value->getLongValue());
                break;
            }
            case DLT860_INT24U:
            case DLT860_INT32U:
            {
                da->mmsValue = GspMmsValue_newUnsignedFromUint32(value->getLongValue());
            }
                break;

            case DLT860_FLOAT32:
            {
                da->mmsValue = GspMmsValue_newFloat(value->getFloatValue());
            }
                break;

            case DLT860_FLOAT64:
            {
                da->mmsValue = GspMmsValue_newDouble(value->getDoubleValue());
            }
                break;

            case DLT860_BOOLEAN:
            {
                da->mmsValue = GspMmsValue_newBoolean(value->getBool());
            }
                break;

            case DLT860_OPTFLDS:
            case DLT860_TRGOPS:
            {
                da->mmsValue = GspMmsValue_newBitString(2);
                GspMmsValue_setBitStringFromIntegerBigEndian(da->mmsValue, value->getLongValue());
            }
                break;
            case DLT860_QUALITY:
            {
                da->mmsValue = GspMmsValue_newQuality();
            }
                break;
            case DLT860_DBPOS:
            {
                da->mmsValue = GspMmsValue_newBitString(2);
                da->mmsValue->present = Data_PR_dbpos;
                break;
            }
            case DLT860_TCMD:
            {
                da->mmsValue = GspMmsValue_newBitString(2);
                da->mmsValue->present = Data_PR_tcmd;
                break;
            }
            default:
                break;
            }
        }
    } else {
        for(auto &subDa : dataAttribute->getSubDataAttributes()) {
            createDataAttribute(subDa.get(), (GspModelNode *)da);
        }
    }
}

void ModelGenerator::createDataSet(scd::DataSet *dataSet, GspLogicalNode *parent)
{
    auto ds = GspDataSet_create(dataSet->getName(), parent);

    for(auto &fcda : dataSet->getFcda()) {
        string refer;

        if(fcda->getPrefix()) {
            refer += fcda->getPrefix();
        }

        refer += fcda->getLnClass();

        if(fcda->getLnInstance()) {
            refer += fcda->getLnInstance();
        }

        refer += ("$" + scd::FunctionConstraint::toString(fcda->getFc()));
        refer += ("$" + toMmsString(fcda->getDoName()));

        if(fcda->getDaName()) {
            refer += ("$" + toMmsString(fcda->getDaName()));
        }

        string ldName;
        if(fcda->getLdInstance()) {
            if(strcmp(fcda->getLdInstance(), parent->name) != 0) {
                ldName = fcda->getLdInstance();
            }
        }

        if(!ldName.empty()) {
            refer = ldName + "/" + refer;
        }

        GspDataSetEntry_create(ds, refer.c_str(), -1, NULL);
    }
}

void ModelGenerator::createReportControl(scd::ReportControlBlock *rcb, GspLogicalNode *parent, const string &index)
{
    string name = rcb->getName() + index;
    GspReportControlBlock_create(
                name.c_str(),
                parent,
                (char *)rcb->getRptID(),
                rcb->getBuffered(),
                (char *)rcb->getDataSet(),
                rcb->getConfRef(),
                rcb->getTriggerOptions()->getIntValue(),
                rcb->getOptionFields()->getIntValue(),
                rcb->getBufferTime(),
                rcb->getIntegrityPeriod());
}

void ModelGenerator::createLogControl(scd::LogControl *lcb, GspLogicalNode *parent, GspLogicalDevice *device)
{
    string logRef;

    if(lcb->getLogName()) {
        //logRef = string(device->name) + "/" + parent->name + "$" + lcb->getLogName();
        logRef = string(device->iedName) + string(device->name) + "/" + parent->name + "." + lcb->getLogName();
    }

    GspLogControlBlock_create(lcb->getName(),
                              parent,
                              (char *)lcb->getDataSet(),
                              (char *)(logRef.empty() ? NULL : logRef.c_str()),
                              lcb->getTriggerOptions()->getIntValue(),
                              lcb->getIntgPd(),
                              lcb->getLogEna(),
                              lcb->getReasonCode());
}

void ModelGenerator::createLog(scd::Log *log, GspLogicalNode *parent)
{
    Log_create(log->getName(), parent);
}

string ModelGenerator::toMmsString(const char *str)
{
    string data = str;
    for(auto &c : data) {
        if(c == '.') {
            c = '$';
        }
    }
    return data;
}
