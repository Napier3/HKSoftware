#pragma once

#include "settingselectdlg.h"
#include <QCursor>
#include <QDialog>
#include "../../../../../Module/DataMngr/DataMaps.h"
#include "../../../../../Module/DataMngr/DvmData.h"
#include "../../../../../Module/System/VariantDataAddress.h"
#include "../../../XLangResource_Native.h"
#include "../../../../../AutoTest/Module/Characteristic/CharInterfaceVariable.h"

#define	SETTING_ID_PATH		                                      "SettingIdPath"
#define STT_SETTING_LINEEDIT_ClassID                               "QSettingLineEdit"
#define STT_SETTING_ITEM_ClassID                                   "QSettingItem"

#define STT_SETTING_SHOW_TYPE_NoSetting									  0		//不显示定值关联
#define STT_SETTING_SHOW_TYPE_INDEX_Value                                 1		//显示关联的值
#define STT_SETTING_SHOW_TYPE_INDEX_Name                                  2		//显示关联的名称
#define STT_SETTING_SHOW_TYPE_INDEX_ValueAndName                          3		//显示关联名称+值


typedef void (G_HL_SETTING_FUN)(QWidget *parent);	//定值选择界面的选择函数

class CSettingInterface
{
public:
	CSettingInterface(void);
	virtual ~CSettingInterface(void);

	//对象设置
	virtual void UpdateObjectText(CExBaseObject *pObject, int iShowLen=3);	//记录需要关联的对象；
	virtual void UpdateObjectText(CExBaseObject *pObject, CString strValue, int iShowLen = 3);

	//结构体设置
	virtual void UpdateStructText(CVariantDataAddress oVarAddress, int iShowLen = 3);		//记录需要关联的地址；

	virtual void RefushData() = 0;	//于刷新界面值；

	virtual BOOL IsSetting();	//依据记录信息判断是否为关联定值，非QObject无法依据属性判断

	void DlgReturnClear();	//删除关联信息

	QString GetValue(){ return  m_strValue; }	//只获取值
	virtual CString GetText()=0;	//20240722 huangliang 获取对象值，是定值关联则返回关联路径

protected:
	CExBaseObject *m_pObject;	//传递对象进来
	CVariantDataAddress m_oVarAddress;	//传递地址进来
	CXDataMap *m_pDataInMap;			//地址对应的Map中对象

	SettingSelectDlg *m_pDlgSetting;	//记录是模态对话框还是非模态对话框的地址

	CString m_strFormat;		//定值路径
	CString m_strName;			//定值名称
	CString m_strValue;			//值

	int m_iShowLen;		//显示浮点数时，保留小数位数

	int m_iBtnX;		//定值界面显示位置
	int m_iBtnY;
    bool m_bShow;       //20240731 huangliang

protected:
	//从模型数据中查找对应名称
	void SetItemText(const CString &sValue, const CString &sFormat);
	
	//显示定值选择界面
	bool GetSettingDvmSelect();

	//关联定值选择界面信号
	virtual void connectSetting()=0;
	virtual void Disconnect()=0;

	//选择定值
	void DlgReturnSetting();
	//取消选择
	void DlgReturnCannel();
	void InitSetting();

	CString GetShowText();
	void SetFloatValue(const CString &sVlaue);
	virtual void SetProperty(const CString &sFormat) = 0;

	CString GetObjectFormat();
	void SetObjectFormat(CString sFormat);

	CString GetObjectValue();
	void SetObjectValue(CString sValue);
};

//extern SettingSelectDlg* g_pSettingSelectDlg;			//定值选择界面 //20240802 huangliang 不再使用，删除此处代码
extern SettingSelectDlg* g_pSettingSelectModalDlg;		//20240724 huangliang  模态对话框中显示定值选择界面
//extern G_HL_SETTING_FUN *g_pSettingSelectFun;			//20240802 huangliang 不再使用，删除此处代码

extern int g_nSettingShowType;							//显示类型0不显示定值关联，1值、2名称、3名称+值
//extern CExBaseList* g_pDvmDevice_AttachSetting;			//模板
extern CDataMaps *g_pCurrTestMacroUI_DataMaps;			//记录匹配关系，每个基础模块打开后都需重新设置，仅对结构体数据使用，对象定值关联不需使用

extern QColor g_SettingColor;	//20241018 huangliang 记录定值关联后控件颜色