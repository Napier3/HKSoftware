//#include "global.h"
#include "QSclFileRead.h"
#include <QProgressDialog>
#include "../../Module/API/StringConvert/String_Utf8_To_Gbk.h"

// CXML::CXML(QWidget *parent) :
//     QWidget(parent)
// {
// }


#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtGui/QtGui>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QToolBar>
#include <QList>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidgetItem>
#include <QtWidgets/QTreeWidget>
#include <QString>
#include <QStringList>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QScrollArea>
#else
#include <QScrollArea>
#include <QtGui/QApplication>
#include <QtGui>
#include <QMainWindow>
#include <QToolBar>
#include <QList>
#include <QToolButton>
#include <QTreeWidgetItem>
#include <QString>
#include <QTreeWidget>
#include <QStringList>
#include <QTextCodec>
#include <QDialog>
#include <QDesktopWidget>
#include <QTreeView>
#include <QComboBox>
#include <QLineEdit>
#endif
#include <QScrollBar>
#include <QPushButton>
#include <QBoxLayout>
#include <QObject>
#include <QMessageBox>
#include <QProgressDialog>
#include <QHBoxLayout>
#include <QDir>
#include <QList>
#include <QFileDialog>
#include <QSettings>
#include "../../Module/OSInterface/QT/XMessageBox.h"


#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif


QSclFileRead::QSclFileRead() 
{
	m_pSclStation = NULL;
	m_pProgressInterface = NULL;
	m_bIsInReadState = FALSE;
	m_pReadThread = NULL;
}

QSclFileRead::~QSclFileRead()
{
	FreeReadThread();
	FreeAllList();
}

void QSclFileRead::FreeThreadAndDatas()
{
	FreeReadThread();
	FreeAllList();
}

void QSclFileRead::FreeAllList()
{
	for (int iIED = 0; iIED < m_oSclIedList.size(); iIED++)
	{
		SCL_IED_INFO_QT *ied = m_oSclIedList[iIED];
		//GSE
		for (int iGSE = 0; iGSE < ied->GSEList.size(); iGSE++)
		{
			SCL_GSE_INFO_QT &gse = ied->GSEList[iGSE];
			for (int iPub = 0; iPub < gse.pubList.size(); iPub++)
			{
				SCL_PUB_REC_INFO_QT &pubRec = gse.pubList[iPub];
				pubRec.recPubList.clear();
			}
			gse.pubList.clear();
		}
		ied->GSEList.clear();
		//SMV
		for (int iSMV = 0; iSMV < ied->SMVList.size(); iSMV++)
		{
			SCL_SMV_INFO_QT &smv = ied->SMVList[iSMV];
			for (int iPub = 0; iPub < smv.pubList.size(); iPub++)
			{
				SCL_PUB_REC_INFO_QT &pubRec = smv.pubList[iPub];
				pubRec.recPubList.clear();
			}
			smv.pubList.clear();
		}
		ied->SMVList.clear();
		//sub
		ied->GOSubList.clear();
		ied->SVSubList.clear();
		delete ied;
	}

	m_oSclIedList.clear();
	m_oLNodeType_Hash.clear();
	m_oDOType_Hash.clear();
	m_oDAType_Hash.clear();
	m_oIedNameHash.clear();
}

void QSclFileRead::FreeReadThread()
{
	if (m_pReadThread != NULL)
	{
		m_pReadThread->PostThreadMessage(WM_QUIT, 0, 0);
		m_pReadThread->wait();
		m_pReadThread = NULL;
	}
}

