#ifndef REPOETSETPARADEFINE_H
#define REPOETSETPARADEFINE_H
#include <QString>

struct reportSetPara
{
	bool bSelTestObject;
	bool bSelTransStationInfo;
	bool bSelDeviceInfo;
	bool bSelRating;//额定值
	bool bSelTestDeviceInfo;
	bool bSelTestPara;
	bool bSelTestName;
	bool bSelCommonPara;
	bool bSelMarkPara;
	bool bSelSwitchPara;
	bool bSelTestResult;
	bool bSelTestItemPara;
	bool bSelTestItemResult;

	QString strReportTitle;
	QString strTransStationName;
	QString strTransStationAddress;
	QString strReturnCircuitName;
	QString strReturnCircuitAddress;
	QString strTestPersionName;

	QString strDeviceTestedName;
	QString strDeviceTestedID;//被测装置型号
	QString strDeviceTestedAddress;
	QString strManufacturer;
	QString strSerialNumber;
	QString strCustomOrderID;
	QString strAddInfo;//附加信息

	reportSetPara()
	{
		bSelTestObject = true;
		bSelTransStationInfo = true;
		bSelDeviceInfo = true;
		bSelRating = true;//额定值
		bSelTestDeviceInfo = true;
		bSelTestPara = true;
		bSelTestName = true;
		bSelCommonPara = true;
		bSelMarkPara = true;
		bSelSwitchPara = true;
		bSelTestResult = true;
		bSelTestItemPara = true;
		bSelTestItemResult = true;
		strReportTitle = "";
		strTransStationName = "";
		strTransStationAddress = "";
		strReturnCircuitName = "";
		strReturnCircuitAddress = "";
		strTestPersionName = "";

		strDeviceTestedName = "";
		strDeviceTestedID = "";//被测装置型号
		strDeviceTestedAddress = "";
		strManufacturer = "";
		strSerialNumber = "";
		strCustomOrderID = "";
		strAddInfo = "";//附加信息
	}

	reportSetPara &operator = (const reportSetPara &right)
	{
		bSelTestObject = right.bSelTestObject;
		bSelTransStationInfo = right.bSelTransStationInfo;
		bSelDeviceInfo = right.bSelDeviceInfo;
		bSelRating = right.bSelRating;//额定值
		bSelTestDeviceInfo = right.bSelTestDeviceInfo;
		bSelTestPara = right.bSelTestPara;
		bSelTestName = right.bSelTestName;
		bSelCommonPara = right.bSelCommonPara;
		bSelMarkPara = right.bSelMarkPara;
		bSelSwitchPara = right.bSelSwitchPara;
		bSelTestResult = right.bSelTestResult;
		bSelTestItemPara = right.bSelTestItemPara;
		bSelTestItemResult = right.bSelTestItemResult;

		strReportTitle = right.strReportTitle;
		strTransStationName = right.strTransStationName;
		strTransStationAddress = right.strTransStationAddress;
		strReturnCircuitName = right.strReturnCircuitName;
		strReturnCircuitAddress = right.strReturnCircuitAddress;
		strTestPersionName = right.strTestPersionName;

		strDeviceTestedName = right.strDeviceTestedName;
		strDeviceTestedID = right.strDeviceTestedID;//被测装置型号
		strDeviceTestedAddress = right.strDeviceTestedAddress;
		strManufacturer = right.strManufacturer;
		strSerialNumber = right.strSerialNumber;
		strCustomOrderID = right.strCustomOrderID;
		strAddInfo = right.strAddInfo;//附加信息
		return *this;
	}
};
#endif