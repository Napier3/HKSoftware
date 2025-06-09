//SttLicenseApi.h
#ifndef __SttLicenseApi_h__
#define __SttLicenseApi_h__

#pragma once

//初始化当前设备的授权
bool SttLicenseInit();  //初始化
bool SttLicenseOpen();//打开文件，文件内容更新
void SttLicenseExit();

//是否可以使用测试功能模块。
//判断授权是否有效，三个判断逻辑：
//       1，strSN\strModuleID是否正确
//       2，如果pszKey中包含授权时间区间，则判断当前时间是否在授权区间之内
//       3，如果pszKey中包含授权使用次数，则判断当前使用次数是否在授权区间之内
//strSN：产品SN；strModuleID：产品模块ID
//nCurrYear、nCurrMonth、nCurrDay：当前的日期
//nCurrTimes：已经使用的次数
bool SttLicenseCanUse(char *strSN, char *strModuleID
                      , int nCurrYear, int nCurrMonth, int nCurrDay
                      , int nCurrTimes);

#endif