BOOL QSclFileRead::IsTscdSclFile(const CString &strSclFilePath)
{   
	CString strPostfix;
	long nPos = strSclFilePath.ReverseFind('.');

	strPostfix = strSclFilePath.Mid(nPos+1);
	strPostfix.MakeLower();

	if (strPostfix == _T("tscd"))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

SCL_IED_INFO_QT* QSclFileRead::GetSclIedInforQT(const QString &strIedName)
{
	if (strIedName.isEmpty())
	{
		return NULL;
	}

	if (m_oSclIedList.size()<=0)
	{
		return NULL;
	}

	long nListIndex = m_oIedNameHash.value(strIedName);

	if (nListIndex<0)
	{
		return NULL;
	}
	else if (nListIndex == 0)
	{
		SCL_IED_INFO_QT *iedInfo = m_oSclIedList[nListIndex];

		if (iedInfo->name == strIedName)
		{
			return iedInfo;
		}

		return NULL;
	}
	else if (nListIndex >= m_oSclIedList.size())
	{
		return NULL;
	}

	return m_oSclIedList[nListIndex];
}

#ifdef SCL_FILE_PARSE_USE_XPUGI

BOOL QSclFileRead::ParseSCL(const CString &strSclFilePath)
{
// 	QTime oTime;//���ڼ�������ʱ
// 	oTime.start();// zhouhj 2024.5.6 delete

	if (m_pProgressInterface != NULL)
	{
// 		m_pProgressInterface->SetTitle("ParseSCL");
// 		m_pProgressInterface->ShowMsg("Loading...");
		m_pProgressInterface->InitThreadProgress(100,1);
		m_pProgressInterface->StepIt();
	}

	FreeAllList();//zhouhj 2023.12.24  ��Ϊͳһ��������
	m_nSclAnalyzeErrorNum=0;

	//װ��SCD�ļ�
	xpugi::xml_document oPugiDoc;
#ifdef _PSX_QT_LINUX_
	QTextCodec *pOldTextCodec = NULL;
	InitLocalCodec_BeforeReadWrite(strSclFilePath,&pOldTextCodec);
#endif
	CString strTmpText;
	QString strTmpPath = strSclFilePath;
	const QByteArray baTmp = strTmpPath.toLocal8Bit();
	const char *pzfFilePath = baTmp.data();

	if (!oPugiDoc.load_file(pzfFilePath,xpugi::parse_default,xpugi::encoding_utf8))
	{
#ifdef _PSX_QT_LINUX_
		ResetLocalCodec(pOldTextCodec);
#endif
		m_nSclAnalyzeErrorNum++;
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("open SCL file(%s)failed."),strSclFilePath.GetString());
		return FALSE;
	}

	if (m_pProgressInterface != NULL)
	{
		m_pProgressInterface->StepIt();
		m_pProgressInterface->ShowMsg("Parsing...");
	}

	//��������ģ���ϣ��
	xpugi::xml_node oRootNodePugi = oPugiDoc.root();
	CreateDataTypeTemplatesHash(oRootNodePugi);

	SetLocalCodec("utf-8");

	//���ý�����

	//��ȡIED�б�
	xpugi::xpath_node_set IED_list=oPugiDoc.select_nodes("/SCL/IED");
	int index=0;

	for(xpugi::xpath_node_set::const_iterator IED_it=IED_list.begin();IED_it!=IED_list.end();IED_it++)
	{
		xpugi::xpath_node IED_xpath=*IED_it;
		SCL_IED_INFO_QT *iedInfo = new SCL_IED_INFO_QT;
		iedInfo->name = QString(IED_xpath.node().attribute("name").value());
		iedInfo->type= QString(IED_xpath.node().attribute("type").value());
		iedInfo->manufacturer= QString(IED_xpath.node().attribute("manufacturer").value());
		iedInfo->configVersion= QString(IED_xpath.node().attribute("configVersion").value());
		iedInfo->desc= QString(IED_xpath.node().attribute("desc").value());

		m_oSclIedList.append(iedInfo);

		//����IED���ƺ�IEDList�Ĺ�ϣ��
		m_oIedNameHash.insert(iedInfo->name,index);
		index++;
	}

	if (m_pProgressInterface != NULL)
	{
		m_pProgressInterface->StepIt();
	}


	//��ȡGSE��SMV
	int progress_counter=1;
	xpugi::xpath_node_set ConnectedAP_list=oPugiDoc.select_nodes("/SCL/Communication/SubNetwork/ConnectedAP");

	if (m_pProgressInterface != NULL)
	{
		//2024.4.22 Xuzt 修改进度条总长�
		m_pProgressInterface->InitThreadProgress((ConnectedAP_list.size()+3*m_oSclIedList.size())*10,10);
	}

	for(xpugi::xpath_node_set::const_iterator ConnectedAP_it=ConnectedAP_list.begin();
		ConnectedAP_it!=ConnectedAP_list.end();ConnectedAP_it++)
	{
		xpugi::xml_node ConnectedAP_node=ConnectedAP_it->node();
		QString iedName=QString(ConnectedAP_node.attribute("iedName").value());

		//�����ӽڵ�
		for(xpugi::xml_node child_node=ConnectedAP_node.first_child();child_node;
			child_node=child_node.next_sibling())
		{
			QString node_name=QString(child_node.name());
			//��ȡGSE����Ϣ
			if(node_name=="GSE")
			{
				SCL_IED_INFO_QT *iedInfo=GetSclIedInforQT(iedName);
				SCL_GSE_INFO_QT gseInfo;

				gseInfo.apName = QString(ConnectedAP_node.attribute("apName").value());
				gseInfo.cbName = QString(child_node.attribute("cbName").value());
				gseInfo.ldInst = QString(child_node.attribute("ldInst").value());

				//Address
				xpugi::xpath_node_set Address_list=child_node.select_nodes("./Address/P");
				for(xpugi::xpath_node_set::const_iterator Address_it=Address_list.begin();
					Address_it!=Address_list.end();Address_it++)
				{
					xpugi::xpath_node Address_node=*Address_it;
					QString Addressstr = QString(Address_node.node().attribute("type").value());
					if(Addressstr=="MAC-Address")
					{
						gseInfo.MAC_Adress = QString(Address_node.node().text().as_string());
					}
					else if(Addressstr=="VLAN-ID")
					{
						gseInfo.VLAN_ID = QString(Address_node.node().text().as_string());
					}
					else if(Addressstr=="APPID")
					{
						gseInfo.APPID = QString(Address_node.node().text().as_string());
					}
					else if(Addressstr=="VLAN-PRIORITY")
					{
						gseInfo.VLAN_PRIORITY = QString(Address_node.node().text().as_string());
					}
				}
				xpugi::xpath_node MinTime_node=child_node.select_node("./MinTime");
				gseInfo.MinTime=MinTime_node.node().text().as_int();

				xpugi::xpath_node MaxTime_node=child_node.select_node("./MaxTime");
				gseInfo.MaxTime=MaxTime_node.node().text().as_int();

				//��ֹ���ƿ��ظ�
				bool flag=true;

				if (iedInfo != NULL)
				{
					foreach(SCL_GSE_INFO_QT it,iedInfo->GSEList)
					{
						if(it.apName==gseInfo.apName
							&&it.cbName==gseInfo.cbName
							&&it.ldInst==gseInfo.ldInst
							&&it.MAC_Adress==gseInfo.MAC_Adress
							&&it.VLAN_ID==gseInfo.VLAN_ID
							&&it.APPID==gseInfo.APPID
							&&it.VLAN_PRIORITY==gseInfo.VLAN_PRIORITY)
						{
							flag=false;
							break;
						}
					}
					if(flag)    iedInfo->GSEList.append(gseInfo);
				}
			}
			//��ȡSMV����Ϣ
			if(node_name=="SMV")
			{
				SCL_IED_INFO_QT *iedInfo= GetSclIedInforQT(iedName);

				SCL_SMV_INFO_QT smvInfo;
				smvInfo.apName = QString(ConnectedAP_node.attribute("apName").value());
				smvInfo.cbName = QString(child_node.attribute("cbName").value());
				smvInfo.ldInst = QString(child_node.attribute("ldInst").value());

				//Address
				xpugi::xpath_node_set Address_list=child_node.select_nodes("./Address/P");
				for(xpugi::xpath_node_set::const_iterator Address_it=Address_list.begin();
					Address_it!=Address_list.end();Address_it++)
				{
					xpugi::xpath_node Address_node=*Address_it;
					QString Addressstr = QString(Address_node.node().attribute("type").value());
					if(Addressstr=="MAC-Address")
					{
						smvInfo.MAC_Adress = QString(Address_node.node().text().as_string());
					}
					else if(Addressstr=="VLAN-ID")
					{
						smvInfo.VLAN_ID = QString(Address_node.node().text().as_string());
					}
					else if(Addressstr=="APPID")
					{
						smvInfo.APPID = QString(Address_node.node().text().as_string());
					}
					else if(Addressstr=="VLAN-PRIORITY")
					{
						smvInfo.VLAN_PRIORITY = QString(Address_node.node().text().as_string());
					}
				}

				if (iedInfo != NULL)
				{
					//��ֹ���ƿ��ظ�
					bool flag=true;
					foreach(SCL_SMV_INFO_QT it,iedInfo->SMVList)
					{
						if(it.apName==smvInfo.apName
							&&it.cbName==smvInfo.cbName
							&&it.ldInst==smvInfo.ldInst
							&&it.MAC_Adress==smvInfo.MAC_Adress
							&&it.VLAN_ID==smvInfo.VLAN_ID
							&&it.APPID==smvInfo.APPID
							&&it.VLAN_PRIORITY==smvInfo.VLAN_PRIORITY)
						{
							flag=false;
							break;
						}
					}
					if(flag)    iedInfo->SMVList.append(smvInfo);
				}
			}
		}

		if (m_pProgressInterface != NULL)
		{
			m_pProgressInterface->StepIt();
		}

		progress_counter++;
	}

	//����IED
	for(int index_IED=0;index_IED<m_oSclIedList.size();index_IED++)
	{
		SCL_IED_INFO_QT *iedInfo = m_oSclIedList[index_IED];

		//��ʱ��ŵ�ǰIED��GSE���Ƴ���һ���ҵ��ģ���������GSEList
		QList<SCL_GSE_INFO_QT> tempGSEList;
		QList<SCL_SMV_INFO_QT> tempSMVList;

		//����IED��LD�ڵ�
		strTmpText = "/SCL/IED[@name='"+iedInfo->name+"']/AccessPoint/Server/LDevice";
		xpugi::xpath_node_set LD_list=oPugiDoc.select_nodes(strTmpText.GetString());

 		for(xpugi::xpath_node_set::const_iterator LD_it=LD_list.begin();
 			LD_it!=LD_list.end();LD_it++)
		{
			xpugi::xml_node LD_node = LD_it->node();
			QString LD_inst = QString(LD_node.attribute("inst").value());
			QString apDesc = QString(LD_node.parent().parent().attribute("desc").value());
			QString apName = QString(LD_node.parent().parent().attribute("name").value());

			//������LD�ӽڵ��LNstr��ϣ���������������������
			DataTypeHash LN_hash;

			//����GSEControl
			for(xpugi::xml_node GSEControl_node=LD_node.child("LN0").child("GSEControl");
				GSEControl_node;GSEControl_node=GSEControl_node.next_sibling("GSEControl"))
			{
				//����һ��LN�ڵ��LN_str��hash
				if(LN_hash.size()==0)
					CreateLNHash(LD_node,&LN_hash);

				//��ȡ���GSEControl����Ϣ
				SCL_GSE_INFO_QT m_gseInfo;
				SCL_GSE_INFO_QT *gseInfo=&m_gseInfo;
				gseInfo->APPID="0000";
				gseInfo->MAC_Adress="01-0C-CD-01-00-00";
				gseInfo->VLAN_ID="1";
				gseInfo->VLAN_PRIORITY="4";
				gseInfo->apDesc=apDesc;
				gseInfo->apName=apName;
				gseInfo->cbName = QString(GSEControl_node.attribute("name").value());
				gseInfo->goID = QString(GSEControl_node.attribute("appID").value());
				gseInfo->datSet = QString(GSEControl_node.attribute("datSet").value());
				gseInfo->confRev = QString(GSEControl_node.attribute("confRev").value());

				//����DataSet�ڵ�
				strTmpText="./DataSet[@name='";
				strTmpText += QString(GSEControl_node.attribute("datSet").value());
				strTmpText+="']";

				xpugi::xpath_node DataSet_node = LD_node.child("LN0").select_node(strTmpText.GetString());
				gseInfo->DataSetDesc = QString(DataSet_node.node().attribute("desc").value());

				//����FCDA�ڵ�
				xpugi::xpath_node_set FCDA_list=DataSet_node.node().select_nodes("./FCDA");
				gseInfo->recNum=FCDA_list.size();

				for(xpugi::xpath_node_set::const_iterator FCDA_it=FCDA_list.begin();FCDA_it!=FCDA_list.end();FCDA_it++)
				{
					//�����������ݼ�
					xpugi::xml_node FCDA_node=FCDA_it->node();
					SCL_PUB_REC_INFO_QT pubRecInfo;

					if (strlen(FCDA_node.attribute("daName").value()) > 0)
					{
						pubRecInfo.ref=QString("%1/%2%3%4.%5.%6").arg(QString(FCDA_node.attribute("ldInst").value()),
							QString(FCDA_node.attribute("prefix").value()),
							QString(FCDA_node.attribute("lnClass").value()),
							QString(FCDA_node.attribute("lnInst").value()),
							QString(FCDA_node.attribute("doName").value()),
							QString(FCDA_node.attribute("daName").value())
							);
					} 
					else
					{
						pubRecInfo.ref=QString("%1/%2%3%4.%5").arg(QString(FCDA_node.attribute("ldInst").value()),
							QString(FCDA_node.attribute("prefix").value()),
							QString(FCDA_node.attribute("lnClass").value()),
							QString(FCDA_node.attribute("lnInst").value()),
							QString(FCDA_node.attribute("doName").value())
							);
					}

					//����ע��
					QString LNstr=QString("%1%2%3").arg(QString(FCDA_node.attribute("prefix").value()),
						QString(FCDA_node.attribute("lnClass").value()),
						QString(FCDA_node.attribute("lnInst").value())
						);
					xpugi::xml_node LN_find=LN_hash.value(LNstr);
					QString lnType = QString(LN_find.attribute("lnType").value());

					strTmpText = QString("./DOI[@name='%1']").arg(QString(FCDA_node.attribute("doName").value()));
					xpugi::xpath_node DOI_xml=LN_find.select_node(strTmpText.GetString());
					pubRecInfo.desc = QString(DOI_xml.node().attribute("desc").value());

					if(pubRecInfo.desc=="")
					{
						QString doName = QString(FCDA_node.attribute("doName").value());
						QStringList  doName_Split=doName.split('.');

						DataTypeHash DO_hash=m_oLNodeType_Hash.value(lnType);

						if (doName_Split.size()>0)
						{
							xpugi::xml_node DO_node=DO_hash.value(doName_Split[0]);
							pubRecInfo.desc = QString(DO_node.attribute("desc").value());
						}
					}
					if(pubRecInfo.desc=="")
						pubRecInfo.desc = QString(LN_find.attribute("desc").value());

					//������������
					QString daName = QString(FCDA_node.attribute("daName").value());
					QString fc = QString(FCDA_node.attribute("fc").value());
					QStringList daName_Split=daName.split('.');
					BOOL bHasFindType = FALSE;

					if (daName_Split.size()>0)
					{
						if(daName_Split[daName_Split.size()-1]=="t")
						{
							pubRecInfo.bType="Timestamp";
							bHasFindType = TRUE;
						}
						else if(daName_Split[daName_Split.size()-1]=="q")
						{
							pubRecInfo.bType="Quality";
							bHasFindType = TRUE;
						}
					}

					if (!bHasFindType)
					{
						//��ȡDOType������DO�ڵ���SDI�����
						QString doName = QString(FCDA_node.attribute("doName").value());
						QStringList  doName_Split=doName.split('.');
						QString DOTypeStr = "";

						if (doName_Split.size()>0)
						{
							DOTypeStr = GetDataFC(QSclFileRead::DOType,lnType,doName_Split[0],fc);
						}

						int doCounter = 1;
						while (doCounter < doName_Split.size())
						{
							DOTypeStr = GetDataFC(QSclFileRead::SDOType, DOTypeStr, doName_Split[doCounter],fc);
							doCounter++;
						}

						pubRecInfo.bType=GetDataFC(QSclFileRead::DAType,DOTypeStr,daName,fc);
					}

					gseInfo->pubList.append(pubRecInfo);
				}

				//���Ҹ�GSEControl��û�з���
				for(int index_GSE=0;index_GSE<iedInfo->GSEList.size();index_GSE++)
				{
					if(iedInfo->GSEList.at(index_GSE).cbName!=gseInfo->cbName
						||iedInfo->GSEList.at(index_GSE).ldInst!=LD_inst)
						continue;

					gseInfo->APPID=iedInfo->GSEList.at(index_GSE).APPID;
					gseInfo->ldInst=iedInfo->GSEList.at(index_GSE).ldInst;
					gseInfo->MAC_Adress=iedInfo->GSEList.at(index_GSE).MAC_Adress;
					gseInfo->VLAN_ID=iedInfo->GSEList.at(index_GSE).VLAN_ID;
					gseInfo->VLAN_PRIORITY=iedInfo->GSEList.at(index_GSE).VLAN_PRIORITY;
					gseInfo->MaxTime=iedInfo->GSEList.at(index_GSE).MaxTime;
					gseInfo->MinTime=iedInfo->GSEList.at(index_GSE).MinTime;

					tempGSEList.append(m_gseInfo);
				}
				if(gseInfo->APPID=="0000")
					tempGSEList.append(m_gseInfo);
			}

			//����SampledValueControl
			for(xpugi::xml_node SampledValueControl_node = LD_node.child("LN0").child("SampledValueControl");
				SampledValueControl_node;SampledValueControl_node = SampledValueControl_node.next_sibling("SampledValueControl"))
			{
				//����һ��LN�ڵ��LN_str��hash
				if(LN_hash.size()==0)
					CreateLNHash(LD_node,&LN_hash);

				SCL_SMV_INFO_QT m_smvInfo;
				SCL_SMV_INFO_QT *smvInfo=&m_smvInfo;

				smvInfo->APPID="0000";
				smvInfo->MAC_Adress="01-0C-CD-04-00-00";
				smvInfo->VLAN_ID="1";
				smvInfo->VLAN_PRIORITY="4";
				smvInfo->apDesc=apDesc;
				smvInfo->apName=apName;
				smvInfo->cbName = QString(SampledValueControl_node.attribute("name").value());
				smvInfo->SmvID =QString(SampledValueControl_node.attribute("smvID").value());
				smvInfo->datSet =QString(SampledValueControl_node.attribute("datSet").value());
				smvInfo->confRev = QString(SampledValueControl_node.attribute("confRev").value());
				smvInfo->nofASDU = SampledValueControl_node.attribute("nofASDU").as_int();
				smvInfo->smpRate = SampledValueControl_node.attribute("smpRate").as_int();

				//����ڵ�SmvOpts
				smvInfo->refreshTime=SampledValueControl_node.child("SmvOpts").attribute("refreshTime").as_bool();
				smvInfo->sampleSynchronized=SampledValueControl_node.child("SmvOpts").attribute("sampleSynchronized").as_bool();
				smvInfo->sampleRate=SampledValueControl_node.child("SmvOpts").attribute("sampleRate").as_bool();
				smvInfo->security=SampledValueControl_node.child("SmvOpts").attribute("security").as_bool();
				smvInfo->dataRef=SampledValueControl_node.child("SmvOpts").attribute("dataRef").as_bool();

				//����DataSet�ڵ�
				strTmpText = QString("./DataSet[@name='%1']").arg(QString(SampledValueControl_node.attribute("datSet").value()));
				xpugi::xpath_node DataSet_node=LD_node.child("LN0").select_node(strTmpText.GetString());
				smvInfo->DataSetDesc = QString(DataSet_node.node().attribute("desc").value());

				//����FCDA�ڵ�
				xpugi::xpath_node_set FCDA_list=DataSet_node.node().select_nodes("./FCDA");
				smvInfo->recNum=FCDA_list.size();

				for(xpugi::xpath_node_set::const_iterator FCDA_it=FCDA_list.begin();FCDA_it!=FCDA_list.end();FCDA_it++)
				{
					//�����������ݼ�
					xpugi::xml_node FCDA_node=FCDA_it->node();
					//ȥ��daNameΪq�ļ�¼
					if (strcmp(FCDA_node.attribute("daName").value() ,"q") == 0)
					{
						smvInfo->recNum--;
						continue;
					}
					SCL_PUB_REC_INFO_QT pubRecInfo;

					if (strlen(FCDA_node.attribute("daName").value()) > 0)
					{
						pubRecInfo.ref=QString("%1/%2%3%4.%5.%6").arg(QString(FCDA_node.attribute("ldInst").value()),
							QString(FCDA_node.attribute("prefix").value()),
							QString(FCDA_node.attribute("lnClass").value()),
							QString(FCDA_node.attribute("lnInst").value()),
							QString(FCDA_node.attribute("doName").value()),
							QString(FCDA_node.attribute("daName").value())
							);
					}
					else
					{
						pubRecInfo.ref=QString("%1/%2%3%4.%5").arg(QString(FCDA_node.attribute("ldInst").value()),
							QString(FCDA_node.attribute("prefix").value()),
							QString(FCDA_node.attribute("lnClass").value()),
							QString(FCDA_node.attribute("lnInst").value()),
							QString(FCDA_node.attribute("doName").value())
							);
					}

					//����ע��
					QString LNstr=QString("%1%2%3").arg(QString(FCDA_node.attribute("prefix").value()),
						QString(FCDA_node.attribute("lnClass").value()),
						QString(FCDA_node.attribute("lnInst").value())
						);
					xpugi::xml_node LN_find=LN_hash.value(LNstr);

					strTmpText = QString("./DOI[@name='%1']").arg(QString(FCDA_node.attribute("doName").value()));
					xpugi::xpath_node DOI_xml=LN_find.select_node(strTmpText.GetString());

					if(!pubRecInfo.ref.contains("DelayTRtg"))
					{
						pubRecInfo.desc = QString(LN_find.attribute("desc").value());
					}
					else
					{
						pubRecInfo.desc = QString(DOI_xml.node().attribute("desc").value());
					}

					pubRecInfo.desc = QString(DOI_xml.node().attribute("desc").value());
					if(pubRecInfo.desc=="")
					{
						//pubRecInfo.desc=DOI_xml.node().attribute("desc").value();
						pubRecInfo.desc = QString(LN_find.attribute("desc").value());
					}

					smvInfo->pubList.append(pubRecInfo);
				}

				//���Ҹ�GSEControl��û�з���
				for(int index_SMV=0;index_SMV<iedInfo->SMVList.size();index_SMV++)
				{
					if(iedInfo->SMVList.at(index_SMV).cbName!=smvInfo->cbName
						||iedInfo->SMVList.at(index_SMV).ldInst!=LD_inst)
						continue;

					smvInfo->APPID=iedInfo->SMVList.at(index_SMV).APPID;
					smvInfo->ldInst=iedInfo->SMVList.at(index_SMV).ldInst;
					smvInfo->MAC_Adress=iedInfo->SMVList.at(index_SMV).MAC_Adress;
					smvInfo->VLAN_ID=iedInfo->SMVList.at(index_SMV).VLAN_ID;
					smvInfo->VLAN_PRIORITY=iedInfo->SMVList.at(index_SMV).VLAN_PRIORITY;

					tempSMVList.append(m_smvInfo);
				}
				if(smvInfo->APPID=="0000")
					tempSMVList.append(m_smvInfo);
			}

			//����Inputs�ڵ㣬��ȡ������Ϣ
			xpugi::xml_node Inputs_node=LD_node.child("LN0").child("Inputs");
			for(xpugi::xml_node ExtRef_node=Inputs_node.child("ExtRef");ExtRef_node;
				ExtRef_node=ExtRef_node.next_sibling("ExtRef"))
			{
				//����һ��LN�ڵ��LN_str��hash
				if(LN_hash.size()==0)
					CreateLNHash(LD_node,&LN_hash);

				xpugi::xml_node AccessPoint_node=LD_node.parent().parent();
				QString AccessPoint_name = QString(AccessPoint_node.attribute("name").value());
				//��ȡGOOSE-Inputs
				if(AccessPoint_name.indexOf("M")!=-1)
				{
					SCL_SUB_REC_INFO_QT subRecInfo;
					subRecInfo.sub_IED_name = QString(ExtRef_node.attribute("iedName").value());

					if (strlen(ExtRef_node.attribute("daName").value()) > 0)
					{
						subRecInfo.sub_ref=QString("%1/%2%3%4.%5.%6").arg(QString(ExtRef_node.attribute("ldInst").value()),
							QString(ExtRef_node.attribute("prefix").value()),
							QString(ExtRef_node.attribute("lnClass").value()),
							QString(ExtRef_node.attribute("lnInst").value()),
							QString(ExtRef_node.attribute("doName").value()),
							QString(ExtRef_node.attribute("daName").value()));
					}
					else
					{
						subRecInfo.sub_ref=QString("%1/%2%3%4.%5").arg(QString(ExtRef_node.attribute("ldInst").value()),
							QString(ExtRef_node.attribute("prefix").value()),
							QString(ExtRef_node.attribute("lnClass").value()),
							QString(ExtRef_node.attribute("lnInst").value()),
							QString(ExtRef_node.attribute("doName").value()));
					}

					subRecInfo.sub_ldInst = QString(ExtRef_node.attribute("ldInst").value());
					subRecInfo.index_IED=-1;
					subRecInfo.index_GSE_SMV=-1;
					subRecInfo.index_Rec=-1;
					subRecInfo.ref = QString(ExtRef_node.attribute("intAddr").value());
					QStringList DO_name_Split=subRecInfo.ref.split('.');

					if(DO_name_Split.size()<2)
					{
						iedInfo->SVSubList.append(subRecInfo);
						continue;
					}

					QString DO_name=DO_name_Split[1];
					QString LNstr=DO_name_Split[0];
					DO_name_Split=LNstr.split('/');

					if (DO_name_Split.size()<=1)
					{
						iedInfo->SVSubList.append(subRecInfo);
						continue;
					}

					LNstr=DO_name_Split[1];

					xpugi::xml_node LN_find=LN_hash.value(LNstr);

					strTmpText = "./DOI[@name='"+DO_name+"']";
					xpugi::xpath_node DOI_xml=LN_find.select_node(strTmpText.GetString());
					subRecInfo.desc = QString(DOI_xml.node().attribute("desc").value());
					if(subRecInfo.desc=="")
						subRecInfo.desc = QString(LN_find.attribute("desc").value());

					iedInfo->SVSubList.append(subRecInfo);
				}
				else
				{
					SCL_SUB_REC_INFO_QT subRecInfo;
					subRecInfo.sub_IED_name = QString(ExtRef_node.attribute("iedName").value());

					if (strlen(ExtRef_node.attribute("daName").value()) > 0)
					{
						subRecInfo.sub_ref=QString("%1/%2%3%4.%5.%6").arg(QString(ExtRef_node.attribute("ldInst").value()),
							QString(ExtRef_node.attribute("prefix").value()),
							QString(ExtRef_node.attribute("lnClass").value()),
							QString(ExtRef_node.attribute("lnInst").value()),
							QString(ExtRef_node.attribute("doName").value()),
							QString(ExtRef_node.attribute("daName").value()));
					}
					else
					{
						subRecInfo.sub_ref=QString("%1/%2%3%4.%5.%6").arg(QString(ExtRef_node.attribute("ldInst").value()),
							QString(ExtRef_node.attribute("prefix").value()),
							QString(ExtRef_node.attribute("lnClass").value()),
							QString(ExtRef_node.attribute("lnInst").value()),
							QString(ExtRef_node.attribute("doName").value()));
					}

					subRecInfo.sub_ldInst = QString(ExtRef_node.attribute("ldInst").value());
					subRecInfo.index_IED=-1;
					subRecInfo.index_GSE_SMV=-1;
					subRecInfo.index_Rec=-1;
					subRecInfo.ref = QString(ExtRef_node.attribute("intAddr").value());
					QStringList DO_name_Split=subRecInfo.ref.split('.');

					if(DO_name_Split.size()<2)
					{
						iedInfo->GOSubList.append(subRecInfo);
						continue;
					}
					QString DO_name=DO_name_Split[1];
					QString LNstr=DO_name_Split[0];
					DO_name_Split = LNstr.split('/');

					if (DO_name_Split.size()<2)
					{
						iedInfo->GOSubList.append(subRecInfo);
						continue;
					}

					LNstr=DO_name_Split[1];

					xpugi::xml_node LN_find=LN_hash.value(LNstr);

					strTmpText="./DOI[@name='"+DO_name+"']";
					xpugi::xpath_node DOI_xml=LN_find.select_node(strTmpText.GetString());
					subRecInfo.desc = QString(DOI_xml.node().attribute("desc").value());
					if(subRecInfo.desc=="")
						subRecInfo.desc = QString(LN_find.attribute("desc").value());

					iedInfo->GOSubList.append(subRecInfo);
				}
			}
		}

		//�����ǰ�ģ�����µ�
		iedInfo->GSEList.clear();
		iedInfo->GSEList.append(tempGSEList);

		iedInfo->SMVList.clear();
		iedInfo->SMVList.append(tempSMVList);

		if (m_pProgressInterface != NULL)
		{
			//2024.4.22 Xuzt 每循环一次刷一次进度条
			m_pProgressInterface->StepIt();
		}

	}

	//ƥ�䶩�Ķ���
	for(int index_IED=0;index_IED<m_oSclIedList.size();index_IED++)
	{
		//����ÿһ��IED�Ķ��������
		SCL_IED_INFO_QT *iedInfo = m_oSclIedList[index_IED];
		//ƥ��GOOSE���������
		for(int index_subRec=0;index_subRec<iedInfo->GOSubList.size();index_subRec++)
		{
			//ƥ����ɱ��
			bool flag=false;
			SCL_SUB_REC_INFO_QT *subRecInfo=&iedInfo->GOSubList[index_subRec];
			//�ҵ���������ӵ�IED
			int index_pubIED=m_oIedNameHash.value(subRecInfo->sub_IED_name);
			SCL_IED_INFO_QT *pubIedInfo = m_oSclIedList[index_pubIED];
			//�ҵ�GSE
			for(int index_GSE=0;index_GSE<pubIedInfo->GSEList.size();index_GSE++)
			{
				SCL_GSE_INFO_QT *gseInfo=&pubIedInfo->GSEList[index_GSE];
				//ƥ��GSE��ldInst
				if(subRecInfo->sub_ldInst==gseInfo->ldInst)
				{
					//ƥ�䷢��������붩�������
					for(int index_pubRec=0;index_pubRec<gseInfo->pubList.size();index_pubRec++)
					{
						SCL_PUB_REC_INFO_QT *pubRecInfo=&gseInfo->pubList[index_pubRec];
						if(subRecInfo->sub_ref==pubRecInfo->ref)
						{
							//������Ϣ
							subRecInfo->index_IED=index_pubIED;
							subRecInfo->index_GSE_SMV=index_GSE;
							subRecInfo->index_Rec=index_pubRec;

							SCL_CONNECT_PUB_INFO_QT connectPubInfo;
							connectPubInfo.index_IED=index_IED;
							connectPubInfo.index_Rec=index_subRec;

							pubRecInfo->recPubList.append(connectPubInfo);

							flag=true;

							break;
						}
					}
				}
				if(flag) break;
			}

			if(subRecInfo->index_IED==-1||subRecInfo->index_GSE_SMV==-1||subRecInfo->index_Rec==-1)
			{
				m_nSclAnalyzeErrorNum++;
			}
		}

		//ƥ��SMV���������
		for(int index_subRec=0;index_subRec<iedInfo->SVSubList.size();index_subRec++)
		{
			//ƥ����ɱ��
			bool flag=false;
			SCL_SUB_REC_INFO_QT *subRecInfo=&iedInfo->SVSubList[index_subRec];
			//�ҵ���������ӵ�IED
			int index_pubIED=m_oIedNameHash.value(subRecInfo->sub_IED_name);
			SCL_IED_INFO_QT *pubIedInfo = m_oSclIedList[index_pubIED];
			//��������IED��SMV���ҵ�ƥ���IED
			for(int index_SMV=0;index_SMV<pubIedInfo->SMVList.size();index_SMV++)
			{
				SCL_SMV_INFO_QT *smvInfo=&pubIedInfo->SMVList[index_SMV];
				//ƥ��GSE��ldInst
				if(subRecInfo->sub_ldInst==smvInfo->ldInst)
				{
					//����SMV�ķ������ݼ���ƥ�䷢��������붩�������
					for(int index_pubRec=0;index_pubRec<smvInfo->pubList.size();index_pubRec++)
					{
						SCL_PUB_REC_INFO_QT *pubRecInfo=&smvInfo->pubList[index_pubRec];
						if(subRecInfo->sub_ref==pubRecInfo->ref)
						{
							//������Ϣ
							subRecInfo->index_IED=index_pubIED;
							subRecInfo->index_GSE_SMV=index_SMV;
							subRecInfo->index_Rec=index_pubRec;

							SCL_CONNECT_PUB_INFO_QT connectPubInfo;
							connectPubInfo.index_IED=index_IED;
							connectPubInfo.index_Rec=index_subRec;

							pubRecInfo->recPubList.append(connectPubInfo);

							flag=true;

							break;
						}
					}
				}
				if(flag) break;
			}

			if(subRecInfo->index_IED==-1||subRecInfo->index_GSE_SMV==-1||subRecInfo->index_Rec==-1)
			{
				m_nSclAnalyzeErrorNum++;
			}
		}

		if (m_pProgressInterface != NULL)
		{
			//2024.4.22 Xuzt 每循环一次刷一次进度条
			m_pProgressInterface->StepIt();
		}

	}

	//ƥ�������,��ֹG���ʵ㽨ģSMV���룬����M���ʵ㣬��ģGOOSE����
	for(int index_IED=0;index_IED<m_oSclIedList.size();index_IED++)
	{
		//��SMV���ҵ���goPub��¼
		QList<int> goSub_SMV_list;
		//����ÿһ��IED�Ķ��������
		SCL_IED_INFO_QT *iedInfo = m_oSclIedList[index_IED];
		//ƥ��GOOSE���������
		for(int index_subRec=0;index_subRec<iedInfo->GOSubList.size();index_subRec++)
		{
			//ƥ����ɱ��
			bool flag=false;
			SCL_SUB_REC_INFO_QT *subRecInfo=&iedInfo->GOSubList[index_subRec];
			//�����Ѿ��ҵ��ļ�¼
			if(subRecInfo->index_IED!=-1)   continue;
			//�ж��Ƿ���SMV������
			int index_pubIED=m_oIedNameHash.value(subRecInfo->sub_IED_name);
			SCL_IED_INFO_QT *pubIedInfo = m_oSclIedList[index_pubIED];
			//�ҵ�SMV
			for(int index_SMV=0;index_SMV<pubIedInfo->SMVList.size();index_SMV++)
			{
				SCL_SMV_INFO_QT *gseInfo=&pubIedInfo->SMVList[index_SMV];
				//ƥ��SMV��ldInst
				if(subRecInfo->sub_ldInst==gseInfo->ldInst)
				{
					//ƥ�䷢��������붩�������
					for(int index_pubRec=0;index_pubRec<gseInfo->pubList.size();index_pubRec++)
					{
						SCL_PUB_REC_INFO_QT *pubRecInfo=&gseInfo->pubList[index_pubRec];
						if(subRecInfo->sub_ref==pubRecInfo->ref)
						{
							//���¶���IED�ķ���IED����Ϣ
							subRecInfo->index_IED=index_pubIED;
							subRecInfo->index_GSE_SMV=index_SMV;
							subRecInfo->index_Rec=index_pubRec;

							//���·����ķ�IED����Ϣ
							SCL_CONNECT_PUB_INFO_QT connectPubInfo;
							connectPubInfo.index_IED=index_IED;
							connectPubInfo.index_Rec=index_subRec;
							pubRecInfo->recPubList.append(connectPubInfo);

							//���
							goSub_SMV_list.append(index_subRec);

							flag=true;

							break;
						}
					}
				}
				if(flag) break;
			}
		}

		//����Щ��¼��ӵ�SMVSub��
		for(int index=0;index<goSub_SMV_list.size();index++)
		{
			iedInfo->SVSubList.append(iedInfo->GOSubList.at(goSub_SMV_list.at(index)));
		}

		//����Щ��¼�Ƴ�GSESub��
		for(int index=0;index<goSub_SMV_list.size();index++)
		{
			iedInfo->GOSubList.removeAt(goSub_SMV_list.at(index)-index);
		}

		//��GSV���ҵ���smvPub��¼
		QList<int> smvSub_GSE_list;
		//ƥ��GOOSE���������
		for(int index_subRec=0;index_subRec<iedInfo->SVSubList.size();index_subRec++)
		{
			//ƥ����ɱ��
			bool flag=false;
			SCL_SUB_REC_INFO_QT *subRecInfo=&iedInfo->SVSubList[index_subRec];
			//�����Ѿ��ҵ��ļ�¼
			if(subRecInfo->index_IED!=-1)   continue;
			//�ж��Ƿ���SMV������
			int index_pubIED=m_oIedNameHash.value(subRecInfo->sub_IED_name);
			SCL_IED_INFO_QT *pubIedInfo = m_oSclIedList[index_pubIED];
			//�ҵ�SMV
			for(int index_GSE=0;index_GSE<pubIedInfo->GSEList.size();index_GSE++)
			{
				SCL_GSE_INFO_QT *gseInfo=&pubIedInfo->GSEList[index_GSE];
				//ƥ��GSE��ldInst
				if(subRecInfo->sub_ldInst==gseInfo->ldInst)
				{
					//ƥ�䷢��������붩�������
					for(int index_pubRec=0;index_pubRec<gseInfo->pubList.size();index_pubRec++)
					{
						SCL_PUB_REC_INFO_QT *pubRecInfo=&gseInfo->pubList[index_pubRec];
						if(subRecInfo->sub_ref==pubRecInfo->ref)
						{
							//���¶���IED�ķ���IED����Ϣ
							subRecInfo->index_IED=index_pubIED;
							subRecInfo->index_GSE_SMV=index_GSE;
							subRecInfo->index_Rec=index_pubRec;

							//���·����ķ�IED����Ϣ
							SCL_CONNECT_PUB_INFO_QT connectPubInfo;
							connectPubInfo.index_IED=index_IED;
							connectPubInfo.index_Rec=index_subRec;
							pubRecInfo->recPubList.append(connectPubInfo);

							//���
							smvSub_GSE_list.append(index_subRec);

							flag=true;

							break;
						}
					}
				}
				if(flag) break;
			}
		}

		//����Щ��¼��ӵ�GSESub��
		for(int index=0;index<smvSub_GSE_list.size();index++)
		{
			iedInfo->GOSubList.append(iedInfo->SVSubList.at(smvSub_GSE_list.at(index)));
		}

		//����Щ��¼�Ƴ�SMVSub��
		for(int index=0;index<smvSub_GSE_list.size();index++)
		{
			iedInfo->SVSubList.removeAt(smvSub_GSE_list.at(index)-index);
		}

		if (m_pProgressInterface != NULL)
		{
			//2024.4.22 Xuzt ÿѭ��һ��ˢһ�ν�����
			m_pProgressInterface->StepIt();
		}

	}

#ifndef USE_IN_Astra_LINUX//zhouhj 2024.4.27 �ǹ��ʲ������Բ��ô˷�ʽ
	SetLocalCodec("GBK");
#endif
	oPugiDoc.reset();

	return TRUE;
}


