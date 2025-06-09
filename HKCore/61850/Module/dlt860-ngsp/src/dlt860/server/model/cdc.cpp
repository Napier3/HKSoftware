/*
 *  cdc.c
 */

#include "dlt860_dynamic_model.h"
#include "dlt860_cdc.h"
#include "libdlt860_platform_includes.h"

/************************************************
 * Constructed Attribute Classes
 ***********************************************/

GspDataAttribute*
GspCAC_AnalogueValue_create(const char* name, GspModelNode* parent, GspFunctionalConstraint fc, uint8_t triggerOptions,
        bool isIntegerNotFloat)
{
    GspDataAttribute* analogeValue = GspDataAttribute_create(name, parent, DLT860_CONSTRUCTED, fc, triggerOptions, 0, 0);

    if (isIntegerNotFloat)
        GspDataAttribute_create("i", (GspModelNode*) analogeValue, DLT860_INT32, fc, triggerOptions, 0, 0);
    else
        GspDataAttribute_create("f", (GspModelNode*) analogeValue, DLT860_FLOAT32, fc, triggerOptions, 0, 0);

    return analogeValue;
}

GspDataAttribute*
GspCAC_ValWithTrans_create(const char* name, GspModelNode* parent, GspFunctionalConstraint fc, uint8_t triggerOptions, bool hasTransientIndicator)
{
    GspDataAttribute* valWithTrans = GspDataAttribute_create(name, parent, DLT860_CONSTRUCTED, fc, triggerOptions, 0, 0);

    GspDataAttribute_create("posVal", (GspModelNode*) valWithTrans, DLT860_INT8, fc, triggerOptions, 0, 0);

    if (hasTransientIndicator)
        GspDataAttribute_create("transInd", (GspModelNode*) valWithTrans, DLT860_BOOLEAN, fc, triggerOptions, 0, 0);

    return valWithTrans;
}

/**
 * CDC_OPTION_AC_CLC_O
 */
GspDataAttribute*
GspCAC_Vector_create(const char* name, GspModelNode* parent, uint32_t options, GspFunctionalConstraint fc, uint8_t triggerOptions)
{
    GspDataAttribute* vector = GspDataAttribute_create(name, parent, DLT860_CONSTRUCTED, fc, triggerOptions, 0, 0);

    GspCAC_AnalogueValue_create("mag", (GspModelNode*) vector, fc, triggerOptions, false);

    if (options & GSP_CDC_OPTION_AC_CLC_O)
        GspCAC_AnalogueValue_create("ang", (GspModelNode*) vector, fc, triggerOptions, false);

    return vector;
}

GspDataAttribute*
GspCAC_Point_create(const char* name, GspModelNode* parent, GspFunctionalConstraint fc, uint8_t triggerOptions, bool hasZVal)
{
    GspDataAttribute* point = GspDataAttribute_create(name, parent, DLT860_CONSTRUCTED, fc, triggerOptions, 0, 0);

    GspDataAttribute_create("xVal", (GspModelNode*) point, DLT860_FLOAT32, fc, triggerOptions, 0, 0);
    GspDataAttribute_create("yVal", (GspModelNode*) point, DLT860_FLOAT32, fc, triggerOptions, 0, 0);

    if (hasZVal)
        GspDataAttribute_create("zVal", (GspModelNode*) point, DLT860_FLOAT32, fc, triggerOptions, 0, 0);

    return point;
}

