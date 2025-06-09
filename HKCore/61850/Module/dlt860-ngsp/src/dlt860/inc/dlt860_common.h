/*
 *  DLT860_common.h
 */

#ifndef GSP_DLT860_COMMON_H_
#define GSP_DLT860_COMMON_H_

#include "logging_api.h"
#include "gsp_mms_value.h"


/** DLT 860 edition 1 */
#define DLT_860_EDITION_1   0

/** IEC 860 edition 2 */
#define DLT_860_EDITION_2   1

/** IEC 860 edition 2.1 */
#define DLT_860_EDITION_2_1 2

/** PhyComAddress type contains Ethernet address and VLAN attributes */
typedef struct {
    uint8_t vlanPriority;
    uint16_t vlanId;
    uint16_t appId;
    uint8_t dstAddress[6];
} GspPhyComAddress;

/**
 * \brief 控制模式
 */
typedef enum {
    // 查看状态信息
    GSP_CONTROL_MODEL_STATUS_ONLY = 0,

    /**
     * Direct control with normal security: Supports Operate, TimeActivatedOperate (optional),
     * and Cancel (optional).
     */
    GSP_CONTROL_MODEL_DIRECT_NORMAL = 1,

    /**
     * Select before operate (SBO) with normal security: Supports Select, Operate, TimeActivatedOperate (optional),
     * and Cancel (optional).
     */
    GSP_CONTROL_MODEL_SBO_NORMAL = 2,

    /**
     * Direct control with enhanced security (enhanced security includes the CommandTermination service)
     */
    GSP_CONTROL_MODEL_DIRECT_ENHANCED = 3,

    /**
     * Select before operate (SBO) with enhanced security (enhanced security includes the CommandTermination service)
     */
    GSP_CONTROL_MODEL_SBO_ENHANCED = 4
} GspControlModel;

/** Report will be triggered when data changes */
#define GSP_TRG_OPT_DATA_CHANGED 1

/** Report will be triggered when quality changes */
#define GSP_TRG_OPT_QUALITY_CHANGED 2

/** Report will be triggered when data is updated */
#define GSP_TRG_OPT_DATA_UPDATE 4

/** Report will be triggered periodically */
#define GSP_TRG_OPT_INTEGRITY 8

/** Report will be triggered by GI (general interrogation) request */
#define GSP_TRG_OPT_GI 16

/** RCB has the owner attribute */
#define GSP_RPT_OPT_HAS_OWNER 64

/** Report will be triggered only on rising edge (transient variable */
#define TRG_OPT_TRANSIENT 128

/** Report contains sequence number */
#define GSP_RPT_OPT_SEQ_NUM 1

/** Report contains a report timestamp */
#define GSP_RPT_OPT_TIME_STAMP 2

/** Report contains reason for inclusion value for each included data set member */
#define GSP_RPT_OPT_REASON_FOR_INCLUSION 4

/** Report contains data set object reference */
#define GSP_RPT_OPT_DATA_SET 8

/** Report contains data reference for each included data set member */
#define GSP_RPT_OPT_DATA_REFERENCE 16

/** Report contains buffer overflow flag */
#define GSP_RPT_OPT_BUFFER_OVERFLOW 32

/** Report contains entry id */
#define GSP_RPT_OPT_ENTRY_ID 64

/** Report contains configuration revision */
#define GSP_RPT_OPT_CONF_REV 128

/** Not supported - should not be used */
#define GSP_CONTROL_ORCAT_NOT_SUPPORTED 0

/** Control operation issued from an operator using a client located at bay level */
#define GSP_CONTROL_ORCAT_BAY_CONTROL 1

/** Control operation issued from an operator using a client located at station level */
#define GSP_CONTROL_ORCAT_STATION_CONTROL 2

/** Control operation from a remote operator outside the substation (for example network control center) */
#define GSP_CONTROL_ORCAT_REMOTE_CONTROL 3

/** Control operation issued from an automatic function at bay level */
#define GSP_CONTROL_ORCAT_AUTOMATIC_BAY 4

/** Control operation issued from an automatic function at station level */
#define GSP_CONTROL_ORCAT_AUTOMATIC_STATION 5

/** Control operation issued from a automatic function outside of the substation */
#define GSP_CONTROL_ORCAT_AUTOMATIC_REMOTE 6

/** Control operation issued from a maintenance/service tool */
#define GSP_CONTROL_ORCAT_MAINTENANCE 7

/** Status change occurred without control action (for example external trip of a circuit breaker or failure inside the breaker) */
#define GSP_CONTROL_ORCAT_PROCESS 8