QString QSclFileRead::GetDataFC(const DataFC dataFC, const QString id, const QString name, const QString fc)
{
	QString strFC="";
	switch(dataFC)
	{
	case DOType:
		{
			DataTypeHash DO_hash=m_oLNodeType_Hash.value(id);
			xpugi::xml_node DO_node=DO_hash.value(name);
			strFC = QString(DO_node.attribute("type").value());
			break;
		}
	case SDOType:
		{
			xpugi::xml_node DOType_xml=m_oDOType_Hash.value(id);
			for(xpugi::xml_node SDO_xml=DOType_xml.child("SDO");SDO_xml;SDO_xml=SDO_xml.next_sibling("SDO"))
			{
				QString SDO_name = QString(SDO_xml.attribute("name").value());
				if(SDO_name==name)
				{
					strFC = QString(SDO_xml.attribute("type").value());
					break;
				}
			}

			break;
		}
		//���������������ҵ��������ͣ�ֱ�ӷ�����������
	case  DAType:
		{
			xpugi::xml_node DOType_node=m_oDOType_Hash.value(id);

			//FCDAû�ж���DA�����
			if(name=="")
			{
				for(xpugi::xml_node DA_node=DOType_node.child("DA");DA_node;DA_node=DA_node.next_sibling("DA"))
				{
					//��ȡFC��ͬ�Ľڵ�
					if(QString("%1").arg(QString(DA_node.attribute("fc").value()))==fc)
					{
						//���DA�ڵ㻹��SDI�ڵ�
						if(QString("%1").arg(QString(DA_node.attribute("bType").value()))=="Struct")
						{
							xpugi::xml_node DAType_node=this->m_oDAType_Hash.value(QString("%1").arg(QString(DA_node.attribute("type").value())));
							//��ȡBDA�ڵ����Ϣ
							for(xpugi::xml_node BDA_node=DAType_node.child("BDA");BDA_node;BDA_node=BDA_node.next_sibling("BDA"))
							{
								//���BDA�ڵ㻹��SDI�ڵ�
								if(QString("%1").arg(QString(BDA_node.attribute("bType").value()))=="Struct")
								{
									QString bType=GetDataFC(
										QSclFileRead::BDAType,
										QString("%1").arg(QString(BDA_node.attribute("type").value())),
										"",
										fc);

									if(strFC=="")
										strFC=bType;
									else
										strFC+=bType;
								}
								else
								{
									if(strFC=="")
										strFC=QString("%1").arg(QString(BDA_node.attribute("bType").value()));
									else
										strFC+=QString(",%1").arg(QString(BDA_node.attribute("bType").value()));
								}
							}
						}
						else
						{
							if(strFC=="")
								strFC=QString("%1").arg(QString(DA_node.attribute("bType").value()));
							else
								strFC+=QString(",%1").arg(QString(DA_node.attribute("bType").value()));
						}
					}
				}

			}
			else
			{
				QStringList strSplit=name.split('.');

				if (strSplit.size()>0)
				{
					xpugi::xml_node DA_xml;
					for(DA_xml=DOType_node.child("DA");DA_xml;DA_xml=DA_xml.next_sibling("DA"))
					{
						QString DA_name = QString(DA_xml.attribute("name").value());

						if(DA_name==strSplit[0])
						{
							break;
						}
					}

					if (DA_xml != NULL)
					{
						if(strSplit.size()>1)
						{
							QString DAType_id = QString(DA_xml.attribute("type").value());
							QString BDA_name=name.right(name.length()-strSplit[0].length()-1);
							strFC=GetDataFC(QSclFileRead::BDAType,DAType_id,BDA_name,fc);
						}
						else
						{
							strFC = QString(DA_xml.attribute("bType").value());
						}
					}
				}
			}

			break;
		}
	case BDAType:
		{
			//�����������nameΪ�գ���˵��ȫ����ȡ
			if(name=="")
			{
				xpugi::xml_node DAType_node=this->m_oDAType_Hash.value(id);
				//��ȡBDA�ڵ����Ϣ
				for(xpugi::xml_node BDA_node=DAType_node.child("BDA");BDA_node;BDA_node=BDA_node.next_sibling("BDA"))
				{
					//���BDA�ڵ㻹��SDI�ڵ�
					if(QString("%1").arg(QString(BDA_node.attribute("bType").value()))=="Struct")
					{
						QString bType=GetDataFC(
							QSclFileRead::BDAType,
							QString("%1").arg(QString(BDA_node.attribute("type").value())),
							"",
							fc);

						if(strFC=="")
							strFC=bType;
						else
							strFC+=bType;
					}
					else
					{
						if(strFC=="")
							strFC=QString("%1").arg(QString(BDA_node.attribute("bType").value()));
						else
							strFC+=QString(",%1").arg(QString(BDA_node.attribute("bType").value()));
					}
				}
			}
			else
			{
				QStringList strSplit=name.split('.');

				if (strSplit.size()>0)
				{
					xpugi::xml_node DAType_xml=m_oDAType_Hash.value(id);
					for(xpugi::xml_node BDA_xml=DAType_xml.child("BDA");BDA_xml;BDA_xml=BDA_xml.next_sibling("BDA"))
					{
						QString BDA_name = QString(BDA_xml.attribute("name").value());
						if(BDA_name==strSplit[0])
						{
							if(strSplit.size()>1)
							{
								QString DAType_id = QString(BDA_xml.attribute("type").value());
								QString BDA_name=name.right(name.length()-strSplit[0].length()-1);
								strFC=GetDataFC(QSclFileRead::BDAType,DAType_id,BDA_name,fc);
							}
							else
							{
								strFC = QString(BDA_xml.attribute("bType").value());
							}
							break;
						}
					}
				}
			}

			break;
		}
	default:
		break;
	}

	return strFC;
}

void QSclFileRead::CreateLNHash(const xpugi::xml_node LD_node, DataTypeHash *pLN_hash)
{
	for(xpugi::xml_node LN_node=LD_node.first_child();LN_node;LN_node=LN_node.next_sibling())
	{
		QString LNstr=QString("%1%2%3").arg(QString(LN_node.attribute("prefix").value()),
			QString(LN_node.attribute("lnClass").value()),QString(LN_node.attribute("inst").value()));
		if(!pLN_hash->contains(LNstr))
		{
			pLN_hash->insert(LNstr,LN_node);
		}
		else
		{
			//            Log4Qt::Logger *log = Log4Qt::Logger::logger("CMXL");
			//            QString Msg=QString("SCL-IED-AccessPoint-Server-LD-LN error:node Repeated!LN is:%1").
			//                    arg(LNstr);
			//            log->error(Msg);
			m_nSclAnalyzeErrorNum++;
		}
	}
}

//��������ģ���ϣ�����ڲ�����������
void QSclFileRead::CreateDataTypeTemplatesHash(xpugi::xml_node oRootNodePugi)
{
	xpugi::xml_node tools=oRootNodePugi.child("SCL").child("DataTypeTemplates");

	for(xpugi::xml_node tool=tools.first_child();tool;tool=tool.next_sibling())
	{
		QString node_name = QString(tool.name());
		if(node_name=="LNodeType")
		{
			QString id = QString(tool.attribute("id").value());

			//��DO�ڵ㽨����ϣ��
			DataTypeHash DO_Hash;
			for(xpugi::xml_node DO_xml=tool.first_child();DO_xml;DO_xml=DO_xml.next_sibling())
			{
				QString DO_name = QString(DO_xml.attribute("name").value());
				//QString DO_type=DO_xml.attribute("type").value();
				if(!DO_Hash.contains(DO_name))
				{
					//DO_Hash.insert(DO_name,DO_type);
					DO_Hash.insert(DO_name,DO_xml);
				}
				else
				{
					//                    Log4Qt::Logger *log = Log4Qt::Logger::logger("CMXL");
					//                    QString Msg=QString("SCL-DataTypeTemplates-LNodeType-DO error:node Repeated!LNOdeType id is:%1.DO name is:%2").
					//                            arg(id).arg(DO_name);
					//                    log->error(Msg);
					m_nSclAnalyzeErrorNum++;
				}
			}
			if(!m_oLNodeType_Hash.contains(id))
			{
				m_oLNodeType_Hash.insert(id,DO_Hash);
			}
			else
			{
				//                Log4Qt::Logger *log = Log4Qt::Logger::logger("CMXL");
				//                QString Msg=QString("SCL-DataTypeTemplates-LNodeType error:node Repeated!LNOdeType id is:%1").
				//                        arg(id);
				//                log->error(Msg);
				m_nSclAnalyzeErrorNum++;
			}
		}
		else if(node_name=="DOType")
		{
			QString id = QString(tool.attribute("id").value());
			if(!m_oDOType_Hash.contains(id))
			{
				m_oDOType_Hash.insert(id,tool);
			}
			else
			{
				//                Log4Qt::Logger *log = Log4Qt::Logger::logger("CMXL");
				//                QString Msg=QString("SCL-DataTypeTemplates-DOType error:node Repeated!DOType id is:%1.").
				//                        arg(id);
				//                log->error(Msg);
				m_nSclAnalyzeErrorNum++;
			}
		}
		else if(node_name=="DAType")
		{
			QString id = QString(tool.attribute("id").value());
			if(!m_oDAType_Hash.contains(id))
			{
				m_oDAType_Hash.insert(id,tool);
			}
			else
			{
				//                Log4Qt::Logger *log = Log4Qt::Logger::logger("CMXL");
				//                QString Msg=QString("SCL-DataTypeTemplates-DAType error:node Repeated!DAType id is:%1").
				//                        arg(id);
				//                log->error(Msg);
				m_nSclAnalyzeErrorNum++;
			}
		}
	}
}


BOOL QSclFileRead::SavePscdFile(const CString &strPscdFilePath)
{
	xpugi::xml_document doc;
	//add declaration
	xpugi::xml_node decl=doc.prepend_child(xpugi::node_declaration);
	decl.append_attribute("version") = "1.0";
	decl.append_attribute("encoding") = "UTF-8";

	// add root
	xpugi::xml_node root = doc.append_child("PSCD");

	//add child node--goose pub
	foreach(SCL_IED_INFO_QT *iedInfo,m_oSclIedList)
	{
		std::string str;
		xpugi::xml_node IED_node = root.append_child("IED");
#ifdef _USE_IN_IED_QT5
		std::wstring wstrTmp =  iedInfo->name.toStdWString();
#else
		QStdWString wstrTmp =  iedInfo->name.toStdWString();
#endif
		const wchar_t *ch1 = wstrTmp.c_str();
		xpugi::xml_attribute oXMlAttr =  IED_node.append_attribute("name");
		oXMlAttr.set_value(ch1);
		wstrTmp = iedInfo->type.toStdWString();
		const wchar_t *ch2 = wstrTmp.c_str(); 

		//        const char *ch2=str.c_str();
		IED_node.append_attribute("type")=ch2;

		//        str=iedInfo->desc.toStdString();
		wstrTmp = iedInfo->desc.toStdWString();
		const wchar_t *ch3=wstrTmp.c_str(); 
		IED_node.append_attribute("desc")=ch3;

		//        str=iedInfo->manufacturer.toStdString();
		wstrTmp = iedInfo->manufacturer.toStdWString();
		const wchar_t *ch4=wstrTmp.c_str(); 
		IED_node.append_attribute("manufacturer")=ch4;

		//        str=iedInfo.configVersion.toStdString();
		wstrTmp = iedInfo->configVersion.toStdWString();
		const wchar_t *ch5=wstrTmp.c_str(); 
		IED_node.append_attribute("configVersion")=ch5;

		//GOOSE pub
		foreach(SCL_GSE_INFO_QT gseInfo,iedInfo->GSEList)
		{
			xpugi::xml_node GSE_node=IED_node.append_child("GSE");

			//            str=gseInfo.apName.toStdString();
			wstrTmp = gseInfo.apName.toStdWString();
			const wchar_t *gse_ch1=wstrTmp.c_str(); 
			GSE_node.append_attribute("apName")=gse_ch1;

			//            str=gseInfo.cbName.toStdString();
			wstrTmp = gseInfo.cbName.toStdWString();
			const wchar_t *gse_ch2=wstrTmp.c_str(); 
			GSE_node.append_attribute("cbName")=gse_ch2;

			//            str=gseInfo.ldInst.toStdString();
			wstrTmp = gseInfo.ldInst.toStdWString();
			const wchar_t *gse_ch3=wstrTmp.c_str(); 
			GSE_node.append_attribute("ldInst")=gse_ch3;

			//            str=gseInfo.desc.toStdString();
			wstrTmp = gseInfo.desc.toStdWString();
			const wchar_t *gse_ch15=wstrTmp.c_str(); 
			GSE_node.append_attribute("desc")=gse_ch15;

			//            str=gseInfo.MAC_Adress.toStdString();
			wstrTmp = gseInfo.MAC_Adress.toStdWString();
			const wchar_t *gse_ch4=wstrTmp.c_str(); 
			GSE_node.append_attribute("MAC_Address")=gse_ch4;

			//            str=gseInfo.VLAN_ID.toStdString();
			wstrTmp = gseInfo.VLAN_ID.toStdWString();
			const wchar_t *gse_ch5=wstrTmp.c_str(); 
			GSE_node.append_attribute("VLAN_ID")=gse_ch5;

			//            str=gseInfo.APPID.toStdString();
			wstrTmp = gseInfo.APPID.toStdWString();
			const wchar_t *gse_ch6=wstrTmp.c_str(); 
			GSE_node.append_attribute("APPID")=gse_ch6;

			//           str=gseInfo.VLAN_PRIORITY.toStdString();
			wstrTmp = gseInfo.VLAN_PRIORITY.toStdWString();
			const wchar_t *gse_ch7=wstrTmp.c_str(); 
			GSE_node.append_attribute("VLAN_PRIORITY")=gse_ch7;

			GSE_node.append_attribute("MinTime")=gseInfo.MinTime;
			GSE_node.append_attribute("MaxTime")=gseInfo.MaxTime;

			//            str=gseInfo.datSet.toStdString();
			wstrTmp = gseInfo.datSet.toStdWString();
			const wchar_t *gse_ch10=wstrTmp.c_str(); 
			GSE_node.append_attribute("DataSet")=gse_ch10;

			//            str=gseInfo.DataSetDesc.toStdString();
			wstrTmp = gseInfo.DataSetDesc.toStdWString();
			const wchar_t *gse_ch13=wstrTmp.c_str(); 
			GSE_node.append_attribute("DataSetDesc")=gse_ch13;

			//            str=gseInfo.goID.toStdString();
			wstrTmp = gseInfo.goID.toStdWString();
			const wchar_t *gse_ch11=wstrTmp.c_str(); 
			GSE_node.append_attribute("goID")=gse_ch11;

			//            str=gseInfo.confRev.toStdString();
			wstrTmp = gseInfo.confRev.toStdWString();
			const wchar_t *gse_ch14=wstrTmp.c_str(); 
			GSE_node.append_attribute("confRev")=gse_ch14;


			foreach(SCL_PUB_REC_INFO_QT pubInfo,gseInfo.pubList)
			{
				xpugi::xml_node PUB_node=GSE_node.append_child("GOPUB");

				//                str=pubInfo.ref.toStdString();
				wstrTmp = pubInfo.ref.toStdWString();
				const wchar_t *pub_ch1=wstrTmp.c_str(); 
				PUB_node.append_attribute("reference")=pub_ch1;

				//                str=pubInfo.desc.toStdString();
				wstrTmp = pubInfo.desc.toStdWString();
				const wchar_t *pub_ch2=wstrTmp.c_str();
				PUB_node.append_attribute("desc")=pub_ch2;

				//                str=pubInfo.bType.toStdString();
				wstrTmp = pubInfo.bType.toStdWString();
				const wchar_t *pub_ch3=wstrTmp.c_str();
				PUB_node.append_attribute("bType")=pub_ch3;

				foreach(SCL_CONNECT_PUB_INFO_QT conInfo,pubInfo.recPubList)
				{
					xpugi::xml_node CON_node=PUB_node.append_child("Outputs");

					CON_node.append_attribute("index_IED")=conInfo.index_IED;
					CON_node.append_attribute("index_Rec")=conInfo.index_Rec;
				}
			}
		}

		//SMV pub
		foreach(SCL_SMV_INFO_QT gseInfo,iedInfo->SMVList)
		{
			xpugi::xml_node GSE_node=IED_node.append_child("SMV");

			//            str=gseInfo.apName.toStdString();
			wstrTmp = gseInfo.apName.toStdWString();
			const wchar_t *gse_ch1=wstrTmp.c_str();
			GSE_node.append_attribute("apName")=gse_ch1;

			//            str=gseInfo.cbName.toStdString();
			wstrTmp = gseInfo.cbName.toStdWString();
			const wchar_t *gse_ch2=wstrTmp.c_str();
			GSE_node.append_attribute("cbName")=gse_ch2;

			//            str=gseInfo.ldInst.toStdString();
			wstrTmp = gseInfo.ldInst.toStdWString();
			const wchar_t *gse_ch3=wstrTmp.c_str();
			GSE_node.append_attribute("ldInst")=gse_ch3;

			//            str=gseInfo.MAC_Adress.toStdString();
			wstrTmp = gseInfo.MAC_Adress.toStdWString();
			const wchar_t *gse_ch4=wstrTmp.c_str();
			GSE_node.append_attribute("MAC_Address")=gse_ch4;

			//            str=gseInfo.VLAN_ID.toStdString();
			wstrTmp = gseInfo.VLAN_ID.toStdWString();
			const wchar_t *gse_ch5=wstrTmp.c_str();
			GSE_node.append_attribute("VLAN_ID")=gse_ch5;

			//            str=gseInfo.APPID.toStdString();
			wstrTmp = gseInfo.APPID.toStdWString();
			const wchar_t *gse_ch6=wstrTmp.c_str();
			GSE_node.append_attribute("APPID")=gse_ch6;

			//            str=gseInfo.VLAN_PRIORITY.toStdString();
			wstrTmp = gseInfo.VLAN_PRIORITY.toStdWString();
			const wchar_t *gse_ch7=wstrTmp.c_str();
			GSE_node.append_attribute("VLAN_PRIORITY")=gse_ch7;

			//            str=gseInfo.datSet.toStdString();
			wstrTmp = gseInfo.datSet.toStdWString();
			const wchar_t *gse_ch10=wstrTmp.c_str();
			GSE_node.append_attribute("datSet")=gse_ch10;

			//            str=gseInfo.SmvID.toStdString();
			wstrTmp = gseInfo.SmvID.toStdWString();
			const wchar_t *gse_ch11=wstrTmp.c_str();
			GSE_node.append_attribute("SmvID")=gse_ch11;

			//            str=gseInfo.DataSetDesc.toStdString();
			wstrTmp = gseInfo.DataSetDesc.toStdWString();
			const wchar_t *gse_ch13=wstrTmp.c_str();
			GSE_node.append_attribute("DataSetDesc")=gse_ch13;

			//           str=gseInfo.confRev.toStdString();
			wstrTmp = gseInfo.confRev.toStdWString();
			const wchar_t *gse_ch14=wstrTmp.c_str();
			GSE_node.append_attribute("confRev")=gse_ch14;

			GSE_node.append_attribute("smpRate")=gseInfo.smpRate;
			GSE_node.append_attribute("nofASDU")=gseInfo.nofASDU;
			GSE_node.append_attribute("refreshTime")=gseInfo.refreshTime;
			GSE_node.append_attribute("sampleSynchronized")=gseInfo.sampleSynchronized;
			GSE_node.append_attribute("sampleRate")=gseInfo.sampleRate;
			GSE_node.append_attribute("security")=gseInfo.security;
			GSE_node.append_attribute("dataRef")=gseInfo.dataRef;

			foreach(SCL_PUB_REC_INFO_QT pubInfo,gseInfo.pubList)
			{
				xpugi::xml_node PUB_node=GSE_node.append_child("GOPUB");

				//                str=pubInfo.ref.toStdString();
				wstrTmp = pubInfo.ref.toStdWString();
				const wchar_t *pub_ch1=wstrTmp.c_str();
				PUB_node.append_attribute("reference")=pub_ch1;

				//                str=pubInfo.desc.toStdString();
				wstrTmp = pubInfo.desc.toStdWString();
				const wchar_t *pub_ch2=wstrTmp.c_str();
				PUB_node.append_attribute("desc")=pub_ch2;

				foreach(SCL_CONNECT_PUB_INFO_QT conInfo,pubInfo.recPubList)
				{
					xpugi::xml_node CON_node=PUB_node.append_child("Outputs");

					CON_node.append_attribute("index_IED")=conInfo.index_IED;
					CON_node.append_attribute("index_Rec")=conInfo.index_Rec;
				}
			}
		}

		//goose sub
		foreach(SCL_SUB_REC_INFO_QT subInfo,iedInfo->GOSubList)
		{
			xpugi::xml_node SUB_node=IED_node.append_child("GOSUB");

			//            str=subInfo.ref.toStdString();
			wstrTmp = subInfo.ref.toStdWString();
			const wchar_t *sub_ch1=wstrTmp.c_str();
			SUB_node.append_attribute("ref")=sub_ch1;

			//            str=subInfo.desc.toStdString();
			wstrTmp = subInfo.desc.toStdWString();
			const wchar_t *sub_ch2=wstrTmp.c_str();
			SUB_node.append_attribute("desc")=sub_ch2;

			//            str=subInfo.sub_IED_name.toStdString();
			wstrTmp = subInfo.sub_IED_name.toStdWString();
			const wchar_t *sub_ch3=wstrTmp.c_str();
			SUB_node.append_attribute("sub_IED_name")=sub_ch3;

			//            str=subInfo.sub_ldInst.toStdString();
			wstrTmp = subInfo.sub_ldInst.toStdWString();
			const wchar_t *sub_ch4=wstrTmp.c_str();
			SUB_node.append_attribute("sub_ldInst")=sub_ch4;

			//            str=subInfo.sub_ref.toStdString();
			wstrTmp = subInfo.sub_ref.toStdWString();
			const wchar_t *sub_ch5=wstrTmp.c_str();
			SUB_node.append_attribute("sub_ref")=sub_ch5;

			SUB_node.append_attribute("index_IED")=subInfo.index_IED;
			SUB_node.append_attribute("index_GSE")=subInfo.index_GSE_SMV;
			SUB_node.append_attribute("index_Rec")=subInfo.index_Rec;
		}

		//sv sub
		foreach(SCL_SUB_REC_INFO_QT subInfo,iedInfo->SVSubList)
		{
			xpugi::xml_node SUB_node=IED_node.append_child("SMVSUB");

			//            str=subInfo.ref.toStdString();
			wstrTmp = subInfo.ref.toStdWString();
			const wchar_t *sub_ch1=wstrTmp.c_str();
			SUB_node.append_attribute("ref")=sub_ch1;

			//            str=subInfo.desc.toStdString();
			wstrTmp = subInfo.desc.toStdWString();
			const wchar_t *sub_ch2=wstrTmp.c_str();
			SUB_node.append_attribute("desc")=sub_ch2;

			//            str=subInfo.sub_IED_name.toStdString();
			wstrTmp = subInfo.sub_IED_name.toStdWString();
			const wchar_t *sub_ch3=wstrTmp.c_str();
			SUB_node.append_attribute("sub_IED_name")=sub_ch3;

			//            str=subInfo.sub_ldInst.toStdString();
			wstrTmp = subInfo.sub_ldInst.toStdWString();
			const wchar_t *sub_ch4=wstrTmp.c_str();
			SUB_node.append_attribute("sub_ldInst")=sub_ch4;

			//            str=subInfo.sub_ref.toStdString();
			wstrTmp = subInfo.sub_ref.toStdWString();
			const wchar_t *sub_ch5=wstrTmp.c_str();
			SUB_node.append_attribute("sub_ref")=sub_ch5;

			SUB_node.append_attribute("index_IED")=subInfo.index_IED;
			SUB_node.append_attribute("index_SMV")=subInfo.index_GSE_SMV;
			SUB_node.append_attribute("index_Rec")=subInfo.index_Rec;
		}
	}

	const QByteArray baTmp=strPscdFilePath.toLocal8Bit();
	const char *chFilePath=baTmp.data();
	if(!doc.save_file(chFilePath,"\t",xpugi::format_no_escapes,xpugi::encoding_utf8))
	{
		CXMessageBox::information(NULL,QObject::tr("error"),QObject::tr("Output file failed !"));
		return FALSE;
	}
	else
	{
#ifdef _PSX_QT_LINUX_  //20220509 zhouhj  linux��д�ļ���,��Ҫ����ͬ������
		system("sync");
#endif
	}

	return TRUE;
}
#else

