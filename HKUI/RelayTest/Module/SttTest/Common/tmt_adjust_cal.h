#ifndef TMT_ADJUST_CAL_H
#define TMT_ADJUST_CAL_H

#include "tmt_adjust_sys_parameter.h"
#include "tmt_adjust_test.h"

//根据校准功能的参数（模块编号、通道编号、频率选择等），从模块输出参数中获得输出设置参数
bool stt_adj_get_output_vector(PTMT_ADJ_MODULE_OUTPUT pParas, TMT_ADJ_CAL_VECTOR &oAdjCalVector);
bool stt_adj_get_output_vector(PTMT_ADJ_MODULE_OUTPUT pParas, TMT_ADJ_CAL_VECTOR_THREE &oAdjCalVector);

//根据校准功能的参数（模块编号、通道编号、频率选择等），从装置系统参数管理对象中获得校准系数
//校准系数获得的逻辑：参考TMT_ADJUST_ONE_PARAS说明
// PSTT_ADJUST_ITEM stt_adj_find_adjust_item(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, long nModuleType,  long nModule, long nTempretureID, long nChannel, long nFreqSel, float fMaxMag);
// PSTT_ADJUST_ITEM stt_adj_find_adjust_item(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, long nModuleType,  long nModule, long nTempretureID, long nChannel, long nFreqSel, long nGearID);
PSTT_ADJUST_ITEM stt_adj_find_adjust_item(PSTT_DEVICESYSTEMPARAMETER pDvSysParas,  TMT_ADJUST_ONE_PARAS &oAdjOneParas);
bool stt_adj_get_adjust_item_ref(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, TMT_ADJ_CAL_VECTOR &oAdjCalVector);
bool stt_adj_get_adjust_item_ref(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, TMT_ADJ_CAL_VECTOR_THREE &oAdjCalVector);

//根据模块输出参数、校准参数，计算校准系数
//以下两个函数，在校准功能执行对象中调用
bool stt_adj_cal(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, PTMT_ADJ_MODULE_OUTPUT pModuleOutput, PTMT_ADJUST_ONE poAdjParas);
bool stt_adj_cal(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, PTMT_ADJ_MODULECH_OUTPUT pModuleChOutput, PTMT_ADJUST_ONE2POINTS poAdjParas);
bool stt_adj_cal(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, PTMT_ADJ_MODULE_OUTPUT pModuleOutput, PTMT_ADJUST_THREE poAdjParas);

//根据校准计算参数结构体，计算校准系数，以下两个函数在stt_adj_cal中调用
bool stt_adj_vector_cal(TMT_ADJ_CAL_VECTOR &oAdjCalVector);
bool stt_adj_vector_cal(TMT_ADJ_CAL_VECTOR_THREE &oAdjCalVector,TMT_ADJUST_THREE_RESULTS &oAdjResults);

#endif // TMT_ADJUST_CAL_H

