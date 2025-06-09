#include "SettingInterface.h"
#include "../../../SttCmd/GuideBook/SttMacroTest.h"

//SettingSelectDlg* g_pSettingSelectDlg = NULL;		//定值选择界面//20240802 huangliang 不再使用，删除此处代码
SettingSelectDlg* g_pSettingSelectModalDlg = NULL;		//20240724 huangliang  显示定值选择界面，Qt::Popup属性可以不区分模态和非模态
//G_HL_SETTING_FUN *g_pSettingSelectFun = NULL;			//20240802 huangliang 不再使用，删除此处代码

int g_nSettingShowType = STT_SETTING_SHOW_TYPE_INDEX_Value;		//显示类型0不显示定值关联，1值、2名称、3名称+值
//CExBaseList* g_pDvmDevice_AttachSetting = NULL;	//模板
CDataMaps *g_pCurrTestMacroUI_DataMaps = NULL;	//记录匹配关系

QColor g_SettingColor = Qt::blue; //QColor(240, 240, 240);	//20241018 huangliang 记录定值关联后控件颜色


CSettingInterface::CSettingInterface(void)
{	
	m_pDataInMap = NULL;
	m_pObject = NULL;	
    m_pDlgSetting = NULL;//20240731 huangliang
    m_bShow = false;

	m_strFormat = "";
	m_strName = "";
	m_strValue = "";
	m_iShowLen = -1;
}

CSettingInterface::~CSettingInterface(void)
{	
}

void CSettingInterface::UpdateObjectText(CExBaseObject *pObject, int iShowLen)
{
	UpdateObjectText(pObject, "", iShowLen);
}
void CSettingInterface::UpdateObjectText(CExBaseObject *pObject, CString strValue, int iShowLen)
{
	SetProperty("");//20241017 huangliang 同一控件，关联了不同对象后需要清除原控件中的关联信息

	m_iShowLen = iShowLen;
	m_pObject = pObject;
	if (m_pObject == NULL)
		return;	

	if (g_nSettingShowType == STT_SETTING_SHOW_TYPE_NoSetting)	//20240719 huangliang  不显示定值
	{		
		m_strValue = strValue;
		if (strValue == "")
		{
			if (m_pObject->GetClassID() == DVMCLASSID_CDVMDATA)
				m_strValue = ((CDvmData*)m_pObject)->m_strValue;
			else if (m_pObject->GetClassID() == STTGBXMLCLASSID_CSTTMACROPARADATA)
				m_strValue = ((CSttMacroTestParaData*)m_pObject)->m_strValue;
			else if (m_pObject->GetClassID() == CHARCLASSID_CCHARINTERFACEVARIABLE)	//20241017 huangliang 新增支持对象类型CCharInterfaceVariable
				m_strValue = ((CCharInterfaceVariable*)m_pObject)->m_strValue;
		}

		RefushData();
		return;
	}

	m_pDataInMap = NULL;

	CString sValue, sFormat;
	if (m_pObject->GetClassID() == DVMCLASSID_CDVMDATA)
	{
		sValue = ((CDvmData*)m_pObject)->m_strValue;
		sFormat = ((CDvmData*)m_pObject)->m_strFormat;
	}
	else if (m_pObject->GetClassID() == STTGBXMLCLASSID_CSTTMACROPARADATA)
	{
		sValue = ((CSttMacroTestParaData*)m_pObject)->m_strValue;
		sFormat = ((CSttMacroTestParaData*)m_pObject)->m_strValue;
	}
	else if (m_pObject->GetClassID() == CHARCLASSID_CCHARINTERFACEVARIABLE)	//20241017 huangliang 新增支持对象类型CCharInterfaceVariable
	{
		sValue = ((CCharInterfaceVariable*)m_pObject)->m_strValue;
		sFormat = ((CCharInterfaceVariable*)m_pObject)->m_strValue;
	}

	SetItemText(sValue, sFormat);
	//if (strValue != "")	//20240730 huangliang 记录原值处理后数据
	if (m_strValue == "")	//20240923 huangliang 在未找到关联值后才赋传入值
		m_strValue = strValue;
}