BOOL QSclFileRead::ParseSCL(const CString &strSclFilePath)
{
// 	QTime oTime;//用于计算总用�?
// 	oTime.start();// zhouhj 2024.5.6 delete

	if (m_pProgressInterface != NULL)
	{
// 		m_pProgressInterface->SetTitle("ParseSCL");
// 		m_pProgressInterface->ShowMsg("Loading...");
		m_pProgressInterface->InitThreadProgress(100,1);
		m_pProgressInterface->StepIt();
	}

	FreeAllList();//zhouhj 2023.12.24 ��Ϊͳһ��������
	m_nSclAnalyzeErrorNum=0;

	//װ��SCD�ļ�
	pugi::xml_document oPugiDoc;
#ifdef _PSX_QT_LINUX_
	QTextCodec *pOldTextCodec = NULL;
	InitLocalCodec_BeforeReadWrite(strSclFilePath,&pOldTextCodec);
#endif
	QString strTmpPath = strSclFilePath;
	const QByteArray baTmp = strTmpPath.toLocal8Bit();
	const char *pzfFilePath = baTmp.data();

	if (!oPugiDoc.load_file(pzfFilePath,pugi::parse_default,pugi::encoding_utf8))
	{
#ifdef _PSX_QT_LINUX_
		ResetLocalCodec(pOldTextCodec);
#endif
		m_nSclAnalyzeErrorNum++;
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("open SCL file(%s)failed."),strSclFilePath.GetString());
		return FALSE;
	}

	if (m_pProgressInterface != NULL)
	{
		m_pProgressInterface->StepIt();
		m_pProgressInterface->ShowMsg("Parsing...");
	}

	//��������ģ���ϣ��
	pugi::xml_node oRootNodePugi = oPugiDoc.root();
	CreateDataTypeTemplatesHash(oRootNodePugi);

	SetLocalCodec("utf-8");

	//���ý�����

	//��ȡIED�б�
	pugi::xpath_node_set IED_list=oPugiDoc.select_nodes(L"/SCL/IED");
	int index=0;

	for(pugi::xpath_node_set::const_iterator IED_it=IED_list.begin();IED_it!=IED_list.end();IED_it++)
	{
		pugi::xpath_node IED_xpath=*IED_it;
		SCL_IED_INFO_QT *iedInfo = new SCL_IED_INFO_QT;
		iedInfo->name = QString::fromWCharArray(IED_xpath.node().attribute(L"name").value());
		iedInfo->type= QString::fromWCharArray(IED_xpath.node().attribute(L"type").value());
		iedInfo->manufacturer= QString::fromWCharArray(IED_xpath.node().attribute(L"manufacturer").value());
		iedInfo->configVersion= QString::fromWCharArray(IED_xpath.node().attribute(L"configVersion").value());
		iedInfo->desc= QString::fromWCharArray(IED_xpath.node().attribute(L"desc").value());

		m_oSclIedList.append(iedInfo);

		//����IED���ƺ�IEDList�Ĺ�ϣ��
		m_oIedNameHash.insert(iedInfo->name,index);
		index++;
	}

	if (m_pProgressInterface != NULL)
	{
		m_pProgressInterface->StepIt();
	}

	//��ȡGSE��SMV
	int progress_counter=1;
	pugi::xpath_node_set ConnectedAP_list=oPugiDoc.select_nodes(L"/SCL/Communication/SubNetwork/ConnectedAP");

	if (m_pProgressInterface != NULL)
	{
		m_pProgressInterface->InitThreadProgress(ConnectedAP_list.size()*10,10);
	}

	for(pugi::xpath_node_set::const_iterator ConnectedAP_it=ConnectedAP_list.begin();
		ConnectedAP_it!=ConnectedAP_list.end();ConnectedAP_it++)
	{
		pugi::xml_node ConnectedAP_node=ConnectedAP_it->node();
		QString iedName=QString::fromWCharArray(ConnectedAP_node.attribute(L"iedName").value());

		//�����ӽڵ�
		for(pugi::xml_node child_node=ConnectedAP_node.first_child();child_node;
			child_node=child_node.next_sibling())
		{
			QString node_name=QString::fromWCharArray(child_node.name());
			//��ȡMMS����Ϣ
			// 			if(node_name=="MMS")
			// 			{
			// 				SCL_IED_INFO_QT *iedInfo=&m_oSclIedList[m_oIedNameHash.value(iedName)];
			// 				SCL_GSE_INFO_QT gseInfo;
			// 
			// 				gseInfo.apName = QString::fromWCharArray(ConnectedAP_node.attribute(L"apName").value());
			// 				gseInfo.cbName = QString::fromWCharArray(child_node.attribute(L"cbName").value());
			// 				gseInfo.ldInst = QString::fromWCharArray(child_node.attribute(L"ldInst").value());
			// 
			// 				//Address
			// 				xpath_node_set Address_list=child_node.select_nodes(L"./Address/P");
			// 				for(xpath_node_set::const_iterator Address_it=Address_list.begin();
			// 					Address_it!=Address_list.end();Address_it++)
			// 				{
			// 					pugi::xpath_node Address_node=*Address_it;
			// 					QString Addressstr = QString::fromWCharArray(Address_node.node().attribute(L"type").value());
			// 					if(Addressstr=="MAC-Address")
			// 					{
			// 						gseInfo.MAC_Adress = QString::fromWCharArray(Address_node.node().text().as_string());
			// 					}
			// 					else if(Addressstr=="VLAN-ID")
			// 					{
			// 						gseInfo.VLAN_ID = QString::fromWCharArray(Address_node.node().text().as_string());
			// 					}
			// 					else if(Addressstr=="APPID")
			// 					{
			// 						gseInfo.APPID = QString::fromWCharArray(Address_node.node().text().as_string());
			// 					}
			// 					else if(Addressstr=="VLAN-PRIORITY")
			// 					{
			// 						gseInfo.VLAN_PRIORITY = QString::fromWCharArray(Address_node.node().text().as_string());
			// 					}
			// 				}
			// 				xpath_node MinTime_node=child_node.select_node(L"./MinTime");
			// 				gseInfo.MinTime=MinTime_node.node().text().as_int();
			// 
			// 				xpath_node MaxTime_node=child_node.select_node(L"./MaxTime");
			// 				gseInfo.MaxTime=MaxTime_node.node().text().as_int();
			// 
			// 				//��ֹ���ƿ��ظ�
			// 				bool flag=true;
			// 				foreach(SCL_GSE_INFO_QT it,iedInfo->GSEList)
			// 				{
			// 					if(it.apName==gseInfo.apName
			// 						&&it.cbName==gseInfo.cbName
			// 						&&it.ldInst==gseInfo.ldInst
			// 						&&it.MAC_Adress==gseInfo.MAC_Adress
			// 						&&it.VLAN_ID==gseInfo.VLAN_ID
			// 						&&it.APPID==gseInfo.APPID
			// 						&&it.VLAN_PRIORITY==gseInfo.VLAN_PRIORITY)
			// 					{
			// 						flag=false;
			// 						break;
			// 					}
			// 				}
			// 				if(flag)    iedInfo->GSEList.append(gseInfo);
			// 			}
			//��ȡGSE����Ϣ
			if(node_name=="GSE")
			{
				SCL_IED_INFO_QT *iedInfo = GetSclIedInforQT(iedName);
				SCL_GSE_INFO_QT gseInfo;

				gseInfo.apName = QString::fromWCharArray(ConnectedAP_node.attribute(L"apName").value());
				gseInfo.cbName = QString::fromWCharArray(child_node.attribute(L"cbName").value());
				gseInfo.ldInst = QString::fromWCharArray(child_node.attribute(L"ldInst").value());

				//Address
				pugi::xpath_node_set Address_list=child_node.select_nodes(L"./Address/P");
				for(pugi::xpath_node_set::const_iterator Address_it=Address_list.begin();
					Address_it!=Address_list.end();Address_it++)
				{
					pugi::xpath_node Address_node=*Address_it;
					QString Addressstr = QString::fromWCharArray(Address_node.node().attribute(L"type").value());
					if(Addressstr=="MAC-Address")
					{
						gseInfo.MAC_Adress = QString::fromWCharArray(Address_node.node().text().as_string());
					}
					else if(Addressstr=="VLAN-ID")
					{
						gseInfo.VLAN_ID = QString::fromWCharArray(Address_node.node().text().as_string());
					}
					else if(Addressstr=="APPID")
					{
						gseInfo.APPID = QString::fromWCharArray(Address_node.node().text().as_string());
					}
					else if(Addressstr=="VLAN-PRIORITY")
					{
						gseInfo.VLAN_PRIORITY = QString::fromWCharArray(Address_node.node().text().as_string());
					}
				}
				pugi::xpath_node MinTime_node=child_node.select_node(L"./MinTime");
				gseInfo.MinTime=MinTime_node.node().text().as_int();

				pugi::xpath_node MaxTime_node=child_node.select_node(L"./MaxTime");
				gseInfo.MaxTime=MaxTime_node.node().text().as_int();

				if (iedInfo != NULL)
				{
					//��ֹ���ƿ��ظ�
					bool flag=true;
					foreach(SCL_GSE_INFO_QT it,iedInfo->GSEList)
					{
						if(it.apName==gseInfo.apName
							&&it.cbName==gseInfo.cbName
							&&it.ldInst==gseInfo.ldInst
							&&it.MAC_Adress==gseInfo.MAC_Adress
							&&it.VLAN_ID==gseInfo.VLAN_ID
							&&it.APPID==gseInfo.APPID
							&&it.VLAN_PRIORITY==gseInfo.VLAN_PRIORITY)
						{
							flag=false;
							break;
						}
					}
					if(flag)    iedInfo->GSEList.append(gseInfo);
				}
				
			}
			//��ȡSMV����Ϣ
			if(node_name=="SMV")
			{
				SCL_IED_INFO_QT *iedInfo = GetSclIedInforQT(iedName);

				SCL_SMV_INFO_QT smvInfo;
				smvInfo.apName = QString::fromWCharArray(ConnectedAP_node.attribute(L"apName").value());
				smvInfo.cbName = QString::fromWCharArray(child_node.attribute(L"cbName").value());
				smvInfo.ldInst = QString::fromWCharArray(child_node.attribute(L"ldInst").value());

				//Address
				pugi::xpath_node_set Address_list=child_node.select_nodes(L"./Address/P");
				for(pugi::xpath_node_set::const_iterator Address_it=Address_list.begin();
					Address_it!=Address_list.end();Address_it++)
				{
					pugi::xpath_node Address_node=*Address_it;
					QString Addressstr = QString::fromWCharArray(Address_node.node().attribute(L"type").value());
					if(Addressstr=="MAC-Address")
					{
						smvInfo.MAC_Adress = QString::fromWCharArray(Address_node.node().text().as_string());
					}
					else if(Addressstr=="VLAN-ID")
					{
						smvInfo.VLAN_ID = QString::fromWCharArray(Address_node.node().text().as_string());
					}
					else if(Addressstr=="APPID")
					{
						smvInfo.APPID = QString::fromWCharArray(Address_node.node().text().as_string());
					}
					else if(Addressstr=="VLAN-PRIORITY")
					{
						smvInfo.VLAN_PRIORITY = QString::fromWCharArray(Address_node.node().text().as_string());
					}
				}

				if (iedInfo != NULL)
				{
					//��ֹ���ƿ��ظ�
					bool flag=true;
					foreach(SCL_SMV_INFO_QT it,iedInfo->SMVList)
					{
						if(it.apName==smvInfo.apName
							&&it.cbName==smvInfo.cbName
							&&it.ldInst==smvInfo.ldInst
							&&it.MAC_Adress==smvInfo.MAC_Adress
							&&it.VLAN_ID==smvInfo.VLAN_ID
							&&it.APPID==smvInfo.APPID
							&&it.VLAN_PRIORITY==smvInfo.VLAN_PRIORITY)
						{
							flag=false;
							break;
						}
					}
					if(flag)    iedInfo->SMVList.append(smvInfo);
				}
			}
		}

		if (m_pProgressInterface != NULL)
		{
			m_pProgressInterface->StepIt();
		}

		progress_counter++;
	}

#ifdef _USE_IN_IED_QT5
	std::wstring wstrTmp;
#else
	QStdWString wstrTmp;
