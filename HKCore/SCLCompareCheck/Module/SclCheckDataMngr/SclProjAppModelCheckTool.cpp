#include "SclProjAppModelCheckTool.h"
#include "../../../../Module/API/StringConvertApi.h"
#include "../../../SttStudio/Test_Win/SCLCompareTool/XLangResource_SCLCompare.h"


CSclProjAppModelCheckTool::CSclProjAppModelCheckTool(void)
{
	m_pProjAppModelChecks = NULL;
	m_pStartCheckThread = NULL;
	m_strSclFilePath = "";
	m_BeCheckFinished = TRUE;
}

CSclProjAppModelCheckTool::~CSclProjAppModelCheckTool(void)
{

}

UINT CSclProjAppModelCheckTool::StartProCheckThread(LPVOID pParam)
{
	CSclProjAppModelCheckTool *pProCheckObject = (CSclProjAppModelCheckTool *)pParam;
	return pProCheckObject->StartCheck();
}

void CSclProjAppModelCheckTool::FreeStartProCheckThread()
{
#ifdef _PSX_IDE_QT_
	if (m_pStartCheckThread != NULL)
	{
		m_pStartCheckThread->PostThreadMessage(WM_QUIT, 0, 0);
		m_pStartCheckThread->wait();
		m_pStartCheckThread = NULL;
	}
#endif
}

int CSclProjAppModelCheckTool::StartProCheckFromThread(const CString &strSclFilePath,CProjAppModelChecks *pProjAppModelChecks,CResultsRec *pProModResults)
{
	m_strSclFilePath = strSclFilePath;
	m_pProjAppModelChecks = pProjAppModelChecks;
	m_pProModResults = pProModResults;

#ifdef _PSX_IDE_QT_
	FreeStartProCheckThread();
	m_BeCheckFinished = FALSE;
	m_pStartCheckThread = new CWinThread(StartProCheckThread, this);
	m_pStartCheckThread->m_bAutoDelete = FALSE;
	m_pStartCheckThread->ResumeThread();
#else
	m_pStartCheckThread = AfxBeginThread(StartProCheckThread, this); //�����߳� 
	m_pStartCheckThread->m_bAutoDelete = TRUE;
#endif

	return 1;
}

int CSclProjAppModelCheckTool::StartProCheckNormal(const CString &strSclFilePath,CProjAppModelChecks *pProjAppModelChecks,CResultsRec *pProModResults)
{
	m_strSclFilePath = strSclFilePath;
	m_pProjAppModelChecks = pProjAppModelChecks;
	m_pProModResults = pProModResults;
	return StartCheck();

}

BOOL CSclProjAppModelCheckTool::StartCheck()
{
	if (!IsFileExist(m_strSclFilePath))//����FileApi.h�е�ȫ�ֺ������ж��ļ�·�����ļ��Ƿ���ڣ�
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, /*_T("�ļ�������(%s).")*/g_sLangTxt_Gradient_FileNoexist.GetString(), m_strSclFilePath.GetString());
		m_BeCheckFinished = TRUE;

		return FALSE;
	}


	xpugi::xml_document oDoc;

	if ( !oDoc.load_file(m_strSclFilePath.GetString())) //����XML2Interface.h�е�ȫ�ֺ�����������Դ����ڷ��ظ�oDoc��
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, /*_T("���ļ�(%s)ʧ��.")*/g_sLangTxt_Native_OpenFail.GetString(), m_strSclFilePath.GetString());
		m_BeCheckFinished = TRUE;

		return FALSE;
	}

//	TiXmlDocument oDoc;// = new TiXmlDocument();
//
//	if ( !oDoc.LoadFile(m_strSclFilePath)) //����XML2Interface.h�е�ȫ�ֺ�����������Դ����ڷ��ظ�oDoc��
//	{
//		return FALSE;
//	}

	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	CString  strObjectID;
	CString strErrorPos;

	xpugi::xml_node oSCLNode = oDoc.child("SCL");
	xpugi::xml_node pTinyCommu = oSCLNode.child("Communication");
	xpugi::xml_node pTinyIEDNode = oSCLNode.child("IED");
	xpugi::xml_node pTinyAccessPointNode;
	xpugi::xml_node pTinyServerNode;
	xpugi::xml_node pTinyLDNode;
	xpugi::xml_node pTinyLNNode;
	xpugi::xml_node pTinyLN0Node;
	m_oSCLTestObjectFile_ProjApp.DeleteAll();

	m_oSCLTestObjectFile_ProjApp.m_bUTF8 = TRUE;
	m_oSCLTestObjectFile_ProjApp.m_strName = m_strSclFilePath;
	m_oSCLTestObjectFile_ProjApp.OpenSclTemplatesFile(m_strSclFilePath);

	CExBaseList *pTestObjectTemplates = (CExBaseList*)m_oSCLTestObjectFile_ProjApp.FindByID("DataTypeTemplates");

	std::map<CString ,xpugi::xml_node> mapLNFullName;
	std::list<CString> list_DataSetName;

	CString strIEDMSG;
	CString strAccessPoint;
	CString strLDevice;

	long nIEDCount = 0;
	long nAccessPoint, nServer ,nLDevice ,nLN;
	long nConfDataSet ,nConfReportControl ,nConfLogControl ,nCurDataSetNum ,nCurRptNum ,nCurLogNum;
	BOOL bHasLLN0,bHasLPHD;

	GetIEDInputsRef(oSCLNode);
	pCheckObject = (CCheckObject*)m_pProjAppModelChecks->FindByID("physConn-OutPort");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		CheckPhysConnPort(pTinyCommu ,strObjectID );
	}

	while(pTinyIEDNode != NULL)
	{
		if (strcmp(pTinyIEDNode.name() , "IED") == 0)
		{
			nIEDCount ++; 
			nAccessPoint = 0;
			GetIEDMSG(pTinyIEDNode ,strIEDMSG);
			nConfDataSet = -1 ,nConfReportControl = -1 ,nConfLogControl = -1;
			nCurDataSetNum = 0 ,nCurRptNum = 0,nCurLogNum = 0;
			pTinyAccessPointNode = pTinyIEDNode.first_child();

			while(pTinyAccessPointNode != NULL)
			{
				if (strcmp(pTinyAccessPointNode.name() , "AccessPoint") == 0)
				{
					nAccessPoint ++;
					nServer = 0;
					strAccessPoint = pTinyAccessPointNode.attribute("name").value();
					pCheckObject = (CCheckObject*)m_pProjAppModelChecks->FindByID("AccessPoint-Name");

					if (BeCheckThisObject(pCheckObject ,strObjectID))
					{
						CheckAccessPointName(pTinyAccessPointNode ,strAccessPoint ,strIEDMSG ,strObjectID);
					}

					pTinyServerNode = pTinyAccessPointNode.first_child();

					while(pTinyServerNode != NULL)
					{
						if (strcmp(pTinyServerNode.name() , "Server") == 0)
						{
							nServer ++;
							nLDevice = 0;
							pTinyLDNode = pTinyServerNode.first_child();

							while(pTinyLDNode != NULL)
							{
								if (strcmp(pTinyLDNode.name() , "LDevice") == 0)
								{
									nLDevice ++;
									nLN = 0;
									bHasLLN0 = FALSE;
									bHasLPHD = FALSE;
									strLDevice = pTinyLDNode.attribute("inst").value();
									pCheckObject = (CCheckObject*)m_pProjAppModelChecks->FindByID("LDevice-Inst");

									if (BeCheckThisObject(pCheckObject ,strObjectID))
									{
										CheckLDeviceInst(pTinyLDNode ,strLDevice ,strAccessPoint ,strIEDMSG ,strObjectID);
									}

									pTinyLNNode = pTinyLDNode.first_child();
									mapLNFullName.clear();
									list_DataSetName.clear();

									while(pTinyLNNode != NULL)
									{
										if (strcmp(pTinyLNNode.name() ,"LN0") == 0)
										{
											nLN ++;
											bHasLLN0 = TRUE;
											pTinyLN0Node = pTinyLNNode;
										}
										else if (strcmp(pTinyLNNode.name() ,"LN") == 0)
										{
											nLN ++;
											if (strcmp(pTinyLNNode.attribute("lnClass").value(),"LPHD") == 0)
											{
												bHasLPHD = TRUE;
											}
										}

										if (pTinyLNNode.type() != xpugi::node_comment)//TINYXML_COMMENT
										{
											CheckDOI_SDI_DAI_RefValid(pTinyLNNode ,pTinyLDNode  ,pTestObjectTemplates,&mapLNFullName ,strLDevice ,strAccessPoint ,strIEDMSG ,m_pProjAppModelChecks);
										}

										pTinyLNNode = pTinyLNNode.next_sibling();
									}

 									CheckDataSetRelated(pTinyLN0Node ,pTinyLDNode ,&mapLNFullName ,strLDevice ,strAccessPoint ,strIEDMSG ,m_pProjAppModelChecks ,nCurDataSetNum);
 									CheckInputsExtRef(pTinyLN0Node ,pTinyLDNode ,&mapLNFullName ,strLDevice ,strAccessPoint ,strIEDMSG ,m_pProjAppModelChecks );
 									GetDataSetName(pTinyLN0Node ,list_DataSetName);
 									CheckReportCtrlRelated(pTinyLN0Node ,list_DataSetName ,strLDevice ,strAccessPoint ,strIEDMSG ,m_pProjAppModelChecks ,nCurRptNum);
 									CheckLogCtrlRelated(pTinyLN0Node ,list_DataSetName ,strLDevice ,strAccessPoint ,strIEDMSG ,m_pProjAppModelChecks ,nCurLogNum);
 									CheckSMVCtrlRelated(pTinyLN0Node ,list_DataSetName ,strLDevice ,strAccessPoint ,strIEDMSG ,m_pProjAppModelChecks);
 									CheckGSECtrlRelated(pTinyLN0Node ,list_DataSetName ,strLDevice ,strAccessPoint ,strIEDMSG ,m_pProjAppModelChecks);
 									CheckSettingCtrlRelated(pTinyLN0Node ,list_DataSetName ,strLDevice ,strAccessPoint ,strIEDMSG ,m_pProjAppModelChecks);
									pTinyLN0Node;
									mapLNFullName.clear();
									list_DataSetName.clear();

									pCheckObject = (CCheckObject*)m_pProjAppModelChecks->FindByID("LN-Object");

									if (BeCheckThisObject(pCheckObject ,strObjectID))
									{
										strErrorPos.Format("%s=%d ,%s=%d" ,g_sLangTxt_SCLCompare_RowNum.GetString(), -1,/*pTinyLDNode->Row(),*/
											g_sLangTxt_SCLCompare_ColumnNum.GetString(), -1/*pTinyLDNode->Column() */);

										if (!bHasLLN0)
										{
											/*strErrorText = "��IED(";
											strErrorText += strIEDMSG;
											strErrorText.AppendFormat(")�� AccessPoint(%s)��, LDevice(%s)������ ȱ��(LLN0);",
												strAccessPoint.GetString() ,strLDevice.GetString());*/
											FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)��, LDevice(%s)������ ȱ��(LLN0);"*/g_sLangTxt_SCLCompare_ProModDescription1.GetString(),
												strIEDMSG.GetString(), strAccessPoint.GetString() ,strLDevice.GetString());
											AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
										}

										if (!bHasLPHD)
										{
											/*strErrorText = "��IED(";
											strErrorText += strIEDMSG;
											strErrorText.AppendFormat(")�� AccessPoint(%s)��, LDevice(%s)������ ȱ��(LPHD);",
												strAccessPoint.GetString() ,strLDevice.GetString());*/
											FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)��, LDevice(%s)������ ȱ��(LPHD);"*/g_sLangTxt_SCLCompare_ProModDescription2.GetString(),
												strIEDMSG.GetString(), strAccessPoint.GetString() ,strLDevice.GetString());
											AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
										}

										if (nLN < 3)
										{
											/*strErrorText = "��IED(";
											strErrorText += strIEDMSG;
											strErrorText.AppendFormat(")�� AccessPoint(%s)��, LDevice(%s)������ LN����(LLN0��LPHD������Ӧ���߼��ӵ�)��������;",
												strAccessPoint.GetString() ,strLDevice.GetString());*/
											FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)��, LDevice(%s)������ LN����(LLN0��LPHD������Ӧ���߼��ӵ�)��������;"*/g_sLangTxt_SCLCompare_ProModDescription3.GetString(),
												strIEDMSG.GetString(), strAccessPoint.GetString() ,strLDevice.GetString());
											AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
										}
									}
								}
								pTinyLDNode = pTinyLDNode.next_sibling();
							}
						}
						pTinyServerNode = pTinyServerNode.next_sibling();
					}

					pCheckObject = (CCheckObject*)m_pProjAppModelChecks->FindByID("Server-Object");

					if ((BeCheckThisObject(pCheckObject ,strObjectID))&&(nServer == 0))
					{
						/*strErrorText = "��IED(";
						strErrorText += strIEDMSG;
						strErrorText.AppendFormat(")�� AccessPoint(%s)�²������κ�Server����;" ,strAccessPoint.GetString());*/
						FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)�²������κ�Server����;"*/g_sLangTxt_SCLCompare_ProModDescription4.GetString(), strIEDMSG.GetString(), strAccessPoint.GetString());
						strErrorPos.Format("%s=%d ,%s=%d" ,g_sLangTxt_SCLCompare_RowNum.GetString(),-1/* pTinyAccessPointNode->Row()*/,
							g_sLangTxt_SCLCompare_ColumnNum.GetString(), -1/*pTinyAccessPointNode->Column()*/ );
						AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
					}
				}
				else if (strcmp(pTinyAccessPointNode.name() , "Services") == 0)
				{
					GetIEDMaxConfigNum(pTinyAccessPointNode, nConfDataSet ,nConfReportControl ,nConfLogControl);
				}
				pTinyAccessPointNode = pTinyAccessPointNode.next_sibling();
			}

			CheckDataSetRptCtrlLogCtrlMaxNum(pTinyIEDNode ,nConfDataSet ,nCurDataSetNum ,nConfReportControl ,nCurRptNum ,nConfLogControl ,nCurLogNum ,strIEDMSG ,m_pProjAppModelChecks );
		}
		pTinyIEDNode = pTinyIEDNode.next_sibling();
	}
	m_BeCheckFinished = TRUE;
	return TRUE;
}