/** AddCause - additional cause information for control model errors */
typedef enum {
    GSP_ADD_CAUSE_UNKNOWN = 0,
    GSP_ADD_CAUSE_NOT_SUPPORTED = 1,
    GSP_ADD_CAUSE_BLOCKED_BY_SWITCHING_HIERARCHY = 2,
    GSP_ADD_CAUSE_SELECT_FAILED = 3,
    GSP_ADD_CAUSE_INVALID_POSITION = 4,
    GSP_ADD_CAUSE_POSITION_REACHED = 5,
    GSP_ADD_CAUSE_PARAMETER_CHANGE_IN_EXECUTION = 6,
    GSP_ADD_CAUSE_STEP_LIMIT = 7,
    GSP_ADD_CAUSE_BLOCKED_BY_MODE = 8,
    GSP_ADD_CAUSE_BLOCKED_BY_PROCESS = 9,
    GSP_ADD_CAUSE_BLOCKED_BY_INTERLOCKING = 10,
    GSP_ADD_CAUSE_BLOCKED_BY_SYNCHROCHECK = 11,
    GSP_ADD_CAUSE_COMMAND_ALREADY_IN_EXECUTION = 12,
    GSP_ADD_CAUSE_BLOCKED_BY_HEALTH = 13,
    GSP_ADD_CAUSE_1_OF_N_CONTROL = 14,
    GSP_ADD_CAUSE_ABORTION_BY_CANCEL = 15,
    GSP_ADD_CAUSE_TIME_LIMIT_OVER = 16,
    GSP_ADD_CAUSE_ABORTION_BY_TRIP = 17,
    GSP_ADD_CAUSE_OBJECT_NOT_SELECTED = 18,
    GSP_ADD_CAUSE_OBJECT_ALREADY_SELECTED = 19,
    GSP_ADD_CAUSE_NO_ACCESS_AUTHORITY = 20,
    GSP_ADD_CAUSE_ENDED_WITH_OVERSHOOT = 21,
    GSP_ADD_CAUSE_ABORTION_DUE_TO_DEVIATION = 22,
    GSP_ADD_CAUSE_ABORTION_BY_COMMUNICATION_LOSS = 23,
    GSP_ADD_CAUSE_ABORTION_BY_COMMAND = 24,
    GSP_ADD_CAUSE_NONE = 25,
    GSP_ADD_CAUSE_INCONSISTENT_PARAMETERS = 26,
    GSP_ADD_CAUSE_LOCKED_BY_OTHER_CLIENT = 27
} GspControlAddCause;

typedef enum {
    GSP_CONTROL_ERROR_NO_ERROR = 0,
    GSP_CONTROL_ERROR_UNKNOWN = 1,
    GSP_CONTROL_ERROR_TIMEOUT_TEST = 2,
    GSP_CONTROL_ERROR_OPERATOR_TEST = 3
} GspControlLastApplError;

#if (CONFIG_PROVIDE_OLD_FC_DEFINES == 1)
#define ST DLT860_FC_ST
#define MX DLT860_FC_MX
#define SP DLT860_FC_SP
#define SV DLT860_FC_SV
#define CF DLT860_FC_CF
#define DC DLT860_FC_DC
#define SG DLT860_FC_SG
#define SE DLT860_FC_SE
#define SR DLT860_FC_SR
#define OR DLT860_FC_OR
#define BL DLT860_FC_BL
#define EX DLT860_FC_EX
#define CO DLT860_FC_CO
#define ALL DLT860_FC_ALL
#define NONE DLT860_FC_NONE
#endif /* (CONFIG_PROVIDE_OLD_FC_DEFINES == 1) */

/** FCs (Functional constraints) according to IEC 860-7-2 */
typedef enum eGspFunctionalConstraint {
    /** Status information */
    DLT860_FC_ST = 0,
    /** Measurands - analog values */
    DLT860_FC_MX = 1,
    /** Setpoint */
    DLT860_FC_SP = 2,
    /** Substitution */
    DLT860_FC_SV = 3,
    /** Configuration */
    DLT860_FC_CF = 4,
    /** Description */
    DLT860_FC_DC = 5,
    /** Setting group */
    DLT860_FC_SG = 6,
    /** Setting group editable */
    DLT860_FC_SE = 7,
    /** Service response / Service tracking */
    DLT860_FC_SR = 8,
    /** Operate received */
    DLT860_FC_OR = 9,
    /** Blocking */
    DLT860_FC_BL = 10,
    /** Extended definition */
    DLT860_FC_EX = 11,
    /** Control */
    DLT860_FC_CO = 12,
    /** Unicast SV */
    DLT860_FC_US = 13,
    /** Multicast SV */
    DLT860_FC_MS = 14,
    /** Unbuffered report */
    DLT860_FC_RP = 15,
    /** Buffered report */
    DLT860_FC_BR = 16,
    /** Log control blocks */
    DLT860_FC_LG = 17,
    /** Goose control blocks */
    DLT860_FC_GO = 18,
    /** All FCs - wildcard value */
    DLT860_FC_ALL = 99,
    DLT860_FC_NONE = -1
} GspFunctionalConstraint;