void CSettingInterface::UpdateStructText(CVariantDataAddress oVarAddress, int iShowLen)
{	
	SetProperty("");//20241017 huangliang 同一控件，关联了不同对象后需要清除原控件中的关联信息

	m_iShowLen = iShowLen;
	if (g_nSettingShowType == STT_SETTING_SHOW_TYPE_NoSetting)	//20240719 huangliang  不显示定值
	{
		m_strValue = oVarAddress.ToString();
		RefushData();
		return;
	}

	m_pObject = NULL;
	m_oVarAddress = oVarAddress;

	if (g_pCurrTestMacroUI_DataMaps != NULL)	//查找在Maps中对象
	{
		m_pDataInMap = (CXDataMap *)g_pCurrTestMacroUI_DataMaps->FindAddressChild(m_oVarAddress);
	}

	//取出值
	CString strValue = m_oVarAddress.ToString();	
	CString strFormat = "";
	if(m_pDataInMap != NULL)
		strFormat = m_pDataInMap->m_strMapID;

	SetItemText(strValue, strFormat);
}

void CSettingInterface::SetItemText(const CString &sValue, const CString &sFormat)
{
	m_strName = g_sLangTxt_Setting_NoWord;
	SetFloatValue(sValue);
	if(sFormat != "")	//通过sFormat获取模型数据中名称或值
	{
		QString strValue;	//20240820 huangliang 
		if (CSttGlobalModel::AnalysisPath(sFormat, &m_strName, &strValue))
		{
	//设置全路径及属性
			SetProperty(sFormat);

	//设置值
			SetFloatValue(strValue);
		}		
	}

	RefushData();
}

//从键盘输入中获取选择定值
bool CSettingInterface::GetSettingDvmSelect()
{
	if (g_nSettingShowType == STT_SETTING_SHOW_TYPE_NoSetting)	//20240719 huangliang  不显示定值
		return false;
	if(m_oVarAddress.vt == 0 && m_pObject == NULL)
		return false;

	QPoint globalPosition = QCursor::pos();
	m_iBtnX = globalPosition.rx() + 20;
	m_iBtnY = globalPosition.ry();

	CString strFormat = "";
	if(m_pObject != NULL)
	{
		strFormat = GetObjectFormat();
	}
	else if(m_pDataInMap != NULL)	
	{
		strFormat = m_pDataInMap->m_strMapID;
	}	

	//20240909 huangliang 未关联时，清除strFormat
	if (m_strName == g_sLangTxt_Setting_NoWord)
	{
		strFormat = "";
	}
	
	if (g_pSettingSelectModalDlg != NULL)
	{
		m_pDlgSetting = g_pSettingSelectModalDlg;
	connectSetting();

		m_pDlgSetting->move(m_iBtnX, m_iBtnY);
		m_pDlgSetting->InitShow(strFormat, m_strName, m_strValue);
		m_pDlgSetting->show();
		m_pDlgSetting->activateWindow();
		m_pDlgSetting->setFocus();
        m_bShow = true;
	return true;
	}
	return false;
}

void CSettingInterface::DlgReturnSetting()
{
	if (m_pDlgSetting == NULL)
		return;

	CString strFullPath = m_pDlgSetting->m_strSelectFullPath;
	if(strFullPath == m_strFormat || strFullPath == "")	//没有改变
		return;

	SetProperty(strFullPath);
	SetFloatValue(m_pDlgSetting->m_strSelectValue);
	m_strName = m_pDlgSetting->m_strSelectName;
	if(m_pObject != NULL)
	{
		SetObjectFormat(strFullPath);
		SetObjectValue(m_strValue);
	}
	else 
	{
		if (g_pCurrTestMacroUI_DataMaps == NULL)
			return ;

		if(m_pDataInMap == NULL)	//新增关联定值到Maps中
			m_pDataInMap = g_pCurrTestMacroUI_DataMaps->AddAddressChild(m_oVarAddress);
		m_pDataInMap->m_strMapID = strFullPath;
		//m_oVarAddress				//更新地址对应值
		m_oVarAddress.FromString(m_strValue.GetString());
	}
	RefushData();
}

void CSettingInterface::InitSetting()
{
	if (m_pObject != NULL)
	{
		SetObjectFormat("");
		SetFloatValue(GetObjectValue());	//删除关联后，设回原值
	}
	else 	//删除Maps中关联定值
	{
		if (g_pCurrTestMacroUI_DataMaps == NULL)
			return;
		if (m_pDataInMap != NULL)
		{
			g_pCurrTestMacroUI_DataMaps->Delete(m_pDataInMap);
			m_pDataInMap = NULL;
		}

		CString strValue = m_oVarAddress.ToString();
		SetFloatValue(strValue);
	}

	SetProperty("");
	m_strName = g_sLangTxt_Setting_NoWord;
	RefushData();
}
void CSettingInterface::DlgReturnClear()
{
	if (m_strName == g_sLangTxt_Setting_NoFind)//20241017 huangliang 未找到的情况下已经不是定值关联，取消后没有去恢复设置显示“尚未关联”
	{
		InitSetting();
		return;
	}

	if(!IsSetting())	
		return ;

	InitSetting();
}