BOOL CSclProjAppModelCheckTool::BeCheckThisObject(CCheckObject *pCheckObject ,CString &strObjectID)
{
	strObjectID = "";
	if (pCheckObject == NULL)
	{
		return TRUE;
	} 
	else
	{
		strObjectID = pCheckObject->m_strErrorType;
		return pCheckObject->m_nChoose;
	}
}

void CSclProjAppModelCheckTool::GetIEDInputsRef(xpugi::xml_node pDocRoot)
{
	if (pDocRoot == NULL)
	{
		return;
	}

	CExBaseList *pIED = NULL;
	CExBaseList *pLDevice = NULL;
	CTinyExtRef *pTinyExtRef = NULL;
	CString strIEDName;
	CString strAccessPoint;
	CString strDatasetName;
	CString strCtrlName;
	CString strIEDPath;
	CString strDaName;

	xpugi::xml_node pTinyIED = pDocRoot.child("IED");
	xpugi::xml_node pTinyAccessPoint;
	xpugi::xml_node pTinyServer;
	xpugi::xml_node pTinyLDevice;
	xpugi::xml_node pTinyLN;
	xpugi::xml_node pTinyDataSet;
	xpugi::xml_node pTinyFCDA;
	xpugi::xml_node pTinyCtrl;

	while(pTinyIED != NULL)
	{
		if (strcmp(pTinyIED.name() ,"IED") == 0)
		{
			pIED = new CExBaseList;
			m_oTinySCLStation.AddNewChild(pIED);
			pIED->m_strID = pTinyIED.attribute("name").value();
			GetTinyDescAndName(pTinyIED ,strIEDName);
			pIED->m_strName = strIEDName;

			pTinyAccessPoint = pTinyIED.child("AccessPoint");

			while(pTinyAccessPoint != NULL)
			{
				if (strcmp(pTinyAccessPoint.name() ,"AccessPoint") == 0)
				{
					strAccessPoint = pTinyAccessPoint.attribute("name").value();
					pTinyServer = pTinyAccessPoint.child("Server");
					while(pTinyServer != NULL)
					{
						if (strcmp(pTinyServer.name() ,"Server") == 0)
						{
							pTinyLDevice = pTinyServer.child("LDevice");
							while(pTinyLDevice != NULL)
							{
								if (strcmp(pTinyLDevice.name() ,"LDevice") == 0)
								{
									pLDevice = new CExBaseList;
									pIED->AddNewChild(pLDevice);
									pLDevice->m_strID = pTinyLDevice.attribute("inst").value();
									pLDevice->m_strName = strAccessPoint;
									pTinyLN = pTinyLDevice.child("LN0");

									if (pTinyLN != NULL)
									{
										pTinyCtrl = pTinyLN.first_child();
										while(pTinyCtrl != NULL)
										{
											if ((strcmp(pTinyCtrl.name() ,"SampledValueControl") == 0)||(strcmp(pTinyCtrl.name() ,"GSEControl") == 0))
											{
												strDatasetName = pTinyCtrl.attribute("datSet").value();
												strCtrlName = pTinyCtrl.attribute("name").value();
												pTinyDataSet = pTinyLN.child("DataSet");
												while(pTinyDataSet != NULL)
												{
													if (strcmp(pTinyDataSet.attribute("name").value() ,strDatasetName.GetString()) == 0)
													{
														pTinyFCDA = pTinyDataSet.first_child();
														while(pTinyFCDA != NULL)
														{
															pTinyExtRef = new CTinyExtRef;
															pLDevice->AddNewChild(pTinyExtRef);
															pTinyExtRef->m_strCtrlName = strCtrlName;
															pTinyExtRef->m_strName = strDatasetName;
															strIEDPath = pTinyFCDA.attribute("ldInst").value();
															strIEDPath += '/';
															strIEDPath += pTinyFCDA.attribute("prefix").value();
															strIEDPath += pTinyFCDA.attribute("lnClass").value();
															strIEDPath += pTinyFCDA.attribute("lnInst").value();
															strIEDPath += '.';
															strIEDPath += pTinyFCDA.attribute("doName").value();
															strDaName = pTinyFCDA.attribute("daName").value();

															if (!strDaName.IsEmpty())
															{
																strIEDPath += '.';
																strIEDPath += strDaName;
															}
															pTinyExtRef->m_strID = strIEDPath;

															pTinyFCDA = pTinyFCDA.next_sibling();
														}
														break;
													}

													pTinyDataSet = pTinyDataSet.next_sibling();
												}
											}

											pTinyCtrl = pTinyCtrl.next_sibling();
										}
									}
								}

								pTinyLDevice = pTinyLDevice.next_sibling();
							}
						}

						pTinyServer = pTinyServer.next_sibling();
					}
				}

				pTinyAccessPoint = pTinyAccessPoint.next_sibling();
			}
		}

		pTinyIED = pTinyIED.next_sibling();
	}
}

void CSclProjAppModelCheckTool::CheckPhysConnPort(xpugi::xml_node pTinyCommu ,CString strObjectID )
{
	if (pTinyCommu == NULL)
	{
		return;
	}

	CString strErrorText;
	CString strErrorPos;

	CString strSubNetwork;
	CString strIEDMSG;
	CString strPhysConnType;
	CString strPortName;

	BOOL bHasPhysConn;

	xpugi::xml_node pTinySubNetwork = pTinyCommu.first_child();
	xpugi::xml_node pTinyConnectedAP;
	xpugi::xml_node pTinyPhysConn;
	xpugi::xml_node pTinyP;

	while(pTinySubNetwork != NULL)
	{
		if (strcmp(pTinySubNetwork.name() , "SubNetwork") == 0 )
		{
			GetTinyDescAndName(pTinySubNetwork ,strSubNetwork);
			pTinyConnectedAP = pTinySubNetwork.first_child();

			while(pTinyConnectedAP != NULL)
			{
				if (strcmp(pTinyConnectedAP.name() , "ConnectedAP") == 0 )
				{
					bHasPhysConn = FALSE;
					FormatString(strIEDMSG,/*"iedName(%s)���ʵ�����(%s)"*/g_sLangTxt_SCLCompare_ProModDescription70.GetString(),pTinyConnectedAP.attribute("iedName").value() ,
						pTinyConnectedAP.attribute("apName").value());
					pTinyPhysConn = pTinyConnectedAP.first_child();

					while(pTinyPhysConn != NULL)
					{
						if (strcmp(pTinyPhysConn.name() , "PhysConn") == 0 )
						{
							bHasPhysConn = TRUE;
							strPhysConnType = pTinyPhysConn.attribute("type").value();
							pTinyP = pTinyPhysConn.first_child();

							while(pTinyP != NULL)
							{
								if (strcmp(pTinyP.attribute("type").value() , "Port") == 0 )
								{
									break;
								}

								pTinyP = pTinyP.next_sibling();
							}

							if (pTinyP == NULL)
							{
								/*strErrorText = strSubNetwork;
								strErrorText += " ������ IED�豸(";
								strErrorText += strIEDMSG;
								strErrorText.AppendFormat(")���������� %s ��ȱ�ٶ˿���Ϣ����;",strPhysConnType.GetString());*/
								FormatString(strErrorText,/*"%s ������ IED�豸(%s)���������� %s ��ȱ�ٶ˿���Ϣ����;"*/g_sLangTxt_SCLCompare_ProModDescription5.GetString(),
									strSubNetwork.GetString(), strIEDMSG.GetString(),strPhysConnType.GetString());
//								xpugi::debug_info_t debugInfo = pTinyPhysConn.offset_debug();
								strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1)/*pTinyPhysConn.offset_debug(),pTinyPhysConn->Column() )*/;
								AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
							} 
							else
							{
								strPortName = pTinyP.first_child().value();

								if (!CheckPortNameValid(strPortName))
								{
									/*strErrorText = strSubNetwork;
									strErrorText += " ������ IED�豸(";
									strErrorText += strIEDMSG;
									strErrorText.AppendFormat(")���������� %s ��ȱ�ٶ˿���Ϣ %s ������ʽ����;",strPhysConnType.GetString() ,strPortName.GetString());*/
									FormatString(strErrorText,/*"%s ������ IED�豸(%s)���������� %s ��ȱ�ٶ˿���Ϣ %s ������ʽ����;"*/g_sLangTxt_SCLCompare_ProModDescription6.GetString(),
										strSubNetwork.GetString(), strIEDMSG.GetString(),strPhysConnType.GetString() ,strPortName.GetString());
									strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyP->Row(),pTinyP->Column() */);
									AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
								}
							}
						}

						pTinyPhysConn = pTinyPhysConn.next_sibling();
					}

					if (!bHasPhysConn)
					{
						/*strErrorText = strSubNetwork;

						strErrorText += " ������ IED�豸 ";
						strErrorText += strIEDMSG;
						strErrorText += " �� ȱ������˿���Ϣ(PhysConn)�ڵ�;";*/
						FormatString(strErrorText,/*"%s ������ IED�豸 %s �� ȱ������˿���Ϣ(PhysConn)�ڵ�;"*/g_sLangTxt_SCLCompare_ProModDescription7.GetString(),
							strSubNetwork.GetString(), strIEDMSG.GetString());
						strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyConnectedAP->Row(),pTinyConnectedAP->Column()*/ );
						AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
					}
				}

				pTinyConnectedAP = pTinyConnectedAP.next_sibling();
			}
		}

		pTinySubNetwork = pTinySubNetwork.next_sibling();
	}
}

void CSclProjAppModelCheckTool::CheckDataSetRptCtrlLogCtrlMaxNum(xpugi::xml_node pTinyIEDNode ,long nConfDataSet ,long nCurDataSetNum ,long nConfReportControl ,long nCurRptNum ,long nConfLogControl ,long nCurLogNum ,
															CString strIEDMSG, CProjAppModelChecks *pProjAppModelChecks )
{
	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	CString  strObjectID;
	CString strErrorPos;

	pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("IEDMaxNum-Valid");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		if ((nConfDataSet != -1)&&(nConfDataSet < nCurDataSetNum))
		{
			/*strErrorText = "��IED(";
			strErrorText += strIEDMSG;
			strErrorText.AppendFormat(")�� ConfDataSet(������ݼ���Ŀ) ֵΪ %ld ,С�� ʵ���������ݼ���Ŀ %ld;",
				nConfDataSet ,nCurDataSetNum);*/
			FormatString(strErrorText,/*"��IED(%s)�� ConfDataSet(������ݼ���Ŀ) ֵΪ %ld ,С�� ʵ���������ݼ���Ŀ %ld;"*/g_sLangTxt_SCLCompare_ProModDescription8.GetString(),
				strIEDMSG.GetString(), nConfDataSet ,nCurDataSetNum);
			strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyIEDNode->Row(),pTinyIEDNode->Column()*/ );
			AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
		}

		if ((nConfReportControl != -1)&&(nConfReportControl < nCurRptNum))
		{
			/*strErrorText = "��IED(";
			strErrorText += strIEDMSG;
			strErrorText.AppendFormat(")�� ConfReportControl(��󱨸���ƿ���Ŀ) ֵΪ %ld ,С�� ʵ�����ñ�����ƿ���Ŀ %ld;",
				nConfReportControl ,nCurRptNum);*/
			FormatString(strErrorText,/*"��IED(%s)�� ConfReportControl(��󱨸���ƿ���Ŀ) ֵΪ %ld ,С�� ʵ�����ñ�����ƿ���Ŀ %ld;"*/g_sLangTxt_SCLCompare_ProModDescription9.GetString(),
				strIEDMSG.GetString(),nConfReportControl ,nCurRptNum);
			strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyIEDNode->Row(),pTinyIEDNode->Column()*/ );
			AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
		}

		if ((nConfLogControl != -1)&&(nConfLogControl < nCurLogNum))
		{
			/*strErrorText = "��IED(";
			strErrorText += strIEDMSG;
			strErrorText.AppendFormat(")�� ConfLogControl(�����־���ƿ���Ŀ) ֵΪ %ld ,С�� ʵ��������־���ƿ���Ŀ %ld;",
				nConfLogControl ,nCurLogNum);*/
			FormatString(strErrorText,/*"��IED(%s)�� ConfLogControl(�����־���ƿ���Ŀ) ֵΪ %ld ,С�� ʵ��������־���ƿ���Ŀ %ld;"*/g_sLangTxt_SCLCompare_ProModDescription10.GetString(),
				strIEDMSG.GetString(),nConfLogControl ,nCurLogNum);
			strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyIEDNode->Row(),pTinyIEDNode->Column() */);
			AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
		}
	}
}

void CSclProjAppModelCheckTool::GetIEDMaxConfigNum(xpugi::xml_node pTinyAccessPointNode,long &nConfDataSet ,long &nConfReportControl ,long &nConfLogControl)
{
	CString strMaxNum;
	xpugi::xml_node pTinyMaxNum = pTinyAccessPointNode.child("ConfDataSet");

	if (pTinyMaxNum != NULL)
	{
		strMaxNum = pTinyMaxNum.attribute("max").value();
		if (!strMaxNum.IsEmpty())
		{
			nConfDataSet = CString_To_long(strMaxNum);
		}
	}

	pTinyMaxNum = pTinyAccessPointNode.child("ConfReportControl");

	if (pTinyMaxNum != NULL)
	{
		strMaxNum = pTinyMaxNum.attribute("max").value();
		if (!strMaxNum.IsEmpty())
		{
			nConfReportControl = CString_To_long(strMaxNum);
		}
	}

	pTinyMaxNum = pTinyAccessPointNode.child("ConfLogControl");

	if (pTinyMaxNum != NULL)
	{
		strMaxNum = pTinyMaxNum.attribute("max").value();
		if (!strMaxNum.IsEmpty())
		{
			nConfLogControl = CString_To_long(strMaxNum);
		}
	}
}


