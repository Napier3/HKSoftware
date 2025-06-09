/*
 *  cdc.h
 */

#ifndef GSP_CDC_H_
#define GSP_CDC_H_

#include "libdlt860_define.h"

/**
 * \brief optional parts of CDCs
 */
#define GSP_CDC_OPTION_PICS_SUBST (1 << 0)
#define GSP_CDC_OPTION_BLK_ENA (1 << 1)

/** Add d (description) data attribute */
#define GSP_CDC_OPTION_DESC (1 << 2)

/** Add dU (unicode description) data attribute */
#define GSP_CDC_OPTION_DESC_UNICODE (1 << 3)

/** Add cdcNs and cdcName required when a CDC is an extension to the standard */
#define GSP_CDC_OPTION_AC_DLNDA (1 << 4)

/** Add dataNs (data namespace) required for extended CDCs */
#define GSP_CDC_OPTION_AC_DLN (1 << 5)

/** Add the unit data attribute */
#define GSP_CDC_OPTION_UNIT (1 << 6)
#define GSP_CDC_OPTION_FROZEN_VALUE (1 << 7)
#define GSP_CDC_OPTION_ADDR (1 << 8)
#define GSP_CDC_OPTION_ADDINFO (1 << 9)
#define GSP_CDC_OPTION_INST_MAG (1 << 10)
#define GSP_CDC_OPTION_RANGE (1 << 11)
#define GSP_CDC_OPTION_UNIT_MULTIPLIER (1 << 12)
#define GSP_CDC_OPTION_AC_SCAV (1 << 13)
#define GSP_CDC_OPTION_MIN (1 << 14)
#define GSP_CDC_OPTION_MAX (1 << 15)
#define GSP_CDC_OPTION_AC_CLC_O (1 << 16)
#define GSP_CDC_OPTION_RANGE_ANG (1 << 17)
#define GSP_CDC_OPTION_PHASE_A (1 << 18)
#define GSP_CDC_OPTION_PHASE_B (1 << 19)
#define GSP_CDC_OPTION_PHASE_C (1 << 20)
#define GSP_CDC_OPTION_PHASE_NEUT (1 << 21)
#define GSP_CDC_OPTION_PHASES_ABC (GSP_CDC_OPTION_PHASE_A | GSP_CDC_OPTION_PHASE_B | GSP_CDC_OPTION_PHASE_C)
#define GSP_CDC_OPTION_PHASES_ALL (GSP_CDC_OPTION_PHASE_A | GSP_CDC_OPTION_PHASE_B | GSP_CDC_OPTION_PHASE_C | GSP_CDC_OPTION_PHASE_NEUT)
#define GSP_CDC_OPTION_STEP_SIZE (1 << 22)
#define GSP_CDC_OPTION_ANGLE_REF (1 << 23)

/** Options that are only valid for DPL CDC */
#define GSP_CDC_OPTION_DPL_HWREV (1 << 17)
#define GSP_CDC_OPTION_DPL_SWREV (1 << 18)
#define GSP_CDC_OPTION_DPL_SERNUM (1 << 19)
#define GSP_CDC_OPTION_DPL_MODEL (1 << 20)
#define GSP_CDC_OPTION_DPL_LOCATION (1 << 21)

/** Add mandatory data attributes for LLN0 (e.g. LBL configRef) */
#define GSP_CDC_OPTION_AC_LN0_M (1 << 24)
#define GSP_CDC_OPTION_AC_LN0_EX (1 << 25)
#define GSP_CDC_OPTION_AC_DLD_M (1 << 26)

/**
 * \brief Control model types
 */
#define GSP_CDC_CTL_MODEL_NONE 0
#define GSP_CDC_CTL_MODEL_DIRECT_NORMAL 1
#define GSP_CDC_CTL_MODEL_SBO_NORMAL 2
#define GSP_CDC_CTL_MODEL_DIRECT_ENHANCED 3
#define GSP_CDC_CTL_MODEL_SBO_ENHANCED 4
#define GSP_CDC_CTL_MODEL_HAS_CANCEL (1 << 4)
#define GSP_CDC_CTL_MODEL_IS_TIME_ACTIVATED (1 << 5)
#define GSP_CDC_CTL_OPTION_ORIGIN (1 << 6)
#define GSP_CDC_CTL_OPTION_CTL_NUM (1 << 7)
#define GSP_CDC_CTL_OPTION_ST_SELD (1 << 8)
#define GSP_CDC_CTL_OPTION_OP_RCVD (1 << 9)
#define GSP_CDC_CTL_OPTION_OP_OK (1 << 10)
#define GSP_CDC_CTL_OPTION_T_OP_OK (1 << 11)
#define GSP_CDC_CTL_OPTION_SBO_TIMEOUT (1 << 12)
#define GSP_CDC_CTL_OPTION_SBO_CLASS (1 << 13)
#define GSP_CDC_CTL_OPTION_OPER_TIMEOUT (1 << 14)