GspDataAttribute*
GspCAC_ScaledValueConfig_create(const char* name, GspModelNode* parent)
{
    GspDataAttribute* scaling = GspDataAttribute_create(name, parent, DLT860_CONSTRUCTED, DLT860_FC_CF, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    GspDataAttribute_create("scaleFactor", (GspModelNode*) scaling, DLT860_FLOAT32, DLT860_FC_CF, GSP_TRG_OPT_DATA_CHANGED, 0, 0);
    GspDataAttribute_create("offset", (GspModelNode*) scaling, DLT860_FLOAT32, DLT860_FC_CF, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    return scaling;
}

GspDataAttribute*
GspCAC_Unit_create(const char* name, GspModelNode* parent, bool hasMagnitude)
{
    GspDataAttribute* unit = GspDataAttribute_create(name, parent, DLT860_CONSTRUCTED, DLT860_FC_CF, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    GspDataAttribute_create("SIUnit", (GspModelNode*) unit, DLT860_ENUMERATED, DLT860_FC_CF, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    if (hasMagnitude)
        GspDataAttribute_create("multiplier", (GspModelNode*) unit, DLT860_ENUMERATED, DLT860_FC_CF, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    return unit;
}

/************************************************
 *  Control parameters
 ************************************************/

static void
addOriginator(char* name, GspModelNode* parent, GspFunctionalConstraint fc)
{
    GspDataAttribute* origin = GspDataAttribute_create(name, parent, DLT860_CONSTRUCTED, fc, 0 ,0 ,0);

    GspDataAttribute_create("orCat", (GspModelNode*) origin, DLT860_ENUMERATED, fc, 0, 0, 0);
    GspDataAttribute_create("orIdent", (GspModelNode*) origin, DLT860_OCTET_STRING_64, fc, 0, 0, 0);

}

static void
addGenericOperateElements(GspDataAttribute* oper, GspDataAttributeType type, bool isTimeActivated, bool hasCheck)
{
    GspDataAttribute_create("ctlVal", (GspModelNode*) oper, type, DLT860_FC_CO, 0, 0, 0);

    if (isTimeActivated)
        GspDataAttribute_create("operTm", (GspModelNode*) oper, DLT860_TIMESTAMP, DLT860_FC_CO, 0, 0, 0);

    addOriginator(std::string("origin").data(), (GspModelNode*) oper, DLT860_FC_CO);

    GspDataAttribute_create("ctlNum", (GspModelNode*) oper, DLT860_INT8U, DLT860_FC_CO, 0, 0, 0);
    GspDataAttribute_create("T", (GspModelNode*) oper, DLT860_TIMESTAMP, DLT860_FC_CO, 0, 0, 0);
    GspDataAttribute_create("Test", (GspModelNode*) oper, DLT860_BOOLEAN, DLT860_FC_CO, 0, 0, 0);

    if (hasCheck)
        GspDataAttribute_create("Check", (GspModelNode*) oper, DLT860_CHECK, DLT860_FC_CO, 0, 0, 0);
}

static void
addCommonOperateElements(GspDataAttribute* oper, bool isTimeActivated, bool hasCheck)
{
    if (isTimeActivated)
        GspDataAttribute_create("operTm", (GspModelNode*) oper, DLT860_TIMESTAMP, DLT860_FC_CO, 0, 0, 0);

    addOriginator(std::string("origin").data(), (GspModelNode*) oper, DLT860_FC_CO);

    GspDataAttribute_create("ctlNum", (GspModelNode*) oper, DLT860_INT8U, DLT860_FC_CO, 0, 0, 0);
    GspDataAttribute_create("T", (GspModelNode*) oper, DLT860_TIMESTAMP, DLT860_FC_CO, 0, 0, 0);
    GspDataAttribute_create("Test", (GspModelNode*) oper, DLT860_BOOLEAN, DLT860_FC_CO, 0, 0, 0);

    if (hasCheck)
        GspDataAttribute_create("Check", (GspModelNode*) oper, DLT860_CHECK, DLT860_FC_CO, 0, 0, 0);
}

static GspDataAttribute*
CDA_Oper(GspModelNode* parent, GspDataAttributeType type, bool isTImeActivated)
{
    GspDataAttribute* oper =  GspDataAttribute_create("Oper", parent, DLT860_CONSTRUCTED, DLT860_FC_CO, 0, 0, 0);

    addGenericOperateElements(oper, type, isTImeActivated, true);

    return oper;
}

static GspDataAttribute*
CDA_SBOw(GspModelNode* parent, GspDataAttributeType type, bool isTImeActivated)
{
    GspDataAttribute* oper =  GspDataAttribute_create("SBOw", parent, DLT860_CONSTRUCTED, DLT860_FC_CO, 0, 0, 0);

    addGenericOperateElements(oper, type, isTImeActivated, true);

    return oper;
}

static GspDataAttribute*
CDA_Cancel(GspModelNode* parent, GspDataAttributeType type, bool isTImeActivated)
{
    GspDataAttribute* oper =  GspDataAttribute_create("Cancel", parent, DLT860_CONSTRUCTED, DLT860_FC_CO, 0, 0, 0);

    addGenericOperateElements(oper, type, isTImeActivated, false);

    return oper;
}



/************************************************
 * Common Data Classes - helper functions
 ***********************************************/

static void
CDC_addTimeQuality(GspDataObject* dataObject, GspFunctionalConstraint fc)
{
    GspDataAttribute_create("q", (GspModelNode*) dataObject, DLT860_QUALITY, fc, GSP_TRG_OPT_QUALITY_CHANGED, 0, 0);
    GspDataAttribute_create("t", (GspModelNode*) dataObject, DLT860_TIMESTAMP, fc, 0, 0, 0);
}

static void
CDC_addStatusToDataObject(GspDataObject* dataObject, GspDataAttributeType statusType)
{
    GspDataAttribute_create("stVal", (GspModelNode*) dataObject, statusType, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED | GSP_TRG_OPT_DATA_UPDATE, 0, 0);
    CDC_addTimeQuality(dataObject, DLT860_FC_ST);
}

static void
CDC_addOptionPicsSubst(GspDataObject* dataObject, GspDataAttributeType type)
{
    GspDataAttribute_create("subEna", (GspModelNode*) dataObject, DLT860_BOOLEAN, DLT860_FC_SV, 0, 0, 0);
    GspDataAttribute_create("subVal", (GspModelNode*) dataObject, type, DLT860_FC_SV, 0, 0, 0);
    GspDataAttribute_create("subQ", (GspModelNode*) dataObject, DLT860_QUALITY, DLT860_FC_SV, 0, 0, 0);
    GspDataAttribute_create("subID", (GspModelNode*) dataObject, DLT860_VISIBLE_STRING_64, DLT860_FC_SV, 0, 0, 0);
}

static void
CDC_addOptionPicsSubstValWithTrans(GspDataObject* dataObject, bool hasTransientIndicator)
{
    GspDataAttribute_create("subEna", (GspModelNode*) dataObject, DLT860_BOOLEAN, DLT860_FC_SV, 0, 0, 0);

    GspCAC_ValWithTrans_create("subVal", (GspModelNode*) dataObject, DLT860_FC_SV, 0, hasTransientIndicator);

    GspDataAttribute_create("subQ", (GspModelNode*) dataObject, DLT860_QUALITY, DLT860_FC_SV, 0, 0, 0);
    GspDataAttribute_create("subID", (GspModelNode*) dataObject, DLT860_VISIBLE_STRING_64, DLT860_FC_SV, 0, 0, 0);
}

/* Add optional attributes for extension (name spaces) and textual descriptions */
static void
CDC_addStandardOptions(GspDataObject* dataObject, uint32_t options)
{
    /* Standard options ? */
    if (options & GSP_CDC_OPTION_DESC)
        GspDataAttribute_create("d",(GspModelNode*)  dataObject, DLT860_VISIBLE_STRING_255, DLT860_FC_DC, 0, 0, 0);

    if (options & GSP_CDC_OPTION_DESC_UNICODE)
        GspDataAttribute_create("dU", (GspModelNode*) dataObject, DLT860_UNICODE_STRING_255, DLT860_FC_DC, 0, 0, 0);

    if (options & GSP_CDC_OPTION_AC_DLNDA) {
        GspDataAttribute_create("cdcNs", (GspModelNode*) dataObject, DLT860_VISIBLE_STRING_255, DLT860_FC_EX, 0, 0, 0);
        GspDataAttribute_create("cdcName", (GspModelNode*) dataObject, DLT860_VISIBLE_STRING_255, DLT860_FC_EX, 0, 0, 0);
    }

    if (options & GSP_CDC_OPTION_AC_DLN)
        GspDataAttribute_create("dataNs", (GspModelNode*) dataObject, DLT860_VISIBLE_STRING_255, DLT860_FC_EX, 0, 0, 0);
}

/************************************************
 * Common Data Classes - constructors
 ***********************************************/

GspDataObject*
GspCDC_SPS_create(const char* dataObjectName, GspModelNode* parent, uint32_t options)
{
    GspDataObject* newSPS = GspDataObject_create(dataObjectName, parent, 0);

    CDC_addStatusToDataObject(newSPS, DLT860_BOOLEAN);

    if (options & GSP_CDC_OPTION_PICS_SUBST)
        CDC_addOptionPicsSubst(newSPS, DLT860_BOOLEAN);

    if (options & GSP_CDC_OPTION_BLK_ENA)
        GspDataAttribute_create("blkEna", (GspModelNode*) newSPS, DLT860_BOOLEAN, DLT860_FC_BL, 0, 0, 0);

    CDC_addStandardOptions(newSPS, options);

    return newSPS;
}

GspDataObject*
GspCDC_DPS_create(const char* dataObjectName, GspModelNode* parent, uint32_t options)
{
    GspDataObject* newDPS = GspDataObject_create(dataObjectName, parent, 0);

    CDC_addStatusToDataObject(newDPS, DLT860_CODEDENUM);

    if (options & GSP_CDC_OPTION_PICS_SUBST)
        CDC_addOptionPicsSubst(newDPS, DLT860_CODEDENUM);

    if (options & GSP_CDC_OPTION_BLK_ENA)
        GspDataAttribute_create("blkEna", (GspModelNode*) newDPS, DLT860_BOOLEAN, DLT860_FC_BL, 0, 0, 0);

    CDC_addStandardOptions(newDPS, options);

    return newDPS;
}

GspDataObject*
GspCDC_INS_create(const char* dataObjectName, GspModelNode* parent, uint32_t options)
{
    GspDataObject* newINS = GspDataObject_create(dataObjectName, parent, 0);

    CDC_addStatusToDataObject(newINS, DLT860_INT32);

    if (options & GSP_CDC_OPTION_PICS_SUBST)
        CDC_addOptionPicsSubst(newINS, DLT860_INT32);

    if (options & GSP_CDC_OPTION_BLK_ENA)
        GspDataAttribute_create("blkEna", (GspModelNode*) newINS, DLT860_BOOLEAN, DLT860_FC_BL, 0, 0, 0);

    CDC_addStandardOptions(newINS, options);

    return newINS;
}


GspDataObject*
GspCDC_ENS_create(const char* dataObjectName, GspModelNode* parent, uint32_t options)
{
    GspDataObject* newENS = GspDataObject_create(dataObjectName, parent, 0);

    CDC_addStatusToDataObject(newENS, DLT860_ENUMERATED);

    if (options & GSP_CDC_OPTION_PICS_SUBST)
        CDC_addOptionPicsSubst(newENS, DLT860_ENUMERATED);

    if (options & GSP_CDC_OPTION_BLK_ENA)
        GspDataAttribute_create("blkEna", (GspModelNode*) newENS, DLT860_BOOLEAN, DLT860_FC_BL, 0, 0, 0);

    CDC_addStandardOptions(newENS, options);

    return newENS;
}

GspDataObject*
GspCDC_BCR_create(const char* dataObjectName, GspModelNode* parent, uint32_t options)
{
    GspDataObject* newBCR = GspDataObject_create(dataObjectName, parent, 0);

    GspDataAttribute_create("actVal", (GspModelNode*) newBCR, DLT860_INT64, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    if (options & GSP_CDC_OPTION_FROZEN_VALUE) {
        GspDataAttribute_create("frVal", (GspModelNode*) newBCR, DLT860_INT64, DLT860_FC_ST, GSP_TRG_OPT_DATA_UPDATE, 0, 0);
        GspDataAttribute_create("frTm", (GspModelNode*) newBCR, DLT860_TIMESTAMP, DLT860_FC_ST, 0, 0, 0);
    }

    CDC_addTimeQuality(newBCR, DLT860_FC_ST);

    if (options & GSP_CDC_OPTION_UNIT)
        GspDataAttribute_create("units", (GspModelNode*) newBCR, DLT860_ENUMERATED, DLT860_FC_CF, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    GspDataAttribute_create("pulsQty", (GspModelNode*) newBCR, DLT860_FLOAT32, DLT860_FC_CF, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    if (options & GSP_CDC_OPTION_FROZEN_VALUE) {
        GspDataAttribute_create("frEna", (GspModelNode*) newBCR, DLT860_BOOLEAN, DLT860_FC_CF, GSP_TRG_OPT_DATA_CHANGED, 0, 0);
        GspDataAttribute_create("strTm", (GspModelNode*) newBCR, DLT860_TIMESTAMP, DLT860_FC_CF, GSP_TRG_OPT_DATA_CHANGED, 0, 0);
        GspDataAttribute_create("frPd", (GspModelNode*) newBCR, DLT860_INT32, DLT860_FC_CF, GSP_TRG_OPT_DATA_CHANGED, 0, 0);
        GspDataAttribute_create("frRs", (GspModelNode*) newBCR, DLT860_BOOLEAN, DLT860_FC_CF, GSP_TRG_OPT_DATA_CHANGED, 0, 0);
    }

    CDC_addStandardOptions(newBCR, options);

    return newBCR;
}

GspDataObject*
GspCDC_SEC_create(const char* dataObjectName, GspModelNode* parent, uint32_t options)
{
    GspDataObject* newSEC = GspDataObject_create(dataObjectName, parent, 0);

    GspDataAttribute_create("cnt", (GspModelNode*) newSEC, DLT860_INT32U, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 0, 0);
    GspDataAttribute_create("sev", (GspModelNode*) newSEC, DLT860_ENUMERATED, DLT860_FC_ST, 0, 0, 0);
    GspDataAttribute_create("t", (GspModelNode*) newSEC, DLT860_TIMESTAMP, DLT860_FC_ST, 0, 0, 0);

    if (options & GSP_CDC_OPTION_ADDR)
        GspDataAttribute_create("addr", (GspModelNode*) newSEC, DLT860_OCTET_STRING_64, DLT860_FC_ST, 0, 0, 0);

    if (options & GSP_CDC_OPTION_ADDINFO)
        GspDataAttribute_create("addInfo", (GspModelNode*) newSEC, DLT860_VISIBLE_STRING_64, DLT860_FC_ST, 0, 0, 0);

    CDC_addStandardOptions(newSEC, options);

    return newSEC;
}


GspDataObject*
GspCDC_VSS_create(const char* dataObjectName, GspModelNode* parent, uint32_t options)
{
    GspDataObject* newSPS = GspDataObject_create(dataObjectName, parent, 0);

    CDC_addStatusToDataObject(newSPS, DLT860_VISIBLE_STRING_255);

    if (options & GSP_CDC_OPTION_PICS_SUBST)
        CDC_addOptionPicsSubst(newSPS, DLT860_BOOLEAN);

    if (options & GSP_CDC_OPTION_BLK_ENA)
        GspDataAttribute_create("blkEna", (GspModelNode*) newSPS, DLT860_BOOLEAN, DLT860_FC_BL, 0, 0, 0);

    CDC_addStandardOptions(newSPS, options);

    return newSPS;
}

/**
 * CDC_OPTION_INST_MAG
 * CDC_OPTION_RANGE
 * CDC_OPTION_PICS_SUBST
 */
GspDataObject*
GspCDC_MV_create(const char* dataObjectName, GspModelNode* parent, uint32_t options, bool isIntegerNotFloat)
{
    GspDataObject* newMV = GspDataObject_create(dataObjectName, parent, 0);

    if (options & GSP_CDC_OPTION_INST_MAG)
        GspCAC_AnalogueValue_create("instMag", (GspModelNode*) newMV, DLT860_FC_MX, 0, isIntegerNotFloat);

    GspCAC_AnalogueValue_create("mag", (GspModelNode*) newMV, DLT860_FC_MX, GSP_TRG_OPT_DATA_CHANGED | GSP_TRG_OPT_DATA_UPDATE, isIntegerNotFloat);

    if (options & GSP_CDC_OPTION_RANGE)
        GspDataAttribute_create("range", (GspModelNode*) newMV, DLT860_ENUMERATED, DLT860_FC_MX, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    CDC_addTimeQuality(newMV, DLT860_FC_MX);

/*
    if (options & CDC_OPTION_PICS_SUBST)
        CDC_addOptionPicsSubst(newMV, )
*/

    CDC_addStandardOptions(newMV, options);

    return newMV;
}

/**
 * CDC_OPTION_INST_MAG
 * CDC_OPTION_RANGE
 */
GspDataObject*
GspCDC_CMV_create(const char* dataObjectName, GspModelNode* parent, uint32_t options)
{
    GspDataObject* newMV = GspDataObject_create(dataObjectName, parent, 0);

    if (options & GSP_CDC_OPTION_INST_MAG)
        GspCAC_Vector_create("instCVal", (GspModelNode*) newMV, options, DLT860_FC_MX, 0);

    GspCAC_Vector_create("cVal", (GspModelNode*) newMV, options, DLT860_FC_MX, GSP_TRG_OPT_DATA_CHANGED | GSP_TRG_OPT_DATA_UPDATE);

    if (options & GSP_CDC_OPTION_RANGE)
        GspDataAttribute_create("range", (GspModelNode*) newMV, DLT860_ENUMERATED, DLT860_FC_MX, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    if (options & GSP_CDC_OPTION_RANGE_ANG)
           GspDataAttribute_create("rangeAng", (GspModelNode*) newMV, DLT860_ENUMERATED, DLT860_FC_MX, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    CDC_addTimeQuality(newMV, DLT860_FC_MX);

/*    if (options & CDC_OPTION_PICS_SUBST)
        CDC_addOptionPicsSubst(newMV, )*/

    CDC_addStandardOptions(newMV, options);

    return newMV;
}


/**
 * CDC_OPTION_UNIT
 * CDC_OPTION_AC_SCAV
 * CDC_OPTION_MIN
 * CDC_OPTION_MAX
 */
GspDataObject*
GspCDC_SAV_create(const char* dataObjectName, GspModelNode* parent, uint32_t options, bool isIntegerNotFloat)
{
    GspDataObject* newSAV = GspDataObject_create(dataObjectName, parent, 0);

    GspCAC_AnalogueValue_create("instMag", (GspModelNode*) newSAV, DLT860_FC_MX, 0, isIntegerNotFloat);

    CDC_addTimeQuality(newSAV, DLT860_FC_MX);

    if (options & GSP_CDC_OPTION_UNIT)
        GspCAC_Unit_create("units", (GspModelNode*) newSAV, options & GSP_CDC_OPTION_UNIT_MULTIPLIER);

    if (options & GSP_CDC_OPTION_AC_SCAV)
        GspCAC_ScaledValueConfig_create("sVC", (GspModelNode*) newSAV);

    if (options & GSP_CDC_OPTION_MIN)
        GspCAC_AnalogueValue_create("min", (GspModelNode*) newSAV, DLT860_FC_CF, GSP_TRG_OPT_DATA_CHANGED, isIntegerNotFloat);

    if (options & GSP_CDC_OPTION_MAX)
        GspCAC_AnalogueValue_create("max", (GspModelNode*) newSAV, DLT860_FC_CF, GSP_TRG_OPT_DATA_CHANGED, isIntegerNotFloat);

    CDC_addStandardOptions(newSAV, options);

    return newSAV;
}

GspDataObject*
GspCDC_HST_create(const char* dataObjectName, GspModelNode* parent, uint32_t options, uint16_t maxPts)
{
    GspDataObject* newHST = GspDataObject_create(dataObjectName, parent, 0);

    GspDataAttribute_create("hstVal", (GspModelNode*) newHST, DLT860_INT32, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED | GSP_TRG_OPT_DATA_UPDATE, maxPts, 0);

    CDC_addTimeQuality(newHST, DLT860_FC_ST);

    GspDataAttribute_create("numPts", (GspModelNode*) newHST, DLT860_INT16U, DLT860_FC_CF, 0, 0, 0);

    /* TODO add mandatory attribute "hstRangeC" */

    GspCAC_Unit_create("units", (GspModelNode*) newHST, options & GSP_CDC_OPTION_UNIT_MULTIPLIER);

    GspDataAttribute_create("maxPts", (GspModelNode*) newHST, DLT860_INT16U, DLT860_FC_CF, 0, 0, 0);

    CDC_addStandardOptions(newHST, options);

    return newHST;
}


static void
addControls(GspDataObject* parent, GspDataAttributeType type, uint32_t controlOptions)
{
    GspDataAttribute* ctlModel =
            GspDataAttribute_create("ctlModel", (GspModelNode*) parent, DLT860_ENUMERATED, DLT860_FC_CF, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    int controlModel = controlOptions & 0x07;

    ctlModel->mmsValue = GspMmsValue_newIntegerFromInt16(controlModel);

    if (controlModel > 0) {

        if (controlModel == GSP_CDC_CTL_MODEL_SBO_NORMAL)
            GspDataAttribute_create("SBO", (GspModelNode*) parent, DLT860_VISIBLE_STRING_129, DLT860_FC_CO, 0, 0, 0);

        bool isTimeActivated = false;

        if (controlOptions & GSP_CDC_CTL_MODEL_IS_TIME_ACTIVATED)
            isTimeActivated = true;

        if (controlModel == GSP_CDC_CTL_MODEL_SBO_ENHANCED)
            CDA_SBOw((GspModelNode*) parent, type, isTimeActivated);

        CDA_Oper((GspModelNode*) parent, type, isTimeActivated);

        if (controlOptions & GSP_CDC_CTL_MODEL_HAS_CANCEL)
            CDA_Cancel((GspModelNode*) parent, type, isTimeActivated);

    }
}

static void
addOriginatorAndCtlNumOptions(GspModelNode* parent, uint32_t controlOptions)
{
    if (controlOptions & GSP_CDC_CTL_OPTION_ORIGIN)
        addOriginator(std::string("origin").data(), parent, DLT860_FC_ST);

    if (controlOptions & GSP_CDC_CTL_OPTION_CTL_NUM)
        GspDataAttribute_create("ctlNum", parent, DLT860_INT8U, DLT860_FC_ST, 0, 0, 0);
}

static void
addCommonControlAttributes(GspDataObject* dobj, uint32_t controlOptions)
{
    if (controlOptions & GSP_CDC_CTL_OPTION_OP_RCVD)
        GspDataAttribute_create("opRcvd", (GspModelNode*) dobj, DLT860_BOOLEAN, DLT860_FC_OR, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    if (controlOptions & GSP_CDC_CTL_OPTION_OP_OK)
        GspDataAttribute_create("opOk", (GspModelNode*) dobj, DLT860_BOOLEAN, DLT860_FC_OR, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    if (controlOptions & GSP_CDC_CTL_OPTION_T_OP_OK)
        GspDataAttribute_create("tOpOk", (GspModelNode*) dobj, DLT860_BOOLEAN, DLT860_FC_OR, GSP_TRG_OPT_DATA_CHANGED, 0, 0);
}

/**
 *
 * CDC_OPTION_IS_TIME_ACTICATED
 *
 * substitution options
 * CDC_OPTION_BLK_ENA
 * standard description and namespace options
 *
 */
GspDataObject*
GspCDC_SPC_create(const char* dataObjectName, GspModelNode* parent, uint32_t options, uint32_t controlOptions)
{
    GspDataObject* newSPC = GspDataObject_create(dataObjectName, parent, 0);

    addOriginatorAndCtlNumOptions((GspModelNode*) newSPC, controlOptions);

    CDC_addStatusToDataObject(newSPC, DLT860_BOOLEAN);

    addControls(newSPC, DLT860_BOOLEAN, controlOptions);

    if (controlOptions & GSP_CDC_CTL_OPTION_ST_SELD)
        GspDataAttribute_create("stSeld", (GspModelNode*) newSPC, DLT860_BOOLEAN, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    addCommonControlAttributes(newSPC, controlOptions);

    if (options & GSP_CDC_OPTION_PICS_SUBST)
        CDC_addOptionPicsSubst(newSPC, DLT860_BOOLEAN);

    if (options & GSP_CDC_OPTION_BLK_ENA)
        GspDataAttribute_create("blkEna", (GspModelNode*) newSPC, DLT860_BOOLEAN, DLT860_FC_BL, 0, 0, 0);

    CDC_addStandardOptions(newSPC, options);

    return newSPC;
}

/**
 *
 * CDC_OPTION_IS_TIME_ACTICATED
 *
 * substitution options
 * CDC_OPTION_BLK_ENA
 * standard description and namespace options
 *
 */
GspDataObject*
GspCDC_DPC_create(const char* dataObjectName, GspModelNode* parent, uint32_t options, uint32_t controlOptions)
{
    GspDataObject* newDPC = GspDataObject_create(dataObjectName, parent, 0);

    addOriginatorAndCtlNumOptions((GspModelNode*) newDPC, controlOptions);

    CDC_addStatusToDataObject(newDPC, DLT860_CODEDENUM);

    addControls(newDPC, DLT860_BOOLEAN, controlOptions);

    if (controlOptions & GSP_CDC_CTL_OPTION_ST_SELD)
        GspDataAttribute_create("stSeld", (GspModelNode*) newDPC, DLT860_BOOLEAN, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    addCommonControlAttributes(newDPC, controlOptions);

    if (options & GSP_CDC_OPTION_PICS_SUBST)
        CDC_addOptionPicsSubst(newDPC, DLT860_CODEDENUM);

    if (options & GSP_CDC_OPTION_BLK_ENA)
        GspDataAttribute_create("blkEna", (GspModelNode*) newDPC, DLT860_BOOLEAN, DLT860_FC_BL, 0, 0, 0);

    CDC_addStandardOptions(newDPC, options);

    return newDPC;
}

static void
addAnalogControls(GspDataObject* parent, uint32_t controlOptions, bool isIntegerNotFloat)
{
    GspDataAttribute* ctlModel =
            GspDataAttribute_create("ctlModel", (GspModelNode*) parent, DLT860_ENUMERATED, DLT860_FC_CF, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    int controlModel = controlOptions & 0x07;

    ctlModel->mmsValue = GspMmsValue_newIntegerFromInt16(controlModel);

    if (controlModel != GSP_CDC_CTL_MODEL_NONE) {

        if (controlModel == GSP_CDC_CTL_MODEL_SBO_NORMAL)
            GspDataAttribute_create("SBO", (GspModelNode*) parent, DLT860_VISIBLE_STRING_129, DLT860_FC_CO, 0, 0, 0);

        bool isTimeActivated = false;

        if (controlOptions & GSP_CDC_CTL_MODEL_IS_TIME_ACTIVATED)
            isTimeActivated = true;

        if (controlModel == GSP_CDC_CTL_MODEL_SBO_ENHANCED) {
            GspDataAttribute* sBOw =  GspDataAttribute_create("SBOw", (GspModelNode*) parent, DLT860_CONSTRUCTED, DLT860_FC_CO, 0, 0, 0);

            GspCAC_AnalogueValue_create("ctlVal", (GspModelNode*) sBOw, DLT860_FC_CO, 0, isIntegerNotFloat);

            addCommonOperateElements(sBOw, isTimeActivated, true);
        }

        GspDataAttribute* oper =  GspDataAttribute_create("Oper", (GspModelNode*) parent, DLT860_CONSTRUCTED, DLT860_FC_CO, 0, 0, 0);

        GspCAC_AnalogueValue_create("ctlVal", (GspModelNode*) oper, DLT860_FC_CO, 0, isIntegerNotFloat);

        addCommonOperateElements(oper, isTimeActivated, true);

        if (controlOptions & GSP_CDC_CTL_MODEL_HAS_CANCEL) {
            GspDataAttribute* cancel =  GspDataAttribute_create("SBOw", (GspModelNode*) parent, DLT860_CONSTRUCTED, DLT860_FC_CO, 0, 0, 0);

            GspCAC_AnalogueValue_create("ctlVal", (GspModelNode*) cancel, DLT860_FC_CO, 0, isIntegerNotFloat);

            addCommonOperateElements(cancel, isTimeActivated, true);
        }

    }
}

static void
addControlStatusAttributesForAnalogControl(GspDataObject* dobj, uint32_t controlOptions)
{
    if (controlOptions & GSP_CDC_CTL_OPTION_ORIGIN)
        addOriginator(std::string("origin").data(), (GspModelNode*) dobj, DLT860_FC_MX);

    if (controlOptions & GSP_CDC_CTL_OPTION_CTL_NUM)
        GspDataAttribute_create("ctlNum", (GspModelNode*) dobj, DLT860_INT8U, DLT860_FC_MX, 0, 0, 0);
}

GspDataObject*
GspCDC_APC_create(const char* dataObjectName, GspModelNode* parent, uint32_t options, uint32_t controlOptions, bool isIntegerNotFloat)
{
    GspDataObject* newAPC = GspDataObject_create(dataObjectName, parent, 0);

    addControlStatusAttributesForAnalogControl(newAPC, controlOptions);

    GspCAC_AnalogueValue_create("mxVal", (GspModelNode*) newAPC, DLT860_FC_MX, GSP_TRG_OPT_DATA_CHANGED, isIntegerNotFloat);

    CDC_addTimeQuality(newAPC, DLT860_FC_MX);

    if (controlOptions & GSP_CDC_CTL_OPTION_ST_SELD)
        GspDataAttribute_create("stSeld", (GspModelNode*) newAPC, DLT860_BOOLEAN, DLT860_FC_MX, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    addCommonControlAttributes(newAPC, controlOptions);

    if (options & GSP_CDC_OPTION_PICS_SUBST) {
        GspDataAttribute_create("subEna", (GspModelNode*) newAPC, DLT860_BOOLEAN, DLT860_FC_SV, 0, 0, 0);
        GspCAC_AnalogueValue_create("subVal", (GspModelNode*) newAPC, DLT860_FC_SV, 0, isIntegerNotFloat);
        GspDataAttribute_create("subQ", (GspModelNode*) newAPC, DLT860_QUALITY, DLT860_FC_SV, 0, 0, 0);
        GspDataAttribute_create("subID", (GspModelNode*) newAPC, DLT860_VISIBLE_STRING_64, DLT860_FC_SV, 0, 0, 0);
    }

    if (options & GSP_CDC_OPTION_BLK_ENA)
        GspDataAttribute_create("blkEna", (GspModelNode*) newAPC, DLT860_BOOLEAN, DLT860_FC_BL, 0, 0, 0);

    addAnalogControls(newAPC, controlOptions, isIntegerNotFloat);

    CDC_addStandardOptions(newAPC, options);

    return newAPC;
}

GspDataObject*
GspCDC_INC_create(const char* dataObjectName, GspModelNode* parent, uint32_t options, uint32_t controlOptions)
{
    GspDataObject* newINC = GspDataObject_create(dataObjectName, parent, 0);

    addOriginatorAndCtlNumOptions((GspModelNode*) newINC, controlOptions);

    CDC_addStatusToDataObject(newINC, DLT860_INT32);

    addControls(newINC, DLT860_INT32, controlOptions);

    if (controlOptions & GSP_CDC_CTL_OPTION_ST_SELD)
        GspDataAttribute_create("stSeld", (GspModelNode*) newINC, DLT860_BOOLEAN, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    addCommonControlAttributes(newINC, controlOptions);

    if (options & GSP_CDC_OPTION_PICS_SUBST)
        CDC_addOptionPicsSubst(newINC, DLT860_INT32);

    if (options & GSP_CDC_OPTION_BLK_ENA)
        GspDataAttribute_create("blkEna", (GspModelNode*) newINC, DLT860_BOOLEAN, DLT860_FC_BL, 0, 0, 0);

    if (options & GSP_CDC_OPTION_MIN)
        GspDataAttribute_create("minVal", (GspModelNode*) newINC, DLT860_INT32, DLT860_FC_CF, 0, 0, 0);

    if (options & GSP_CDC_OPTION_MAX)
        GspDataAttribute_create("maxVal", (GspModelNode*) newINC, DLT860_INT32, DLT860_FC_CF, 0, 0, 0);

    if (options & GSP_CDC_OPTION_STEP_SIZE)
        GspDataAttribute_create("stepSize", (GspModelNode*) newINC, DLT860_INT32U, DLT860_FC_CF, 0, 0, 0);

    CDC_addStandardOptions(newINC, options);

    return newINC;
}

GspDataObject*
GspCDC_ENC_create(const char* dataObjectName, GspModelNode* parent, uint32_t options, uint32_t controlOptions)
{
    GspDataObject* newENC = GspDataObject_create(dataObjectName, parent, 0);

    addOriginatorAndCtlNumOptions((GspModelNode*) newENC, controlOptions);

    CDC_addStatusToDataObject(newENC, DLT860_ENUMERATED);

    addControls(newENC, DLT860_ENUMERATED, controlOptions);

    if (controlOptions & GSP_CDC_CTL_OPTION_ST_SELD)
        GspDataAttribute_create("stSeld", (GspModelNode*) newENC, DLT860_BOOLEAN, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    addCommonControlAttributes(newENC, controlOptions);

    if (options & GSP_CDC_OPTION_PICS_SUBST)
        CDC_addOptionPicsSubst(newENC, DLT860_ENUMERATED);

    if (options & GSP_CDC_OPTION_BLK_ENA)
        GspDataAttribute_create("blkEna", (GspModelNode*) newENC, DLT860_BOOLEAN, DLT860_FC_BL, 0, 0, 0);

    CDC_addStandardOptions(newENC, options);

    return newENC;
}

GspDataObject*
GspCDC_BSC_create(const char* dataObjectName, GspModelNode* parent, uint32_t options, uint32_t controlOptions, bool hasTransientIndicator)
{
    GspDataObject* newBSC = GspDataObject_create(dataObjectName, parent, 0);

    addOriginatorAndCtlNumOptions((GspModelNode*) newBSC, controlOptions);

    GspCAC_ValWithTrans_create("valWTr", (GspModelNode*) newBSC, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, hasTransientIndicator);
    CDC_addTimeQuality(newBSC, DLT860_FC_ST);

    GspDataAttribute_create("persistent", (GspModelNode*) newBSC, DLT860_BOOLEAN, DLT860_FC_CF, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    addControls(newBSC, DLT860_CODEDENUM, controlOptions);

    if (controlOptions & GSP_CDC_CTL_OPTION_ST_SELD)
        GspDataAttribute_create("stSeld", (GspModelNode*) newBSC, DLT860_BOOLEAN, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    addCommonControlAttributes(newBSC, controlOptions);

    if (options & GSP_CDC_OPTION_PICS_SUBST)
        CDC_addOptionPicsSubstValWithTrans(newBSC, hasTransientIndicator);

    if (options & GSP_CDC_OPTION_BLK_ENA)
        GspDataAttribute_create("blkEna", (GspModelNode*) newBSC, DLT860_BOOLEAN, DLT860_FC_BL, 0, 0, 0);

    CDC_addStandardOptions(newBSC, options);

    return newBSC;
}

GspDataObject*
GspCDC_ISC_create(const char* dataObjectName, GspModelNode* parent, uint32_t options, uint32_t controlOptions, bool hasTransientIndicator)
{
    GspDataObject* newISC = GspDataObject_create(dataObjectName, parent, 0);

    addOriginatorAndCtlNumOptions((GspModelNode*) newISC, controlOptions);

    GspCAC_ValWithTrans_create("valWTr", (GspModelNode*) newISC, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, hasTransientIndicator);
    CDC_addTimeQuality(newISC, DLT860_FC_ST);

    addControls(newISC, DLT860_INT8, controlOptions);

    if (controlOptions & GSP_CDC_CTL_OPTION_ST_SELD)
        GspDataAttribute_create("stSeld", (GspModelNode*) newISC, DLT860_BOOLEAN, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    addCommonControlAttributes(newISC, controlOptions);

    if (options & GSP_CDC_OPTION_PICS_SUBST)
        CDC_addOptionPicsSubstValWithTrans(newISC, hasTransientIndicator);

    if (options & GSP_CDC_OPTION_BLK_ENA)
        GspDataAttribute_create("blkEna", (GspModelNode*) newISC, DLT860_BOOLEAN, DLT860_FC_BL, 0, 0, 0);

    if (options & GSP_CDC_OPTION_MIN)
        GspDataAttribute_create("minVal", (GspModelNode*) newISC, DLT860_INT32, DLT860_FC_CF, 0, 0, 0);

    if (options & GSP_CDC_OPTION_MAX)
        GspDataAttribute_create("maxVal", (GspModelNode*) newISC, DLT860_INT32, DLT860_FC_CF, 0, 0, 0);

    CDC_addStandardOptions(newISC, options);

    return newISC;
}

GspDataObject*
GspCDC_BAC_create(const char* dataObjectName, GspModelNode* parent, uint32_t options, uint32_t controlOptions, bool isIntegerNotFloat)
{
    GspDataObject* newBAC = GspDataObject_create(dataObjectName, parent, 0);

    addControlStatusAttributesForAnalogControl(newBAC, controlOptions);

    GspCAC_AnalogueValue_create("mxVal", (GspModelNode*) newBAC, DLT860_FC_MX, GSP_TRG_OPT_DATA_CHANGED, isIntegerNotFloat);

    CDC_addTimeQuality(newBAC, DLT860_FC_MX);

    if (controlOptions & GSP_CDC_CTL_OPTION_ST_SELD)
        GspDataAttribute_create("stSeld", (GspModelNode*) newBAC, DLT860_BOOLEAN, DLT860_FC_MX, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    addControls(newBAC, DLT860_INT8, controlOptions);

    if (options & GSP_CDC_OPTION_PICS_SUBST) {
        GspDataAttribute_create("subEna", (GspModelNode*) newBAC, DLT860_BOOLEAN, DLT860_FC_SV, 0, 0, 0);
        GspCAC_AnalogueValue_create("subVal", (GspModelNode*) newBAC, DLT860_FC_SV, 0, isIntegerNotFloat);
        GspDataAttribute_create("subQ", (GspModelNode*) newBAC, DLT860_QUALITY, DLT860_FC_SV, 0, 0, 0);
        GspDataAttribute_create("subID", (GspModelNode*) newBAC, DLT860_VISIBLE_STRING_64, DLT860_FC_SV, 0, 0, 0);
    }

    if (options & GSP_CDC_OPTION_BLK_ENA)
        GspDataAttribute_create("blkEna", (GspModelNode*) newBAC, DLT860_BOOLEAN, DLT860_FC_BL, 0, 0, 0);

    GspDataAttribute_create("persistent", (GspModelNode*) newBAC, DLT860_BOOLEAN, DLT860_FC_CF, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    addAnalogControls(newBAC, controlOptions, isIntegerNotFloat);

    if (options & GSP_CDC_OPTION_MIN)
        GspCAC_AnalogueValue_create("minVal", (GspModelNode*) newBAC, DLT860_FC_CF, 0, isIntegerNotFloat);

    if (options & GSP_CDC_OPTION_MAX)
        GspCAC_AnalogueValue_create("maxVal", (GspModelNode*) newBAC, DLT860_FC_CF, 0, isIntegerNotFloat);

    if (options & GSP_CDC_OPTION_STEP_SIZE)
        GspCAC_AnalogueValue_create("stepSize", (GspModelNode*) newBAC, DLT860_FC_CF, 0, isIntegerNotFloat);

    CDC_addStandardOptions(newBAC, options);

    return newBAC;
}

GspDataObject*
GspCDC_LPL_create(const char* dataObjectName, GspModelNode* parent, uint32_t options)
{
    GspDataObject* newLPL = GspDataObject_create(dataObjectName, parent, 0);

    GspDataAttribute_create("vendor", (GspModelNode*) newLPL, DLT860_VISIBLE_STRING_255, DLT860_FC_DC, 0, 0, 0);
    GspDataAttribute_create("swRev", (GspModelNode*) newLPL, DLT860_VISIBLE_STRING_255, DLT860_FC_DC, 0, 0, 0);

    if (options & GSP_CDC_OPTION_AC_LN0_M)
        GspDataAttribute_create("configRev", (GspModelNode*) newLPL, DLT860_VISIBLE_STRING_255, DLT860_FC_DC, 0, 0, 0);

    if (options & GSP_CDC_OPTION_AC_LN0_EX)
        GspDataAttribute_create("ldNs", (GspModelNode*) newLPL, DLT860_VISIBLE_STRING_255, DLT860_FC_EX, 0, 0, 0);

    if (options & GSP_CDC_OPTION_AC_DLD_M)
        GspDataAttribute_create("lnNs", (GspModelNode*) newLPL, DLT860_VISIBLE_STRING_255, DLT860_FC_EX, 0, 0, 0);

    CDC_addStandardOptions(newLPL, options);

    return newLPL;
}

GspDataObject*
GspCDC_DPL_create(const char* dataObjectName, GspModelNode* parent, uint32_t options)
{
    GspDataObject* newDPL = GspDataObject_create(dataObjectName, parent, 0);

    GspDataAttribute_create("vendor", (GspModelNode*) newDPL, DLT860_VISIBLE_STRING_255, DLT860_FC_DC, 0, 0, 0);

    if (options & GSP_CDC_OPTION_DPL_HWREV)
        GspDataAttribute_create("hwRev", (GspModelNode*) newDPL, DLT860_VISIBLE_STRING_255, DLT860_FC_DC, 0, 0, 0);

    if (options & GSP_CDC_OPTION_DPL_SWREV)
        GspDataAttribute_create("swRev", (GspModelNode*) newDPL, DLT860_VISIBLE_STRING_255, DLT860_FC_DC, 0, 0, 0);

    if (options & GSP_CDC_OPTION_DPL_SERNUM)
        GspDataAttribute_create("serNum", (GspModelNode*) newDPL, DLT860_VISIBLE_STRING_255, DLT860_FC_DC, 0, 0, 0);

    if (options & GSP_CDC_OPTION_DPL_MODEL)
        GspDataAttribute_create("model", (GspModelNode*) newDPL, DLT860_VISIBLE_STRING_255, DLT860_FC_DC, 0, 0, 0);

    if (options & GSP_CDC_OPTION_DPL_LOCATION)
        GspDataAttribute_create("location", (GspModelNode*) newDPL, DLT860_VISIBLE_STRING_255, DLT860_FC_DC, 0, 0, 0);

    CDC_addStandardOptions(newDPL, options);

    return newDPL;
}

/* Directional protection activation information (ACD) */
GspDataObject*
GspCDC_ACD_create(const char* dataObjectName, GspModelNode* parent, uint32_t options)
{
    GspDataObject* newACD = GspDataObject_create(dataObjectName, parent, 0);

    GspDataAttribute_create("general", (GspModelNode*) newACD, DLT860_BOOLEAN, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 0, 0);
    GspDataAttribute_create("dirGeneral", (GspModelNode*) newACD, DLT860_ENUMERATED, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    if (options & GSP_CDC_OPTION_PHASE_A) {
        GspDataAttribute_create("phsA", (GspModelNode*) newACD, DLT860_BOOLEAN, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 0, 0);
        GspDataAttribute_create("dirPhsA", (GspModelNode*) newACD, DLT860_ENUMERATED, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 0, 0);
    }

    if (options & GSP_CDC_OPTION_PHASE_B) {
        GspDataAttribute_create("phsB", (GspModelNode*) newACD, DLT860_BOOLEAN, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 0, 0);
        GspDataAttribute_create("dirPhsB", (GspModelNode*) newACD, DLT860_ENUMERATED, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 0, 0);
    }

    if (options & GSP_CDC_OPTION_PHASE_C) {
        GspDataAttribute_create("phsC", (GspModelNode*) newACD, DLT860_BOOLEAN, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 0, 0);
        GspDataAttribute_create("dirPhsC", (GspModelNode*) newACD, DLT860_ENUMERATED, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 0, 0);
    }

    if (options & GSP_CDC_OPTION_PHASE_NEUT) {
        GspDataAttribute_create("neut", (GspModelNode*) newACD, DLT860_BOOLEAN, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 0, 0);
        GspDataAttribute_create("dirNeut", (GspModelNode*) newACD, DLT860_ENUMERATED, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 0, 0);
    }

    CDC_addTimeQuality(newACD, DLT860_FC_ST);

    CDC_addStandardOptions(newACD, options);

    return newACD;
}

GspDataObject*
GspCDC_ACT_create(const char* dataObjectName, GspModelNode* parent, uint32_t options)
{
    GspDataObject* newACT = GspDataObject_create(dataObjectName, parent, 0);

    GspDataAttribute_create("general", (GspModelNode*) newACT, DLT860_BOOLEAN, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    if (options & GSP_CDC_OPTION_PHASE_A)
        GspDataAttribute_create("phsA", (GspModelNode*) newACT, DLT860_BOOLEAN, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    if (options & GSP_CDC_OPTION_PHASE_B)
        GspDataAttribute_create("phsB", (GspModelNode*) newACT, DLT860_BOOLEAN, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    if (options & GSP_CDC_OPTION_PHASE_C)
        GspDataAttribute_create("phsC", (GspModelNode*) newACT, DLT860_BOOLEAN, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    if (options & GSP_CDC_OPTION_PHASE_NEUT)
        GspDataAttribute_create("neut", (GspModelNode*) newACT, DLT860_BOOLEAN, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    CDC_addTimeQuality(newACT, DLT860_FC_ST);

    CDC_addStandardOptions(newACT, options);

    return newACT;
}

GspDataObject*
GspCDC_WYE_create(const char* dataObjectName, GspModelNode* parent, uint32_t options)
{
    GspDataObject* newWYE = GspDataObject_create(dataObjectName, parent, 0);

    /* TODO check if some options should be masked */
    /* TODO take care for GC_1 */
    GspCDC_CMV_create("phsA", (GspModelNode*) newWYE, options);
    GspCDC_CMV_create("phsB", (GspModelNode*) newWYE, options);
    GspCDC_CMV_create("phsC", (GspModelNode*) newWYE, options);
    GspCDC_CMV_create("neut", (GspModelNode*) newWYE, options);
    GspCDC_CMV_create("net", (GspModelNode*) newWYE, options);
    GspCDC_CMV_create("res", (GspModelNode*) newWYE, options);

    if (options & GSP_CDC_OPTION_ANGLE_REF)
        GspDataAttribute_create("angRef", (GspModelNode*) newWYE, DLT860_ENUMERATED, DLT860_FC_CF, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    CDC_addStandardOptions(newWYE, options);

    return newWYE;
}


GspDataObject*
GspCDC_DEL_create(const char* dataObjectName, GspModelNode* parent, uint32_t options)
{
    GspDataObject* newDEL = GspDataObject_create(dataObjectName, parent, 0);

    /* TODO check if some options should be masked */
    GspCDC_CMV_create("phsAB", (GspModelNode*) newDEL, options);
    GspCDC_CMV_create("phsBC", (GspModelNode*) newDEL, options);
    GspCDC_CMV_create("phsCA", (GspModelNode*) newDEL, options);

    if (options & GSP_CDC_OPTION_ANGLE_REF)
        GspDataAttribute_create("angRef", (GspModelNode*) newDEL, DLT860_ENUMERATED, DLT860_FC_CF, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    CDC_addStandardOptions(newDEL, options);

    return newDEL;
}


GspDataObject*
GspCDC_SPG_create(const char* dataObjectName, GspModelNode* parent, uint32_t options)
{
    GspDataObject* newSPG = GspDataObject_create(dataObjectName, parent, 0);

    GspDataAttribute_create("setVal", (GspModelNode*) newSPG, DLT860_BOOLEAN, DLT860_FC_SP, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    CDC_addStandardOptions(newSPG, options);

    return newSPG;
}

GspDataObject*
GspCDC_VSG_create(const char* dataObjectName, GspModelNode* parent, uint32_t options)
{
    GspDataObject* newSPG = GspDataObject_create(dataObjectName, parent, 0);

    GspDataAttribute_create("setVal", (GspModelNode*) newSPG, DLT860_VISIBLE_STRING_255, DLT860_FC_SP, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    CDC_addStandardOptions(newSPG, options);

    return newSPG;
}


GspDataObject*
GspCDC_ENG_create(const char* dataObjectName, GspModelNode* parent, uint32_t options)
{
    GspDataObject* newENG = GspDataObject_create(dataObjectName, parent, 0);

    GspDataAttribute_create("setVal", (GspModelNode*) newENG, DLT860_ENUMERATED, DLT860_FC_SP, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    CDC_addStandardOptions(newENG, options);

    return newENG;
}

GspDataObject*
GspCDC_ING_create(const char* dataObjectName, GspModelNode* parent, uint32_t options)
{
    GspDataObject* newING = GspDataObject_create(dataObjectName, parent, 0);

    GspDataAttribute_create("setVal", (GspModelNode*) newING, DLT860_INT32, DLT860_FC_SP, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    if (options & GSP_CDC_OPTION_UNIT)
        GspCAC_Unit_create("units", (GspModelNode*) newING, options & GSP_CDC_OPTION_UNIT_MULTIPLIER);

    if (options & GSP_CDC_OPTION_MIN)
        GspDataAttribute_create("minVal", (GspModelNode*) newING, DLT860_INT32, DLT860_FC_SP, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    if (options & GSP_CDC_OPTION_MAX)
        GspDataAttribute_create("maxVal", (GspModelNode*) newING, DLT860_INT32, DLT860_FC_SP, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    if (options & GSP_CDC_OPTION_STEP_SIZE)
        GspDataAttribute_create("stepSize", (GspModelNode*) newING, DLT860_INT32U, DLT860_FC_SP, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    CDC_addStandardOptions(newING, options);


    return newING;
}

GspDataObject*
GspCDC_ASG_create(const char* dataObjectName, GspModelNode* parent, uint32_t options, bool isIntegerNotFloat)
{
    GspDataObject* newASG = GspDataObject_create(dataObjectName, parent, 0);

    GspCAC_AnalogueValue_create("setMag", (GspModelNode*) newASG, DLT860_FC_SP, GSP_TRG_OPT_DATA_CHANGED, isIntegerNotFloat);

    if (options & GSP_CDC_OPTION_UNIT)
        GspCAC_Unit_create("units", (GspModelNode*) newASG, options & GSP_CDC_OPTION_UNIT_MULTIPLIER);

    if (options & GSP_CDC_OPTION_AC_SCAV)
        GspCAC_ScaledValueConfig_create("sVC", (GspModelNode*) newASG);

    if (options & GSP_CDC_OPTION_MIN)
        GspCAC_AnalogueValue_create("minVal", (GspModelNode*) newASG, DLT860_FC_CF, GSP_TRG_OPT_DATA_CHANGED, isIntegerNotFloat);

    if (options & GSP_CDC_OPTION_MAX)
        GspCAC_AnalogueValue_create("maxVal", (GspModelNode*) newASG, DLT860_FC_CF, GSP_TRG_OPT_DATA_CHANGED, isIntegerNotFloat);

    if (options & GSP_CDC_OPTION_STEP_SIZE)
        GspCAC_AnalogueValue_create("stepSize", (GspModelNode*) newASG, DLT860_FC_CF, GSP_TRG_OPT_DATA_CHANGED, isIntegerNotFloat);

    CDC_addStandardOptions(newASG, options);

    return newASG;
}

/**********************************************************************************
 * Wind power specific CDCs - according to 61400-25-2:2006
 *********************************************************************************/

GspDataObject*
GspCDC_SPV_create(const char* dataObjectName, GspModelNode* parent, uint32_t options, uint32_t controlOptions, uint32_t wpOptions, bool hasChaManRs)
{
    GspDataObject* newSPV = GspDataObject_create(dataObjectName, parent, 0);

    if (hasChaManRs)
        GspCDC_SPC_create("chaManRs", (GspModelNode*) newSPV, 0, GSP_CDC_CTL_MODEL_DIRECT_NORMAL);

    GspCDC_APC_create("actVal", (GspModelNode*) newSPV, 0, controlOptions, false);

    /* TOOO add optional "oldVal" APC */

    if (wpOptions & GSP_CDC_OPTION_61400_MIN_MX_VAL)
        GspCAC_AnalogueValue_create("minMxVal", (GspModelNode*) newSPV, DLT860_FC_MX, 0, false);

    if (wpOptions & GSP_CDC_OPTION_61400_MAX_MX_VAL)
        GspCAC_AnalogueValue_create("maxMxVal", (GspModelNode*) newSPV, DLT860_FC_MX, 0, false);

    if (wpOptions & GSP_CDC_OPTION_61400_TOT_AV_VAL)
        GspCAC_AnalogueValue_create("totAvVal", (GspModelNode*) newSPV, DLT860_FC_MX, 0, false);

    if (wpOptions & GSP_CDC_OPTION_61400_SDV_VAL)
        GspCAC_AnalogueValue_create("sdvVal", (GspModelNode*) newSPV, DLT860_FC_MX, 0, false);

    if (options & GSP_CDC_OPTION_UNIT)
        GspCAC_Unit_create("units", (GspModelNode*) newSPV, options & GSP_CDC_OPTION_UNIT_MULTIPLIER);

    if (options & GSP_CDC_OPTION_MIN)
        GspCAC_AnalogueValue_create("minVal", (GspModelNode*) newSPV, DLT860_FC_CF, GSP_TRG_OPT_DATA_CHANGED, false);

    if (options & GSP_CDC_OPTION_MAX)
        GspCAC_AnalogueValue_create("maxVal", (GspModelNode*) newSPV, DLT860_FC_CF, GSP_TRG_OPT_DATA_CHANGED, false);

    if (wpOptions & GSP_CDC_OPTION_61400_SP_ACS)
        GspDataAttribute_create("spAcs", (GspModelNode*) newSPV, DLT860_CODEDENUM, DLT860_FC_CF, 0, 0, 0);

    if (wpOptions & GSP_CDC_OPTION_61400_CHA_PER_RS)
        GspDataAttribute_create("chaPerRs", (GspModelNode*) newSPV, DLT860_CODEDENUM, DLT860_FC_CF, 0, 0, 0);

    CDC_addStandardOptions(newSPV, options);

    return newSPV;
}

GspDataObject*
GspCDC_STV_create(const char* dataObjectName, GspModelNode* parent,
        uint32_t options,
        uint32_t controlOptions,
        uint32_t wpOptions,
        bool hasOldStatus)
{
    GspDataObject* newSTV = GspDataObject_create(dataObjectName, parent, 0);

    GspCDC_INS_create("actSt", (GspModelNode*) newSTV, 0);

    if (hasOldStatus)
        GspCDC_INS_create("oldSt", (GspModelNode*) newSTV, 0);

    CDC_addStandardOptions(newSTV, options);

    return newSTV;
}

GspDataObject*
GspCDC_ALM_create(const char* dataObjectName, GspModelNode* parent,
        uint32_t options,
        uint32_t controlOptions,
        uint32_t wpOptions,
        bool hasOldStatus)
{
    GspDataObject* newALM = GspDataObject_create(dataObjectName, parent, 0);

    GspCDC_SPC_create("almAck", (GspModelNode*) newALM, 0, GSP_CDC_CTL_MODEL_DIRECT_NORMAL | GSP_CDC_CTL_OPTION_ORIGIN);

    GspCDC_INS_create("actSt", (GspModelNode*) newALM, 0);

    if (hasOldStatus)
        GspCDC_INS_create("oldSt", (GspModelNode*) newALM, 0);

    CDC_addStandardOptions(newALM, options);

    return newALM;
}

GspDataObject*
GspCDC_CMD_create(const char* dataObjectName, GspModelNode* parent,
        uint32_t options,
        uint32_t controlOptions,
        uint32_t wpOptions,
        bool hasOldStatus,
        bool hasCmTm,
        bool hasCmCt)
{
    GspDataObject* newCMD = GspDataObject_create(dataObjectName, parent, 0);

    GspCDC_INC_create("actSt", (GspModelNode*) newCMD, 0, controlOptions);

    if (hasOldStatus)
        GspCDC_INS_create("oldSt", (GspModelNode*) newCMD, 0);

    if (wpOptions & GSP_CDC_OPTION_61400_CM_ACS)
        GspDataAttribute_create("cmAcs", (GspModelNode*) newCMD, DLT860_INT8U, DLT860_FC_CF, 0, 0, 0);

    CDC_addStandardOptions(newCMD, options);

    return newCMD;
}


/**
 * \brief create a new CDC instance of type CTE (Event counting)
 */
GspDataObject*
GspCDC_CTE_create(const char* dataObjectName, GspModelNode* parent,
        uint32_t options,
        uint32_t controlOptions,
        uint32_t wpOptions,
        bool hasHisRs)
{
    GspDataObject* newCTE = GspDataObject_create(dataObjectName, parent, 0);

    GspCDC_SPC_create("manRs", (GspModelNode*) newCTE, 0, GSP_CDC_CTL_MODEL_DIRECT_NORMAL | GSP_CDC_CTL_OPTION_ORIGIN);

    if (hasHisRs)
        GspCDC_INC_create("hisRs", (GspModelNode*) newCTE, 0, GSP_CDC_CTL_MODEL_DIRECT_NORMAL | GSP_CDC_CTL_OPTION_ORIGIN);

    GspCDC_INS_create("actCtVal", (GspModelNode*) newCTE, 0);

    GspCDC_INS_create("oldCtVal", (GspModelNode*) newCTE, 0);

    if (wpOptions & GSP_CDC_OPTION_61400_TM_TOT)
        GspDataAttribute_create("ctTot", (GspModelNode*) newCTE, DLT860_INT32U, DLT860_FC_ST, 0, 0, 0);

    if (wpOptions & GSP_CDC_OPTION_61400_COUNTING_DAILY)
        GspDataAttribute_create("dly", (GspModelNode*) newCTE, DLT860_INT32U, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 32, 0);

    if (wpOptions & GSP_CDC_OPTION_61400_COUNTING_MONTHLY)
        GspDataAttribute_create("mly", (GspModelNode*) newCTE, DLT860_INT32U, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 13, 0);

    if (wpOptions & GSP_CDC_OPTION_61400_COUNTING_YEARLY)
        GspDataAttribute_create("mly", (GspModelNode*) newCTE, DLT860_INT32U, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 21, 0);

    if (wpOptions & GSP_CDC_OPTION_61400_COUNTING_TOTAL)
        GspDataAttribute_create("tot", (GspModelNode*) newCTE, DLT860_INT32U, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 0, 0);

    CDC_addStandardOptions(newCTE, options);

    return newCTE;
}


GspDataObject*
GspCDC_TMS_create(const char* dataObjectName, GspModelNode* parent,
        uint32_t options,
        uint32_t controlOptions,
        uint32_t wpOptions,
        bool hasHisRs)
{
    GspDataObject* newTMS = GspDataObject_create(dataObjectName, parent, 0);

    GspCDC_SPC_create("manRs", (GspModelNode*) newTMS, 0, GSP_CDC_CTL_MODEL_DIRECT_NORMAL | GSP_CDC_CTL_OPTION_ORIGIN);

    if (hasHisRs)
        GspCDC_INC_create("hisRs", (GspModelNode*) newTMS, 0, GSP_CDC_CTL_MODEL_DIRECT_NORMAL | GSP_CDC_CTL_OPTION_ORIGIN);

    GspCDC_INS_create("actTmVal", (GspModelNode*) newTMS, 0);

    GspCDC_INS_create("oldTmVal", (GspModelNode*) newTMS, 0);

    if (wpOptions & GSP_CDC_OPTION_61400_TM_TOT)
        GspDataAttribute_create("tmTot", (GspModelNode*) newTMS, DLT860_INT32U, DLT860_FC_ST, 0, 0, 0);

    if (wpOptions & GSP_CDC_OPTION_61400_COUNTING_DAILY)
        GspDataAttribute_create("dly", (GspModelNode*) newTMS, DLT860_INT32U, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 32, 0);

    if (wpOptions & GSP_CDC_OPTION_61400_COUNTING_MONTHLY)
        GspDataAttribute_create("mly", (GspModelNode*) newTMS, DLT860_INT32U, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 13, 0);

    if (wpOptions & GSP_CDC_OPTION_61400_COUNTING_YEARLY)
        GspDataAttribute_create("mly", (GspModelNode*) newTMS, DLT860_INT32U, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 21, 0);

    if (wpOptions & GSP_CDC_OPTION_61400_COUNTING_TOTAL)
        GspDataAttribute_create("tot", (GspModelNode*) newTMS, DLT860_INT32U, DLT860_FC_ST, GSP_TRG_OPT_DATA_CHANGED, 0, 0);


    CDC_addStandardOptions(newTMS, options);

    return newTMS;
}