void CSclProjAppModelCheckTool::AddCheckResultProjAppModel(CString strErrorType ,CString strText ,CString strErrorPos)
{
	CResultRec *pResultRec = new CResultRec();
	m_pProModResults->AddNewChild(pResultRec);
	pResultRec->m_strErrorText = strText;
	pResultRec->m_strErrorPos = strErrorPos;
	if (strErrorType == "tips")
	{
		m_pProModResults->m_nAllTipIndex++;
		pResultRec->m_strErrorType = /*"��ʾ"*/g_sLangTxt_Native_LangTip;
		pResultRec->m_strErrorType.AppendFormat("%d ",m_pProModResults->m_nAllTipIndex);
		pResultRec->m_nTipIndex = 1;	
	}
	else if (strErrorType == "warning")
	{
		m_pProModResults->m_nAllWarningIndex++;
		pResultRec->m_strErrorType = /*"�澯"*/g_sLangTxt_SCLCompare_Warning;
		pResultRec->m_strErrorType.AppendFormat("%d ",m_pProModResults->m_nAllWarningIndex);
		pResultRec->m_nWarningIndex = 1;	
	}
	else if (strErrorType == "error")
	{
		m_pProModResults->m_nAllErrorIndex++;
		pResultRec->m_strErrorType = /*"����"*/g_sLangTxt_Native_error;
		pResultRec->m_strErrorType.AppendFormat("%d ",m_pProModResults->m_nAllErrorIndex);
		pResultRec->m_nErrorIndex = 1;
	}
	else if (strErrorType == "fatalerror")
	{
		m_pProModResults->m_nAllFatalErrorIndex++;
		pResultRec->m_strErrorType = /*"����"*/g_sLangTxt_SCLCompare_Serious;
		pResultRec->m_strErrorType.AppendFormat("%d ",m_pProModResults->m_nAllFatalErrorIndex);
		pResultRec->m_nFatalErrorIndex = 1;	
	}
}


void CSclProjAppModelCheckTool::CheckSettingCtrlRelated(xpugi::xml_node pTinyLN0Node ,std::list<CString> list_DataSetName ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,
												   CProjAppModelChecks *pProjAppModelChecks)
{
	if (pTinyLN0Node == NULL)
	{
		return;
	}

	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	CString  strObjectID;
	CString strErrorPos;
	CString strDataSetName;
	BOOL bCheck = FALSE;

	std::list<CString>::iterator iter = list_DataSetName.begin();
	std::list<CString>::iterator iend = list_DataSetName.end();

	pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("SettingCtrl-Related");

	if(BeCheckThisObject(pCheckObject ,strObjectID))
	{
		for(iter = list_DataSetName.begin(); iter != iend; iter++)
		{
			if ((*iter).Find("dsSetting") == 0)
			{
				bCheck = TRUE;
				break;
			}
		}

		xpugi::xml_node pTinySettingCtrl = pTinyLN0Node.child("SettingControl");

		if (pTinySettingCtrl != NULL)
		{
			long nNumSGs = -1;
			CString strNum = pTinySettingCtrl.attribute("numOfSGs").value();

			if (strNum.IsEmpty())
			{
				/*strErrorText = "��IED(";
				strErrorText += strIEDMSG;
				strErrorText.AppendFormat(")�� AccessPoint(%s)��, LDevice(%s)������ �Ķ�ֵ���ƿ���ȱ�� numOfSGs(��ֵ����Ŀ)����;",
					strAccessPoint.GetString() ,strLDevice.GetString());*/
				FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)��, LDevice(%s)������ �Ķ�ֵ���ƿ���ȱ�� numOfSGs(��ֵ����Ŀ)����;"*/g_sLangTxt_SCLCompare_ProModDescription11.GetString(),
					strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString());
				strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinySettingCtrl->Row(),pTinySettingCtrl->Column()*/ );
				AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
			} 
			else
			{
				nNumSGs = CString_To_long(strNum);
				if (nNumSGs < 2)
				{
					/*strErrorText = "��IED(";
					strErrorText += strIEDMSG;
					strErrorText.AppendFormat(")�� AccessPoint(%s)��, LDevice(%s)������ �Ķ�ֵ���ƿ��� numOfSGs(��ֵ����Ŀ)����ֵС��2;",
						strAccessPoint.GetString() ,strLDevice.GetString());*/
					FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)��, LDevice(%s)������ �Ķ�ֵ���ƿ��� numOfSGs(��ֵ����Ŀ)����ֵС��2;"*/g_sLangTxt_SCLCompare_ProModDescription12.GetString(),
						strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString());
					strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinySettingCtrl->Row(),pTinySettingCtrl->Column()*/ );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}

			strNum = pTinySettingCtrl.attribute("actSG").value();

			if (strNum.IsEmpty())
			{
				/*strErrorText = "��IED(";
				strErrorText += strIEDMSG;
				strErrorText.AppendFormat(")�� AccessPoint(%s)��, LDevice(%s)������ �Ķ�ֵ���ƿ���ȱ�� actSG(���ֵ��)����;",
					strAccessPoint.GetString() ,strLDevice.GetString());*/
				FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)��, LDevice(%s)������ �Ķ�ֵ���ƿ���ȱ�� actSG(���ֵ��)����;"*/g_sLangTxt_SCLCompare_ProModDescription13.GetString(),
					strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString());
				strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinySettingCtrl->Row(),pTinySettingCtrl->Column()*/ );
				AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
			} 
			else
			{
				long nActSG = CString_To_long(strNum);

				if ((nNumSGs != -1)&&(nActSG > nNumSGs))
				{
					/*strErrorText = "��IED(";
					strErrorText += strIEDMSG;
					strErrorText.AppendFormat(")�� AccessPoint(%s)��, LDevice(%s)������ �Ķ�ֵ���ƿ��� actSG(���ֵ��)����ֵ)%ld)���� numOfSGs(��ֵ����Ŀ)����ֵ(%ld);",
						strAccessPoint.GetString() ,
						strLDevice.GetString() ,nActSG ,nNumSGs);*/
					FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)��, LDevice(%s)������ �Ķ�ֵ���ƿ��� actSG(���ֵ��)����ֵ)%ld)���� numOfSGs(��ֵ����Ŀ)����ֵ(%ld);"*/g_sLangTxt_SCLCompare_ProModDescription14.GetString(),
						strIEDMSG.GetString(),strAccessPoint.GetString() ,
						strLDevice.GetString() ,nActSG ,nNumSGs);
					strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinySettingCtrl->Row(),pTinySettingCtrl->Column()*/ );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}
		}
		else if (bCheck)
		{
			/*strErrorText = "��IED(";
			strErrorText += strIEDMSG;
			strErrorText.AppendFormat(")�� AccessPoint(%s)��, LDevice(%s)������ ������ֵ���ݼ� ��ȱ�ٶ�ֵ���ƿ�;",
				strAccessPoint.GetString() ,strLDevice.GetString());*/
			FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)��, LDevice(%s)������ ������ֵ���ݼ� ��ȱ�ٶ�ֵ���ƿ�;"*/g_sLangTxt_SCLCompare_ProModDescription15.GetString(),
				strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString());
			strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyLN0Node->Row(),pTinyLN0Node->Column() */);
			AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
		}
		else if (strLDevice == "PROT")
		{
			/*strErrorText = "��IED(";
			strErrorText += strIEDMSG;
			strErrorText.AppendFormat(")�� AccessPoint(%s)��, LDevice(%s)������ ȱ�ٶ�ֵ���ƿ�;",
				strAccessPoint.GetString() ,strLDevice.GetString());*/
			FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)��, LDevice(%s)������ ȱ�ٶ�ֵ���ƿ�;"*/g_sLangTxt_SCLCompare_ProModDescription16.GetString(),
				strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString());
			strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyLN0Node->Row(),pTinyLN0Node->Column()*/ );
			AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
		}
	}
}

void CSclProjAppModelCheckTool::CheckGSECtrlRelated(xpugi::xml_node pTinyLN0Node ,std::list<CString> list_DataSetName ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,
											   CProjAppModelChecks *pProjAppModelChecks)
{
	if (pTinyLN0Node == NULL)
	{
		return;
	}

	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	CString  strObjectID;
	CString strErrorPos;
	CString strDataSetName;

	std::list<CString>::iterator iter = list_DataSetName.begin();
	std::list<CString>::iterator iend = list_DataSetName.end();

	xpugi::xml_node pTinyGSECtrl = pTinyLN0Node.child("GSEControl");
	while(pTinyGSECtrl != NULL)
	{
		if (strcmp(pTinyGSECtrl.name() ,"GSEControl") == 0)
		{
			pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("GSECtrl-DataSet");

			if(BeCheckThisObject(pCheckObject ,strObjectID))
			{
				strDataSetName = pTinyGSECtrl.attribute("datSet").value();

				for(iter = list_DataSetName.begin(); iter != iend; iter++)
				{
					if (*iter == strDataSetName)
					{
						break;
					}
				}

				if (iter == iend)
				{
					/*strErrorText = "��IED(";
					strErrorText += strIEDMSG;
					strErrorText.AppendFormat(")�� AccessPoint(%s)��, LDevice(%s)������ GOOSE���ƿ�(%s)���������ݼ�(%s)δ����;",
						strAccessPoint.GetString() ,strLDevice.GetString(),
						pTinyGSECtrl->Attribute("name") ,strDataSetName.GetString());*/
					FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)��, LDevice(%s)������ GOOSE���ƿ�(%s)���������ݼ�(%s)δ����;"*/g_sLangTxt_SCLCompare_ProModDescription17.GetString(),
						strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString(),
						pTinyGSECtrl.attribute("name").value() ,strDataSetName.GetString());
					strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyGSECtrl->Row(),pTinyGSECtrl->Column()*/ );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}
		}

		pTinyGSECtrl = pTinyGSECtrl.next_sibling();
	}
}


void CSclProjAppModelCheckTool::CheckSMVCtrlRelated(xpugi::xml_node pTinyLN0Node ,std::list<CString> list_DataSetName ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,
											   CProjAppModelChecks *pProjAppModelChecks)
{
	if (pTinyLN0Node == NULL)
	{
		return;
	}

	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	CString  strObjectID;
	CString strErrorPos;
	CString strDataSetName;

	std::list<CString>::iterator iter = list_DataSetName.begin();
	std::list<CString>::iterator iend = list_DataSetName.end();

	xpugi::xml_node pTinySMVCtrl = pTinyLN0Node.child("SampledValueControl");
	while(pTinySMVCtrl != NULL)
	{
		if (strcmp(pTinySMVCtrl.name() ,"SampledValueControl") == 0)
		{
			pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("SMVCtrl-DataSet");

			if(BeCheckThisObject(pCheckObject ,strObjectID))
			{
				strDataSetName = pTinySMVCtrl.attribute("datSet").value();

				for(iter = list_DataSetName.begin(); iter != iend; iter++)
				{
					if (*iter == strDataSetName)
					{
						break;
					}
				}

				if (iter == iend)
				{
					/*strErrorText = "��IED(";
					strErrorText += strIEDMSG;
					strErrorText.AppendFormat(")�� AccessPoint(%s)��, LDevice(%s)������ ����ֵ���ƿ�(%s)���������ݼ�(%s)δ����;",
						strAccessPoint.GetString() ,strLDevice.GetString() ,
						pTinySMVCtrl->Attribute("name") ,strDataSetName.GetString());*/
					FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)��, LDevice(%s)������ ����ֵ���ƿ�(%s)���������ݼ�(%s)δ����;"*/g_sLangTxt_SCLCompare_ProModDescription18.GetString(),
						strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString() ,
						pTinySMVCtrl.attribute("name").value() ,strDataSetName.GetString());
					strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinySMVCtrl->Row(),pTinySMVCtrl->Column()*/ );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}
		}

		pTinySMVCtrl = pTinySMVCtrl.next_sibling();
	}
}

void CSclProjAppModelCheckTool::CheckLogCtrlRelated(xpugi::xml_node pTinyLN0Node ,std::list<CString> list_DataSetName ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,
											   CProjAppModelChecks *pProjAppModelChecks ,long &nCurLogNum)
{
	if (pTinyLN0Node == NULL)
	{
		return;
	}

	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	CString  strObjectID;
	CString strErrorPos;
	CString strDataSetName;

	std::list<CString>::iterator iter = list_DataSetName.begin();
	std::list<CString>::iterator iend = list_DataSetName.end();

	xpugi::xml_node pTinyLogCtrl = pTinyLN0Node.child("LogControl");
	while(pTinyLogCtrl != NULL)
	{
		if (strcmp(pTinyLogCtrl.name() ,"LogControl") == 0)
		{
			nCurLogNum++;
			pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("LogCtrl-DataSet");

			if(BeCheckThisObject(pCheckObject ,strObjectID))
			{
				strDataSetName = pTinyLogCtrl.attribute("datSet").value();

				for(iter = list_DataSetName.begin(); iter != iend; iter++)
				{
					if (*iter == strDataSetName)
					{
						break;
					}
				}

				if (iter == iend)
				{
					/*strErrorText = "��IED(";
					strErrorText += strIEDMSG;
					strErrorText.AppendFormat(")�� AccessPoint(%s)��, LDevice(%s)������ ��־���ƿ�(%s)���������ݼ�(%s)δ����;",
						strAccessPoint.GetString() ,strLDevice.GetString() ,
						pTinyLogCtrl->Attribute("name") ,strDataSetName.GetString());*/
					FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)��, LDevice(%s)������ ��־���ƿ�(%s)���������ݼ�(%s)δ����;"*/g_sLangTxt_SCLCompare_ProModDescription19.GetString(),
						strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString() ,
						pTinyLogCtrl.attribute("name").value() ,strDataSetName.GetString());
					strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyLogCtrl->Row(),pTinyLogCtrl->Column()*/ );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}
		}

		pTinyLogCtrl = pTinyLogCtrl.next_sibling();
	}
}

