//#include "global.h"
#include "QSclFileRead.h"
#include <QProgressDialog>
#include "../../../Module/API/StringConvert/String_Utf8_To_Gbk.h"

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


#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

	QSclFileRead::QSclFileRead() 
{
	m_pSclStation = NULL;
	m_pProgressInterface = NULL;
}

QSclFileRead::~QSclFileRead()
{
	for (int iIED = 0; iIED < m_oSclIedList.size(); iIED++)
	{
		SCL_IED_INFO_QT &ied = m_oSclIedList[iIED];
		//GSE
		for (int iGSE = 0; iGSE < ied.GSEList.size(); iGSE++)
		{
			SCL_GSE_INFO_QT &gse = ied.GSEList[iGSE];
			for (int iPub = 0; iPub < gse.pubList.size(); iPub++)
			{
				SCL_PUB_REC_INFO_QT &pubRec = gse.pubList[iPub];
				pubRec.recPubList.clear();
			}
			gse.pubList.clear();
		}
		ied.GSEList.clear();
		//SMV
		for (int iSMV = 0; iSMV < ied.SMVList.size(); iSMV++)
		{
			SCL_SMV_INFO_QT &smv = ied.SMVList[iSMV];
			for (int iPub = 0; iPub < smv.pubList.size(); iPub++)
			{
				SCL_PUB_REC_INFO_QT &pubRec = smv.pubList[iPub];
				pubRec.recPubList.clear();
			}
			smv.pubList.clear();
		}
		ied.SMVList.clear();
		//sub
		ied.GOSubList.clear();
		ied.SVSubList.clear();
	}
}

