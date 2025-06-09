/*
 *  model.h
 *
 */

#ifndef GSP_MODEL_H_
#define GSP_MODEL_H_

#include "dlt860_common.h"
#include <vector>
#include <set>
#include <map>
#include <string>

using namespace std;

typedef struct sGspModelNode GspModelNode;

typedef struct sGspDataAttribute GspDataAttribute;

typedef struct sGspDataObject GspDataObject;

typedef struct sGspLogicalNode GspLogicalNode;

typedef struct sGspLogicalDevice GspLogicalDevice;

typedef struct sGspIedModel GspIedModel;

typedef struct sGspDataSet GspDataSet;

typedef struct sGspReportControlBlock GspReportControlBlock;

typedef struct sGspSettingGroupControlBlock GspSettingGroupControlBlock;

typedef struct sGspGSEControlBlock GspGSEControlBlock;

typedef struct sGspSVControlBlock GspSVControlBlock;

typedef struct sGspLogControlBlock GspLogControlBlock;

typedef struct sGspLog GspLog;

struct GspReportControl;

typedef enum {
    DLT860_BOOLEAN = 0,/* int */
    DLT860_INT8 = 1,   /* int8_t */
    DLT860_INT16 = 2,  /* int16_t */
    DLT860_INT32 = 3,  /* int32_t */
    DLT860_INT64 = 4,  /* int64_t */
    DLT860_INT128 = 5, /* no native mapping! */
    DLT860_INT8U = 6,  /* uint8_t */
    DLT860_INT16U = 7, /* uint16_t */
    DLT860_INT24U = 8, /* uint32_t */
    DLT860_INT32U = 9, /* uint32_t */
    DLT860_FLOAT32 = 10, /* float */
    DLT860_FLOAT64 = 11, /* double */
    DLT860_ENUMERATED = 12,
    DLT860_OCTET_STRING_64 = 13,
    DLT860_OCTET_STRING_6 = 14,
    DLT860_OCTET_STRING_8 = 15,
    DLT860_VISIBLE_STRING_32 = 16,
    DLT860_VISIBLE_STRING_64 = 17,
    DLT860_VISIBLE_STRING_65 = 18,
    DLT860_VISIBLE_STRING_129 = 19,
    DLT860_VISIBLE_STRING_255 = 20,
    DLT860_UNICODE_STRING_255 = 21,
    DLT860_TIMESTAMP = 22,
    DLT860_QUALITY = 23,
    DLT860_CHECK = 24,
    DLT860_CODEDENUM = 25,
    DLT860_GENERIC_BITSTRING = 26,
    DLT860_CONSTRUCTED = 27,
    DLT860_ENTRY_TIME = 28,
    DLT860_PHYCOMADDR = 29,
    DLT860_CURRENCY = 30,
    DLT860_OPTFLDS = 31, /* bit-string(10) */
    DLT860_TRGOPS = 32, /* bit-string(6) */
    DLT860_DBPOS = 33,
    DLT860_TCMD = 34

#if (CONFIG_IEC61850_USE_COMPAT_TYPE_DECLARATIONS == 1)
	,
    BOOLEAN = 0,/* int */
    INT8 = 1,   /* int8_t */
    INT16 = 2,  /* int16_t */
    INT32 = 3,  /* int32_t */
    INT64 = 4,  /* int64_t */
    INT128 = 5, /* no native mapping! */
    INT8U = 6,  /* uint8_t */
    INT16U = 7, /* uint16_t */
    INT24U = 8, /* uint32_t */
    INT32U = 9, /* uint32_t */
    FLOAT32 = 10, /* float */
    FLOAT64 = 11, /* double */
    ENUMERATED = 12,
    OCTET_STRING_64 = 13,
    OCTET_STRING_6 = 14,
    OCTET_STRING_8 = 15,
    VISIBLE_STRING_32 = 16,
    VISIBLE_STRING_64 = 17,
    VISIBLE_STRING_65 = 18,
    VISIBLE_STRING_129 = 19,
    VISIBLE_STRING_255 = 20,
    UNICODE_STRING_255 = 21,
    TIMESTAMP = 22,
    QUALITY = 23,
    CHECK = 24,
    CODEDENUM = 25,
    GENERIC_BITSTRING = 26,
    CONSTRUCTED = 27,
    ENTRY_TIME = 28,
    PHYCOMADDR = 29,
    CURRENCY = 30
    OPTFLDS = 31,
    TRGOPS = 32
#endif
} GspDataAttributeType;

typedef enum {
    GspLogicalDeviceModelType,
    GspLogicalNodeModelType,
    GspDataObjectModelType,
    GspDataAttributeModelType
} GspModelNodeType;