void CSclProjAppModelCheckTool::CheckReportCtrlRelated(xpugi::xml_node pTinyLN0Node ,std::list<CString> list_DataSetName ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,
												  CProjAppModelChecks *pProjAppModelChecks ,long &nCurRptNum)
{
	if (pTinyLN0Node == NULL)
	{
		return;
	}

	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	CString  strObjectID;
	CString strErrorPos;
	CString strDataSetName;
	CString strRptID;
	CString strRptName;
	CString strRptIDPort = strLDevice;
	strRptIDPort += "/LLN0";
	long nMax = 0;
	CString strMax;

	xpugi::xml_node pTinyRptEnabled;

	std::list<CString>::iterator iter = list_DataSetName.begin();
	std::list<CString>::iterator iend = list_DataSetName.end();

	xpugi::xml_node pTinyReportCtrl = pTinyLN0Node.child("ReportControl");
	while(pTinyReportCtrl != NULL)
	{
		if (strcmp(pTinyReportCtrl.name() ,"ReportControl") == 0)
		{
			nCurRptNum++;
			strRptName = pTinyReportCtrl.attribute("name").value();

			pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("ReportCtrl-DataSet");

			if(BeCheckThisObject(pCheckObject ,strObjectID))
			{
				strDataSetName = pTinyReportCtrl.attribute("datSet").value();
				for(iter = list_DataSetName.begin(); iter != iend; iter++)
				{
					if (*iter == strDataSetName)
					{
						break;
					}
				}

				if (iter == iend)
				{
					/*strErrorText = "��IED(";
					strErrorText += strIEDMSG;
					strErrorText.AppendFormat(")�� AccessPoint(%s)��, LDevice(%s)������ ������ƿ�(%s)���������ݼ�(%s)δ����;",
						strAccessPoint.GetString() ,strLDevice.GetString() ,
						strRptName.GetString() ,strDataSetName.GetString());*/
					FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)��, LDevice(%s)������ ������ƿ�(%s)���������ݼ�(%s)δ����;"*/g_sLangTxt_SCLCompare_ProModDescription20.GetString(),
						strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString() ,
						strRptName.GetString() ,strDataSetName.GetString());
					strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyReportCtrl->Row(),pTinyReportCtrl->Column()*/ );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}

			pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("ReportCtrl-rptID");

			if(BeCheckThisObject(pCheckObject ,strObjectID))
			{
				strRptID = pTinyReportCtrl.attribute("rptID").value();

				if (strRptID.Find(strRptIDPort) >= 0)
				{
					/*strErrorText = "��IED(";
					strErrorText += strIEDMSG;
					strErrorText.AppendFormat(")�� AccessPoint(%s)��, LDevice(%s)������ ������ƿ�(%s)�� rptID =(%s)����, Ӧ��Ϊ���͵�·��;",
						strAccessPoint.GetString() ,
						strLDevice.GetString() ,strRptName.GetString() ,strRptID.GetString());*/
					FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)��, LDevice(%s)������ ������ƿ�(%s)�� rptID =(%s)����, Ӧ��Ϊ���͵�·��;"*/g_sLangTxt_SCLCompare_ProModDescription21.GetString(),
						strIEDMSG.GetString(),strAccessPoint.GetString() ,
						strLDevice.GetString() ,strRptName.GetString() ,strRptID.GetString());
					strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyReportCtrl->Row(),pTinyReportCtrl->Column()*/ );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}

			pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("ReportCtrlName-Valid");

			if(BeCheckThisObject(pCheckObject ,strObjectID))
			{
				if (!((strRptName.Find("urcb") == 0)||((strRptName.Find("brcb") == 0))))
				{
					/*strErrorText = "��IED(";
					strErrorText += strIEDMSG;
					strErrorText.AppendFormat(")�� AccessPoint(%s)��, LDevice(%s)������ ������ƿ�(%s)����������, Ӧ���� urcb �� brcb ��ͷ;",
						strAccessPoint.GetString() ,
						strLDevice.GetString() ,strRptName.GetString() );*/
					FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)��, LDevice(%s)������ ������ƿ�(%s)����������, Ӧ���� urcb �� brcb ��ͷ;"*/g_sLangTxt_SCLCompare_ProModDescription22.GetString(),
						strIEDMSG.GetString(),strAccessPoint.GetString() ,
						strLDevice.GetString() ,strRptName.GetString());
					strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyReportCtrl->Row(),pTinyReportCtrl->Column()*/ );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}

			pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("RptEnabled-Max");

			if(BeCheckThisObject(pCheckObject ,strObjectID))
			{
				pTinyRptEnabled = pTinyReportCtrl.child("RptEnabled");

				if (pTinyRptEnabled != NULL)
				{
					strMax = pTinyRptEnabled.attribute("max").value();
					nMax = CString_To_long(strMax);

					if (nMax < 12)
					{
						/*strErrorText = "��IED(";
						strErrorText += strIEDMSG;
						strErrorText.AppendFormat(")�� AccessPoint(%s)��, LDevice(%s)������ ������ƿ�(%s)��RptEnabled �µ� max =(%s)С��12 �� ��Ч ;"
							 ,strAccessPoint.GetString() ,
							strLDevice.GetString() ,strRptName.GetString() ,strMax.GetString());*/
						FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)��, LDevice(%s)������ ������ƿ�(%s)��RptEnabled �µ� max =(%s)С��12 �� ��Ч ;"*/g_sLangTxt_SCLCompare_ProModDescription23.GetString(),
							strIEDMSG.GetString(),strAccessPoint.GetString() ,
							strLDevice.GetString() ,strRptName.GetString() ,strMax.GetString());
						strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyRptEnabled->Row(),pTinyRptEnabled->Column()*/ );
						AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
					}
				} 
				else
				{
					/*strErrorText = "��IED(";
					strErrorText += strIEDMSG;
					strErrorText.AppendFormat(")�� AccessPoint(%s)��, LDevice(%s)������ ������ƿ�(%s)��RptEnabled ����δ��ʼ�� ;",
						strAccessPoint.GetString() ,
						strLDevice.GetString() ,strRptName.GetString() );*/
					FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)��, LDevice(%s)������ ������ƿ�(%s)��RptEnabled ����δ��ʼ�� ;"*/g_sLangTxt_SCLCompare_ProModDescription24.GetString(),
							strIEDMSG.GetString(),strAccessPoint.GetString() ,
						strLDevice.GetString() ,strRptName.GetString());
					strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyReportCtrl->Row(),pTinyReportCtrl->Column()*/ );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}
		}

		pTinyReportCtrl = pTinyReportCtrl.next_sibling();
	}
}

void CSclProjAppModelCheckTool::GetDataSetName(xpugi::xml_node pTinyLN0Node ,std::list<CString> &list_DataSetName)
{
	if (pTinyLN0Node == NULL)
	{
		return;
	}

	xpugi::xml_node pTinyDataSet = pTinyLN0Node.child("DataSet");
	while(pTinyDataSet != NULL)
	{
		if (strcmp(pTinyDataSet.name() ,"DataSet") == 0)
		{
			list_DataSetName.push_back(CString(pTinyDataSet.attribute("name").value()));
		}

		pTinyDataSet = pTinyDataSet.next_sibling();
	}
}

void CSclProjAppModelCheckTool::CheckInputsExtRef(xpugi::xml_node pTinyLN0Node ,xpugi::xml_node pTinyLDNode ,std::map<CString ,xpugi::xml_node> *mapLNFullName ,CString strLDevice ,CString strAccessPoint ,
											 CString strIEDMSG ,CProjAppModelChecks *pProjAppModelChecks )
{
	if (pTinyLN0Node == NULL)
	{
		return;
	}

	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	CString  strObjectID;
	CString strErrorPos;
	CString strIEDPath;

	xpugi::xml_node pTinyInputs = pTinyLN0Node.child("Inputs");
	xpugi::xml_node pTinyExtRef;

	while(pTinyInputs != NULL)
	{
		if (strcmp(pTinyInputs.name(),"Inputs") == 0)
		{
			pTinyExtRef = pTinyInputs.first_child();

			while(pTinyExtRef != NULL)
			{
				CheckIntAddrOfExRef(pTinyExtRef ,pTinyExtRef.attribute("intAddr").value() ,mapLNFullName ,strLDevice ,strAccessPoint ,strIEDMSG ,pProjAppModelChecks);

				pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("Inputs-ExtAddr");

				if (BeCheckThisObject(pCheckObject ,strObjectID))
				{
					CString strName = pTinyExtRef.attribute("iedName").value();
					CExBaseList *pIED = (CExBaseList *)m_oTinySCLStation.FindByID(strName);

					if (pIED == NULL)
					{
						/*strErrorText = "��IED(";
						strErrorText += strIEDMSG;
						strErrorText.AppendFormat(")�� AccessPoint(%s)�µ� LDevice(%s)��inputs �������ⲿ iedName(%s)������;",
							strAccessPoint.GetString() ,strLDevice.GetString() ,strName.GetString() );*/
						FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)�µ� LDevice(%s)��inputs �������ⲿ iedName(%s)������;"*/g_sLangTxt_SCLCompare_ProModDescription25.GetString(),
							strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString() ,strName.GetString());
						strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyExtRef->Row(),pTinyExtRef->Column()*/ );
						AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
					} 
					else
					{
						strName = pTinyExtRef.attribute("ldInst").value();
						CExBaseList *pLDevice = (CExBaseList *)pIED->FindByID(strName);

						if (pLDevice == NULL)
						{
							/*strErrorText = "��IED(";
							strErrorText += strIEDMSG;
							strErrorText.AppendFormat(")�� AccessPoint(%s)�µ� LDevice(%s)��inputs �������ⲿIED(%s)�� ldInst(%s)������;",
								strAccessPoint.GetString() ,strLDevice.GetString() ,pIED->m_strName.GetString() , strName.GetString() );*/
							FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)�µ� LDevice(%s)��inputs �������ⲿIED(%s)�� ldInst(%s)������;"*/g_sLangTxt_SCLCompare_ProModDescription26.GetString(),
								strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString() ,pIED->m_strName.GetString() , strName.GetString() );
							strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyExtRef->Row(),pTinyExtRef->Column()*/ );
							AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
						} 
						else
						{
							strIEDPath = strName;
							strIEDPath += '/';
							strIEDPath += pTinyExtRef.attribute("prefix").value();
							strIEDPath += pTinyExtRef.attribute("lnClass").value();
							strIEDPath += pTinyExtRef.attribute("lnInst").value();
							strIEDPath += '.';
							strIEDPath += pTinyExtRef.attribute("doName").value();
							strName = pTinyExtRef.attribute("daName").value();

							if (!strName.IsEmpty())
							{
								strIEDPath += '.';
								strIEDPath += strName;
							}
							CTinyExtRef *pExtRef = (CTinyExtRef *)pLDevice->FindByID(strIEDPath);

							if (pExtRef == NULL)
							{
								/*strErrorText = "��IED(";
								strErrorText += strIEDMSG;
								strErrorText.AppendFormat(")�� AccessPoint(%s)�µ� LDevice(%s)��inputs �������ⲿ IED(%s)��ͨ��·��(%s)������;",
									strAccessPoint.GetString() ,strLDevice.GetString() ,pIED->m_strName.GetString() ,strIEDPath.GetString() );*/
								FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)�µ� LDevice(%s)��inputs �������ⲿ IED(%s)��ͨ��·��(%s)������;"*/g_sLangTxt_SCLCompare_ProModDescription27.GetString(),
									strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString() ,pIED->m_strName.GetString() ,strIEDPath.GetString());
								strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyExtRef->Row(),pTinyExtRef->Column() */);
								AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
							} 
						}
					}
				}
				pTinyExtRef = pTinyExtRef.next_sibling();
			}
		}

		pTinyInputs = pTinyInputs.next_sibling();
	}

}

