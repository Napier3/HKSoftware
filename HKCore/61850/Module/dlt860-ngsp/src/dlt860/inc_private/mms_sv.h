/*
 *  mms_sv.h
 *
 */

#ifndef GSP_LIBIEC61850_SRC_IEC61850_INC_PRIVATE_MMS_SV_H_
#define GSP_LIBIEC61850_SRC_IEC61850_INC_PRIVATE_MMS_SV_H_


typedef struct sMmsSampledValueControlBlock* MmsSampledValueControlBlock;

LIB860_INTERNAL MmsSampledValueControlBlock MmsSampledValueControlBlock_create(void);

LIB860_INTERNAL void MmsSampledValueControlBlock_destroy(MmsSampledValueControlBlock self);

LIB860_INTERNAL GspMmsVariableSpecification* LIBIEC61850_SV_createSVControlBlocks(GspMmsMapping* self,
                                                                                  GspMmsDomain* domain,
                                                                                  GspLogicalNode* logicalNode,
                                                                                  int svCount,
                                                                                  bool unicast);

LIB860_INTERNAL GspMmsValue* LIBIEC61850_SV_readAccessSampledValueControlBlock(GspMmsMapping* self, GspMmsDomain* domain, char* variableIdOrig);

LIB860_INTERNAL GspMmsDataAccessError LIBIEC61850_SV_writeAccessSVControlBlock(GspMmsMapping* self,
                                                                               GspMmsDomain* domain,
                                                                               char* variableIdOrig,
                                                                               GspMmsValue* value,
                                                                               GspMmsServerConnection connection);

LIB860_INTERNAL void LIBIEC61850_SV_setSVCBHandler(GspMmsMapping* self, GspSVControlBlock* svcb, GspSVCBEventHandler handler, void* parameter);

#endif /* GSP_LIBIEC61850_SRC_IEC61850_INC_PRIVATE_MMS_SV_H_ */