struct sGspIedModel {
    char* name;
    GspLogicalDevice* firstChild;
    GspDataSet* dataSets;
    GspReportControlBlock* rcbs;
    GspGSEControlBlock* gseCBs;
    GspSVControlBlock* svCBs;
    GspSettingGroupControlBlock* sgcbs;
    GspLogControlBlock* lcbs;
    GspLog* logs;
    void (*initializer) (void);
    bool installCacheValue;
};

struct sGspLogicalDevice {
    GspModelNodeType modelType;
    char* name;
    GspModelNode* parent;
    GspModelNode* sibling;
    GspModelNode* firstChild;
    char* iedName;
};

struct sGspModelNode {
    GspModelNodeType modelType;
    char* name;
    GspModelNode* parent;
    GspModelNode* sibling;
    GspModelNode* firstChild;
};

struct sGspLogicalNode {
    GspModelNodeType modelType;
    char* name;
    GspModelNode* parent;
    GspModelNode* sibling;
    GspModelNode* firstChild;
};

struct sGspDataObject {
    GspModelNodeType modelType;
    char* name;
    GspModelNode* parent;
    GspModelNode* sibling;
    GspModelNode* firstChild;

    int elementCount; /* > 0 if this is an array */
    char* cdcType;
};

struct sGspDataAttribute {
    GspModelNodeType modelType;
    char* name;
    GspModelNode* parent;
    GspModelNode* sibling;
    GspModelNode* firstChild;

    int elementCount; /* > 0 if this is an array */

    GspFunctionalConstraint fc;
    GspDataAttributeType type;

    uint8_t triggerOptions; /* TRG_OPT_DATA_CHANGED | TRG_OPT_QUALITY_CHANGED | TRG_OPT_DATA_UPDATE */

    GspMmsValue* mmsValue;

    uint32_t sAddr;
};

typedef struct sGspDataSetEntry {
    char* logicalDeviceName;
    bool isLDNameDynamicallyAllocated;
    char* variableName;
    int index;
    char* componentName;
    GspMmsValue* value;
    struct sGspDataSetEntry* sibling;
} GspDataSetEntry;

struct sGspDataSet {
    char* logicalDeviceName;
    char* name; /* eg. MMXU1$dataset1 */
    int elementCount;
    GspDataSetEntry* fcdas;
    vector<GspDataSetEntry*> fcdaArray;
    GspDataSet* sibling;
    set<GspReportControl *> rcSet;
    string refer;
    char *iedName;
};

struct sGspReportControlBlock {
    GspLogicalNode* parent;
    char* name;
    char* rptId;
    bool buffered;
    char* dataSetName; /* pre loaded with relative name in logical node */

    uint32_t confRef; /* ConfRef - configuration revision */
    uint8_t trgOps; /* TrgOps - trigger conditions */
    uint8_t options; /* OptFlds */
    uint32_t bufferTime; /* BufTm - time to buffer events until a report is generated */
    uint32_t intPeriod; /* IntgPd - integrity period */

    /* type (first byte) and address of the pre-configured client
       type can be one of (0 - no reservation, 4 - IPv4 client, 6 - IPv6 client) */
    uint8_t clientReservation[17];

    GspReportControlBlock* sibling; /* next control block in list or NULL if this is the last entry */
};

struct sGspLogControlBlock {
    GspLogicalNode* parent;
    char* name;
    char* dataSetName;
    char* logRef;        /* object reference to the journal. Defaults to <MMS DomainName>/<LNName>$GeneralLog */
    uint8_t trgOps;      /* TrgOps - trigger conditions */
    uint32_t intPeriod;  /* IntgPd - integrity period */
    bool logEna;         /* enable log by default */
    bool reasonCode;     /* include reason code in log */
    GspLogControlBlock* sibling; /* next control block in list or NULL if this is the last entry */
};

struct sGspLog {
    GspLogicalNode* parent;
    char* name;
    GspLog* sibling; /* next log instance in list or NULL if this is the last entry */
};

struct sGspSettingGroupControlBlock {
    GspLogicalNode* parent;

    uint8_t actSG;       /* value from SCL file */
    uint8_t numOfSGs;    /* value from SCL file */

    uint8_t editSG;      /* 0 at power-up */
    bool cnfEdit;        /* false at power-up */
    uint64_t timestamp;
    uint16_t resvTms;

    vector<map<string, Data_t *> > editSgs;

    GspSettingGroupControlBlock* sibling; /* next control block in list or NULL if this is the last entry */
};

