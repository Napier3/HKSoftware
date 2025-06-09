#include "QSettingLineEdit.h"


QSettingLineEdit::QSettingLineEdit(QWidget *parent):QSttLineEdit(parent)
{
	m_StartTime = QTime::currentTime();	
	m_SettingCloseTime = QTime::currentTime();
	m_bEditState = false;
	QObject::connect(this, SIGNAL(textChanged(const QString &)), this, SLOT(slot_textChanged(const QString &)), Qt::UniqueConnection);
}

QSettingLineEdit::~QSettingLineEdit()
{
}

void QSettingLineEdit::UpdateText(const QString &strText)
{
	setText(strText);
}
void QSettingLineEdit::RefushData()
{
	QString sValue = GetShowText();
	setText(sValue);

	QPalette palette = this->palette();

	if (!IsSetting())	//20241018 huangliang 设置定值后颜色
		palette.setColor(QPalette::Text, Qt::black); // 设置色
	else
		palette.setColor(QPalette::Text, g_SettingColor); // 设置色
	
	this->setPalette(palette);
}
void QSettingLineEdit::mousePressEvent(QMouseEvent *event)
{
	//如果单击了就触发clicked信号
	if (event->button() == Qt::LeftButton)
	{
		ShowSettingDlg();
	}

	//将该事件传给父类处理
	QLineEdit::mousePressEvent(event);
}
void QSettingLineEdit::focusInEvent(QFocusEvent *event)
{
	//ShowSettingDlg();
	//QObject *pParent = this->parent();
	//if(pParent != NULL)
	//	((QWidget*)pParent)->setFocus();	//取消当前对象的焦点

	////将该事件传给父类处理
	//QLineEdit::focusInEvent(event);
}
void QSettingLineEdit::ShowSettingDlg()
{
	if(isReadOnly()) 
		return ;
	if(!isEnabled()) 
		return ;

	if (IsSetting())	//20240903 huangliang 已关联定值
	{
		GetSettingDvmSelect();
		return;
	}

	if (m_bEditState)
	{
		m_bShow = false;
		int msecsTime = m_StartTime.msecsTo(QTime::currentTime());
        if (msecsTime < 1 * 1000)	//20240801 huangliang 超过1s，编辑恢复可以弹出定值关联界面
		{
			return;	//继续编辑
		}

		m_bEditState = false;
		GetSettingDvmSelect();
		return;
	}

	int mCloseTime = m_SettingCloseTime.msecsTo(QTime::currentTime());
	if (mCloseTime > 1 * 1000)	//20240903 huangliang 超过1s，编辑恢复可以弹出定值关联界面
	{
		GetSettingDvmSelect();
		return;	
	}

	if (m_bShow)   //20240731 huangliang 定值关联窗口已显示，则隐藏
	{
		m_bEditState = true;
		m_StartTime = QTime::currentTime();
		m_pDlgSetting->hide();
		this->selectAll();
		this->setFocus();
		return;
	}

	GetSettingDvmSelect();
}
void QSettingLineEdit::slot_textChanged(const QString &strText)
{
    if (m_bEditState)	//20240801 huangliang  编辑中就一直更新记录时间
	{
		m_StartTime = QTime::currentTime();
	}
}

void QSettingLineEdit::SetProperty(const CString &sFormat)
{
	m_strFormat = sFormat;	//20240802 huangliang 未保存路径ID成功
	if(sFormat != "")
		setProperty(SETTING_ID_PATH, sFormat);	//添加属性
	else 
		setProperty(SETTING_ID_PATH, QVariant());	//删除属性
}

void QSettingLineEdit::connectSetting()
{
	QObject::connect(m_pDlgSetting, SIGNAL(sig_Setting()), this, SLOT(slot_Setting()), Qt::UniqueConnection);
	QObject::connect(m_pDlgSetting, SIGNAL(sig_Clear()), this, SLOT(slot_Clear()), Qt::UniqueConnection);
	QObject::connect(m_pDlgSetting, SIGNAL(sig_Cannel(bool)), this, SLOT(slot_Cannel(bool)), Qt::UniqueConnection);
}
void QSettingLineEdit::Disconnect()
{
	QObject::disconnect(m_pDlgSetting, SIGNAL(sig_Setting()), this, SLOT(slot_Setting()));
	QObject::disconnect(m_pDlgSetting, SIGNAL(sig_Clear()), this, SLOT(slot_Clear()));
	QObject::disconnect(m_pDlgSetting, SIGNAL(sig_Cannel(bool)), this, SLOT(slot_Cannel(bool)));
}
void QSettingLineEdit::slot_Setting()
{
	DlgReturnSetting();
	Disconnect();
}
void QSettingLineEdit::slot_Clear()
{
	DlgReturnClear();
	Disconnect();
}
void QSettingLineEdit::slot_Cannel(bool bHide)
{
	////if (bHide)
	////	m_bShow = false;    //20240731 huangliang
	m_SettingCloseTime = QTime::currentTime();	//20240903 huangliang 定值框关闭时

	DlgReturnCannel();
	Disconnect();
}

BOOL QSettingLineEdit::IsSetting()
{
	if (g_nSettingShowType == STT_SETTING_SHOW_TYPE_NoSetting)	//20240719 huangliang  不显示定值
		return FALSE;
	QVariant var = QObject::property(SETTING_ID_PATH);
	if(var.toString() == "")
		return FALSE;
	return TRUE;
}

CString QSettingLineEdit::GetText()
{
	if (!IsSetting())
	{
		return this->text();	//不是定值关联就返回控件本身值
	}

	return m_strFormat;	//是定值关联就返回关联路径
}
