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
//20240717 huangliang 删除对父级设置焦点
//	if(m_pTableWidget != NULL)
//		m_pTableWidget->setFocus();	//取消当前对象的焦点
}

//20240806 huangliang 单击事件被过滤后调用
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

	if (!IsSetting())	//20241018 huangliang 设置定值后颜色
		this->setTextColor(Qt::black);
	else
		this->setTextColor(g_SettingColor);
}

void QSettingItem::SetProperty(const CString &sFormat)
{
	m_strFormat = sFormat;	//20240802 huangliang 未保存路径ID成功
	if(sFormat != "")
		QObject::setProperty(SETTING_ID_PATH, sFormat);	//添加属性
	else 
		QObject::setProperty(SETTING_ID_PATH, QVariant());	//删除属性
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
	if (g_nSettingShowType == STT_SETTING_SHOW_TYPE_NoSetting)	//20240719 huangliang  不显示定值
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
		return this->text();	//不是定值关联就返回控件本身值
	}

	return m_strFormat;	//是定值关联就返回关联路径
}