BOOL QSclFileRead::ParseSCL(const CString &strSclFilePath)
{
	QTime oTime;//用于计算总用时
	oTime.start();

	if (m_pProgressInterface != NULL)
	{
		m_pProgressInterface->SetTitle("ParseSCL");
		m_pProgressInterface->ShowMsg("Loading...");
		m_pProgressInterface->InitThreadProgress(100,1);
		m_pProgressInterface->StepIt();
	}
	//init
	m_oSclIedList.clear();
	m_oLNodeType_Hash.clear();
	m_oDOType_Hash.clear();
	m_oDAType_Hash.clear();
	m_oIedNameHash.clear();
	m_nSclAnalyzeErrorNum=0;

	//装载SCD文件
	xml_document oPugiDoc;
	QString strTmpPath = strSclFilePath;
	const QByteArray baTmp = strTmpPath.toLocal8Bit();
	const char *pzfFilePath = baTmp.data();

	if (!oPugiDoc.load_file(pzfFilePath,pugi::parse_default,pugi::encoding_utf8))
	{
		//        Log4Qt::Logger *log = Log4Qt::Logger::logger("CMXL");
		//        log->error(tr("Open SCD file failed !")+strSclFilePath);
		//        QString strMsg = tr("Open SCD file failed !");
		//        strMsg += strSclFilePath;
		//        QMessageBox::information(this,tr("error"),strMsg);
		m_nSclAnalyzeErrorNum++;
		return FALSE;
	}

	if (m_pProgressInterface != NULL)
	{
		m_pProgressInterface->StepIt();
		m_pProgressInterface->ShowMsg("Parsing...");
	}

	//创建数据模板哈希表
	xml_node oRootNodePugi = oPugiDoc.root();
	CreateDataTypeTemplatesHash(oRootNodePugi);

	QTextCodec *codec = QTextCodec::codecForName("utf-8");
	QTextCodec::setCodecForLocale(codec);
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);
	//设置进度条

	//获取IED列表
	xpath_node_set IED_list=oPugiDoc.select_nodes(L"/SCL/IED");
	int index=0;

	for(xpath_node_set::const_iterator IED_it=IED_list.begin();IED_it!=IED_list.end();IED_it++)
	{
		xpath_node IED_xpath=*IED_it;
		SCL_IED_INFO_QT iedInfo;
		iedInfo.name = QString::fromWCharArray(IED_xpath.node().attribute(L"name").value());
		iedInfo.type= QString::fromWCharArray(IED_xpath.node().attribute(L"type").value());
		iedInfo.manufacturer= QString::fromWCharArray(IED_xpath.node().attribute(L"manufacturer").value());
		iedInfo.configVersion= QString::fromWCharArray(IED_xpath.node().attribute(L"configVersion").value());
		iedInfo.desc= QString::fromWCharArray(IED_xpath.node().attribute(L"desc").value());

		m_oSclIedList<<iedInfo;

		//建立IED名称和IEDList的哈希表
		m_oIedNameHash.insert(iedInfo.name,index);
		index++;
	}

	if (m_pProgressInterface != NULL)
	{
		m_pProgressInterface->StepIt();
	}

	//获取GSE和SMV
	int progress_counter=1;
	xpath_node_set ConnectedAP_list=oPugiDoc.select_nodes(L"/SCL/Communication/SubNetwork/ConnectedAP");

	if (m_pProgressInterface != NULL)
	{
		m_pProgressInterface->InitThreadProgress(ConnectedAP_list.size()*10,10);
	}

	for(xpath_node_set::const_iterator ConnectedAP_it=ConnectedAP_list.begin();
		ConnectedAP_it!=ConnectedAP_list.end();ConnectedAP_it++)
	{
		xml_node ConnectedAP_node=ConnectedAP_it->node();
		QString iedName=QString::fromWCharArray(ConnectedAP_node.attribute(L"iedName").value());

		//遍历子节点
		for(xml_node child_node=ConnectedAP_node.first_child();child_node;
			child_node=child_node.next_sibling())
		{
			QString node_name=QString::fromWCharArray(child_node.name());
			//获取GSE的信息
			if(node_name=="GSE")
			{
				SCL_IED_INFO_QT *iedInfo=&m_oSclIedList[m_oIedNameHash.value(iedName)];
				SCL_GSE_INFO_QT gseInfo;

				gseInfo.apName = QString::fromWCharArray(ConnectedAP_node.attribute(L"apName").value());
				gseInfo.cbName = QString::fromWCharArray(child_node.attribute(L"cbName").value());
				gseInfo.ldInst = QString::fromWCharArray(child_node.attribute(L"ldInst").value());

				//Address
				xpath_node_set Address_list=child_node.select_nodes(L"./Address/P");
				for(xpath_node_set::const_iterator Address_it=Address_list.begin();
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
				xpath_node MinTime_node=child_node.select_node(L"./MinTime");
				gseInfo.MinTime=MinTime_node.node().text().as_int();

				xpath_node MaxTime_node=child_node.select_node(L"./MaxTime");
				gseInfo.MaxTime=MaxTime_node.node().text().as_int();

				//防止控制块重复
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
			//获取SMV的信息
			if(node_name=="SMV")
			{
				SCL_IED_INFO_QT *iedInfo=&m_oSclIedList[m_oIedNameHash.value(iedName)];

				SCL_SMV_INFO_QT smvInfo;
				smvInfo.apName = QString::fromWCharArray(ConnectedAP_node.attribute(L"apName").value());
				smvInfo.cbName = QString::fromWCharArray(child_node.attribute(L"cbName").value());
				smvInfo.ldInst = QString::fromWCharArray(child_node.attribute(L"ldInst").value());

				//Address
				xpath_node_set Address_list=child_node.select_nodes(L"./Address/P");
				for(xpath_node_set::const_iterator Address_it=Address_list.begin();
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

				//防止控制块重复
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

		if (m_pProgressInterface != NULL)
		{
			m_pProgressInterface->StepIt();
		}

		progress_counter++;
	}

	QStdWString wstrTmp;

	//遍历IED
	for(int index_IED=0;index_IED<m_oSclIedList.size();index_IED++)
	{
		SCL_IED_INFO_QT *iedInfo=&m_oSclIedList[index_IED];

		//临时存放当前IED的GSE。移除上一步找到的，添加下面的GSEList
		QList<SCL_GSE_INFO_QT> tempGSEList;
		QList<SCL_SMV_INFO_QT> tempSMVList;

		//查找IED中LD节点
		strTmpPath="/SCL/IED[@name='"+iedInfo->name+"']/AccessPoint/Server/LDevice";
		wstrTmp = strTmpPath.toStdWString();
		const wchar_t * LDChar = wstrTmp.c_str();

		//         const QByteArray LDByte=strTmpPath.toLocal8Bit();
		//         const char *LDChar=LDByte.data();
		xpath_node_set LD_list=oPugiDoc.select_nodes(LDChar);
		for(xpath_node_set::const_iterator LD_it=LD_list.begin();
			LD_it!=LD_list.end();LD_it++)
		{
			xml_node LD_node = LD_it->node();
			QString LD_inst = QString::fromWCharArray(LD_node.attribute(L"inst").value());
			QString apDesc = QString::fromWCharArray(LD_node.parent().parent().attribute(L"desc").value());
			QString apName = QString::fromWCharArray(LD_node.parent().parent().attribute(L"name").value());

			//建立该LD子节点的LNstr哈希表，可以用于以下三种情况
			DataTypeHash LN_hash;

			//查找GSEControl
			for(xml_node GSEControl_node=LD_node.child(L"LN0").child(L"GSEControl");
				GSEControl_node;GSEControl_node=GSEControl_node.next_sibling(L"GSEControl"))
			{
				//建立一个LN节点和LN_str的hash
				if(LN_hash.size()==0)
					CreateLNHash(LD_node,&LN_hash);

				//获取这个GSEControl的信息
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

				//进入DataSet节点
				strTmpPath="./DataSet[@name='";
				strTmpPath += QString::fromWCharArray(GSEControl_node.attribute(L"datSet").value());
				strTmpPath+="']";

				wstrTmp = strTmpPath.toStdWString();
				const wchar_t * DataSetChar = wstrTmp.c_str();
				//                 const QByteArray DataSetText= strTmpPath.toLocal8Bit();
				//                 const char *DataSetChar = DataSetText.data();

				xpath_node DataSet_node = LD_node.child(L"LN0").select_node(DataSetChar);
				gseInfo->DataSetDesc = QString::fromWCharArray(DataSet_node.node().attribute(L"desc").value());

				//进入FCDA节点
				xpath_node_set FCDA_list=DataSet_node.node().select_nodes(L"./FCDA");
				gseInfo->recNum=FCDA_list.size();

				for(xpath_node_set::const_iterator FCDA_it=FCDA_list.begin();FCDA_it!=FCDA_list.end();FCDA_it++)
				{
					//遍历发布数据集
					xml_node FCDA_node=FCDA_it->node();
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
					
					//查找注释
					QString LNstr=QString("%1%2%3").arg(QString::fromWCharArray(FCDA_node.attribute(L"prefix").value()),
						QString::fromWCharArray(FCDA_node.attribute(L"lnClass").value()),
						QString::fromWCharArray(FCDA_node.attribute(L"lnInst").value())
						);
					xml_node LN_find=LN_hash.value(LNstr);
					QString lnType = QString::fromWCharArray(LN_find.attribute(L"lnType").value());

					strTmpPath = QString("./DOI[@name='%1']").arg(QString::fromWCharArray(FCDA_node.attribute(L"doName").value()));

					wstrTmp = strTmpPath.toStdWString();
					const wchar_t * DOIChar = wstrTmp.c_str();

					//                     const QByteArray DOIText= strTmpPath.toLocal8Bit();
					//                     const char *DOIChar = DOIText.data();

					xpath_node DOI_xml=LN_find.select_node(DOIChar);
					pubRecInfo.desc = QString::fromWCharArray(DOI_xml.node().attribute(L"desc").value());
					if(pubRecInfo.desc=="")
					{
						QString doName = QString::fromWCharArray(FCDA_node.attribute(L"doName").value());
						QStringList  doName_Split=doName.split('.');

						DataTypeHash DO_hash=m_oLNodeType_Hash.value(lnType);
						xml_node DO_node=DO_hash.value(doName_Split[0]);
						pubRecInfo.desc = QString::fromWCharArray(DO_node.attribute(L"desc").value());
					}
					if(pubRecInfo.desc=="")
						pubRecInfo.desc = QString::fromWCharArray(LN_find.attribute(L"desc").value());

					//查找数据类型
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
						//获取DOType，考虑DO节点有SDI的情况
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

				//查找该GSEControl有没有发布
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

			//查找SampledValueControl
			for(xml_node SampledValueControl_node = LD_node.child(L"LN0").child(L"SampledValueControl");
				SampledValueControl_node;SampledValueControl_node = SampledValueControl_node.next_sibling(L"SampledValueControl"))
			{
				//建立一个LN节点和LN_str的hash
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

				//进入节点SmvOpts
				smvInfo->refreshTime=SampledValueControl_node.child(L"SmvOpts").attribute(L"refreshTime").as_bool();
				smvInfo->sampleSynchronized=SampledValueControl_node.child(L"SmvOpts").attribute(L"sampleSynchronized").as_bool();
				smvInfo->sampleRate=SampledValueControl_node.child(L"SmvOpts").attribute(L"sampleRate").as_bool();
				smvInfo->security=SampledValueControl_node.child(L"SmvOpts").attribute(L"security").as_bool();
				smvInfo->dataRef=SampledValueControl_node.child(L"SmvOpts").attribute(L"dataRef").as_bool();

				//进入DataSet节点
				strTmpPath = QString("./DataSet[@name='%1']").arg(QString::fromWCharArray(SampledValueControl_node.attribute(L"datSet").value()));

				wstrTmp = strTmpPath.toStdWString();
				const wchar_t * DataSetChar = wstrTmp.c_str();
				//                 const QByteArray DataSetText= strTmpPath.toLocal8Bit();
				//                 const char *DataSetChar = DataSetText.data();

				xpath_node DataSet_node=LD_node.child(L"LN0").select_node(DataSetChar);
				smvInfo->DataSetDesc = QString::fromWCharArray(DataSet_node.node().attribute(L"desc").value());

				//进入FCDA节点
				xpath_node_set FCDA_list=DataSet_node.node().select_nodes(L"./FCDA");
				smvInfo->recNum=FCDA_list.size();

				for(xpath_node_set::const_iterator FCDA_it=FCDA_list.begin();FCDA_it!=FCDA_list.end();FCDA_it++)
				{
					//遍历发布数据集
					xml_node FCDA_node=FCDA_it->node();
					//去除daName为q的记录
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
					
					//查找注释
					QString LNstr=QString("%1%2%3").arg(QString::fromWCharArray(FCDA_node.attribute(L"prefix").value()),
						QString::fromWCharArray(FCDA_node.attribute(L"lnClass").value()),
						QString::fromWCharArray(FCDA_node.attribute(L"lnInst").value())
						);
					xml_node LN_find=LN_hash.value(LNstr);

					strTmpPath = QString("./DOI[@name='%1']").arg(QString::fromWCharArray(FCDA_node.attribute(L"doName").value()));

					wstrTmp = strTmpPath.toStdWString();
					const wchar_t * DOIChar = wstrTmp.c_str();
					//                     const QByteArray DOIText= strTmpPath.toLocal8Bit();
					//                     const char *DOIChar = DOIText.data();

					xpath_node DOI_xml=LN_find.select_node(DOIChar);

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

				//查找该GSEControl有没有发布
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

			//遍历Inputs节点，获取输入信息
			xml_node Inputs_node=LD_node.child(L"LN0").child(L"Inputs");
			for(xml_node ExtRef_node=Inputs_node.child(L"ExtRef");ExtRef_node;
				ExtRef_node=ExtRef_node.next_sibling(L"ExtRef"))
			{
				//建立一个LN节点和LN_str的hash
				if(LN_hash.size()==0)
					CreateLNHash(LD_node,&LN_hash);

				xml_node AccessPoint_node=LD_node.parent().parent();
				QString AccessPoint_name = QString::fromWCharArray(AccessPoint_node.attribute(L"name").value());
				//获取GOOSE-Inputs
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

					xml_node LN_find=LN_hash.value(LNstr);

					strTmpPath = "./DOI[@name='"+DO_name+"']";

					wstrTmp = strTmpPath.toStdWString();
					const wchar_t * DOIChar = wstrTmp.c_str();
					//                     const QByteArray DOIText= strTmpPath.toLocal8Bit();
					//                     const char *DOIChar = DOIText.data();

					xpath_node DOI_xml=LN_find.select_node(DOIChar);
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

					xml_node LN_find=LN_hash.value(LNstr);

					strTmpPath="./DOI[@name='"+DO_name+"']";

					wstrTmp = strTmpPath.toStdWString();
					const wchar_t * DOIChar = wstrTmp.c_str();
					//                     const QByteArray DOIText= strTmpPath.toLocal8Bit();
					//                     const char *DOIChar = DOIText.data();

					xpath_node DOI_xml=LN_find.select_node(DOIChar);
					subRecInfo.desc = QString::fromWCharArray(DOI_xml.node().attribute(L"desc").value());
					if(subRecInfo.desc=="")
						subRecInfo.desc = QString::fromWCharArray(LN_find.attribute(L"desc").value());

					iedInfo->GOSubList.append(subRecInfo);
				}
			}
		}

		//清楚以前的，添加新的
		iedInfo->GSEList.clear();
		iedInfo->GSEList.append(tempGSEList);

		iedInfo->SMVList.clear();
		iedInfo->SMVList.append(tempSMVList);

//		oProgressDlg.setValue(30+65*index_IED/m_oSclIedList.size());
	}

	//匹配订阅端子
	for(int index_IED=0;index_IED<m_oSclIedList.size();index_IED++)
	{
		//遍历每一个IED的订阅虚端子
		SCL_IED_INFO_QT *iedInfo=&m_oSclIedList[index_IED];
		//匹配GOOSE订阅虚端子
		for(int index_subRec=0;index_subRec<iedInfo->GOSubList.size();index_subRec++)
		{
			//匹配完成标记
			bool flag=false;
			SCL_SUB_REC_INFO_QT *subRecInfo=&iedInfo->GOSubList[index_subRec];
			//找到发布虚端子的IED
			int index_pubIED=m_oIedNameHash.value(subRecInfo->sub_IED_name);
			SCL_IED_INFO_QT *pubIedInfo=&m_oSclIedList[index_pubIED];
			//找到GSE
			for(int index_GSE=0;index_GSE<pubIedInfo->GSEList.size();index_GSE++)
			{
				SCL_GSE_INFO_QT *gseInfo=&pubIedInfo->GSEList[index_GSE];
				//匹配GSE的ldInst
				if(subRecInfo->sub_ldInst==gseInfo->ldInst)
				{
					//匹配发布虚端子与订阅虚端子
					for(int index_pubRec=0;index_pubRec<gseInfo->pubList.size();index_pubRec++)
					{
						SCL_PUB_REC_INFO_QT *pubRecInfo=&gseInfo->pubList[index_pubRec];
						if(subRecInfo->sub_ref==pubRecInfo->ref)
						{
							//更新信息
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
				//                QString Msg=QString(tr("定义的虚端子输入，没有找到。IED name is:%1.AccessPoint is GOOSE.reference is:%2")).
				//                        arg(iedInfo->name).arg(subRecInfo->ref);
				//                log->error(Msg);
				m_nSclAnalyzeErrorNum++;
			}
		}

		//匹配SMV订阅虚端子
		for(int index_subRec=0;index_subRec<iedInfo->SVSubList.size();index_subRec++)
		{
			//匹配完成标记
			bool flag=false;
			SCL_SUB_REC_INFO_QT *subRecInfo=&iedInfo->SVSubList[index_subRec];
			//找到发布虚端子的IED
			int index_pubIED=m_oIedNameHash.value(subRecInfo->sub_IED_name);
			SCL_IED_INFO_QT *pubIedInfo=&m_oSclIedList[index_pubIED];
			//遍历发布IED的SMV，找到匹配的IED
			for(int index_SMV=0;index_SMV<pubIedInfo->SMVList.size();index_SMV++)
			{
				SCL_SMV_INFO_QT *smvInfo=&pubIedInfo->SMVList[index_SMV];
				//匹配GSE的ldInst
				if(subRecInfo->sub_ldInst==smvInfo->ldInst)
				{
					//遍历SMV的发布数据集，匹配发布虚端子与订阅虚端子
					for(int index_pubRec=0;index_pubRec<smvInfo->pubList.size();index_pubRec++)
					{
						SCL_PUB_REC_INFO_QT *pubRecInfo=&smvInfo->pubList[index_pubRec];
						if(subRecInfo->sub_ref==pubRecInfo->ref)
						{
							//更新信息
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
				//                QString Msg=QString(tr("定义的虚端子输入，没有找到。IED name is:%1.AccessPoint is SMV.reference is:%2")).
				//                        arg(iedInfo->name).arg(subRecInfo->ref);
				//                log->error(Msg);
				m_nSclAnalyzeErrorNum++;
			}
		}
	}


	//匹配虚端子,防止G访问点建模SMV输入，或者M访问点，建模GOOSE输入
	for(int index_IED=0;index_IED<m_oSclIedList.size();index_IED++)
	{
		//在SMV中找到的goPub记录
		QList<int> goSub_SMV_list;
		//遍历每一个IED的订阅虚端子
		SCL_IED_INFO_QT *iedInfo=&m_oSclIedList[index_IED];
		//匹配GOOSE订阅虚端子
		for(int index_subRec=0;index_subRec<iedInfo->GOSubList.size();index_subRec++)
		{
			//匹配完成标记
			bool flag=false;
			SCL_SUB_REC_INFO_QT *subRecInfo=&iedInfo->GOSubList[index_subRec];
			//跳过已经找到的记录
			if(subRecInfo->index_IED!=-1)   continue;
			//判断是否在SMV发布中
			int index_pubIED=m_oIedNameHash.value(subRecInfo->sub_IED_name);
			SCL_IED_INFO_QT *pubIedInfo=&m_oSclIedList[index_pubIED];
			//找到SMV
			for(int index_SMV=0;index_SMV<pubIedInfo->SMVList.size();index_SMV++)
			{
				SCL_SMV_INFO_QT *gseInfo=&pubIedInfo->SMVList[index_SMV];
				//匹配SMV的ldInst
				if(subRecInfo->sub_ldInst==gseInfo->ldInst)
				{
					//匹配发布虚端子与订阅虚端子
					for(int index_pubRec=0;index_pubRec<gseInfo->pubList.size();index_pubRec++)
					{
						SCL_PUB_REC_INFO_QT *pubRecInfo=&gseInfo->pubList[index_pubRec];
						if(subRecInfo->sub_ref==pubRecInfo->ref)
						{
							//更新订阅IED的发布IED的信息
							subRecInfo->index_IED=index_pubIED;
							subRecInfo->index_GSE_SMV=index_SMV;
							subRecInfo->index_Rec=index_pubRec;

							//更新发布的方IED的信息
							SCL_CONNECT_PUB_INFO_QT connectPubInfo;
							connectPubInfo.index_IED=index_IED;
							connectPubInfo.index_Rec=index_subRec;
							pubRecInfo->recPubList.append(connectPubInfo);

							//添加
							goSub_SMV_list.append(index_subRec);

							flag=true;

							break;
						}
					}
				}
				if(flag) break;
			}
		}

		//将这些记录添加到SMVSub中
		for(int index=0;index<goSub_SMV_list.size();index++)
		{
			iedInfo->SVSubList.append(iedInfo->GOSubList.at(goSub_SMV_list.at(index)));
		}

		//将这些记录移出GSESub中
		for(int index=0;index<goSub_SMV_list.size();index++)
		{
			iedInfo->GOSubList.removeAt(goSub_SMV_list.at(index)-index);
		}

		//在GSV中找到的smvPub记录
		QList<int> smvSub_GSE_list;
		//匹配GOOSE订阅虚端子
		for(int index_subRec=0;index_subRec<iedInfo->SVSubList.size();index_subRec++)
		{
			//匹配完成标记
			bool flag=false;
			SCL_SUB_REC_INFO_QT *subRecInfo=&iedInfo->SVSubList[index_subRec];
			//跳过已经找到的记录
			if(subRecInfo->index_IED!=-1)   continue;
			//判断是否在SMV发布中
			int index_pubIED=m_oIedNameHash.value(subRecInfo->sub_IED_name);
			SCL_IED_INFO_QT *pubIedInfo=&m_oSclIedList[index_pubIED];
			//找到SMV
			for(int index_GSE=0;index_GSE<pubIedInfo->GSEList.size();index_GSE++)
			{
				SCL_GSE_INFO_QT *gseInfo=&pubIedInfo->GSEList[index_GSE];
				//匹配GSE的ldInst
				if(subRecInfo->sub_ldInst==gseInfo->ldInst)
				{
					//匹配发布虚端子与订阅虚端子
					for(int index_pubRec=0;index_pubRec<gseInfo->pubList.size();index_pubRec++)
					{
						SCL_PUB_REC_INFO_QT *pubRecInfo=&gseInfo->pubList[index_pubRec];
						if(subRecInfo->sub_ref==pubRecInfo->ref)
						{
							//更新订阅IED的发布IED的信息
							subRecInfo->index_IED=index_pubIED;
							subRecInfo->index_GSE_SMV=index_GSE;
							subRecInfo->index_Rec=index_pubRec;

							//更新发布的方IED的信息
							SCL_CONNECT_PUB_INFO_QT connectPubInfo;
							connectPubInfo.index_IED=index_IED;
							connectPubInfo.index_Rec=index_subRec;
							pubRecInfo->recPubList.append(connectPubInfo);

							//添加
							smvSub_GSE_list.append(index_subRec);

							flag=true;

							break;
						}
					}
				}
				if(flag) break;
			}
		}

		//将这些记录添加到GSESub中
		for(int index=0;index<smvSub_GSE_list.size();index++)
		{
			iedInfo->GOSubList.append(iedInfo->SVSubList.at(smvSub_GSE_list.at(index)));
		}

		//将这些记录移出SMVSub中
		for(int index=0;index<smvSub_GSE_list.size();index++)
		{
			iedInfo->SVSubList.removeAt(smvSub_GSE_list.at(index)-index);
		}
	}

//	oProgressDlg.setValue(100);
	qDebug()<<strSclFilePath<<":"<<oTime.elapsed()/1000.0<<"s";
	//QString Msg=QString(tr("错误个数：%1\n错误详情，请查看LOG文件")).arg(errMsg_counter);
	//QMessageBox::information(this,tr("警告"),Msg);

	codec = QTextCodec::codecForName("GBK");
	QTextCodec::setCodecForLocale(codec);
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);

	oPugiDoc.reset();
	return TRUE;
}

BOOL QSclFileRead::ReadSclFile(const CString &strSclFilePath, CSclStation *pSclStation)
{   
	m_pSclStation = pSclStation;

	if (m_pSclStation->GetScdFile() == strSclFilePath)
	{
		return TRUE;
	}

	m_pSclStation->DeleteAll();
	m_pSclStation->SetScdFile(strSclFilePath);
	m_pSclStation->m_strName = ParseFileName(strSclFilePath);
	m_pSclStation->m_strID = m_pSclStation->m_strName;

	if (!ParseSCL(strSclFilePath))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("SCL文件(%s)解析失败."),strSclFilePath.GetString());
		return FALSE;
	}

	ReadSclStation();
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
        xml_node DO_node=DO_hash.value(name);
        strFC = QString::fromWCharArray(DO_node.attribute(L"type").value());
        break;
    }
    case SDOType:
    {
        xml_node DOType_xml=m_oDOType_Hash.value(id);
        for(xml_node SDO_xml=DOType_xml.child(L"SDO");SDO_xml;SDO_xml=SDO_xml.next_sibling(L"SDO"))
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
    //以下两种情况如果找到数据类型，直接返回数据类型
    case  DAType:
    {
        xml_node DOType_node=m_oDOType_Hash.value(id);

        //FCDA没有定义DA的情况
        if(name=="")
        {
            for(xml_node DA_node=DOType_node.child(L"DA");DA_node;DA_node=DA_node.next_sibling(L"DA"))
            {
                //获取FC相同的节点
                if(QString("%1").arg(QString::fromWCharArray(DA_node.attribute(L"fc").value()))==fc)
                {
                    //如果DA节点还有SDI节点
                    if(QString("%1").arg(QString::fromWCharArray(DA_node.attribute(L"bType").value()))=="Struct")
                    {
                        xml_node DAType_node=this->m_oDAType_Hash.value(QString("%1").arg(QString::fromWCharArray(DA_node.attribute(L"type").value())));
                        //获取BDA节点的信息
                        for(xml_node BDA_node=DAType_node.child(L"BDA");BDA_node;BDA_node=BDA_node.next_sibling(L"BDA"))
                        {
                            //如果BDA节点还有SDI节点
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
            xml_node DA_xml;
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
        //如果传过来的name为空，则说明全部获取
        if(name=="")
        {
            xml_node DAType_node=this->m_oDAType_Hash.value(id);
            //获取BDA节点的信息
            for(xml_node BDA_node=DAType_node.child(L"BDA");BDA_node;BDA_node=BDA_node.next_sibling(L"BDA"))
            {
                //如果BDA节点还有SDI节点
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
            xml_node DAType_xml=m_oDAType_Hash.value(id);
            for(xml_node BDA_xml=DAType_xml.child(L"BDA");BDA_xml;BDA_xml=BDA_xml.next_sibling(L"BDA"))
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

void QSclFileRead::CreateLNHash(const xml_node LD_node, DataTypeHash *pLN_hash)
{
    for(xml_node LN_node=LD_node.first_child();LN_node;LN_node=LN_node.next_sibling())
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

//创建数据模板哈希表，用于查找数据类型
void QSclFileRead::CreateDataTypeTemplatesHash(xml_node oRootNodePugi)
{
    xml_node tools=oRootNodePugi.child(L"SCL").child(L"DataTypeTemplates");

    for(xml_node tool=tools.first_child();tool;tool=tool.next_sibling())
    {
        QString node_name = QString::fromWCharArray(tool.name());
        if(node_name=="LNodeType")
        {
            QString id = QString::fromWCharArray(tool.attribute(L"id").value());

            //将DO节点建立哈希表
            DataTypeHash DO_Hash;
            for(xml_node DO_xml=tool.first_child();DO_xml;DO_xml=DO_xml.next_sibling())
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
    xml_document doc;
    //add declaration
    xml_node decl=doc.prepend_child(pugi::node_declaration);
    decl.append_attribute(L"version") = L"1.0";
    decl.append_attribute(L"encoding") = L"UTF-8";

    // add root
    xml_node root = doc.append_child(L"PSCD");

    //add child node--goose pub
    foreach(SCL_IED_INFO_QT iedInfo,m_oSclIedList)
    {
        std::string str;
        xml_node IED_node = root.append_child(L"IED");
        QStdWString wstrTmp =  iedInfo.name.toStdWString();
        const wchar_t *ch1 = wstrTmp.c_str();
        xml_attribute oXMlAttr =  IED_node.append_attribute(L"name");
        oXMlAttr.set_value(ch1);
		wstrTmp = iedInfo.type.toStdWString();
		const wchar_t *ch2 = wstrTmp.c_str(); 

//        const char *ch2=str.c_str();
        IED_node.append_attribute(L"type")=ch2;

//        str=iedInfo.desc.toStdString();
		wstrTmp = iedInfo.desc.toStdWString();
        const wchar_t *ch3=wstrTmp.c_str(); 
        IED_node.append_attribute(L"desc")=ch3;

//        str=iedInfo.manufacturer.toStdString();
		wstrTmp = iedInfo.manufacturer.toStdWString();
        const wchar_t *ch4=wstrTmp.c_str(); 
        IED_node.append_attribute(L"manufacturer")=ch4;

//        str=iedInfo.configVersion.toStdString();
		wstrTmp = iedInfo.configVersion.toStdWString();
        const wchar_t *ch5=wstrTmp.c_str(); 
        IED_node.append_attribute(L"configVersion")=ch5;

        //GOOSE pub
        foreach(SCL_GSE_INFO_QT gseInfo,iedInfo.GSEList)
        {
            xml_node GSE_node=IED_node.append_child(L"GSE");

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
                xml_node PUB_node=GSE_node.append_child(L"GOPUB");

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
                    xml_node CON_node=PUB_node.append_child(L"Outputs");

                    CON_node.append_attribute(L"index_IED")=conInfo.index_IED;
                    CON_node.append_attribute(L"index_Rec")=conInfo.index_Rec;
                }
            }
        }

        //SMV pub
        foreach(SCL_SMV_INFO_QT gseInfo,iedInfo.SMVList)
        {
            xml_node GSE_node=IED_node.append_child(L"SMV");

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
                xml_node PUB_node=GSE_node.append_child(L"GOPUB");

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
                    xml_node CON_node=PUB_node.append_child(L"Outputs");

                    CON_node.append_attribute(L"index_IED")=conInfo.index_IED;
                    CON_node.append_attribute(L"index_Rec")=conInfo.index_Rec;
                }
            }
        }

        //goose sub
        foreach(SCL_SUB_REC_INFO_QT subInfo,iedInfo.GOSubList)
        {
            xml_node SUB_node=IED_node.append_child(L"GOSUB");

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
        foreach(SCL_SUB_REC_INFO_QT subInfo,iedInfo.SVSubList)
        {
            xml_node SUB_node=IED_node.append_child(L"SMVSUB");

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
        QMessageBox::information(NULL,QObject::tr("error"),QObject::tr("Output file failed !"));
        return FALSE;
    }

    return TRUE;
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
		m_pProgressInterface->SetTitle("ReadSclStation");
		m_pProgressInterface->ShowMsg("Loading...");
		m_pProgressInterface->InitThreadProgress(m_oSclIedList.count(),1);
		m_pProgressInterface->StepIt();
	}

// 	QProgressDialog oProgressDlg(m_pParentWidget);//用于显示解析进度
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

	foreach(SCL_IED_INFO_QT oCurIedInfo,m_oSclIedList)
	{
		nCurrIndex++;
//		oProgressDlg.setValue(nCurrIndex);
		pNewIed = new CSclIed();
		m_pSclStation->AddNewChild(pNewIed);
		pNewIed->m_strID = oCurIedInfo.name;
		pNewIed->m_strModel = oCurIedInfo.type;
		pNewIed->m_strManufacturer = oCurIedInfo.manufacturer;

		if (m_pProgressInterface != NULL)
		{
			strMsgString = QString(QObject::tr("%1/%2(%3).")).arg(nCurrIndex).arg(m_oSclIedList.count()).arg(pNewIed->m_strID);
			m_pProgressInterface->ShowMsg(strMsgString);
			m_pProgressInterface->StepIt();
		}

		 if (!oCurIedInfo.desc.isEmpty())
		 {
			 pNewIed->m_strName = oCurIedInfo.desc;
		 }
		 else
		 {
			 pNewIed->m_strName = pNewIed->m_strID;
		 }

		 pCurSmvOuts = pNewIed->GetSmvOuts();
		 pCurGsOuts = pNewIed->GetGsOuts();

		 //SMV 输出
		 foreach(SCL_SMV_INFO_QT oSmvInfo,oCurIedInfo.SMVList)
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
 				 pSclChBase->m_strID = oCurIedInfo.name + pubInfo.ref;
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

		 //GOOSE 输出
 		 foreach(SCL_GSE_INFO_QT gseInfo,oCurIedInfo.GSEList)
 		 {
 			 pNewSclCtrlGsOut = new CSclCtrlGsOut();
 			 pCurGsOuts->AddNewChild(pNewSclCtrlGsOut);
 
 			 pNewSclCtrlGsOut->apName = gseInfo.apName;
  			 pNewSclCtrlGsOut->m_strID = /*gseInfo.goID*/gseInfo.cbName;//与IEC61850Config保持一致  在FindGooseOutput函数中需要用到此值不能改为其它
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
				 pSclChGs->m_strID = oCurIedInfo.name + pubInfo.ref;
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

	foreach(SCL_IED_INFO_QT oCurIedInfo,m_oSclIedList)
	{
		pNewIed = (CSclIed*)m_pSclStation->FindByID(oCurIedInfo.name);
		ASSERT(pNewIed);
		pCurSmvIns = pNewIed->GetSmvIns();
		pCurGsIns = pNewIed->GetGsIns();
		nInIndex = 0;

		nCurrIndex++;

		if (m_pProgressInterface != NULL)
		{
			strMsgString = QString(QObject::tr("%1/%2(%3).")).arg(nCurrIndex).arg(m_oSclIedList.count()).arg(pNewIed->m_strID);
			m_pProgressInterface->ShowMsg(strMsgString);
			m_pProgressInterface->StepIt();
		}

		//SMV 接收
		foreach(SCL_SUB_REC_INFO_QT subInfo,oCurIedInfo.SVSubList)
		{
			pSclChBase = FindVirtualTerminalCh((CSclCtrlBase **)&pSclCtrlSmvOut,subInfo.sub_IED_name,subInfo.sub_ref,TRUE);
			nInIndex++;

			if (pSclChBase == NULL)
			{
				continue;
			}

			pSclCtrlSmvIn = (CSclCtrlSmvIn*)pCurSmvIns->FindByID(pSclCtrlSmvOut->m_strSVID);

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
//				pSclCtrlSmvIn->ldName_own = subInfo.sub_ldInst;
			}

			pSclCtrlSmvIn->m_nChnCount++;
			pSclChSmvIn = (CSclChSmvIn*)pSclCtrlSmvIn->CreateNewCh();
			pSclChSmvIn->m_strName = subInfo.ref;
			pSclChSmvIn->m_strID = subInfo.sub_ref;
			pSclChSmvIn->fcda_name = subInfo.sub_ref;
			pSclChSmvIn->inPath = subInfo.ref;
			pSclChSmvIn->outIndex = subInfo.index_Rec;
			pSclChSmvIn->inIndex = nInIndex;
			pSclChSmvIn->inDODesc = subInfo.desc;
		}

		nInIndex = 0;

		//GOOSE 接收
		foreach(SCL_SUB_REC_INFO_QT subInfo,oCurIedInfo.GOSubList)
		{
			pSclChBase = FindVirtualTerminalCh((CSclCtrlBase **)&pSclCtrlGsOut,subInfo.sub_IED_name,subInfo.sub_ref,FALSE);
			nInIndex++;

			if (pSclChBase == NULL)
			{
				continue;
			}

			pSclCtrlGsIn = (CSclCtrlGsIn*)pCurGsIns->FindByID(pSclCtrlGsOut->m_strID);

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
				pSclCtrlGsIn->apName_own = pSclCtrlGsOut->apName;//zhouhj 20220415 当前未记录自身apName用此标识
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
//				pSclCtrlGsIn->ldName_own = subInfo.sub_ldInst;
			}

			pSclCtrlGsIn->m_nChnCount++;
			pSclChGsIn = (CSclChGsIn*)pSclCtrlGsIn->CreateNewCh();
			pSclChGsIn->m_strName = subInfo.ref;
			pSclChGsIn->m_strID = subInfo.sub_ref;
			pSclChGsIn->fcda_name = subInfo.sub_ref;
			pSclChGsIn->inPath = subInfo.ref;
			pSclChGsIn->outIndex = subInfo.index_Rec;
			pSclChGsIn->inIndex = nInIndex;
			pSclChGsIn->inDODesc = subInfo.desc;
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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("查找OutCtrl失败,未查找到IED(%s)."),strIedName.GetString());
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

	strTmp = ("查找OutCtrl失败,未查找到IED(%s)对于的虚端子(%s).");
	char *pzsLogMsg = NULL;
	int nOutLenth = 0;
	utf8_to_gbk((const unsigned char*)strTmp.GetString(),(int)String_Char_Count(strTmp),(unsigned char **)&pzsLogMsg,&nOutLenth);
	CLogPrint::LogFormatString(XLOGLEVEL_ERROR,pzsLogMsg,strIedName.GetString(),strFcdaRef.GetString());
	delete pzsLogMsg;
	return NULL;

}