void CSclProjAppModelCheckTool::CheckIntAddrOfExRef(xpugi::xml_node pTinyExtRef,CString strIntAddr ,std::map<CString ,xpugi::xml_node> *mapLNFullName ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,
											   CProjAppModelChecks *pProjAppModelChecks)
{
	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	CString  strObjectID;
	CString strErrorPos;

	CString strPort,strIntPath = strIntAddr;
	long nIndex = strIntAddr.Find(':');

	pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("physConn-InPort");
 	if (nIndex != -1)
 	{
 		strPort = strIntAddr.Left(nIndex);
 		strIntPath = strIntAddr.Mid(nIndex + 1);
 
 		if (BeCheckThisObject(pCheckObject ,strObjectID))
 		{
 			if (!CheckPortNameValid(strPort))
 			{
 				/*strErrorText = "��IED(";
 				strErrorText += strIEDMSG;
 				strErrorText.AppendFormat(")�� AccessPoint(%s)�µ� LDevice(%s)��inputs �������ⲿ����intAddr(%s)������˶˿ڵ�������Ϣ��ʽ���� ;",
 					strAccessPoint.GetString() ,strLDevice.GetString() ,strIntAddr.GetString() );*/
 				FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)�µ� LDevice(%s)��inputs �������ⲿ����intAddr(%s)������˶˿ڵ�������Ϣ��ʽ���� ;"*/g_sLangTxt_SCLCompare_ProModDescription28.GetString(),
 					strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString() ,strIntAddr.GetString());
 				strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyExtRef->Row(),pTinyExtRef->Column()*/ );
 				AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
 			}
 		}
 	}
 	else if (BeCheckThisObject(pCheckObject ,strObjectID))
 	{
 		/*strErrorText = "��IED(";
 		strErrorText += strIEDMSG;
 		strErrorText.AppendFormat(")�� AccessPoint(%s)�µ� LDevice(%s)��inputs �������ⲿ����intAddr(%s)��ȱ������˶˿ڵ�������Ϣ ;",
 			strAccessPoint.GetString() ,strLDevice.GetString() ,strIntAddr.GetString() );*/
 		FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)�µ� LDevice(%s)��inputs �������ⲿ����intAddr(%s)��ȱ������˶˿ڵ�������Ϣ ;"*/g_sLangTxt_SCLCompare_ProModDescription29.GetString(),
 					strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString() ,strIntAddr.GetString());
 		strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyExtRef->Row(),pTinyExtRef->Column() */);
 		AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
 	}
 
 	pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("Inputs-intAddr");
 
 	if (BeCheckThisObject(pCheckObject ,strObjectID))
 	{
 		nIndex = strIntPath.Find('/');
 		strIntPath = strIntPath.Mid(nIndex + 1);
 		nIndex = strIntPath.Find('.');
 		CString strLNName = strIntPath.Left(nIndex);
 		strIntPath = strIntPath.Mid(nIndex + 1);
 		std::map<CString ,xpugi::xml_node>::iterator iterLNFullName;
 		iterLNFullName = mapLNFullName->find(strLNName);
 
 		xpugi::xml_node pTinyLNNode;
 		xpugi::xml_node pTinyDOI;
 		xpugi::xml_node pTinySDI;
 
 		if (iterLNFullName == mapLNFullName->end())
 		{
 			/*strErrorText = "��IED(";
 			strErrorText += strIEDMSG;
 			strErrorText.AppendFormat(")�� AccessPoint(%s)�µ� LDevice(%s)��inputs �������ⲿ����intAddr(%s)δ�ҵ���Ӧʵ����LN�ڵ�(%s);",
 				strAccessPoint.GetString() ,strLDevice.GetString() ,strIntAddr.GetString() ,strLNName.GetString() );*/
 			FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)�µ� LDevice(%s)��inputs �������ⲿ����intAddr(%s)δ�ҵ���Ӧʵ����LN�ڵ�(%s);"*/g_sLangTxt_SCLCompare_ProModDescription30.GetString(),
 					strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString() ,strIntAddr.GetString() ,strLNName.GetString());
 			strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyExtRef->Row(),pTinyExtRef->Column()*/ );
 			AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
 		} 
 		else
 		{
 			pTinyLNNode = iterLNFullName->second;
 			nIndex = strIntPath.Find('.');
 			CString strDOName = strIntPath;
 
 			if (nIndex != -1)
 			{
 				strDOName = strIntPath.Left(nIndex);
 				strIntPath = strIntPath.Mid(nIndex + 1);
 			}
 
 			if (!FindTinyChildAttrValue(pTinyLNNode ,&pTinyDOI ,"name" ,strDOName))
 			{
 				/*strErrorText = "��IED(";
 				strErrorText += strIEDMSG;
 				strErrorText.AppendFormat(")�� AccessPoint(%s)�µ� LDevice(%s)��inputs �������ⲿ����intAddr(%s)δ�ҵ���Ӧʵ����DOI name =(%s);",
 					strAccessPoint.GetString() ,strLDevice.GetString() ,
 					strIntAddr.GetString() ,strDOName.GetString() );*/
 				FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)�µ� LDevice(%s)��inputs �������ⲿ����intAddr(%s)δ�ҵ���Ӧʵ����DOI name =(%s);"*/g_sLangTxt_SCLCompare_ProModDescription31.GetString(),
 					strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString() ,
 					strIntAddr.GetString() ,strDOName.GetString() );
 				strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyLNNode->Row(),pTinyLNNode->Column() */);
 				AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
 			}
 			else if (nIndex != -1)
 			{
 				nIndex = strIntPath.Find('.');
 				strDOName = strIntPath;
 
 				if (nIndex != -1)
 				{
 					strDOName = strIntPath.Left(nIndex);
 					strIntPath = strIntPath.Mid(nIndex + 1);
 				}
 
 				if (!FindTinyChildAttrValue(pTinyDOI ,&pTinySDI ,"name" ,strDOName))
 				{
 					/*strErrorText = "��IED(";
 					strErrorText += strIEDMSG;
 					strErrorText.AppendFormat(")�� AccessPoint(%s)�µ� LDevice(%s)��inputs �������ⲿ����intAddr(%s)δ�ҵ���Ӧʵ����SDI �� DAI name =(%s);",
 						strAccessPoint.GetString() ,strLDevice.GetString() ,
 						strIntAddr.GetString() ,strDOName.GetString() );*/
 					FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)�µ� LDevice(%s)��inputs �������ⲿ����intAddr(%s)δ�ҵ���Ӧʵ����SDI �� DAI name =(%s);"*/g_sLangTxt_SCLCompare_ProModDescription32.GetString(),
 						strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString() ,
 						strIntAddr.GetString() ,strDOName.GetString());
 					strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyDOI->Row(),pTinyDOI->Column() */);
 					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
 				}
 				else if (nIndex != -1)
 				{
 					xpugi::xml_node pTinyDAI;
 					if (!FindTinyChildAttrValue(pTinySDI ,&pTinyDAI ,"name" ,strIntPath))
 					{
 						/*strErrorText = "��IED(";
 						strErrorText += strIEDMSG;
 						strErrorText.AppendFormat(")�� AccessPoint(%s)�µ� LDevice(%s)��inputs �������ⲿ����intAddr(%s)δ�ҵ���Ӧʵ����DAI �� DAI name =(%s);",
 							strAccessPoint.GetString() ,strLDevice.GetString() ,
 							strIntAddr.GetString() ,strIntPath.GetString() );*/
 						FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)�µ� LDevice(%s)��inputs �������ⲿ����intAddr(%s)δ�ҵ���Ӧʵ����DAI �� DAI name =(%s);"*/g_sLangTxt_SCLCompare_ProModDescription33.GetString(),
 							strIEDMSG.GetString(), strAccessPoint.GetString() ,strLDevice.GetString() ,
 							strIntAddr.GetString() ,strIntPath.GetString() );
 						strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyDAI->Row(),pTinyDAI->Column()*/ );
 						AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
 					}
 				}
 			}
 
 		}
 	}
}

BOOL CSclProjAppModelCheckTool::FindTinyChildAttrValue(xpugi::xml_node pTinyElement ,xpugi::xml_node *pTinyChild ,CString strAttrName ,CString strChildAttrValue)
{
	*pTinyChild = pTinyElement.first_child();

	while((*pTinyChild) != NULL)
	{
		if ((*pTinyChild).type() != xpugi::node_comment)//TINYXML_COMMENT
		{
			const char* pTmp = (*pTinyChild).attribute(strAttrName.GetString()).value();

			if (pTmp != NULL)
			{
				if (strcmp(pTmp , strChildAttrValue.GetString()) == 0)
				{
					break;
				}
			}
		}

		*pTinyChild = (*pTinyChild).next_sibling();
	}
	return (*pTinyChild) != NULL;
}

BOOL CSclProjAppModelCheckTool::CheckPortNameValid(CString strPortName)
{
	if (strPortName.IsEmpty())
	{
		return FALSE;
	} 
	else
	{
		int nIndex = strPortName.GetLength();
		nIndex = strPortName.Find('-');

		if (nIndex == -1)
		{
			return FALSE;
		}

		CString strBoardNum = strPortName.Left(nIndex);
		CString strPortNum = strPortName.Mid(nIndex+1);

		if (strBoardNum.IsEmpty()||strPortNum.IsEmpty())
		{
			return FALSE;
		}

		int nCount = 0;
		nIndex = strBoardNum.GetLength();
		for(nCount = 0;nCount < nIndex;nCount++)
		{
			if ((strBoardNum[nCount]<'0')||(strBoardNum[nCount]>'9'))
			{
				return FALSE;
			}
		}

		nIndex = strPortNum.GetLength();
		for(nCount = 0;nCount < nIndex;nCount++)
		{
			if ((strPortNum[nCount]<'A')||(strPortNum[nCount]>'Z'))
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

void CSclProjAppModelCheckTool::CheckDataSetRelated(xpugi::xml_node pTinyLNNode ,xpugi::xml_node pTinyLDNode ,std::map<CString ,xpugi::xml_node> *mapLNFullName ,CString strLDevice ,
											   CString strAccessPoint ,CString strIEDMSG ,CProjAppModelChecks *pProjAppModelChecks ,long &nCurDataSetNum)
{
	if (pTinyLNNode == NULL)
	{
		return;
	}

	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	CString  strObjectID;
	CString strErrorPos;
	CString strFCDAPath;
	CString strSecond;
	CString strLdInst;
	CString strDaName;
	CString strMsg;

	long nIndex = 0;

	std::map<CString ,CString> mapFCDA ,mapFCDALog;
	std::map<CString ,CString>::iterator iterFCDA ,iterFCDALog;

	xpugi::xml_node pTinyDataSetNode = pTinyLNNode.child("DataSet");
	xpugi::xml_node pTinyFCDANode;
	CString strDataSetName ,strDataSetNameNew;

	pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("LD-desc");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		CString strLDdesc;
		strLDdesc = pTinyLDNode.attribute("desc").value();

		if (strLDdesc.IsEmpty())
		{
			/*strErrorText = "��IED(";
			strErrorText += strIEDMSG;
			strErrorText.AppendFormat(")�� AccessPoint(%s)�µ� LDevice(%s)�� desc ����Ϊ�� ,�����ϱ�׼Ҫ��;",
				strAccessPoint.GetString() ,strLDevice.GetString());*/
			FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)�µ� LDevice(%s)�� desc ����Ϊ�� ,�����ϱ�׼Ҫ��;"*/g_sLangTxt_SCLCompare_ProModDescription34.GetString(),
							strIEDMSG.GetString(), strAccessPoint.GetString() ,strLDevice.GetString());
			strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyLDNode->Row(),pTinyLDNode->Column()*/ );
			AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
		}
	}

	mapFCDA.clear();
	mapFCDALog.clear();

	while(pTinyDataSetNode != NULL)
	{
		if (strcmp(pTinyDataSetNode.name() , "DataSet") != 0)
		{
			pTinyDataSetNode = pTinyDataSetNode.next_sibling();
			continue;
		}
		nCurDataSetNum++;

		strDataSetName = pTinyDataSetNode.attribute("name").value();
		strDataSetNameNew = strDataSetName;
		DelTailDigtal(&strDataSetNameNew);
		pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("DataSet-Name");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{
			if ((strDataSetNameNew!="dsAin")&&(strDataSetNameNew!="dsDin")&&(strDataSetNameNew!="dsInterLock")&&(strDataSetNameNew!="dsAlarm")&&(strDataSetNameNew!="dsWarning")&&(strDataSetNameNew!="dsCommState")&&
				(strDataSetNameNew!="dsParameter")&&(strDataSetNameNew!="dsGOOSE")&&(strDataSetNameNew!="dsTripInfo")&&(strDataSetNameNew!="dsRelayDin")&&(strDataSetNameNew!="dsRelayEna")&&(strDataSetNameNew!="dsRelayRec")&&
				(strDataSetNameNew!="dsRelayAin")&&(strDataSetNameNew!="dsDeviceState")&&(strDataSetNameNew!="dsRelayState")&&(strDataSetNameNew!="dsRelayBlk")&&(strDataSetNameNew!="dsRelayFunEn")&&(strDataSetNameNew!="dsSetGrpNum")&&
				(strDataSetNameNew!="dsSetting")&&(strDataSetNameNew!="dsSV")&&(strDataSetNameNew!="dsLog")&&(strDataSetNameNew!="dsRtFre")&&(strDataSetNameNew!="dsRtMMXU")&&(strDataSetNameNew!="dsRtMSQI")&&(strDataSetNameNew!="dsRtHarm")
				&&(strDataSetNameNew!="dsRtIHarm")&&(strDataSetNameNew!="dsStMMXU")&&(strDataSetNameNew!="dsStMSQI")&&(strDataSetNameNew!="dsStHarm")&&(strDataSetNameNew!="dsStIHarm")&&(strDataSetNameNew!="dsPST")
				&&(strDataSetNameNew!="dsPLT")&&(strDataSetNameNew!="dsFluc")&&(strDataSetNameNew!="dsMMTR")&&(strDataSetNameNew!="dsEveQFVR")&&(strDataSetNameNew!="dsEveQIUB")&&(strDataSetNameNew!="dsEveQVUB")
				&&(strDataSetNameNew!="dsEveQVVR")&&(strDataSetNameNew!="dsEveRDRE")&&(strDataSetNameNew!="dsEveQVTR")&&(strDataSetNameNew!="dsEveQITR")&&(strDataSetNameNew!="dsDevice"))
			{
				/*strErrorText = "��IED(";
				strErrorText += strIEDMSG;
				strErrorText.AppendFormat(")�� AccessPoint(%s)�µ� LDevice(%s)��DataSet(%s)����������Q/GDW 1396�е�8.3.1;",
					strAccessPoint.GetString() ,strLDevice.GetString() ,strDataSetName.GetString());*/
				FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)�µ� LDevice(%s)��DataSet(%s)����������Q/GDW 1396�е�8.3.1;"*/g_sLangTxt_SCLCompare_ProModDescription35.GetString(),
							strIEDMSG.GetString(), strAccessPoint.GetString() ,strLDevice.GetString() ,strDataSetName.GetString());
				strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyDataSetNode->Row(),pTinyDataSetNode->Column()*/ );
				AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
			}
		}

		pTinyFCDANode = pTinyDataSetNode.child("FCDA");

		nIndex = 0;

		while(pTinyFCDANode != NULL)
		{
			if (pTinyFCDANode.type() == xpugi::node_comment)//TINYXML_COMMENT
			{
				pTinyFCDANode = pTinyFCDANode.next_sibling();
				continue;
			}

			nIndex++;
			strSecond.Format(/*"���ݼ�:%s ,���%d"*/g_sLangTxt_SCLCompare_ProModDescription71.GetString() ,strDataSetName.GetString() ,nIndex);

			/*strMsg = "��IED(";
			strMsg += strIEDMSG;
			strMsg.AppendFormat(")�� AccessPoint(%s)�µ� LDevice(%s)��",strAccessPoint.GetString() ,strLDevice.GetString());
			strMsg += strSecond;*/
			FormatString(strMsg,/*"��IED(%s)�� AccessPoint(%s)�µ� LDevice(%s)��%s"*/g_sLangTxt_SCLCompare_ProModDescription72.GetString(),
				strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString(),strSecond.GetString());
			CheckFCDARefValid(pTinyFCDANode ,mapLNFullName, strMsg, strLdInst, strDaName, strFCDAPath,strDataSetNameNew, pProjAppModelChecks);

			if (strDataSetNameNew == "dsLog")
			{
				iterFCDALog = mapFCDALog.find(strFCDAPath);

				if (iterFCDALog != mapFCDALog.end())
				{
					pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("FCDA-Unique");

					if (BeCheckThisObject(pCheckObject ,strObjectID))
					{
						/*strErrorText = "��IED(";
						strErrorText += strIEDMSG;
						strErrorText.AppendFormat(")�� AccessPoint(%s)�µ� LDevice(%s)�� %s FCDA·��(%s)�� %s �ظ� ;",
							strAccessPoint.GetString() ,strLDevice.GetString() ,strSecond.GetString() ,
							strFCDAPath,iterFCDALog->second );*/
						FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)�µ� LDevice(%s)�� %s FCDA·��(%s)�� %s �ظ� ;"*/g_sLangTxt_SCLCompare_ProModDescription36.GetString(),
							strIEDMSG.GetString(), strAccessPoint.GetString() ,strLDevice.GetString() ,strSecond.GetString() ,
							strFCDAPath,iterFCDALog->second );
						strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyFCDANode->Row(),pTinyFCDANode->Column()*/ );
						AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
					}
				} 
				else
				{
					mapFCDALog.insert(std::make_pair(strFCDAPath ,strSecond));
				}
			} 
			else
			{
				iterFCDA = mapFCDA.find(strFCDAPath);

				if (iterFCDA != mapFCDA.end())
				{
					pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("FCDA-Unique");

					if (BeCheckThisObject(pCheckObject ,strObjectID))
					{
						/*strErrorText = "��IED(";
						strErrorText += strIEDMSG;
						strErrorText.AppendFormat(")�� AccessPoint(%s)�µ� LDevice(%s)�� %s FCDA·��(%s)�� %s �ظ� ;",
							strAccessPoint.GetString() ,strLDevice.GetString() ,strSecond.GetString() ,strFCDAPath.GetString(),iterFCDA->second );*/
						FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)�µ� LDevice(%s)�� %s FCDA·��(%s)�� %s �ظ� ;"*/g_sLangTxt_SCLCompare_ProModDescription36.GetString(),
							strIEDMSG.GetString(), strAccessPoint.GetString() ,strLDevice.GetString() ,strSecond.GetString() ,strFCDAPath.GetString(),iterFCDA->second );
						strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyFCDANode->Row(),pTinyFCDANode->Column()*/ );
						AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
					}
				} 
				else
				{
					mapFCDA.insert(std::make_pair(strFCDAPath ,strSecond));
				}
			}

			pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("FCDA-FCD");

			if (BeCheckThisObject(pCheckObject ,strObjectID))
			{
				if ((strDataSetNameNew == "dsGOOSE")&&(strDaName.IsEmpty()))
				{
					/*strErrorText = "��IED(";
					strErrorText += strIEDMSG;
					strErrorText.AppendFormat(")�� AccessPoint(%s)�µ� LDevice(%s)�� %s FCDA·��(%s)������daName ,������dsGOOSE���ݼ����� ;"
						,strAccessPoint.GetString() ,strLDevice.GetString() ,strSecond.GetString() ,strFCDAPath.GetString());*/
					FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)�µ� LDevice(%s)�� %s FCDA·��(%s)������daName ,������dsGOOSE���ݼ����� ;"*/g_sLangTxt_SCLCompare_ProModDescription37.GetString(),
							strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString() ,strSecond.GetString() ,strFCDAPath.GetString());	
					strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyFCDANode->Row(),pTinyFCDANode->Column()*/ );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
				else if ((strDataSetNameNew != "dsGOOSE")&&(!strDaName.IsEmpty()))
				{
					/*strErrorText = "��IED(";
					strErrorText += strIEDMSG;
					strErrorText.AppendFormat(")�� AccessPoint(%s)�µ� LDevice(%s)�� %s FCDA·��(%s)����daName ,�����Ϸ�dsGOOSE���ݼ����� ;",
						strAccessPoint.GetString() ,strLDevice.GetString() ,strSecond.GetString() ,strFCDAPath.GetString());*/
					FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)�µ� LDevice(%s)�� %s FCDA·��(%s)����daName ,�����Ϸ�dsGOOSE���ݼ����� ;"*/g_sLangTxt_SCLCompare_ProModDescription38.GetString(),
							strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString() ,strSecond.GetString() ,strFCDAPath.GetString());
					strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyFCDANode->Row(),pTinyFCDANode->Column() */);
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}

			pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("FCDA-LdInst");

			if (BeCheckThisObject(pCheckObject ,strObjectID))
			{
				if (strLdInst != strLDevice)
				{
					/*strErrorText = "��IED(";
					strErrorText += strIEDMSG;
					strErrorText.AppendFormat(")�� AccessPoint(%s) �µ� LDevice(%s) �� %s FCDA·��(%s) ��LD�����ϱ�׼Ҫ�� ;",
						strIEDMSG.GetString() ,strAccessPoint.GetString() ,strLDevice.GetString() ,strSecond.GetString() ,strFCDAPath.GetString());*/
					FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s) �µ� LDevice(%s) �� %s FCDA·��(%s) ��LD�����ϱ�׼Ҫ�� ;"*/g_sLangTxt_SCLCompare_ProModDescription39.GetString(),
							strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString() ,strSecond.GetString() ,strFCDAPath.GetString());
					strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyFCDANode->Row(),pTinyFCDANode->Column()*/ );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}

			pTinyFCDANode = pTinyFCDANode.next_sibling();
		}

		if (nIndex > 256)
		{
			pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("FCDA-Number");

			if (BeCheckThisObject(pCheckObject ,strObjectID))
			{
				/*strErrorText = "��IED(";
				strErrorText += strIEDMSG;
				strErrorText.AppendFormat(")�� AccessPoint(%s) �µ� LDevice(%s) �����ݼ� %s �����ݼ���Ա %ld��, ���峬����256�� ;",
					strAccessPoint.GetString() ,strLDevice.GetString() ,strDataSetName.GetString() ,nIndex);*/
				FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s) �µ� LDevice(%s) �����ݼ� %s �����ݼ���Ա %ld��, ���峬����256�� ;"*/g_sLangTxt_SCLCompare_ProModDescription40.GetString(),
							strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString() ,strDataSetName.GetString() ,nIndex);
				strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyDataSetNode->Row(),pTinyDataSetNode->Column()*/ );
				AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
			}
		}

		pTinyDataSetNode = pTinyDataSetNode.next_sibling();
	}

	mapFCDA.clear();
	mapFCDALog.clear();
}

