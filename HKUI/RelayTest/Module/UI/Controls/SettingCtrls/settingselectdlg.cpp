#include "settingselectdlg.h"
#include "ui_settingselectdlg.h"
#include "../../../../../Module/API/GlobalConfigApi.h"


//20240820 huangliang ת�Ƶ�CSttGlobalModel��
//CExBaseList* g_pDvmDevice_AttachSetting = NULL;	//ģ��	20240806 huangliang 

SettingSelectDlg::SettingSelectDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingSelectDlg)
{
	setModal(false);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Popup);
    ui->setupUi(this);

	ui->label_Name->setText(g_sLangTxt_Setting_NoWord);
	ui->pushButton_Setting->setText(g_sLangTxt_Setting_Link);
	ui->pushButton_cannel->setText(g_sLangTxt_Setting_Cancel);
	ui->pushButton_AllCannel->setText(g_sLangTxt_Setting_CancelAll);
}

SettingSelectDlg::~SettingSelectDlg()
{
    delete ui;
}

void SettingSelectDlg::InitShow(const QString &strFullPath, const QString &strName, const QString &strValue)
{
	m_strSelectFullPath = strFullPath;
	m_strSelectName = strName;
	m_strSelectValue = strValue;

	ui->label_Name->setText(m_strSelectName);
	ui->label_Value->setText(m_strSelectValue);
}

void SettingSelectDlg::slot_SelectModeData(CExBaseObject *pItem)
{
	if(pItem == NULL)
		return ;

	QString strFullPath, strName, strValue;
	if(pItem->GetClassID() == DVMCLASSID_CDVMDATA)
	{
		strName = ((CDvmData*)pItem)->m_strName;
		strValue = ((CDvmData*)pItem)->m_strValue;
	}
	else if(pItem->GetClassID() == DVMCLASSID_CDVMVALUE)
	{
		strName = ((CDvmValue*)pItem)->m_strName;
		strValue = ((CDvmValue*)pItem)->m_strValue;
	}
	else
	{
		return ;
	}

	strFullPath = pItem->GetIDPathEx((CExBaseObject *)pItem->GetRoot(), false);	//20240903 huangliang ��Ҫ��Ŀ¼ID
	
	InitShow(strFullPath, strName, strValue);
	emit sig_Setting();
	this->hide();
}
void SettingSelectDlg::slot_SelectModeData(QString sValue)
{
	if (sValue == "")
		return;

	QString strFullPath, strName, strValue;
	strFullPath = sValue;
	if (!CSttGlobalModel::AnalysisPath(strFullPath, &strName, &strValue))
		return;

	InitShow(strFullPath, strName, strValue);
	emit sig_Setting();
	this->hide();
}

void SettingSelectDlg::on_pushButton_Setting_clicked()
{
	//�����豸ģ���ź�
	this->hide();
	emit sig_ShowSetting(m_strSelectFullPath, m_strSelectName);
}

void SettingSelectDlg::on_pushButton_cannel_clicked()
{
	m_strSelectFullPath = "";
	emit sig_Clear();
    this->hide();
}

void SettingSelectDlg::on_pushButton_AllCannel_clicked()
{
	emit sig_ClearAll();
    this->hide();
}

void SettingSelectDlg::focusOutEvent(QFocusEvent *event)
{
	////�ų��ӿؼ���ȡ����ʱ����
	//if(CheckFocusInChild(this))
	//	return;

	//emit sig_Cannel();
	//this->hide();
}
bool SettingSelectDlg::CheckFocusInChild(QWidget *pParent)
{
	QList<QWidget *> allWidgets = pParent->findChildren<QWidget *>();
	foreach (QWidget *widget, allWidgets) 
	{
		if(widget->hasFocus())
			return true;
		if(CheckFocusInChild(widget))
			return true;
	}
	return false;
}

void SettingSelectDlg::keyPressEvent(QKeyEvent *event)
{
	QDialog::keyPressEvent(event);
}
void SettingSelectDlg::mousePressEvent(QMouseEvent *event)
{
	if (this->isVisible())	//20240731 huangliang ��ӱ༭�ٴε��ʱ���Ա༭
	{
		emit sig_Cannel(false);
		this->hide();
		return;
	}

	emit sig_Cannel(true);
	this->hide();
}

