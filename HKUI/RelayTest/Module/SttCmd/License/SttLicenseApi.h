//SttLicenseApi.h
#ifndef __SttLicenseApi_h__
#define __SttLicenseApi_h__

#pragma once

//��ʼ����ǰ�豸����Ȩ
bool SttLicenseInit();  //��ʼ��
bool SttLicenseOpen();//���ļ����ļ����ݸ���
void SttLicenseExit();

//�Ƿ����ʹ�ò��Թ���ģ�顣
//�ж���Ȩ�Ƿ���Ч�������ж��߼���
//       1��strSN\strModuleID�Ƿ���ȷ
//       2�����pszKey�а�����Ȩʱ�����䣬���жϵ�ǰʱ���Ƿ�����Ȩ����֮��
//       3�����pszKey�а�����Ȩʹ�ô��������жϵ�ǰʹ�ô����Ƿ�����Ȩ����֮��
//strSN����ƷSN��strModuleID����Ʒģ��ID
//nCurrYear��nCurrMonth��nCurrDay����ǰ������
//nCurrTimes���Ѿ�ʹ�õĴ���
bool SttLicenseCanUse(char *strSN, char *strModuleID
                      , int nCurrYear, int nCurrMonth, int nCurrDay
                      , int nCurrTimes);

#endif


