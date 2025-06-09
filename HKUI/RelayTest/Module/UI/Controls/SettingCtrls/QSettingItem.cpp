#include "QSettingItem.h"


//QSettingItem::QSettingItem(const QString &text): QGV_ITEM(text)
//{
//	lParam = 0;
//	m_pEditFunc = NULL;
//	iMaxLen = 0;
//	dwValue = 0;
//	nReserved = 0;
//}
QSettingItem::QSettingItem(QTableWidget *parent): QGV_ITEM("")
{
	lParam = 0;
	m_pEditFunc = NULL;
	iMaxLen = 0;
	dwValue = 0;
	nReserved = 0;

	m_pTableWidget = parent;
    QObject::connect(parent,SIGNAL(itemPressed(QTableWidgetItem *)),this,SLOT(slot_itemPressed(QTableWidgetItem *)), Qt::UniqueConnection);
}

QSettingItem::~QSettingItem(void)
{
}

void QSettingItem::slot_itemPressed(QTableWidgetItem *item)
{
	if(this != item)
	{
		return ;
	}

	GetSettingDvmSelect();
//20240717 huangliang ɾ���Ը������ý���
//	if(m_pTableWidget != NULL)
//		m_pTableWidget->setFocus();	//ȡ����ǰ����Ľ���
}

//20240806 huangliang �����¼������˺����
void QSettingItem::ShowSettingDlg()
{
	GetSettingDvmSelect();
}

void QSettingItem::UpdateText(const QString &strText)
{
	setText(strText);
}
void QSettingItem::RefushData()
{
	QString sValue = GetShowText();
	setText(sValue);

	if (!IsSetting())	//20241018 huangliang ���ö�ֵ����ɫ
		this->setTextColor(Qt::black);
	else
		this->setTextColor(g_SettingColor);
}

void QSettingItem::SetProperty(const CString &sFormat)
{
	m_strFormat = sFormat;	//20240802 huangliang δ����·��ID�ɹ�
	if(sFormat != "")
		QObject::setProperty(SETTING_ID_PATH, sFormat);	//�������
	else 
		QObject::setProperty(SETTING_ID_PATH, QVariant());	//ɾ������
}

void QSettingItem::connectSetting()
{
	QObject::connect(m_pDlgSetting, SIGNAL(sig_Setting()), this, SLOT(slot_Setting()), Qt::UniqueConnection);
	QObject::connect(m_pDlgSetting, SIGNAL(sig_Clear()), this, SLOT(slot_Clear()), Qt::UniqueConnection);
	QObject::connect(m_pDlgSetting, SIGNAL(sig_Cannel(bool)), this, SLOT(slot_Cannel(bool)), Qt::UniqueConnection);

	disconnect(m_pTableWidget,SIGNAL(cellChanged (int,int)),m_pTableWidget,SLOT(slot_OnCellChanged(int ,int)));
}
void QSettingItem::Disconnect()
{
	QObject::disconnect(m_pDlgSetting, SIGNAL(sig_Setting()), this, SLOT(slot_Setting()));
	QObject::disconnect(m_pDlgSetting, SIGNAL(sig_Clear()), this, SLOT(slot_Clear()));
	QObject::disconnect(m_pDlgSetting, SIGNAL(sig_Cannel(bool)), this, SLOT(slot_Cannel(bool)));

	connect(m_pTableWidget,SIGNAL(cellChanged (int,int)),m_pTableWidget,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}

void QSettingItem::slot_Setting()
{
	DlgReturnSetting();
	Disconnect();
}
void QSettingItem::slot_Clear()
{
	DlgReturnClear();
	Disconnect();
}
void QSettingItem::slot_Cannel(bool bHide)
{
	DlgReturnCannel();
	Disconnect();
}

BOOL QSettingItem::IsSetting()
{
	if (g_nSettingShowType == STT_SETTING_SHOW_TYPE_NoSetting)	//20240719 huangliang  ����ʾ��ֵ
		return FALSE;
	QVariant var = QObject::property(SETTING_ID_PATH);
	if(var.toString() == "")
		return FALSE;
	return TRUE;
}

CString QSettingItem::GetText()
{
	if (!IsSetting())
	{
		return this->text();	//���Ƕ�ֵ�����ͷ��ؿؼ�����ֵ
	}

	return m_strFormat;	//�Ƕ�ֵ�����ͷ��ع���·��
}