void CSettingInterface::DlgReturnCannel()
{
	Disconnect();
}

CString CSettingInterface::GetShowText()
{
	if(!IsSetting())
		return m_strValue;

	if (m_strName == g_sLangTxt_Setting_NoWord || m_strName == "")
		return m_strValue;

	if (g_nSettingShowType == STT_SETTING_SHOW_TYPE_NoSetting)
		return m_strValue;
	else if (g_nSettingShowType == STT_SETTING_SHOW_TYPE_INDEX_Value)
		return m_strValue;
	else if (g_nSettingShowType == STT_SETTING_SHOW_TYPE_INDEX_Name)
		return m_strName;
	return m_strName + " " + m_strValue;
}
void CSettingInterface::SetFloatValue(const CString &sVlaue)
{
	m_strValue = sVlaue;
	if(m_iShowLen < 0)
		return ;

	double dValue = m_strValue.toDouble();
	m_strValue = QString::number(dValue, 'f', m_iShowLen);
}

CString CSettingInterface::GetObjectFormat()
{
	if (m_pObject->GetClassID() == DVMCLASSID_CDVMDATA)
		return ((CDvmData*)m_pObject)->m_strFormat;
	else if (m_pObject->GetClassID() == STTGBXMLCLASSID_CSTTMACROPARADATA)
		return ((CSttMacroTestParaData*)m_pObject)->m_strValue;
	else if (m_pObject->GetClassID() == CHARCLASSID_CCHARINTERFACEVARIABLE)	//20241017 huangliang 新增支持对象类型CCharInterfaceVariable
		return ((CCharInterfaceVariable*)m_pObject)->m_strValue;
	return "";
}

void CSettingInterface::SetObjectFormat(CString sFormat)
{
	if (m_pObject->GetClassID() == DVMCLASSID_CDVMDATA)
		((CDvmData*)m_pObject)->m_strFormat = sFormat;
	else if (m_pObject->GetClassID() == STTGBXMLCLASSID_CSTTMACROPARADATA)
		((CSttMacroTestParaData*)m_pObject)->m_strValue = sFormat;
	else if (m_pObject->GetClassID() == CHARCLASSID_CCHARINTERFACEVARIABLE)	//20241017 huangliang 新增支持对象类型CCharInterfaceVariable
		((CCharInterfaceVariable*)m_pObject)->m_strValue = sFormat;
}

CString CSettingInterface::GetObjectValue()
{
	if (m_pObject->GetClassID() == DVMCLASSID_CDVMDATA)
		return ((CDvmData*)m_pObject)->m_strValue;
	else if (m_pObject->GetClassID() == STTGBXMLCLASSID_CSTTMACROPARADATA)
		return ((CSttMacroTestParaData*)m_pObject)->m_strValue;
	else if (m_pObject->GetClassID() == CHARCLASSID_CCHARINTERFACEVARIABLE)	//20241017 huangliang 新增支持对象类型CCharInterfaceVariable
		return ((CCharInterfaceVariable*)m_pObject)->m_strValue;
	return "";
}

void CSettingInterface::SetObjectValue(CString sValue)
{
	if (m_pObject->GetClassID() == DVMCLASSID_CDVMDATA)
		((CDvmData*)m_pObject)->m_strValue = sValue;
	else if (m_pObject->GetClassID() == STTGBXMLCLASSID_CSTTMACROPARADATA)
	{

	}
	else if (m_pObject->GetClassID() == CHARCLASSID_CCHARINTERFACEVARIABLE)	//20241017 huangliang 新增支持对象类型CCharInterfaceVariable
	{

	}
}

BOOL CSettingInterface::IsSetting()
{
	if (g_nSettingShowType == STT_SETTING_SHOW_TYPE_NoSetting)	//20240719 huangliang  不显示定值
		return FALSE;
	if(m_oVarAddress.vt == 0 && m_pObject == NULL)
		return FALSE;

	if(m_pObject != NULL)
	{
		//20240909 huangliang 未关联时，认为不是定值关联，CSttMacroTestParaData类型数据会返回Format值
		if (m_strName == g_sLangTxt_Setting_NoWord)	
			return FALSE;

		if (GetObjectFormat() == "")
			return FALSE;
	}
	else 	
	{
		if (g_pCurrTestMacroUI_DataMaps == NULL)
			return FALSE;
		if(m_pDataInMap == NULL)
			return FALSE;
	}
	return TRUE;
}