/****************************************************
 * Constructed Attribute Classes (CAC)
 ***************************************************/

LIB860_API GspDataAttribute* GspCAC_AnalogueValue_create(const char* name,
                                                         GspModelNode* parent,
                                                         GspFunctionalConstraint fc,
                                                         uint8_t triggerOptions,
                                                         bool isIntegerNotFloat);

LIB860_API GspDataAttribute* GspCAC_ValWithTrans_create(const char* name,
                                                        GspModelNode* parent,
                                                        GspFunctionalConstraint fc,
                                                        uint8_t triggerOptions,
                                                        bool hasTransientIndicator);


LIB860_API GspDataAttribute* GspCAC_Vector_create(const char* name,
                                                  GspModelNode* parent,
                                                  uint32_t options,
                                                  GspFunctionalConstraint fc,
                                                  uint8_t triggerOptions);

LIB860_API GspDataAttribute* GspCAC_Point_create(const char* name,
                                                 GspModelNode* parent,
                                                 GspFunctionalConstraint fc,
                                                 uint8_t triggerOptions,
                                                 bool hasZVal);

LIB860_API GspDataAttribute* GspCAC_ScaledValueConfig_create(const char* name,
                                                             GspModelNode* parent);

LIB860_API GspDataAttribute* GspCAC_Unit_create(const char* name,
                                                GspModelNode* parent,
                                                bool hasMagnitude);

LIB860_API GspDataAttribute* GspCDA_OperBoolean(GspModelNode* parent,
                                                bool isTImeActivated);

/****************************************************
 * Common Data Classes (CDC)
 ***************************************************/

LIB860_API GspDataObject* GspCDC_SPS_create(const char* dataObjectName, GspModelNode* parent, uint32_t options);

LIB860_API GspDataObject* GspCDC_DPS_create(const char* dataObjectName, GspModelNode* parent, uint32_t options);

LIB860_API GspDataObject* GspCDC_INS_create(const char* dataObjectName, GspModelNode* parent, uint32_t options);

LIB860_API GspDataObject* GspCDC_ENS_create(const char* dataObjectName, GspModelNode* parent, uint32_t options);

LIB860_API GspDataObject* GspCDC_BCR_create(const char* dataObjectName, GspModelNode* parent, uint32_t options);

LIB860_API GspDataObject* GspCDC_VSS_create(const char* dataObjectName, GspModelNode* parent, uint32_t options);

LIB860_API GspDataObject* GspCDC_SEC_create(const char* dataObjectName, GspModelNode* parent, uint32_t options);

LIB860_API GspDataObject* GspCDC_MV_create(const char* dataObjectName, GspModelNode* parent, uint32_t options, bool isIntegerNotFloat);

LIB860_API GspDataObject* GspCDC_CMV_create(const char* dataObjectName, GspModelNode* parent, uint32_t options);

LIB860_API GspDataObject* GspCDC_SAV_create(const char* dataObjectName, GspModelNode* parent, uint32_t options, bool isIntegerNotFloat);

LIB860_API GspDataObject* GspCDC_LPL_create(const char* dataObjectName, GspModelNode* parent, uint32_t options);

LIB860_API GspDataObject* GspCDC_DPL_create(const char* dataObjectName, GspModelNode* parent, uint32_t options);

LIB860_API GspDataObject* GspCDC_HST_create(const char* dataObjectName, GspModelNode* parent, uint32_t options, uint16_t maxPts);

LIB860_API GspDataObject* GspCDC_ACD_create(const char* dataObjectName, GspModelNode* parent, uint32_t options);

LIB860_API GspDataObject* GspCDC_ACT_create(const char* dataObjectName, GspModelNode* parent, uint32_t options);

LIB860_API GspDataObject* GspCDC_SPG_create(const char* dataObjectName, GspModelNode* parent, uint32_t options);

LIB860_API GspDataObject* GspCDC_VSG_create(const char* dataObjectName, GspModelNode* parent, uint32_t options);

LIB860_API GspDataObject* GspCDC_ENG_create(const char* dataObjectName, GspModelNode* parent, uint32_t options);

LIB860_API GspDataObject* GspCDC_ING_create(const char* dataObjectName, GspModelNode* parent, uint32_t options);

LIB860_API GspDataObject* GspCDC_ASG_create(const char* dataObjectName, GspModelNode* parent, uint32_t options, bool isIntegerNotFloat);

LIB860_API GspDataObject* GspCDC_WYE_create(const char* dataObjectName, GspModelNode* parent, uint32_t options);

LIB860_API GspDataObject* GspCDC_DEL_create(const char* dataObjectName, GspModelNode* parent, uint32_t options);

/***************************
 * Controls
 ***************************/

LIB860_API GspDataObject* GspCDC_SPC_create(const char* dataObjectName, GspModelNode* parent, uint32_t options, uint32_t controlOptions);