#endif

	//����IED
	for(int index_IED=0;index_IED<m_oSclIedList.size();index_IED++)
	{
		SCL_IED_INFO_QT *iedInfo = m_oSclIedList[index_IED];

		//��ʱ��ŵ�ǰIED��GSE���Ƴ���һ���ҵ��ģ���������GSEList
		QList<SCL_GSE_INFO_QT> tempGSEList;
		QList<SCL_SMV_INFO_QT> tempSMVList;

		//����IED��LD�ڵ�
		strTmpPath="/SCL/IED[@name='"+iedInfo->name+"']/AccessPoint/Server/LDevice";

#ifdef _MSC_VER
		wstrTmp =  std::wstring((const wchar_t *)strTmpPath.utf16());
#else
		wstrTmp = strTmpPath.toStdWString();
#endif

		const wchar_t * LDChar = wstrTmp.c_str();

		//         const QByteArray LDByte=strTmpPath.toLocal8Bit();
		//         const char *LDChar=LDByte.data();
		pugi::xpath_node_set LD_list=oPugiDoc.select_nodes(LDChar);
		for(pugi::xpath_node_set::const_iterator LD_it=LD_list.begin();
			LD_it!=LD_list.end();LD_it++)
		{
			pugi::xml_node LD_node = LD_it->node();
			QString LD_inst = QString::fromWCharArray(LD_node.attribute(L"inst").value());
			QString apDesc = QString::fromWCharArray(LD_node.parent().parent().attribute(L"desc").value());
			QString apName = QString::fromWCharArray(LD_node.parent().parent().attribute(L"name").value());

			//������LD�ӽڵ��LNstr��ϣ���������������������
			DataTypeHash LN_hash;

			//����GSEControl
			for(pugi::xml_node GSEControl_node=LD_node.child(L"LN0").child(L"GSEControl");
				GSEControl_node;GSEControl_node=GSEControl_node.next_sibling(L"GSEControl"))
			{
				//����һ��LN�ڵ��LN_str��hash
				if(LN_hash.size()==0)
					CreateLNHash(LD_node,&LN_hash);

				//��ȡ���GSEControl����Ϣ
				SCL_GSE_INFO_QT m_gseInfo;
				SCL_GSE_INFO_QT *gseInfo=&m_gseInfo;
				gseInfo->APPID="0000";
				gseInfo->MAC_Adress="01-0C-CD-01-00-00";
				gseInfo->VLAN_ID="1";
				gseInfo->VLAN_PRIORITY="4";
				gseInfo->apDesc=apDesc;
				gseInfo->apName=apName;
				gseInfo->cbName = QString::fromWCharArray(GSEControl_node.attribute(L"name").value());
				gseInfo->goID = QString::fromWCharArray(GSEControl_node.attribute(L"appID").value());
				gseInfo->datSet = QString::fromWCharArray(GSEControl_node.attribute(L"datSet").value());
				gseInfo->confRev = QString::fromWCharArray(GSEControl_node.attribute(L"confRev").value());

				//����DataSet�ڵ�
				strTmpPath="./DataSet[@name='";
				strTmpPath += QString::fromWCharArray(GSEControl_node.attribute(L"datSet").value());
				strTmpPath+="']";

#ifdef _MSC_VER
				wstrTmp =  std::wstring((const wchar_t *)strTmpPath.utf16());
#else
				wstrTmp = strTmpPath.toStdWString();
#endif
				const wchar_t * DataSetChar = wstrTmp.c_str();
				//                 const QByteArray DataSetText= strTmpPath.toLocal8Bit();
				//                 const char *DataSetChar = DataSetText.data();

				pugi::xpath_node DataSet_node = LD_node.child(L"LN0").select_node(DataSetChar);
				gseInfo->DataSetDesc = QString::fromWCharArray(DataSet_node.node().attribute(L"desc").value());

				//����FCDA�ڵ�
				pugi::xpath_node_set FCDA_list=DataSet_node.node().select_nodes(L"./FCDA");
				gseInfo->recNum=FCDA_list.size();

				for(pugi::xpath_node_set::const_iterator FCDA_it=FCDA_list.begin();FCDA_it!=FCDA_list.end();FCDA_it++)
				{
					//�����������ݼ�
					pugi::xml_node FCDA_node=FCDA_it->node();
					SCL_PUB_REC_INFO_QT pubRecInfo;

					if (wcslen(FCDA_node.attribute(L"daName").value()) > 0)
					{
						pubRecInfo.ref=QString("%1/%2%3%4.%5.%6").arg(QString::fromWCharArray(FCDA_node.attribute(L"ldInst").value()),
							QString::fromWCharArray(FCDA_node.attribute(L"prefix").value()),
							QString::fromWCharArray(FCDA_node.attribute(L"lnClass").value()),
							QString::fromWCharArray(FCDA_node.attribute(L"lnInst").value()),
							QString::fromWCharArray(FCDA_node.attribute(L"doName").value()),
							QString::fromWCharArray(FCDA_node.attribute(L"daName").value())
							);
					} 
					else
					{
						pubRecInfo.ref=QString("%1/%2%3%4.%5").arg(QString::fromWCharArray(FCDA_node.attribute(L"ldInst").value()),
							QString::fromWCharArray(FCDA_node.attribute(L"prefix").value()),
							QString::fromWCharArray(FCDA_node.attribute(L"lnClass").value()),
							QString::fromWCharArray(FCDA_node.attribute(L"lnInst").value()),
							QString::fromWCharArray(FCDA_node.attribute(L"doName").value())
							);
					}

					//����ע��
					QString LNstr=QString("%1%2%3").arg(QString::fromWCharArray(FCDA_node.attribute(L"prefix").value()),
						QString::fromWCharArray(FCDA_node.attribute(L"lnClass").value()),
						QString::fromWCharArray(FCDA_node.attribute(L"lnInst").value())
						);
					pugi::xml_node LN_find=LN_hash.value(LNstr);
					QString lnType = QString::fromWCharArray(LN_find.attribute(L"lnType").value());

					strTmpPath = QString("./DOI[@name='%1']").arg(QString::fromWCharArray(FCDA_node.attribute(L"doName").value()));

#ifdef _MSC_VER
					wstrTmp =  std::wstring((const wchar_t *)strTmpPath.utf16());
#else
					wstrTmp = strTmpPath.toStdWString();
#endif
					const wchar_t * DOIChar = wstrTmp.c_str();

					//                     const QByteArray DOIText= strTmpPath.toLocal8Bit();
					//                     const char *DOIChar = DOIText.data();

					pugi::xpath_node DOI_xml=LN_find.select_node(DOIChar);
					pubRecInfo.desc = QString::fromWCharArray(DOI_xml.node().attribute(L"desc").value());
					if(pubRecInfo.desc=="")
					{
						QString doName = QString::fromWCharArray(FCDA_node.attribute(L"doName").value());
						QStringList  doName_Split=doName.split('.');

						DataTypeHash DO_hash=m_oLNodeType_Hash.value(lnType);
						pugi::xml_node DO_node=DO_hash.value(doName_Split[0]);
						pubRecInfo.desc = QString::fromWCharArray(DO_node.attribute(L"desc").value());
					}
					if(pubRecInfo.desc=="")
						pubRecInfo.desc = QString::fromWCharArray(LN_find.attribute(L"desc").value());

					//������������
					QString daName = QString::fromWCharArray(FCDA_node.attribute(L"daName").value());
					QString fc = QString::fromWCharArray(FCDA_node.attribute(L"fc").value());
					QStringList daName_Split=daName.split('.');
					if(daName_Split[daName_Split.size()-1]=="t")
					{
						pubRecInfo.bType="Timestamp";
					}
					else if(daName_Split[daName_Split.size()-1]=="q")
					{
						pubRecInfo.bType="Quality";
					}
					else
					{
						//��ȡDOType������DO�ڵ���SDI�����
						QString doName = QString::fromWCharArray(FCDA_node.attribute(L"doName").value());
						QStringList  doName_Split=doName.split('.');
						QString DOTypeStr=GetDataFC(QSclFileRead::DOType,lnType,doName_Split[0],fc);
						int doCounter = 1;
						while (doCounter < doName_Split.size())
						{
							DOTypeStr = GetDataFC(QSclFileRead::SDOType, DOTypeStr, doName_Split[doCounter],fc);
							doCounter++;
						}

						pubRecInfo.bType=GetDataFC(QSclFileRead::DAType,DOTypeStr,daName,fc);
					}
					gseInfo->pubList.append(pubRecInfo);
				}

				//���Ҹ�GSEControl��û�з���
				for(int index_GSE=0;index_GSE<iedInfo->GSEList.size();index_GSE++)
				{
					if(iedInfo->GSEList.at(index_GSE).cbName!=gseInfo->cbName
						||iedInfo->GSEList.at(index_GSE).ldInst!=LD_inst)
						continue;

					gseInfo->APPID=iedInfo->GSEList.at(index_GSE).APPID;
					gseInfo->ldInst=iedInfo->GSEList.at(index_GSE).ldInst;
					gseInfo->MAC_Adress=iedInfo->GSEList.at(index_GSE).MAC_Adress;
					gseInfo->VLAN_ID=iedInfo->GSEList.at(index_GSE).VLAN_ID;
					gseInfo->VLAN_PRIORITY=iedInfo->GSEList.at(index_GSE).VLAN_PRIORITY;
					gseInfo->MaxTime=iedInfo->GSEList.at(index_GSE).MaxTime;
					gseInfo->MinTime=iedInfo->GSEList.at(index_GSE).MinTime;

					tempGSEList.append(m_gseInfo);
				}
				if(gseInfo->APPID=="0000")
					tempGSEList.append(m_gseInfo);
			}

			//����SampledValueControl
			for(pugi::xml_node SampledValueControl_node = LD_node.child(L"LN0").child(L"SampledValueControl");
				SampledValueControl_node;SampledValueControl_node = SampledValueControl_node.next_sibling(L"SampledValueControl"))
			{
				//����һ��LN�ڵ��LN_str��hash
				if(LN_hash.size()==0)
					CreateLNHash(LD_node,&LN_hash);

				SCL_SMV_INFO_QT m_smvInfo;
				SCL_SMV_INFO_QT *smvInfo=&m_smvInfo;

				smvInfo->APPID="0000";
				smvInfo->MAC_Adress="01-0C-CD-04-00-00";
				smvInfo->VLAN_ID="1";
				smvInfo->VLAN_PRIORITY="4";
				smvInfo->apDesc=apDesc;
				smvInfo->apName=apName;
				smvInfo->cbName = QString::fromWCharArray(SampledValueControl_node.attribute(L"name").value());
				smvInfo->SmvID =QString::fromWCharArray(SampledValueControl_node.attribute(L"smvID").value());
				smvInfo->datSet =QString::fromWCharArray(SampledValueControl_node.attribute(L"datSet").value());
				smvInfo->confRev = QString::fromWCharArray(SampledValueControl_node.attribute(L"confRev").value());
				smvInfo->nofASDU = SampledValueControl_node.attribute(L"nofASDU").as_int();
				smvInfo->smpRate = SampledValueControl_node.attribute(L"smpRate").as_int();

				//����ڵ�SmvOpts
				smvInfo->refreshTime=SampledValueControl_node.child(L"SmvOpts").attribute(L"refreshTime").as_bool();
				smvInfo->sampleSynchronized=SampledValueControl_node.child(L"SmvOpts").attribute(L"sampleSynchronized").as_bool();
				smvInfo->sampleRate=SampledValueControl_node.child(L"SmvOpts").attribute(L"sampleRate").as_bool();
				smvInfo->security=SampledValueControl_node.child(L"SmvOpts").attribute(L"security").as_bool();
				smvInfo->dataRef=SampledValueControl_node.child(L"SmvOpts").attribute(L"dataRef").as_bool();

				//����DataSet�ڵ�
				strTmpPath = QString("./DataSet[@name='%1']").arg(QString::fromWCharArray(SampledValueControl_node.attribute(L"datSet").value()));

#ifdef _MSC_VER
				wstrTmp =  std::wstring((const wchar_t *)strTmpPath.utf16());
#else
				wstrTmp = strTmpPath.toStdWString();
#endif
				const wchar_t * DataSetChar = wstrTmp.c_str();
				//                 const QByteArray DataSetText= strTmpPath.toLocal8Bit();
				//                 const char *DataSetChar = DataSetText.data();

				pugi::xpath_node DataSet_node=LD_node.child(L"LN0").select_node(DataSetChar);
				smvInfo->DataSetDesc = QString::fromWCharArray(DataSet_node.node().attribute(L"desc").value());

				//����FCDA�ڵ�
				pugi::xpath_node_set FCDA_list=DataSet_node.node().select_nodes(L"./FCDA");
				smvInfo->recNum=FCDA_list.size();

				for(pugi::xpath_node_set::const_iterator FCDA_it=FCDA_list.begin();FCDA_it!=FCDA_list.end();FCDA_it++)
				{
					//�����������ݼ�
					pugi::xml_node FCDA_node=FCDA_it->node();
					//ȥ��daNameΪq�ļ�¼
					if (wcscmp(FCDA_node.attribute(L"daName").value() ,L"q") == 0)
					{
						smvInfo->recNum--;
						continue;
					}
					SCL_PUB_REC_INFO_QT pubRecInfo;

					if (wcslen(FCDA_node.attribute(L"daName").value()) > 0)
					{
						pubRecInfo.ref=QString("%1/%2%3%4.%5.%6").arg(QString::fromWCharArray(FCDA_node.attribute(L"ldInst").value()),
							QString::fromWCharArray(FCDA_node.attribute(L"prefix").value()),
							QString::fromWCharArray(FCDA_node.attribute(L"lnClass").value()),
							QString::fromWCharArray(FCDA_node.attribute(L"lnInst").value()),
							QString::fromWCharArray(FCDA_node.attribute(L"doName").value()),
							QString::fromWCharArray(FCDA_node.attribute(L"daName").value())
							);
					}
					else
					{
						pubRecInfo.ref=QString("%1/%2%3%4.%5").arg(QString::fromWCharArray(FCDA_node.attribute(L"ldInst").value()),
							QString::fromWCharArray(FCDA_node.attribute(L"prefix").value()),
							QString::fromWCharArray(FCDA_node.attribute(L"lnClass").value()),
							QString::fromWCharArray(FCDA_node.attribute(L"lnInst").value()),
							QString::fromWCharArray(FCDA_node.attribute(L"doName").value())
							);
					}

					//����ע��
					QString LNstr=QString("%1%2%3").arg(QString::fromWCharArray(FCDA_node.attribute(L"prefix").value()),
						QString::fromWCharArray(FCDA_node.attribute(L"lnClass").value()),
						QString::fromWCharArray(FCDA_node.attribute(L"lnInst").value())
						);
					pugi::xml_node LN_find=LN_hash.value(LNstr);

					strTmpPath = QString("./DOI[@name='%1']").arg(QString::fromWCharArray(FCDA_node.attribute(L"doName").value()));

#ifdef _MSC_VER
					wstrTmp =  std::wstring((const wchar_t *)strTmpPath.utf16());
#else
					wstrTmp = strTmpPath.toStdWString();
#endif
					const wchar_t * DOIChar = wstrTmp.c_str();
					//                     const QByteArray DOIText= strTmpPath.toLocal8Bit();
					//                     const char *DOIChar = DOIText.data();

					pugi::xpath_node DOI_xml=LN_find.select_node(DOIChar);

					if(!pubRecInfo.ref.contains("DelayTRtg"))
					{
						pubRecInfo.desc = QString::fromWCharArray(LN_find.attribute(L"desc").value());
					}
					else
					{
						pubRecInfo.desc = QString::fromWCharArray(DOI_xml.node().attribute(L"desc").value());
					}

					pubRecInfo.desc = QString::fromWCharArray(DOI_xml.node().attribute(L"desc").value());
					if(pubRecInfo.desc=="")
					{
						//pubRecInfo.desc=DOI_xml.node().attribute("desc").value();
						pubRecInfo.desc = QString::fromWCharArray(LN_find.attribute(L"desc").value());
					}

					smvInfo->pubList.append(pubRecInfo);
				}

				//���Ҹ�GSEControl��û�з���
				for(int index_SMV=0;index_SMV<iedInfo->SMVList.size();index_SMV++)
				{
					if(iedInfo->SMVList.at(index_SMV).cbName!=smvInfo->cbName
						||iedInfo->SMVList.at(index_SMV).ldInst!=LD_inst)
						continue;

					smvInfo->APPID=iedInfo->SMVList.at(index_SMV).APPID;
					smvInfo->ldInst=iedInfo->SMVList.at(index_SMV).ldInst;
					smvInfo->MAC_Adress=iedInfo->SMVList.at(index_SMV).MAC_Adress;
					smvInfo->VLAN_ID=iedInfo->SMVList.at(index_SMV).VLAN_ID;
					smvInfo->VLAN_PRIORITY=iedInfo->SMVList.at(index_SMV).VLAN_PRIORITY;

					tempSMVList.append(m_smvInfo);
				}
				if(smvInfo->APPID=="0000")
					tempSMVList.append(m_smvInfo);
			}

			//����Inputs�ڵ㣬��ȡ������Ϣ
			pugi::xml_node Inputs_node=LD_node.child(L"LN0").child(L"Inputs");
			for(pugi::xml_node ExtRef_node=Inputs_node.child(L"ExtRef");ExtRef_node;
				ExtRef_node=ExtRef_node.next_sibling(L"ExtRef"))
			{
				//����һ��LN�ڵ��LN_str��hash
				if(LN_hash.size()==0)
					CreateLNHash(LD_node,&LN_hash);

				pugi::xml_node AccessPoint_node=LD_node.parent().parent();
				QString AccessPoint_name = QString::fromWCharArray(AccessPoint_node.attribute(L"name").value());
				//��ȡGOOSE-Inputs
				if(AccessPoint_name.indexOf("M")!=-1)
				{
					SCL_SUB_REC_INFO_QT subRecInfo;
					subRecInfo.sub_IED_name = QString::fromWCharArray(ExtRef_node.attribute(L"iedName").value());

					if (wcslen(ExtRef_node.attribute(L"daName").value()) > 0)
					{
						subRecInfo.sub_ref=QString("%1/%2%3%4.%5.%6").arg(QString::fromWCharArray(ExtRef_node.attribute(L"ldInst").value()),
							QString::fromWCharArray(ExtRef_node.attribute(L"prefix").value()),
							QString::fromWCharArray(ExtRef_node.attribute(L"lnClass").value()),
							QString::fromWCharArray(ExtRef_node.attribute(L"lnInst").value()),
							QString::fromWCharArray(ExtRef_node.attribute(L"doName").value()),
							QString::fromWCharArray(ExtRef_node.attribute(L"daName").value()));
					}
					else
					{
						subRecInfo.sub_ref=QString("%1/%2%3%4.%5").arg(QString::fromWCharArray(ExtRef_node.attribute(L"ldInst").value()),
							QString::fromWCharArray(ExtRef_node.attribute(L"prefix").value()),
							QString::fromWCharArray(ExtRef_node.attribute(L"lnClass").value()),
							QString::fromWCharArray(ExtRef_node.attribute(L"lnInst").value()),
							QString::fromWCharArray(ExtRef_node.attribute(L"doName").value()));
					}

					subRecInfo.sub_ldInst = QString::fromWCharArray(ExtRef_node.attribute(L"ldInst").value());
					subRecInfo.index_IED=-1;
					subRecInfo.index_GSE_SMV=-1;
					subRecInfo.index_Rec=-1;
					subRecInfo.ref = QString::fromWCharArray(ExtRef_node.attribute(L"intAddr").value());
					QStringList DO_name_Split=subRecInfo.ref.split('.');

					if(DO_name_Split.size()<2)
					{
						iedInfo->SVSubList.append(subRecInfo);
						continue;
					}
					QString DO_name=DO_name_Split[1];
					QString LNstr=DO_name_Split[0];
					DO_name_Split=LNstr.split('/');
					LNstr=DO_name_Split[1];

					pugi::xml_node LN_find=LN_hash.value(LNstr);

					strTmpPath = "./DOI[@name='"+DO_name+"']";

#ifdef _MSC_VER
					wstrTmp =  std::wstring((const wchar_t *)strTmpPath.utf16());
#else
					wstrTmp = strTmpPath.toStdWString();
#endif
					const wchar_t * DOIChar = wstrTmp.c_str();
					//                     const QByteArray DOIText= strTmpPath.toLocal8Bit();
					//                     const char *DOIChar = DOIText.data();

					pugi::xpath_node DOI_xml=LN_find.select_node(DOIChar);
					subRecInfo.desc = QString::fromWCharArray(DOI_xml.node().attribute(L"desc").value());
					if(subRecInfo.desc=="")
						subRecInfo.desc = QString::fromWCharArray(LN_find.attribute(L"desc").value());

					iedInfo->SVSubList.append(subRecInfo);
				}
				else
				{
					SCL_SUB_REC_INFO_QT subRecInfo;
					subRecInfo.sub_IED_name = QString::fromWCharArray(ExtRef_node.attribute(L"iedName").value());

					if (wcslen(ExtRef_node.attribute(L"daName").value()) > 0)
					{
						subRecInfo.sub_ref=QString("%1/%2%3%4.%5.%6").arg(QString::fromWCharArray(ExtRef_node.attribute(L"ldInst").value()),
							QString::fromWCharArray(ExtRef_node.attribute(L"prefix").value()),
							QString::fromWCharArray(ExtRef_node.attribute(L"lnClass").value()),
							QString::fromWCharArray(ExtRef_node.attribute(L"lnInst").value()),
							QString::fromWCharArray(ExtRef_node.attribute(L"doName").value()),
							QString::fromWCharArray(ExtRef_node.attribute(L"daName").value()));
					}
					else
					{
						subRecInfo.sub_ref=QString("%1/%2%3%4.%5.%6").arg(QString::fromWCharArray(ExtRef_node.attribute(L"ldInst").value()),
							QString::fromWCharArray(ExtRef_node.attribute(L"prefix").value()),
							QString::fromWCharArray(ExtRef_node.attribute(L"lnClass").value()),
							QString::fromWCharArray(ExtRef_node.attribute(L"lnInst").value()),
							QString::fromWCharArray(ExtRef_node.attribute(L"doName").value()));
					}

					subRecInfo.sub_ldInst = QString::fromWCharArray(ExtRef_node.attribute(L"ldInst").value());
					subRecInfo.index_IED=-1;
					subRecInfo.index_GSE_SMV=-1;
					subRecInfo.index_Rec=-1;
					subRecInfo.ref = QString::fromWCharArray(ExtRef_node.attribute(L"intAddr").value());
					QStringList DO_name_Split=subRecInfo.ref.split('.');
					if(DO_name_Split.size()<2)
					{
						iedInfo->GOSubList.append(subRecInfo);
						continue;
					}
					QString DO_name=DO_name_Split[1];
					QString LNstr=DO_name_Split[0];
					DO_name_Split=LNstr.split('/');
					LNstr=DO_name_Split[1];

					pugi::xml_node LN_find=LN_hash.value(LNstr);

					strTmpPath="./DOI[@name='"+DO_name+"']";

#ifdef _MSC_VER
					wstrTmp =  std::wstring((const wchar_t *)strTmpPath.utf16());
#else
					wstrTmp = strTmpPath.toStdWString();
#endif
					const wchar_t * DOIChar = wstrTmp.c_str();
					//                     const QByteArray DOIText= strTmpPath.toLocal8Bit();
					//                     const char *DOIChar = DOIText.data();

					pugi::xpath_node DOI_xml=LN_find.select_node(DOIChar);
					subRecInfo.desc = QString::fromWCharArray(DOI_xml.node().attribute(L"desc").value());
					if(subRecInfo.desc=="")
						subRecInfo.desc = QString::fromWCharArray(LN_find.attribute(L"desc").value());

					iedInfo->GOSubList.append(subRecInfo);
				}
			}
		}

		//�����ǰ�ģ�����µ�
		iedInfo->GSEList.clear();
		iedInfo->GSEList.append(tempGSEList);

		iedInfo->SMVList.clear();
		iedInfo->SMVList.append(tempSMVList);

		//		oProgressDlg.setValue(30+65*index_IED/m_oSclIedList.size());
	}

	//ƥ�䶩�Ķ���
	for(int index_IED=0;index_IED<m_oSclIedList.size();index_IED++)
	{
		//����ÿһ��IED�Ķ��������
		SCL_IED_INFO_QT *iedInfo = m_oSclIedList[index_IED];
		//ƥ��GOOSE���������
		for(int index_subRec=0;index_subRec<iedInfo->GOSubList.size();index_subRec++)
		{
			//ƥ����ɱ��
			bool flag=false;
			SCL_SUB_REC_INFO_QT *subRecInfo=&iedInfo->GOSubList[index_subRec];
			//�ҵ���������ӵ�IED
			int index_pubIED=m_oIedNameHash.value(subRecInfo->sub_IED_name);
			SCL_IED_INFO_QT *pubIedInfo = m_oSclIedList[index_pubIED];
			//�ҵ�GSE
			for(int index_GSE=0;index_GSE<pubIedInfo->GSEList.size();index_GSE++)
			{
				SCL_GSE_INFO_QT *gseInfo=&pubIedInfo->GSEList[index_GSE];
				//ƥ��GSE��ldInst
				if(subRecInfo->sub_ldInst==gseInfo->ldInst)
				{
					//ƥ�䷢��������붩�������
					for(int index_pubRec=0;index_pubRec<gseInfo->pubList.size();index_pubRec++)
					{
						SCL_PUB_REC_INFO_QT *pubRecInfo=&gseInfo->pubList[index_pubRec];
						if(subRecInfo->sub_ref==pubRecInfo->ref)
						{
							//������Ϣ
							subRecInfo->index_IED=index_pubIED;
							subRecInfo->index_GSE_SMV=index_GSE;
							subRecInfo->index_Rec=index_pubRec;

							SCL_CONNECT_PUB_INFO_QT connectPubInfo;
							connectPubInfo.index_IED=index_IED;
							connectPubInfo.index_Rec=index_subRec;

							pubRecInfo->recPubList.append(connectPubInfo);

							flag=true;

							break;
						}
					}
				}
				if(flag) break;
			}

			if(subRecInfo->index_IED==-1||subRecInfo->index_GSE_SMV==-1||subRecInfo->index_Rec==-1)
			{
				//                Log4Qt::Logger *log = Log4Qt::Logger::logger("CMXL");
				//                QString Msg=QString(tr("�������������룬û���ҵ���IED name is:%1.AccessPoint is GOOSE.reference is:%2")).
				//                        arg(iedInfo->name).arg(subRecInfo->ref);
				//                log->error(Msg);
				m_nSclAnalyzeErrorNum++;
			}
		}

		//ƥ��SMV���������
		for(int index_subRec=0;index_subRec<iedInfo->SVSubList.size();index_subRec++)
		{
			//ƥ����ɱ��
			bool flag=false;
			SCL_SUB_REC_INFO_QT *subRecInfo=&iedInfo->SVSubList[index_subRec];
			//�ҵ���������ӵ�IED
			int index_pubIED=m_oIedNameHash.value(subRecInfo->sub_IED_name);
			SCL_IED_INFO_QT *pubIedInfo = m_oSclIedList[index_pubIED];
			//��������IED��SMV���ҵ�ƥ���IED
			for(int index_SMV=0;index_SMV<pubIedInfo->SMVList.size();index_SMV++)
			{
				SCL_SMV_INFO_QT *smvInfo=&pubIedInfo->SMVList[index_SMV];
				//ƥ��GSE��ldInst
				if(subRecInfo->sub_ldInst==smvInfo->ldInst)
				{
					//����SMV�ķ������ݼ���ƥ�䷢��������붩�������
					for(int index_pubRec=0;index_pubRec<smvInfo->pubList.size();index_pubRec++)
					{
						SCL_PUB_REC_INFO_QT *pubRecInfo=&smvInfo->pubList[index_pubRec];
						if(subRecInfo->sub_ref==pubRecInfo->ref)
						{
							//������Ϣ
							subRecInfo->index_IED=index_pubIED;
							subRecInfo->index_GSE_SMV=index_SMV;
							subRecInfo->index_Rec=index_pubRec;

							SCL_CONNECT_PUB_INFO_QT connectPubInfo;
							connectPubInfo.index_IED=index_IED;
							connectPubInfo.index_Rec=index_subRec;

							pubRecInfo->recPubList.append(connectPubInfo);

							flag=true;

							break;
						}
					}
				}
				if(flag) break;
			}

			if(subRecInfo->index_IED==-1||subRecInfo->index_GSE_SMV==-1||subRecInfo->index_Rec==-1)
			{
				//                Log4Qt::Logger *log = Log4Qt::Logger::logger("CMXL");
				//                QString Msg=QString(tr("�������������룬û���ҵ���IED name is:%1.AccessPoint is SMV.reference is:%2")).
				//                        arg(iedInfo->name).arg(subRecInfo->ref);
				//                log->error(Msg);
				m_nSclAnalyzeErrorNum++;
			}
		}
	}


	//ƥ�������,��ֹG���ʵ㽨ģSMV���룬����M���ʵ㣬��ģGOOSE����
	for(int index_IED=0;index_IED<m_oSclIedList.size();index_IED++)
	{
		//��SMV���ҵ���goPub��¼
		QList<int> goSub_SMV_list;
		//����ÿһ��IED�Ķ��������
		SCL_IED_INFO_QT *iedInfo = m_oSclIedList[index_IED];
		//ƥ��GOOSE���������
		for(int index_subRec=0;index_subRec<iedInfo->GOSubList.size();index_subRec++)
		{
			//ƥ����ɱ��
			bool flag=false;
			SCL_SUB_REC_INFO_QT *subRecInfo=&iedInfo->GOSubList[index_subRec];
			//�����Ѿ��ҵ��ļ�¼
			if(subRecInfo->index_IED!=-1)   continue;
			//�ж��Ƿ���SMV������
			int index_pubIED=m_oIedNameHash.value(subRecInfo->sub_IED_name);
			SCL_IED_INFO_QT *pubIedInfo = m_oSclIedList[index_pubIED];
			//�ҵ�SMV
			for(int index_SMV=0;index_SMV<pubIedInfo->SMVList.size();index_SMV++)
			{
				SCL_SMV_INFO_QT *gseInfo=&pubIedInfo->SMVList[index_SMV];
				//ƥ��SMV��ldInst
				if(subRecInfo->sub_ldInst==gseInfo->ldInst)
				{
					//ƥ�䷢��������붩�������
					for(int index_pubRec=0;index_pubRec<gseInfo->pubList.size();index_pubRec++)
					{
						SCL_PUB_REC_INFO_QT *pubRecInfo=&gseInfo->pubList[index_pubRec];
						if(subRecInfo->sub_ref==pubRecInfo->ref)
						{
							//���¶���IED�ķ���IED����Ϣ
							subRecInfo->index_IED=index_pubIED;
							subRecInfo->index_GSE_SMV=index_SMV;
							subRecInfo->index_Rec=index_pubRec;

							//���·����ķ�IED����Ϣ
							SCL_CONNECT_PUB_INFO_QT connectPubInfo;
							connectPubInfo.index_IED=index_IED;
							connectPubInfo.index_Rec=index_subRec;
							pubRecInfo->recPubList.append(connectPubInfo);

							//���
							goSub_SMV_list.append(index_subRec);

							flag=true;

							break;
						}
					}
				}
				if(flag) break;
			}
		}

		//����Щ��¼��ӵ�SMVSub��
		for(int index=0;index<goSub_SMV_list.size();index++)
		{
			iedInfo->SVSubList.append(iedInfo->GOSubList.at(goSub_SMV_list.at(index)));
		}

		//����Щ��¼�Ƴ�GSESub��
		for(int index=0;index<goSub_SMV_list.size();index++)
		{
			iedInfo->GOSubList.removeAt(goSub_SMV_list.at(index)-index);
		}

		//��GSV���ҵ���smvPub��¼
		QList<int> smvSub_GSE_list;
		//ƥ��GOOSE���������
		for(int index_subRec=0;index_subRec<iedInfo->SVSubList.size();index_subRec++)
		{
			//ƥ����ɱ��
			bool flag=false;
			SCL_SUB_REC_INFO_QT *subRecInfo=&iedInfo->SVSubList[index_subRec];
			//�����Ѿ��ҵ��ļ�¼
			if(subRecInfo->index_IED!=-1)   continue;
			//�ж��Ƿ���SMV������
			int index_pubIED=m_oIedNameHash.value(subRecInfo->sub_IED_name);
			SCL_IED_INFO_QT *pubIedInfo = m_oSclIedList[index_pubIED];
			//�ҵ�SMV
			for(int index_GSE=0;index_GSE<pubIedInfo->GSEList.size();index_GSE++)
			{
				SCL_GSE_INFO_QT *gseInfo=&pubIedInfo->GSEList[index_GSE];
				//ƥ��GSE��ldInst
				if(subRecInfo->sub_ldInst==gseInfo->ldInst)
				{
					//ƥ�䷢��������붩�������
					for(int index_pubRec=0;index_pubRec<gseInfo->pubList.size();index_pubRec++)
					{
						SCL_PUB_REC_INFO_QT *pubRecInfo=&gseInfo->pubList[index_pubRec];
						if(subRecInfo->sub_ref==pubRecInfo->ref)
						{
							//���¶���IED�ķ���IED����Ϣ
							subRecInfo->index_IED=index_pubIED;
							subRecInfo->index_GSE_SMV=index_GSE;
							subRecInfo->index_Rec=index_pubRec;

							//���·����ķ�IED����Ϣ
							SCL_CONNECT_PUB_INFO_QT connectPubInfo;
							connectPubInfo.index_IED=index_IED;
							connectPubInfo.index_Rec=index_subRec;
							pubRecInfo->recPubList.append(connectPubInfo);

							//���
							smvSub_GSE_list.append(index_subRec);

							flag=true;

							break;
						}
					}
				}
				if(flag) break;
			}
		}

		//����Щ��¼��ӵ�GSESub��
		for(int index=0;index<smvSub_GSE_list.size();index++)
		{
			iedInfo->GOSubList.append(iedInfo->SVSubList.at(smvSub_GSE_list.at(index)));
		}

		//����Щ��¼�Ƴ�SMVSub��
		for(int index=0;index<smvSub_GSE_list.size();index++)
		{
			iedInfo->SVSubList.removeAt(smvSub_GSE_list.at(index)-index);
		}
	}

	//	oProgressDlg.setValue(100);
	//	qDebug()<<strSclFilePath<<":"<<oTime.elapsed()/1000.0<<"s";
	//QString Msg=QString(tr("���������%1\n�������飬��鿴LOG�ļ�")).arg(errMsg_counter);
	//QMessageBox::information(this,tr("����"),Msg);