LIB860_API char* GspFunctionalConstraint_toString(GspFunctionalConstraint fc);
LIB860_API GspFunctionalConstraint GspFunctionalConstraint_fromString(const char* fcString);

typedef uint16_t GspQuality;
typedef uint16_t GspValidity;

#define GSP_QUALITY_VALIDITY_GOOD 0
#define GSP_QUALITY_VALIDITY_INVALID 2
#define GSP_QUALITY_VALIDITY_RESERVED 1
#define GSP_QUALITY_VALIDITY_QUESTIONABLE 3
#define GSP_QUALITY_DETAIL_OVERFLOW 4
#define GSP_QUALITY_DETAIL_OUT_OF_RANGE 8
#define GSP_QUALITY_DETAIL_BAD_REFERENCE 16
#define GSP_QUALITY_DETAIL_OSCILLATORY 32
#define GSP_QUALITY_DETAIL_FAILURE 64
#define GSP_QUALITY_DETAIL_OLD_DATA 128
#define GSP_QUALITY_DETAIL_INCONSISTENT 256
#define GSP_QUALITY_DETAIL_INACCURATE 512
#define GSP_QUALITY_SOURCE_SUBSTITUTED 1024
#define GSP_QUALITY_TEST 2048
#define GSP_QUALITY_OPERATOR_BLOCKED  4096
#define GSP_QUALITY_DERIVED 8192

LIB860_API GspValidity GspQuality_getValidity(GspQuality* self);

LIB860_API void GspQuality_setValidity(GspQuality* self, GspValidity validity);

LIB860_API void GspQuality_setFlag(GspQuality* self, int flag);

LIB860_API void GspQuality_unsetFlag(GspQuality* self, int flag);

LIB860_API bool GspQuality_isFlagSet(GspQuality* self, int flag);

LIB860_API GspQuality GspQuality_fromMmsValue(const GspMmsValue* mmsValue);

typedef enum {
    GSP_DBPOS_INTERMEDIATE_STATE = 0,
    GSP_DBPOS_OFF = 1,
    GSP_DBPOS_ON = 2,
    GSP_DBPOS_BAD_STATE = 3
} GspDbpos;

LIB860_API GspDbpos GspDbpos_fromMmsValue(const GspMmsValue* mmsValue);

LIB860_API GspMmsValue* GspDbpos_toMmsValue(GspMmsValue* mmsValue, GspDbpos dbpos);

typedef union {
    uint8_t val[8];
} GspTimestamp;

LIB860_API GspTimestamp* GspTimestamp_create(void);

LIB860_API GspTimestamp* GspTimestamp_createFromByteArray(uint8_t* byteArray);

LIB860_API void GspTimestamp_destroy(GspTimestamp* self);

LIB860_API void GspTimestamp_clearFlags(GspTimestamp* self);

LIB860_API uint32_t GspTimestamp_getTimeInSeconds(GspTimestamp* self);

LIB860_API uint64_t GspTimestamp_getTimeInMs(GspTimestamp* self);

LIB860_API bool GspTimestamp_isLeapSecondKnown(GspTimestamp* self);

LIB860_API void GspTimestamp_setLeapSecondKnown(GspTimestamp* self, bool value);

LIB860_API bool GspTimestamp_hasClockFailure(GspTimestamp* self);

LIB860_API void GspTimestamp_setClockFailure(GspTimestamp* self, bool value);

LIB860_API bool GspTimestamp_isClockNotSynchronized(GspTimestamp* self);

LIB860_API void GspTimestamp_setClockNotSynchronized(GspTimestamp* self, bool value);

LIB860_API int GspTimestamp_getSubsecondPrecision(GspTimestamp* self);

LIB860_API void GspTimestamp_setSubsecondPrecision(GspTimestamp* self, int subsecondPrecision);

LIB860_API void GspTimestamp_setTimeInSeconds(GspTimestamp* self, uint32_t secondsSinceEpoch);

LIB860_API void GspTimestamp_setTimeInMilliseconds(GspTimestamp* self, uint64_t millisSinceEpoch);

LIB860_API char* LibDLT860_getVersionString(void);

#endif /* GSP_DLT860_COMMON_H_ */
