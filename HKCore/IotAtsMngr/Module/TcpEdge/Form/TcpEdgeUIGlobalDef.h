#ifndef _TCPEDGEUIGLOBALDEF_H_
#define _TCPEDGEUIGLOBALDEF_H_

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QGroupBox>
#include <QCheckBox>
#include "../../../../Module/DataMngr/DvmDatasetGroup.h"
#include "../../../../Module/API/GlobalConfigApi.h"

Q_DECLARE_METATYPE(CExBaseObject*)
Q_DECLARE_METATYPE(CBaseObject*)
Q_DECLARE_METATYPE(CDvmDataset*)
Q_DECLARE_METATYPE(QTableWidgetItem*)

inline void UIAutoConnect(QWidget* pUIWidget, QWidget* pChildUIWidget = NULL)
{
	QObjectList list = pChildUIWidget ? pChildUIWidget->children() : pUIWidget->children();
	for (int i = 0; i < list.count(); i++)
	{
		QObject* pObj = list[i];
		QString strClassName = pObj->metaObject()->className();
		if(pObj->objectName().indexOf("__") != -1)
		{
			QObject::connect(pObj, SIGNAL(stateChanged(int)), pUIWidget, SLOT(slot_autoConnected(int)));
		}
		else if (strClassName == "QGroupBox")
		{
			UIAutoConnect(pUIWidget, (QGroupBox*)pObj);
		}
	}
}

inline void UIAutoInitValue(QWidget* pUIWidget)
{
	CString strConfigFile = _P_GetConfigPath();
	strConfigFile += "TcpEdgeServerCfg.uixml";
	CDvmDatasetGroup cfg;
	++CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	cfg.OpenXmlFile(strConfigFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	--CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;

	POS pos = cfg.GetHeadPosition();
	while(pos)
	{
		CDvmData* pData = (CDvmData*)cfg.GetNext(pos);
		QString strObjName = pData->m_strID;
		QString strObjClassName = pData->m_strName;
		if(strObjClassName == "QComboBox")
		{
			QComboBox* pObj = pUIWidget->findChild<QComboBox*>(strObjName);
			if(!pObj)
			{
				continue;	
			}

			POS pos = pData->GetHeadPosition();
			while (pos)
			{
				CDvmValue* pValue = (CDvmValue*)pData->GetNext(pos);
				QString strText = pValue->m_strID + " (" + pValue->m_strName + ")";
				pObj->addItem(strText, QVariant::fromValue<QString>(pValue->m_strID));
			}
		}
	}
}

inline void UIAutoFillValue(QWidget* pUIWidget, const QString& strID, CDvmData* pData)
{
	//初始化不包括QTableWidget中的数据
	QObjectList list = pUIWidget->children();
	QObject* pObj = pUIWidget->findChild<QObject*>(strID);
	if(pObj)
	{
		QString strObjClassName = pObj->metaObject()->className();
		if(strObjClassName == "QComboBox")
		{
			QComboBox* pWidget = (QComboBox*)pObj;
			long nIndex = pWidget->findData(QVariant::fromValue<QString>(pData->m_strValue));
			pWidget->setCurrentIndex(nIndex);
		}
		else if(strObjClassName == "QLineEdit")
		{
			QLineEdit* pWidget = (QLineEdit*)pObj;
			pWidget->setText(pData->m_strValue);
		}
		else if (strObjClassName == "QDateTimeEdit")
		{
			QDateTimeEdit* pWidget = (QDateTimeEdit*)pObj;
			QDateTime date = QDateTime::fromString(pData->m_strValue, "yyyy-M-d H:m:s.z");
			pWidget->setDateTime(date);
		}

		((QWidget*)pObj)->setEnabled(pData->m_dwItemData);
		QString strCbID = "_" + strID + "_";
		QCheckBox* pCb = pUIWidget->findChild<QCheckBox*>(strCbID);
		pCb->setChecked(pData->m_dwItemData);

		return;
	}
}

inline void UISetDataset(QWidget* pUIWidget, CDvmDataset* pDataset)
{
	POS pos = pDataset->GetHeadPosition();
	while(pos)
	{
		CDvmData* pData = (CDvmData*)pDataset->GetNext(pos);
		QString strTempID = "_" + pData->m_strID + "_";
		if(pData->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			UIAutoFillValue(pUIWidget, strTempID, pData);
		}
	}
}

inline void UIGetDataset(QWidget* pUIWidget, CDvmDataset* pDataset)
{
	//更新不包括QTableWidget中的数据
	if(!pDataset)
	{
		return;
	}

	QObjectList list = pUIWidget->children();
	for (int i = 0; i < list.count(); i++)
	{
		QObject* pObj = list[i];
		QString strObjName = pObj->objectName();
		if (strObjName.indexOf("_") != -1)
		{
			strObjName = strObjName.mid(strObjName.indexOf("_") + 1);
		}
		if(strObjName.lastIndexOf("_") != -1)
		{
			strObjName = strObjName.left(strObjName.lastIndexOf("_"));
		}
		CDvmData* pData = (CDvmData*)pDataset->FindByID(strObjName);
		if(pData)
		{
			QString strObjClassName = pObj->metaObject()->className();
			if(strObjClassName == "QComboBox")
			{
				long nIndex = ((QComboBox*)pObj)->currentText().indexOf(" (");
				pData->m_strValue = ((QComboBox*)pObj)->currentText().left(nIndex);
			}
			else if(strObjClassName == "QLineEdit")
			{
				pData->m_strValue = ((QLineEdit*)pObj)->text();
				//lmy,20230908添加,对参数、定值分析的默认值进行分析赋值
				if(pData->m_strValue == "参数(parameter)")
				{
					pData->m_strValue = "parameter";
				}
			}
			else if(strObjClassName == "QDateTimeEdit")
			{
				if(((QDateTimeEdit*)pObj)->isEnabled())
				{
					QDateTime date = ((QDateTimeEdit*)pObj)->dateTime();
					pData->m_strValue = date.toString("yyyy-MM-dd hh:mm:ss.z");
				}
				else
				{
					QDateTime date = QDateTime::currentDateTime();
					pData->m_strValue = date.toString("yyyy-MM-dd hh:mm:ss.z");
				}	
			}
			else if(strObjClassName == "QGroupBox")
			{
				CDvmDataset* pChildDataset = (CDvmDataset*)pDataset->FindByID(strObjName);
				UIGetDataset((QGroupBox*)pObj, pChildDataset);
			}
		}
	}
}

#endif