#ifndef USE_IN_Astra_LINUX//zhouhj 2024.4.27 �ǹ��ʲ������Բ��ô˷�ʽ
	SetLocalCodec("GBK");
#endif

	oPugiDoc.reset();

	// 	//yzj 2024.1.10 ����������Ҳ���,�����ڴ����ռ��
	// 	FreeAllList();

	return TRUE;
}


QString QSclFileRead::GetDataFC(const DataFC dataFC, const QString id, const QString name, const QString fc)
{
	QString strFC="";
	switch(dataFC)
	{
	case DOType:
		{
			DataTypeHash DO_hash=m_oLNodeType_Hash.value(id);
			pugi::xml_node DO_node=DO_hash.value(name);
			strFC = QString::fromWCharArray(DO_node.attribute(L"type").value());
			break;
		}
	case SDOType:
		{
			pugi::xml_node DOType_xml=m_oDOType_Hash.value(id);
			for(pugi::xml_node SDO_xml=DOType_xml.child(L"SDO");SDO_xml;SDO_xml=SDO_xml.next_sibling(L"SDO"))
			{
				QString SDO_name = QString::fromWCharArray(SDO_xml.attribute(L"name").value());
				if(SDO_name==name)
				{
					strFC = QString::fromWCharArray(SDO_xml.attribute(L"type").value());
					break;
				}
			}

			break;
		}
		//���������������ҵ��������ͣ�ֱ�ӷ�����������
	case  DAType:
		{
			pugi::xml_node DOType_node=m_oDOType_Hash.value(id);

			//FCDAû�ж���DA�����
			if(name=="")
			{
				for(pugi::xml_node DA_node=DOType_node.child(L"DA");DA_node;DA_node=DA_node.next_sibling(L"DA"))
				{
					//��ȡFC��ͬ�Ľڵ�
					if(QString("%1").arg(QString::fromWCharArray(DA_node.attribute(L"fc").value()))==fc)
					{
						//���DA�ڵ㻹��SDI�ڵ�
						if(QString("%1").arg(QString::fromWCharArray(DA_node.attribute(L"bType").value()))=="Struct")
						{
							pugi::xml_node DAType_node=this->m_oDAType_Hash.value(QString("%1").arg(QString::fromWCharArray(DA_node.attribute(L"type").value())));
							//��ȡBDA�ڵ����Ϣ
							for(pugi::xml_node BDA_node=DAType_node.child(L"BDA");BDA_node;BDA_node=BDA_node.next_sibling(L"BDA"))
							{
								//���BDA�ڵ㻹��SDI�ڵ�
								if(QString("%1").arg(QString::fromWCharArray(BDA_node.attribute(L"bType").value()))=="Struct")
								{
									QString bType=GetDataFC(
										QSclFileRead::BDAType,
										QString("%1").arg(QString::fromWCharArray(BDA_node.attribute(L"type").value())),
										"",
										fc);

									if(strFC=="")
										strFC=bType;
									else
										strFC+=bType;
								}
								else
								{
									if(strFC=="")
										strFC=QString("%1").arg(QString::fromWCharArray(BDA_node.attribute(L"bType").value()));
									else
										strFC+=QString(",%1").arg(QString::fromWCharArray(BDA_node.attribute(L"bType").value()));
								}
							}
						}
						else
						{
							if(strFC=="")
								strFC=QString("%1").arg(QString::fromWCharArray(DA_node.attribute(L"bType").value()));
							else
								strFC+=QString(",%1").arg(QString::fromWCharArray(DA_node.attribute(L"bType").value()));
						}
					}
				}

			}
			else
			{
				QStringList strSplit=name.split('.');
				pugi::xml_node DA_xml;
				for(DA_xml=DOType_node.child(L"DA");DA_xml;DA_xml=DA_xml.next_sibling(L"DA"))
				{
					QString DA_name = QString::fromWCharArray(DA_xml.attribute(L"name").value());
					if(DA_name==strSplit[0])
					{
						break;
					}
				}

				if(strSplit.size()>1)
				{
					QString DAType_id = QString::fromWCharArray(DA_xml.attribute(L"type").value());
					QString BDA_name=name.right(name.length()-strSplit[0].length()-1);
					strFC=GetDataFC(QSclFileRead::BDAType,DAType_id,BDA_name,fc);
				}
				else
				{
					strFC = QString::fromWCharArray(DA_xml.attribute(L"bType").value());
				}
			}

			break;
		}
	case BDAType:
		{
			//�����������nameΪ�գ���˵��ȫ����ȡ
			if(name=="")
			{
				pugi::xml_node DAType_node=this->m_oDAType_Hash.value(id);
				//��ȡBDA�ڵ����Ϣ
				for(pugi::xml_node BDA_node=DAType_node.child(L"BDA");BDA_node;BDA_node=BDA_node.next_sibling(L"BDA"))
				{
					//���BDA�ڵ㻹��SDI�ڵ�
					if(QString("%1").arg(QString::fromWCharArray(BDA_node.attribute(L"bType").value()))=="Struct")
					{
						QString bType=GetDataFC(
							QSclFileRead::BDAType,
							QString("%1").arg(QString::fromWCharArray(BDA_node.attribute(L"type").value())),
							"",
							fc);

						if(strFC=="")
							strFC=bType;
						else
							strFC+=bType;
					}
					else
					{
						if(strFC=="")
							strFC=QString("%1").arg(QString::fromWCharArray(BDA_node.attribute(L"bType").value()));
						else
							strFC+=QString(",%1").arg(QString::fromWCharArray(BDA_node.attribute(L"bType").value()));
					}
				}
			}
			else
			{
				QStringList strSplit=name.split('.');
				pugi::xml_node DAType_xml=m_oDAType_Hash.value(id);
				for(pugi::xml_node BDA_xml=DAType_xml.child(L"BDA");BDA_xml;BDA_xml=BDA_xml.next_sibling(L"BDA"))
				{
					QString BDA_name = QString::fromWCharArray(BDA_xml.attribute(L"name").value());
					if(BDA_name==strSplit[0])
					{
						if(strSplit.size()>1)
						{
							QString DAType_id = QString::fromWCharArray(BDA_xml.attribute(L"type").value());
							QString BDA_name=name.right(name.length()-strSplit[0].length()-1);
							strFC=GetDataFC(QSclFileRead::BDAType,DAType_id,BDA_name,fc);
						}
						else
						{
							strFC = QString::fromWCharArray(BDA_xml.attribute(L"bType").value());
						}
						break;
					}
				}
			}

			break;
		}
	default:
		break;
	}

	return strFC;
}

void QSclFileRead::CreateLNHash(const pugi::xml_node LD_node, DataTypeHash *pLN_hash)
{
	for(pugi::xml_node LN_node=LD_node.first_child();LN_node;LN_node=LN_node.next_sibling())
	{
		QString LNstr=QString("%1%2%3").arg(QString::fromWCharArray(LN_node.attribute(L"prefix").value()),
			QString::fromWCharArray(LN_node.attribute(L"lnClass").value()),QString::fromWCharArray(LN_node.attribute(L"inst").value()));
		if(!pLN_hash->contains(LNstr))
		{
			pLN_hash->insert(LNstr,LN_node);
		}
		else
		{
			//            Log4Qt::Logger *log = Log4Qt::Logger::logger("CMXL");
			//            QString Msg=QString("SCL-IED-AccessPoint-Server-LD-LN error:node Repeated!LN is:%1").
			//                    arg(LNstr);
			//            log->error(Msg);
			m_nSclAnalyzeErrorNum++;
		}
	}
}

//��������ģ���ϣ�����ڲ�����������
void QSclFileRead::CreateDataTypeTemplatesHash(pugi::xml_node oRootNodePugi)
{
	pugi::xml_node tools=oRootNodePugi.child(L"SCL").child(L"DataTypeTemplates");

	for(pugi::xml_node tool=tools.first_child();tool;tool=tool.next_sibling())
	{
		QString node_name = QString::fromWCharArray(tool.name());
		if(node_name=="LNodeType")
		{
			QString id = QString::fromWCharArray(tool.attribute(L"id").value());

			//��DO�ڵ㽨����ϣ��
			DataTypeHash DO_Hash;
			for(pugi::xml_node DO_xml=tool.first_child();DO_xml;DO_xml=DO_xml.next_sibling())
			{
				QString DO_name = QString::fromWCharArray(DO_xml.attribute(L"name").value());
				//QString DO_type=DO_xml.attribute("type").value();
				if(!DO_Hash.contains(DO_name))
				{
					//DO_Hash.insert(DO_name,DO_type);
					DO_Hash.insert(DO_name,DO_xml);
				}
				else
				{
					//                    Log4Qt::Logger *log = Log4Qt::Logger::logger("CMXL");
					//                    QString Msg=QString("SCL-DataTypeTemplates-LNodeType-DO error:node Repeated!LNOdeType id is:%1.DO name is:%2").
					//                            arg(id).arg(DO_name);
					//                    log->error(Msg);
					m_nSclAnalyzeErrorNum++;
				}
			}
			if(!m_oLNodeType_Hash.contains(id))
			{
				m_oLNodeType_Hash.insert(id,DO_Hash);
			}
			else
			{
				//                Log4Qt::Logger *log = Log4Qt::Logger::logger("CMXL");
				//                QString Msg=QString("SCL-DataTypeTemplates-LNodeType error:node Repeated!LNOdeType id is:%1").
				//                        arg(id);
				//                log->error(Msg);
				m_nSclAnalyzeErrorNum++;
			}
		}
		else if(node_name=="DOType")
		{
			QString id = QString::fromWCharArray(tool.attribute(L"id").value());
			if(!m_oDOType_Hash.contains(id))
			{
				m_oDOType_Hash.insert(id,tool);
			}
			else
			{
				//                Log4Qt::Logger *log = Log4Qt::Logger::logger("CMXL");
				//                QString Msg=QString("SCL-DataTypeTemplates-DOType error:node Repeated!DOType id is:%1.").
				//                        arg(id);
				//                log->error(Msg);
				m_nSclAnalyzeErrorNum++;
			}
		}
		else if(node_name=="DAType")
		{
			QString id = QString::fromWCharArray(tool.attribute(L"id").value());
			if(!m_oDAType_Hash.contains(id))
			{
				m_oDAType_Hash.insert(id,tool);
			}
			else
			{
				//                Log4Qt::Logger *log = Log4Qt::Logger::logger("CMXL");
				//                QString Msg=QString("SCL-DataTypeTemplates-DAType error:node Repeated!DAType id is:%1").
				//                        arg(id);
				//                log->error(Msg);
				m_nSclAnalyzeErrorNum++;
			}
		}
	}
}