struct sGspGSEControlBlock {
    GspLogicalNode* parent;
    char* name;
    char* appId;
    char* dataSetName; /* pre loaded with relative name in logical node */
    uint32_t confRev;  /* ConfRev - configuration revision */
    bool fixedOffs;    /* fixed offsets */
    GspPhyComAddress* address; /* GSE communication parameters */
    int minTime; /* optional minTime parameter --> -1 if not present */
    int maxTime; /* optional maxTime parameter --> -1 if not present */
    GspGSEControlBlock* sibling; /* next control block in list or NULL if this is the last entry */
};

struct sGspSVControlBlock {
    GspLogicalNode* parent;
    char* name;
    char* svId; /* MsvUD/UsvID */
    char* dataSetName; /* pre loaded with relative name in logical node */
    uint8_t optFlds;
    uint8_t smpMod;
    uint16_t smpRate;
    uint32_t confRev;  /* ConfRev - configuration revision */
    GspPhyComAddress* dstAddress; /* SV communication parameters */
    bool isUnicast;
    int noASDU;
    GspSVControlBlock* sibling; /* next control block in list or NULL if this is the last entry */
};



LIB860_API int GspModelNode_getChildCount(GspModelNode* self);

LIB860_API GspModelNode* GspModelNode_getChild(GspModelNode* self, const char* name);

LIB860_API GspModelNode* GspModelNode_getChildWithFc(GspModelNode* self, const char* name, GspFunctionalConstraint fc);

LIB860_API char* GspModelNode_getObjectReference(GspModelNode* self, char* objectReference);
LIB860_API string GspModelNode_getObjectReference(GspModelNode* self);

LIB860_API GspModelNodeType GspModelNode_getType(GspModelNode* self);

LIB860_API void GspIedModel_setIedName(GspIedModel* self, const char* iedName);

LIB860_API GspModelNode* GspIedModel_getModelNodeByObjectReference(GspIedModel* self, const char* objectReference);
LIB860_API GspModelNode* GspIedModel_getModelNodeByReference(GspIedModel* self, const char* objectReference, const char *fc);

//LIB860_API GspSVControlBlock* GspIedModel_getSVControlBlock(GspIedModel* self, GspLogicalNode* parentLN, const char* svcbName);

LIB860_API GspModelNode* GspIedModel_getModelNodeByShortObjectReference(GspIedModel* self, const char* objectReference);

LIB860_API GspModelNode* GspIedModel_getModelNodeByShortAddress(GspIedModel* self, uint32_t shortAddress);

LIB860_API GspLogicalDevice* GspIedModel_getDeviceByInst(GspIedModel* self, const char* ldInst);

LIB860_API GspLogicalDevice* GspIedModel_getDeviceByIndex(GspIedModel* self, int index);

LIB860_API GspLogicalNode* GspLogicalDevice_getLogicalNode(GspLogicalDevice* self, const char* lnName);

LIB860_API GspSettingGroupControlBlock* GspLogicalDevice_getSettingGroupControlBlock(GspLogicalDevice* self);

LIB860_API void GspIedModel_setAttributeValuesToNull(GspIedModel* self);

LIB860_API GspLogicalDevice* GspIedModel_getDevice(GspIedModel* self, const char* ldName);

LIB860_API GspDataSet* GspIedModel_lookupDataSetFromModels(GspIedModel** self, const char* dataSetReference);

LIB860_API GspDataSet* GspIedModel_lookupDataSet(GspIedModel* self, const char* dataSetReference);

LIB860_API GspDataAttribute* GspIedModel_lookupDataAttributeByMmsValue(GspIedModel* self, GspMmsValue* value);

LIB860_API int GspIedModel_getLogicalDeviceCount(GspIedModel* self);

LIB860_API int GspLogicalDevice_getLogicalNodeCount(GspLogicalDevice* self);

LIB860_API GspModelNode* GspLogicalDevice_getChildByMmsVariableName(GspLogicalDevice* self, const char* mmsVariableName);

LIB860_API bool GspLogicalNode_hasFCData(GspLogicalNode* self, GspFunctionalConstraint fc);

//LIB860_API bool GspLogicalNode_hasBufferedReports(GspLogicalNode* self);

//LIB860_API bool GspLogicalNode_hasUnbufferedReports(GspLogicalNode* self);

LIB860_API GspDataSet* GspLogicalNode_getDataSet(GspLogicalNode* self, const char* dataSetName);

LIB860_API bool GspDataObject_hasFCData(GspDataObject* self, GspFunctionalConstraint fc);

LIB860_API void GspDataObject_getFCDA(GspDataObject *self, GspFunctionalConstraint fc, vector<GspDataAttribute *> &daVec);

LIB860_API string GspIedModel_getDataTypeStr(int type);
#endif /* GSP_MODEL_H_ */