void CSclProjAppModelCheckTool::CheckFCDARefValid(xpugi::xml_node pTinyFCDANode , std::map<CString ,xpugi::xml_node> *mapLNFullName ,CString strMsg ,CString &strLdInst, CString &strDaName, CString &strFCDAPath, 
											 CString strDataSetNameNew , CProjAppModelChecks *pProjAppModelChecks)
{
	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	CString  strObjectID;
	CString strErrorPos;

	CString strLnFullName;
	CString strDOName;
	CString strSDOName;
	std::map<CString ,xpugi::xml_node>::iterator iterLNFullName;

	xpugi::xml_node pTinyLNNode;
	xpugi::xml_node pTinyDOI;
	xpugi::xml_node pTinySDO;
	xpugi::xml_node pTinyDAI;

	strLdInst = pTinyFCDANode.attribute("ldInst").value();
	strDaName = pTinyFCDANode.attribute("daName").value();

	strFCDAPath = strLdInst;
	strFCDAPath += "/";
	strLnFullName = pTinyFCDANode.attribute("prefix").value();
	strLnFullName += pTinyFCDANode.attribute("lnClass").value();
	strLnFullName += pTinyFCDANode.attribute("lnInst").value();
	strFCDAPath += strLnFullName;
	strFCDAPath += "$";
	strFCDAPath += pTinyFCDANode.attribute("fc").value();
	strFCDAPath += "$";
	strDOName = pTinyFCDANode.attribute("doName").value();
	strFCDAPath += strDOName;

	if (!strDaName.IsEmpty())
	{
		strFCDAPath += ".";
		strFCDAPath += strDaName;
	}

	GetSDOFromDoName(strDOName ,strSDOName );

	pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("FCDA-RefValid");

	iterLNFullName = mapLNFullName->find(strLnFullName);

	if (iterLNFullName != mapLNFullName->end())
	{
		pTinyLNNode = iterLNFullName->second;

		if (!FindTinyChildAttrValue(pTinyLNNode ,&pTinyDOI ,"name" ,strDOName))
		{
			if (BeCheckThisObject(pCheckObject ,strObjectID))
			{
				/*strErrorText = strMsg;
				strErrorText.AppendFormat("��FCDA·��(%s),����DO name =(%s)δʵ����;", 
					strFCDAPath.GetString() ,strDOName.GetString());*/
				FormatString(strErrorText,/*"%s��FCDA·��(%s),����DO name =(%s)δʵ����;"*/g_sLangTxt_SCLCompare_ProModDescription41.GetString(),
							strMsg.GetString(),strFCDAPath.GetString() ,strDOName.GetString());
				strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyLNNode->Row(),pTinyLNNode->Column()*/ );
				AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
			}
		}
		else
		{
			if (!strSDOName.IsEmpty())
			{
				if ((!FindTinyChildAttrValue(pTinyDOI ,&pTinySDO ,"name" ,strSDOName))&&(BeCheckThisObject(pCheckObject ,strObjectID)))
				{
					/*strErrorText = strMsg;
					strErrorText.AppendFormat("��FCDA·��(%s),����SDO name =(%s)δʵ����;",
						strFCDAPath.GetString(),strSDOName.GetString());*/
					FormatString(strErrorText,/*"%s��FCDA·��(%s),����SDO name =(%s)δʵ����;"*/g_sLangTxt_SCLCompare_ProModDescription42.GetString(),
							strMsg.GetString(),strFCDAPath.GetString(),strSDOName.GetString());
					strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyDOI->Row(),pTinyDOI->Column() */);
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}
			else
			{
				pTinySDO = pTinyDOI;
			}

			if ((!strDaName.IsEmpty())&&(pTinySDO != NULL))
			{
				if ((!FindTinyChildAttrValue(pTinySDO ,&pTinyDAI ,"name" ,strDaName))&&(BeCheckThisObject(pCheckObject ,strObjectID)))
				{
					/*strErrorText = strMsg;
					strErrorText.AppendFormat("��FCDA·��(%s),����DA name =(%s)δʵ����;", 
						strFCDAPath.GetString() ,strDaName.GetString());*/
					FormatString(strErrorText,/*"%s��FCDA·��(%s),����DA name =(%s)δʵ����;"*/g_sLangTxt_SCLCompare_ProModDescription43.GetString(),
							strMsg.GetString(),strFCDAPath.GetString() ,strDaName.GetString());
					strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinySDO->Row(),pTinySDO->Column()*/ );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}

			if (strDataSetNameNew == "dsRelayEna")//��鱣��ѹ�����ݵ�ctlModel,sboTimeout��ֵ��ʼ�����
			{
				CheckRelayEnaInit(pTinyDOI ,strMsg ,strFCDAPath ,pProjAppModelChecks);
			}
		}
	} 
	else if(BeCheckThisObject(pCheckObject ,strObjectID))
	{
		/*strErrorText = strMsg;
		strErrorText.AppendFormat("��FCDA·��(%s),����LN =(%s)δʵ����;",
			 strFCDAPath.GetString() ,strLnFullName.GetString());*/
		FormatString(strErrorText,/*"%s��FCDA·��(%s),����LN =(%s)δʵ����;"*/g_sLangTxt_SCLCompare_ProModDescription44.GetString(),
							strMsg.GetString(),strFCDAPath.GetString() ,strLnFullName.GetString());
		strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyFCDANode->Row(),pTinyFCDANode->Column()*/ );
		AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
	}

	pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("LN-DOIdesc");

	if(BeCheckThisObject(pCheckObject ,strObjectID))
	{
		CString strDesc,strDescNew;
		if (pTinyLNNode != NULL)
		{
			strDesc = pTinyLNNode.attribute("desc").value();

			if (strDesc.IsEmpty())
			{
				/*strErrorText = strMsg;
				strErrorText.AppendFormat("��FCDA·��(%s),����LN =(%s)��desc ����Ϊ��;",
					strFCDAPath.GetString() ,strLnFullName.GetString());*/
				FormatString(strErrorText,/*"%s��FCDA·��(%s),����LN =(%s)��desc ����Ϊ��;"*/g_sLangTxt_SCLCompare_ProModDescription45.GetString(),
							strMsg.GetString(),strFCDAPath.GetString() ,strLnFullName.GetString());
				strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyLNNode->Row(),pTinyLNNode->Column()*/ );
				AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
			}

			if (pTinyDOI != NULL)
			{
				strDesc = pTinyDOI.attribute("desc").value();

				if (strDesc.IsEmpty())
				{
					/*strErrorText = strMsg;
					strErrorText.AppendFormat("��FCDA·��(%s),����DOI name =(%s)��desc ����Ϊ��;",
						 strFCDAPath.GetString() ,strDOName.GetString());*/
					FormatString(strErrorText,/*"%s��FCDA·��(%s),����DOI name =(%s)��desc ����Ϊ��;"*/g_sLangTxt_SCLCompare_ProModDescription46.GetString(),
							strMsg.GetString(),strFCDAPath.GetString() ,strDOName.GetString());
					strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyDOI->Row(),pTinyDOI->Column()*/ );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}

				if (FindTinyChildAttrValue(pTinySDO ,&pTinyDAI ,"name" ,"dU" ))
				{
					pTinyDAI = pTinyDAI.first_child();

					if (pTinyDAI == NULL)
					{
						/*strErrorText = strMsg;
						strErrorText.AppendFormat("��FCDA·��(%s),����DOI name =(%s)�µ�dU δ����Val�ӽڵ�;", 
							 strFCDAPath.GetString() ,strDOName.GetString());*/
						FormatString(strErrorText,/*"%s��FCDA·��(%s),����DOI name =(%s)�µ�dU δ����Val�ӽڵ�;"*/g_sLangTxt_SCLCompare_ProModDescription47.GetString(),
							strMsg.GetString(),strFCDAPath.GetString() ,strDOName.GetString());
						strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinySDO->Row(),pTinySDO->Column() */);
						AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
					} 
					else
					{
						strDesc = pTinyDAI.first_child().value();

						//UTF8ToMultiByte(strDesc);
						utf8_to_gbk(strDesc,strDescNew);
						strDesc = strDescNew;

						if (strDesc.IsEmpty())
						{
							/*strErrorText = strMsg;
							strErrorText.AppendFormat("��FCDA·��(%s),����dU ��ֵΪ��;",strFCDAPath.GetString() );*/
							FormatString(strErrorText,/*"%s��FCDA·��(%s),����dU ��ֵΪ��;"*/g_sLangTxt_SCLCompare_ProModDescription48.GetString(),
								strMsg.GetString(),strFCDAPath.GetString());
							strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyDAI->Row(),pTinyDAI->Column() */);
							AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
						}
					}
				} 
				else
				{
					/*strErrorText = strMsg;
					strErrorText.AppendFormat("��FCDA·��(%s),������dU δʵ����;", strFCDAPath.GetString());*/
					FormatString(strErrorText,/*"%s��FCDA·��(%s),������dU δʵ����;"*/g_sLangTxt_SCLCompare_ProModDescription49.GetString(),
						strMsg.GetString(),strFCDAPath.GetString());
					strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyFCDANode->Row(),pTinyFCDANode->Column()*/ );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			} 
		}
	}
}