BOOL QSclFileRead::SavePscdFile(const CString &strPscdFilePath)
{
	pugi::xml_document doc;
	//add declaration
	pugi::xml_node decl=doc.prepend_child(pugi::node_declaration);
	decl.append_attribute(L"version") = L"1.0";
	decl.append_attribute(L"encoding") = L"UTF-8";

	// add root
	pugi::xml_node root = doc.append_child(L"PSCD");

	//add child node--goose pub
	foreach(SCL_IED_INFO_QT *iedInfo,m_oSclIedList)
	{
		std::string str;
		pugi::xml_node IED_node = root.append_child(L"IED");
#ifdef _USE_IN_IED_QT5
		std::wstring wstrTmp =  iedInfo->name.toStdWString();
#else
		QStdWString wstrTmp =  iedInfo->name.toStdWString();
#endif
		const wchar_t *ch1 = wstrTmp.c_str();
		pugi::xml_attribute oXMlAttr =  IED_node.append_attribute(L"name");
		oXMlAttr.set_value(ch1);
		wstrTmp = iedInfo->type.toStdWString();
		const wchar_t *ch2 = wstrTmp.c_str(); 

		//        const char *ch2=str.c_str();
		IED_node.append_attribute(L"type")=ch2;

		//        str=iedInfo.desc.toStdString();
		wstrTmp = iedInfo->desc.toStdWString();
		const wchar_t *ch3=wstrTmp.c_str(); 
		IED_node.append_attribute(L"desc")=ch3;

		//        str=iedInfo.manufacturer.toStdString();
		wstrTmp = iedInfo->manufacturer.toStdWString();
		const wchar_t *ch4=wstrTmp.c_str(); 
		IED_node.append_attribute(L"manufacturer")=ch4;

		//        str=iedInfo.configVersion.toStdString();
		wstrTmp = iedInfo->configVersion.toStdWString();
		const wchar_t *ch5=wstrTmp.c_str(); 
		IED_node.append_attribute(L"configVersion")=ch5;

		//GOOSE pub
		foreach(SCL_GSE_INFO_QT gseInfo,iedInfo->GSEList)
		{
			pugi::xml_node GSE_node=IED_node.append_child(L"GSE");

			//            str=gseInfo.apName.toStdString();
			wstrTmp = gseInfo.apName.toStdWString();
			const wchar_t *gse_ch1=wstrTmp.c_str(); 
			GSE_node.append_attribute(L"apName")=gse_ch1;

			//            str=gseInfo.cbName.toStdString();
			wstrTmp = gseInfo.cbName.toStdWString();
			const wchar_t *gse_ch2=wstrTmp.c_str(); 
			GSE_node.append_attribute(L"cbName")=gse_ch2;

			//            str=gseInfo.ldInst.toStdString();
			wstrTmp = gseInfo.ldInst.toStdWString();
			const wchar_t *gse_ch3=wstrTmp.c_str(); 
			GSE_node.append_attribute(L"ldInst")=gse_ch3;

			//            str=gseInfo.desc.toStdString();
			wstrTmp = gseInfo.desc.toStdWString();
			const wchar_t *gse_ch15=wstrTmp.c_str(); 
			GSE_node.append_attribute(L"desc")=gse_ch15;

			//            str=gseInfo.MAC_Adress.toStdString();
			wstrTmp = gseInfo.MAC_Adress.toStdWString();
			const wchar_t *gse_ch4=wstrTmp.c_str(); 
			GSE_node.append_attribute(L"MAC_Address")=gse_ch4;

			//            str=gseInfo.VLAN_ID.toStdString();
			wstrTmp = gseInfo.VLAN_ID.toStdWString();
			const wchar_t *gse_ch5=wstrTmp.c_str(); 
			GSE_node.append_attribute(L"VLAN_ID")=gse_ch5;

			//            str=gseInfo.APPID.toStdString();
			wstrTmp = gseInfo.APPID.toStdWString();
			const wchar_t *gse_ch6=wstrTmp.c_str(); 
			GSE_node.append_attribute(L"APPID")=gse_ch6;

			//           str=gseInfo.VLAN_PRIORITY.toStdString();
			wstrTmp = gseInfo.VLAN_PRIORITY.toStdWString();
			const wchar_t *gse_ch7=wstrTmp.c_str(); 
			GSE_node.append_attribute(L"VLAN_PRIORITY")=gse_ch7;

			GSE_node.append_attribute(L"MinTime")=gseInfo.MinTime;
			GSE_node.append_attribute(L"MaxTime")=gseInfo.MaxTime;

			//            str=gseInfo.datSet.toStdString();
			wstrTmp = gseInfo.datSet.toStdWString();
			const wchar_t *gse_ch10=wstrTmp.c_str(); 
			GSE_node.append_attribute(L"DataSet")=gse_ch10;

			//            str=gseInfo.DataSetDesc.toStdString();
			wstrTmp = gseInfo.DataSetDesc.toStdWString();
			const wchar_t *gse_ch13=wstrTmp.c_str(); 
			GSE_node.append_attribute(L"DataSetDesc")=gse_ch13;

			//            str=gseInfo.goID.toStdString();
			wstrTmp = gseInfo.goID.toStdWString();
			const wchar_t *gse_ch11=wstrTmp.c_str(); 
			GSE_node.append_attribute(L"goID")=gse_ch11;

			//            str=gseInfo.confRev.toStdString();
			wstrTmp = gseInfo.confRev.toStdWString();
			const wchar_t *gse_ch14=wstrTmp.c_str(); 
			GSE_node.append_attribute(L"confRev")=gse_ch14;


			foreach(SCL_PUB_REC_INFO_QT pubInfo,gseInfo.pubList)
			{
				pugi::xml_node PUB_node=GSE_node.append_child(L"GOPUB");

				//                str=pubInfo.ref.toStdString();
				wstrTmp = pubInfo.ref.toStdWString();
				const wchar_t *pub_ch1=wstrTmp.c_str(); 
				PUB_node.append_attribute(L"reference")=pub_ch1;

				//                str=pubInfo.desc.toStdString();
				wstrTmp = pubInfo.desc.toStdWString();
				const wchar_t *pub_ch2=wstrTmp.c_str();
				PUB_node.append_attribute(L"desc")=pub_ch2;

				//                str=pubInfo.bType.toStdString();
				wstrTmp = pubInfo.bType.toStdWString();
				const wchar_t *pub_ch3=wstrTmp.c_str();
				PUB_node.append_attribute(L"bType")=pub_ch3;

				foreach(SCL_CONNECT_PUB_INFO_QT conInfo,pubInfo.recPubList)
				{
					pugi::xml_node CON_node=PUB_node.append_child(L"Outputs");

					CON_node.append_attribute(L"index_IED")=conInfo.index_IED;
					CON_node.append_attribute(L"index_Rec")=conInfo.index_Rec;
				}
			}
		}

		//SMV pub
		foreach(SCL_SMV_INFO_QT gseInfo,iedInfo->SMVList)
		{
			pugi::xml_node GSE_node=IED_node.append_child(L"SMV");

			//            str=gseInfo.apName.toStdString();
			wstrTmp = gseInfo.apName.toStdWString();
			const wchar_t *gse_ch1=wstrTmp.c_str();
			GSE_node.append_attribute(L"apName")=gse_ch1;

			//            str=gseInfo.cbName.toStdString();
			wstrTmp = gseInfo.cbName.toStdWString();
			const wchar_t *gse_ch2=wstrTmp.c_str();
			GSE_node.append_attribute(L"cbName")=gse_ch2;

			//            str=gseInfo.ldInst.toStdString();
			wstrTmp = gseInfo.ldInst.toStdWString();
			const wchar_t *gse_ch3=wstrTmp.c_str();
			GSE_node.append_attribute(L"ldInst")=gse_ch3;

			//            str=gseInfo.MAC_Adress.toStdString();
			wstrTmp = gseInfo.MAC_Adress.toStdWString();
			const wchar_t *gse_ch4=wstrTmp.c_str();
			GSE_node.append_attribute(L"MAC_Address")=gse_ch4;

			//            str=gseInfo.VLAN_ID.toStdString();
			wstrTmp = gseInfo.VLAN_ID.toStdWString();
			const wchar_t *gse_ch5=wstrTmp.c_str();
			GSE_node.append_attribute(L"VLAN_ID")=gse_ch5;

			//            str=gseInfo.APPID.toStdString();
			wstrTmp = gseInfo.APPID.toStdWString();
			const wchar_t *gse_ch6=wstrTmp.c_str();
			GSE_node.append_attribute(L"APPID")=gse_ch6;

			//            str=gseInfo.VLAN_PRIORITY.toStdString();
			wstrTmp = gseInfo.VLAN_PRIORITY.toStdWString();
			const wchar_t *gse_ch7=wstrTmp.c_str();
			GSE_node.append_attribute(L"VLAN_PRIORITY")=gse_ch7;

			//            str=gseInfo.datSet.toStdString();
			wstrTmp = gseInfo.datSet.toStdWString();
			const wchar_t *gse_ch10=wstrTmp.c_str();
			GSE_node.append_attribute(L"datSet")=gse_ch10;

			//            str=gseInfo.SmvID.toStdString();
			wstrTmp = gseInfo.SmvID.toStdWString();
			const wchar_t *gse_ch11=wstrTmp.c_str();
			GSE_node.append_attribute(L"SmvID")=gse_ch11;

			//            str=gseInfo.DataSetDesc.toStdString();
			wstrTmp = gseInfo.DataSetDesc.toStdWString();
			const wchar_t *gse_ch13=wstrTmp.c_str();
			GSE_node.append_attribute(L"DataSetDesc")=gse_ch13;

			//           str=gseInfo.confRev.toStdString();
			wstrTmp = gseInfo.confRev.toStdWString();
			const wchar_t *gse_ch14=wstrTmp.c_str();
			GSE_node.append_attribute(L"confRev")=gse_ch14;

			GSE_node.append_attribute(L"smpRate")=gseInfo.smpRate;
			GSE_node.append_attribute(L"nofASDU")=gseInfo.nofASDU;
			GSE_node.append_attribute(L"refreshTime")=gseInfo.refreshTime;
			GSE_node.append_attribute(L"sampleSynchronized")=gseInfo.sampleSynchronized;
			GSE_node.append_attribute(L"sampleRate")=gseInfo.sampleRate;
			GSE_node.append_attribute(L"security")=gseInfo.security;
			GSE_node.append_attribute(L"dataRef")=gseInfo.dataRef;

			foreach(SCL_PUB_REC_INFO_QT pubInfo,gseInfo.pubList)
			{
				pugi::xml_node PUB_node=GSE_node.append_child(L"GOPUB");

				//                str=pubInfo.ref.toStdString();
				wstrTmp = pubInfo.ref.toStdWString();
				const wchar_t *pub_ch1=wstrTmp.c_str();
				PUB_node.append_attribute(L"reference")=pub_ch1;

				//                str=pubInfo.desc.toStdString();
				wstrTmp = pubInfo.desc.toStdWString();
				const wchar_t *pub_ch2=wstrTmp.c_str();
				PUB_node.append_attribute(L"desc")=pub_ch2;

				foreach(SCL_CONNECT_PUB_INFO_QT conInfo,pubInfo.recPubList)
				{
					pugi::xml_node CON_node=PUB_node.append_child(L"Outputs");

					CON_node.append_attribute(L"index_IED")=conInfo.index_IED;
					CON_node.append_attribute(L"index_Rec")=conInfo.index_Rec;
				}
			}
		}

		//goose sub
		foreach(SCL_SUB_REC_INFO_QT subInfo,iedInfo->GOSubList)
		{
			pugi::xml_node SUB_node=IED_node.append_child(L"GOSUB");

			//            str=subInfo.ref.toStdString();
			wstrTmp = subInfo.ref.toStdWString();
			const wchar_t *sub_ch1=wstrTmp.c_str();
			SUB_node.append_attribute(L"ref")=sub_ch1;

			//            str=subInfo.desc.toStdString();
			wstrTmp = subInfo.desc.toStdWString();
			const wchar_t *sub_ch2=wstrTmp.c_str();
			SUB_node.append_attribute(L"desc")=sub_ch2;

			//            str=subInfo.sub_IED_name.toStdString();
			wstrTmp = subInfo.sub_IED_name.toStdWString();
			const wchar_t *sub_ch3=wstrTmp.c_str();
			SUB_node.append_attribute(L"sub_IED_name")=sub_ch3;

			//            str=subInfo.sub_ldInst.toStdString();
			wstrTmp = subInfo.sub_ldInst.toStdWString();
			const wchar_t *sub_ch4=wstrTmp.c_str();
			SUB_node.append_attribute(L"sub_ldInst")=sub_ch4;

			//            str=subInfo.sub_ref.toStdString();
			wstrTmp = subInfo.sub_ref.toStdWString();
			const wchar_t *sub_ch5=wstrTmp.c_str();
			SUB_node.append_attribute(L"sub_ref")=sub_ch5;

			SUB_node.append_attribute(L"index_IED")=subInfo.index_IED;
			SUB_node.append_attribute(L"index_GSE")=subInfo.index_GSE_SMV;
			SUB_node.append_attribute(L"index_Rec")=subInfo.index_Rec;
		}

		//sv sub
		foreach(SCL_SUB_REC_INFO_QT subInfo,iedInfo->SVSubList)
		{
			pugi::xml_node SUB_node=IED_node.append_child(L"SMVSUB");

			//            str=subInfo.ref.toStdString();
			wstrTmp = subInfo.ref.toStdWString();
			const wchar_t *sub_ch1=wstrTmp.c_str();
			SUB_node.append_attribute(L"ref")=sub_ch1;

			//            str=subInfo.desc.toStdString();
			wstrTmp = subInfo.desc.toStdWString();
			const wchar_t *sub_ch2=wstrTmp.c_str();
			SUB_node.append_attribute(L"desc")=sub_ch2;

			//            str=subInfo.sub_IED_name.toStdString();
			wstrTmp = subInfo.sub_IED_name.toStdWString();
			const wchar_t *sub_ch3=wstrTmp.c_str();
			SUB_node.append_attribute(L"sub_IED_name")=sub_ch3;

			//            str=subInfo.sub_ldInst.toStdString();
			wstrTmp = subInfo.sub_ldInst.toStdWString();
			const wchar_t *sub_ch4=wstrTmp.c_str();
			SUB_node.append_attribute(L"sub_ldInst")=sub_ch4;

			//            str=subInfo.sub_ref.toStdString();
			wstrTmp = subInfo.sub_ref.toStdWString();
			const wchar_t *sub_ch5=wstrTmp.c_str();
			SUB_node.append_attribute(L"sub_ref")=sub_ch5;

			SUB_node.append_attribute(L"index_IED")=subInfo.index_IED;
			SUB_node.append_attribute(L"index_SMV")=subInfo.index_GSE_SMV;
			SUB_node.append_attribute(L"index_Rec")=subInfo.index_Rec;
		}
	}

	const QByteArray baTmp=strPscdFilePath.toLocal8Bit();
	const char *chFilePath=baTmp.data();
	if(!doc.save_file(chFilePath,L"\t",pugi::format_no_escapes,pugi::encoding_utf8))
	{
		CXMessageBox::information(NULL,QObject::tr("error"),QObject::tr("Output file failed !"));
		return FALSE;
	}
	else
	{
#ifdef _PSX_QT_LINUX_  //20220509 zhouhj  linux��д�ļ���,��Ҫ����ͬ������
		system("sync");
#endif
	}

	return TRUE;
}
#endif

BOOL QSclFileRead::ReadSclFile(const CString &strSclFilePath, CSclStation *pSclStation)
{   
	m_pSclStation = pSclStation;
	m_pSclStation->DeleteAll();
	m_pSclStation->SetScdFile(strSclFilePath);
	m_pSclStation->m_strName = ParseFileName(strSclFilePath);
	m_pSclStation->m_strID = m_pSclStation->m_strName;

	FreeReadThread();
	m_bIsInReadState = TRUE;
	m_pReadThread = new CWinThread(ReadSCLThread,this);
	m_pReadThread->m_bAutoDelete = FALSE;
	m_pReadThread->start();
	return TRUE;
}

void QSclFileRead::InitThreadProgress()
{
	if (m_pProgressInterface != NULL)
	{
		m_pProgressInterface->InitThreadProgress(100,1);
		m_pProgressInterface->StepIt();
	}
}

UINT QSclFileRead::ReadSCLThread( LPVOID pParam )
{
	QSclFileRead *pSclFileRead = (QSclFileRead *)pParam;
	pSclFileRead->m_bIsInReadState = TRUE;
	CString strSclFilePath;
	strSclFilePath = pSclFileRead->m_pSclStation->GetScdFile();
	BOOL bRet = TRUE;

	if (pSclFileRead->IsTscdSclFile(strSclFilePath))
	{
		pSclFileRead->InitThreadProgress();
		pSclFileRead->m_pSclStation->OpenSclStationFile(strSclFilePath);
	}
	else if (pSclFileRead->ParseSCL(strSclFilePath))
	{
		pSclFileRead->ReadSclStation();
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("SCL file(%s)parse failed."),strSclFilePath.GetString());
		bRet = 0;
	}

	pSclFileRead->m_bIsInReadState = FALSE;
	return bRet;
}

CString QSclFileRead::GetIEDDescByIEDName(const CString &strIEDName)
{ 
	CString strIEDDesc;
	strIEDDesc = _T("");

	foreach(SCL_IED_INFO_QT *oCurIedInfo,m_oSclIedList)
	{
		if (oCurIedInfo->name == strIEDName)
		{
			strIEDDesc = oCurIedInfo->desc;
			break;
		}
	}

	return strIEDDesc;
}

DWORD QSclFileRead::GetHexValue(const QString &strHexText)
{
	CString strNewHexText = strHexText;
//	strNewHexText = QString("0x%1").arg(strHexText);
	DWORD dwValue = 0;
	HexToDWORD(strNewHexText,dwValue);
	return dwValue;
}