LIB860_API GspDataObject* GspCDC_DPC_create(const char* dataObjectName, GspModelNode* parent, uint32_t options, uint32_t controlOptions);

LIB860_API GspDataObject* GspCDC_INC_create(const char* dataObjectName, GspModelNode* parent, uint32_t options, uint32_t controlOptions);

LIB860_API GspDataObject* GspCDC_ENC_create(const char* dataObjectName, GspModelNode* parent, uint32_t options, uint32_t controlOptions);

LIB860_API GspDataObject* GspCDC_BSC_create(const char* dataObjectName, GspModelNode* parent, uint32_t options, uint32_t controlOptions, bool hasTransientIndicator);

LIB860_API GspDataObject* GspCDC_ISC_create(const char* dataObjectName, GspModelNode* parent, uint32_t options, uint32_t controlOptions, bool hasTransientIndicator);

LIB860_API GspDataObject* GspCDC_APC_create(const char* dataObjectName, GspModelNode* parent, uint32_t options, uint32_t controlOptions, bool isIntegerNotFloat);

LIB860_API GspDataObject* GspCDC_BAC_create(const char* dataObjectName, GspModelNode* parent, uint32_t options, uint32_t controlOptions, bool isIntegerNotFloat);

/** Minimum measured value */
#define GSP_CDC_OPTION_61400_MIN_MX_VAL (1 << 10)

/** Maximum measured value */
#define GSP_CDC_OPTION_61400_MAX_MX_VAL (1 << 11)

/** Total average value of data */
#define GSP_CDC_OPTION_61400_TOT_AV_VAL (1 << 12)

/** Standard deviation of data */
#define GSP_CDC_OPTION_61400_SDV_VAL (1 << 13)

/** Rate of increase */
#define GSP_CDC_OPTION_61400_INC_RATE (1 << 14)

/** Rate of decrease */
#define GSP_CDC_OPTION_61400_DEC_RATE (1 << 15)

/** Setpoint or parameter access level (low/medium/high) */
#define GSP_CDC_OPTION_61400_SP_ACS (1 << 16)

/** Time periodical reset (hourly/daily/weekly/monthly) */
#define GSP_CDC_OPTION_61400_CHA_PER_RS (1 << 17)

/** Command access level */
#define GSP_CDC_OPTION_61400_CM_ACS (1 << 18)

/** Total time duration of a state */
#define GSP_CDC_OPTION_61400_TM_TOT (1 << 19)

/** Daily counting data */
#define GSP_CDC_OPTION_61400_COUNTING_DAILY (1 << 20)

/** Monthly counting data */
#define GSP_CDC_OPTION_61400_COUNTING_MONTHLY (1 << 21)

/** Yearly counting data */
#define GSP_CDC_OPTION_61400_COUNTING_YEARLY (1 << 22)

/** Total counting data */
#define GSP_CDC_OPTION_61400_COUNTING_TOTAL (1 << 23)

/** All counting data */
#define GSP_CDC_OPTION_61400_COUNTING_ALL (GSP_CDC_OPTION_61400_COUNTING_DAILY | GSP_CDC_OPTION_61400_COUNTING_MONTHLY | GSP_CDC_OPTION_61400_COUNTING_YEARLY | GSP_CDC_OPTION_61400_COUNTING_TOTAL)

LIB860_API GspDataObject* GspCDC_SPV_create(const char* dataObjectName,
                                            GspModelNode* parent,
                                            uint32_t options,
                                            uint32_t controlOptions,
                                            uint32_t wpOptions,
                                            bool hasChaManRs);

LIB860_API GspDataObject* GspCDC_STV_create(const char* dataObjectName,
                                            GspModelNode* parent,
                                            uint32_t options,
                                            uint32_t controlOptions,
                                            uint32_t wpOptions,
                                            bool hasOldStatus);

LIB860_API GspDataObject* GspCDC_CMD_create(const char* dataObjectName,
                                            GspModelNode* parent,
                                            uint32_t options,
                                            uint32_t controlOptions,
                                            uint32_t wpOptions,
                                            bool hasOldStatus,
                                            bool hasCmTm,
                                            bool hasCmCt);

LIB860_API GspDataObject* GspCDC_ALM_create(const char* dataObjectName,
                                            GspModelNode* parent,
                                            uint32_t options,
                                            uint32_t controlOptions,
                                            uint32_t wpOptions,
                                            bool hasOldStatus);

LIB860_API GspDataObject* GspCDC_CTE_create(const char* dataObjectName,
                                            GspModelNode* parent,
                                            uint32_t options,
                                            uint32_t controlOptions,
                                            uint32_t wpOptions,
                                            bool hasHisRs);

LIB860_API GspDataObject* GspCDC_TMS_create(const char* dataObjectName,
                                            GspModelNode* parent,
                                            uint32_t options,
                                            uint32_t controlOptions,
                                            uint32_t wpOptions,
                                            bool hasHisRs);
#endif /* GSP_CDC_H_ */