CString CSclProjAppModelCheckTool::GetAttributeText(xpugi::xml_node oPugiNode,const char *pstrID)
{
	CString strText;
	xpugi::xml_node oPugiChild = oPugiNode.child(pstrID);

	if (oPugiChild == NULL)
	{
		return "";
	}

	xpugi::xml_node oPugiChildChild = oPugiChild.first_child();

	if (oPugiChildChild == NULL)
	{
		return "";
	}

	return oPugiChildChild.value();
}

void CSclProjAppModelCheckTool::CheckRelayEnaInit(xpugi::xml_node pTinyDOI ,CString strMsg ,CString strFCDAPath ,CProjAppModelChecks *pProjAppModelChecks)
{
	CString strDOName = pTinyDOI.attribute("name").value();

	if ((strDOName == "RemGoEna")||(strDOName == "RemGrpEna")||(strDOName == "RemSetEna"))
	{
		return;
	}

	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	CString  strObjectID;
	CString strErrorPos;
	xpugi::xml_node pTinyDAI;
	CString strDAIName;
	CString strCtlModel;
	CString strSboTimeOut;
	BOOL bCtlModelFind = FALSE;
	BOOL bSboTimeoutFind = FALSE;

	pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("ctlModel-sboTimeout");

	if(BeCheckThisObject(pCheckObject ,strObjectID))
	{
		pTinyDAI = pTinyDOI.first_child();

		while(pTinyDAI != NULL)
		{
			strDAIName = pTinyDAI.attribute("name").value();

			if (strcmp(strDAIName.GetString() , "ctlModel") == 0)
			{
				bCtlModelFind = TRUE;
				strCtlModel = GetAttributeText(pTinyDAI,"Val");
				if (strCtlModel.IsEmpty())
				{
					/*strErrorText = strMsg;
					strErrorText.AppendFormat("��FCDA·��(%s),��ѹ���ctlModel ���ݳ�ʼ��Ϊ��;",strFCDAPath.GetString() );*/
					FormatString(strErrorText,/*"%s��FCDA·��(%s),��ѹ���ctlModel ���ݳ�ʼ��Ϊ��;"*/g_sLangID_SCLCompare_ProModDescription50.GetString(),
						strMsg.GetString(),strFCDAPath.GetString());
					strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyDAI->Row(),pTinyDAI->Column()*/ );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
				else if ((strCtlModel!="status-only")&&(strCtlModel!="direct-with-normal-security")&&(strCtlModel!="sbo-with-normal-security")&&
					(strCtlModel!="direct-with-enhanced-security")&&(strCtlModel!="sbo-with-enhanced-security"))
				{
					/*strErrorText = strMsg;
					strErrorText.AppendFormat("��FCDA·��(%s),��ѹ���ctlModel ʵ���� ��ֵΪ %s ��ö������ֵ��һ��;",
						strFCDAPath.GetString() ,strCtlModel.GetString());*/
					FormatString(strErrorText,/*"%s��FCDA·��(%s),��ѹ���ctlModel ʵ���� ��ֵΪ %s ��ö������ֵ��һ��;"*/g_sLangTxt_SCLCompare_ProModDescription51.GetString(),
						strMsg.GetString(),strFCDAPath.GetString() ,strCtlModel.GetString());
					strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyDAI->Row(),pTinyDAI->Column()*/ );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}

			if (strcmp(strDAIName.GetString() , "sboTimeout") == 0)
			{
				bSboTimeoutFind = TRUE;
				strSboTimeOut = GetAttributeText(pTinyDAI,"Val");
				if (strSboTimeOut.IsEmpty())
				{
					/*strErrorText = strMsg;
					strErrorText.AppendFormat("��FCDA·��(%s),��ѹ���sboTimeout ���ݳ�ʼ��Ϊ��;" ,strFCDAPath.GetString() );*/
					FormatString(strErrorText,/*"%s��FCDA·��(%s),��ѹ���sboTimeout ���ݳ�ʼ��Ϊ��;"*/g_sLangTxt_SCLCompare_ProModDescription52.GetString(),
						strMsg.GetString(),strFCDAPath.GetString());
					strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyDAI->Row(),pTinyDAI->Column()*/ );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}

			pTinyDAI = pTinyDAI.next_sibling();
		}

		if (!bCtlModelFind)
		{
			/*strErrorText = strMsg;
			strErrorText.AppendFormat("��FCDA·��(%s),��ѹ���ctlModel ����δʵ����;",strFCDAPath.GetString() );*/
			FormatString(strErrorText,/*"%s��FCDA·��(%s),��ѹ���ctlModel ����δʵ����;"*/g_sLangTxt_SCLCompare_ProModDescription53.GetString(),
						strMsg.GetString(),strFCDAPath.GetString());
			strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyDOI->Row(),pTinyDOI->Column()*/ );
			AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
		}

		if (!bSboTimeoutFind)
		{
			/*strErrorText = strMsg;
			strErrorText.AppendFormat("��FCDA·��(%s),��ѹ���sboTimeout ����δʵ����;",strFCDAPath.GetString() );*/
			FormatString(strErrorText,/*"%s��FCDA·��(%s),��ѹ���sboTimeout ����δʵ����;"*/g_sLangTxt_SCLCompare_ProModDescription54.GetString(),
						strMsg.GetString(),strFCDAPath.GetString());
			strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyDOI->Row(),pTinyDOI->Column()*/ );
			AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
		}
	}
}

void CSclProjAppModelCheckTool::GetSDOFromDoName(CString &strDOName ,CString &strSDOName )
{
	long nIndex = strDOName.ReverseFind('.');

	if (nIndex != -1)
	{
		strSDOName = strDOName.Mid(nIndex+1);
		strDOName = strDOName.Left(nIndex);
	}
}

void CSclProjAppModelCheckTool::CheckDOI_SDI_DAI_RefValid(xpugi::xml_node pTinyLNNode ,xpugi::xml_node pTinyLDNode  ,CExBaseList *pTestObjectTemplates ,std::map<CString ,xpugi::xml_node> *mapLNFullName ,
													 CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,CProjAppModelChecks *pProjAppModelChecks)
{
	std::map<CString ,xpugi::xml_node>::iterator iterLNFullName;
	std::list<CString>	list_DOI;
	CString strLNFullName;

	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	CString  strObjectID;
	CString strErrorPos;
	CString strLnType;
	CString strLnClass;
	CString strDOIName;
	CString strMSGFull;

	CLNodeType *pLNodeType = NULL;
	CDOValue *pDOValue = NULL;

	xpugi::xml_node pTinyDOI;
 
 	strLNFullName = pTinyLNNode.attribute("prefix").value();
 	strLnClass = pTinyLNNode.attribute("lnClass").value();
 	strLNFullName += strLnClass;
 	strLNFullName += pTinyLNNode.attribute("inst").value();
 	iterLNFullName = mapLNFullName->find(strLNFullName);
 
 	pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("LNObject-Repeat");
 
 	if (iterLNFullName == mapLNFullName->end())
 	{
 		mapLNFullName->insert(std::make_pair(strLNFullName ,pTinyLNNode));
 	} 
 	else if (BeCheckThisObject(pCheckObject ,strObjectID))
 	{
 		/*strErrorText = "��IED(";
 		strErrorText += strIEDMSG;
 		strErrorText.AppendFormat(")�� AccessPoint (%s) �µ� LDevice (%s) ��ʵ����LN(%s)��ͻ, �����ظ�ʵ���� ;",
 			strAccessPoint.GetString() ,strLDevice.GetString() , strLNFullName.GetString());*/
 		FormatString(strErrorText,/*"��IED(%s)�� AccessPoint (%s) �µ� LDevice (%s) ��ʵ����LN(%s)��ͻ, �����ظ�ʵ���� ;"*/g_sLangTxt_SCLCompare_ProModDescription55.GetString(),
 						strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString() , strLNFullName.GetString());
 		strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyLNNode->Row(),pTinyLNNode->Column() */);
 		AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
 	}
 
 	strLnType = pTinyLNNode.attribute("lnType").value();
 	if(pTestObjectTemplates != NULL)
 	pLNodeType = (CLNodeType *)pTestObjectTemplates->FindByID(strLnType);
 
 	pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("LN-DOI-DAI-Valid");
 
 	if (BeCheckThisObject(pCheckObject ,strObjectID))
 	{
 		if (pLNodeType == NULL)
 		{
 			/*strErrorText = "��IED(";
 			strErrorText += strIEDMSG;
 			strErrorText.AppendFormat(")�� AccessPoint(%s)�µ� LDevice(%s)��ʵ����LN(%s)��lnType(%s)δ���� ;",
 				strAccessPoint.GetString() ,strLDevice.GetString() , strLNFullName.GetString() ,strLnType.GetString());*/
 			FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)�µ� LDevice(%s)��ʵ����LN(%s)��lnType(%s)δ���� ;"*/g_sLangTxt_SCLCompare_ProModDescription56.GetString(),
 						strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString() , strLNFullName.GetString() ,strLnType.GetString());
 			strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyLNNode->Row(),pTinyLNNode->Column()*/ );
 			AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
 		}
 		else if (pLNodeType->m_strLnClass != strLnClass)
 		{
 			/*strErrorText = "��IED(";
 			strErrorText += strIEDMSG;
 			strErrorText.AppendFormat(")�� AccessPoint(%s)�µ� LDevice(%s)��ʵ����LN(%s) ��lnType(%s) �����lnClass(%s) ��ʵ����������lnClass(%s)��һ��;",
 				strAccessPoint.GetString() ,strLDevice.GetString(),
 				strLNFullName.GetString() ,strLnType.GetString() ,pLNodeType->m_strLnClass.GetString() ,strLnClass.GetString());*/
 			FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s)�µ� LDevice(%s)��ʵ����LN(%s) ��lnType(%s) �����lnClass(%s) ��ʵ����������lnClass(%s)��һ��;"*/
 				g_sLangTxt_SCLCompare_ProModDescription57.GetString(),
 				strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString(),
 				strLNFullName.GetString() ,strLnType.GetString() ,pLNodeType->m_strLnClass.GetString() ,strLnClass.GetString());
 			strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyLNNode->Row(),pTinyLNNode->Column() */);
 			AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
 		}
 	}
 
 	if (pLNodeType != NULL)
 	{
 		pTinyDOI = pTinyLNNode.first_child();
 		while(pTinyDOI != NULL)
 		{
 			if (strcmp(pTinyDOI.name() , "DOI") != 0)
 			{
 				pTinyDOI = pTinyDOI.next_sibling();
 				continue;
 			}
 
 			strDOIName = pTinyDOI.attribute("name").value();
 			pDOValue = (CDOValue *)pLNodeType->FindByID(strDOIName);
 
 			pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("LN-DOI-DAI-Valid");
 
 			if ((BeCheckThisObject(pCheckObject ,strObjectID))&&(pDOValue == NULL))
 			{
 				/*strErrorText = "��IED(";
 				strErrorText += strIEDMSG;
 				strErrorText.AppendFormat(")�� AccessPoint (%s) �µ� LDevice (%s) ��ʵ����LN (%s) �µ�DOI (%s) ��lnType = (%s)��δ����;",
 					strAccessPoint.GetString(),strLDevice.GetString() , strLNFullName.GetString() ,strDOIName.GetString() ,
 					strLnType.GetString());*/
 				FormatString(strErrorText,/*"��IED(%s)�� AccessPoint (%s) �µ� LDevice (%s) ��ʵ����LN (%s) �µ�DOI (%s) ��lnType = (%s)��δ����;"*/
 					g_sLangTxt_SCLCompare_ProModDescription58.GetString(),
 					strIEDMSG.GetString(),strAccessPoint.GetString(),strLDevice.GetString() , strLNFullName.GetString() ,strDOIName.GetString() ,
 					strLnType.GetString());
 				strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyDOI->Row(),pTinyDOI->Column()*/ );
 				AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
 			}
 
 			/*strMSGFull = "��IED (";
 			strMSGFull += strIEDMSG;
 			strMSGFull.AppendFormat(")�� AccessPoint (%s) �µ� LDevice (%s) ��ʵ����LN(%s)�µ�DOI(%s)",
 				strAccessPoint.GetString() ,strLDevice.GetString() , strLNFullName.GetString() ,strDOIName.GetString());*/
 			FormatString(strMSGFull, /*"��IED(%s)�� AccessPoint (%s) �µ� LDevice (%s) ��ʵ����LN(%s)�µ�DOI(%s)"*/
 				g_sLangTxt_SCLCompare_ProModDescription59.GetString(),
 				strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString() , strLNFullName.GetString() ,strDOIName.GetString());
 			pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("LEDRs-ctlModel");
 
 			if (BeCheckThisObject(pCheckObject ,strObjectID))
 			{
 				if (strDOIName == "LEDRs")//������� �źŸ���� ctlModel �Ƿ��ʼ��
 				{
 					CString strLEDRsVal;
 					xpugi::xml_node pTinyDAI = pTinyDOI.first_child();
 
 					while(pTinyDAI != NULL)
 					{
 						if (strcmp(pTinyDAI.attribute("name").value() , "ctlModel") == 0)
 						{
 							strLEDRsVal = GetAttributeText(pTinyDAI,"Val");
 							if (strLEDRsVal.IsEmpty())
 							{
 								/*strErrorText = strMSGFull;
 								strErrorText += "��ctlModelʵ������ֵΪ��;";*/
 								FormatString(strErrorText,/*"%s��ctlModelʵ������ֵΪ��;"*/
 									g_sLangTxt_SCLCompare_ProModDescription60.GetString(),
 									strMSGFull.GetString());
 								strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyDAI->Row(),pTinyDAI->Column()*/ );
 								AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
 							}
 							else if ((strLEDRsVal!="status-only")&&(strLEDRsVal!="direct-with-normal-security")&&(strLEDRsVal!="sbo-with-normal-security")&&
 								(strLEDRsVal!="direct-with-enhanced-security")&&(strLEDRsVal!="sbo-with-enhanced-security"))
 							{
 								/*strErrorText = strMSGFull;
 								strErrorText.AppendFormat("��ctlModel ʵ���� ��ֵΪ %s ��ö������ֵ��һ��;",strLEDRsVal.GetString());*/
 								FormatString(strErrorText,/*"%s��ctlModel ʵ���� ��ֵΪ %s ��ö������ֵ��һ��;"*/
 									g_sLangTxt_SCLCompare_ProModDescription61.GetString(),
 									strMSGFull.GetString(),strLEDRsVal.GetString());
 								strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyDAI->Row(),pTinyDAI->Column()*/ );
 								AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
 							}
 							break;
 						}
 
 						pTinyDAI = pTinyDAI.next_sibling();
 					}
 
 					if (pTinyDAI == NULL)
 					{
 						/*strErrorText = strMSGFull;
 						strErrorText += "��ctlModelδʵ����;";*/
 						FormatString(strErrorText,/*"%s��ctlModelδʵ����;"*/
 							g_sLangTxt_SCLCompare_ProModDescription62.GetString(),
 							strMSGFull.GetString());
 						strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyDOI->Row(),pTinyDOI->Column()*/ );
 						AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
 					}
 				}
 			}
 
 			if (pDOValue != NULL)
 			{
 				pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("DOI-Repeat");
 
 				if (BeCheckThisObject(pCheckObject ,strObjectID))
 				{
 					if (list_DOI.empty())
 					{
 						list_DOI.push_back(CString(strDOIName));
 					}
 					else
 					{
 						std::list<CString>::iterator iter = list_DOI.begin();
 						std::list<CString>::iterator iend = list_DOI.end();
 						for(; iter != iend; iter++)
 						{
 							if (*iter == strDOIName)
 							{
 								/*strErrorText = strMSGFull;
 								strErrorText += "��ͻ, �����ظ�ʵ����;";*/
 								FormatString(strErrorText,/*"%s��ͻ, �����ظ�ʵ����;"*/
 									g_sLangTxt_SCLCompare_ProModDescription63.GetString(),
 									strMSGFull.GetString());
 								strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyDOI->Row(),pTinyDOI->Column()*/ );
 								AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
 								break;
 							}
 						}
 
 						if (iter == iend)
 						{
 							list_DOI.push_back(CString(strDOIName));
 						}
 					}
 				}
 
 				pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("LN-DOI-DAI-Valid");
 
 				if (BeCheckThisObject(pCheckObject ,strObjectID))
 				{
 					CheckSDI_DAIValid(pTinyDOI ,pTestObjectTemplates , pDOValue->m_strType ,strMSGFull ,strObjectID);
 				}
 			}
 
 			pTinyDOI = pTinyDOI.next_sibling();
 		}
 		list_DOI.clear();
 	}
}

