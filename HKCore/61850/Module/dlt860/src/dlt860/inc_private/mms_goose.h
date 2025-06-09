/*
 *  mms_goose.h
 */

#ifndef GSP_MMS_GOOSE_H_
#define GSP_MMS_GOOSE_H_

typedef struct sMmsGooseControlBlock* GspMmsGooseControlBlock;

LIB860_INTERNAL GspMmsGooseControlBlock MmsGooseControlBlock_create(void);

LIB860_INTERNAL void GspMmsGooseControlBlock_destroy(GspMmsGooseControlBlock self);

LIB860_INTERNAL GspMmsDomain* GspMmsGooseControlBlock_getDomain(GspMmsGooseControlBlock self);

LIB860_INTERNAL void GspMmsGooseControlBlock_useGooseVlanTag(GspMmsGooseControlBlock self, bool useVlanTag);

LIB860_INTERNAL void GspMmsGooseControlBlock_setGooseInterfaceId(GspMmsGooseControlBlock self, const char* interfaceId);

LIB860_INTERNAL GspLogicalNode* GspMmsGooseControlBlock_getLogicalNode(GspMmsGooseControlBlock self);

LIB860_INTERNAL char* GspMmsGooseControlBlock_getLogicalNodeName(GspMmsGooseControlBlock self);

LIB860_INTERNAL char* GspMmsGooseControlBlock_getName(GspMmsGooseControlBlock self);

LIB860_INTERNAL GspMmsValue* GspMmsGooseControlBlock_getGCBValue(GspMmsGooseControlBlock self, char* elementName);

LIB860_INTERNAL GspMmsValue* GspMmsGooseControlBlock_getMmsValues(GspMmsGooseControlBlock self);

LIB860_INTERNAL GspMmsVariableSpecification* GspMmsGooseControlBlock_getVariableSpecification(GspMmsGooseControlBlock self);

LIB860_INTERNAL GspDataSet* GspMmsGooseControlBlock_getDataSet(GspMmsGooseControlBlock self);

LIB860_INTERNAL bool GspMmsGooseControlBlock_isEnabled(GspMmsGooseControlBlock self);

LIB860_INTERNAL void GspMmsGooseControlBlock_checkAndPublish(GspMmsGooseControlBlock self, uint64_t currentTime);

LIB860_INTERNAL void GspMmsGooseControlBlock_observedObjectChanged(GspMmsGooseControlBlock self);

LIB860_INTERNAL void GspMmsGooseControlBlock_enable(GspMmsGooseControlBlock self);

LIB860_INTERNAL void GspMmsGooseControlBlock_disable(GspMmsGooseControlBlock self);

LIB860_INTERNAL GspMmsVariableSpecification* GspGOOSE_createGOOSEControlBlocks(GspMmsMapping* self,
                                                                            GspMmsDomain* domain,
                                                                            GspLogicalNode* logicalNode,
                                                                            int gseCount);

#endif /* GSP_MMS_GOOSE_H_ */