//20240820 huangliang ת�Ƶ�CSttGlobalModel��
////20240806 huangliang ������ֵ����·��,�������ʽ����
//bool SettingSelectDlg::AnalysisPath(const QString &strSrcPath, QString *strName, QString *strValue)
//{
//	if (strSrcPath == "")
//		return false;
//
//	if (IsStringNumber(strSrcPath.toLocal8Bit()))
//	{
//		return false;
//	}
//
//	if (g_pDvmDevice_AttachSetting == NULL)
//	{
//		return FALSE;
//	}
//
//	//20240813 huangliang IDȫ·������ʼIDΪ�ļ�·������ʱ�滻
//	QString sRepaceHead = "HLHeadRepaceHeadPath";
//	QString sHeadPath = g_pDvmDevice_AttachSetting->m_strID;
//	QString strNewSrcPath = strSrcPath;
//	strNewSrcPath.replace(sHeadPath, sRepaceHead);
//
//	CEpExpression oEpExp;
//	if (oEpExp.ChangeEpExpression(strNewSrcPath) == -1)
//	{
//		return false;
//	}
//
//	bool bCheckOk = false;
//	QString sName = strNewSrcPath;
//	QString sValue = strNewSrcPath;
//	POS pos = oEpExp.GetHeadPosition();
//	CEpExpVariable *pExpVar = NULL;	
//	while (pos != NULL)
//	{
//		pExpVar = oEpExp.GetNext(pos);
//
//		QString sTempName, sTempValue, sTempID;
//		sTempID = pExpVar->m_strVarID;
//		sTempID.replace(sRepaceHead, sHeadPath);	//20240813 huangliang ����ǰ�滻��ȫ·��ID
//		bCheckOk |= FindNameFromDeviceModel(sTempID, &sTempName, &sTempValue);	//��һ���ҵ�����ɹ�
//
//		//�滻���ʽ�е�·��
//		sName = sName.replace(pExpVar->m_strVarID, sTempName);
//		sValue = sValue.replace(pExpVar->m_strVarID, sTempValue);
//
//		pExpVar->m_dValue = CString_To_double(sTempValue);
//	}
//
//	double dValue = 1;
//	oEpExp.Value(dValue);
//	sValue += "=";
//	sValue += QString::number(dValue);
//
//	*strName = sName;
//	*strValue = QString::number(dValue); //sValue;ֻ��ʾ������ֵ
//	return bCheckOk;
//}
//
//BOOL SettingSelectDlg::FindNameFromDeviceModel(const CString &strPath, QString *strName, QString *strValue)
//{
//	*strName = "δ�ҵ�";
//	*strValue = "0";
//
//	if (strPath.GetLength() == 0)
//	{
//		return FALSE;
//	}
//
//	if (g_pDvmDevice_AttachSetting == NULL)
//	{
//		return FALSE;
//	}
//
//	CExBaseObject *pHeadChild = NULL;
//	if (strPath.GetAt(0) == '$')
//	{
//		pHeadChild = g_pDvmDevice_AttachSetting->FindByID(strPath.Mid(1));
//	}
//	else
//	{
//		pHeadChild = g_pDvmDevice_AttachSetting;
//		long nPos = MatchID(pHeadChild, strPath);
//		if (nPos > 0)
//		{
//			pHeadChild = FindRptDataByPath((CExBaseList *)pHeadChild, strPath.Mid(nPos));
//		}
//		else
//		{
//			pHeadChild = FindRptDataByPath((CExBaseList *)pHeadChild, strPath);
//		}
//	}
//
//	if (pHeadChild == NULL)
//		return FALSE;
//
//	*strName = pHeadChild->m_strName;
//
//	//����ֵ
//	if (pHeadChild->GetClassID() == DVMCLASSID_CDVMDATA)
//		*strValue = ((CDvmData*)pHeadChild)->m_strValue;
//	else if (pHeadChild->GetClassID() == DVMCLASSID_CDVMVALUE)
//		*strValue = ((CDvmValue*)pHeadChild)->m_strValue;
//	return TRUE;
//}
//long SettingSelectDlg::MatchID(CExBaseObject *pCurrItem, const CString &strPath)
//{
//	CString strID = pCurrItem->m_strID;
//	strID += _T("$");
//
//	if (strPath.GetLength() < strID.GetLength())
//	{
//		return -1;
//	}
//
//	if (strID == strPath.Left(strID.GetLength()))
//	{
//		return strID.GetLength();
//	}
//	else
//	{
//		return -1;
//	}
//}
//
//CExBaseObject* SettingSelectDlg::FindRptDataByPath(CExBaseList *pCurrItem, const CString &strPath)
//{
//	POS pos = pCurrItem->GetHeadPosition();
//	CExBaseObject *p = NULL;
//	CString strID;
//	long nPos = 0;
//	CExBaseObject *pFind = NULL;
//	CString strPath2;
//	long nSubItemCount = 0;
//
//	while (pos != NULL)
//	{
//		p = pCurrItem->GetNext(pos);
//		if (p == NULL)
//			return NULL;
//
//		nSubItemCount++;
//		nPos = MatchID(p, strPath);
//
//		if (nPos < 0)
//		{
//			continue;
//		}
//
//		strPath2 = strPath.Mid(nPos);
//		pFind = FindRptDataByPath((CExBaseList *)p, strPath2);
//
//		if (pFind == NULL)
//		{//û���ҵ���������Ŀp�в��ұ�������
//			return ((CExBaseList *)p)->FindByID(strPath2);
//		}
//		else
//		{
//			return pFind;
//		}
//	}
//
//	if (nSubItemCount == 0)
//	{//û������Ŀ�����ʾ�����Ǹ��ڵ㣬���ұ�������
//		return pCurrItem->FindByID(strPath);
//	}
//	else
//	{
//		return NULL;
//	}
//}