void CSclProjAppModelCheckTool::CheckSDI_DAIValid(xpugi::xml_node pTinyDOI ,CExBaseList *pTestObjectTemplates, CString strType, CString strMSGFull ,CString strObjectID)
{
	CString strErrorText;
	CString strErrorPos;
	CString strDAIName;
	CString strMSGFullNew;
	std::list<CString>	list_DAI;

	xpugi::xml_node pTinyDAI;

	CDOType *pDOType = (CDOType *)pTestObjectTemplates->FindByID(strType);
	CExBaseObject *pDAValue = NULL;

	if (pDOType == NULL)
	{
		/*strErrorText = strMSGFull;
		strErrorText.AppendFormat("���õ� type =(%s)δ����;",strType.GetString());*/
		FormatString(strErrorText,/*"%s���õ� type =(%s)δ����;"*/
			g_sLangTxt_SCLCompare_ProModDescription64.GetString(),
			strMSGFull.GetString(),strType.GetString());
		strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyDOI->Row(),pTinyDOI->Column()*/ );
		AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
	}
	else
	{
		pTinyDAI = pTinyDOI.first_child();
		while(pTinyDAI != NULL)
		{
			if ((strcmp(pTinyDAI.name() , "SDI") != 0)&&(strcmp(pTinyDAI.name() , "DAI") != 0))
			{
				pTinyDAI = pTinyDAI.next_sibling();
				continue;
			}

			strDAIName = pTinyDAI.attribute("name").value();
			pDAValue = pDOType->FindByID(strDAIName);

			if (pDAValue == NULL)
			{
				/*strErrorText = strMSGFull;
				strErrorText.AppendFormat("���õ� DOType =(%s)�µ�ʵ���� DAI name =(%s)δ����;",strType.GetString() ,strDAIName.GetString());*/
				FormatString(strErrorText,/*"%s���õ� DOType =(%s)�µ�ʵ���� DAI name =(%s)δ����;"*/
					g_sLangTxt_SCLCompare_ProModDescription65.GetString(),
					strMSGFull.GetString(),strType.GetString() ,strDAIName.GetString());
				strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyDAI->Row(),pTinyDAI->Column()*/ );
				AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
			}
			else if (pDAValue->GetClassID() == SCLCLASSID_CSCLFILE_SDODETAIL)
			{
				/*strMSGFullNew = strMSGFull;
				strMSGFullNew.AppendFormat("�µ�SDI name =(%s)" ,strDAIName.GetString());*/
				FormatString(strMSGFullNew,/*"%s�µ�SDI name =(%s)"*/
					g_sLangTxt_SCLCompare_ProModDescription66.GetString(),
					strMSGFull.GetString(),strDAIName.GetString());
				CheckSDI_DAIValid(pTinyDAI ,pTestObjectTemplates , pDAValue->m_strName ,strMSGFullNew ,strObjectID);
			}

			if (list_DAI.empty())
			{
				list_DAI.push_back(CString(strDAIName));
			}
			else
			{
				std::list<CString>::iterator iter = list_DAI.begin();
				std::list<CString>::iterator iend = list_DAI.end();
				for(; iter != iend; iter++)
				{
					if (*iter == strDAIName)
					{
						/*strErrorText = strMSGFull;
						strErrorText.AppendFormat("�µ�DAI name =(%s)��ͻ, �����ظ�ʵ����;",strDAIName.GetString());*/
						FormatString(strErrorText,/*"%s�µ�DAI name =(%s)��ͻ, �����ظ�ʵ����;"*/
							g_sLangTxt_SCLCompare_ProModDescription67.GetString(),
							strMSGFull.GetString(),strDAIName.GetString());
						strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyDAI->Row(),pTinyDAI->Column()*/ );
						AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
						break;
					}
				}

				if (iter == iend)
				{
					list_DAI.push_back(CString(strDAIName));
				}
			}

			pTinyDAI = pTinyDAI.next_sibling();
		}
		list_DAI.clear();
	}
}

long CSclProjAppModelCheckTool::DelTailDigtal(CString *strName )
{
	long nIndex = 0;
	char szDigtal[20] = {""};
	char szNew[20] = {""};
	szDigtal[0] = strName->GetAt(strName->GetLength()-1);
	char *pzfTmp = szDigtal;
	bool bSmb = ('0'<=*pzfTmp)&&(*pzfTmp<='9');

	while(bSmb)
	{
		pzfTmp++;
		*strName = strName->Left(strName->GetLength()-1);
		*pzfTmp = strName->GetAt(strName->GetLength()-1);
		bSmb = ('0'<=*pzfTmp)&&(*pzfTmp<='9');
	}
	*pzfTmp = '\0';

	nIndex = strlen(szDigtal);
	for (int i=0; i<nIndex;i++)
	{
		szNew[i] = szDigtal[nIndex-i-1];
	}

	nIndex = CString_To_long(szNew);
	return nIndex;
}

void CSclProjAppModelCheckTool::CheckLDeviceInst(xpugi::xml_node pTinyLDNode ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,CString strObjectID)
{
	CString strErrorText;
	CString strErrorPos;
	CString strLDNew = strLDevice;

	if (strLDNew != "LD0")
	{
		DelTailDigtal(&strLDNew);

		if ((strLDNew != "MEAS")&&(strLDNew != "PROT")&&(strLDNew != "CTRL")&&(strLDNew != "PIGO")&&(strLDNew != "PISV")&&(strLDNew != "RPIT")&&(strLDNew != "RCD")&&(strLDNew != "MUGO")
			&&(strLDNew != "MUSV")&&(strLDNew != "PQLD"))
		{
			strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyLDNode->Row(),pTinyLDNode->Column()*/);
			/*strErrorText += "��IED(";
			strErrorText += strIEDMSG;
			strErrorText.AppendFormat(")�� AccessPoint (%s)�µ� LD (%s)���������� Q/GDW 1396�е�7.1.3(��Q/GDW1650.3��5.2.3)��Ҫ��;",
				strAccessPoint.GetString() ,strLDevice.GetString());*/
			//FormatString(strErrorText,/*"��IED(%s)�� AccessPoint (%s)�µ� LD (%s)���������� Q/GDW 1396�е�7.1.3(��Q/GDW1650.3��5.2.3)��Ҫ��;"*/
			//	g_sLangTxt_SCLCompare_ProModDescription68.GetString(),
			//	strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString());
			FormatString(strErrorText,/*"��IED(%s)�� AccessPoint (%s)�µ� LD (%s)���������� Q/GDW 1396�е�7.1.3(��Q/GDW1650.3��5.2.3)��Ҫ��;"*/
				g_sLangTxt_SCLCompare_ProModDescription68.GetString(),
				strIEDMSG.GetString(),strAccessPoint.GetString() ,strLDevice.GetString());
			AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
		}
	}
}

void CSclProjAppModelCheckTool::CheckAccessPointName(xpugi::xml_node pTinyAccessPointNode ,CString strAccessPoint ,CString strIEDMSG ,CString  strObjectID)
{
	CString strErrorText;
	CString strErrorPos;
	CString strAccPoint = strAccessPoint;
	DelTailDigtal(&strAccPoint);

	if ((strAccPoint != "S")&&(strAccPoint != "M")&&(strAccPoint != "G"))
	{
		strErrorPos.Format(/*"�к�=%d ,�к�=%d"*/g_sLangTxt_SCLCompare_RowColumnNum.GetString(),-1,-1/*pTinyAccessPointNode->Row(),pTinyAccessPointNode->Column()*/);
		/*strErrorText = "��IED(";
		strErrorText += strIEDMSG;
		strErrorText.AppendFormat(")�� AccessPoint(%s) ���������� Q/GDW 1396�е�7.1.2��Ҫ��;",strAccessPoint.GetString());*/
		FormatString(strErrorText,/*"��IED(%s)�� AccessPoint(%s) ���������� Q/GDW 1396�е�7.1.2��Ҫ��;"*/
			g_sLangTxt_SCLCompare_ProModDescription69.GetString(),
			strIEDMSG.GetString(),strAccessPoint.GetString());
		AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
	}
}

void CSclProjAppModelCheckTool::GetIEDMSG(xpugi::xml_node pTinyIEDNode , CString &strIEDMSG)
{
	strIEDMSG  = pTinyIEDNode.attribute("name").value();
	CString strDesc = pTinyIEDNode.attribute("desc").value();
	CString strDescNew;
	utf8_to_gbk(strDesc,strDescNew);
	strDesc = strDescNew;
	//UTF8ToMultiByte(strDesc);

	if (strIEDMSG.IsEmpty())
	{
		strIEDMSG = strDesc;
	} 
	else if (!strDesc.IsEmpty())
	{
		strIEDMSG += "--";
		strIEDMSG += strDesc;
	}
}

void CSclProjAppModelCheckTool::GetTinyDescAndName(xpugi::xml_node pTinySubNetwork ,CString &strSubNetwork)
{
	strSubNetwork = pTinySubNetwork.attribute("desc").value();

	CString strTmpdesc;
	utf8_to_gbk(strSubNetwork,strTmpdesc);
	strSubNetwork = strTmpdesc;

	if (!strSubNetwork.IsEmpty())
	{
		strSubNetwork += "-";
	}
	CString strTmpname;
	strTmpname = pTinySubNetwork.attribute("name").value();
	utf8_to_gbk(strTmpdesc,strTmpname);
	strSubNetwork += strTmpdesc;//2023-12-14 zhou yangyong�޸�,"-"�ٴ�ת�����������

	//UTF8ToMultiByte(strSubNetwork);
}

void CSclProjAppModelCheckTool::FormatString(CString &strText, const char *strFormat, ...)
{
#ifdef _PSX_IDE_QT_
	va_list argList;
	va_start( argList, strFormat );
	str_formart_v(strFormat, argList, strText);
	va_end( argList );
#else
	va_list argList;
    va_start( argList, format );
    strText.vsprintf(format, argList );
    va_end( argList );
#endif
}