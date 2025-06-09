#ifndef TMT_ADJUST_CAL_H
#define TMT_ADJUST_CAL_H

#include "../tmt_adjust_sys_parameter.h"
#include "tmt_adjust_test.h"

//����У׼���ܵĲ�����ģ���š�ͨ����š�Ƶ��ѡ��ȣ�����ģ����������л��������ò���
BOOL stt_adj_get_output_vector(PTMT_ADJ_MODULE_OUTPUT pParas, TMT_ADJ_CAL_VECTOR &oAdjCalVector);
BOOL stt_adj_get_output_vector(PTMT_ADJ_MODULE_OUTPUT pParas, TMT_ADJ_CAL_VECTOR_THREE &oAdjCalVector);

//����У׼���ܵĲ�����ģ���š�ͨ����š�Ƶ��ѡ��ȣ�����װ��ϵͳ������������л��У׼ϵ��
//У׼ϵ����õ��߼����ο�TMT_ADJUST_ONE_PARAS˵��
PSTT_ADJUST_ITEM stt_adj_find_adjust_item(PSTT_DEVICESYSTEMPARAMETER pDvSysParas,  TMT_ADJUST_ONE_PARAS &oAdjOneParas);
BOOL stt_adj_get_adjust_item_ref(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, TMT_ADJ_CAL_VECTOR &oAdjCalVector);
BOOL stt_adj_get_adjust_item_ref(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, TMT_ADJ_CAL_VECTOR_THREE &oAdjCalVector);

//����ģ�����������У׼����������У׼ϵ��
//����������������У׼����ִ�ж����е���
BOOL stt_adj_cal(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, PTMT_ADJ_MODULE_OUTPUT pModuleOutput, PTMT_ADJUST_ONE poAdjParas);
BOOL stt_adj_cal(PSTT_DEVICESYSTEMPARAMETER pDvSysParas,  PTMT_ADJUST_ONE2POINTS poAdjParas);
BOOL stt_adj_cal(PSTT_DEVICESYSTEMPARAMETER pDvSysParas,  PTMT_ADJUST_ANGLE poAdjParas);
BOOL stt_adj_cal(PSTT_DEVICESYSTEMPARAMETER pDvSysParas,  PTMT_ADJUST_FREQ poAdjParas);
BOOL stt_adj_cal(PSTT_DEVICESYSTEMPARAMETER pDvSysParas,  PTMT_ADJUST_DCZERO poAdjParas);
BOOL stt_adj_cal(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, PTMT_ADJ_MODULE_OUTPUT pModuleOutput, PTMT_ADJUST_THREE poAdjParas);

//����У׼��������ṹ�壬����У׼ϵ������������������stt_adj_cal�е���
BOOL stt_adj_vector_cal(TMT_ADJ_CAL_VECTOR &oAdjCalVector);
BOOL stt_adj_vector_cal(TMT_ADJ_CAL_VECTOR_THREE &oAdjCalVector,TMT_ADJUST_THREE_RESULTS &oAdjResults);

#endif // TMT_ADJUST_CAL_H

