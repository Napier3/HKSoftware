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

	if (!IsSetting())	//20241018 huangliang ���ö�ֵ����ɫ
		palette.setColor(QPalette::Text, Qt::black); // ����ɫ
	else
		palette.setColor(QPalette::Text, g_SettingColor); // ����ɫ
	
	this->setPalette(palette);
}
void QSettingLineEdit::mousePressEvent(QMouseEvent *event)
{
	//��������˾ʹ���clicked�ź�
	if (event->button() == Qt::LeftButton)
	{
		ShowSettingDlg();
	}

	//�����¼��������ദ��
	QLineEdit::mousePressEvent(event);
}
void QSettingLineEdit::focusInEvent(QFocusEvent *event)
{
	//ShowSettingDlg();
	//QObject *pParent = this->parent();
	//if(pParent != NULL)
	//	((QWidget*)pParent)->setFocus();	//ȡ����ǰ����Ľ���

	////�����¼��������ദ��
	//QLineEdit::focusInEvent(event);
}
void QSettingLineEdit::ShowSettingDlg()
{
	if(isReadOnly()) 
		return ;
	if(!isEnabled()) 
		return ;

	if (IsSetting())	//20240903 huangliang �ѹ�����ֵ
	{
		GetSettingDvmSelect();
		return;
	}

	if (m_bEditState)
	{
		m_bShow = false;
		int msecsTime = m_StartTime.msecsTo(QTime::currentTime());
        if (msecsTime < 1 * 1000)	//20240801 huangliang ����1s���༭�ָ����Ե�����ֵ��������
		{
			return;	//�����༭
		}

		m_bEditState = false;
		GetSettingDvmSelect();
		return;
	}

	int mCloseTime = m_SettingCloseTime.msecsTo(QTime::currentTime());
	if (mCloseTime > 1 * 1000)	//20240903 huangliang ����1s���༭�ָ����Ե�����ֵ��������
	{
		GetSettingDvmSelect();
		return;	
	}

	if (m_bShow)   //20240731 huangliang ��ֵ������������ʾ��������
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
    if (m_bEditState)	//20240801 huangliang  �༭�о�һֱ���¼�¼ʱ��
	{
		m_StartTime = QTime::currentTime();
	}
}

void QSettingLineEdit::SetProperty(const CString &sFormat)
{
	m_strFormat = sFormat;	//20240802 huangliang δ����·��ID�ɹ�
	if(sFormat != "")
		setProperty(SETTING_ID_PATH, sFormat);	//�������
	else 
		setProperty(SETTING_ID_PATH, QVariant());	//ɾ������
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
	m_SettingCloseTime = QTime::currentTime();	//20240903 huangliang ��ֵ��ر�ʱ

	DlgReturnCannel();
	Disconnect();
}

BOOL QSettingLineEdit::IsSetting()
{
	if (g_nSettingShowType == STT_SETTING_SHOW_TYPE_NoSetting)	//20240719 huangliang  ����ʾ��ֵ
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
		return this->text();	//���Ƕ�ֵ�����ͷ��ؿؼ�����ֵ
	}

	return m_strFormat;	//�Ƕ�ֵ�����ͷ��ع���·��
}
