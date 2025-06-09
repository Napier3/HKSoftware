/*
 *  dynamic_model.h
 */

#ifndef GSP_DYNAMIC_MODEL_H_
#define GSP_DYNAMIC_MODEL_H_

#include "dlt860_model.h"
#include "dlt860_cdc.h"

LIB860_API GspIedModel* GspIedModel_create(const char* name);

LIB860_API void GspIedModel_setIedNameForDynamicModel(GspIedModel* self, const char* name);

LIB860_API void GspIedModel_destroy(GspIedModel* model);

LIB860_API GspLogicalDevice* GspLogicalDevice_create(const char* name, GspIedModel* parent);

LIB860_API GspLogicalNode* GspLogicalNode_create(const char* name, GspLogicalDevice* parent);

LIB860_API GspDataObject* GspDataObject_create(const char* name, GspModelNode* parent, int arrayElements, const char *cdcType = "");

LIB860_API GspDataAttribute* GspDataAttribute_create(const char* name,
                                                     GspModelNode* parent,
                                                     GspDataAttributeType type,
                                                     GspFunctionalConstraint fc,
                                                     uint8_t triggerOptions,
                                                     int arrayElements,
                                                     uint32_t sAddr);

LIB860_API GspReportControlBlock* GspReportControlBlock_create(const char* name,
                                                               GspLogicalNode* parent,
                                                               char* rptId,
                                                               bool isBuffered,
                                                               char* dataSetName,
                                                               uint32_t confRef,
                                                               uint8_t trgOps,
                                                               uint8_t options,
                                                               uint32_t bufTm,
                                                               uint32_t intgPd);

LIB860_API void GspReportControlBlock_setPreconfiguredClient(GspReportControlBlock* self, uint8_t clientType, uint8_t* clientAddress);

LIB860_API GspLogControlBlock* GspLogControlBlock_create(const char* name,
                                                         GspLogicalNode* parent,
                                                         char* dataSetName,
                                                         char* logRef,
                                                         uint8_t trgOps,
                                                         uint32_t intgPd,
                                                         bool logEna,
                                                         bool reasonCode);

LIB860_API GspLog* Log_create(const char* name, GspLogicalNode* parent);

LIB860_API GspSettingGroupControlBlock* GspSettingGroupControlBlock_create(GspLogicalNode* parent, uint8_t actSG, uint8_t numOfSGs);

LIB860_API GspGSEControlBlock* GspGSEControlBlock_create(const char* name,
                                                         GspLogicalNode* parent,
                                                         char* appId,
                                                         char* dataSet,
                                                         uint32_t confRev,
                                                         bool fixedOffs,
                                                         int minTime,
                                                         int maxTime);

LIB860_API GspSVControlBlock* GspSVControlBlock_create(const char* name,
                                                       GspLogicalNode* parent,
                                                       char* svID,
                                                       char* dataSet,
                                                       uint32_t confRev,
                                                       uint8_t smpMod,
                                                       uint16_t smpRate,
                                                       uint8_t optFlds,
                                                       bool isUnicast);

LIB860_API void GspSVControlBlock_addPhyComAddress(GspSVControlBlock* self, GspPhyComAddress* phyComAddress);

LIB860_API void GspGSEControlBlock_addPhyComAddress(GspGSEControlBlock* self, GspPhyComAddress* phyComAddress);

LIB860_API GspPhyComAddress* GspPhyComAddress_create(uint8_t vlanPriority, uint16_t vlanId, uint16_t appId, uint8_t dstAddress[]);

LIB860_API GspDataSet* GspDataSet_create(const char* name, GspLogicalNode* parent);

LIB860_API int GspDataSet_getSize(GspDataSet* self);

LIB860_API GspDataSetEntry* GspDataSet_getFirstEntry(GspDataSet* self);

LIB860_API GspDataSetEntry* GspDataSetEntry_getNext(GspDataSetEntry* self);

LIB860_API GspDataSetEntry* GspDataSetEntry_create(GspDataSet* dataSet,
                                                   const char* variable,
                                                   int index,
                                                   const char* component);

#endif /* GSP_DYNAMIC_MODEL_H_ */
