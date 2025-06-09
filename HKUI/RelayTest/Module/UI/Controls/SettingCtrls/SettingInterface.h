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

#define STT_SETTING_SHOW_TYPE_NoSetting									  0		//����ʾ��ֵ����
#define STT_SETTING_SHOW_TYPE_INDEX_Value                                 1		//��ʾ������ֵ
#define STT_SETTING_SHOW_TYPE_INDEX_Name                                  2		//��ʾ����������
#define STT_SETTING_SHOW_TYPE_INDEX_ValueAndName                          3		//��ʾ��������+ֵ


typedef void (G_HL_SETTING_FUN)(QWidget *parent);	//��ֵѡ������ѡ����

class CSettingInterface
{
public:
	CSettingInterface(void);
	virtual ~CSettingInterface(void);

	//��������
	virtual void UpdateObjectText(CExBaseObject *pObject, int iShowLen=3);	//��¼��Ҫ�����Ķ���
	virtual void UpdateObjectText(CExBaseObject *pObject, CString strValue, int iShowLen = 3);

	//�ṹ������
	virtual void UpdateStructText(CVariantDataAddress oVarAddress, int iShowLen = 3);		//��¼��Ҫ�����ĵ�ַ��

	virtual void RefushData() = 0;	//��ˢ�½���ֵ��

	virtual BOOL IsSetting();	//���ݼ�¼��Ϣ�ж��Ƿ�Ϊ������ֵ����QObject�޷����������ж�

	void DlgReturnClear();	//ɾ��������Ϣ

	QString GetValue(){ return  m_strValue; }	//ֻ��ȡֵ
	virtual CString GetText()=0;	//20240722 huangliang ��ȡ����ֵ���Ƕ�ֵ�����򷵻ع���·��

protected:
	CExBaseObject *m_pObject;	//���ݶ������
	CVariantDataAddress m_oVarAddress;	//���ݵ�ַ����
	CXDataMap *m_pDataInMap;			//��ַ��Ӧ��Map�ж���

	SettingSelectDlg *m_pDlgSetting;	//��¼��ģ̬�Ի����Ƿ�ģ̬�Ի���ĵ�ַ

	CString m_strFormat;		//��ֵ·��
	CString m_strName;			//��ֵ����
	CString m_strValue;			//ֵ

	int m_iShowLen;		//��ʾ������ʱ������С��λ��

	int m_iBtnX;		//��ֵ������ʾλ��
	int m_iBtnY;
    bool m_bShow;       //20240731 huangliang

protected:
	//��ģ�������в��Ҷ�Ӧ����
	void SetItemText(const CString &sValue, const CString &sFormat);
	
	//��ʾ��ֵѡ�����
	bool GetSettingDvmSelect();

	//������ֵѡ������ź�
	virtual void connectSetting()=0;
	virtual void Disconnect()=0;

	//ѡ��ֵ
	void DlgReturnSetting();
	//ȡ��ѡ��
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

//extern SettingSelectDlg* g_pSettingSelectDlg;			//��ֵѡ����� //20240802 huangliang ����ʹ�ã�ɾ���˴�����
extern SettingSelectDlg* g_pSettingSelectModalDlg;		//20240724 huangliang  ģ̬�Ի�������ʾ��ֵѡ�����
//extern G_HL_SETTING_FUN *g_pSettingSelectFun;			//20240802 huangliang ����ʹ�ã�ɾ���˴�����

extern int g_nSettingShowType;							//��ʾ����0����ʾ��ֵ������1ֵ��2���ơ�3����+ֵ
//extern CExBaseList* g_pDvmDevice_AttachSetting;			//ģ��
extern CDataMaps *g_pCurrTestMacroUI_DataMaps;			//��¼ƥ���ϵ��ÿ������ģ��򿪺����������ã����Խṹ������ʹ�ã�����ֵ��������ʹ��

extern QColor g_SettingColor;	//20241018 huangliang ��¼��ֵ������ؼ���ɫ