void QSclFileRead::ReadSclStation()
{
	CSclIed *pNewIed = NULL;
	CSclCtrlsSmvOut* pCurSmvOuts = NULL;
	CSclCtrlsSmvIn*  pCurSmvIns = NULL;
	CSclCtrlsGsOut*  pCurGsOuts = NULL;
	CSclCtrlsGsIn*   pCurGsIns = NULL;

	CSclCtrlSmvOut *pNewSclCtrlSmvOut = NULL;
	CSclCtrlGsOut *pNewSclCtrlGsOut = NULL;
	CSclCtrlSmvIn *pSclCtrlSmvIn = NULL;
	CSclCtrlGsIn *pSclCtrlGsIn = NULL;
	CSclChBase *pSclChBase = NULL;
	CSclChGs *pSclChGs = NULL;

	if (m_pProgressInterface != NULL)
	{
// 		m_pProgressInterface->SetTitle("ReadSclStation");
// 		m_pProgressInterface->ShowMsg("Loading...");
		//2024.4.22 Xuzt 修改进度条总长�
		m_pProgressInterface->InitThreadProgress(m_oSclIedList.count()*2,1);
		m_pProgressInterface->StepIt();
	}

// 	QProgressDialog oProgressDlg(m_pParentWidget);//������ʾ��������
// 	oProgressDlg.resize(300,100);
// 	oProgressDlg.setFont(QFont(QObject::tr("Arial"),10,4));
// 	oProgressDlg.setLabelText(QObject::tr("Loading..."));
// 	oProgressDlg.setRange(0,m_oSclIedList.count());

//	QDesktopWidget *desk=QApplication::desktop();  
// 	long nWidth = desk->width();
// 	long nHeight = desk->height();
// 	long nParentWidth = m_pParentWidget->width();
// 	long nParentHeight = m_pParentWidget->height();
// 	long nOwnWidth = oProgressDlg.width();
// 	long nOwnHeight = oProgressDlg.height();
//	oProgressDlg.move((desk->width() /*- oProgressDlg.width()*/)/2,(desk->height()/* - oProgressDlg.height()*/)/2);

//	oProgressDlg.move((m_pParentWidget->width() - oProgressDlg.width())/2,(m_pParentWidget->height() - oProgressDlg.height())/2);

// 	QRect rc = m_pParentWidget->topLevelWidget()->geometry();
// 	oProgressDlg.setGeometry(rc.left() + m_pParentWidget->width()/2-150, rc.top() + m_pParentWidget->height()/2 -50, 300, 100);
// 
// 	oProgressDlg.setModal(true);
// 	oProgressDlg.show();
	long nCurrIndex = 0;
	QString strMsgString;

	foreach(SCL_IED_INFO_QT *oCurIedInfo,m_oSclIedList)
	{
		nCurrIndex++;
//		oProgressDlg.setValue(nCurrIndex);
		pNewIed = new CSclIed();
		m_pSclStation->AddNewChild(pNewIed);
		pNewIed->m_strID = oCurIedInfo->name;
		pNewIed->m_strModel = oCurIedInfo->type;
		pNewIed->m_strManufacturer = oCurIedInfo->manufacturer;

		if (m_pProgressInterface != NULL)
		{
			strMsgString = QString(QObject::tr("%1/%2(%3).")).arg(nCurrIndex).arg(m_oSclIedList.count()).arg(pNewIed->m_strID);
			m_pProgressInterface->ShowMsg(strMsgString);
			m_pProgressInterface->StepIt();
		}

		 if (!oCurIedInfo->desc.isEmpty())
		 {
			 pNewIed->m_strName = oCurIedInfo->desc;
		 }
		 else
		 {
			 pNewIed->m_strName = pNewIed->m_strID;
		 }

		 pCurSmvOuts = pNewIed->GetSmvOuts();
		 pCurGsOuts = pNewIed->GetGsOuts();

		//SMV ���
		 foreach(SCL_SMV_INFO_QT oSmvInfo,oCurIedInfo->SMVList)
		 {
			 pNewSclCtrlSmvOut = new CSclCtrlSmvOut();
			 pCurSmvOuts->AddNewChild(pNewSclCtrlSmvOut);
			 pNewSclCtrlSmvOut->m_strID = oSmvInfo.SmvID;
			 pNewSclCtrlSmvOut->apName = oSmvInfo.apName;
			 pNewSclCtrlSmvOut->m_strName = oSmvInfo.cbName;
			 pNewSclCtrlSmvOut->m_strLDdesc = oSmvInfo.ldInst;
			 pNewSclCtrlSmvOut->m_strMac = oSmvInfo.MAC_Adress;
			 pNewSclCtrlSmvOut->scl_smv_VLANID = GetHexValue(oSmvInfo.VLAN_ID);
			 pNewSclCtrlSmvOut->m_dwAppID = GetHexValue(oSmvInfo.APPID);
			 pNewSclCtrlSmvOut->scl_smv_VLANPRI = GetHexValue(oSmvInfo.VLAN_PRIORITY);
			 pNewSclCtrlSmvOut->m_strDataSet = oSmvInfo.datSet;
			 pNewSclCtrlSmvOut->m_strDataSetPath.Format(_T("%s%s/LLN0$%s"), pNewIed->m_strID.GetString(), pNewSclCtrlSmvOut->m_strLDdesc.GetString(), pNewSclCtrlSmvOut->m_strDataSet.GetString());
			 pNewSclCtrlSmvOut->m_strSVID = oSmvInfo.SmvID;
			 pNewSclCtrlSmvOut->m_strDataSetDesc = oSmvInfo.DataSetDesc;
			 pNewSclCtrlSmvOut->scl_svcb_confRev = oSmvInfo.confRev.toULong();

 			 pNewSclCtrlSmvOut->scl_svcb_smpRate = oSmvInfo.smpRate;
			 pNewSclCtrlSmvOut->scl_svcb_nofASDU = oSmvInfo.nofASDU;
 			 pNewSclCtrlSmvOut->m_nChnCount = oSmvInfo.pubList.size();
//  			 GSE_node.append_attribute(L"refreshTime") = oSmvInfo.refreshTime;
//  			 GSE_node.append_attribute(L"sampleSynchronized")=oSmvInfo.sampleSynchronized;
//  			 GSE_node.append_attribute(L"sampleRate")=oSmvInfo.sampleRate;
//  			 GSE_node.append_attribute(L"security")=oSmvInfo.security;
//  			 GSE_node.append_attribute(L"dataRef")=oSmvInfo.dataRef;
 
 			 foreach(SCL_PUB_REC_INFO_QT pubInfo,oSmvInfo.pubList)
 			 {
				 pSclChBase = pNewSclCtrlSmvOut->CreateNewCh();
 				 pSclChBase->m_strID = oCurIedInfo->name + pubInfo.ref;
 				 pSclChBase->m_strName = pubInfo.desc;
				 pSclChBase->fcda_desc = pubInfo.desc;
				 pSclChBase->fcda_dodesc = pubInfo.desc;
				 pSclChBase->fcda_name = pSclChBase->m_strID;
 
//  				 foreach(SCL_CONNECT_PUB_INFO_QT conInfo,pubInfo.recPubList)
//  				 {
//  					 xml_node CON_node=PUB_node.append_child(L"Outputs");
//  
//  					 CON_node.append_attribute(L"index_IED")=conInfo.index_IED;
//  					 CON_node.append_attribute(L"index_Rec")=conInfo.index_Rec;
//  				 }
 			 }
		 }

		//GOOSE ���
 		 foreach(SCL_GSE_INFO_QT gseInfo,oCurIedInfo->GSEList)
 		 {
 			 pNewSclCtrlGsOut = new CSclCtrlGsOut();
 			 pCurGsOuts->AddNewChild(pNewSclCtrlGsOut);
 
 			 pNewSclCtrlGsOut->apName = gseInfo.apName;
  			 pNewSclCtrlGsOut->m_strID = /*gseInfo.goID*/gseInfo.cbName;//��IEC61850Config����һ��  ��FindGooseOutput��������Ҫ�õ���ֵ���ܸ�Ϊ����
//   			 wstrTmp = gseInfo.ldInst.toStdWString();
//   			 const wchar_t *gse_ch3=wstrTmp.c_str(); 
//   			 GSE_node.append_attribute(L"ldInst")=gse_ch3;
  
			 pNewSclCtrlGsOut->gocbref = gseInfo.cbName;
			 pNewSclCtrlGsOut->ldName = gseInfo.ldInst;
			 pNewSclCtrlGsOut->m_strgocbRef.Format(_T("%s%s/LLN0$GO$%s"), pNewIed->m_strID.GetString(), pNewSclCtrlGsOut->ldName.GetString(), pNewSclCtrlGsOut->gocbref.GetString());
  			 pNewSclCtrlGsOut->m_strLDdesc = gseInfo.desc;
  			 pNewSclCtrlGsOut->m_strMac = gseInfo.MAC_Adress;
  			 pNewSclCtrlGsOut->m_dwVLandID = GetHexValue(gseInfo.VLAN_ID);
  			 pNewSclCtrlGsOut->m_dwAppID = GetHexValue(gseInfo.APPID);
  			 pNewSclCtrlGsOut->m_dwVLandPriority = GetHexValue(gseInfo.VLAN_PRIORITY);
  
  			 pNewSclCtrlGsOut->scl_gse_MinTime = gseInfo.MinTime;
  			 pNewSclCtrlGsOut->scl_gse_MaxTime = gseInfo.MaxTime;
			 pNewSclCtrlGsOut->apName = gseInfo.apName;
  
  			 pNewSclCtrlGsOut->m_strDataSet = gseInfo.datSet;
			 pNewSclCtrlGsOut->m_strDataSetPath.Format(_T("%s%s/LLN0$%s"), pNewIed->m_strID.GetString(), pNewSclCtrlGsOut->ldName.GetString(), pNewSclCtrlGsOut->m_strDataSet.GetString());
  			 pNewSclCtrlGsOut->m_strDataSetDesc = gseInfo.DataSetDesc;
  			 pNewSclCtrlGsOut->m_strGooseId = gseInfo.goID;
  			 pNewSclCtrlGsOut->m_dwVersion = gseInfo.confRev.toULong();
			 pNewSclCtrlGsOut->m_nChnCount = gseInfo.pubList.size();
  
  			 foreach(SCL_PUB_REC_INFO_QT pubInfo,gseInfo.pubList)
  			 {
				 pSclChGs = (CSclChGs*)pNewSclCtrlGsOut->CreateNewCh();
				 pSclChGs->m_strName = pubInfo.desc;
				 pSclChGs->m_strID = oCurIedInfo->name + pubInfo.ref;
				 pSclChGs->fcda_dodesc = pSclChGs->m_strName;
				 pSclChGs->fcda_name = pSclChGs->m_strID;
				 pSclChGs->fcda_type = pubInfo.bType;
   
//    				 foreach(SCL_CONNECT_PUB_INFO_QT conInfo,pubInfo.recPubList)
//    				 {
//    					 xml_node CON_node=PUB_node.append_child(L"Outputs");
//    
//    					 CON_node.append_attribute(L"index_IED")=conInfo.index_IED;
//    					 CON_node.append_attribute(L"index_Rec")=conInfo.index_Rec;
//    				 }
  			 }
 		 }
	}

	CSclCtrlSmvOut *pSclCtrlSmvOut = NULL;
	CSclCtrlGsOut *pSclCtrlGsOut = NULL;
	CSclChSmvIn *pSclChSmvIn = NULL;
	CSclChGsIn *pSclChGsIn = NULL;
	long nInIndex = 1;
	nCurrIndex = 0;

	foreach(SCL_IED_INFO_QT *oCurIedInfo,m_oSclIedList)
	{
		pNewIed = (CSclIed*)m_pSclStation->FindByID(oCurIedInfo->name);
		ASSERT(pNewIed);
		pCurSmvIns = pNewIed->GetSmvIns();
		pCurGsIns = pNewIed->GetGsIns();
		nInIndex = 0;

		nCurrIndex++;

		if (m_pProgressInterface != NULL)
		{
			//2024.4.22 Xuzt 每循环一次刷一次进度条
			strMsgString = QString(QObject::tr("%1/%2(%3).")).arg(nCurrIndex).arg(m_oSclIedList.count()).arg(pNewIed->m_strID);
			m_pProgressInterface->ShowMsg(strMsgString);
			m_pProgressInterface->StepIt();
		}

		//SMV ����
		foreach(SCL_SUB_REC_INFO_QT subInfo,oCurIedInfo->SVSubList)
		{
			pSclChBase = FindVirtualTerminalCh((CSclCtrlBase **)&pSclCtrlSmvOut,subInfo.sub_IED_name,subInfo.sub_ref,TRUE);
			nInIndex++;

			if (pSclChBase == NULL)
			{
				continue;
			}

			pSclCtrlSmvIn = (CSclCtrlSmvIn*)pCurSmvIns->FindSclCtrlBySvID_DesMac(pSclCtrlSmvOut->m_strSVID,pSclCtrlSmvOut->m_strMac);

			if (pSclCtrlSmvIn == NULL)
			{
				pSclCtrlSmvIn= new CSclCtrlSmvIn();
				pCurSmvIns->AddNewChild(pSclCtrlSmvIn);
				pSclCtrlSmvIn->m_strName = pSclCtrlSmvOut->m_strName;
				pSclCtrlSmvIn->m_strID = pSclCtrlSmvOut->m_strID;
				pSclCtrlSmvIn->ldName = pSclCtrlSmvOut->ldName;
				pSclCtrlSmvIn->lnName = pSclCtrlSmvOut->lnName;
				pSclCtrlSmvIn->m_strDataSet = pSclCtrlSmvOut->m_strDataSet;
				pSclCtrlSmvIn->m_strDataSetPath = pSclCtrlSmvOut->m_strDataSetPath;
				pSclCtrlSmvIn->m_strDataSetDesc = pSclCtrlSmvOut->m_strDataSetDesc;
				pSclCtrlSmvIn->apName = pSclCtrlSmvOut->apName;
				pSclCtrlSmvIn->m_strMac = pSclCtrlSmvOut->m_strMac;
				pSclCtrlSmvIn->m_nChnRefCount = pSclCtrlSmvOut->m_nChnCount;
				pSclCtrlSmvIn->m_strLDdesc = pSclCtrlSmvOut->m_strLDdesc;
				pSclCtrlSmvIn->scl_svcb_smpRate = pSclCtrlSmvOut->scl_svcb_smpRate;
				pSclCtrlSmvIn->m_strSVID = pSclCtrlSmvOut->m_strSVID;
				pSclCtrlSmvIn->scl_svcb_nofASDU = pSclCtrlSmvOut->scl_svcb_nofASDU;
				pSclCtrlSmvIn->scl_svcb_confRev = pSclCtrlSmvOut->scl_svcb_confRev;
				pSclCtrlSmvIn->m_dwAppID = pSclCtrlSmvOut->m_dwAppID;
				pSclCtrlSmvIn->scl_smv_VLANID = pSclCtrlSmvOut->scl_smv_VLANID;
				pSclCtrlSmvIn->scl_smv_VLANPRI = pSclCtrlSmvOut->scl_smv_VLANPRI;
				pSclCtrlSmvIn->iedExtName = subInfo.sub_IED_name;
//				pSclCtrlSmvIn->m_strIedRefDesc = subInfo.sub_IED_name;
				pSclCtrlSmvIn->m_strExIedDesc = GetIEDDescByIEDName(subInfo.sub_IED_name);
//				pSclCtrlSmvIn->ldName_own = subInfo.sub_ldInst;
			}

			pSclCtrlSmvIn->m_nChnCount++;
			pSclChSmvIn = (CSclChSmvIn*)pSclCtrlSmvIn->CreateNewCh();
			//zhouhj 2023.9.19 ��Ϊ�ⲿͨ������
			pSclChSmvIn->m_strName = pSclChBase->m_strName/*subInfo.ref*/;
			pSclChSmvIn->m_strID = subInfo.sub_ref;
			pSclChSmvIn->fcda_name = subInfo.sub_ref;
			pSclChSmvIn->inPath = subInfo.ref;
			pSclChSmvIn->outIndex = subInfo.index_Rec;
			pSclChSmvIn->inIndex = nInIndex;
			pSclChSmvIn->inDODesc = subInfo.desc;
		}

		nInIndex = 0;

		//GOOSE ����
		foreach(SCL_SUB_REC_INFO_QT subInfo,oCurIedInfo->GOSubList)
		{
			pSclChBase = FindVirtualTerminalCh((CSclCtrlBase **)&pSclCtrlGsOut,subInfo.sub_IED_name,subInfo.sub_ref,FALSE);
			nInIndex++;

			if (pSclChBase == NULL)
			{
				continue;
			}

			pSclCtrlGsIn = (CSclCtrlGsIn*)pCurGsIns->FindSclCtrlByGoID_DesMac(pSclCtrlGsOut->m_strGooseId,pSclCtrlGsOut->m_strMac);//FindByID(pSclCtrlGsOut->m_strID);

			if (pSclCtrlGsIn == NULL)
			{
				pSclCtrlGsIn= new CSclCtrlGsIn();
				pCurGsIns->AddNewChild(pSclCtrlGsIn);
				pSclCtrlGsIn->m_strName = pSclCtrlGsOut->m_strName;
				pSclCtrlGsIn->m_strID = pSclCtrlGsOut->m_strID;
				pSclCtrlGsIn->ldName = pSclCtrlGsOut->ldName;
				pSclCtrlGsIn->lnName = pSclCtrlGsOut->lnName;
				pSclCtrlGsIn->m_strDataSet = pSclCtrlGsOut->m_strDataSet;
				pSclCtrlGsIn->m_strDataSetPath = pSclCtrlGsOut->m_strDataSetPath;
				pSclCtrlGsIn->m_strDataSetDesc = pSclCtrlGsOut->m_strDataSetDesc;
				pSclCtrlGsIn->apName = pSclCtrlGsOut->apName;
				pSclCtrlGsIn->apName_own = pSclCtrlGsOut->apName;//zhouhj 20220415 ��ǰδ��¼����apName�ô˱�ʶ
				pSclCtrlGsIn->m_strMac = pSclCtrlGsOut->m_strMac;
				pSclCtrlGsIn->m_nChnRefCount = pSclCtrlGsOut->m_nChnCount;
				pSclCtrlGsIn->m_strLDdesc = pSclCtrlGsOut->m_strLDdesc;
				pSclCtrlGsIn->gocbref = pSclCtrlGsOut->gocbref;
				pSclCtrlGsIn->m_strgocbRef = pSclCtrlGsOut->m_strgocbRef;
				pSclCtrlGsIn->m_dwVersion = pSclCtrlGsOut->m_dwVersion;
				pSclCtrlGsIn->m_strGooseId = pSclCtrlGsOut->m_strGooseId;
				pSclCtrlGsIn->m_dwAppID = pSclCtrlGsOut->m_dwAppID;
				pSclCtrlGsIn->m_dwVLandID = pSclCtrlGsOut->m_dwVLandID;
				pSclCtrlGsIn->m_dwVLandPriority = pSclCtrlGsOut->m_dwVLandPriority;
				pSclCtrlGsIn->scl_gse_MinTime = pSclCtrlGsOut->scl_gse_MinTime;
				pSclCtrlGsIn->scl_gse_MaxTime = pSclCtrlGsOut->scl_gse_MaxTime;
				pSclCtrlGsIn->m_strIedID = subInfo.sub_IED_name;
				pSclCtrlGsIn->m_strExIedDesc = GetIEDDescByIEDName(subInfo.sub_IED_name);
//				pSclCtrlGsIn->ldName_own = subInfo.sub_ldInst;
			}

			pSclCtrlGsIn->m_nChnCount++;
			pSclChGsIn = (CSclChGsIn*)pSclCtrlGsIn->CreateNewCh();
			//zhouhj 2023.9.19 ��Ϊ�ⲿͨ������
			pSclChGsIn->m_strName = pSclChBase->m_strName/*subInfo.ref*/;
			pSclChGsIn->m_strID = subInfo.sub_ref;
			pSclChGsIn->fcda_name = subInfo.sub_ref;
			pSclChGsIn->inPath = subInfo.ref;
			pSclChGsIn->outIndex = subInfo.index_Rec;
			pSclChGsIn->inIndex = nInIndex;
			pSclChGsIn->inDODesc = subInfo.desc;
			pSclChGsIn->fcda_type = ((CSclChGsOut*)pSclChBase)->fcda_type;
		}
	}

//	m_pSclStation->SaveStationFile();
}

CSclChBase* Global_FindSclCh(CSclCtrlBase **ppSclCtrlOut,CSclCtrls* pSclCtrls,const CString &strFcdaRef)
{
	CSclCtrlBase* pCurrCtrl = NULL;
	CSclChBase* pSclChOut = NULL;
	POS pos_ctrl = pSclCtrls->GetHeadPosition();

	while(pos_ctrl)
	{
		pCurrCtrl = (CSclCtrlBase*)pSclCtrls->GetNext(pos_ctrl);
		pSclChOut = (CSclChBase*)pCurrCtrl->FindByID(strFcdaRef);

		if (pSclChOut != NULL)
		{
			*ppSclCtrlOut = pCurrCtrl;
			return pSclChOut;
		}
	}

	return NULL;
}

CSclChBase* QSclFileRead::FindVirtualTerminalCh(CSclCtrlBase **ppSclCtrlOut,const CString strIedName,const CString strChRef,BOOL bSmvCtrl)
{
	CSclIed *pSclIED = NULL;
	CString strFcdaRef;
	strFcdaRef.Format(_T("%s%s"),strIedName.GetString(),strChRef.GetString());
	CSclChBase* pSclChOut = NULL;

	if (*ppSclCtrlOut != NULL)
	{
		pSclIED = (CSclIed*)(*ppSclCtrlOut)->GetAncestor(SCLIECCLASSID_IED);

		if ((pSclIED != NULL)&&(pSclIED->m_strID == strIedName))
		{
			pSclChOut = (CSclChBase*)(*ppSclCtrlOut)->FindByID(strFcdaRef);

			if (pSclChOut != NULL)
			{
				return pSclChOut;
			}
		}
	}

	pSclIED = (CSclIed*)m_pSclStation->FindByID(strIedName);

	if (pSclIED == NULL)
	{
		CString strTmp;
		strTmp = "����OutCtrlʧ��,δ���ҵ�IED(%s).";
		char *pzsLogMsg = NULL;
		int nOutLenth = 0;
		utf8_to_gbk_r((const unsigned char*)strTmp.GetString(),(int)String_Char_Count(strTmp),(unsigned char **)&pzsLogMsg,&nOutLenth);
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,pzsLogMsg,strIedName.GetString());
		delete pzsLogMsg;
		return NULL;
	}

	CSclCtrls* pSclCtrls = NULL;

	if (bSmvCtrl)
	{
		pSclCtrls = pSclIED->GetSmvOuts();
	} 
	else
	{
		pSclCtrls = pSclIED->GetGsOuts();
	}

	pSclChOut = Global_FindSclCh(ppSclCtrlOut,pSclCtrls,strFcdaRef);

	if (pSclChOut != NULL)
	{
		return pSclChOut;
	}

	long nLenth = strFcdaRef.ReverseFind('.');
    CString strTmp;

	if (nLenth>0)
	{
		strTmp = strFcdaRef.Left(nLenth);
		pSclChOut = Global_FindSclCh(ppSclCtrlOut,pSclCtrls,strTmp);

		if (pSclChOut != NULL)
		{
			return pSclChOut;
		}

		nLenth = strTmp.ReverseFind('.');

		if (nLenth>0)
		{
			CString strTmp2;
			strTmp2 = strTmp.Left(nLenth);
			pSclChOut = Global_FindSclCh(ppSclCtrlOut,pSclCtrls,strTmp2);

			if (pSclChOut != NULL)
			{
				return pSclChOut;
			}
		}
	}

	strTmp = ("����OutCtrlʧ��,δ���ҵ�IED(%s)���ڵ������(%s).");
	//#ifdef _PSX_QT_LINUX_
	char *pzsLogMsg = NULL;
	int nOutLenth = 0;
	utf8_to_gbk_r((const unsigned char*)strTmp.GetString(),(int)String_Char_Count(strTmp),(unsigned char **)&pzsLogMsg,&nOutLenth);
	CLogPrint::LogFormatString(XLOGLEVEL_ERROR,pzsLogMsg,strIedName.GetString(),strFcdaRef.GetString());
	delete pzsLogMsg;
// #else
// 	CLogPrint::LogFormatString(XLOGLEVEL_ERROR,strTmp.GetString(),strIedName.GetString(),strFcdaRef.GetString());
// #endif
	return NULL;

}





