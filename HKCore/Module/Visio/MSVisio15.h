#ifndef MSVISIO15_H__
#define MSVISIO15_H__

#include "MSVisioEnumDef.h"

namespace MSVisio15
{

	// CEApplication 包装类

	class CEApplication : public COleDispatchDriver
	{
	public:
		CEApplication(){} // 调用 COleDispatchDriver 默认构造函数
		CEApplication(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CEApplication(const CEApplication& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// EApplication 方法
	public:
		void AppActivated(LPDISPATCH app)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1001, DISPATCH_METHOD, VT_EMPTY, NULL, parms, app);
		}
		void AppDeactivated(LPDISPATCH app)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1002, DISPATCH_METHOD, VT_EMPTY, NULL, parms, app);
		}
		void AppObjActivated(LPDISPATCH app)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1004, DISPATCH_METHOD, VT_EMPTY, NULL, parms, app);
		}
		void AppObjDeactivated(LPDISPATCH app)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1008, DISPATCH_METHOD, VT_EMPTY, NULL, parms, app);
		}
		void BeforeQuit(LPDISPATCH app)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1010, DISPATCH_METHOD, VT_EMPTY, NULL, parms, app);
		}
		void BeforeModal(LPDISPATCH app)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1020, DISPATCH_METHOD, VT_EMPTY, NULL, parms, app);
		}
		void AfterModal(LPDISPATCH app)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1040, DISPATCH_METHOD, VT_EMPTY, NULL, parms, app);
		}
		void WindowOpened(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8001, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void SelectionChanged(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2bd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void BeforeWindowClosed(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4001, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void WindowActivated(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1080, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void BeforeWindowSelDelete(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2be, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void BeforeWindowPageTurn(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2bf, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void WindowTurnedToPage(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2c0, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void DocumentOpened(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void DocumentCreated(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void DocumentSaved(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void DocumentSavedAs(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void DocumentChanged(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2002, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void BeforeDocumentClose(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4002, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void StyleAdded(LPDISPATCH Style)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8004, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style);
		}
		void StyleChanged(LPDISPATCH Style)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2004, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style);
		}
		void BeforeStyleDelete(LPDISPATCH Style)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4004, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style);
		}
		void MasterAdded(LPDISPATCH Master)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8008, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Master);
		}
		void MasterChanged(LPDISPATCH Master)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2008, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Master);
		}
		void BeforeMasterDelete(LPDISPATCH Master)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4008, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Master);
		}
		void PageAdded(LPDISPATCH Page)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8010, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Page);
		}
		void PageChanged(LPDISPATCH Page)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2010, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Page);
		}
		void BeforePageDelete(LPDISPATCH Page)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4010, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Page);
		}
		void ShapeAdded(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8040, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void BeforeSelectionDelete(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x385, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void ShapeChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2040, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void SelectionAdded(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x386, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void BeforeShapeDelete(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4040, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void TextChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2080, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void CellChanged(LPDISPATCH Cell)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2800, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Cell);
		}
		void MarkerEvent(LPDISPATCH app, long SequenceNum, LPCTSTR ContextString)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_BSTR ;
			InvokeHelper(0x1100, DISPATCH_METHOD, VT_EMPTY, NULL, parms, app, SequenceNum, ContextString);
		}
		void NoEventsPending(LPDISPATCH app)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1200, DISPATCH_METHOD, VT_EMPTY, NULL, parms, app);
		}
		void VisioIsIdle(LPDISPATCH app)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1400, DISPATCH_METHOD, VT_EMPTY, NULL, parms, app);
		}
		void MustFlushScopeBeginning(LPDISPATCH app)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0xc8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, app);
		}
		void MustFlushScopeEnded(LPDISPATCH app)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0xc9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, app);
		}
		void RunModeEntered(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void DesignModeEntered(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void BeforeDocumentSave(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void BeforeDocumentSaveAs(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void FormulaChanged(LPDISPATCH Cell)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x3000, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Cell);
		}
		void ConnectionsAdded(LPDISPATCH Connects)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8100, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Connects);
		}
		void ConnectionsDeleted(LPDISPATCH Connects)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4100, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Connects);
		}
		void EnterScope(LPDISPATCH app, long nScopeID, LPCTSTR bstrDescription)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_BSTR ;
			InvokeHelper(0xca, DISPATCH_METHOD, VT_EMPTY, NULL, parms, app, nScopeID, bstrDescription);
		}
		void ExitScope(LPDISPATCH app, long nScopeID, LPCTSTR bstrDescription, BOOL bErrOrCancelled)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_BSTR VTS_BOOL ;
			InvokeHelper(0xcb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, app, nScopeID, bstrDescription, bErrOrCancelled);
		}
		void QueryCancelQuit(LPDISPATCH app, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0xcc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, app, lpboolRet);
		}
		void QuitCanceled(LPDISPATCH app)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0xcd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, app);
		}
		void WindowChanged(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2001, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void ViewChanged(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2c1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void QueryCancelWindowClose(LPDISPATCH Window, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x2c2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window, lpboolRet);
		}
		void WindowCloseCanceled(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2c3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void QueryCancelDocumentClose(LPDISPATCH doc, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc, lpboolRet);
		}
		void DocumentCloseCanceled(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void QueryCancelStyleDelete(LPDISPATCH Style, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x12c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style, lpboolRet);
		}
		void StyleDeleteCanceled(LPDISPATCH Style)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x12d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style);
		}
		void QueryCancelMasterDelete(LPDISPATCH Master, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x190, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Master, lpboolRet);
		}
		void MasterDeleteCanceled(LPDISPATCH Master)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x191, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Master);
		}
		void QueryCancelPageDelete(LPDISPATCH Page, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x1f4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Page, lpboolRet);
		}
		void PageDeleteCanceled(LPDISPATCH Page)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1f5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Page);
		}
		void ShapeParentChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x322, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void BeforeShapeTextEdit(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x323, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void ShapeExitedTextEdit(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x324, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void QueryCancelSelectionDelete(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x387, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void SelectionDeleteCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x388, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void QueryCancelUngroup(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x389, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void UngroupCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x38a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void QueryCancelConvertToGroup(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x38b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void ConvertToGroupCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x38c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void QueryCancelSuspend(LPDISPATCH app, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0xce, DISPATCH_METHOD, VT_EMPTY, NULL, parms, app, lpboolRet);
		}
		void SuspendCanceled(LPDISPATCH app)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0xcf, DISPATCH_METHOD, VT_EMPTY, NULL, parms, app);
		}
		void BeforeSuspend(LPDISPATCH app)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0xd0, DISPATCH_METHOD, VT_EMPTY, NULL, parms, app);
		}
		void AfterResume(LPDISPATCH app)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0xd1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, app);
		}
		void OnKeystrokeMessageForAddon(LPDISPATCH MSG, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x2c4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, MSG, lpboolRet);
		}
		void MouseDown(long Button, long KeyButtonState, double x, double y, BOOL * CancelDefault)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_PBOOL ;
			InvokeHelper(0x2c5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Button, KeyButtonState, x, y, CancelDefault);
		}
		void MouseMove(long Button, long KeyButtonState, double x, double y, BOOL * CancelDefault)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_PBOOL ;
			InvokeHelper(0x2c6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Button, KeyButtonState, x, y, CancelDefault);
		}
		void MouseUp(long Button, long KeyButtonState, double x, double y, BOOL * CancelDefault)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_PBOOL ;
			InvokeHelper(0x2c7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Button, KeyButtonState, x, y, CancelDefault);
		}
		void KeyDown(long KeyCode, long KeyButtonState, BOOL * CancelDefault)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_PBOOL ;
			InvokeHelper(0x2c8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, KeyCode, KeyButtonState, CancelDefault);
		}
		void KeyPress(long KeyAscii, BOOL * CancelDefault)
		{
			static BYTE parms[] = VTS_I4 VTS_PBOOL ;
			InvokeHelper(0x2c9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, KeyAscii, CancelDefault);
		}
		void KeyUp(long KeyCode, long KeyButtonState, BOOL * CancelDefault)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_PBOOL ;
			InvokeHelper(0x2ca, DISPATCH_METHOD, VT_EMPTY, NULL, parms, KeyCode, KeyButtonState, CancelDefault);
		}
		void QueryCancelSuspendEvents(LPDISPATCH app, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0xd2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, app, lpboolRet);
		}
		void SuspendEventsCanceled(LPDISPATCH app)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0xd3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, app);
		}
		void BeforeSuspendEvents(LPDISPATCH app)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0xd4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, app);
		}
		void AfterResumeEvents(LPDISPATCH app)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0xd5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, app);
		}
		void QueryCancelGroup(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x38d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void GroupCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x38e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void ShapeDataGraphicChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x327, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void BeforeDataRecordsetDelete(LPDISPATCH DataRecordset)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4020, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DataRecordset);
		}
		void DataRecordsetChanged(LPDISPATCH DataRecordsetChanged)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2020, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DataRecordsetChanged);
		}
		void DataRecordsetAdded(LPDISPATCH DataRecordset)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8020, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DataRecordset);
		}
		void ShapeLinkAdded(LPDISPATCH Shape, long DataRecordsetID, long DataRowID)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 ;
			InvokeHelper(0x325, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape, DataRecordsetID, DataRowID);
		}
		void ShapeLinkDeleted(LPDISPATCH Shape, long DataRecordsetID, long DataRowID)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 ;
			InvokeHelper(0x326, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape, DataRecordsetID, DataRowID);
		}
		void AfterRemoveHiddenInformation(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void ContainerRelationshipAdded(LPDISPATCH ShapePair)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1f6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ShapePair);
		}
		void ContainerRelationshipDeleted(LPDISPATCH ShapePair)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1f7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ShapePair);
		}
		void CalloutRelationshipAdded(LPDISPATCH ShapePair)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1f8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ShapePair);
		}
		void CalloutRelationshipDeleted(LPDISPATCH ShapePair)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1f9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ShapePair);
		}
		void RuleSetValidated(LPDISPATCH RuleSet)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, RuleSet);
		}
		void QueryCancelReplaceShapes(LPDISPATCH replaceShapes, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x38f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, replaceShapes, lpboolRet);
		}
		void ReplaceShapesCanceled(LPDISPATCH replaceShapes)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x390, DISPATCH_METHOD, VT_EMPTY, NULL, parms, replaceShapes);
		}
		void BeforeReplaceShapes(LPDISPATCH replaceShapes)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x391, DISPATCH_METHOD, VT_EMPTY, NULL, parms, replaceShapes);
		}
		void AfterReplaceShapes(LPDISPATCH sel)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x392, DISPATCH_METHOD, VT_EMPTY, NULL, parms, sel);
		}

		// EApplication 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CECell 包装类

	class CECell : public COleDispatchDriver
	{
	public:
		CECell(){} // 调用 COleDispatchDriver 默认构造函数
		CECell(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CECell(const CECell& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// ECell 方法
	public:
		void CellChanged(LPDISPATCH Cell)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2800, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Cell);
		}
		void FormulaChanged(LPDISPATCH Cell)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x3000, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Cell);
		}

		// ECell 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CECharacters 包装类

	class CECharacters : public COleDispatchDriver
	{
	public:
		CECharacters(){} // 调用 COleDispatchDriver 默认构造函数
		CECharacters(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CECharacters(const CECharacters& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// ECharacters 方法
	public:
		void TextChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2080, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}

		// ECharacters 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CEDataRecordset 包装类

	class CEDataRecordset : public COleDispatchDriver
	{
	public:
		CEDataRecordset(){} // 调用 COleDispatchDriver 默认构造函数
		CEDataRecordset(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CEDataRecordset(const CEDataRecordset& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// EDataRecordset 方法
	public:
		void DataRecordsetChanged(LPDISPATCH DataRecordsetChanged)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2020, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DataRecordsetChanged);
		}
		void BeforeDataRecordsetDelete(LPDISPATCH DataRecordset)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4020, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DataRecordset);
		}

		// EDataRecordset 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CEDataRecordsets 包装类

	class CEDataRecordsets : public COleDispatchDriver
	{
	public:
		CEDataRecordsets(){} // 调用 COleDispatchDriver 默认构造函数
		CEDataRecordsets(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CEDataRecordsets(const CEDataRecordsets& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// EDataRecordsets 方法
	public:
		void DataRecordsetAdded(LPDISPATCH DataRecordset)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8020, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DataRecordset);
		}
		void BeforeDataRecordsetDelete(LPDISPATCH DataRecordset)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4020, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DataRecordset);
		}
		void DataRecordsetChanged(LPDISPATCH DataRecordsetChanged)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2020, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DataRecordsetChanged);
		}

		// EDataRecordsets 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CEDocument 包装类

	class CEDocument : public COleDispatchDriver
	{
	public:
		CEDocument(){} // 调用 COleDispatchDriver 默认构造函数
		CEDocument(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CEDocument(const CEDocument& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// EDocument 方法
	public:
		void DocumentOpened(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void DocumentCreated(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void DocumentSaved(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void DocumentSavedAs(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void DocumentChanged(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2002, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void BeforeDocumentClose(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4002, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void StyleAdded(LPDISPATCH Style)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8004, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style);
		}
		void StyleChanged(LPDISPATCH Style)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2004, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style);
		}
		void BeforeStyleDelete(LPDISPATCH Style)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4004, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style);
		}
		void MasterAdded(LPDISPATCH Master)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8008, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Master);
		}
		void MasterChanged(LPDISPATCH Master)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2008, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Master);
		}
		void BeforeMasterDelete(LPDISPATCH Master)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4008, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Master);
		}
		void PageAdded(LPDISPATCH Page)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8010, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Page);
		}
		void PageChanged(LPDISPATCH Page)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2010, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Page);
		}
		void BeforePageDelete(LPDISPATCH Page)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4010, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Page);
		}
		void ShapeAdded(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8040, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void BeforeSelectionDelete(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x385, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void RunModeEntered(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void DesignModeEntered(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void BeforeDocumentSave(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void BeforeDocumentSaveAs(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void QueryCancelDocumentClose(LPDISPATCH doc, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc, lpboolRet);
		}
		void DocumentCloseCanceled(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void QueryCancelStyleDelete(LPDISPATCH Style, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x12c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style, lpboolRet);
		}
		void StyleDeleteCanceled(LPDISPATCH Style)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x12d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style);
		}
		void QueryCancelMasterDelete(LPDISPATCH Master, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x190, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Master, lpboolRet);
		}
		void MasterDeleteCanceled(LPDISPATCH Master)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x191, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Master);
		}
		void QueryCancelPageDelete(LPDISPATCH Page, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x1f4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Page, lpboolRet);
		}
		void PageDeleteCanceled(LPDISPATCH Page)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1f5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Page);
		}
		void ShapeParentChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x322, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void BeforeShapeTextEdit(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x323, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void ShapeExitedTextEdit(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x324, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void QueryCancelSelectionDelete(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x387, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void SelectionDeleteCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x388, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void QueryCancelUngroup(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x389, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void UngroupCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x38a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void QueryCancelConvertToGroup(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x38b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void ConvertToGroupCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x38c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void QueryCancelGroup(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x38d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void GroupCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x38e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void ShapeDataGraphicChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x327, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void BeforeDataRecordsetDelete(LPDISPATCH DataRecordset)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4020, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DataRecordset);
		}
		void DataRecordsetAdded(LPDISPATCH DataRecordset)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8020, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DataRecordset);
		}
		void AfterRemoveHiddenInformation(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void RuleSetValidated(LPDISPATCH RuleSet)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, RuleSet);
		}
		void AfterDocumentMerge(LPDISPATCH coauthMergeObjects)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms, coauthMergeObjects);
		}

		// EDocument 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CEDocuments 包装类

	class CEDocuments : public COleDispatchDriver
	{
	public:
		CEDocuments(){} // 调用 COleDispatchDriver 默认构造函数
		CEDocuments(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CEDocuments(const CEDocuments& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// EDocuments 方法
	public:
		void DocumentOpened(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void DocumentCreated(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void DocumentSaved(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void DocumentSavedAs(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void DocumentChanged(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2002, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void BeforeDocumentClose(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4002, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void StyleAdded(LPDISPATCH Style)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8004, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style);
		}
		void StyleChanged(LPDISPATCH Style)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2004, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style);
		}
		void BeforeStyleDelete(LPDISPATCH Style)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4004, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style);
		}
		void MasterAdded(LPDISPATCH Master)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8008, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Master);
		}
		void MasterChanged(LPDISPATCH Master)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2008, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Master);
		}
		void BeforeMasterDelete(LPDISPATCH Master)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4008, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Master);
		}
		void PageAdded(LPDISPATCH Page)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8010, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Page);
		}
		void PageChanged(LPDISPATCH Page)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2010, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Page);
		}
		void BeforePageDelete(LPDISPATCH Page)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4010, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Page);
		}
		void ShapeAdded(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8040, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void BeforeSelectionDelete(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x385, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void ShapeChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2040, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void SelectionAdded(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x386, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void BeforeShapeDelete(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4040, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void TextChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2080, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void CellChanged(LPDISPATCH Cell)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2800, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Cell);
		}
		void RunModeEntered(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void DesignModeEntered(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void BeforeDocumentSave(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void BeforeDocumentSaveAs(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void FormulaChanged(LPDISPATCH Cell)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x3000, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Cell);
		}
		void ConnectionsAdded(LPDISPATCH Connects)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8100, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Connects);
		}
		void ConnectionsDeleted(LPDISPATCH Connects)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4100, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Connects);
		}
		void QueryCancelDocumentClose(LPDISPATCH doc, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc, lpboolRet);
		}
		void DocumentCloseCanceled(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void QueryCancelStyleDelete(LPDISPATCH Style, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x12c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style, lpboolRet);
		}
		void StyleDeleteCanceled(LPDISPATCH Style)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x12d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style);
		}
		void QueryCancelMasterDelete(LPDISPATCH Master, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x190, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Master, lpboolRet);
		}
		void MasterDeleteCanceled(LPDISPATCH Master)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x191, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Master);
		}
		void QueryCancelPageDelete(LPDISPATCH Page, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x1f4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Page, lpboolRet);
		}
		void PageDeleteCanceled(LPDISPATCH Page)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1f5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Page);
		}
		void ShapeParentChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x322, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void BeforeShapeTextEdit(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x323, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void ShapeExitedTextEdit(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x324, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void QueryCancelSelectionDelete(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x387, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void SelectionDeleteCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x388, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void QueryCancelUngroup(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x389, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void UngroupCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x38a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void QueryCancelConvertToGroup(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x38b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void ConvertToGroupCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x38c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void QueryCancelGroup(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x38d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void GroupCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x38e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void ShapeDataGraphicChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x327, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void BeforeDataRecordsetDelete(LPDISPATCH DataRecordset)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4020, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DataRecordset);
		}
		void DataRecordsetChanged(LPDISPATCH DataRecordsetChanged)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2020, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DataRecordsetChanged);
		}
		void DataRecordsetAdded(LPDISPATCH DataRecordset)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8020, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DataRecordset);
		}
		void ShapeLinkAdded(LPDISPATCH Shape, long DataRecordsetID, long DataRowID)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 ;
			InvokeHelper(0x325, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape, DataRecordsetID, DataRowID);
		}
		void ShapeLinkDeleted(LPDISPATCH Shape, long DataRecordsetID, long DataRowID)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 ;
			InvokeHelper(0x326, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape, DataRecordsetID, DataRowID);
		}
		void AfterRemoveHiddenInformation(LPDISPATCH doc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, doc);
		}
		void ContainerRelationshipAdded(LPDISPATCH ShapePair)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1f6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ShapePair);
		}
		void ContainerRelationshipDeleted(LPDISPATCH ShapePair)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1f7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ShapePair);
		}
		void CalloutRelationshipAdded(LPDISPATCH ShapePair)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1f8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ShapePair);
		}
		void CalloutRelationshipDeleted(LPDISPATCH ShapePair)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1f9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ShapePair);
		}
		void RuleSetValidated(LPDISPATCH RuleSet)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, RuleSet);
		}
		void QueryCancelReplaceShapes(LPDISPATCH replaceShapes, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x38f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, replaceShapes, lpboolRet);
		}
		void ReplaceShapesCanceled(LPDISPATCH replaceShapes)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x390, DISPATCH_METHOD, VT_EMPTY, NULL, parms, replaceShapes);
		}
		void BeforeReplaceShapes(LPDISPATCH replaceShapes)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x391, DISPATCH_METHOD, VT_EMPTY, NULL, parms, replaceShapes);
		}
		void AfterReplaceShapes(LPDISPATCH sel)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x392, DISPATCH_METHOD, VT_EMPTY, NULL, parms, sel);
		}
		void AfterDocumentMerge(LPDISPATCH coauthMergeObjects)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms, coauthMergeObjects);
		}

		// EDocuments 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CEMaster 包装类

	class CEMaster : public COleDispatchDriver
	{
	public:
		CEMaster(){} // 调用 COleDispatchDriver 默认构造函数
		CEMaster(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CEMaster(const CEMaster& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// EMaster 方法
	public:
		void MasterChanged(LPDISPATCH Master)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2008, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Master);
		}
		void BeforeMasterDelete(LPDISPATCH Master)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4008, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Master);
		}
		void ShapeAdded(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8040, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void BeforeSelectionDelete(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x385, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void ShapeChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2040, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void SelectionAdded(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x386, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void BeforeShapeDelete(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4040, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void TextChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2080, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void CellChanged(LPDISPATCH Cell)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2800, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Cell);
		}
		void FormulaChanged(LPDISPATCH Cell)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x3000, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Cell);
		}
		void ConnectionsAdded(LPDISPATCH Connects)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8100, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Connects);
		}
		void ConnectionsDeleted(LPDISPATCH Connects)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4100, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Connects);
		}
		void QueryCancelMasterDelete(LPDISPATCH Master, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x190, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Master, lpboolRet);
		}
		void MasterDeleteCanceled(LPDISPATCH Master)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x191, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Master);
		}
		void ShapeParentChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x322, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void BeforeShapeTextEdit(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x323, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void ShapeExitedTextEdit(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x324, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void QueryCancelSelectionDelete(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x387, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void SelectionDeleteCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x388, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void QueryCancelUngroup(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x389, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void UngroupCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x38a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void QueryCancelConvertToGroup(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x38b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void ConvertToGroupCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x38c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void QueryCancelGroup(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x38d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void GroupCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x38e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void ShapeDataGraphicChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x327, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}

		// EMaster 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CEMasters 包装类

	class CEMasters : public COleDispatchDriver
	{
	public:
		CEMasters(){} // 调用 COleDispatchDriver 默认构造函数
		CEMasters(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CEMasters(const CEMasters& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// EMasters 方法
	public:
		void MasterAdded(LPDISPATCH Master)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8008, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Master);
		}
		void MasterChanged(LPDISPATCH Master)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2008, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Master);
		}
		void BeforeMasterDelete(LPDISPATCH Master)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4008, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Master);
		}
		void ShapeAdded(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8040, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void BeforeSelectionDelete(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x385, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void ShapeChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2040, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void SelectionAdded(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x386, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void BeforeShapeDelete(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4040, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void TextChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2080, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void CellChanged(LPDISPATCH Cell)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2800, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Cell);
		}
		void FormulaChanged(LPDISPATCH Cell)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x3000, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Cell);
		}
		void ConnectionsAdded(LPDISPATCH Connects)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8100, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Connects);
		}
		void ConnectionsDeleted(LPDISPATCH Connects)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4100, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Connects);
		}
		void QueryCancelMasterDelete(LPDISPATCH Master, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x190, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Master, lpboolRet);
		}
		void MasterDeleteCanceled(LPDISPATCH Master)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x191, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Master);
		}
		void ShapeParentChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x322, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void BeforeShapeTextEdit(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x323, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void ShapeExitedTextEdit(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x324, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void QueryCancelSelectionDelete(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x387, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void SelectionDeleteCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x388, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void QueryCancelUngroup(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x389, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void UngroupCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x38a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void QueryCancelConvertToGroup(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x38b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void ConvertToGroupCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x38c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void QueryCancelGroup(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x38d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void GroupCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x38e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void ShapeDataGraphicChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x327, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}

		// EMasters 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CEPage 包装类

	class CEPage : public COleDispatchDriver
	{
	public:
		CEPage(){} // 调用 COleDispatchDriver 默认构造函数
		CEPage(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CEPage(const CEPage& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// EPage 方法
	public:
		void PageChanged(LPDISPATCH Page)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2010, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Page);
		}
		void BeforePageDelete(LPDISPATCH Page)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4010, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Page);
		}
		void ShapeAdded(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8040, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void BeforeSelectionDelete(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x385, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void ShapeChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2040, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void SelectionAdded(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x386, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void BeforeShapeDelete(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4040, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void TextChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2080, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void CellChanged(LPDISPATCH Cell)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2800, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Cell);
		}
		void FormulaChanged(LPDISPATCH Cell)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x3000, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Cell);
		}
		void ConnectionsAdded(LPDISPATCH Connects)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8100, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Connects);
		}
		void ConnectionsDeleted(LPDISPATCH Connects)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4100, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Connects);
		}
		void QueryCancelPageDelete(LPDISPATCH Page, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x1f4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Page, lpboolRet);
		}
		void PageDeleteCanceled(LPDISPATCH Page)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1f5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Page);
		}
		void ShapeParentChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x322, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void BeforeShapeTextEdit(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x323, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void ShapeExitedTextEdit(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x324, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void QueryCancelSelectionDelete(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x387, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void SelectionDeleteCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x388, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void QueryCancelUngroup(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x389, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void UngroupCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x38a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void QueryCancelConvertToGroup(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x38b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void ConvertToGroupCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x38c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void QueryCancelGroup(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x38d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void GroupCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x38e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void ShapeDataGraphicChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x327, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void ShapeLinkAdded(LPDISPATCH Shape, long DataRecordsetID, long DataRowID)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 ;
			InvokeHelper(0x325, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape, DataRecordsetID, DataRowID);
		}
		void ShapeLinkDeleted(LPDISPATCH Shape, long DataRecordsetID, long DataRowID)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 ;
			InvokeHelper(0x326, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape, DataRecordsetID, DataRowID);
		}
		void ContainerRelationshipAdded(LPDISPATCH ShapePair)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1f6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ShapePair);
		}
		void ContainerRelationshipDeleted(LPDISPATCH ShapePair)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1f7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ShapePair);
		}
		void CalloutRelationshipAdded(LPDISPATCH ShapePair)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1f8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ShapePair);
		}
		void CalloutRelationshipDeleted(LPDISPATCH ShapePair)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1f9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ShapePair);
		}
		void QueryCancelReplaceShapes(LPDISPATCH replaceShapes, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x38f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, replaceShapes, lpboolRet);
		}
		void ReplaceShapesCanceled(LPDISPATCH replaceShapes)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x390, DISPATCH_METHOD, VT_EMPTY, NULL, parms, replaceShapes);
		}
		void BeforeReplaceShapes(LPDISPATCH replaceShapes)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x391, DISPATCH_METHOD, VT_EMPTY, NULL, parms, replaceShapes);
		}
		void AfterReplaceShapes(LPDISPATCH sel)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x392, DISPATCH_METHOD, VT_EMPTY, NULL, parms, sel);
		}

		// EPage 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CEPages 包装类

	class CEPages : public COleDispatchDriver
	{
	public:
		CEPages(){} // 调用 COleDispatchDriver 默认构造函数
		CEPages(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CEPages(const CEPages& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// EPages 方法
	public:
		void PageAdded(LPDISPATCH Page)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8010, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Page);
		}
		void PageChanged(LPDISPATCH Page)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2010, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Page);
		}
		void BeforePageDelete(LPDISPATCH Page)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4010, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Page);
		}
		void ShapeAdded(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8040, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void BeforeSelectionDelete(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x385, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void ShapeChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2040, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void SelectionAdded(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x386, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void BeforeShapeDelete(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4040, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void TextChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2080, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void CellChanged(LPDISPATCH Cell)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2800, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Cell);
		}
		void FormulaChanged(LPDISPATCH Cell)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x3000, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Cell);
		}
		void ConnectionsAdded(LPDISPATCH Connects)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8100, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Connects);
		}
		void ConnectionsDeleted(LPDISPATCH Connects)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4100, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Connects);
		}
		void QueryCancelPageDelete(LPDISPATCH Page, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x1f4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Page, lpboolRet);
		}
		void PageDeleteCanceled(LPDISPATCH Page)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1f5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Page);
		}
		void ShapeParentChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x322, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void BeforeShapeTextEdit(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x323, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void ShapeExitedTextEdit(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x324, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void QueryCancelSelectionDelete(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x387, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void SelectionDeleteCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x388, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void QueryCancelUngroup(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x389, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void UngroupCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x38a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void QueryCancelConvertToGroup(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x38b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void ConvertToGroupCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x38c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void QueryCancelGroup(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x38d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void GroupCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x38e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void ShapeDataGraphicChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x327, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void ShapeLinkAdded(LPDISPATCH Shape, long DataRecordsetID, long DataRowID)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 ;
			InvokeHelper(0x325, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape, DataRecordsetID, DataRowID);
		}
		void ShapeLinkDeleted(LPDISPATCH Shape, long DataRecordsetID, long DataRowID)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 ;
			InvokeHelper(0x326, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape, DataRecordsetID, DataRowID);
		}
		void ContainerRelationshipAdded(LPDISPATCH ShapePair)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1f6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ShapePair);
		}
		void ContainerRelationshipDeleted(LPDISPATCH ShapePair)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1f7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ShapePair);
		}
		void CalloutRelationshipAdded(LPDISPATCH ShapePair)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1f8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ShapePair);
		}
		void CalloutRelationshipDeleted(LPDISPATCH ShapePair)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1f9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ShapePair);
		}
		void QueryCancelReplaceShapes(LPDISPATCH replaceShapes, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x38f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, replaceShapes, lpboolRet);
		}
		void ReplaceShapesCanceled(LPDISPATCH replaceShapes)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x390, DISPATCH_METHOD, VT_EMPTY, NULL, parms, replaceShapes);
		}
		void BeforeReplaceShapes(LPDISPATCH replaceShapes)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x391, DISPATCH_METHOD, VT_EMPTY, NULL, parms, replaceShapes);
		}
		void AfterReplaceShapes(LPDISPATCH sel)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x392, DISPATCH_METHOD, VT_EMPTY, NULL, parms, sel);
		}

		// EPages 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CERow 包装类

	class CERow : public COleDispatchDriver
	{
	public:
		CERow(){} // 调用 COleDispatchDriver 默认构造函数
		CERow(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CERow(const CERow& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// ERow 方法
	public:
		void CellChanged(LPDISPATCH Cell)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2800, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Cell);
		}
		void FormulaChanged(LPDISPATCH Cell)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x3000, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Cell);
		}

		// ERow 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CESection 包装类

	class CESection : public COleDispatchDriver
	{
	public:
		CESection(){} // 调用 COleDispatchDriver 默认构造函数
		CESection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CESection(const CESection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// ESection 方法
	public:
		void CellChanged(LPDISPATCH Cell)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2800, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Cell);
		}
		void FormulaChanged(LPDISPATCH Cell)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x3000, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Cell);
		}

		// ESection 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CEShape 包装类

	class CEShape : public COleDispatchDriver
	{
	public:
		CEShape(){} // 调用 COleDispatchDriver 默认构造函数
		CEShape(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CEShape(const CEShape& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// EShape 方法
	public:
		void CellChanged(LPDISPATCH Cell)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2800, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Cell);
		}
		void ShapeAdded(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8040, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void BeforeSelectionDelete(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x385, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void ShapeChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2040, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void SelectionAdded(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x386, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void BeforeShapeDelete(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4040, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void TextChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2080, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void FormulaChanged(LPDISPATCH Cell)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x3000, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Cell);
		}
		void ShapeParentChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x322, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void BeforeShapeTextEdit(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x323, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void ShapeExitedTextEdit(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x324, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void QueryCancelSelectionDelete(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x387, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void SelectionDeleteCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x388, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void QueryCancelUngroup(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x389, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void UngroupCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x38a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void QueryCancelConvertToGroup(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x38b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void ConvertToGroupCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x38c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void QueryCancelGroup(LPDISPATCH Selection, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x38d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection, lpboolRet);
		}
		void GroupCanceled(LPDISPATCH Selection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x38e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Selection);
		}
		void ShapeDataGraphicChanged(LPDISPATCH Shape)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x327, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape);
		}
		void ShapeLinkAdded(LPDISPATCH Shape, long DataRecordsetID, long DataRowID)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 ;
			InvokeHelper(0x325, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape, DataRecordsetID, DataRowID);
		}
		void ShapeLinkDeleted(LPDISPATCH Shape, long DataRecordsetID, long DataRowID)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 ;
			InvokeHelper(0x326, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Shape, DataRecordsetID, DataRowID);
		}

		// EShape 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CEStyle 包装类

	class CEStyle : public COleDispatchDriver
	{
	public:
		CEStyle(){} // 调用 COleDispatchDriver 默认构造函数
		CEStyle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CEStyle(const CEStyle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// EStyle 方法
	public:
		void StyleChanged(LPDISPATCH Style)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2004, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style);
		}
		void BeforeStyleDelete(LPDISPATCH Style)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4004, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style);
		}
		void QueryCancelStyleDelete(LPDISPATCH Style, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x12c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style, lpboolRet);
		}
		void StyleDeleteCanceled(LPDISPATCH Style)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x12d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style);
		}

		// EStyle 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CEStyles 包装类

	class CEStyles : public COleDispatchDriver
	{
	public:
		CEStyles(){} // 调用 COleDispatchDriver 默认构造函数
		CEStyles(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CEStyles(const CEStyles& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// EStyles 方法
	public:
		void StyleAdded(LPDISPATCH Style)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8004, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style);
		}
		void StyleChanged(LPDISPATCH Style)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2004, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style);
		}
		void BeforeStyleDelete(LPDISPATCH Style)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4004, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style);
		}
		void QueryCancelStyleDelete(LPDISPATCH Style, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x12c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style, lpboolRet);
		}
		void StyleDeleteCanceled(LPDISPATCH Style)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x12d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style);
		}

		// EStyles 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CEWindow 包装类

	class CEWindow : public COleDispatchDriver
	{
	public:
		CEWindow(){} // 调用 COleDispatchDriver 默认构造函数
		CEWindow(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CEWindow(const CEWindow& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// EWindow 方法
	public:
		void SelectionChanged(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2bd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void BeforeWindowClosed(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4001, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void WindowActivated(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1080, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void BeforeWindowSelDelete(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2be, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void BeforeWindowPageTurn(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2bf, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void WindowTurnedToPage(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2c0, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void WindowChanged(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2001, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void ViewChanged(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2c1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void QueryCancelWindowClose(LPDISPATCH Window, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x2c2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window, lpboolRet);
		}
		void WindowCloseCanceled(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2c3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void OnKeystrokeMessageForAddon(LPDISPATCH MSG, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x2c4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, MSG, lpboolRet);
		}
		void MouseDown(long Button, long KeyButtonState, double x, double y, BOOL * CancelDefault)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_PBOOL ;
			InvokeHelper(0x2c5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Button, KeyButtonState, x, y, CancelDefault);
		}
		void MouseMove(long Button, long KeyButtonState, double x, double y, BOOL * CancelDefault)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_PBOOL ;
			InvokeHelper(0x2c6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Button, KeyButtonState, x, y, CancelDefault);
		}
		void MouseUp(long Button, long KeyButtonState, double x, double y, BOOL * CancelDefault)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_PBOOL ;
			InvokeHelper(0x2c7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Button, KeyButtonState, x, y, CancelDefault);
		}
		void KeyDown(long KeyCode, long KeyButtonState, BOOL * CancelDefault)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_PBOOL ;
			InvokeHelper(0x2c8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, KeyCode, KeyButtonState, CancelDefault);
		}
		void KeyPress(long KeyAscii, BOOL * CancelDefault)
		{
			static BYTE parms[] = VTS_I4 VTS_PBOOL ;
			InvokeHelper(0x2c9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, KeyAscii, CancelDefault);
		}
		void KeyUp(long KeyCode, long KeyButtonState, BOOL * CancelDefault)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_PBOOL ;
			InvokeHelper(0x2ca, DISPATCH_METHOD, VT_EMPTY, NULL, parms, KeyCode, KeyButtonState, CancelDefault);
		}

		// EWindow 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CEWindows 包装类

	class CEWindows : public COleDispatchDriver
	{
	public:
		CEWindows(){} // 调用 COleDispatchDriver 默认构造函数
		CEWindows(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CEWindows(const CEWindows& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// EWindows 方法
	public:
		void WindowOpened(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8001, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void SelectionChanged(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2bd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void BeforeWindowClosed(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4001, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void WindowActivated(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1080, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void BeforeWindowSelDelete(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2be, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void BeforeWindowPageTurn(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2bf, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void WindowTurnedToPage(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2c0, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void WindowChanged(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2001, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void ViewChanged(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2c1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void QueryCancelWindowClose(LPDISPATCH Window, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x2c2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window, lpboolRet);
		}
		void WindowCloseCanceled(LPDISPATCH Window)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2c3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Window);
		}
		void OnKeystrokeMessageForAddon(LPDISPATCH MSG, BOOL * lpboolRet)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x2c4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, MSG, lpboolRet);
		}
		void MouseDown(long Button, long KeyButtonState, double x, double y, BOOL * CancelDefault)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_PBOOL ;
			InvokeHelper(0x2c5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Button, KeyButtonState, x, y, CancelDefault);
		}
		void MouseMove(long Button, long KeyButtonState, double x, double y, BOOL * CancelDefault)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_PBOOL ;
			InvokeHelper(0x2c6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Button, KeyButtonState, x, y, CancelDefault);
		}
		void MouseUp(long Button, long KeyButtonState, double x, double y, BOOL * CancelDefault)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_PBOOL ;
			InvokeHelper(0x2c7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Button, KeyButtonState, x, y, CancelDefault);
		}
		void KeyDown(long KeyCode, long KeyButtonState, BOOL * CancelDefault)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_PBOOL ;
			InvokeHelper(0x2c8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, KeyCode, KeyButtonState, CancelDefault);
		}
		void KeyPress(long KeyAscii, BOOL * CancelDefault)
		{
			static BYTE parms[] = VTS_I4 VTS_PBOOL ;
			InvokeHelper(0x2c9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, KeyAscii, CancelDefault);
		}
		void KeyUp(long KeyCode, long KeyButtonState, BOOL * CancelDefault)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_PBOOL ;
			InvokeHelper(0x2ca, DISPATCH_METHOD, VT_EMPTY, NULL, parms, KeyCode, KeyButtonState, CancelDefault);
		}

		// EWindows 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVAccelItem 包装类

	class CVAccelItem : public COleDispatchDriver
	{
	public:
		CVAccelItem(){} // 调用 COleDispatchDriver 默认构造函数
		CVAccelItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVAccelItem(const CVAccelItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVAccelItem 方法
	public:
		void Delete()
		{
			InvokeHelper(0x60020000, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		short get_Default()
		{
			short result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_CmdNum(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_CmdNum()
		{
			short result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Key(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Key()
		{
			short result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Alt(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Alt()
		{
			short result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Shift(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Shift()
		{
			short result;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Control(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Control()
		{
			short result;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_AddOnName(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_AddOnName()
		{
			CString result;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_AddOnArgs(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_AddOnArgs()
		{
			CString result;
			InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}

		// IVAccelItem 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVAccelItems 包装类

	class CVAccelItems : public COleDispatchDriver
	{
	public:
		CVAccelItems(){} // 调用 COleDispatchDriver 默认构造函数
		CVAccelItems(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVAccelItems(const CVAccelItems& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVAccelItems 方法
	public:
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long lIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, lIndex);
			return result;
		}
		LPDISPATCH Add()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020002, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}

		// IVAccelItems 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVAccelTable 包装类

	class CVAccelTable : public COleDispatchDriver
	{
	public:
		CVAccelTable(){} // 调用 COleDispatchDriver 默认构造函数
		CVAccelTable(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVAccelTable(const CVAccelTable& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVAccelTable 方法
	public:
		void Delete()
		{
			InvokeHelper(0x60020000, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		CString get_Default()
		{
			CString result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_TableName(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_TableName()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long get_SetID()
		{
			long result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_AccelItems()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}

		// IVAccelTable 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVAccelTables 包装类

	class CVAccelTables : public COleDispatchDriver
	{
	public:
		CVAccelTables(){} // 调用 COleDispatchDriver 默认构造函数
		CVAccelTables(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVAccelTables(const CVAccelTables& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVAccelTables 方法
	public:
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long lIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, lIndex);
			return result;
		}
		LPDISPATCH get_ItemAtID(long lID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, lID);
			return result;
		}
		LPDISPATCH Add()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020003, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH AddAtID(long lID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020004, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, lID);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}

		// IVAccelTables 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVAddon 包装类

	class CVAddon : public COleDispatchDriver
	{
	public:
		CVAddon(){} // 调用 COleDispatchDriver 默认构造函数
		CVAddon(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVAddon(const CVAddon& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVAddon 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		short get_Index()
		{
			short result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Enabled()
		{
			short result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void Run(LPCTSTR ArgString)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ArgString);
		}
		CString get_NameU()
		{
			CString result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}

		// IVAddon 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVAddons 包装类

	class CVAddons : public COleDispatchDriver
	{
	public:
		CVAddons(){} // 调用 COleDispatchDriver 默认构造函数
		CVAddons(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVAddons(const CVAddons& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVAddons 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(VARIANT& NameOrIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &NameOrIndex);
			return result;
		}
		short get_Count()
		{
			short result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Add(LPCTSTR FileName)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FileName);
			return result;
		}
		void GetNames(SAFEARRAY * * NameArray)
		{
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, NameArray);
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ItemU(VARIANT& NameOrIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &NameOrIndex);
			return result;
		}
		void GetNamesU(SAFEARRAY * * NameArray)
		{
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0x60020008, DISPATCH_METHOD, VT_EMPTY, NULL, parms, NameArray);
		}

		// IVAddons 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVAmbients 包装类

	class CVAmbients : public COleDispatchDriver
	{
	public:
		CVAmbients(){} // 调用 COleDispatchDriver 默认构造函数
		CVAmbients(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVAmbients(const CVAmbients& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVAmbients 方法
	public:
		long get_BackColor()
		{
			long result;
			InvokeHelper(DISPID_AMBIENT_BACKCOLOR, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_DisplayName()
		{
			CString result;
			InvokeHelper(DISPID_AMBIENT_DISPLAYNAME, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Font()
		{
			LPDISPATCH result;
			InvokeHelper(DISPID_AMBIENT_FONT, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_ForeColor()
		{
			long result;
			InvokeHelper(DISPID_AMBIENT_FORECOLOR, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_LocaleID()
		{
			long result;
			InvokeHelper(DISPID_AMBIENT_LOCALEID, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_MessageReflect()
		{
			BOOL result;
			InvokeHelper(DISPID_AMBIENT_MESSAGEREFLECT, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		CString get_ScaleUnits()
		{
			CString result;
			InvokeHelper(DISPID_AMBIENT_SCALEUNITS, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		short get_TextAlign()
		{
			short result;
			InvokeHelper(DISPID_AMBIENT_TEXTALIGN, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		BOOL get_UserMode()
		{
			BOOL result;
			InvokeHelper(DISPID_AMBIENT_USERMODE, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		BOOL get_UIDead()
		{
			BOOL result;
			InvokeHelper(DISPID_AMBIENT_UIDEAD, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		BOOL get_ShowGrabHandles()
		{
			BOOL result;
			InvokeHelper(DISPID_AMBIENT_SHOWGRABHANDLES, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		BOOL get_ShowHatching()
		{
			BOOL result;
			InvokeHelper(DISPID_AMBIENT_SHOWHATCHING, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		BOOL get_DisplayAsDefault()
		{
			BOOL result;
			InvokeHelper(DISPID_AMBIENT_DISPLAYASDEFAULT, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		BOOL get_SupportsMnemonics()
		{
			BOOL result;
			InvokeHelper(DISPID_AMBIENT_SUPPORTSMNEMONICS, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		BOOL get_AutoClip()
		{
			BOOL result;
			InvokeHelper(DISPID_AMBIENT_AUTOCLIP, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		long get_Appearance()
		{
			long result;
			InvokeHelper(DISPID_AMBIENT_APPEARANCE, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Shape()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020010, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		BOOL get_CancelOperation()
		{
			BOOL result;
			InvokeHelper(0x60020011, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}

		// IVAmbients 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVApplication 包装类

	class CVApplication : public COleDispatchDriver
	{
	public:
		CVApplication(){} // 调用 COleDispatchDriver 默认构造函数
		CVApplication(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVApplication(const CVApplication& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVApplication 方法
	public:
		LPDISPATCH get_ActiveDocument()
		{
			LPDISPATCH result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ActivePage()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ActiveWindow()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Documents()
		{
			LPDISPATCH result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		long get_OnDataChangeDelay()
		{
			long result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_OnDataChangeDelay(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_ProcessID()
		{
			long result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void Quit()
		{
			InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Redo()
		{
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		short get_ScreenUpdating()
		{
			short result;
			InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_ScreenUpdating(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void Undo()
		{
			InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		CString get_Version()
		{
			CString result;
			InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		short get_WindowHandle()
		{
			short result;
			InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Windows()
		{
			LPDISPATCH result;
			InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Language()
		{
			long result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		short get_IsVisio16()
		{
			short result;
			InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_IsVisio32()
		{
			short result;
			InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		long get_WindowHandle32()
		{
			long result;
			InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		short get_InstanceHandle()
		{
			short result;
			InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		long get_InstanceHandle32()
		{
			long result;
			InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_BuiltInMenus()
		{
			LPDISPATCH result;
			InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_BuiltInToolbars(short fIgnored)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, fIgnored);
			return result;
		}
		LPDISPATCH get_CustomMenus()
		{
			LPDISPATCH result;
			InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void SetCustomMenus(LPDISPATCH MenusObject)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, parms, MenusObject);
		}
		CString get_CustomMenusFile()
		{
			CString result;
			InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_CustomMenusFile(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void ClearCustomMenus()
		{
			InvokeHelper(0x1b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_CustomToolbars()
		{
			LPDISPATCH result;
			InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void SetCustomToolbars(LPDISPATCH ToolbarsObject)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ToolbarsObject);
		}
		CString get_CustomToolbarsFile()
		{
			CString result;
			InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_CustomToolbarsFile(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void ClearCustomToolbars()
		{
			InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		CString get_AddonPaths()
		{
			CString result;
			InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_AddonPaths(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x20, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_DrawingPaths()
		{
			CString result;
			InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_DrawingPaths(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x21, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_FilterPaths()
		{
			CString result;
			InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_FilterPaths(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x22, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_HelpPaths()
		{
			CString result;
			InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_HelpPaths(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x23, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_StartupPaths()
		{
			CString result;
			InvokeHelper(0x24, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_StartupPaths(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x24, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_StencilPaths()
		{
			CString result;
			InvokeHelper(0x25, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_StencilPaths(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x25, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_TemplatePaths()
		{
			CString result;
			InvokeHelper(0x26, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_TemplatePaths(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x26, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_UserName()
		{
			CString result;
			InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_UserName(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x27, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_PromptForSummary()
		{
			short result;
			InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_PromptForSummary(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x28, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Addons()
		{
			LPDISPATCH result;
			InvokeHelper(0x29, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void SaveWorkspaceAs(LPCTSTR FileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x2a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
		}
		void DoCmd(short CommandID)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x2b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, CommandID);
		}
		CString get_ProfileName()
		{
			CString result;
			InvokeHelper(0x2c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_EventInfo(long eventSeqNum)
		{
			CString result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x2d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, eventSeqNum);
			return result;
		}
		LPDISPATCH get_EventList()
		{
			LPDISPATCH result;
			InvokeHelper(0x2e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_PersistsEvents()
		{
			short result;
			InvokeHelper(0x2f, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Active()
		{
			short result;
			InvokeHelper(0x30, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_DeferRecalc()
		{
			short result;
			InvokeHelper(0x31, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_DeferRecalc(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x31, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_AlertResponse()
		{
			short result;
			InvokeHelper(0x32, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_AlertResponse(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x32, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_ShowProgress()
		{
			short result;
			InvokeHelper(0x33, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_ShowProgress(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x33, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Vbe()
		{
			LPDISPATCH result;
			InvokeHelper(0x34, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ShowMenus()
		{
			short result;
			InvokeHelper(0x35, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_ShowMenus(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x35, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_ToolbarStyle()
		{
			short result;
			InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_ToolbarStyle(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x36, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_ShowStatusBar()
		{
			short result;
			InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_ShowStatusBar(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x37, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_EventsEnabled()
		{
			short result;
			InvokeHelper(0x38, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_EventsEnabled(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x38, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString FormatResult(VARIANT& StringOrNumber, VARIANT& UnitsIn, VARIANT& UnitsOut, LPCTSTR Format)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_BSTR ;
			InvokeHelper(0x39, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, &StringOrNumber, &UnitsIn, &UnitsOut, Format);
			return result;
		}
		double ConvertResult(VARIANT& StringOrNumber, VARIANT& UnitsIn, VARIANT& UnitsOut)
		{
			double result;
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x3a, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &StringOrNumber, &UnitsIn, &UnitsOut);
			return result;
		}
		CString get_Path()
		{
			CString result;
			InvokeHelper(0x3b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void EnumDirectories(LPCTSTR PathsString, SAFEARRAY * * NameArray)
		{
			static BYTE parms[] = VTS_BSTR VTS_UNKNOWN ;
			InvokeHelper(0x3c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, PathsString, NameArray);
		}
		long get_TraceFlags()
		{
			long result;
			InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_TraceFlags(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x3d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void PurgeUndo()
		{
			InvokeHelper(0x3e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		long QueueMarkerEvent(LPCTSTR ContextString)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x3f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ContextString);
			return result;
		}
		short get_ShowToolbar()
		{
			short result;
			InvokeHelper(0x40, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_ShowToolbar(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x40, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_LiveDynamics()
		{
			BOOL result;
			InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_LiveDynamics(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x41, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_AutoLayout()
		{
			BOOL result;
			InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_AutoLayout(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x42, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Visible()
		{
			BOOL result;
			InvokeHelper(0x43, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Visible(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x43, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long BeginUndoScope(LPCTSTR bstrUndoScopeName)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x44, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrUndoScopeName);
			return result;
		}
		void EndUndoScope(long nScopeID, BOOL bCommit)
		{
			static BYTE parms[] = VTS_I4 VTS_BOOL ;
			InvokeHelper(0x45, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nScopeID, bCommit);
		}
		void AddUndoUnit(LPUNKNOWN pUndoUnit)
		{
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0x46, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pUndoUnit);
		}
		CString get_CommandLine()
		{
			CString result;
			InvokeHelper(0x47, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		BOOL get_IsUndoingOrRedoing()
		{
			BOOL result;
			InvokeHelper(0x48, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		long get_CurrentScope()
		{
			long result;
			InvokeHelper(0x49, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_IsInScope(long nCmdID)
		{
			BOOL result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x4a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, nCmdID);
			return result;
		}
		LPDISPATCH get_old_Addins()
		{
			LPDISPATCH result;
			InvokeHelper(0x4b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_ProductName()
		{
			CString result;
			InvokeHelper(0x4c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		BOOL get_UndoEnabled()
		{
			BOOL result;
			InvokeHelper(0x4d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_UndoEnabled(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x4d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ShowChanges()
		{
			BOOL result;
			InvokeHelper(0x4e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ShowChanges(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x4e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_TypelibMajorVersion()
		{
			short result;
			InvokeHelper(0x4f, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_TypelibMinorVersion()
		{
			short result;
			InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_AutoRecoverInterval()
		{
			short result;
			InvokeHelper(0x51, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_AutoRecoverInterval(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x51, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_InhibitSelectChange()
		{
			BOOL result;
			InvokeHelper(0x6002006e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_InhibitSelectChange(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002006e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_ActivePrinter()
		{
			CString result;
			InvokeHelper(0x60020070, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_ActivePrinter(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020070, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		SAFEARRAY * get_AvailablePrinters()
		{
			InvokeHelper(0x60020072, DISPATCH_PROPERTYGET, VT_EMPTY, NULL, NULL);
		}
		void RenameCurrentScope(LPCTSTR bstrScopeName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020073, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrScopeName);
		}
		void InvokeHelp(LPCTSTR bstrHelpFileName, long Command, long Data)
		{
			static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 ;
			InvokeHelper(0x60020074, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrHelpFileName, Command, Data);
		}
		LPDISPATCH get_CommandBars()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020075, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Build()
		{
			long result;
			InvokeHelper(0x60020076, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_COMAddIns()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020077, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		VARIANT get_DefaultPageUnits()
		{
			VARIANT result;
			InvokeHelper(0x60020078, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_DefaultPageUnits(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020078, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_DefaultTextUnits()
		{
			VARIANT result;
			InvokeHelper(0x6002007a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_DefaultTextUnits(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x6002007a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_DefaultAngleUnits()
		{
			VARIANT result;
			InvokeHelper(0x6002007c, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_DefaultAngleUnits(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x6002007c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_DefaultDurationUnits()
		{
			VARIANT result;
			InvokeHelper(0x6002007e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_DefaultDurationUnits(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x6002007e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		long get_FullBuild()
		{
			long result;
			InvokeHelper(0x60020080, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void OnComponentEnterState(long uStateID, BOOL bEnter)
		{
			static BYTE parms[] = VTS_I4 VTS_BOOL ;
			InvokeHelper(0x60020081, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uStateID, bEnter);
		}
		BOOL get_VBAEnabled()
		{
			BOOL result;
			InvokeHelper(0x60020082, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		long get_DefaultZoomBehavior()
		{
			long result;
			InvokeHelper(0x60020083, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_DefaultZoomBehavior(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020083, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		VARIANT GetUsageStatistic(long nWhichStatistic)
		{
			VARIANT result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020085, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, nWhichStatistic);
			return result;
		}
		LPDISPATCH get_DialogFont()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020086, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_LanguageHelp()
		{
			long result;
			InvokeHelper(0x60020087, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Window()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020088, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x60020089, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get_ConnectorToolDataObject()
		{
			LPUNKNOWN result;
			InvokeHelper(0x6002008a, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Settings()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002008b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString FormatResultEx(VARIANT& StringOrNumber, VARIANT& UnitsIn, VARIANT& UnitsOut, LPCTSTR Format, long LangID, long CalendarID)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_BSTR VTS_I4 VTS_I4 ;
			InvokeHelper(0x6002008c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, &StringOrNumber, &UnitsIn, &UnitsOut, Format, LangID, CalendarID);
			return result;
		}
		LPDISPATCH get_SaveAsWebObject()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002008d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_MsoDebugOptions()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002008e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_MyShapesPath()
		{
			CString result;
			InvokeHelper(0x6002008f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_MyShapesPath(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002008f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPUNKNOWN get_DefaultRectangleDataObject()
		{
			LPUNKNOWN result;
			InvokeHelper(0x60020091, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		BOOL get_DataFeaturesEnabled()
		{
			BOOL result;
			InvokeHelper(0x60020092, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_LanguageSettings()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020093, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Assistance()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020094, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void RegisterRibbonX(LPUNKNOWN SourceAddOn, LPDISPATCH TargetDocument, long TargetModes, LPCTSTR FriendlyName)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_DISPATCH VTS_I4 VTS_BSTR ;
			InvokeHelper(0x60020095, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SourceAddOn, TargetDocument, TargetModes, FriendlyName);
		}
		void UnregisterRibbonX(LPUNKNOWN SourceAddOn, LPDISPATCH TargetDocument)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_DISPATCH ;
			InvokeHelper(0x60020096, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SourceAddOn, TargetDocument);
		}
		BOOL GetPreviewEnabled(LPCTSTR GalleryName)
		{
			BOOL result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020097, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, GalleryName);
			return result;
		}
		void SetPreviewEnabled(LPCTSTR GalleryName, BOOL OnOrOff)
		{
			static BYTE parms[] = VTS_BSTR VTS_BOOL ;
			InvokeHelper(0x60020098, DISPATCH_METHOD, VT_EMPTY, NULL, parms, GalleryName, OnOrOff);
		}
		CString GetBuiltInStencilFile(long StencilType, long MeasurementSystem)
		{
			CString result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0x60020099, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, StencilType, MeasurementSystem);
			return result;
		}
		CString GetCustomStencilFile(long StencilType)
		{
			CString result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002009a, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, StencilType);
			return result;
		}
		BOOL get_DeferRelationshipRecalc()
		{
			BOOL result;
			InvokeHelper(0x6002009b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_DeferRelationshipRecalc(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002009b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_CurrentEdition()
		{
			long result;
			InvokeHelper(0x6002009d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		__int64 get_InstanceHandle64()
		{
			__int64 result;
			InvokeHelper(0x6002009e, DISPATCH_PROPERTYGET, VT_I8, (void*)&result, NULL);
			return result;
		}

		// IVApplication 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVApplicationSettings 包装类

	class CVApplicationSettings : public COleDispatchDriver
	{
	public:
		CVApplicationSettings(){} // 调用 COleDispatchDriver 默认构造函数
		CVApplicationSettings(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVApplicationSettings(const CVApplicationSettings& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVApplicationSettings 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_ObjectType()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_DrawingAids()
		{
			BOOL result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_DrawingAids(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_SnapStrengthRulerX()
		{
			long result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_SnapStrengthRulerX(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_SnapStrengthRulerY()
		{
			long result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_SnapStrengthRulerY(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_SnapStrengthGridX()
		{
			long result;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_SnapStrengthGridX(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_SnapStrengthGridY()
		{
			long result;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_SnapStrengthGridY(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_SnapStrengthGuidesX()
		{
			long result;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_SnapStrengthGuidesX(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_SnapStrengthGuidesY()
		{
			long result;
			InvokeHelper(0x6002000e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_SnapStrengthGuidesY(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002000e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_SnapStrengthPointsX()
		{
			long result;
			InvokeHelper(0x60020010, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_SnapStrengthPointsX(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020010, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_SnapStrengthPointsY()
		{
			long result;
			InvokeHelper(0x60020012, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_SnapStrengthPointsY(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020012, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_SnapStrengthGeometryX()
		{
			long result;
			InvokeHelper(0x60020014, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_SnapStrengthGeometryX(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020014, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_SnapStrengthGeometryY()
		{
			long result;
			InvokeHelper(0x60020016, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_SnapStrengthGeometryY(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020016, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_SnapStrengthExtensionsX()
		{
			long result;
			InvokeHelper(0x60020018, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_SnapStrengthExtensionsX(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020018, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_SnapStrengthExtensionsY()
		{
			long result;
			InvokeHelper(0x6002001a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_SnapStrengthExtensionsY(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002001a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ShowFileSaveWarnings()
		{
			BOOL result;
			InvokeHelper(0x6002001c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ShowFileSaveWarnings(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002001c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ShowFileOpenWarnings()
		{
			BOOL result;
			InvokeHelper(0x6002001e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ShowFileOpenWarnings(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002001e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_DefaultSaveFormat()
		{
			long result;
			InvokeHelper(0x60020020, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_DefaultSaveFormat(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020020, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		unsigned long get_DrawingPageColor()
		{
			unsigned long result;
			InvokeHelper(0x60020022, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
			return result;
		}
		void put_DrawingPageColor(unsigned long newValue)
		{
			static BYTE parms[] = VTS_UI4 ;
			InvokeHelper(0x60020022, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		unsigned long get_DrawingBackgroundColor()
		{
			unsigned long result;
			InvokeHelper(0x60020024, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
			return result;
		}
		void put_DrawingBackgroundColor(unsigned long newValue)
		{
			static BYTE parms[] = VTS_UI4 ;
			InvokeHelper(0x60020024, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		unsigned long get_DrawingBackgroundColorGradient()
		{
			unsigned long result;
			InvokeHelper(0x60020026, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
			return result;
		}
		void put_DrawingBackgroundColorGradient(unsigned long newValue)
		{
			static BYTE parms[] = VTS_UI4 ;
			InvokeHelper(0x60020026, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		unsigned long get_StencilBackgroundColor()
		{
			unsigned long result;
			InvokeHelper(0x60020028, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
			return result;
		}
		void put_StencilBackgroundColor(unsigned long newValue)
		{
			static BYTE parms[] = VTS_UI4 ;
			InvokeHelper(0x60020028, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		unsigned long get_StencilBackgroundColorGradient()
		{
			unsigned long result;
			InvokeHelper(0x6002002a, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
			return result;
		}
		void put_StencilBackgroundColorGradient(unsigned long newValue)
		{
			static BYTE parms[] = VTS_UI4 ;
			InvokeHelper(0x6002002a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		unsigned long get_StencilTextColor()
		{
			unsigned long result;
			InvokeHelper(0x6002002c, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
			return result;
		}
		void put_StencilTextColor(unsigned long newValue)
		{
			static BYTE parms[] = VTS_UI4 ;
			InvokeHelper(0x6002002c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		unsigned long get_PrintPreviewBackgroundColor()
		{
			unsigned long result;
			InvokeHelper(0x6002002e, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
			return result;
		}
		void put_PrintPreviewBackgroundColor(unsigned long newValue)
		{
			static BYTE parms[] = VTS_UI4 ;
			InvokeHelper(0x6002002e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		unsigned long get_FullScreenBackgroundColor()
		{
			unsigned long result;
			InvokeHelper(0x60020030, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
			return result;
		}
		void put_FullScreenBackgroundColor(unsigned long newValue)
		{
			static BYTE parms[] = VTS_UI4 ;
			InvokeHelper(0x60020030, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ShowStartupDialog()
		{
			BOOL result;
			InvokeHelper(0x60020032, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ShowStartupDialog(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020032, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ShowSmartTags()
		{
			BOOL result;
			InvokeHelper(0x60020034, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ShowSmartTags(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020034, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_TextDisplayQuality()
		{
			long result;
			InvokeHelper(0x60020036, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_TextDisplayQuality(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020036, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_HigherQualityShapeDisplay()
		{
			BOOL result;
			InvokeHelper(0x60020038, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_HigherQualityShapeDisplay(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020038, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_SmoothDrawing()
		{
			BOOL result;
			InvokeHelper(0x6002003a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_SmoothDrawing(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002003a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_StencilCharactersPerLine()
		{
			long result;
			InvokeHelper(0x6002003c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_StencilCharactersPerLine(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002003c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_StencilLinesPerMaster()
		{
			long result;
			InvokeHelper(0x6002003e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_StencilLinesPerMaster(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002003e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_UserName()
		{
			CString result;
			InvokeHelper(0x60020040, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_UserName(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020040, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_UserInitials()
		{
			CString result;
			InvokeHelper(0x60020042, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_UserInitials(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020042, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ZoomOnRoll()
		{
			BOOL result;
			InvokeHelper(0x60020044, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ZoomOnRoll(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020044, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_UndoLevels()
		{
			long result;
			InvokeHelper(0x60020046, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_UndoLevels(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020046, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_RecentFilesListSize()
		{
			long result;
			InvokeHelper(0x60020048, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_RecentFilesListSize(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020048, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_CenterSelectionOnZoom()
		{
			BOOL result;
			InvokeHelper(0x6002004a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_CenterSelectionOnZoom(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002004a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ConnectorSplittingEnabled()
		{
			BOOL result;
			InvokeHelper(0x6002004c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ConnectorSplittingEnabled(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002004c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_AsianTextUI()
		{
			long result;
			InvokeHelper(0x6002004e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_AsianTextUI(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002004e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_ComplexTextUI()
		{
			long result;
			InvokeHelper(0x60020050, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_ComplexTextUI(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020050, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_KanaFindAndReplace()
		{
			long result;
			InvokeHelper(0x60020052, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_KanaFindAndReplace(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020052, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_FreeformDrawingPrecision()
		{
			long result;
			InvokeHelper(0x60020054, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_FreeformDrawingPrecision(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020054, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_FreeformDrawingSmoothing()
		{
			long result;
			InvokeHelper(0x60020056, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_FreeformDrawingSmoothing(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020056, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_DeveloperMode()
		{
			BOOL result;
			InvokeHelper(0x60020058, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_DeveloperMode(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020058, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ShowChooseDrawingTypePane()
		{
			BOOL result;
			InvokeHelper(0x6002005a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ShowChooseDrawingTypePane(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002005a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ShowShapeSearchPane()
		{
			BOOL result;
			InvokeHelper(0x6002005c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ShowShapeSearchPane(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002005c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ApplyThemesOnShapeAdd()
		{
			BOOL result;
			InvokeHelper(0x6002005e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ApplyThemesOnShapeAdd(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002005e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_SATextUI()
		{
			long result;
			InvokeHelper(0x60020060, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_BIDITextUI()
		{
			long result;
			InvokeHelper(0x60020061, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_KashidaTextUI()
		{
			long result;
			InvokeHelper(0x60020062, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x60020063, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		BOOL get_ShowMoreShapeHandlesOnHover()
		{
			BOOL result;
			InvokeHelper(0x60020064, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ShowMoreShapeHandlesOnHover(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020064, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_EnableAutoConnect()
		{
			BOOL result;
			InvokeHelper(0x60020066, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_EnableAutoConnect(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020066, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ApplyBackgroundToDocument()
		{
			BOOL result;
			InvokeHelper(0x60020068, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ApplyBackgroundToDocument(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020068, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_TransitionsEnabled()
		{
			BOOL result;
			InvokeHelper(0x6002006a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_TransitionsEnabled(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002006a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_EnableFormulaAutoComplete()
		{
			BOOL result;
			InvokeHelper(0x6002006c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_EnableFormulaAutoComplete(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002006c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_DeleteConnectorsEnabled()
		{
			BOOL result;
			InvokeHelper(0x6002006e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_DeleteConnectorsEnabled(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002006e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_RecentTemplatesListSize()
		{
			long result;
			InvokeHelper(0x60020070, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_RecentTemplatesListSize(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020070, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void SetRasterExportResolution(long resolution, double Width, double Height, long resolutionUnits)
		{
			static BYTE parms[] = VTS_I4 VTS_R8 VTS_R8 VTS_I4 ;
			InvokeHelper(0x60020072, DISPATCH_METHOD, VT_EMPTY, NULL, parms, resolution, Width, Height, resolutionUnits);
		}
		void GetRasterExportResolution(long * pResolution, double * pWidth, double * pHeight, long * pResolutionUnits)
		{
			static BYTE parms[] = VTS_PI4 VTS_PR8 VTS_PR8 VTS_PI4 ;
			InvokeHelper(0x60020073, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pResolution, pWidth, pHeight, pResolutionUnits);
		}
		void SetRasterExportSize(long size, double Width, double Height, long sizeUnits)
		{
			static BYTE parms[] = VTS_I4 VTS_R8 VTS_R8 VTS_I4 ;
			InvokeHelper(0x60020074, DISPATCH_METHOD, VT_EMPTY, NULL, parms, size, Width, Height, sizeUnits);
		}
		void GetRasterExportSize(long * pSize, double * pWidth, double * pHeight, long * pSizeUnits)
		{
			static BYTE parms[] = VTS_PI4 VTS_PR8 VTS_PR8 VTS_PI4 ;
			InvokeHelper(0x60020075, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pSize, pWidth, pHeight, pSizeUnits);
		}
		long get_RasterExportDataFormat()
		{
			long result;
			InvokeHelper(0x60020076, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_RasterExportDataFormat(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020076, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_RasterExportDataCompression()
		{
			long result;
			InvokeHelper(0x60020078, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_RasterExportDataCompression(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020078, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_RasterExportColorReduction()
		{
			long result;
			InvokeHelper(0x6002007a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_RasterExportColorReduction(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002007a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_RasterExportColorFormat()
		{
			long result;
			InvokeHelper(0x6002007c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_RasterExportColorFormat(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002007c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_RasterExportOperation()
		{
			long result;
			InvokeHelper(0x6002007e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_RasterExportOperation(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002007e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_RasterExportRotation()
		{
			long result;
			InvokeHelper(0x60020080, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_RasterExportRotation(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020080, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_RasterExportFlip()
		{
			long result;
			InvokeHelper(0x60020082, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_RasterExportFlip(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020082, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		unsigned long get_RasterExportBackgroundColor()
		{
			unsigned long result;
			InvokeHelper(0x60020084, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
			return result;
		}
		void put_RasterExportBackgroundColor(unsigned long newValue)
		{
			static BYTE parms[] = VTS_UI4 ;
			InvokeHelper(0x60020084, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		unsigned long get_RasterExportTransparencyColor()
		{
			unsigned long result;
			InvokeHelper(0x60020086, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
			return result;
		}
		void put_RasterExportTransparencyColor(unsigned long newValue)
		{
			static BYTE parms[] = VTS_UI4 ;
			InvokeHelper(0x60020086, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_RasterExportUseTransparencyColor()
		{
			BOOL result;
			InvokeHelper(0x60020088, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_RasterExportUseTransparencyColor(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020088, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_RasterExportQuality()
		{
			long result;
			InvokeHelper(0x6002008a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_RasterExportQuality(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002008a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_SVGExportFormat()
		{
			long result;
			InvokeHelper(0x6002008c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_SVGExportFormat(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002008c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_EnterCommitsText()
		{
			BOOL result;
			InvokeHelper(0x6002008e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_EnterCommitsText(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002008e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_UseLocalUserInfo()
		{
			BOOL result;
			InvokeHelper(0x60020090, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_UseLocalUserInfo(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020090, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_RecentFoldersListSize()
		{
			long result;
			InvokeHelper(0x60020092, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_RecentFoldersListSize(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020092, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}

		// IVApplicationSettings 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVBUndoManager 包装类

	class CVBUndoManager : public COleDispatchDriver
	{
	public:
		CVBUndoManager(){} // 调用 COleDispatchDriver 默认构造函数
		CVBUndoManager(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVBUndoManager(const CVBUndoManager& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVBUndoManager 方法
	public:
		void Add(LPDISPATCH pUnit)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x60020000, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pUnit);
		}

		// IVBUndoManager 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVBUndoUnit 包装类

	class CVBUndoUnit : public COleDispatchDriver
	{
	public:
		CVBUndoUnit(){} // 调用 COleDispatchDriver 默认构造函数
		CVBUndoUnit(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVBUndoUnit(const CVBUndoUnit& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVBUndoUnit 方法
	public:
		void Do(LPDISPATCH pMgr)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x60020000, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pMgr);
		}
		CString get_Description()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_UnitTypeCLSID()
		{
			CString result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void OnNextAdd()
		{
			InvokeHelper(0x60020003, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		long get_UnitTypeLong()
		{
			long result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_UnitSize()
		{
			long result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}

		// IVBUndoUnit 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVCell 包装类

	class CVCell : public COleDispatchDriver
	{
	public:
		CVCell(){} // 调用 COleDispatchDriver 默认构造函数
		CVCell(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVCell(const CVCell& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVCell 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Error()
		{
			short result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		CString get_Formula()
		{
			CString result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Formula(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_FormulaForce(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void GlueTo(LPDISPATCH CellObject)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, CellObject);
		}
		void GlueToPos(LPDISPATCH SheetObject, double xPercent, double yPercent)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_R8 VTS_R8 ;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SheetObject, xPercent, yPercent);
		}
		double get_Result(VARIANT& UnitsNameOrCode)
		{
			double result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, parms, &UnitsNameOrCode);
			return result;
		}
		void put_Result(VARIANT& UnitsNameOrCode, double newValue)
		{
			static BYTE parms[] = VTS_VARIANT VTS_R8 ;
			InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &UnitsNameOrCode, newValue);
		}
		void put_ResultForce(VARIANT& UnitsNameOrCode, double newValue)
		{
			static BYTE parms[] = VTS_VARIANT VTS_R8 ;
			InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &UnitsNameOrCode, newValue);
		}
		double get_ResultIU()
		{
			double result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_ResultIU(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_ResultIUForce(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Units()
		{
			short result;
			InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_LocalName()
		{
			CString result;
			InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_RowName(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Shape()
		{
			LPDISPATCH result;
			InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Style()
		{
			LPDISPATCH result;
			InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Section()
		{
			short result;
			InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Row()
		{
			short result;
			InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Column()
		{
			short result;
			InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_IsConstant()
		{
			short result;
			InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_IsInherited()
		{
			short result;
			InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		long get_ResultInt(VARIANT& UnitsNameOrCode, short fRound)
		{
			long result;
			static BYTE parms[] = VTS_VARIANT VTS_I2 ;
			InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, &UnitsNameOrCode, fRound);
			return result;
		}
		void put_ResultFromInt(VARIANT& UnitsNameOrCode, long newValue)
		{
			static BYTE parms[] = VTS_VARIANT VTS_I4 ;
			InvokeHelper(0x9c3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &UnitsNameOrCode, newValue);
		}
		void put_ResultFromIntForce(VARIANT& UnitsNameOrCode, long newValue)
		{
			static BYTE parms[] = VTS_VARIANT VTS_I4 ;
			InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &UnitsNameOrCode, newValue);
		}
		CString get_ResultStr(VARIANT& UnitsNameOrCode)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &UnitsNameOrCode);
			return result;
		}
		void Trigger()
		{
			InvokeHelper(0x1b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		CString get_RowName()
		{
			CString result;
			InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_EventList()
		{
			LPDISPATCH result;
			InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_PersistsEvents()
		{
			short result;
			InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ContainingRow()
		{
			LPDISPATCH result;
			InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_FormulaU()
		{
			CString result;
			InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_FormulaU(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_FormulaForceU(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x20, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_RowNameU()
		{
			CString result;
			InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_RowNameU(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x21, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_InheritedValueSource()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020029, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_InheritedFormulaSource()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002002a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		SAFEARRAY * get_Dependents()
		{
			InvokeHelper(0x6002002b, DISPATCH_PROPERTYGET, VT_EMPTY, NULL, NULL);
		}
		SAFEARRAY * get_Precedents()
		{
			InvokeHelper(0x6002002c, DISPATCH_PROPERTYGET, VT_EMPTY, NULL, NULL);
		}
		long get_ContainingPageID()
		{
			long result;
			InvokeHelper(0x6002002d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_ContainingMasterID()
		{
			long result;
			InvokeHelper(0x6002002e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_ResultStrU(VARIANT& UnitsNameOrCode)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x6002002f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &UnitsNameOrCode);
			return result;
		}

		// IVCell 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVCharacters 包装类

	class CVCharacters : public COleDispatchDriver
	{
	public:
		CVCharacters(){} // 调用 COleDispatchDriver 默认构造函数
		CVCharacters(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVCharacters(const CVCharacters& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVCharacters 方法
	public:
		void AddCustomField(LPCTSTR Formula, short Format)
		{
			static BYTE parms[] = VTS_BSTR VTS_I2 ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Formula, Format);
		}
		void AddField(short Category, short Code, short Format)
		{
			static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Category, Code, Format);
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Begin()
		{
			long result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Begin(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_CharCount()
		{
			long result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_CharProps(short CellIndex, short newValue)
		{
			static BYTE parms[] = VTS_I2 VTS_I2 ;
			InvokeHelper(0x15, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, CellIndex, newValue);
		}
		short get_CharPropsRow(short BiasLorR)
		{
			short result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, BiasLorR);
			return result;
		}
		void Copy()
		{
			InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Cut()
		{
			InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		long get_End()
		{
			long result;
			InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_End(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_FieldCategory()
		{
			short result;
			InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_FieldCode()
		{
			short result;
			InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_FieldFormat()
		{
			short result;
			InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		CString get_FieldFormula()
		{
			CString result;
			InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		short get_IsField()
		{
			short result;
			InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_ParaProps(short CellIndex, short newValue)
		{
			static BYTE parms[] = VTS_I2 VTS_I2 ;
			InvokeHelper(0x16, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, CellIndex, newValue);
		}
		short get_ParaPropsRow(short BiasLorR)
		{
			short result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, BiasLorR);
			return result;
		}
		void Paste()
		{
			InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		short get_TabPropsRow(short BiasLorR)
		{
			short result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, BiasLorR);
			return result;
		}
		long get_RunBegin(short RunType)
		{
			long result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, RunType);
			return result;
		}
		long get_RunEnd(short RunType)
		{
			long result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, RunType);
			return result;
		}
		LPDISPATCH get_Shape()
		{
			LPDISPATCH result;
			InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		CString get_TextAsString()
		{
			CString result;
			InvokeHelper(0x3e7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Text(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_EventList()
		{
			LPDISPATCH result;
			InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_PersistsEvents()
		{
			short result;
			InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		VARIANT get_Text()
		{
			VARIANT result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void AddCustomFieldU(LPCTSTR Formula, short Format)
		{
			static BYTE parms[] = VTS_BSTR VTS_I2 ;
			InvokeHelper(0x1c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Formula, Format);
		}
		CString get_FieldFormulaU()
		{
			CString result;
			InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void Delete()
		{
			InvokeHelper(0x1e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void AddFieldEx(long Category, long Code, long Format, long LangID, long CalendarID)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
			InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Category, Code, Format, LangID, CalendarID);
		}
		long get_ContainingPageID()
		{
			long result;
			InvokeHelper(0x60020024, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_ContainingMasterID()
		{
			long result;
			InvokeHelper(0x60020025, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}

		// IVCharacters 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVCoauthMergeEvent 包装类

	class CVCoauthMergeEvent : public COleDispatchDriver
	{
	public:
		CVCoauthMergeEvent(){} // 调用 COleDispatchDriver 默认构造函数
		CVCoauthMergeEvent(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVCoauthMergeEvent(const CVCoauthMergeEvent& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVCoauthMergeEvent 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_BaseDocument()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_DownloadDocument()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_WorkingDocument()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}

		// IVCoauthMergeEvent 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVColor 包装类

	class CVColor : public COleDispatchDriver
	{
	public:
		CVColor(){} // 调用 COleDispatchDriver 默认构造函数
		CVColor(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVColor(const CVColor& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVColor 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Index16()
		{
			short result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Red()
		{
			short result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Red(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Green()
		{
			short result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Green(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Blue()
		{
			short result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Blue(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Flags()
		{
			short result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Flags(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_PaletteEntry()
		{
			long result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_PaletteEntry(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		long get_Index()
		{
			long result;
			InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}

		// IVColor 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVColors 包装类

	class CVColors : public COleDispatchDriver
	{
	public:
		CVColors(){} // 调用 COleDispatchDriver 默认构造函数
		CVColors(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVColors(const CVColors& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVColors 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Count16()
		{
			short result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item16(short Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x3e7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}

		// IVColors 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVComment 包装类

	class CVComment : public COleDispatchDriver
	{
	public:
		CVComment(){} // 调用 COleDispatchDriver 默认构造函数
		CVComment(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVComment(const CVComment& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVComment 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_AssociatedObject()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		DATE get_CreateDate()
		{
			DATE result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
			return result;
		}
		DATE get_EditDate()
		{
			DATE result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
			return result;
		}
		BOOL get_Collapsed()
		{
			BOOL result;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		CString get_Text()
		{
			CString result;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_AuthorName()
		{
			CString result;
			InvokeHelper(0x60020009, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_AuthorSipAddress()
		{
			CString result;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_AuthorSMTPAddress()
		{
			CString result;
			InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_AuthorInitials()
		{
			CString result;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Collapsed(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_Text(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Delete()
		{
			InvokeHelper(0x6002000f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}

		// IVComment 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVComments 包装类

	class CVComments : public COleDispatchDriver
	{
	public:
		CVComments(){} // 调用 COleDispatchDriver 默认构造函数
		CVComments(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVComments(const CVComments& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVComments 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Add(LPCTSTR Text)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020007, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Text);
			return result;
		}
		void DeleteAll()
		{
			InvokeHelper(0x60020008, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}

		// IVComments 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVConnect 包装类

	class CVConnect : public COleDispatchDriver
	{
	public:
		CVConnect(){} // 调用 COleDispatchDriver 默认构造函数
		CVConnect(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVConnect(const CVConnect& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVConnect 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_FromSheet()
		{
			LPDISPATCH result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ToSheet()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_FromCell()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ToCell()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_FromPart()
		{
			short result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_ToPart()
		{
			short result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Index16()
		{
			short result;
			InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Index()
		{
			long result;
			InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_ContainingPageID()
		{
			long result;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_ContainingMasterID()
		{
			long result;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}

		// IVConnect 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVConnects 包装类

	class CVConnects : public COleDispatchDriver
	{
	public:
		CVConnects(){} // 调用 COleDispatchDriver 默认构造函数
		CVConnects(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVConnects(const CVConnects& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVConnects 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item16(short Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x3e7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		short get_Count16()
		{
			short result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_FromSheet()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ToSheet()
		{
			LPDISPATCH result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}

		// IVConnects 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVContainerProperties 包装类

	class CVContainerProperties : public COleDispatchDriver
	{
	public:
		CVContainerProperties(){} // 调用 COleDispatchDriver 默认构造函数
		CVContainerProperties(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVContainerProperties(const CVContainerProperties& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVContainerProperties 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Shape()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_ContainerType()
		{
			long result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_ListAlignment()
		{
			long result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_ListAlignment(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_ListDirection()
		{
			long result;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_ListDirection(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_LockMembership()
		{
			BOOL result;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_LockMembership(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_ResizeAsNeeded()
		{
			long result;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_ResizeAsNeeded(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Disband()
		{
			InvokeHelper(0x6002000e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void FitToContents()
		{
			InvokeHelper(0x6002000f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		double GetMargin(long MarginUnits)
		{
			double result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020010, DISPATCH_METHOD, VT_R8, (void*)&result, parms, MarginUnits);
			return result;
		}
		void SetMargin(long MarginUnits, double MarginSize)
		{
			static BYTE parms[] = VTS_I4 VTS_R8 ;
			InvokeHelper(0x60020011, DISPATCH_METHOD, VT_EMPTY, NULL, parms, MarginUnits, MarginSize);
		}
		double GetListSpacing(long SpacingUnits)
		{
			double result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020012, DISPATCH_METHOD, VT_R8, (void*)&result, parms, SpacingUnits);
			return result;
		}
		void SetListSpacing(long SpacingUnits, double SpacingSize)
		{
			static BYTE parms[] = VTS_I4 VTS_R8 ;
			InvokeHelper(0x60020013, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SpacingUnits, SpacingSize);
		}
		void InsertListMember(LPUNKNOWN ObjectToInsert, long Position)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_I4 ;
			InvokeHelper(0x60020014, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ObjectToInsert, Position);
		}
		long GetListMemberPosition(LPDISPATCH ShapeMember)
		{
			long result;
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x60020015, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ShapeMember);
			return result;
		}
		long GetMemberState(LPDISPATCH Shape)
		{
			long result;
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x60020016, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Shape);
			return result;
		}
		void RemoveMember(LPUNKNOWN ObjectToRemove)
		{
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0x60020017, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ObjectToRemove);
		}
		void ReorderListMember(LPUNKNOWN ObjectToReorder, long Position)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_I4 ;
			InvokeHelper(0x60020018, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ObjectToReorder, Position);
		}
		SAFEARRAY * GetListMembers()
		{
			InvokeHelper(0x60020019, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		SAFEARRAY * GetMemberShapes(long ContainerFlags)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002001a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ContainerFlags);
		}
		void AddMember(LPUNKNOWN pObjectToAdd, long AddOptions)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_I4 ;
			InvokeHelper(0x6002001b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pObjectToAdd, AddOptions);
		}
		LPDISPATCH get_OverlappedList()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002001c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_OverlappedList(LPDISPATCH newValue)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x6002001c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void RotateFlipList(long Direction)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002001e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Direction);
		}
		long get_ContainerStyle()
		{
			long result;
			InvokeHelper(0x6002001f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_ContainerStyle(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002001f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_HeadingStyle()
		{
			long result;
			InvokeHelper(0x60020021, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_HeadingStyle(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020021, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}

		// IVContainerProperties 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVCurve 包装类

	class CVCurve : public COleDispatchDriver
	{
	public:
		CVCurve(){} // 调用 COleDispatchDriver 默认构造函数
		CVCurve(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVCurve(const CVCurve& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVCurve 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Closed()
		{
			short result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void Points(double Tolerance, SAFEARRAY * * xyArray)
		{
			static BYTE parms[] = VTS_R8 VTS_UNKNOWN ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Tolerance, xyArray);
		}
		double get_Start()
		{
			double result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		double get_End()
		{
			double result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void Point(double t, double * x, double * y)
		{
			static BYTE parms[] = VTS_R8 VTS_PR8 VTS_PR8 ;
			InvokeHelper(0x0, DISPATCH_METHOD, VT_EMPTY, NULL, parms, t, x, y);
		}
		void PointAndDerivatives(double t, short n, double * x, double * y, double * dxdt, double * dydt, double * ddxdt, double * ddydt)
		{
			static BYTE parms[] = VTS_R8 VTS_I2 VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 ;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, t, n, x, y, dxdt, dydt, ddxdt, ddydt);
		}

		// IVCurve 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVDataColumn 包装类

	class CVDataColumn : public COleDispatchDriver
	{
	public:
		CVDataColumn(){} // 调用 COleDispatchDriver 默认构造函数
		CVDataColumn(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVDataColumn(const CVDataColumn& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVDataColumn 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_DataRecordset()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_DisplayName()
		{
			CString result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_DisplayName(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Visible()
		{
			BOOL result;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Visible(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		VARIANT GetProperty(long Property)
		{
			VARIANT result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002000a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, Property);
			return result;
		}
		void SetProperty(long Property, VARIANT& Value)
		{
			static BYTE parms[] = VTS_I4 VTS_VARIANT ;
			InvokeHelper(0x6002000b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Property, &Value);
		}
		BOOL get_Hyperlink()
		{
			BOOL result;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Hyperlink(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}

		// IVDataColumn 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVDataColumns 包装类

	class CVDataColumns : public COleDispatchDriver
	{
	public:
		CVDataColumns(){} // 调用 COleDispatchDriver 默认构造函数
		CVDataColumns(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVDataColumns(const CVDataColumns& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVDataColumns 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_DataRecordset()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(VARIANT& IndexOrName)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &IndexOrName);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		void SetColumnProperties(SAFEARRAY * * ColumnNames, SAFEARRAY * * Properties, SAFEARRAY * * Values)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x60020008, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ColumnNames, Properties, Values);
		}

		// IVDataColumns 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVDataConnection 包装类

	class CVDataConnection : public COleDispatchDriver
	{
	public:
		CVDataConnection(){} // 调用 COleDispatchDriver 默认构造函数
		CVDataConnection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVDataConnection(const CVDataConnection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVDataConnection 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		long get_ID()
		{
			long result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_ConnectionString()
		{
			CString result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_ConnectionString(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_FileName()
		{
			CString result;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long get_Timeout()
		{
			long result;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Timeout(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}

		// IVDataConnection 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVDataRecordset 包装类

	class CVDataRecordset : public COleDispatchDriver
	{
	public:
		CVDataRecordset(){} // 调用 COleDispatchDriver 默认构造函数
		CVDataRecordset(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVDataRecordset(const CVDataRecordset& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVDataRecordset 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		long get_ID()
		{
			long result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Name(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_LinkReplaceBehavior()
		{
			long result;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_LinkReplaceBehavior(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_DataConnection()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020009, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_DataColumns()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void GetPrimaryKey(long * PrimaryKeySettings, SAFEARRAY * * PrimaryKey)
		{
			static BYTE parms[] = VTS_PI4 VTS_UNKNOWN ;
			InvokeHelper(0x6002000b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, PrimaryKeySettings, PrimaryKey);
		}
		void SetPrimaryKey(long PrimaryKeySettings, SAFEARRAY * * PrimaryKey)
		{
			static BYTE parms[] = VTS_I4 VTS_UNKNOWN ;
			InvokeHelper(0x6002000c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, PrimaryKeySettings, PrimaryKey);
		}
		CString get_CommandString()
		{
			CString result;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_CommandString(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_DataAsXML()
		{
			CString result;
			InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		SAFEARRAY * GetDataRowIDs(LPCTSTR CriteriaString)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020010, DISPATCH_METHOD, VT_EMPTY, NULL, parms, CriteriaString);
		}
		SAFEARRAY * GetRowData(long DataRowID)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020011, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DataRowID);
		}
		void Delete()
		{
			InvokeHelper(0x60020012, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Refresh()
		{
			InvokeHelper(0x60020013, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void RefreshUsingXML(LPCTSTR NewDataAsXML)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020014, DISPATCH_METHOD, VT_EMPTY, NULL, parms, NewDataAsXML);
		}
		DATE get_TimeRefreshed()
		{
			DATE result;
			InvokeHelper(0x60020015, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
			return result;
		}
		long get_RefreshInterval()
		{
			long result;
			InvokeHelper(0x60020016, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_RefreshInterval(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020016, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_RefreshSettings()
		{
			long result;
			InvokeHelper(0x60020018, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_RefreshSettings(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020018, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_EventList()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002001a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		SAFEARRAY * GetAllRefreshConflicts()
		{
			InvokeHelper(0x6002001b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void RemoveRefreshConflict(LPDISPATCH ShapeInConflict)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x6002001c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ShapeInConflict);
		}
		SAFEARRAY * GetMatchingRowsForRefreshConflict(LPDISPATCH ShapeInConflict)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x6002001d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ShapeInConflict);
		}

		// IVDataRecordset 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVDataRecordsetChangedEvent 包装类

	class CVDataRecordsetChangedEvent : public COleDispatchDriver
	{
	public:
		CVDataRecordsetChangedEvent(){} // 调用 COleDispatchDriver 默认构造函数
		CVDataRecordsetChangedEvent(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVDataRecordsetChangedEvent(const CVDataRecordsetChangedEvent& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVDataRecordsetChangedEvent 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_DataRecordset()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		SAFEARRAY * get_DataRowsAdded()
		{
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_EMPTY, NULL, NULL);
		}
		SAFEARRAY * get_DataRowsDeleted()
		{
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_EMPTY, NULL, NULL);
		}
		SAFEARRAY * get_DataColumnsAdded()
		{
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_EMPTY, NULL, NULL);
		}
		SAFEARRAY * get_DataColumnsDeleted()
		{
			InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_EMPTY, NULL, NULL);
		}
		SAFEARRAY * get_DataColumnsChanged()
		{
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_EMPTY, NULL, NULL);
		}

		// IVDataRecordsetChangedEvent 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVDataRecordsets 包装类

	class CVDataRecordsets : public COleDispatchDriver
	{
	public:
		CVDataRecordsets(){} // 调用 COleDispatchDriver 默认构造函数
		CVDataRecordsets(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVDataRecordsets(const CVDataRecordsets& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVDataRecordsets 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		LPDISPATCH get_ItemFromID(long ID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, ID);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_EventList()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Add(VARIANT& ConnectionIDOrString, LPCTSTR CommandString, long AddOptions, LPCTSTR Name)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT VTS_BSTR VTS_I4 VTS_BSTR ;
			InvokeHelper(0x60020009, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &ConnectionIDOrString, CommandString, AddOptions, Name);
			return result;
		}
		LPDISPATCH AddFromXML(LPCTSTR XMLString, long AddOptions, LPCTSTR Name)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR ;
			InvokeHelper(0x6002000a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, XMLString, AddOptions, Name);
			return result;
		}
		LPDISPATCH AddFromConnectionFile(LPCTSTR FileName, long AddOptions, LPCTSTR Name)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR ;
			InvokeHelper(0x6002000b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FileName, AddOptions, Name);
			return result;
		}
		void GetLastDataError(long * DataErrorCode, BSTR * DataErrorDescription, long * RecordsetID)
		{
			static BYTE parms[] = VTS_PI4 VTS_PBSTR VTS_PI4 ;
			InvokeHelper(0x6002000c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DataErrorCode, DataErrorDescription, RecordsetID);
		}

		// IVDataRecordsets 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVDispExtender 包装类

	class CVDispExtender : public COleDispatchDriver
	{
	public:
		CVDispExtender(){} // 调用 COleDispatchDriver 默认构造函数
		CVDispExtender(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVDispExtender(const CVDispExtender& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVDispExtender 方法
	public:
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x80010000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Name(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x80010000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPUNKNOWN get_Object()
		{
			LPUNKNOWN result;
			InvokeHelper(DISPID_Object, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get_Parent()
		{
			LPUNKNOWN result;
			InvokeHelper(0x80010008, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		void Delete()
		{
			InvokeHelper(DISPID_Delete, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Index()
		{
			InvokeHelper(0xfffffcdc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_Shape()
		{
			LPDISPATCH result;
			InvokeHelper(0x80010100, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void VoidGroup()
		{
			InvokeHelper(0x8001012d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void BringForward()
		{
			InvokeHelper(0x8001012e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void BringToFront()
		{
			InvokeHelper(0x8001012f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void ConvertToGroup()
		{
			InvokeHelper(0x80010130, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void SendBackward()
		{
			InvokeHelper(0x80010134, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void SendToBack()
		{
			InvokeHelper(0x80010135, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x8001012c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ShapeParent()
		{
			LPDISPATCH result;
			InvokeHelper(0x80010138, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x80010101, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Master()
		{
			LPDISPATCH result;
			InvokeHelper(0x80010115, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Cells(LPCTSTR localeSpecificCellName)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x8001010d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, localeSpecificCellName);
			return result;
		}
		LPDISPATCH get_CellsSRC(short Section, short Row, short Column)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
			InvokeHelper(0x8001010e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Section, Row, Column);
			return result;
		}
		CString get_Data1()
		{
			CString result;
			InvokeHelper(0x8001010f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Data1(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x8001010f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Data2()
		{
			CString result;
			InvokeHelper(0x80010110, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Data2(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x80010110, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Data3()
		{
			CString result;
			InvokeHelper(0x80010111, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Data3(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x80010111, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Help()
		{
			CString result;
			InvokeHelper(0x80010112, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Help(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x80010112, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_NameID()
		{
			CString result;
			InvokeHelper(0x80010104, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void ShapeCopy()
		{
			InvokeHelper(0x80010109, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void ShapeCut()
		{
			InvokeHelper(0x8001010a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void ShapeDelete()
		{
			InvokeHelper(0x8001010b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void VoidShapeDuplicate()
		{
			InvokeHelper(0x8001010c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		short get_RowCount(short Section)
		{
			short result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x80010118, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, Section);
			return result;
		}
		short AddSection(short Section)
		{
			short result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x80010119, DISPATCH_METHOD, VT_I2, (void*)&result, parms, Section);
			return result;
		}
		void DeleteSection(short Section)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x8001011a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Section);
		}
		short AddRow(short Section, short Row, short RowTag)
		{
			short result;
			static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
			InvokeHelper(0x8001011b, DISPATCH_METHOD, VT_I2, (void*)&result, parms, Section, Row, RowTag);
			return result;
		}
		void DeleteRow(short Section, short Row)
		{
			static BYTE parms[] = VTS_I2 VTS_I2 ;
			InvokeHelper(0x8001011c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Section, Row);
		}
		short get_RowsCellCount(short Section, short Row)
		{
			short result;
			static BYTE parms[] = VTS_I2 VTS_I2 ;
			InvokeHelper(0x8001011d, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, Section, Row);
			return result;
		}
		short get_RowType(short Section, short Row)
		{
			short result;
			static BYTE parms[] = VTS_I2 VTS_I2 ;
			InvokeHelper(0x8001011e, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, Section, Row);
			return result;
		}
		void put_RowType(short Section, short Row, short newValue)
		{
			static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
			InvokeHelper(0x8001011e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, Section, Row, newValue);
		}
		void SetCenter(double xPos, double yPos)
		{
			static BYTE parms[] = VTS_R8 VTS_R8 ;
			InvokeHelper(0x8001011f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, xPos, yPos);
		}
		LPDISPATCH get_Connects()
		{
			LPDISPATCH result;
			InvokeHelper(0x80010122, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ShapeIndex16()
		{
			short result;
			InvokeHelper(0x80010123, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		CString get_Style()
		{
			CString result;
			InvokeHelper(0x80010124, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Style(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x80010124, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_StyleKeepFmt(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x80010128, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_LineStyle()
		{
			CString result;
			InvokeHelper(0x80010125, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_LineStyle(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x80010125, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_LineStyleKeepFmt(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x80010129, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_FillStyle()
		{
			CString result;
			InvokeHelper(0x80010126, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_FillStyle(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x80010126, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_FillStyleKeepFmt(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x8001012a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Export(LPCTSTR FileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x80010139, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
		}
		CString get_UniqueID(short fUniqueID)
		{
			CString result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x8001013d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, fUniqueID);
			return result;
		}
		LPDISPATCH get_ContainingPage()
		{
			LPDISPATCH result;
			InvokeHelper(0x8001013e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ContainingMaster()
		{
			LPDISPATCH result;
			InvokeHelper(0x8001013f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ContainingShape()
		{
			LPDISPATCH result;
			InvokeHelper(0x80010140, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_SectionExists(short Section, short fExistsLocally)
		{
			short result;
			static BYTE parms[] = VTS_I2 VTS_I2 ;
			InvokeHelper(0x80010141, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, Section, fExistsLocally);
			return result;
		}
		short get_RowExists(short Section, short Row, short fExistsLocally)
		{
			short result;
			static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
			InvokeHelper(0x80010142, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, Section, Row, fExistsLocally);
			return result;
		}
		short get_CellExists(LPCTSTR localeSpecificCellName, short fExistsLocally)
		{
			short result;
			static BYTE parms[] = VTS_BSTR VTS_I2 ;
			InvokeHelper(0x80010143, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, localeSpecificCellName, fExistsLocally);
			return result;
		}
		short get_CellsSRCExists(short Section, short Row, short Column, short fExistsLocally)
		{
			short result;
			static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 VTS_I2 ;
			InvokeHelper(0x80010144, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, Section, Row, Column, fExistsLocally);
			return result;
		}
		short get_LayerCount()
		{
			short result;
			InvokeHelper(0x80010145, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Layer(short Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x80010146, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		short AddNamedRow(short Section, LPCTSTR RowName, short RowTag)
		{
			short result;
			static BYTE parms[] = VTS_I2 VTS_BSTR VTS_I2 ;
			InvokeHelper(0x80010147, DISPATCH_METHOD, VT_I2, (void*)&result, parms, Section, RowName, RowTag);
			return result;
		}
		short AddRows(short Section, short Row, short RowTag, short RowCount)
		{
			short result;
			static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 VTS_I2 ;
			InvokeHelper(0x80010148, DISPATCH_METHOD, VT_I2, (void*)&result, parms, Section, Row, RowTag, RowCount);
			return result;
		}
		LPDISPATCH get_EventList()
		{
			LPDISPATCH result;
			InvokeHelper(0x80010149, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_PersistsEvents()
		{
			short result;
			InvokeHelper(0x8001014a, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		CString get_ClassID()
		{
			CString result;
			InvokeHelper(0x80010156, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ShapeObject()
		{
			LPDISPATCH result;
			InvokeHelper(0x80010158, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH OpenSheetWindow()
		{
			LPDISPATCH result;
			InvokeHelper(0x8001015a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ShapeID16()
		{
			short result;
			InvokeHelper(0x8001015b, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void GetFormulas(SAFEARRAY * * SRCStream, SAFEARRAY * * formulaArray)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x8001015d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SRCStream, formulaArray);
		}
		void GetResults(SAFEARRAY * * SRCStream, short Flags, SAFEARRAY * * UnitsNamesOrCodes, SAFEARRAY * * resultArray)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_I2 VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x8001015e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SRCStream, Flags, UnitsNamesOrCodes, resultArray);
		}
		short SetFormulas(SAFEARRAY * * SRCStream, SAFEARRAY * * formulaArray, short Flags)
		{
			short result;
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN VTS_I2 ;
			InvokeHelper(0x8001015f, DISPATCH_METHOD, VT_I2, (void*)&result, parms, SRCStream, formulaArray, Flags);
			return result;
		}
		short SetResults(SAFEARRAY * * SRCStream, SAFEARRAY * * UnitsNamesOrCodes, SAFEARRAY * * resultArray, short Flags)
		{
			short result;
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN VTS_UNKNOWN VTS_I2 ;
			InvokeHelper(0x80010160, DISPATCH_METHOD, VT_I2, (void*)&result, parms, SRCStream, UnitsNamesOrCodes, resultArray, Flags);
			return result;
		}
		LPDISPATCH get_FromConnects()
		{
			LPDISPATCH result;
			InvokeHelper(0x80010161, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void BoundingBox(short Flags, double * lpr8Left, double * lpr8Bottom, double * lpr8Right, double * lpr8Top)
		{
			static BYTE parms[] = VTS_I2 VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 ;
			InvokeHelper(0x80010163, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Flags, lpr8Left, lpr8Bottom, lpr8Right, lpr8Top);
		}
		short HitTest(double xPos, double yPos, double Tolerance)
		{
			short result;
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 ;
			InvokeHelper(0x80010164, DISPATCH_METHOD, VT_I2, (void*)&result, parms, xPos, yPos, Tolerance);
			return result;
		}
		LPDISPATCH get_Hyperlink()
		{
			LPDISPATCH result;
			InvokeHelper(0x80010165, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_ProgID()
		{
			CString result;
			InvokeHelper(0x80010166, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		short get_ObjectIsInherited()
		{
			short result;
			InvokeHelper(0x80010167, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		long get_ShapeID()
		{
			long result;
			InvokeHelper(0x8001016b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_ShapeIndex()
		{
			long result;
			InvokeHelper(0x8001016c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Group()
		{
			LPDISPATCH result;
			InvokeHelper(0x80010182, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH ShapeDuplicate()
		{
			LPDISPATCH result;
			InvokeHelper(0x80010183, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void VisualBoundingBox(short Flags, double * lpr8Left, double * lpr8Bottom, double * lpr8Right, double * lpr8Top)
		{
			static BYTE parms[] = VTS_I2 VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 ;
			InvokeHelper(0x80010184, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Flags, lpr8Left, lpr8Bottom, lpr8Right, lpr8Top);
		}

		// IVDispExtender 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVDocument 包装类

	class CVDocument : public COleDispatchDriver
	{
	public:
		CVDocument(){} // 调用 COleDispatchDriver 默认构造函数
		CVDocument(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVDocument(const CVDocument& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVDocument 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_InPlace()
		{
			short result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Masters()
		{
			LPDISPATCH result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Pages()
		{
			LPDISPATCH result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Styles()
		{
			LPDISPATCH result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Path()
		{
			CString result;
			InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_FullName()
		{
			CString result;
			InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Drop(LPUNKNOWN ObjectToDrop, short xPos, short yPos)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_UNKNOWN VTS_I2 VTS_I2 ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ObjectToDrop, xPos, yPos);
			return result;
		}
		short get_Index()
		{
			short result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_old_Saved()
		{
			short result;
			InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_old_Saved(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_ReadOnly()
		{
			short result;
			InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short Save()
		{
			short result;
			InvokeHelper(0xc, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
			return result;
		}
		short SaveAs(LPCTSTR FileName)
		{
			short result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xd, DISPATCH_METHOD, VT_I2, (void*)&result, parms, FileName);
			return result;
		}
		long get_old_Version()
		{
			long result;
			InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_old_Version(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Title()
		{
			CString result;
			InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Title(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Subject()
		{
			CString result;
			InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Subject(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Creator()
		{
			CString result;
			InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Creator(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Keywords()
		{
			CString result;
			InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Keywords(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Description()
		{
			CString result;
			InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Description(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x13, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Print()
		{
			InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Close()
		{
			InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_CustomMenus()
		{
			LPDISPATCH result;
			InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void SetCustomMenus(LPDISPATCH MenusObject)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, parms, MenusObject);
		}
		CString get_CustomMenusFile()
		{
			CString result;
			InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_CustomMenusFile(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void ClearCustomMenus()
		{
			InvokeHelper(0x1b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_CustomToolbars()
		{
			LPDISPATCH result;
			InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void SetCustomToolbars(LPDISPATCH ToolbarsObject)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ToolbarsObject);
		}
		CString get_CustomToolbarsFile()
		{
			CString result;
			InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_CustomToolbarsFile(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void ClearCustomToolbars()
		{
			InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_Fonts()
		{
			LPDISPATCH result;
			InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Colors()
		{
			LPDISPATCH result;
			InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_EventList()
		{
			LPDISPATCH result;
			InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Template()
		{
			CString result;
			InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void SaveAsEx(LPCTSTR FileName, short SaveFlags)
		{
			static BYTE parms[] = VTS_BSTR VTS_I2 ;
			InvokeHelper(0x24, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName, SaveFlags);
		}
		short get_old_SavePreviewMode()
		{
			short result;
			InvokeHelper(0x25, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_old_SavePreviewMode(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x25, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void GetIcon(short ID, LPCTSTR FileName)
		{
			static BYTE parms[] = VTS_I2 VTS_BSTR ;
			InvokeHelper(0x26, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ID, FileName);
		}
		void SetIcon(short ID, short Index, LPCTSTR FileName)
		{
			static BYTE parms[] = VTS_I2 VTS_I2 VTS_BSTR ;
			InvokeHelper(0x27, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ID, Index, FileName);
		}
		double get_LeftMargin(VARIANT& UnitsNameOrCode)
		{
			double result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, parms, &UnitsNameOrCode);
			return result;
		}
		void put_LeftMargin(VARIANT& UnitsNameOrCode, double newValue)
		{
			static BYTE parms[] = VTS_VARIANT VTS_R8 ;
			InvokeHelper(0x28, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &UnitsNameOrCode, newValue);
		}
		double get_RightMargin(VARIANT& UnitsNameOrCode)
		{
			double result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x29, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, parms, &UnitsNameOrCode);
			return result;
		}
		void put_RightMargin(VARIANT& UnitsNameOrCode, double newValue)
		{
			static BYTE parms[] = VTS_VARIANT VTS_R8 ;
			InvokeHelper(0x29, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &UnitsNameOrCode, newValue);
		}
		double get_TopMargin(VARIANT& UnitsNameOrCode)
		{
			double result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x2a, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, parms, &UnitsNameOrCode);
			return result;
		}
		void put_TopMargin(VARIANT& UnitsNameOrCode, double newValue)
		{
			static BYTE parms[] = VTS_VARIANT VTS_R8 ;
			InvokeHelper(0x2a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &UnitsNameOrCode, newValue);
		}
		double get_BottomMargin(VARIANT& UnitsNameOrCode)
		{
			double result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x2b, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, parms, &UnitsNameOrCode);
			return result;
		}
		void put_BottomMargin(VARIANT& UnitsNameOrCode, double newValue)
		{
			static BYTE parms[] = VTS_VARIANT VTS_R8 ;
			InvokeHelper(0x2b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &UnitsNameOrCode, newValue);
		}
		short get_old_PrintLandscape()
		{
			short result;
			InvokeHelper(0x2c, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_old_PrintLandscape(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x2c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_old_PrintCenteredH()
		{
			short result;
			InvokeHelper(0x2d, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_old_PrintCenteredH(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x2d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_old_PrintCenteredV()
		{
			short result;
			InvokeHelper(0x2e, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_old_PrintCenteredV(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x2e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		double get_PrintScale()
		{
			double result;
			InvokeHelper(0x2f, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_PrintScale(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x2f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_old_PrintFitOnPages()
		{
			short result;
			InvokeHelper(0x30, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_old_PrintFitOnPages(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x30, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_PrintPagesAcross()
		{
			short result;
			InvokeHelper(0x31, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_PrintPagesAcross(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x31, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_PrintPagesDown()
		{
			short result;
			InvokeHelper(0x32, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_PrintPagesDown(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x32, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_DefaultStyle()
		{
			CString result;
			InvokeHelper(0x33, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_DefaultStyle(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x33, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_DefaultLineStyle()
		{
			CString result;
			InvokeHelper(0x34, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_DefaultLineStyle(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x34, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_DefaultFillStyle()
		{
			CString result;
			InvokeHelper(0x35, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_DefaultFillStyle(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x35, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_DefaultTextStyle()
		{
			CString result;
			InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_DefaultTextStyle(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x36, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_PersistsEvents()
		{
			short result;
			InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH OpenStencilWindow()
		{
			LPDISPATCH result;
			InvokeHelper(0x38, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void ParseLine(LPCTSTR Line)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x39, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Line);
		}
		void ExecuteLine(LPCTSTR Line)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x3a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Line);
		}
		LPDISPATCH get_VBProject()
		{
			LPDISPATCH result;
			InvokeHelper(0x3b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		double get_PaperWidth(VARIANT& UnitsNameOrCode)
		{
			double result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x3c, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, parms, &UnitsNameOrCode);
			return result;
		}
		double get_PaperHeight(VARIANT& UnitsNameOrCode)
		{
			double result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, parms, &UnitsNameOrCode);
			return result;
		}
		short get_old_PaperSize()
		{
			short result;
			InvokeHelper(0x3e, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_old_PaperSize(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x3e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void FollowHyperlink45(LPCTSTR Target, LPCTSTR Location)
		{
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x3f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Target, Location);
		}
		CString get_CodeName()
		{
			CString result;
			InvokeHelper(0x80010000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		short get_old_Mode()
		{
			short result;
			InvokeHelper(0x40, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_old_Mode(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x40, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_OLEObjects()
		{
			LPDISPATCH result;
			InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void FollowHyperlink(LPCTSTR Address, LPCTSTR SubAddress, VARIANT& ExtraInfo, VARIANT& Frame, VARIANT& NewWindow, VARIANT& res1, VARIANT& res2, VARIANT& res3)
		{
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x42, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Address, SubAddress, &ExtraInfo, &Frame, &NewWindow, &res1, &res2, &res3);
		}
		CString get_Manager()
		{
			CString result;
			InvokeHelper(0x43, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Manager(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x43, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Company()
		{
			CString result;
			InvokeHelper(0x44, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Company(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x44, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Category()
		{
			CString result;
			InvokeHelper(0x45, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Category(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x45, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_HyperlinkBase()
		{
			CString result;
			InvokeHelper(0x46, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_HyperlinkBase(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x46, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_DocumentSheet()
		{
			LPDISPATCH result;
			InvokeHelper(0x47, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Container()
		{
			LPDISPATCH result;
			InvokeHelper(0x48, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_ClassID()
		{
			CString result;
			InvokeHelper(0x49, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_ProgID()
		{
			CString result;
			InvokeHelper(0x4a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_MasterShortcuts()
		{
			LPDISPATCH result;
			InvokeHelper(0x4b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_AlternateNames()
		{
			CString result;
			InvokeHelper(0x4c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_AlternateNames(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x4c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_GestureFormatSheet()
		{
			LPDISPATCH result;
			InvokeHelper(0x4d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void ClearGestureFormatSheet()
		{
			InvokeHelper(0x4e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		BOOL get_AutoRecover()
		{
			BOOL result;
			InvokeHelper(0x4f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_AutoRecover(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x4f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Saved()
		{
			BOOL result;
			InvokeHelper(0x60020072, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Saved(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020072, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Version()
		{
			long result;
			InvokeHelper(0x60020074, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Version(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020074, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_SavePreviewMode()
		{
			long result;
			InvokeHelper(0x60020076, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_SavePreviewMode(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020076, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_PrintLandscape()
		{
			BOOL result;
			InvokeHelper(0x60020078, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_PrintLandscape(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020078, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_PrintCenteredH()
		{
			BOOL result;
			InvokeHelper(0x6002007a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_PrintCenteredH(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002007a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_PrintCenteredV()
		{
			BOOL result;
			InvokeHelper(0x6002007c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_PrintCenteredV(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002007c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_PrintFitOnPages()
		{
			BOOL result;
			InvokeHelper(0x6002007e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_PrintFitOnPages(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002007e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_PaperSize()
		{
			long result;
			InvokeHelper(0x60020080, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_PaperSize(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020080, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Mode()
		{
			long result;
			InvokeHelper(0x60020082, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Mode(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020082, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_SnapEnabled()
		{
			BOOL result;
			InvokeHelper(0x60020084, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_SnapEnabled(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020084, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_SnapSettings()
		{
			long result;
			InvokeHelper(0x60020086, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_SnapSettings(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020086, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_SnapExtensions()
		{
			long result;
			InvokeHelper(0x60020088, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_SnapExtensions(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020088, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		SAFEARRAY * get_SnapAngles()
		{
			InvokeHelper(0x6002008a, DISPATCH_PROPERTYGET, VT_EMPTY, NULL, NULL);
		}
		void put_SnapAngles(SAFEARRAY * * newValue)
		{
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0x6002008a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_GlueEnabled()
		{
			BOOL result;
			InvokeHelper(0x6002008c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_GlueEnabled(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002008c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_GlueSettings()
		{
			long result;
			InvokeHelper(0x6002008e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_GlueSettings(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002008e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_DynamicGridEnabled()
		{
			BOOL result;
			InvokeHelper(0x60020090, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_DynamicGridEnabled(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020090, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_DefaultGuideStyle()
		{
			CString result;
			InvokeHelper(0x60020092, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_DefaultGuideStyle(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020092, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Protection(VARIANT& bstrPassword)
		{
			long result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020094, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, &bstrPassword);
			return result;
		}
		void put_Protection(VARIANT& bstrPassword, long newValue)
		{
			static BYTE parms[] = VTS_VARIANT VTS_I4 ;
			InvokeHelper(0x60020094, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &bstrPassword, newValue);
		}
		CString get_Printer()
		{
			CString result;
			InvokeHelper(0x60020096, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Printer(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020096, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_PrintCopies()
		{
			long result;
			InvokeHelper(0x60020098, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_PrintCopies(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020098, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_HeaderLeft()
		{
			CString result;
			InvokeHelper(0x6002009a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_HeaderLeft(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002009a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_HeaderCenter()
		{
			CString result;
			InvokeHelper(0x6002009c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_HeaderCenter(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002009c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_HeaderRight()
		{
			CString result;
			InvokeHelper(0x6002009e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_HeaderRight(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002009e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		double get_HeaderMargin(VARIANT& UnitsNameOrCode)
		{
			double result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x600200a0, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, parms, &UnitsNameOrCode);
			return result;
		}
		void put_HeaderMargin(VARIANT& UnitsNameOrCode, double newValue)
		{
			static BYTE parms[] = VTS_VARIANT VTS_R8 ;
			InvokeHelper(0x600200a0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &UnitsNameOrCode, newValue);
		}
		CString get_FooterLeft()
		{
			CString result;
			InvokeHelper(0x600200a2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_FooterLeft(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x600200a2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_FooterCenter()
		{
			CString result;
			InvokeHelper(0x600200a4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_FooterCenter(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x600200a4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_FooterRight()
		{
			CString result;
			InvokeHelper(0x600200a6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_FooterRight(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x600200a6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		double get_FooterMargin(VARIANT& UnitsNameOrCode)
		{
			double result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x600200a8, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, parms, &UnitsNameOrCode);
			return result;
		}
		void put_FooterMargin(VARIANT& UnitsNameOrCode, double newValue)
		{
			static BYTE parms[] = VTS_VARIANT VTS_R8 ;
			InvokeHelper(0x600200a8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &UnitsNameOrCode, newValue);
		}
		LPDISPATCH get_HeaderFooterFont()
		{
			LPDISPATCH result;
			InvokeHelper(0x600200aa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void putref_HeaderFooterFont(LPDISPATCH newValue)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x600200aa, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms, newValue);
		}
		unsigned long get_HeaderFooterColor()
		{
			unsigned long result;
			InvokeHelper(0x600200ac, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
			return result;
		}
		void put_HeaderFooterColor(unsigned long newValue)
		{
			static BYTE parms[] = VTS_UI4 ;
			InvokeHelper(0x600200ac, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_Password(VARIANT& bstrExistingPassword, LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_VARIANT VTS_BSTR ;
			InvokeHelper(0x600200ae, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &bstrExistingPassword, newValue);
		}
		LPDISPATCH get_PreviewPicture()
		{
			LPDISPATCH result;
			InvokeHelper(0x600200af, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void putref_PreviewPicture(LPDISPATCH newValue)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x600200af, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms, newValue);
		}
		void Clean(VARIANT& nTargets, VARIANT& nActions, VARIANT& nAlerts, VARIANT& nFixes, VARIANT& bStopOnError, VARIANT& bLogFileName, VARIANT& nReserved)
		{
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x600200b1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &nTargets, &nActions, &nAlerts, &nFixes, &bStopOnError, &bLogFileName, &nReserved);
		}
		long get_BuildNumberCreated()
		{
			long result;
			InvokeHelper(0x600200b2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_BuildNumberEdited()
		{
			long result;
			InvokeHelper(0x600200b3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		DATE get_TimeCreated()
		{
			DATE result;
			InvokeHelper(0x600200b4, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
			return result;
		}
		DATE get_Time()
		{
			DATE result;
			InvokeHelper(0x600200b5, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
			return result;
		}
		DATE get_TimeEdited()
		{
			DATE result;
			InvokeHelper(0x600200b6, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
			return result;
		}
		DATE get_TimePrinted()
		{
			DATE result;
			InvokeHelper(0x600200b7, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
			return result;
		}
		DATE get_TimeSaved()
		{
			DATE result;
			InvokeHelper(0x600200b8, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
			return result;
		}
		void CopyPreviewPicture(LPDISPATCH pSourceDoc)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x600200b9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pSourceDoc);
		}
		BOOL get_ContainsWorkspace()
		{
			BOOL result;
			InvokeHelper(0x600200ba, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		SAFEARRAY * get_EmailRoutingData()
		{
			InvokeHelper(0x600200bb, DISPATCH_PROPERTYGET, VT_EMPTY, NULL, NULL);
		}
		SAFEARRAY * get_VBProjectData()
		{
			InvokeHelper(0x600200bc, DISPATCH_PROPERTYGET, VT_EMPTY, NULL, NULL);
		}
		long get_SolutionXMLElementCount()
		{
			long result;
			InvokeHelper(0x600200bd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_SolutionXMLElementName(long Index)
		{
			CString result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x600200be, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, Index);
			return result;
		}
		BOOL get_SolutionXMLElementExists(LPCTSTR ElementName)
		{
			BOOL result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x600200bf, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, ElementName);
			return result;
		}
		CString get_SolutionXMLElement(LPCTSTR ElementName)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x600200c0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, ElementName);
			return result;
		}
		void put_SolutionXMLElement(LPCTSTR ElementName, LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x600200c0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, ElementName, newValue);
		}
		void DeleteSolutionXMLElement(LPCTSTR ElementName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x600200c2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ElementName);
		}
		long get_FullBuildNumberCreated()
		{
			long result;
			InvokeHelper(0x600200c3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_FullBuildNumberEdited()
		{
			long result;
			InvokeHelper(0x600200c4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_ID()
		{
			long result;
			InvokeHelper(0x600200c5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_MacrosEnabled()
		{
			BOOL result;
			InvokeHelper(0x600200c6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		long get_ZoomBehavior()
		{
			long result;
			InvokeHelper(0x600200c7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_ZoomBehavior(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x600200c7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL CanCheckIn()
		{
			BOOL result;
			InvokeHelper(0x600200c9, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void CheckIn(BOOL SaveChanges, VARIANT * Comments, BOOL MakePublic)
		{
			static BYTE parms[] = VTS_BOOL VTS_PVARIANT VTS_BOOL ;
			InvokeHelper(0x600200ca, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SaveChanges, Comments, MakePublic);
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x600200cb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Language()
		{
			long result;
			InvokeHelper(0x600200cc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Language(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x600200cc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_RemovePersonalInformation()
		{
			BOOL result;
			InvokeHelper(0x600200ce, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_RemovePersonalInformation(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x600200ce, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void PrintOut(long PrintRange, long FromPage, long ToPage, BOOL ScaleCurrentViewToPaper, LPCTSTR PrinterName, BOOL PrintToFile, LPCTSTR OutputFileName, long Copies, BOOL Collate, BOOL ColorAsBlack)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_BOOL VTS_BSTR VTS_BOOL VTS_BSTR VTS_I4 VTS_BOOL VTS_BOOL ;
			InvokeHelper(0x600200d0, DISPATCH_METHOD, VT_EMPTY, NULL, parms, PrintRange, FromPage, ToPage, ScaleCurrentViewToPaper, PrinterName, PrintToFile, OutputFileName, Copies, Collate, ColorAsBlack);
		}
		long BeginUndoScope(LPCTSTR bstrUndoScopeName)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x600200d1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrUndoScopeName);
			return result;
		}
		void EndUndoScope(long nScopeID, BOOL bCommit)
		{
			static BYTE parms[] = VTS_I4 VTS_BOOL ;
			InvokeHelper(0x600200d2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nScopeID, bCommit);
		}
		void AddUndoUnit(LPUNKNOWN pUndoUnit)
		{
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0x600200d3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pUndoUnit);
		}
		void PurgeUndo()
		{
			InvokeHelper(0x600200d4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		BOOL get_UndoEnabled()
		{
			BOOL result;
			InvokeHelper(0x600200d5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_UndoEnabled(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x600200d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void RenameCurrentScope(LPCTSTR bstrScopeName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x600200d7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrScopeName);
		}
		LPDISPATCH get_SharedWorkspace()
		{
			LPDISPATCH result;
			InvokeHelper(0x600200d8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Sync()
		{
			LPDISPATCH result;
			InvokeHelper(0x600200d9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void RemoveHiddenInformation(long RemoveHiddenInfoItems)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x600200da, DISPATCH_METHOD, VT_EMPTY, NULL, parms, RemoveHiddenInfoItems);
		}
		LPDISPATCH get_DataRecordsets()
		{
			LPDISPATCH result;
			InvokeHelper(0x600200db, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void GetThemeNames(long eType, SAFEARRAY * * NameArray)
		{
			static BYTE parms[] = VTS_I4 VTS_UNKNOWN ;
			InvokeHelper(0x600200dc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, eType, NameArray);
		}
		void GetThemeNamesU(long eType, SAFEARRAY * * NameArray)
		{
			static BYTE parms[] = VTS_I4 VTS_UNKNOWN ;
			InvokeHelper(0x600200dd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, eType, NameArray);
		}
		BOOL CanUndoCheckOut()
		{
			BOOL result;
			InvokeHelper(0x600200de, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void UndoCheckOut()
		{
			InvokeHelper(0x600200df, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		BOOL get_ContainsWorkspaceEx()
		{
			BOOL result;
			InvokeHelper(0x600200e0, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ContainsWorkspaceEx(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x600200e0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void ExportAsFixedFormat(long FixedFormat, LPCTSTR OutputFileName, long Intent, long PrintRange, long FromPage, long ToPage, BOOL ColorAsBlack, BOOL IncludeBackground, BOOL IncludeDocumentProperties, BOOL IncludeStructureTags, BOOL UseISO19005_1, VARIANT& FixedFormatExtClass)
		{
			static BYTE parms[] = VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BOOL VTS_BOOL VTS_BOOL VTS_BOOL VTS_BOOL VTS_VARIANT ;
			InvokeHelper(0x600200e2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FixedFormat, OutputFileName, Intent, PrintRange, FromPage, ToPage, ColorAsBlack, IncludeBackground, IncludeDocumentProperties, IncludeStructureTags, UseISO19005_1, &FixedFormatExtClass);
		}
		CString get_DefaultSavePath()
		{
			CString result;
			InvokeHelper(0x600200e3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_DefaultSavePath(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x600200e3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_CustomUI()
		{
			CString result;
			InvokeHelper(0x600200e5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_CustomUI(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x600200e5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_UserCustomUI()
		{
			CString result;
			InvokeHelper(0x600200e7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_UserCustomUI(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x600200e7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_ServerPublishOptions()
		{
			LPDISPATCH result;
			InvokeHelper(0x600200e9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Validation()
		{
			LPDISPATCH result;
			InvokeHelper(0x600200ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_DiagramServicesEnabled()
		{
			long result;
			InvokeHelper(0x600200eb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_DiagramServicesEnabled(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x600200eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_CompatibilityMode()
		{
			BOOL result;
			InvokeHelper(0x600200ed, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Comments()
		{
			LPDISPATCH result;
			InvokeHelper(0x600200ee, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_EditorCount()
		{
			long result;
			InvokeHelper(0x600200ef, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}

		// IVDocument 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVDocuments 包装类

	class CVDocuments : public COleDispatchDriver
	{
	public:
		CVDocuments(){} // 调用 COleDispatchDriver 默认构造函数
		CVDocuments(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVDocuments(const CVDocuments& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVDocuments 方法
	public:
		LPDISPATCH Add(LPCTSTR FileName)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FileName);
			return result;
		}
		LPDISPATCH Open(LPCTSTR FileName)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FileName);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(VARIANT& NameOrIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &NameOrIndex);
			return result;
		}
		short get_Count()
		{
			short result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH OpenEx(LPCTSTR FileName, short Flags)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_I2 ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FileName, Flags);
			return result;
		}
		LPDISPATCH get_EventList()
		{
			LPDISPATCH result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_PersistsEvents()
		{
			short result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void GetNames(SAFEARRAY * * NameArray)
		{
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, NameArray);
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ItemFromID(long ObjectID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, ObjectID);
			return result;
		}
		BOOL CanCheckOut(LPCTSTR FileName)
		{
			BOOL result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002000c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, FileName);
			return result;
		}
		void CheckOut(LPCTSTR FileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002000d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
		}
		LPDISPATCH AddEx(LPCTSTR FileName, long MeasurementSystem, long Flags, long LangID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_I4 ;
			InvokeHelper(0x6002000e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FileName, MeasurementSystem, Flags, LangID);
			return result;
		}

		// IVDocuments 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVEvent 包装类

	class CVEvent : public COleDispatchDriver
	{
	public:
		CVEvent(){} // 调用 COleDispatchDriver 默认构造函数
		CVEvent(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVEvent(const CVEvent& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVEvent 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_EventList()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Index()
		{
			short result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Event()
		{
			short result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Event(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Action()
		{
			short result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Action(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Target()
		{
			CString result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Target(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_TargetArgs()
		{
			CString result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_TargetArgs(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Trigger(LPCTSTR ContextString)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ContextString);
		}
		void Delete()
		{
			InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		long get_ID()
		{
			long result;
			InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		short get_Enabled()
		{
			short result;
			InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Enabled(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Persistable()
		{
			short result;
			InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Persistent()
		{
			short result;
			InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Persistent(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		SAFEARRAY * GetFilterObjects()
		{
			InvokeHelper(0x60020014, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void SetFilterObjects(SAFEARRAY * * Objects)
		{
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0x60020015, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Objects);
		}
		SAFEARRAY * GetFilterCommands()
		{
			InvokeHelper(0x60020016, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void SetFilterCommands(SAFEARRAY * * Commands)
		{
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0x60020017, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Commands);
		}
		SAFEARRAY * GetFilterSRC()
		{
			InvokeHelper(0x60020018, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void SetFilterSRC(SAFEARRAY * * SRCStream)
		{
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0x60020019, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SRCStream);
		}
		SAFEARRAY * GetFilterActions()
		{
			InvokeHelper(0x6002001a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void SetFilterActions(SAFEARRAY * * filterActionStream)
		{
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0x6002001b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, filterActionStream);
		}

		// IVEvent 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVEventList 包装类

	class CVEventList : public COleDispatchDriver
	{
	public:
		CVEventList(){} // 调用 COleDispatchDriver 默认构造函数
		CVEventList(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVEventList(const CVEventList& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVEventList 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(short Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		short get_Count()
		{
			short result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Add(short EventCode, short Action, LPCTSTR Target, LPCTSTR TargetArgs)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 VTS_I2 VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, EventCode, Action, Target, TargetArgs);
			return result;
		}
		LPDISPATCH AddAdvise(short EventCode, VARIANT& SinkIUnkOrIDisp, LPCTSTR IIDSink, LPCTSTR TargetArgs)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 VTS_VARIANT VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, EventCode, &SinkIUnkOrIDisp, IIDSink, TargetArgs);
			return result;
		}
		LPDISPATCH get_ItemFromID(long ObjectID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, ObjectID);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}

		// IVEventList 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVExtender 包装类

	class CVExtender : public COleDispatchDriver
	{
	public:
		CVExtender(){} // 调用 COleDispatchDriver 默认构造函数
		CVExtender(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVExtender(const CVExtender& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVExtender 方法
	public:
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x80010000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Name(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x80010000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPUNKNOWN get_Object()
		{
			LPUNKNOWN result;
			InvokeHelper(DISPID_Object, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get_Parent()
		{
			LPUNKNOWN result;
			InvokeHelper(0x80010008, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		void Delete()
		{
			InvokeHelper(DISPID_Delete, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Index()
		{
			InvokeHelper(0xfffffcdc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_Shape()
		{
			LPDISPATCH result;
			InvokeHelper(0x80010100, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void VoidGroup()
		{
			InvokeHelper(0x8001012d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void BringForward()
		{
			InvokeHelper(0x8001012e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void BringToFront()
		{
			InvokeHelper(0x8001012f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void ConvertToGroup()
		{
			InvokeHelper(0x80010130, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void SendBackward()
		{
			InvokeHelper(0x80010134, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void SendToBack()
		{
			InvokeHelper(0x80010135, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x8001012c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ShapeParent()
		{
			LPDISPATCH result;
			InvokeHelper(0x80010138, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x80010101, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Master()
		{
			LPDISPATCH result;
			InvokeHelper(0x80010115, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Cells(LPCTSTR localeSpecificCellName)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x8001010d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, localeSpecificCellName);
			return result;
		}
		LPDISPATCH get_CellsSRC(short Section, short Row, short Column)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
			InvokeHelper(0x8001010e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Section, Row, Column);
			return result;
		}
		CString get_Data1()
		{
			CString result;
			InvokeHelper(0x8001010f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Data1(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x8001010f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Data2()
		{
			CString result;
			InvokeHelper(0x80010110, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Data2(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x80010110, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Data3()
		{
			CString result;
			InvokeHelper(0x80010111, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Data3(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x80010111, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Help()
		{
			CString result;
			InvokeHelper(0x80010112, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Help(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x80010112, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_NameID()
		{
			CString result;
			InvokeHelper(0x80010104, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void ShapeCopy()
		{
			InvokeHelper(0x80010109, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void ShapeCut()
		{
			InvokeHelper(0x8001010a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void ShapeDelete()
		{
			InvokeHelper(0x8001010b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void VoidShapeDuplicate()
		{
			InvokeHelper(0x8001010c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		short get_RowCount(short Section)
		{
			short result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x80010118, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, Section);
			return result;
		}
		short AddSection(short Section)
		{
			short result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x80010119, DISPATCH_METHOD, VT_I2, (void*)&result, parms, Section);
			return result;
		}
		void DeleteSection(short Section)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x8001011a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Section);
		}
		short AddRow(short Section, short Row, short RowTag)
		{
			short result;
			static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
			InvokeHelper(0x8001011b, DISPATCH_METHOD, VT_I2, (void*)&result, parms, Section, Row, RowTag);
			return result;
		}
		void DeleteRow(short Section, short Row)
		{
			static BYTE parms[] = VTS_I2 VTS_I2 ;
			InvokeHelper(0x8001011c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Section, Row);
		}
		short get_RowsCellCount(short Section, short Row)
		{
			short result;
			static BYTE parms[] = VTS_I2 VTS_I2 ;
			InvokeHelper(0x8001011d, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, Section, Row);
			return result;
		}
		short get_RowType(short Section, short Row)
		{
			short result;
			static BYTE parms[] = VTS_I2 VTS_I2 ;
			InvokeHelper(0x8001011e, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, Section, Row);
			return result;
		}
		void put_RowType(short Section, short Row, short newValue)
		{
			static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
			InvokeHelper(0x8001011e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, Section, Row, newValue);
		}
		void SetCenter(double xPos, double yPos)
		{
			static BYTE parms[] = VTS_R8 VTS_R8 ;
			InvokeHelper(0x8001011f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, xPos, yPos);
		}
		LPDISPATCH get_Connects()
		{
			LPDISPATCH result;
			InvokeHelper(0x80010122, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ShapeIndex16()
		{
			short result;
			InvokeHelper(0x80010123, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		CString get_Style()
		{
			CString result;
			InvokeHelper(0x80010124, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Style(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x80010124, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_StyleKeepFmt(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x80010128, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_LineStyle()
		{
			CString result;
			InvokeHelper(0x80010125, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_LineStyle(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x80010125, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_LineStyleKeepFmt(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x80010129, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_FillStyle()
		{
			CString result;
			InvokeHelper(0x80010126, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_FillStyle(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x80010126, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_FillStyleKeepFmt(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x8001012a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Export(LPCTSTR FileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x80010139, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
		}
		CString get_UniqueID(short fUniqueID)
		{
			CString result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x8001013d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, fUniqueID);
			return result;
		}
		LPDISPATCH get_ContainingPage()
		{
			LPDISPATCH result;
			InvokeHelper(0x8001013e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ContainingMaster()
		{
			LPDISPATCH result;
			InvokeHelper(0x8001013f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ContainingShape()
		{
			LPDISPATCH result;
			InvokeHelper(0x80010140, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_SectionExists(short Section, short fExistsLocally)
		{
			short result;
			static BYTE parms[] = VTS_I2 VTS_I2 ;
			InvokeHelper(0x80010141, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, Section, fExistsLocally);
			return result;
		}
		short get_RowExists(short Section, short Row, short fExistsLocally)
		{
			short result;
			static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
			InvokeHelper(0x80010142, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, Section, Row, fExistsLocally);
			return result;
		}
		short get_CellExists(LPCTSTR localeSpecificCellName, short fExistsLocally)
		{
			short result;
			static BYTE parms[] = VTS_BSTR VTS_I2 ;
			InvokeHelper(0x80010143, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, localeSpecificCellName, fExistsLocally);
			return result;
		}
		short get_CellsSRCExists(short Section, short Row, short Column, short fExistsLocally)
		{
			short result;
			static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 VTS_I2 ;
			InvokeHelper(0x80010144, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, Section, Row, Column, fExistsLocally);
			return result;
		}
		short get_LayerCount()
		{
			short result;
			InvokeHelper(0x80010145, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Layer(short Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x80010146, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		short AddNamedRow(short Section, LPCTSTR RowName, short RowTag)
		{
			short result;
			static BYTE parms[] = VTS_I2 VTS_BSTR VTS_I2 ;
			InvokeHelper(0x80010147, DISPATCH_METHOD, VT_I2, (void*)&result, parms, Section, RowName, RowTag);
			return result;
		}
		short AddRows(short Section, short Row, short RowTag, short RowCount)
		{
			short result;
			static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 VTS_I2 ;
			InvokeHelper(0x80010148, DISPATCH_METHOD, VT_I2, (void*)&result, parms, Section, Row, RowTag, RowCount);
			return result;
		}
		LPDISPATCH get_EventList()
		{
			LPDISPATCH result;
			InvokeHelper(0x80010149, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_PersistsEvents()
		{
			short result;
			InvokeHelper(0x8001014a, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		CString get_ClassID()
		{
			CString result;
			InvokeHelper(0x80010156, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ShapeObject()
		{
			LPDISPATCH result;
			InvokeHelper(0x80010158, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH OpenSheetWindow()
		{
			LPDISPATCH result;
			InvokeHelper(0x8001015a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ShapeID16()
		{
			short result;
			InvokeHelper(0x8001015b, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void GetFormulas(SAFEARRAY * * SRCStream, SAFEARRAY * * formulaArray)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x8001015d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SRCStream, formulaArray);
		}
		void GetResults(SAFEARRAY * * SRCStream, short Flags, SAFEARRAY * * UnitsNamesOrCodes, SAFEARRAY * * resultArray)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_I2 VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x8001015e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SRCStream, Flags, UnitsNamesOrCodes, resultArray);
		}
		short SetFormulas(SAFEARRAY * * SRCStream, SAFEARRAY * * formulaArray, short Flags)
		{
			short result;
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN VTS_I2 ;
			InvokeHelper(0x8001015f, DISPATCH_METHOD, VT_I2, (void*)&result, parms, SRCStream, formulaArray, Flags);
			return result;
		}
		short SetResults(SAFEARRAY * * SRCStream, SAFEARRAY * * UnitsNamesOrCodes, SAFEARRAY * * resultArray, short Flags)
		{
			short result;
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN VTS_UNKNOWN VTS_I2 ;
			InvokeHelper(0x80010160, DISPATCH_METHOD, VT_I2, (void*)&result, parms, SRCStream, UnitsNamesOrCodes, resultArray, Flags);
			return result;
		}
		LPDISPATCH get_FromConnects()
		{
			LPDISPATCH result;
			InvokeHelper(0x80010161, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void BoundingBox(short Flags, double * lpr8Left, double * lpr8Bottom, double * lpr8Right, double * lpr8Top)
		{
			static BYTE parms[] = VTS_I2 VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 ;
			InvokeHelper(0x80010163, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Flags, lpr8Left, lpr8Bottom, lpr8Right, lpr8Top);
		}
		short HitTest(double xPos, double yPos, double Tolerance)
		{
			short result;
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 ;
			InvokeHelper(0x80010164, DISPATCH_METHOD, VT_I2, (void*)&result, parms, xPos, yPos, Tolerance);
			return result;
		}
		LPDISPATCH get_Hyperlink()
		{
			LPDISPATCH result;
			InvokeHelper(0x80010165, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_ProgID()
		{
			CString result;
			InvokeHelper(0x80010166, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		short get_ObjectIsInherited()
		{
			short result;
			InvokeHelper(0x80010167, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		long get_ShapeID()
		{
			long result;
			InvokeHelper(0x8001016b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_ShapeIndex()
		{
			long result;
			InvokeHelper(0x8001016c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Group()
		{
			LPDISPATCH result;
			InvokeHelper(0x80010182, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH ShapeDuplicate()
		{
			LPDISPATCH result;
			InvokeHelper(0x80010183, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void VisualBoundingBox(short Flags, double * lpr8Left, double * lpr8Bottom, double * lpr8Right, double * lpr8Top)
		{
			static BYTE parms[] = VTS_I2 VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 ;
			InvokeHelper(0x80010184, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Flags, lpr8Left, lpr8Bottom, lpr8Right, lpr8Top);
		}

		// IVExtender 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVFont 包装类

	class CVFont : public COleDispatchDriver
	{
	public:
		CVFont(){} // 调用 COleDispatchDriver 默认构造函数
		CVFont(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVFont(const CVFont& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVFont 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Index()
		{
			short result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		short get_ID16()
		{
			short result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Attributes()
		{
			short result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_CharSet()
		{
			short result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_PitchAndFamily()
		{
			short result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		long get_ID()
		{
			long result;
			InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}

		// IVFont 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVFonts 包装类

	class CVFonts : public COleDispatchDriver
	{
	public:
		CVFonts(){} // 调用 COleDispatchDriver 默认构造函数
		CVFonts(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVFonts(const CVFonts& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVFonts 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Count()
		{
			short result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(VARIANT& NameOrIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &NameOrIndex);
			return result;
		}
		LPDISPATCH get_ItemFromID(long ObjectID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, ObjectID);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}

		// IVFonts 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVGlobal 包装类

	class CVGlobal : public COleDispatchDriver
	{
	public:
		CVGlobal(){} // 调用 COleDispatchDriver 默认构造函数
		CVGlobal(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVGlobal(const CVGlobal& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVGlobal 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ActiveDocument()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ActivePage()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ActiveWindow()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Documents()
		{
			LPDISPATCH result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Windows()
		{
			LPDISPATCH result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Addons()
		{
			LPDISPATCH result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Vbe()
		{
			LPDISPATCH result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}

		// IVGlobal 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVGraphicItem 包装类

	class CVGraphicItem : public COleDispatchDriver
	{
	public:
		CVGraphicItem(){} // 调用 COleDispatchDriver 默认构造函数
		CVGraphicItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVGraphicItem(const CVGraphicItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVGraphicItem 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_ObjectType()
		{
			long result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void Delete()
		{
			InvokeHelper(0x60020003, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		long get_Index()
		{
			long result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Index(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_ID()
		{
			long result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Description()
		{
			CString result;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void GetExpression(long * Field, BSTR * Expression)
		{
			static BYTE parms[] = VTS_PI4 VTS_PBSTR ;
			InvokeHelper(0x60020009, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Field, Expression);
		}
		void SetExpression(long Field, LPCTSTR Expression)
		{
			static BYTE parms[] = VTS_I4 VTS_BSTR ;
			InvokeHelper(0x6002000a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Field, Expression);
		}
		LPDISPATCH get_DataGraphic()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		CString get_Tag()
		{
			CString result;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Tag(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_HorizontalPosition()
		{
			long result;
			InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_HorizontalPosition(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_VerticalPosition()
		{
			long result;
			InvokeHelper(0x60020011, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_VerticalPosition(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_UseDataGraphicPosition()
		{
			BOOL result;
			InvokeHelper(0x60020013, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_UseDataGraphicPosition(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}

		// IVGraphicItem 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVGraphicItems 包装类

	class CVGraphicItems : public COleDispatchDriver
	{
	public:
		CVGraphicItems(){} // 调用 COleDispatchDriver 默认构造函数
		CVGraphicItems(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVGraphicItems(const CVGraphicItems& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVGraphicItems 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_ObjectType()
		{
			long result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_DataGraphic()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH AddCopy(LPDISPATCH GraphicItem)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x60020006, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, GraphicItem);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		LPDISPATCH get_ItemFromID(long ObjectID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, ObjectID);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x60020009, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}

		// IVGraphicItems 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVHyperlink 包装类

	class CVHyperlink : public COleDispatchDriver
	{
	public:
		CVHyperlink(){} // 调用 COleDispatchDriver 默认构造函数
		CVHyperlink(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVHyperlink(const CVHyperlink& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVHyperlink 方法
	public:
		CString get_Description()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Description(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Shape()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		CString get_Address()
		{
			CString result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Address(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_SubAddress()
		{
			CString result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_SubAddress(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_NewWindow()
		{
			short result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_NewWindow(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_ExtraInfo()
		{
			CString result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_ExtraInfo(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Frame()
		{
			CString result;
			InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Frame(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void AddToFavorites(VARIANT& FavoritesTitle)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &FavoritesTitle);
		}
		void Follow()
		{
			InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Delete()
		{
			InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Copy()
		{
			InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		CString CreateURL(short CanonicalForm)
		{
			CString result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0xe, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, CanonicalForm);
			return result;
		}
		short get_Row()
		{
			short result;
			InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_IsDefaultLink()
		{
			short result;
			InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_IsDefaultLink(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Name(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_NameU()
		{
			CString result;
			InvokeHelper(0x6002001a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_NameU(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002001a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}

		// IVHyperlink 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVHyperlinks 包装类

	class CVHyperlinks : public COleDispatchDriver
	{
	public:
		CVHyperlinks(){} // 调用 COleDispatchDriver 默认构造函数
		CVHyperlinks(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVHyperlinks(const CVHyperlinks& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVHyperlinks 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Shape()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(VARIANT& NameOrIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &NameOrIndex);
			return result;
		}
		short get_Count()
		{
			short result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Add()
		{
			LPDISPATCH result;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ItemU(VARIANT& NameOrIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &NameOrIndex);
			return result;
		}

		// IVHyperlinks 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVisEventProc 包装类

	class CVisEventProc : public COleDispatchDriver
	{
	public:
		CVisEventProc(){} // 调用 COleDispatchDriver 默认构造函数
		CVisEventProc(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVisEventProc(const CVisEventProc& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVisEventProc 方法
	public:
		VARIANT VisEventProc(short nEventCode, LPDISPATCH pSourceObj, long nEventID, long nEventSeqNum, LPDISPATCH pSubjectObj, VARIANT& vMoreInfo)
		{
			VARIANT result;
			static BYTE parms[] = VTS_I2 VTS_DISPATCH VTS_I4 VTS_I4 VTS_DISPATCH VTS_VARIANT ;
			InvokeHelper(0x60020000, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, nEventCode, pSourceObj, nEventID, nEventSeqNum, pSubjectObj, &vMoreInfo);
			return result;
		}

		// IVisEventProc 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVLayer 包装类

	class CVLayer : public COleDispatchDriver
	{
	public:
		CVLayer(){} // 调用 COleDispatchDriver 默认构造函数
		CVLayer(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVLayer(const CVLayer& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVLayer 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Page()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Master()
		{
			LPDISPATCH result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Index()
		{
			short result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Row()
		{
			short result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void Add(LPDISPATCH SheetObject, short fPresMems)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_I2 ;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SheetObject, fPresMems);
		}
		void Remove(LPDISPATCH SheetObject, short fPresMems)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_I2 ;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SheetObject, fPresMems);
		}
		void Delete(short fDeleteShapes)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, fDeleteShapes);
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Name(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_CellsC(short Column)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Column);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_EventList()
		{
			LPDISPATCH result;
			InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_PersistsEvents()
		{
			short result;
			InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		CString get_NameU()
		{
			CString result;
			InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_NameU(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}

		// IVLayer 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVLayers 包装类

	class CVLayers : public COleDispatchDriver
	{
	public:
		CVLayers(){} // 调用 COleDispatchDriver 默认构造函数
		CVLayers(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVLayers(const CVLayers& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVLayers 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Page()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Master()
		{
			LPDISPATCH result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Count()
		{
			short result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(VARIANT& NameOrIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &NameOrIndex);
			return result;
		}
		LPDISPATCH Add(LPCTSTR LayerName)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, LayerName);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_EventList()
		{
			LPDISPATCH result;
			InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_PersistsEvents()
		{
			short result;
			InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ItemU(VARIANT& NameOrIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &NameOrIndex);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}

		// IVLayers 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVMaster 包装类

	class CVMaster : public COleDispatchDriver
	{
	public:
		CVMaster(){} // 调用 COleDispatchDriver 默认构造函数
		CVMaster(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVMaster(const CVMaster& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVMaster 方法
	public:
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Prompt()
		{
			CString result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Prompt(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_AlignName()
		{
			short result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_AlignName(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_IconSize()
		{
			short result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_IconSize(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_IconUpdate()
		{
			short result;
			InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_IconUpdate(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Name(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Shapes()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Index()
		{
			short result;
			InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_OneD()
		{
			short result;
			InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void Delete()
		{
			InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		CString get_UniqueID()
		{
			CString result;
			InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Layers()
		{
			LPDISPATCH result;
			InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_PageSheet()
		{
			LPDISPATCH result;
			InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Drop(LPUNKNOWN ObjectToDrop, double xPos, double yPos)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_UNKNOWN VTS_R8 VTS_R8 ;
			InvokeHelper(0x10, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ObjectToDrop, xPos, yPos);
			return result;
		}
		void CenterDrawing()
		{
			InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_EventList()
		{
			LPDISPATCH result;
			InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_PersistsEvents()
		{
			short result;
			InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH DrawLine(double xBegin, double yBegin, double xEnd, double yEnd)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
			InvokeHelper(0x14, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, xBegin, yBegin, xEnd, yEnd);
			return result;
		}
		LPDISPATCH DrawRectangle(double x1, double y1, double x2, double y2)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
			InvokeHelper(0x15, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, x1, y1, x2, y2);
			return result;
		}
		LPDISPATCH DrawOval(double x1, double y1, double x2, double y2)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
			InvokeHelper(0x16, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, x1, y1, x2, y2);
			return result;
		}
		LPDISPATCH DrawSpline(SAFEARRAY * * xyArray, double Tolerance, short Flags)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_UNKNOWN VTS_R8 VTS_I2 ;
			InvokeHelper(0x17, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, xyArray, Tolerance, Flags);
			return result;
		}
		LPDISPATCH DrawBezier(SAFEARRAY * * xyArray, short degree, short Flags)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_UNKNOWN VTS_I2 VTS_I2 ;
			InvokeHelper(0x18, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, xyArray, degree, Flags);
			return result;
		}
		LPDISPATCH DrawPolyline(SAFEARRAY * * xyArray, short Flags)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_UNKNOWN VTS_I2 ;
			InvokeHelper(0x19, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, xyArray, Flags);
			return result;
		}
		LPDISPATCH Import(LPCTSTR FileName)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FileName);
			return result;
		}
		void Export(LPCTSTR FileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
		}
		LPDISPATCH InsertFromFile(LPCTSTR FileName, short Flags)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_I2 ;
			InvokeHelper(0x1c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FileName, Flags);
			return result;
		}
		LPDISPATCH InsertObject(LPCTSTR ClassOrProgID, short Flags)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_I2 ;
			InvokeHelper(0x1d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ClassOrProgID, Flags);
			return result;
		}
		LPDISPATCH OpenDrawWindow()
		{
			LPDISPATCH result;
			InvokeHelper(0x1e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH OpenIconWindow()
		{
			LPDISPATCH result;
			InvokeHelper(0x1f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Open()
		{
			LPDISPATCH result;
			InvokeHelper(0x20, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Close()
		{
			InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		short DropMany(SAFEARRAY * * ObjectsToInstance, SAFEARRAY * * xyArray, SAFEARRAY * * IDArray)
		{
			short result;
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x22, DISPATCH_METHOD, VT_I2, (void*)&result, parms, ObjectsToInstance, xyArray, IDArray);
			return result;
		}
		void GetFormulas(SAFEARRAY * * SID_SRCStream, SAFEARRAY * * formulaArray)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SID_SRCStream, formulaArray);
		}
		void GetResults(SAFEARRAY * * SID_SRCStream, short Flags, SAFEARRAY * * UnitsNamesOrCodes, SAFEARRAY * * resultArray)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_I2 VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x24, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SID_SRCStream, Flags, UnitsNamesOrCodes, resultArray);
		}
		short SetFormulas(SAFEARRAY * * SID_SRCStream, SAFEARRAY * * formulaArray, short Flags)
		{
			short result;
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN VTS_I2 ;
			InvokeHelper(0x25, DISPATCH_METHOD, VT_I2, (void*)&result, parms, SID_SRCStream, formulaArray, Flags);
			return result;
		}
		short SetResults(SAFEARRAY * * SID_SRCStream, SAFEARRAY * * UnitsNamesOrCodes, SAFEARRAY * * resultArray, short Flags)
		{
			short result;
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN VTS_UNKNOWN VTS_I2 ;
			InvokeHelper(0x26, DISPATCH_METHOD, VT_I2, (void*)&result, parms, SID_SRCStream, UnitsNamesOrCodes, resultArray, Flags);
			return result;
		}
		LPDISPATCH get_Connects()
		{
			LPDISPATCH result;
			InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void ImportIcon(LPCTSTR FileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x28, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
		}
		void ExportIconTransparentAsBlack(LPCTSTR FileName, short Flags)
		{
			static BYTE parms[] = VTS_BSTR VTS_I2 ;
			InvokeHelper(0x29, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName, Flags);
		}
		void Layout()
		{
			InvokeHelper(0x2a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void BoundingBox(short Flags, double * lpr8Left, double * lpr8Bottom, double * lpr8Right, double * lpr8Top)
		{
			static BYTE parms[] = VTS_I2 VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 ;
			InvokeHelper(0x2b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Flags, lpr8Left, lpr8Bottom, lpr8Right, lpr8Top);
		}
		short get_ID16()
		{
			short result;
			InvokeHelper(0x2c, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_OLEObjects()
		{
			LPDISPATCH result;
			InvokeHelper(0x2d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_PatternFlags()
		{
			short result;
			InvokeHelper(0x2e, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_PatternFlags(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x2e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_MatchByName()
		{
			short result;
			InvokeHelper(0x2f, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_MatchByName(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x2f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_ID()
		{
			long result;
			InvokeHelper(0x30, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		short get_Hidden()
		{
			short result;
			InvokeHelper(0x31, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Hidden(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x31, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_BaseID()
		{
			CString result;
			InvokeHelper(0x32, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_NewBaseID()
		{
			CString result;
			InvokeHelper(0x33, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_SpatialSearch(double x, double y, short Relation, double Tolerance, short Flags)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_I2 VTS_R8 VTS_I2 ;
			InvokeHelper(0x34, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, x, y, Relation, Tolerance, Flags);
			return result;
		}
		LPDISPATCH CreateShortcut()
		{
			LPDISPATCH result;
			InvokeHelper(0x35, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_NameU()
		{
			CString result;
			InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_NameU(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x36, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short DropManyU(SAFEARRAY * * ObjectsToInstance, SAFEARRAY * * xyArray, SAFEARRAY * * IDArray)
		{
			short result;
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x37, DISPATCH_METHOD, VT_I2, (void*)&result, parms, ObjectsToInstance, xyArray, IDArray);
			return result;
		}
		void GetFormulasU(SAFEARRAY * * SID_SRCStream, SAFEARRAY * * formulaArray)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x38, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SID_SRCStream, formulaArray);
		}
		LPDISPATCH DrawNURBS(short degree, short Flags, SAFEARRAY * * xyArray, SAFEARRAY * * knots, VARIANT& weights)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 VTS_I2 VTS_UNKNOWN VTS_UNKNOWN VTS_VARIANT ;
			InvokeHelper(0x39, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, degree, Flags, xyArray, knots, &weights);
			return result;
		}
		void ExportIcon(LPCTSTR FileName, short Flags, VARIANT& TransparentRGB)
		{
			static BYTE parms[] = VTS_BSTR VTS_I2 VTS_VARIANT ;
			InvokeHelper(0x3a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName, Flags, &TransparentRGB);
		}
		short get_IndexInStencil()
		{
			short result;
			InvokeHelper(0x3b, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Picture()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020045, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Icon()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020046, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void putref_Icon(LPDISPATCH newValue)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x60020046, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_EditCopy()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020048, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Original()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020049, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		BOOL get_IsChanged()
		{
			BOOL result;
			InvokeHelper(0x6002004a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_IndexInStencil(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x3b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void ResizeToFitContents()
		{
			InvokeHelper(0x6002004c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Paste(VARIANT& Flags)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x6002004d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Flags);
		}
		void PasteSpecial(long Format, VARIANT& Link, VARIANT& DisplayAsIcon)
		{
			static BYTE parms[] = VTS_I4 VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x6002004e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Format, &Link, &DisplayAsIcon);
		}
		LPDISPATCH CreateSelection(long SelType, long IterationMode, VARIANT& Data)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_VARIANT ;
			InvokeHelper(0x6002004f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, SelType, IterationMode, &Data);
			return result;
		}
		LPDISPATCH AddGuide(short Type, double xPos, double yPos)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 VTS_R8 VTS_R8 ;
			InvokeHelper(0x60020050, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Type, xPos, yPos);
			return result;
		}
		LPDISPATCH DrawArcByThreePoints(double xBegin, double yBegin, double xEnd, double yEnd, double xControl, double yControl)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
			InvokeHelper(0x60020051, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, xBegin, yBegin, xEnd, yEnd, xControl, yControl);
			return result;
		}
		LPDISPATCH DrawQuarterArc(double xBegin, double yBegin, double xEnd, double yEnd, long SweepFlag)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_I4 ;
			InvokeHelper(0x60020052, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, xBegin, yBegin, xEnd, yEnd, SweepFlag);
			return result;
		}
		LPDISPATCH DrawCircularArc(double xCenter, double yCenter, double Radius, double StartAngle, double EndAngle)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
			InvokeHelper(0x60020053, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, xCenter, yCenter, Radius, StartAngle, EndAngle);
			return result;
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x60020054, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_DataGraphicHidden()
		{
			BOOL result;
			InvokeHelper(0x60020055, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_DataGraphicHidden(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020055, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_DataGraphicHidesText()
		{
			BOOL result;
			InvokeHelper(0x60020057, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_DataGraphicHidesText(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020057, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_DataGraphicShowBorder()
		{
			BOOL result;
			InvokeHelper(0x60020059, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_DataGraphicShowBorder(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020059, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_DataGraphicHorizontalPosition()
		{
			long result;
			InvokeHelper(0x6002005b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_DataGraphicHorizontalPosition(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002005b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_DataGraphicVerticalPosition()
		{
			long result;
			InvokeHelper(0x6002005d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_DataGraphicVerticalPosition(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002005d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_GraphicItems()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002005f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void DataGraphicDelete()
		{
			InvokeHelper(0x60020060, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void PasteToLocation(double xPos, double yPos, long Flags)
		{
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_I4 ;
			InvokeHelper(0x60020061, DISPATCH_METHOD, VT_EMPTY, NULL, parms, xPos, yPos, Flags);
		}
		void VisualBoundingBox(short Flags, double * lpr8Left, double * lpr8Bottom, double * lpr8Right, double * lpr8Top)
		{
			static BYTE parms[] = VTS_I2 VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 ;
			InvokeHelper(0x60020062, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Flags, lpr8Left, lpr8Bottom, lpr8Right, lpr8Top);
		}

		// IVMaster 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVMasters 包装类

	class CVMasters : public COleDispatchDriver
	{
	public:
		CVMasters(){} // 调用 COleDispatchDriver 默认构造函数
		CVMasters(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVMasters(const CVMasters& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVMasters 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(VARIANT& NameUIDOrIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &NameUIDOrIndex);
			return result;
		}
		short get_Count()
		{
			short result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_EventList()
		{
			LPDISPATCH result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_PersistsEvents()
		{
			short result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Add()
		{
			LPDISPATCH result;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void GetNames(SAFEARRAY * * localeSpecificNameArray)
		{
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, localeSpecificNameArray);
		}
		LPDISPATCH Drop(LPUNKNOWN ObjectToDrop, short xPos, short yPos)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_UNKNOWN VTS_I2 VTS_I2 ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ObjectToDrop, xPos, yPos);
			return result;
		}
		LPDISPATCH get_ItemU(VARIANT& NameUIDOrIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &NameUIDOrIndex);
			return result;
		}
		void GetNamesU(SAFEARRAY * * localeIndependentNameArray)
		{
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, localeIndependentNameArray);
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ItemFromID(long nID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002000e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, nID);
			return result;
		}
		void Paste(VARIANT& Flags)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x6002000f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Flags);
		}
		LPDISPATCH AddEx(long Type)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020010, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Type);
			return result;
		}

		// IVMasters 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVMasterShortcut 包装类

	class CVMasterShortcut : public COleDispatchDriver
	{
	public:
		CVMasterShortcut(){} // 调用 COleDispatchDriver 默认构造函数
		CVMasterShortcut(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVMasterShortcut(const CVMasterShortcut& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVMasterShortcut 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Index()
		{
			short result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Name(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Prompt()
		{
			CString result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Prompt(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_AlignName()
		{
			short result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_AlignName(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_IconSize()
		{
			short result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_IconSize(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Delete()
		{
			InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void ImportIcon(LPCTSTR FileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
		}
		void ExportIcon(LPCTSTR FileName, short Flags, VARIANT& TransparentRGB)
		{
			static BYTE parms[] = VTS_BSTR VTS_I2 VTS_VARIANT ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName, Flags, &TransparentRGB);
		}
		long get_ID()
		{
			long result;
			InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH OpenIconWindow()
		{
			LPDISPATCH result;
			InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_TargetDocumentName()
		{
			CString result;
			InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_TargetDocumentName(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_TargetMasterName()
		{
			CString result;
			InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_TargetMasterName(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_TargetBaseID()
		{
			CString result;
			InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_TargetBaseID(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_DropActions()
		{
			CString result;
			InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_DropActions(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_ShapeHelp()
		{
			CString result;
			InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_ShapeHelp(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_NameU()
		{
			CString result;
			InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_NameU(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x13, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_IndexInStencil()
		{
			short result;
			InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Icon()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002001f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void putref_Icon(LPDISPATCH newValue)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x6002001f, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms, newValue);
		}
		void put_IndexInStencil(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x14, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}

		// IVMasterShortcut 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVMasterShortcuts 包装类

	class CVMasterShortcuts : public COleDispatchDriver
	{
	public:
		CVMasterShortcuts(){} // 调用 COleDispatchDriver 默认构造函数
		CVMasterShortcuts(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVMasterShortcuts(const CVMasterShortcuts& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVMasterShortcuts 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(VARIANT& NameOrIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &NameOrIndex);
			return result;
		}
		short get_Count()
		{
			short result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void GetNames(SAFEARRAY * * localeSpecificNameArray)
		{
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, localeSpecificNameArray);
		}
		LPDISPATCH Drop(LPUNKNOWN ObjectToDrop, short xPos, short yPos)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_UNKNOWN VTS_I2 VTS_I2 ;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ObjectToDrop, xPos, yPos);
			return result;
		}
		LPDISPATCH get_ItemU(VARIANT& NameOrIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &NameOrIndex);
			return result;
		}
		void GetNamesU(SAFEARRAY * * localeIndependentNameArray)
		{
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, localeIndependentNameArray);
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ItemFromID(long nID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, nID);
			return result;
		}
		void Paste(VARIANT& Flags)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x6002000c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Flags);
		}

		// IVMasterShortcuts 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVMenu 包装类

	class CVMenu : public COleDispatchDriver
	{
	public:
		CVMenu(){} // 调用 COleDispatchDriver 默认构造函数
		CVMenu(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVMenu(const CVMenu& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVMenu 方法
	public:
		void Delete()
		{
			InvokeHelper(0x60020000, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		CString get_Default()
		{
			CString result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Caption(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Caption()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long get_Index()
		{
			long result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_MDIWindowMenu(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_MDIWindowMenu()
		{
			short result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_MenuItems()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_CmdNum(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020009, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_CmdNum()
		{
			short result;
			InvokeHelper(0x60020009, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_HelpContextID(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x6002000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_HelpContextID()
		{
			short result;
			InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_IsSeparator()
		{
			short result;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_IsHierarchical()
		{
			short result;
			InvokeHelper(0x6002000e, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_CntrlType(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x6002000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_CntrlType()
		{
			short result;
			InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_CntrlID(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_CntrlID()
		{
			short result;
			InvokeHelper(0x60020011, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_TypeSpecific1(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_TypeSpecific1()
		{
			short result;
			InvokeHelper(0x60020013, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Priority(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020015, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Priority()
		{
			short result;
			InvokeHelper(0x60020015, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Spacing(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020017, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Spacing()
		{
			short result;
			InvokeHelper(0x60020017, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_TypeSpecific2(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020019, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_TypeSpecific2()
		{
			short result;
			InvokeHelper(0x60020019, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_ActionText(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002001b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_ActionText()
		{
			CString result;
			InvokeHelper(0x6002001b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_MiniHelp(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002001d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_MiniHelp()
		{
			CString result;
			InvokeHelper(0x6002001d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_AddOnName(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002001f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_AddOnName()
		{
			CString result;
			InvokeHelper(0x6002001f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_AddOnArgs(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020021, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_AddOnArgs()
		{
			CString result;
			InvokeHelper(0x60020021, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_HelpFile(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020023, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_HelpFile()
		{
			CString result;
			InvokeHelper(0x60020023, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void IconFileName(LPCTSTR IconFileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020025, DISPATCH_METHOD, VT_EMPTY, NULL, parms, IconFileName);
		}
		BOOL get_BuiltIn()
		{
			BOOL result;
			InvokeHelper(0x60020026, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Enabled(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020027, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Enabled()
		{
			BOOL result;
			InvokeHelper(0x60020027, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_FaceID(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020029, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_FaceID()
		{
			short result;
			InvokeHelper(0x60020029, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_State(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x6002002b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_State()
		{
			short result;
			InvokeHelper(0x6002002b, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Style(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x6002002d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Style()
		{
			short result;
			InvokeHelper(0x6002002d, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Visible(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002002f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Visible()
		{
			BOOL result;
			InvokeHelper(0x6002002f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Width(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020031, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Width()
		{
			short result;
			InvokeHelper(0x60020031, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_PaletteWidth(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020033, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_PaletteWidth()
		{
			short result;
			InvokeHelper(0x60020033, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}

		// IVMenu 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVMenuItem 包装类

	class CVMenuItem : public COleDispatchDriver
	{
	public:
		CVMenuItem(){} // 调用 COleDispatchDriver 默认构造函数
		CVMenuItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVMenuItem(const CVMenuItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVMenuItem 方法
	public:
		void Delete()
		{
			InvokeHelper(0x60020000, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		CString get_Default()
		{
			CString result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long get_Index()
		{
			long result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_MenuItems()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_CmdNum(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_CmdNum()
		{
			short result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_HelpContextID(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_HelpContextID()
		{
			short result;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_IsSeparator()
		{
			short result;
			InvokeHelper(0x60020009, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_IsHierarchical()
		{
			short result;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Caption(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Caption()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_ActionText(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_ActionText()
		{
			CString result;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_MiniHelp(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_MiniHelp()
		{
			CString result;
			InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_AddOnName(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_AddOnName()
		{
			CString result;
			InvokeHelper(0x60020011, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_AddOnArgs(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_AddOnArgs()
		{
			CString result;
			InvokeHelper(0x60020013, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_HelpFile(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020015, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_HelpFile()
		{
			CString result;
			InvokeHelper(0x60020015, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_CntrlType(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020017, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_CntrlType()
		{
			short result;
			InvokeHelper(0x60020017, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_CntrlID(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020019, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_CntrlID()
		{
			short result;
			InvokeHelper(0x60020019, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_TypeSpecific1(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x6002001b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_TypeSpecific1()
		{
			short result;
			InvokeHelper(0x6002001b, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Priority(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x6002001d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Priority()
		{
			short result;
			InvokeHelper(0x6002001d, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Spacing(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x6002001f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Spacing()
		{
			short result;
			InvokeHelper(0x6002001f, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_TypeSpecific2(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020021, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_TypeSpecific2()
		{
			short result;
			InvokeHelper(0x60020021, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void IconFileName(LPCTSTR IconFileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020023, DISPATCH_METHOD, VT_EMPTY, NULL, parms, IconFileName);
		}
		BOOL get_BuiltIn()
		{
			BOOL result;
			InvokeHelper(0x60020024, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Enabled(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020025, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Enabled()
		{
			BOOL result;
			InvokeHelper(0x60020025, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_FaceID(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020027, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_FaceID()
		{
			short result;
			InvokeHelper(0x60020027, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_State(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020029, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_State()
		{
			short result;
			InvokeHelper(0x60020029, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Style(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x6002002b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Style()
		{
			short result;
			InvokeHelper(0x6002002b, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Visible(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002002d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Visible()
		{
			BOOL result;
			InvokeHelper(0x6002002d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Width(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x6002002f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Width()
		{
			short result;
			InvokeHelper(0x6002002f, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_PaletteWidth(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020031, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_PaletteWidth()
		{
			short result;
			InvokeHelper(0x60020031, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_BeginGroup(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020033, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_BeginGroup()
		{
			BOOL result;
			InvokeHelper(0x60020033, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}

		// IVMenuItem 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVMenuItems 包装类

	class CVMenuItems : public COleDispatchDriver
	{
	public:
		CVMenuItems(){} // 调用 COleDispatchDriver 默认构造函数
		CVMenuItems(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVMenuItems(const CVMenuItems& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVMenuItems 方法
	public:
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long lIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, lIndex);
			return result;
		}
		LPDISPATCH Add()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020002, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH AddAt(long lIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020003, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, lIndex);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ParentItem()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}

		// IVMenuItems 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVMenus 包装类

	class CVMenus : public COleDispatchDriver
	{
	public:
		CVMenus(){} // 调用 COleDispatchDriver 默认构造函数
		CVMenus(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVMenus(const CVMenus& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVMenus 方法
	public:
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long lIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, lIndex);
			return result;
		}
		LPDISPATCH Add()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020002, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH AddAt(long lIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020003, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, lIndex);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}

		// IVMenus 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVMenuSet 包装类

	class CVMenuSet : public COleDispatchDriver
	{
	public:
		CVMenuSet(){} // 调用 COleDispatchDriver 默认构造函数
		CVMenuSet(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVMenuSet(const CVMenuSet& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVMenuSet 方法
	public:
		void Delete()
		{
			InvokeHelper(0x60020000, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		CString get_Default()
		{
			CString result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Caption(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Caption()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long get_SetID()
		{
			long result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Menus()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		BOOL get_BuiltIn()
		{
			BOOL result;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Enabled(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Enabled()
		{
			BOOL result;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Height(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Height()
		{
			short result;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Left(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Left()
		{
			short result;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Position(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x6002000e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Position()
		{
			short result;
			InvokeHelper(0x6002000e, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Protection(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020010, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Protection()
		{
			short result;
			InvokeHelper(0x60020010, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_RowIndex(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020012, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_RowIndex()
		{
			short result;
			InvokeHelper(0x60020012, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Top(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020014, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Top()
		{
			short result;
			InvokeHelper(0x60020014, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Visible(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020016, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Visible()
		{
			BOOL result;
			InvokeHelper(0x60020016, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Width(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020018, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Width()
		{
			short result;
			InvokeHelper(0x60020018, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}

		// IVMenuSet 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVMenuSets 包装类

	class CVMenuSets : public COleDispatchDriver
	{
	public:
		CVMenuSets(){} // 调用 COleDispatchDriver 默认构造函数
		CVMenuSets(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVMenuSets(const CVMenuSets& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVMenuSets 方法
	public:
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long lIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, lIndex);
			return result;
		}
		LPDISPATCH get_ItemAtID(long lID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, lID);
			return result;
		}
		LPDISPATCH Add()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020003, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH AddAtID(long lID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020004, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, lID);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}

		// IVMenuSets 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVMovedSelectionEvent 包装类

	class CVMovedSelectionEvent : public COleDispatchDriver
	{
	public:
		CVMovedSelectionEvent(){} // 调用 COleDispatchDriver 默认构造函数
		CVMovedSelectionEvent(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVMovedSelectionEvent(const CVMovedSelectionEvent& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVMovedSelectionEvent 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ReplacementShape()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_SelectionSource()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_SelectionTarget()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}

		// IVMovedSelectionEvent 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVMSGWrap 包装类

	class CVMSGWrap : public COleDispatchDriver
	{
	public:
		CVMSGWrap(){} // 调用 COleDispatchDriver 默认构造函数
		CVMSGWrap(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVMSGWrap(const CVMSGWrap& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVMSGWrap 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		long get_hwnd()
		{
			long result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_hwnd(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_message()
		{
			long result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_message(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_wParam()
		{
			long result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_wParam(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_lParam()
		{
			long result;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_lParam(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_posttime()
		{
			long result;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_posttime(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_ptx()
		{
			long result;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_ptx(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_pty()
		{
			long result;
			InvokeHelper(0x6002000e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_pty(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002000e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}

		// IVMSGWrap 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVOLEObject 包装类

	class CVOLEObject : public COleDispatchDriver
	{
	public:
		CVOLEObject(){} // 调用 COleDispatchDriver 默认构造函数
		CVOLEObject(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVOLEObject(const CVOLEObject& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVOLEObject 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Shape()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		CString get_ClassID()
		{
			CString result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_ProgID()
		{
			CString result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		short get_ForeignType()
		{
			short result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Object()
		{
			LPDISPATCH result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}

		// IVOLEObject 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVOLEObjects 包装类

	class CVOLEObjects : public COleDispatchDriver
	{
	public:
		CVOLEObjects(){} // 调用 COleDispatchDriver 默认构造函数
		CVOLEObjects(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVOLEObjects(const CVOLEObjects& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVOLEObjects 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(VARIANT& NameOrIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &NameOrIndex);
			return result;
		}
		short get_Count16()
		{
			short result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}

		// IVOLEObjects 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVPage 包装类

	class CVPage : public COleDispatchDriver
	{
	public:
		CVPage(){} // 调用 COleDispatchDriver 默认构造函数
		CVPage(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVPage(const CVPage& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVPage 方法
	public:
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Background()
		{
			short result;
			InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Background(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void old_Paste()
		{
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void old_PasteSpecial(short Format)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Format);
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH DrawLine(double xBegin, double yBegin, double xEnd, double yEnd)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, xBegin, yBegin, xEnd, yEnd);
			return result;
		}
		LPDISPATCH DrawRectangle(double x1, double y1, double x2, double y2)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, x1, y1, x2, y2);
			return result;
		}
		LPDISPATCH DrawOval(double x1, double y1, double x2, double y2)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, x1, y1, x2, y2);
			return result;
		}
		short get_Index()
		{
			short result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Name(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Shapes()
		{
			LPDISPATCH result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Drop(LPUNKNOWN ObjectToDrop, double xPos, double yPos)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_UNKNOWN VTS_R8 VTS_R8 ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ObjectToDrop, xPos, yPos);
			return result;
		}
		LPDISPATCH AddGuide(short Type, double xPos, double yPos)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 VTS_R8 VTS_R8 ;
			InvokeHelper(0xc, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Type, xPos, yPos);
			return result;
		}
		LPDISPATCH get_BackPageAsObj()
		{
			LPDISPATCH result;
			InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_BackPageFromName(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x5db, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Print()
		{
			InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH Import(LPCTSTR FileName)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x11, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FileName);
			return result;
		}
		void Export(LPCTSTR FileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
		}
		LPDISPATCH get_Layers()
		{
			LPDISPATCH result;
			InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_PageSheet()
		{
			LPDISPATCH result;
			InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Delete(short fRenumberPages)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, parms, fRenumberPages);
		}
		void CenterDrawing()
		{
			InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_EventList()
		{
			LPDISPATCH result;
			InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_PersistsEvents()
		{
			short result;
			InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH DrawSpline(SAFEARRAY * * xyArray, double Tolerance, short Flags)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_UNKNOWN VTS_R8 VTS_I2 ;
			InvokeHelper(0x19, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, xyArray, Tolerance, Flags);
			return result;
		}
		LPDISPATCH DrawBezier(SAFEARRAY * * xyArray, short degree, short Flags)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_UNKNOWN VTS_I2 VTS_I2 ;
			InvokeHelper(0x1a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, xyArray, degree, Flags);
			return result;
		}
		LPDISPATCH DrawPolyline(SAFEARRAY * * xyArray, short Flags)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_UNKNOWN VTS_I2 ;
			InvokeHelper(0x1b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, xyArray, Flags);
			return result;
		}
		LPDISPATCH InsertFromFile(LPCTSTR FileName, short Flags)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_I2 ;
			InvokeHelper(0x1c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FileName, Flags);
			return result;
		}
		LPDISPATCH InsertObject(LPCTSTR ClassOrProgID, short Flags)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_I2 ;
			InvokeHelper(0x1d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ClassOrProgID, Flags);
			return result;
		}
		LPDISPATCH OpenDrawWindow()
		{
			LPDISPATCH result;
			InvokeHelper(0x1e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short DropMany(SAFEARRAY * * ObjectsToInstance, SAFEARRAY * * xyArray, SAFEARRAY * * IDArray)
		{
			short result;
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x1f, DISPATCH_METHOD, VT_I2, (void*)&result, parms, ObjectsToInstance, xyArray, IDArray);
			return result;
		}
		void GetFormulas(SAFEARRAY * * SID_SRCStream, SAFEARRAY * * formulaArray)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x20, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SID_SRCStream, formulaArray);
		}
		void GetResults(SAFEARRAY * * SID_SRCStream, short Flags, SAFEARRAY * * UnitsNamesOrCodes, SAFEARRAY * * resultArray)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_I2 VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SID_SRCStream, Flags, UnitsNamesOrCodes, resultArray);
		}
		short SetFormulas(SAFEARRAY * * SID_SRCStream, SAFEARRAY * * formulaArray, short Flags)
		{
			short result;
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN VTS_I2 ;
			InvokeHelper(0x22, DISPATCH_METHOD, VT_I2, (void*)&result, parms, SID_SRCStream, formulaArray, Flags);
			return result;
		}
		short SetResults(SAFEARRAY * * SID_SRCStream, SAFEARRAY * * UnitsNamesOrCodes, SAFEARRAY * * resultArray, short Flags)
		{
			short result;
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN VTS_UNKNOWN VTS_I2 ;
			InvokeHelper(0x23, DISPATCH_METHOD, VT_I2, (void*)&result, parms, SID_SRCStream, UnitsNamesOrCodes, resultArray, Flags);
			return result;
		}
		LPDISPATCH get_Connects()
		{
			LPDISPATCH result;
			InvokeHelper(0x24, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		VARIANT get_BackPage()
		{
			VARIANT result;
			InvokeHelper(0x25, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_BackPage(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x25, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		void Layout()
		{
			InvokeHelper(0x26, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void BoundingBox(short Flags, double * lpr8Left, double * lpr8Bottom, double * lpr8Right, double * lpr8Top)
		{
			static BYTE parms[] = VTS_I2 VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 ;
			InvokeHelper(0x27, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Flags, lpr8Left, lpr8Bottom, lpr8Right, lpr8Top);
		}
		short get_ID16()
		{
			short result;
			InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_OLEObjects()
		{
			LPDISPATCH result;
			InvokeHelper(0x29, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_ID()
		{
			long result;
			InvokeHelper(0x2a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_SpatialSearch(double x, double y, short Relation, double Tolerance, short Flags)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_I2 VTS_R8 VTS_I2 ;
			InvokeHelper(0x2b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, x, y, Relation, Tolerance, Flags);
			return result;
		}
		CString get_NameU()
		{
			CString result;
			InvokeHelper(0x2c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_NameU(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x2c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short DropManyU(SAFEARRAY * * ObjectsToInstance, SAFEARRAY * * xyArray, SAFEARRAY * * IDArray)
		{
			short result;
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x2d, DISPATCH_METHOD, VT_I2, (void*)&result, parms, ObjectsToInstance, xyArray, IDArray);
			return result;
		}
		void GetFormulasU(SAFEARRAY * * SID_SRCStream, SAFEARRAY * * formulaArray)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x2e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SID_SRCStream, formulaArray);
		}
		LPDISPATCH DrawNURBS(short degree, short Flags, SAFEARRAY * * xyArray, SAFEARRAY * * knots, VARIANT& weights)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 VTS_I2 VTS_UNKNOWN VTS_UNKNOWN VTS_VARIANT ;
			InvokeHelper(0x2f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, degree, Flags, xyArray, knots, &weights);
			return result;
		}
		LPDISPATCH get_Picture()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020035, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_Index(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_PrintTileCount()
		{
			long result;
			InvokeHelper(0x60020037, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void PrintTile(long nTile)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020038, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nTile);
		}
		void ResizeToFitContents()
		{
			InvokeHelper(0x60020039, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Paste(VARIANT& Flags)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x6002003a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Flags);
		}
		void PasteSpecial(long Format, VARIANT& Link, VARIANT& DisplayAsIcon)
		{
			static BYTE parms[] = VTS_I4 VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x6002003b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Format, &Link, &DisplayAsIcon);
		}
		LPDISPATCH CreateSelection(long SelType, long IterationMode, VARIANT& Data)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_VARIANT ;
			InvokeHelper(0x6002003c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, SelType, IterationMode, &Data);
			return result;
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x6002003d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH DrawArcByThreePoints(double xBegin, double yBegin, double xEnd, double yEnd, double xControl, double yControl)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
			InvokeHelper(0x6002003e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, xBegin, yBegin, xEnd, yEnd, xControl, yControl);
			return result;
		}
		LPDISPATCH DrawQuarterArc(double xBegin, double yBegin, double xEnd, double yEnd, long SweepFlag)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_I4 ;
			InvokeHelper(0x6002003f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, xBegin, yBegin, xEnd, yEnd, SweepFlag);
			return result;
		}
		LPDISPATCH DrawCircularArc(double xCenter, double yCenter, double Radius, double StartAngle, double EndAngle)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
			InvokeHelper(0x60020040, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, xCenter, yCenter, Radius, StartAngle, EndAngle);
			return result;
		}
		long get_ReviewerID()
		{
			long result;
			InvokeHelper(0x60020041, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_OriginalPage()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020042, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void GetShapesLinkedToData(long DataRecordsetID, SAFEARRAY * * ShapeIDs)
		{
			static BYTE parms[] = VTS_I4 VTS_UNKNOWN ;
			InvokeHelper(0x60020043, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DataRecordsetID, ShapeIDs);
		}
		void GetShapesLinkedToDataRow(long DataRecordsetID, long DataRowID, SAFEARRAY * * ShapeIDs)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_UNKNOWN ;
			InvokeHelper(0x60020044, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DataRecordsetID, DataRowID, ShapeIDs);
		}
		void LinkShapesToDataRows(long DataRecordsetID, SAFEARRAY * * DataRowIDs, SAFEARRAY * * ShapeIDs, BOOL ApplyDataGraphicAfterLink)
		{
			static BYTE parms[] = VTS_I4 VTS_UNKNOWN VTS_UNKNOWN VTS_BOOL ;
			InvokeHelper(0x60020045, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DataRecordsetID, DataRowIDs, ShapeIDs, ApplyDataGraphicAfterLink);
		}
		void ShapeIDsToUniqueIDs(SAFEARRAY * * ShapeIDs, long UniqueIDArgs, SAFEARRAY * * GUIDs)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_I4 VTS_UNKNOWN ;
			InvokeHelper(0x60020046, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ShapeIDs, UniqueIDArgs, GUIDs);
		}
		void UniqueIDsToShapeIDs(SAFEARRAY * * GUIDs, SAFEARRAY * * ShapeIDs)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x60020047, DISPATCH_METHOD, VT_EMPTY, NULL, parms, GUIDs, ShapeIDs);
		}
		LPDISPATCH DropLinked(LPUNKNOWN ObjectToDrop, double x, double y, long DataRecordsetID, long DataRowID, BOOL ApplyDataGraphicAfterLink)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_UNKNOWN VTS_R8 VTS_R8 VTS_I4 VTS_I4 VTS_BOOL ;
			InvokeHelper(0x60020048, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ObjectToDrop, x, y, DataRecordsetID, DataRowID, ApplyDataGraphicAfterLink);
			return result;
		}
		long DropManyLinkedU(SAFEARRAY * * ObjectsToInstance, SAFEARRAY * * XYs, long DataRecordsetID, SAFEARRAY * * DataRowIDs, BOOL ApplyDataGraphicAfterLink, SAFEARRAY * * ShapeIDs)
		{
			long result;
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN VTS_I4 VTS_UNKNOWN VTS_BOOL VTS_UNKNOWN ;
			InvokeHelper(0x60020049, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ObjectsToInstance, XYs, DataRecordsetID, DataRowIDs, ApplyDataGraphicAfterLink, ShapeIDs);
			return result;
		}
		VARIANT get_ThemeColors()
		{
			VARIANT result;
			InvokeHelper(0x6002004a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_ThemeColors(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x6002004a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_ThemeEffects()
		{
			VARIANT result;
			InvokeHelper(0x6002004c, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_ThemeEffects(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x6002004c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		LPDISPATCH DropConnected(LPUNKNOWN ObjectToDrop, LPDISPATCH TargetShape, long PlacementDir, LPUNKNOWN Connector)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_UNKNOWN VTS_DISPATCH VTS_I4 VTS_UNKNOWN ;
			InvokeHelper(0x6002004e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ObjectToDrop, TargetShape, PlacementDir, Connector);
			return result;
		}
		long AutoConnectMany(SAFEARRAY * * FromShapeIDs, SAFEARRAY * * ToShapeIDs, SAFEARRAY * * PlacementDirs, LPUNKNOWN Connector)
		{
			long result;
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x6002004f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, FromShapeIDs, ToShapeIDs, PlacementDirs, Connector);
			return result;
		}
		LPDISPATCH DropContainer(LPUNKNOWN ObjectToDrop, LPUNKNOWN TargetShapes)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x60020050, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ObjectToDrop, TargetShapes);
			return result;
		}
		void LayoutIncremental(long AlignOrSpace, long AlignHorizontal, long AlignVertical, double SpaceHorizontal, double SpaceVertical, long UnitsNameOrCode)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_I4 ;
			InvokeHelper(0x60020051, DISPATCH_METHOD, VT_EMPTY, NULL, parms, AlignOrSpace, AlignHorizontal, AlignVertical, SpaceHorizontal, SpaceVertical, UnitsNameOrCode);
		}
		void LayoutChangeDirection(long Direction)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020052, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Direction);
		}
		void AvoidPageBreaks()
		{
			InvokeHelper(0x60020053, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH SplitConnector(LPDISPATCH ConnectorToSplit, LPDISPATCH Shape)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH ;
			InvokeHelper(0x60020054, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ConnectorToSplit, Shape);
			return result;
		}
		LPDISPATCH DropCallout(LPUNKNOWN ObjectToDrop, LPDISPATCH TargetShape)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_UNKNOWN VTS_DISPATCH ;
			InvokeHelper(0x60020055, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ObjectToDrop, TargetShape);
			return result;
		}
		void PasteToLocation(double xPos, double yPos, long Flags)
		{
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_I4 ;
			InvokeHelper(0x60020056, DISPATCH_METHOD, VT_EMPTY, NULL, parms, xPos, yPos, Flags);
		}
		SAFEARRAY * GetContainers(long NestedOptions)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020057, DISPATCH_METHOD, VT_EMPTY, NULL, parms, NestedOptions);
		}
		SAFEARRAY * GetCallouts(long NestedOptions)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020058, DISPATCH_METHOD, VT_EMPTY, NULL, parms, NestedOptions);
		}
		BOOL get_LayoutRoutePassive()
		{
			BOOL result;
			InvokeHelper(0x60020059, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_LayoutRoutePassive(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020059, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH DropLegend(LPUNKNOWN OuterList, LPUNKNOWN InnerContainer, long populateFlags)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN VTS_I4 ;
			InvokeHelper(0x6002005b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, OuterList, InnerContainer, populateFlags);
			return result;
		}
		LPDISPATCH DropIntoList(LPUNKNOWN ObjectToDrop, LPDISPATCH TargetList, long lPosition)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_UNKNOWN VTS_DISPATCH VTS_I4 ;
			InvokeHelper(0x6002005c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ObjectToDrop, TargetList, lPosition);
			return result;
		}
		BOOL get_AutoSize()
		{
			BOOL result;
			InvokeHelper(0x6002005d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_AutoSize(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002005d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void AutoSizeDrawing()
		{
			InvokeHelper(0x6002005f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH Duplicate()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020060, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		VARIANT GetTheme(long eThemeType)
		{
			VARIANT result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020061, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, eThemeType);
			return result;
		}
		void SetTheme(VARIANT& varThemeIndex, VARIANT& varColorScheme, VARIANT& varEffectScheme, VARIANT& varConnectorScheme, VARIANT& varFontScheme)
		{
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x60020062, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &varThemeIndex, &varColorScheme, &varEffectScheme, &varConnectorScheme, &varFontScheme);
		}
		LPDISPATCH get_Comments()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020063, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ShapeComments()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020064, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void GetThemeVariant(short * pVariantColor, short * pVariantStyle, short * pEmbellishment)
		{
			static BYTE parms[] = VTS_PI2 VTS_PI2 VTS_PI2 ;
			InvokeHelper(0x60020065, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pVariantColor, pVariantStyle, pEmbellishment);
		}
		void SetThemeVariant(short variantColor, short variantStyle, short embellishment)
		{
			static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
			InvokeHelper(0x60020066, DISPATCH_METHOD, VT_EMPTY, NULL, parms, variantColor, variantStyle, embellishment);
		}
		void VisualBoundingBox(short Flags, double * lpr8Left, double * lpr8Bottom, double * lpr8Right, double * lpr8Top)
		{
			static BYTE parms[] = VTS_I2 VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 ;
			InvokeHelper(0x60020067, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Flags, lpr8Left, lpr8Bottom, lpr8Right, lpr8Top);
		}

		// IVPage 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVPages 包装类

	class CVPages : public COleDispatchDriver
	{
	public:
		CVPages(){} // 调用 COleDispatchDriver 默认构造函数
		CVPages(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVPages(const CVPages& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVPages 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(VARIANT& NameOrIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &NameOrIndex);
			return result;
		}
		short get_Count()
		{
			short result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Add()
		{
			LPDISPATCH result;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_EventList()
		{
			LPDISPATCH result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_PersistsEvents()
		{
			short result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void GetNames(SAFEARRAY * * localeSpecificNameArray)
		{
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, localeSpecificNameArray);
		}
		LPDISPATCH get_ItemU(VARIANT& NameOrIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &NameOrIndex);
			return result;
		}
		void GetNamesU(SAFEARRAY * * localeIndependentNameArray)
		{
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, localeIndependentNameArray);
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ItemFromID(long nID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, nID);
			return result;
		}

		// IVPages 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVPath 包装类

	class CVPath : public COleDispatchDriver
	{
	public:
		CVPath(){} // 调用 COleDispatchDriver 默认构造函数
		CVPath(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVPath(const CVPath& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVPath 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item16(short Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x3e7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		short get_Count16()
		{
			short result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Closed()
		{
			short result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void Points(double Tolerance, SAFEARRAY * * xyArray)
		{
			static BYTE parms[] = VTS_R8 VTS_UNKNOWN ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Tolerance, xyArray);
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}

		// IVPath 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVPaths 包装类

	class CVPaths : public COleDispatchDriver
	{
	public:
		CVPaths(){} // 调用 COleDispatchDriver 默认构造函数
		CVPaths(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVPaths(const CVPaths& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVPaths 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item16(short Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x3e7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		short get_Count16()
		{
			short result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}

		// IVPaths 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVRelatedShapePairEvent 包装类

	class CVRelatedShapePairEvent : public COleDispatchDriver
	{
	public:
		CVRelatedShapePairEvent(){} // 调用 COleDispatchDriver 默认构造函数
		CVRelatedShapePairEvent(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVRelatedShapePairEvent(const CVRelatedShapePairEvent& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVRelatedShapePairEvent 方法
	public:
		short get_Stat()
		{
			short result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ContainingPage()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_ContainingPageID()
		{
			long result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_FromShapeID()
		{
			long result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_ToShapeID()
		{
			long result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}

		// IVRelatedShapePairEvent 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVReplaceShapesEvent 包装类

	class CVReplaceShapesEvent : public COleDispatchDriver
	{
	public:
		CVReplaceShapesEvent(){} // 调用 COleDispatchDriver 默认构造函数
		CVReplaceShapesEvent(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVReplaceShapesEvent(const CVReplaceShapesEvent& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVReplaceShapesEvent 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get_ReplacementMaster()
		{
			LPUNKNOWN result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_SelectionSource()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_ReplaceFlags()
		{
			long result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}

		// IVReplaceShapesEvent 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVRow 包装类

	class CVRow : public COleDispatchDriver
	{
	public:
		CVRow(){} // 调用 COleDispatchDriver 默认构造函数
		CVRow(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVRow(const CVRow& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVRow 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Shape()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Style()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ContainingSection()
		{
			LPDISPATCH result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Index()
		{
			short result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_EventList()
		{
			LPDISPATCH result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_PersistsEvents()
		{
			short result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Name(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Count()
		{
			short result;
			InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Cell(VARIANT& NameOrIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &NameOrIndex);
			return result;
		}
		CString get_NameU()
		{
			CString result;
			InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_NameU(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_CellU(VARIANT& NameOrIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &NameOrIndex);
			return result;
		}
		void GetPolylineData(short Flags, SAFEARRAY * * xyArray)
		{
			static BYTE parms[] = VTS_I2 VTS_UNKNOWN ;
			InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Flags, xyArray);
		}
		long get_ContainingPageID()
		{
			long result;
			InvokeHelper(0x60020011, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_ContainingMasterID()
		{
			long result;
			InvokeHelper(0x60020012, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}

		// IVRow 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVSection 包装类

	class CVSection : public COleDispatchDriver
	{
	public:
		CVSection(){} // 调用 COleDispatchDriver 默认构造函数
		CVSection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVSection(const CVSection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVSection 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Shape()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Style()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Index()
		{
			short result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_EventList()
		{
			LPDISPATCH result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_PersistsEvents()
		{
			short result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_Count()
		{
			short result;
			InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Row(short Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		long get_ContainingPageID()
		{
			long result;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_ContainingMasterID()
		{
			long result;
			InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}

		// IVSection 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVSelection 包装类

	class CVSelection : public COleDispatchDriver
	{
	public:
		CVSelection(){} // 调用 COleDispatchDriver 默认构造函数
		CVSelection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVSelection(const CVSelection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVSelection 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item16(short Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x3e7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		short get_Count16()
		{
			short result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void Export(LPCTSTR FileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ContainingPage()
		{
			LPDISPATCH result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ContainingMaster()
		{
			LPDISPATCH result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ContainingShape()
		{
			LPDISPATCH result;
			InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void BringForward()
		{
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void BringToFront()
		{
			InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void SendBackward()
		{
			InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void SendToBack()
		{
			InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		CString get_Style()
		{
			CString result;
			InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Style(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_StyleKeepFmt(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_LineStyle()
		{
			CString result;
			InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_LineStyle(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_LineStyleKeepFmt(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_FillStyle()
		{
			CString result;
			InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_FillStyle(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_FillStyleKeepFmt(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x13, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_TextStyle()
		{
			CString result;
			InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_TextStyle(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x14, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_TextStyleKeepFmt(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x15, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Combine()
		{
			InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Fragment()
		{
			InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Intersect()
		{
			InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Subtract()
		{
			InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Union()
		{
			InvokeHelper(0x1a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void FlipHorizontal()
		{
			InvokeHelper(0x1b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void FlipVertical()
		{
			InvokeHelper(0x1c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void ReverseEnds()
		{
			InvokeHelper(0x1d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Rotate90()
		{
			InvokeHelper(0x1e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void old_Copy()
		{
			InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void old_Cut()
		{
			InvokeHelper(0x20, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Delete()
		{
			InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void VoidDuplicate()
		{
			InvokeHelper(0x22, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void VoidGroup()
		{
			InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void ConvertToGroup()
		{
			InvokeHelper(0x24, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Ungroup()
		{
			InvokeHelper(0x25, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void SelectAll()
		{
			InvokeHelper(0x26, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void DeselectAll()
		{
			InvokeHelper(0x27, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Select(LPDISPATCH SheetObject, short SelectAction)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_I2 ;
			InvokeHelper(0x28, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SheetObject, SelectAction);
		}
		LPDISPATCH get_EventList()
		{
			LPDISPATCH result;
			InvokeHelper(0x29, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_PersistsEvents()
		{
			short result;
			InvokeHelper(0x2a, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void Trim()
		{
			InvokeHelper(0x2b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Join()
		{
			InvokeHelper(0x2c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void FitCurve(double Tolerance, short Flags)
		{
			static BYTE parms[] = VTS_R8 VTS_I2 ;
			InvokeHelper(0x2d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Tolerance, Flags);
		}
		void Layout()
		{
			InvokeHelper(0x2e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void BoundingBox(short Flags, double * lpr8Left, double * lpr8Bottom, double * lpr8Right, double * lpr8Top)
		{
			static BYTE parms[] = VTS_I2 VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 ;
			InvokeHelper(0x2f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Flags, lpr8Left, lpr8Bottom, lpr8Right, lpr8Top);
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x30, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH DrawRegion(double Tolerance, short Flags, VARIANT& x, VARIANT& y, VARIANT& ResultsMaster)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_R8 VTS_I2 VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x31, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Tolerance, Flags, &x, &y, &ResultsMaster);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		long get_IterationMode()
		{
			long result;
			InvokeHelper(0x32, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_IterationMode(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x32, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_ItemStatus(long Index)
		{
			short result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x33, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, Index);
			return result;
		}
		LPDISPATCH get_PrimaryItem()
		{
			LPDISPATCH result;
			InvokeHelper(0x34, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Picture()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002003c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Group()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002003d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void SwapEnds()
		{
			InvokeHelper(0x6002003e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void AddToGroup()
		{
			InvokeHelper(0x6002003f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void RemoveFromGroup()
		{
			InvokeHelper(0x60020040, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH Duplicate()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020041, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Copy(VARIANT& Flags)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020042, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Flags);
		}
		void Cut(VARIANT& Flags)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020043, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Flags);
		}
		void Move(double dx, double dy, VARIANT& UnitsNameOrCode)
		{
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_VARIANT ;
			InvokeHelper(0x60020044, DISPATCH_METHOD, VT_EMPTY, NULL, parms, dx, dy, &UnitsNameOrCode);
		}
		void Rotate(double Angle, VARIANT& AngleUnitsNameOrCode, BOOL BlastGuards, long RotationType, double PinX, double PinY, VARIANT& PinUnitsNameOrCode)
		{
			static BYTE parms[] = VTS_R8 VTS_VARIANT VTS_BOOL VTS_I4 VTS_R8 VTS_R8 VTS_VARIANT ;
			InvokeHelper(0x60020045, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Angle, &AngleUnitsNameOrCode, BlastGuards, RotationType, PinX, PinY, &PinUnitsNameOrCode);
		}
		void Align(long AlignHorizontal, long AlignVertical, BOOL GlueToGuide)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL ;
			InvokeHelper(0x60020046, DISPATCH_METHOD, VT_EMPTY, NULL, parms, AlignHorizontal, AlignVertical, GlueToGuide);
		}
		void Distribute(long Distribute, BOOL GlueToGuide)
		{
			static BYTE parms[] = VTS_I4 VTS_BOOL ;
			InvokeHelper(0x60020047, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Distribute, GlueToGuide);
		}
		void UpdateAlignmentBox()
		{
			InvokeHelper(0x60020048, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Offset(double Distance)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x60020049, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Distance);
		}
		void ConnectShapes()
		{
			InvokeHelper(0x6002004a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Flip(long FlipDirection, long FlipType, BOOL BlastGuards, double PinX, double PinY, VARIANT& PinUnitsNameOrCode)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL VTS_R8 VTS_R8 VTS_VARIANT ;
			InvokeHelper(0x6002004b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FlipDirection, FlipType, BlastGuards, PinX, PinY, &PinUnitsNameOrCode);
		}
		long get_ContainingPageID()
		{
			long result;
			InvokeHelper(0x6002004c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_ContainingMasterID()
		{
			long result;
			InvokeHelper(0x6002004d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void LinkToData(long DataRecordsetID, long DataRowID, BOOL ApplyDataGraphicAfterLink)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL ;
			InvokeHelper(0x6002004e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DataRecordsetID, DataRowID, ApplyDataGraphicAfterLink);
		}
		void BreakLinkToData(long DataRecordsetID)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002004f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DataRecordsetID);
		}
		void GetIDs(SAFEARRAY * * ShapeIDs)
		{
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0x60020050, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ShapeIDs);
		}
		long AutomaticLink(long DataRecordsetID, SAFEARRAY * * ColumnNames, SAFEARRAY * * AutoLinkFieldTypes, SAFEARRAY * * FieldNames, long AutoLinkBehavior, SAFEARRAY * * ShapeIDs)
		{
			long result;
			static BYTE parms[] = VTS_I4 VTS_UNKNOWN VTS_UNKNOWN VTS_UNKNOWN VTS_I4 VTS_UNKNOWN ;
			InvokeHelper(0x60020051, DISPATCH_METHOD, VT_I4, (void*)&result, parms, DataRecordsetID, ColumnNames, AutoLinkFieldTypes, FieldNames, AutoLinkBehavior, ShapeIDs);
			return result;
		}
		LPDISPATCH get_DataGraphic()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020052, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_DataGraphic(LPDISPATCH newValue)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x60020052, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void LayoutIncremental(long AlignOrSpace, long AlignHorizontal, long AlignVertical, double SpaceHorizontal, double SpaceVertical, long UnitCode)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_I4 ;
			InvokeHelper(0x60020054, DISPATCH_METHOD, VT_EMPTY, NULL, parms, AlignOrSpace, AlignHorizontal, AlignVertical, SpaceHorizontal, SpaceVertical, UnitCode);
		}
		void LayoutChangeDirection(long Direction)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020055, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Direction);
		}
		void AvoidPageBreaks()
		{
			InvokeHelper(0x60020056, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Resize(long Direction, double Distance, long UnitCode)
		{
			static BYTE parms[] = VTS_I4 VTS_R8 VTS_I4 ;
			InvokeHelper(0x60020057, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Direction, Distance, UnitCode);
		}
		void AddToContainers()
		{
			InvokeHelper(0x60020058, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void RemoveFromContainers()
		{
			InvokeHelper(0x60020059, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH MoveToSubprocess(LPDISPATCH Page, LPUNKNOWN ObjectToDrop, LPDISPATCH * NewShape)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_DISPATCH VTS_UNKNOWN VTS_PDISPATCH ;
			InvokeHelper(0x6002005a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Page, ObjectToDrop, NewShape);
			return result;
		}
		LPDISPATCH get_SelectionForDragCopy()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002005b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void DeleteEx(long DelFlags)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002005c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DelFlags);
		}
		SAFEARRAY * GetContainers(long NestedOptions)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002005d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, NestedOptions);
		}
		SAFEARRAY * GetCallouts(long NestedOptions)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002005e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, NestedOptions);
		}
		SAFEARRAY * MemberOfContainersUnion()
		{
			InvokeHelper(0x6002005f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		SAFEARRAY * MemberOfContainersIntersection()
		{
			InvokeHelper(0x60020060, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		SAFEARRAY * SetContainerFormat(long FormatType, VARIANT& FormatValue)
		{
			static BYTE parms[] = VTS_I4 VTS_VARIANT ;
			InvokeHelper(0x60020061, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FormatType, &FormatValue);
		}
		SAFEARRAY * ReplaceShape(LPUNKNOWN MasterOrMasterShortcutToDrop, long ReplaceFlags)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_I4 ;
			InvokeHelper(0x60020062, DISPATCH_METHOD, VT_EMPTY, NULL, parms, MasterOrMasterShortcutToDrop, ReplaceFlags);
		}
		void SetQuickStyle(long lineMatrix, long fillMatrix, long effectsMatrix, long fontMatrix, long lineColor, long fillColor, long shadowColor, long fontColor)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
			InvokeHelper(0x60020063, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lineMatrix, fillMatrix, effectsMatrix, fontMatrix, lineColor, fillColor, shadowColor, fontColor);
		}
		void VisualBoundingBox(short Flags, double * lpr8Left, double * lpr8Bottom, double * lpr8Right, double * lpr8Top)
		{
			static BYTE parms[] = VTS_I2 VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 ;
			InvokeHelper(0x60020064, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Flags, lpr8Left, lpr8Bottom, lpr8Right, lpr8Top);
		}

		// IVSelection 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVServerPublishOptions 包装类

	class CVServerPublishOptions : public COleDispatchDriver
	{
	public:
		CVServerPublishOptions(){} // 调用 COleDispatchDriver 默认构造函数
		CVServerPublishOptions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVServerPublishOptions(const CVServerPublishOptions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVServerPublishOptions 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		BOOL get_IsPublishedPage(LPCTSTR PageName, long Flags)
		{
			BOOL result;
			static BYTE parms[] = VTS_BSTR VTS_I4 ;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, PageName, Flags);
			return result;
		}
		void IncludePage(LPCTSTR PageName, long Flags)
		{
			static BYTE parms[] = VTS_BSTR VTS_I4 ;
			InvokeHelper(0x60020005, DISPATCH_METHOD, VT_EMPTY, NULL, parms, PageName, Flags);
		}
		void ExcludePage(LPCTSTR PageName, long Flags)
		{
			static BYTE parms[] = VTS_BSTR VTS_I4 ;
			InvokeHelper(0x60020006, DISPATCH_METHOD, VT_EMPTY, NULL, parms, PageName, Flags);
		}
		void SetPagesToPublish(long PublishPages, SAFEARRAY * * NamesArray, long Flags)
		{
			static BYTE parms[] = VTS_I4 VTS_UNKNOWN VTS_I4 ;
			InvokeHelper(0x60020007, DISPATCH_METHOD, VT_EMPTY, NULL, parms, PublishPages, NamesArray, Flags);
		}
		void GetPagesToPublish(long Flags, long * PublishPages, SAFEARRAY * * NamesArray)
		{
			static BYTE parms[] = VTS_I4 VTS_PI4 VTS_UNKNOWN ;
			InvokeHelper(0x60020008, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Flags, PublishPages, NamesArray);
		}
		void SetRecordsetsToPublish(long PublishDataRecordsets, SAFEARRAY * * DataRecordsetIDs)
		{
			static BYTE parms[] = VTS_I4 VTS_UNKNOWN ;
			InvokeHelper(0x60020009, DISPATCH_METHOD, VT_EMPTY, NULL, parms, PublishDataRecordsets, DataRecordsetIDs);
		}
		void GetRecordsetsToPublish(long * PublishDataRecordsets, SAFEARRAY * * DataRecordsetIDs)
		{
			static BYTE parms[] = VTS_PI4 VTS_UNKNOWN ;
			InvokeHelper(0x6002000a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, PublishDataRecordsets, DataRecordsetIDs);
		}

		// IVServerPublishOptions 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVShape 包装类

	class CVShape : public COleDispatchDriver
	{
	public:
		CVShape(){} // 调用 COleDispatchDriver 默认构造函数
		CVShape(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVShape(const CVShape& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVShape 方法
	public:
		void VoidGroup()
		{
			InvokeHelper(0x2d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void BringForward()
		{
			InvokeHelper(0x2e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void BringToFront()
		{
			InvokeHelper(0x2f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void ConvertToGroup()
		{
			InvokeHelper(0x30, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void FlipHorizontal()
		{
			InvokeHelper(0x31, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void FlipVertical()
		{
			InvokeHelper(0x32, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void ReverseEnds()
		{
			InvokeHelper(0x33, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void SendBackward()
		{
			InvokeHelper(0x34, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void SendToBack()
		{
			InvokeHelper(0x35, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Rotate90()
		{
			InvokeHelper(0x36, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Ungroup()
		{
			InvokeHelper(0x37, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x2c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x38, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Master()
		{
			LPDISPATCH result;
			InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Type()
		{
			short result;
			InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Cells(LPCTSTR localeSpecificCellName)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, localeSpecificCellName);
			return result;
		}
		LPDISPATCH get_CellsSRC(short Section, short Row, short Column)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
			InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Section, Row, Column);
			return result;
		}
		LPDISPATCH get_Shapes()
		{
			LPDISPATCH result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Data1()
		{
			CString result;
			InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Data1(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Data2()
		{
			CString result;
			InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Data2(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Data3()
		{
			CString result;
			InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Data3(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Help()
		{
			CString result;
			InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Help(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_NameID()
		{
			CString result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Name(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Text()
		{
			CString result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Text(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_CharCount()
		{
			long result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Characters()
		{
			LPDISPATCH result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void old_Copy()
		{
			InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void old_Cut()
		{
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Delete()
		{
			InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void VoidDuplicate()
		{
			InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH Drop(LPUNKNOWN ObjectToDrop, double xPos, double yPos)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_UNKNOWN VTS_R8 VTS_R8 ;
			InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ObjectToDrop, xPos, yPos);
			return result;
		}
		short get_OneD()
		{
			short result;
			InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_OneD(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x16, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_GeometryCount()
		{
			short result;
			InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_RowCount(short Section)
		{
			short result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, Section);
			return result;
		}
		short AddSection(short Section)
		{
			short result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x19, DISPATCH_METHOD, VT_I2, (void*)&result, parms, Section);
			return result;
		}
		void DeleteSection(short Section)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x1a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Section);
		}
		short AddRow(short Section, short Row, short RowTag)
		{
			short result;
			static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
			InvokeHelper(0x1b, DISPATCH_METHOD, VT_I2, (void*)&result, parms, Section, Row, RowTag);
			return result;
		}
		void DeleteRow(short Section, short Row)
		{
			static BYTE parms[] = VTS_I2 VTS_I2 ;
			InvokeHelper(0x1c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Section, Row);
		}
		short get_RowsCellCount(short Section, short Row)
		{
			short result;
			static BYTE parms[] = VTS_I2 VTS_I2 ;
			InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, Section, Row);
			return result;
		}
		short get_RowType(short Section, short Row)
		{
			short result;
			static BYTE parms[] = VTS_I2 VTS_I2 ;
			InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, Section, Row);
			return result;
		}
		void put_RowType(short Section, short Row, short newValue)
		{
			static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
			InvokeHelper(0x1e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, Section, Row, newValue);
		}
		void SetCenter(double xPos, double yPos)
		{
			static BYTE parms[] = VTS_R8 VTS_R8 ;
			InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, xPos, yPos);
		}
		void SetBegin(double xPos, double yPos)
		{
			static BYTE parms[] = VTS_R8 VTS_R8 ;
			InvokeHelper(0x20, DISPATCH_METHOD, VT_EMPTY, NULL, parms, xPos, yPos);
		}
		void SetEnd(double xPos, double yPos)
		{
			static BYTE parms[] = VTS_R8 VTS_R8 ;
			InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, parms, xPos, yPos);
		}
		LPDISPATCH get_Connects()
		{
			LPDISPATCH result;
			InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Index16()
		{
			short result;
			InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		CString get_Style()
		{
			CString result;
			InvokeHelper(0x24, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Style(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x24, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_StyleKeepFmt(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x28, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_LineStyle()
		{
			CString result;
			InvokeHelper(0x25, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_LineStyle(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x25, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_LineStyleKeepFmt(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x29, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_FillStyle()
		{
			CString result;
			InvokeHelper(0x26, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_FillStyle(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x26, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_FillStyleKeepFmt(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x2a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_TextStyle()
		{
			CString result;
			InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_TextStyle(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x27, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_TextStyleKeepFmt(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x2b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Export(LPCTSTR FileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x39, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
		}
		double get_old_AreaIU()
		{
			double result;
			InvokeHelper(0x3a, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		double get_old_LengthIU()
		{
			double result;
			InvokeHelper(0x3b, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get_GeomExIf(short fFill, double LineRes)
		{
			LPUNKNOWN result;
			static BYTE parms[] = VTS_I2 VTS_R8 ;
			InvokeHelper(0x3c, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, parms, fFill, LineRes);
			return result;
		}
		CString get_UniqueID(short fUniqueID)
		{
			CString result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, fUniqueID);
			return result;
		}
		LPDISPATCH get_ContainingPage()
		{
			LPDISPATCH result;
			InvokeHelper(0x3e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ContainingMaster()
		{
			LPDISPATCH result;
			InvokeHelper(0x3f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ContainingShape()
		{
			LPDISPATCH result;
			InvokeHelper(0x40, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_SectionExists(short Section, short fExistsLocally)
		{
			short result;
			static BYTE parms[] = VTS_I2 VTS_I2 ;
			InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, Section, fExistsLocally);
			return result;
		}
		short get_RowExists(short Section, short Row, short fExistsLocally)
		{
			short result;
			static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
			InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, Section, Row, fExistsLocally);
			return result;
		}
		short get_CellExists(LPCTSTR localeSpecificCellName, short fExistsLocally)
		{
			short result;
			static BYTE parms[] = VTS_BSTR VTS_I2 ;
			InvokeHelper(0x43, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, localeSpecificCellName, fExistsLocally);
			return result;
		}
		short get_CellsSRCExists(short Section, short Row, short Column, short fExistsLocally)
		{
			short result;
			static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 VTS_I2 ;
			InvokeHelper(0x44, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, Section, Row, Column, fExistsLocally);
			return result;
		}
		short get_LayerCount()
		{
			short result;
			InvokeHelper(0x45, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Layer(short Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x46, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		short AddNamedRow(short Section, LPCTSTR RowName, short RowTag)
		{
			short result;
			static BYTE parms[] = VTS_I2 VTS_BSTR VTS_I2 ;
			InvokeHelper(0x47, DISPATCH_METHOD, VT_I2, (void*)&result, parms, Section, RowName, RowTag);
			return result;
		}
		short AddRows(short Section, short Row, short RowTag, short RowCount)
		{
			short result;
			static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 VTS_I2 ;
			InvokeHelper(0x48, DISPATCH_METHOD, VT_I2, (void*)&result, parms, Section, Row, RowTag, RowCount);
			return result;
		}
		LPDISPATCH get_EventList()
		{
			LPDISPATCH result;
			InvokeHelper(0x49, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_PersistsEvents()
		{
			short result;
			InvokeHelper(0x4a, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH DrawLine(double xBegin, double yBegin, double xEnd, double yEnd)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
			InvokeHelper(0x4b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, xBegin, yBegin, xEnd, yEnd);
			return result;
		}
		LPDISPATCH DrawRectangle(double x1, double y1, double x2, double y2)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
			InvokeHelper(0x4c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, x1, y1, x2, y2);
			return result;
		}
		LPDISPATCH DrawOval(double x1, double y1, double x2, double y2)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
			InvokeHelper(0x4d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, x1, y1, x2, y2);
			return result;
		}
		LPDISPATCH DrawSpline(SAFEARRAY * * xyArray, double Tolerance, short Flags)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_UNKNOWN VTS_R8 VTS_I2 ;
			InvokeHelper(0x4e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, xyArray, Tolerance, Flags);
			return result;
		}
		LPDISPATCH DrawBezier(SAFEARRAY * * xyArray, short degree, short Flags)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_UNKNOWN VTS_I2 VTS_I2 ;
			InvokeHelper(0x4f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, xyArray, degree, Flags);
			return result;
		}
		LPDISPATCH DrawPolyline(SAFEARRAY * * xyArray, short Flags)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_UNKNOWN VTS_I2 ;
			InvokeHelper(0x50, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, xyArray, Flags);
			return result;
		}
		void FitCurve(double Tolerance, short Flags)
		{
			static BYTE parms[] = VTS_R8 VTS_I2 ;
			InvokeHelper(0x51, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Tolerance, Flags);
		}
		LPDISPATCH Import(LPCTSTR FileName)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x52, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FileName);
			return result;
		}
		void CenterDrawing()
		{
			InvokeHelper(0x53, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH InsertFromFile(LPCTSTR FileName, short Flags)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_I2 ;
			InvokeHelper(0x54, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FileName, Flags);
			return result;
		}
		LPDISPATCH InsertObject(LPCTSTR ClassOrProgID, short Flags)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_I2 ;
			InvokeHelper(0x55, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ClassOrProgID, Flags);
			return result;
		}
		CString get_ClassID()
		{
			CString result;
			InvokeHelper(0x56, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		short get_ForeignType()
		{
			short result;
			InvokeHelper(0x57, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Object()
		{
			LPDISPATCH result;
			InvokeHelper(0x58, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH OpenDrawWindow()
		{
			LPDISPATCH result;
			InvokeHelper(0x59, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH OpenSheetWindow()
		{
			LPDISPATCH result;
			InvokeHelper(0x5a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ID16()
		{
			short result;
			InvokeHelper(0x5b, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short DropMany(SAFEARRAY * * ObjectsToInstance, SAFEARRAY * * xyArray, SAFEARRAY * * IDArray)
		{
			short result;
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x5c, DISPATCH_METHOD, VT_I2, (void*)&result, parms, ObjectsToInstance, xyArray, IDArray);
			return result;
		}
		void GetFormulas(SAFEARRAY * * SRCStream, SAFEARRAY * * formulaArray)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x5d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SRCStream, formulaArray);
		}
		void GetResults(SAFEARRAY * * SRCStream, short Flags, SAFEARRAY * * UnitsNamesOrCodes, SAFEARRAY * * resultArray)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_I2 VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x5e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SRCStream, Flags, UnitsNamesOrCodes, resultArray);
		}
		short SetFormulas(SAFEARRAY * * SRCStream, SAFEARRAY * * formulaArray, short Flags)
		{
			short result;
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN VTS_I2 ;
			InvokeHelper(0x5f, DISPATCH_METHOD, VT_I2, (void*)&result, parms, SRCStream, formulaArray, Flags);
			return result;
		}
		short SetResults(SAFEARRAY * * SRCStream, SAFEARRAY * * UnitsNamesOrCodes, SAFEARRAY * * resultArray, short Flags)
		{
			short result;
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN VTS_UNKNOWN VTS_I2 ;
			InvokeHelper(0x60, DISPATCH_METHOD, VT_I2, (void*)&result, parms, SRCStream, UnitsNamesOrCodes, resultArray, Flags);
			return result;
		}
		LPDISPATCH get_FromConnects()
		{
			LPDISPATCH result;
			InvokeHelper(0x61, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Layout()
		{
			InvokeHelper(0x62, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void BoundingBox(short Flags, double * lpr8Left, double * lpr8Bottom, double * lpr8Right, double * lpr8Top)
		{
			static BYTE parms[] = VTS_I2 VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 ;
			InvokeHelper(0x63, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Flags, lpr8Left, lpr8Bottom, lpr8Right, lpr8Top);
		}
		short HitTest(double xPos, double yPos, double Tolerance)
		{
			short result;
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 ;
			InvokeHelper(0x64, DISPATCH_METHOD, VT_I2, (void*)&result, parms, xPos, yPos, Tolerance);
			return result;
		}
		LPDISPATCH get_Hyperlink()
		{
			LPDISPATCH result;
			InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_ProgID()
		{
			CString result;
			InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		short get_ObjectIsInherited()
		{
			short result;
			InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Paths()
		{
			LPDISPATCH result;
			InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_PathsLocal()
		{
			LPDISPATCH result;
			InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH AddHyperlink()
		{
			LPDISPATCH result;
			InvokeHelper(0x6a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_ID()
		{
			long result;
			InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Index()
		{
			long result;
			InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Section(short Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		LPDISPATCH get_Hyperlinks()
		{
			LPDISPATCH result;
			InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_SpatialRelation(LPDISPATCH OtherShape, double Tolerance, short Flags)
		{
			short result;
			static BYTE parms[] = VTS_DISPATCH VTS_R8 VTS_I2 ;
			InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, OtherShape, Tolerance, Flags);
			return result;
		}
		double get_DistanceFrom(LPDISPATCH OtherShape, short Flags)
		{
			double result;
			static BYTE parms[] = VTS_DISPATCH VTS_I2 ;
			InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, parms, OtherShape, Flags);
			return result;
		}
		double get_DistanceFromPoint(double x, double y, short Flags, VARIANT * pvPathIndex, VARIANT * pvCurveIndex, VARIANT * pvt)
		{
			double result;
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_I2 VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
			InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, parms, x, y, Flags, pvPathIndex, pvCurveIndex, pvt);
			return result;
		}
		LPDISPATCH get_SpatialNeighbors(short Relation, double Tolerance, short Flags, VARIANT& ResultRoot)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 VTS_R8 VTS_I2 VTS_VARIANT ;
			InvokeHelper(0x72, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Relation, Tolerance, Flags, &ResultRoot);
			return result;
		}
		LPDISPATCH get_SpatialSearch(double x, double y, short Relation, double Tolerance, short Flags)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_I2 VTS_R8 VTS_I2 ;
			InvokeHelper(0x73, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, x, y, Relation, Tolerance, Flags);
			return result;
		}
		void TransformXYTo(LPDISPATCH OtherShape, double x, double y, double * xprime, double * yprime)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_R8 VTS_R8 VTS_PR8 VTS_PR8 ;
			InvokeHelper(0x74, DISPATCH_METHOD, VT_EMPTY, NULL, parms, OtherShape, x, y, xprime, yprime);
		}
		void TransformXYFrom(LPDISPATCH OtherShape, double x, double y, double * xprime, double * yprime)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_R8 VTS_R8 VTS_PR8 VTS_PR8 ;
			InvokeHelper(0x75, DISPATCH_METHOD, VT_EMPTY, NULL, parms, OtherShape, x, y, xprime, yprime);
		}
		void XYToPage(double x, double y, double * xprime, double * yprime)
		{
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_PR8 VTS_PR8 ;
			InvokeHelper(0x76, DISPATCH_METHOD, VT_EMPTY, NULL, parms, x, y, xprime, yprime);
		}
		void XYFromPage(double x, double y, double * xprime, double * yprime)
		{
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_PR8 VTS_PR8 ;
			InvokeHelper(0x77, DISPATCH_METHOD, VT_EMPTY, NULL, parms, x, y, xprime, yprime);
		}
		void UpdateAlignmentBox()
		{
			InvokeHelper(0x78, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_CellsU(LPCTSTR localeIndependentCellName)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x79, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, localeIndependentCellName);
			return result;
		}
		CString get_NameU()
		{
			CString result;
			InvokeHelper(0x7a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_NameU(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x7a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_CellExistsU(LPCTSTR localeIndependentCellName, short fExistsLocally)
		{
			short result;
			static BYTE parms[] = VTS_BSTR VTS_I2 ;
			InvokeHelper(0x7b, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, localeIndependentCellName, fExistsLocally);
			return result;
		}
		short DropManyU(SAFEARRAY * * ObjectsToInstance, SAFEARRAY * * xyArray, SAFEARRAY * * IDArray)
		{
			short result;
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x7c, DISPATCH_METHOD, VT_I2, (void*)&result, parms, ObjectsToInstance, xyArray, IDArray);
			return result;
		}
		void GetFormulasU(SAFEARRAY * * SRCStream, SAFEARRAY * * formulaArray)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x7d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SRCStream, formulaArray);
		}
		LPDISPATCH DrawNURBS(short degree, short Flags, SAFEARRAY * * xyArray, SAFEARRAY * * knots, VARIANT& weights)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 VTS_I2 VTS_UNKNOWN VTS_UNKNOWN VTS_VARIANT ;
			InvokeHelper(0x7e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, degree, Flags, xyArray, knots, &weights);
			return result;
		}
		short get_CellsRowIndex(LPCTSTR localeSpecificCellName)
		{
			short result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x7f, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, localeSpecificCellName);
			return result;
		}
		short get_CellsRowIndexU(LPCTSTR localeIndependentCellName)
		{
			short result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, localeIndependentCellName);
			return result;
		}
		BOOL get_IsOpenForTextEdit()
		{
			BOOL result;
			InvokeHelper(0x81, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_RootShape()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002008f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_MasterShape()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020090, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Picture()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020091, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Group()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020092, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Duplicate()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020093, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void SwapEnds()
		{
			InvokeHelper(0x60020094, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void put_Parent(LPDISPATCH newValue)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x38, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		SAFEARRAY * get_ForeignData()
		{
			InvokeHelper(0x60020096, DISPATCH_PROPERTYGET, VT_EMPTY, NULL, NULL);
		}
		void Copy(VARIANT& Flags)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020097, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Flags);
		}
		void Cut(VARIANT& Flags)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020098, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Flags);
		}
		void Paste(VARIANT& Flags)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020099, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Flags);
		}
		void PasteSpecial(long Format, VARIANT& Link, VARIANT& DisplayAsIcon)
		{
			static BYTE parms[] = VTS_I4 VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x6002009a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Format, &Link, &DisplayAsIcon);
		}
		LPDISPATCH CreateSelection(long SelType, long IterationMode, VARIANT& Data)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_VARIANT ;
			InvokeHelper(0x6002009b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, SelType, IterationMode, &Data);
			return result;
		}
		long get_Language()
		{
			long result;
			InvokeHelper(0x6002009c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Language(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002009c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Offset(double Distance)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x6002009e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Distance);
		}
		LPDISPATCH AddGuide(short Type, double xPos, double yPos)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 VTS_R8 VTS_R8 ;
			InvokeHelper(0x6002009f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Type, xPos, yPos);
			return result;
		}
		double get_AreaIU(BOOL fIncludeSubShapes)
		{
			double result;
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x600200a0, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, parms, fIncludeSubShapes);
			return result;
		}
		double get_LengthIU(BOOL fIncludeSubShapes)
		{
			double result;
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x600200a1, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, parms, fIncludeSubShapes);
			return result;
		}
		LPDISPATCH DrawArcByThreePoints(double xBegin, double yBegin, double xEnd, double yEnd, double xControl, double yControl)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
			InvokeHelper(0x600200a2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, xBegin, yBegin, xEnd, yEnd, xControl, yControl);
			return result;
		}
		LPDISPATCH DrawQuarterArc(double xBegin, double yBegin, double xEnd, double yEnd, long SweepFlag)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_I4 ;
			InvokeHelper(0x600200a3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, xBegin, yBegin, xEnd, yEnd, SweepFlag);
			return result;
		}
		LPDISPATCH DrawCircularArc(double xCenter, double yCenter, double Radius, double StartAngle, double EndAngle)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
			InvokeHelper(0x600200a4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, xCenter, yCenter, Radius, StartAngle, EndAngle);
			return result;
		}
		long get_ContainingPageID()
		{
			long result;
			InvokeHelper(0x600200a5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_ContainingMasterID()
		{
			long result;
			InvokeHelper(0x600200a6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void LinkToData(long DataRecordsetID, long RowID, BOOL ApplyDataGraphicAfterLink)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL ;
			InvokeHelper(0x600200a7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DataRecordsetID, RowID, ApplyDataGraphicAfterLink);
		}
		void BreakLinkToData(long DataRecordsetID)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x600200a8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DataRecordsetID);
		}
		long GetLinkedDataRow(long DataRecordsetID)
		{
			long result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x600200a9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, DataRecordsetID);
			return result;
		}
		void GetLinkedDataRecordsetIDs(SAFEARRAY * * DataRecordsetIDs)
		{
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0x600200aa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DataRecordsetIDs);
		}
		void GetCustomPropertiesLinkedToData(long DataRecordsetID, SAFEARRAY * * CustomPropertyIndices)
		{
			static BYTE parms[] = VTS_I4 VTS_UNKNOWN ;
			InvokeHelper(0x600200ab, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DataRecordsetID, CustomPropertyIndices);
		}
		BOOL IsCustomPropertyLinked(long DataRecordsetID, long CustomPropertyIndex)
		{
			BOOL result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0x600200ac, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, DataRecordsetID, CustomPropertyIndex);
			return result;
		}
		CString GetCustomPropertyLinkedColumn(long DataRecordsetID, long CustomPropertyIndex)
		{
			CString result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0x600200ad, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, DataRecordsetID, CustomPropertyIndex);
			return result;
		}
		void AutoConnect(LPDISPATCH ToShape, long PlacementDir, LPUNKNOWN Connector)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_UNKNOWN ;
			InvokeHelper(0x600200ae, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ToShape, PlacementDir, Connector);
		}
		LPDISPATCH get_DataGraphic()
		{
			LPDISPATCH result;
			InvokeHelper(0x600200af, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_DataGraphic(LPDISPATCH newValue)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x600200af, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_IsDataGraphicCallout()
		{
			BOOL result;
			InvokeHelper(0x600200b1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ContainerProperties()
		{
			LPDISPATCH result;
			InvokeHelper(0x600200b2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		BOOL HasCategory(LPCTSTR Category)
		{
			BOOL result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x600200b3, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Category);
			return result;
		}
		SAFEARRAY * get_MemberOfContainers()
		{
			InvokeHelper(0x600200b4, DISPATCH_PROPERTYGET, VT_EMPTY, NULL, NULL);
		}
		VARIANT ConnectedShapes(long Flags, LPCTSTR CategoryFilter)
		{
			static BYTE parms[] = VTS_I4 VTS_BSTR ;
			VARIANT result;
			InvokeHelper(0x600200b5, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, Flags, CategoryFilter);
			return result;
		}
		VARIANT GluedShapes(long Flags, LPCTSTR CategoryFilter, LPDISPATCH pOtherConnectedShape)
		{
			static BYTE parms[] = VTS_I4 VTS_BSTR VTS_DISPATCH ;
			VARIANT result;
			InvokeHelper(0x600200b6, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, Flags, CategoryFilter, pOtherConnectedShape);
			return result;
		}
		VARIANT GluedShapes(long Flags, LPCTSTR CategoryFilter)
		{
			static BYTE parms[] = VTS_I4 VTS_BSTR VTS_DISPATCH ;
			VARIANT result;
			InvokeHelper(0x600200b6, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, Flags, CategoryFilter ,*this);
			return result;
		}
		void Disconnect(long ConnectorEnd, double OffsetX, double OffsetY, long Units)
		{
			static BYTE parms[] = VTS_I4 VTS_R8 VTS_R8 VTS_I4 ;
			InvokeHelper(0x600200b7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ConnectorEnd, OffsetX, OffsetY, Units);
		}
		BOOL get_IsCallout()
		{
			BOOL result;
			InvokeHelper(0x600200b8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_CalloutTarget()
		{
			LPDISPATCH result;
			InvokeHelper(0x600200b9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_CalloutTarget(LPDISPATCH newValue)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x600200b9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		SAFEARRAY * get_CalloutsAssociated()
		{
			InvokeHelper(0x600200bb, DISPATCH_PROPERTYGET, VT_EMPTY, NULL, NULL);
		}
		void Resize(long Direction, double Distance, long UnitCode)
		{
			static BYTE parms[] = VTS_I4 VTS_R8 VTS_I4 ;
			InvokeHelper(0x600200bc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Direction, Distance, UnitCode);
		}
		void AddToContainers()
		{
			InvokeHelper(0x600200bd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void RemoveFromContainers()
		{
			InvokeHelper(0x600200be, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH CreateSubProcess()
		{
			LPDISPATCH result;
			InvokeHelper(0x600200bf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH MoveToSubprocess(LPDISPATCH Page, LPUNKNOWN ObjectToDrop, LPDISPATCH * NewShape)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_DISPATCH VTS_UNKNOWN VTS_PDISPATCH ;
			InvokeHelper(0x600200c0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Page, ObjectToDrop, NewShape);
			return result;
		}
		void DeleteEx(long DelFlags)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x600200c1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DelFlags);
		}
		LPDISPATCH ReplaceShape(LPUNKNOWN MasterOrMasterShortcutToDrop, long ReplaceFlags)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_UNKNOWN VTS_I4 ;
			InvokeHelper(0x600200c2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, MasterOrMasterShortcutToDrop, ReplaceFlags);
			return result;
		}
		void SetQuickStyle(long lineMatrix, long fillMatrix, long effectsMatrix, long fontMatrix, long lineColor, long fillColor, long shadowColor, long fontColor)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
			InvokeHelper(0x600200c3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lineMatrix, fillMatrix, effectsMatrix, fontMatrix, lineColor, fillColor, shadowColor, fontColor);
		}
		double ChangePicture(LPCTSTR FileName, long ChangePictureFlags)
		{
			double result;
			static BYTE parms[] = VTS_BSTR VTS_I4 ;
			InvokeHelper(0x600200c4, DISPATCH_METHOD, VT_R8, (void*)&result, parms, FileName, ChangePictureFlags);
			return result;
		}
		LPDISPATCH get_Comments()
		{
			LPDISPATCH result;
			InvokeHelper(0x600200c5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void VisualBoundingBox(short Flags, double * lpr8Left, double * lpr8Bottom, double * lpr8Right, double * lpr8Top)
		{
			static BYTE parms[] = VTS_I2 VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 ;
			InvokeHelper(0x600200c6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Flags, lpr8Left, lpr8Bottom, lpr8Right, lpr8Top);
		}

		// IVShape 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVShapes 包装类

	class CVShapes : public COleDispatchDriver
	{
	public:
		CVShapes(){} // 调用 COleDispatchDriver 默认构造函数
		CVShapes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVShapes(const CVShapes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVShapes 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(VARIANT& NameUIDOrIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &NameUIDOrIndex);
			return result;
		}
		short get_Count16()
		{
			short result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ContainingPage()
		{
			LPDISPATCH result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ContainingMaster()
		{
			LPDISPATCH result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ContainingShape()
		{
			LPDISPATCH result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void CenterDrawing()
		{
			InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_EventList()
		{
			LPDISPATCH result;
			InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_PersistsEvents()
		{
			short result;
			InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ItemFromID16(short ObjectID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, ObjectID);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ItemFromID(long ObjectID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, ObjectID);
			return result;
		}
		LPDISPATCH get_ItemU(VARIANT& NameUIDOrIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &NameUIDOrIndex);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ItemFromUniqueID(LPCTSTR UniqueID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020011, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, UniqueID);
			return result;
		}

		// IVShapes 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVStatusBar 包装类

	class CVStatusBar : public COleDispatchDriver
	{
	public:
		CVStatusBar(){} // 调用 COleDispatchDriver 默认构造函数
		CVStatusBar(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVStatusBar(const CVStatusBar& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVStatusBar 方法
	public:
		void Delete()
		{
			InvokeHelper(0x60020000, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		CString get_Default()
		{
			CString result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Caption(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Caption()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long get_SetID()
		{
			long result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_StatusBarItems()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		BOOL get_BuiltIn()
		{
			BOOL result;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Protection(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Protection()
		{
			short result;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}

		// IVStatusBar 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVStatusBarItem 包装类

	class CVStatusBarItem : public COleDispatchDriver
	{
	public:
		CVStatusBarItem(){} // 调用 COleDispatchDriver 默认构造函数
		CVStatusBarItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVStatusBarItem(const CVStatusBarItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVStatusBarItem 方法
	public:
		void Delete()
		{
			InvokeHelper(0x60020000, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void IconFileName(LPCTSTR IconFileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020001, DISPATCH_METHOD, VT_EMPTY, NULL, parms, IconFileName);
		}
		CString get_Default()
		{
			CString result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long get_Index()
		{
			long result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_CmdNum(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_CmdNum()
		{
			short result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_HelpContextID(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_HelpContextID()
		{
			short result;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_ActionText(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_ActionText()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_AddOnName(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_AddOnName()
		{
			CString result;
			InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_AddOnArgs(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_AddOnArgs()
		{
			CString result;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_HelpFile(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_HelpFile()
		{
			CString result;
			InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_CntrlType(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_CntrlType()
		{
			short result;
			InvokeHelper(0x60020011, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_CntrlID(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_CntrlID()
		{
			short result;
			InvokeHelper(0x60020013, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_TypeSpecific1(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020015, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_TypeSpecific1()
		{
			short result;
			InvokeHelper(0x60020015, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Priority(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020017, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Priority()
		{
			short result;
			InvokeHelper(0x60020017, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Spacing(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020019, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Spacing()
		{
			short result;
			InvokeHelper(0x60020019, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_TypeSpecific2(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x6002001b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_TypeSpecific2()
		{
			short result;
			InvokeHelper(0x6002001b, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Caption(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002001d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Caption()
		{
			CString result;
			InvokeHelper(0x6002001d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_MiniHelp(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002001f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_MiniHelp()
		{
			CString result;
			InvokeHelper(0x6002001f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		BOOL get_BuiltIn()
		{
			BOOL result;
			InvokeHelper(0x60020021, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Enabled(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020022, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Enabled()
		{
			BOOL result;
			InvokeHelper(0x60020022, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_FaceID(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020024, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_FaceID()
		{
			short result;
			InvokeHelper(0x60020024, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_State(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020026, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_State()
		{
			short result;
			InvokeHelper(0x60020026, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Style(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020028, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Style()
		{
			short result;
			InvokeHelper(0x60020028, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Visible(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002002a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Visible()
		{
			BOOL result;
			InvokeHelper(0x6002002a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Width(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x6002002c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Width()
		{
			short result;
			InvokeHelper(0x6002002c, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_PaletteWidth(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x6002002e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_PaletteWidth()
		{
			short result;
			InvokeHelper(0x6002002e, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_StatusBarItems()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020030, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_IsSeparator()
		{
			short result;
			InvokeHelper(0x60020031, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_IsHierarchical()
		{
			short result;
			InvokeHelper(0x60020032, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}

		// IVStatusBarItem 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVStatusBarItems 包装类

	class CVStatusBarItems : public COleDispatchDriver
	{
	public:
		CVStatusBarItems(){} // 调用 COleDispatchDriver 默认构造函数
		CVStatusBarItems(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVStatusBarItems(const CVStatusBarItems& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVStatusBarItems 方法
	public:
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long lIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, lIndex);
			return result;
		}
		LPDISPATCH Add()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020002, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH AddAt(long lIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020003, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, lIndex);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ParentItem()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}

		// IVStatusBarItems 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVStatusBars 包装类

	class CVStatusBars : public COleDispatchDriver
	{
	public:
		CVStatusBars(){} // 调用 COleDispatchDriver 默认构造函数
		CVStatusBars(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVStatusBars(const CVStatusBars& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVStatusBars 方法
	public:
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long lIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, lIndex);
			return result;
		}
		LPDISPATCH get_ItemAtID(long lID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, lID);
			return result;
		}
		LPDISPATCH Add()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020003, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH AddAtID(long lID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020004, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, lID);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}

		// IVStatusBars 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVStyle 包装类

	class CVStyle : public COleDispatchDriver
	{
	public:
		CVStyle(){} // 调用 COleDispatchDriver 默认构造函数
		CVStyle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVStyle(const CVStyle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVStyle 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Name(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Index16()
		{
			short result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_BasedOn()
		{
			CString result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_BasedOn(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_TextBasedOn()
		{
			CString result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_TextBasedOn(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_LineBasedOn()
		{
			CString result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_LineBasedOn(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_FillBasedOn()
		{
			CString result;
			InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_FillBasedOn(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_IncludesText()
		{
			short result;
			InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_IncludesText(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_IncludesLine()
		{
			short result;
			InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_IncludesLine(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_IncludesFill()
		{
			short result;
			InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_IncludesFill(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Cells(LPCTSTR localeSpecificCellName)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, localeSpecificCellName);
			return result;
		}
		void Delete()
		{
			InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_EventList()
		{
			LPDISPATCH result;
			InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_PersistsEvents()
		{
			short result;
			InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_ID16()
		{
			short result;
			InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void GetFormulas(SAFEARRAY * * SRCStream, SAFEARRAY * * formulaArray)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SRCStream, formulaArray);
		}
		void GetResults(SAFEARRAY * * SRCStream, short Flags, SAFEARRAY * * UnitsNamesOrCodes, SAFEARRAY * * resultArray)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_I2 VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SRCStream, Flags, UnitsNamesOrCodes, resultArray);
		}
		short SetFormulas(SAFEARRAY * * SRCStream, SAFEARRAY * * formulaArray, short Flags)
		{
			short result;
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN VTS_I2 ;
			InvokeHelper(0x14, DISPATCH_METHOD, VT_I2, (void*)&result, parms, SRCStream, formulaArray, Flags);
			return result;
		}
		short SetResults(SAFEARRAY * * SRCStream, SAFEARRAY * * UnitsNamesOrCodes, SAFEARRAY * * resultArray, short Flags)
		{
			short result;
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN VTS_UNKNOWN VTS_I2 ;
			InvokeHelper(0x15, DISPATCH_METHOD, VT_I2, (void*)&result, parms, SRCStream, UnitsNamesOrCodes, resultArray, Flags);
			return result;
		}
		long get_ID()
		{
			long result;
			InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Index()
		{
			long result;
			InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Section(short Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		short get_Hidden()
		{
			short result;
			InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Hidden(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_NameU()
		{
			CString result;
			InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_NameU(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_CellsU(LPCTSTR localeIndependentCellName)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, localeIndependentCellName);
			return result;
		}
		short get_CellExists(LPCTSTR localeSpecificCellName, short fExistsLocally)
		{
			short result;
			static BYTE parms[] = VTS_BSTR VTS_I2 ;
			InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, localeSpecificCellName, fExistsLocally);
			return result;
		}
		short get_CellExistsU(LPCTSTR localeIndependentCellName, short fExistsLocally)
		{
			short result;
			static BYTE parms[] = VTS_BSTR VTS_I2 ;
			InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, localeIndependentCellName, fExistsLocally);
			return result;
		}
		void GetFormulasU(SAFEARRAY * * SRCStream, SAFEARRAY * * formulaArray)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x1e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SRCStream, formulaArray);
		}
		LPDISPATCH get_CellsSRC(short Section, short Row, short Column)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
			InvokeHelper(0x60020029, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Section, Row, Column);
			return result;
		}
		short get_CellsSRCExists(short Section, short Row, short Column, short fExistsLocally)
		{
			short result;
			static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 VTS_I2 ;
			InvokeHelper(0x6002002a, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, Section, Row, Column, fExistsLocally);
			return result;
		}

		// IVStyle 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVStyles 包装类

	class CVStyles : public COleDispatchDriver
	{
	public:
		CVStyles(){} // 调用 COleDispatchDriver 默认构造函数
		CVStyles(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVStyles(const CVStyles& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVStyles 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(VARIANT& NameOrIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &NameOrIndex);
			return result;
		}
		short get_Count16()
		{
			short result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Add(LPCTSTR StyleName, LPCTSTR BasedOn, short fIncludesText, short fIncludesLine, short fIncludesFill)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I2 VTS_I2 VTS_I2 ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, StyleName, BasedOn, fIncludesText, fIncludesLine, fIncludesFill);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_EventList()
		{
			LPDISPATCH result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_PersistsEvents()
		{
			short result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ItemFromID16(short ObjectID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, ObjectID);
			return result;
		}
		void GetNames(SAFEARRAY * * localeSpecificNameArray)
		{
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, localeSpecificNameArray);
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ItemFromID(long ObjectID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, ObjectID);
			return result;
		}
		LPDISPATCH get_ItemU(VARIANT& NameOrIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &NameOrIndex);
			return result;
		}
		void GetNamesU(SAFEARRAY * * localeIndependentNameArray)
		{
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms, localeIndependentNameArray);
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}

		// IVStyles 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVToolbar 包装类

	class CVToolbar : public COleDispatchDriver
	{
	public:
		CVToolbar(){} // 调用 COleDispatchDriver 默认构造函数
		CVToolbar(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVToolbar(const CVToolbar& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVToolbar 方法
	public:
		void Delete()
		{
			InvokeHelper(0x60020000, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		CString get_Default()
		{
			CString result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Caption(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Caption()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long get_Index()
		{
			long result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ToolbarItems()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		BOOL get_BuiltIn()
		{
			BOOL result;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Enabled(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Enabled()
		{
			BOOL result;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Height(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Height()
		{
			short result;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Left(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Left()
		{
			short result;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Position(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x6002000e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Position()
		{
			short result;
			InvokeHelper(0x6002000e, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Protection(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020010, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Protection()
		{
			short result;
			InvokeHelper(0x60020010, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_RowIndex(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020012, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_RowIndex()
		{
			short result;
			InvokeHelper(0x60020012, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Top(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020014, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Top()
		{
			short result;
			InvokeHelper(0x60020014, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Visible(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020016, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Visible()
		{
			BOOL result;
			InvokeHelper(0x60020016, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Width(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020018, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Width()
		{
			short result;
			InvokeHelper(0x60020018, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}

		// IVToolbar 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVToolbarItem 包装类

	class CVToolbarItem : public COleDispatchDriver
	{
	public:
		CVToolbarItem(){} // 调用 COleDispatchDriver 默认构造函数
		CVToolbarItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVToolbarItem(const CVToolbarItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVToolbarItem 方法
	public:
		void Delete()
		{
			InvokeHelper(0x60020000, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void IconFileName(LPCTSTR IconFileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020001, DISPATCH_METHOD, VT_EMPTY, NULL, parms, IconFileName);
		}
		CString get_Default()
		{
			CString result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long get_Index()
		{
			long result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_CmdNum(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_CmdNum()
		{
			short result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_HelpContextID(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_HelpContextID()
		{
			short result;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_ActionText(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_ActionText()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_AddOnName(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_AddOnName()
		{
			CString result;
			InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_AddOnArgs(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_AddOnArgs()
		{
			CString result;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_HelpFile(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_HelpFile()
		{
			CString result;
			InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_CntrlType(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_CntrlType()
		{
			short result;
			InvokeHelper(0x60020011, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_CntrlID(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_CntrlID()
		{
			short result;
			InvokeHelper(0x60020013, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_TypeSpecific1(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020015, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_TypeSpecific1()
		{
			short result;
			InvokeHelper(0x60020015, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Priority(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020017, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Priority()
		{
			short result;
			InvokeHelper(0x60020017, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Spacing(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020019, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Spacing()
		{
			short result;
			InvokeHelper(0x60020019, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_TypeSpecific2(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x6002001b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_TypeSpecific2()
		{
			short result;
			InvokeHelper(0x6002001b, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Caption(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002001d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Caption()
		{
			CString result;
			InvokeHelper(0x6002001d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_MiniHelp(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002001f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_MiniHelp()
		{
			CString result;
			InvokeHelper(0x6002001f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		BOOL get_BuiltIn()
		{
			BOOL result;
			InvokeHelper(0x60020021, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Enabled(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020022, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Enabled()
		{
			BOOL result;
			InvokeHelper(0x60020022, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_FaceID(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020024, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_FaceID()
		{
			short result;
			InvokeHelper(0x60020024, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_State(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020026, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_State()
		{
			short result;
			InvokeHelper(0x60020026, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Style(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020028, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Style()
		{
			short result;
			InvokeHelper(0x60020028, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_Visible(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002002a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Visible()
		{
			BOOL result;
			InvokeHelper(0x6002002a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Width(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x6002002c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Width()
		{
			short result;
			InvokeHelper(0x6002002c, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_PaletteWidth(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x6002002e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_PaletteWidth()
		{
			short result;
			InvokeHelper(0x6002002e, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ToolbarItems()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020030, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_IsSeparator()
		{
			short result;
			InvokeHelper(0x60020031, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_IsHierarchical()
		{
			short result;
			InvokeHelper(0x60020032, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_BeginGroup(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020033, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_BeginGroup()
		{
			BOOL result;
			InvokeHelper(0x60020033, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}

		// IVToolbarItem 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVToolbarItems 包装类

	class CVToolbarItems : public COleDispatchDriver
	{
	public:
		CVToolbarItems(){} // 调用 COleDispatchDriver 默认构造函数
		CVToolbarItems(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVToolbarItems(const CVToolbarItems& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVToolbarItems 方法
	public:
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long lIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, lIndex);
			return result;
		}
		LPDISPATCH Add()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020002, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH AddAt(long lIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020003, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, lIndex);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ParentItem()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}

		// IVToolbarItems 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVToolbars 包装类

	class CVToolbars : public COleDispatchDriver
	{
	public:
		CVToolbars(){} // 调用 COleDispatchDriver 默认构造函数
		CVToolbars(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVToolbars(const CVToolbars& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVToolbars 方法
	public:
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long lIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, lIndex);
			return result;
		}
		LPDISPATCH Add()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020002, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH AddAt(long lIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020003, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, lIndex);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}

		// IVToolbars 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVToolbarSet 包装类

	class CVToolbarSet : public COleDispatchDriver
	{
	public:
		CVToolbarSet(){} // 调用 COleDispatchDriver 默认构造函数
		CVToolbarSet(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVToolbarSet(const CVToolbarSet& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVToolbarSet 方法
	public:
		void Delete()
		{
			InvokeHelper(0x60020000, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		CString get_Default()
		{
			CString result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Caption(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Caption()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long get_SetID()
		{
			long result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Toolbars()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}

		// IVToolbarSet 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVToolbarSets 包装类

	class CVToolbarSets : public COleDispatchDriver
	{
	public:
		CVToolbarSets(){} // 调用 COleDispatchDriver 默认构造函数
		CVToolbarSets(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVToolbarSets(const CVToolbarSets& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVToolbarSets 方法
	public:
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long lIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, lIndex);
			return result;
		}
		LPDISPATCH get_ItemAtID(long lID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, lID);
			return result;
		}
		LPDISPATCH Add()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020003, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH AddAtID(long lID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020004, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, lID);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}

		// IVToolbarSets 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVUIObject 包装类

	class CVUIObject : public COleDispatchDriver
	{
	public:
		CVUIObject(){} // 调用 COleDispatchDriver 默认构造函数
		CVUIObject(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVUIObject(const CVUIObject& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVUIObject 方法
	public:
		void Delete()
		{
			InvokeHelper(0x60020000, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		CString get_Default()
		{
			CString result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Name(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Flavor(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_Flavor()
		{
			short result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_MenuSets()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ToolbarSets()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_StatusBars()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_AccelTables()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020009, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void SaveToFile(LPCTSTR FileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002000a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
		}
		void LoadFromFile(LPCTSTR FileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002000b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
		}
		void UpdateUI()
		{
			InvokeHelper(0x6002000c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		BOOL get_DisplayKeysInTooltips()
		{
			BOOL result;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_DisplayKeysInTooltips(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_DisplayTooltips()
		{
			BOOL result;
			InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_DisplayTooltips(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_LargeButtons()
		{
			BOOL result;
			InvokeHelper(0x60020011, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_LargeButtons(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_MenuAnimationStyle()
		{
			short result;
			InvokeHelper(0x60020013, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_MenuAnimationStyle(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x60020013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Clone()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020015, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}

		// IVUIObject 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVValidation 包装类

	class CVValidation : public COleDispatchDriver
	{
	public:
		CVValidation(){} // 调用 COleDispatchDriver 默认构造函数
		CVValidation(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVValidation(const CVValidation& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVValidation 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		DATE get_LastValidatedDate()
		{
			DATE result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
			return result;
		}
		BOOL get_ShowIgnoredIssues()
		{
			BOOL result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ShowIgnoredIssues(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_RuleSets()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Issues()
		{
			LPDISPATCH result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Validate(LPDISPATCH RuleSet, long Flags)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_I4 ;
			InvokeHelper(0x60020009, DISPATCH_METHOD, VT_EMPTY, NULL, parms, RuleSet, Flags);
		}

		// IVValidation 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVValidationIssue 包装类

	class CVValidationIssue : public COleDispatchDriver
	{
	public:
		CVValidationIssue(){} // 调用 COleDispatchDriver 默认构造函数
		CVValidationIssue(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVValidationIssue(const CVValidationIssue& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVValidationIssue 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		long get_ID()
		{
			long result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_TargetPage()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_TargetPageID()
		{
			long result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_TargetShape()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		BOOL get_Ignored()
		{
			BOOL result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Ignored(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Rule()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Delete()
		{
			InvokeHelper(0x6002000b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}

		// IVValidationIssue 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVValidationIssues 包装类

	class CVValidationIssues : public COleDispatchDriver
	{
	public:
		CVValidationIssues(){} // 调用 COleDispatchDriver 默认构造函数
		CVValidationIssues(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVValidationIssues(const CVValidationIssues& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVValidationIssues 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		LPDISPATCH get_ItemFromID(long IssueID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, IssueID);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		void Clear()
		{
			InvokeHelper(0x60020008, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}

		// IVValidationIssues 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVValidationRule 包装类

	class CVValidationRule : public COleDispatchDriver
	{
	public:
		CVValidationRule(){} // 调用 COleDispatchDriver 默认构造函数
		CVValidationRule(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVValidationRule(const CVValidationRule& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVValidationRule 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		long get_ID()
		{
			long result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_NameU()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_NameU(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Category()
		{
			CString result;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Category(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Description()
		{
			CString result;
			InvokeHelper(0x60020009, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Description(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020009, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Ignored()
		{
			BOOL result;
			InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Ignored(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_FilterExpression()
		{
			CString result;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_FilterExpression(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_TargetType()
		{
			long result;
			InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_TargetType(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_TestExpression()
		{
			CString result;
			InvokeHelper(0x60020011, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_TestExpression(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_RuleSet()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020013, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Delete()
		{
			InvokeHelper(0x60020014, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH AddIssue(LPDISPATCH TargetPage, LPDISPATCH TargetShape)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH ;
			InvokeHelper(0x60020015, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, TargetPage, TargetShape);
			return result;
		}

		// IVValidationRule 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVValidationRules 包装类

	class CVValidationRules : public COleDispatchDriver
	{
	public:
		CVValidationRules(){} // 调用 COleDispatchDriver 默认构造函数
		CVValidationRules(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVValidationRules(const CVValidationRules& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVValidationRules 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(VARIANT& NameUOrIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &NameUOrIndex);
			return result;
		}
		LPDISPATCH get_ItemFromID(long RuleID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, RuleID);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Add(LPCTSTR NameU)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020008, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, NameU);
			return result;
		}

		// IVValidationRules 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVValidationRuleSet 包装类

	class CVValidationRuleSet : public COleDispatchDriver
	{
	public:
		CVValidationRuleSet(){} // 调用 COleDispatchDriver 默认构造函数
		CVValidationRuleSet(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVValidationRuleSet(const CVValidationRuleSet& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVValidationRuleSet 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		long get_ID()
		{
			long result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Name(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_NameU()
		{
			CString result;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_NameU(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Description()
		{
			CString result;
			InvokeHelper(0x60020009, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Description(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020009, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Enabled()
		{
			BOOL result;
			InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Enabled(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_RuleSetFlags()
		{
			long result;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_RuleSetFlags(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Rules()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Delete()
		{
			InvokeHelper(0x60020010, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}

		// IVValidationRuleSet 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVValidationRuleSets 包装类

	class CVValidationRuleSets : public COleDispatchDriver
	{
	public:
		CVValidationRuleSets(){} // 调用 COleDispatchDriver 默认构造函数
		CVValidationRuleSets(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVValidationRuleSets(const CVValidationRuleSets& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVValidationRuleSets 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(VARIANT& NameUOrIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &NameUOrIndex);
			return result;
		}
		LPDISPATCH get_ItemFromID(long RuleID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, RuleID);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Add(LPCTSTR NameU)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020008, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, NameU);
			return result;
		}
		LPDISPATCH AddCopy(LPDISPATCH RuleSet, LPCTSTR NameU)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_DISPATCH VTS_BSTR ;
			InvokeHelper(0x60020009, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, RuleSet, NameU);
			return result;
		}

		// IVValidationRuleSets 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVWindow 包装类

	class CVWindow : public COleDispatchDriver
	{
	public:
		CVWindow(){} // 调用 COleDispatchDriver 默认构造函数
		CVWindow(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVWindow(const CVWindow& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVWindow 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_Stat()
		{
			short result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void Activate()
		{
			InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		short get_Type()
		{
			short result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Document()
		{
			LPDISPATCH result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_PageAsObj()
		{
			LPDISPATCH result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_PageFromName(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x2bb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		double get_Zoom()
		{
			double result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_Zoom(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Close()
		{
			InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void SelectAll()
		{
			InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void DeselectAll()
		{
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_Selection()
		{
			LPDISPATCH result;
			InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Select(LPDISPATCH SheetObject, short SelectAction)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_I2 ;
			InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SheetObject, SelectAction);
		}
		short get_Index()
		{
			short result;
			InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void Cut()
		{
			InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Copy()
		{
			InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Paste()
		{
			InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Delete()
		{
			InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Duplicate()
		{
			InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Group()
		{
			InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Union()
		{
			InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Combine()
		{
			InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Fragment()
		{
			InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void AddToGroup()
		{
			InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void RemoveFromGroup()
		{
			InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		short get_SubType()
		{
			short result;
			InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void Intersect()
		{
			InvokeHelper(0x1a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Subtract()
		{
			InvokeHelper(0x1b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_EventList()
		{
			LPDISPATCH result;
			InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_PersistsEvents()
		{
			short result;
			InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		short get_WindowHandle()
		{
			short result;
			InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		long get_WindowHandle32()
		{
			long result;
			InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void Trim()
		{
			InvokeHelper(0x20, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Join()
		{
			InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		short get_ShowRulers()
		{
			short result;
			InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_ShowRulers(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x22, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_ShowGrid()
		{
			short result;
			InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_ShowGrid(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x23, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_ShowGuides()
		{
			short result;
			InvokeHelper(0x24, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_ShowGuides(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x24, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_ShowConnectPoints()
		{
			short result;
			InvokeHelper(0x25, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_ShowConnectPoints(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x25, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		short get_ShowPageBreaks()
		{
			short result;
			InvokeHelper(0x26, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_ShowPageBreaks(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x26, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		VARIANT get_Page()
		{
			VARIANT result;
			InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_Page(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x27, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		void DockedStencils(SAFEARRAY * * NameArray)
		{
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0x28, DISPATCH_METHOD, VT_EMPTY, NULL, parms, NameArray);
		}
		VARIANT get_Master()
		{
			VARIANT result;
			InvokeHelper(0x29, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		short get_ShowScrollBars()
		{
			short result;
			InvokeHelper(0x2a, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void put_ShowScrollBars(short newValue)
		{
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x2a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Visible()
		{
			BOOL result;
			InvokeHelper(0x2b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Visible(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x2b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Caption()
		{
			CString result;
			InvokeHelper(0x2c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Caption(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x2c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Windows()
		{
			LPDISPATCH result;
			InvokeHelper(0x2d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Scroll(long nxFlags, long nyFlags)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0x2e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nxFlags, nyFlags);
		}
		void ScrollViewTo(double x, double y)
		{
			static BYTE parms[] = VTS_R8 VTS_R8 ;
			InvokeHelper(0x2f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, x, y);
		}
		void GetViewRect(double * pdLeft, double * pdTop, double * pdWidth, double * pdHeight)
		{
			static BYTE parms[] = VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 ;
			InvokeHelper(0x30, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pdLeft, pdTop, pdWidth, pdHeight);
		}
		void SetViewRect(double dLeft, double dTop, double dWidth, double dHeight)
		{
			static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
			InvokeHelper(0x31, DISPATCH_METHOD, VT_EMPTY, NULL, parms, dLeft, dTop, dWidth, dHeight);
		}
		void GetWindowRect(long * pnLeft, long * pnTop, long * pnWidth, long * pnHeight)
		{
			static BYTE parms[] = VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 ;
			InvokeHelper(0x32, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pnLeft, pnTop, pnWidth, pnHeight);
		}
		void SetWindowRect(long nLeft, long nTop, long nWidth, long nHeight)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
			InvokeHelper(0x33, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nLeft, nTop, nWidth, nHeight);
		}
		long get_WindowState()
		{
			long result;
			InvokeHelper(0x34, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_WindowState(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x34, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_ViewFit()
		{
			long result;
			InvokeHelper(0x35, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_ViewFit(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x35, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_IsEditingText()
		{
			BOOL result;
			InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		BOOL get_IsEditingOLE()
		{
			BOOL result;
			InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x38, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_MasterShortcut()
		{
			LPDISPATCH result;
			InvokeHelper(0x39, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_ID()
		{
			long result;
			InvokeHelper(0x3a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ParentWindow()
		{
			LPDISPATCH result;
			InvokeHelper(0x3b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_MergeID()
		{
			CString result;
			InvokeHelper(0x60020049, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_MergeClass()
		{
			CString result;
			InvokeHelper(0x6002004a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long get_MergePosition()
		{
			long result;
			InvokeHelper(0x6002004b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_AllowEditing()
		{
			BOOL result;
			InvokeHelper(0x6002004c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_AllowEditing(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002004c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		double get_PageTabWidth()
		{
			double result;
			InvokeHelper(0x6002004e, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_PageTabWidth(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x6002004e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ShowPageTabs()
		{
			BOOL result;
			InvokeHelper(0x60020050, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ShowPageTabs(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020050, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_MergeID(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020049, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_MergeClass(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002004a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_MergePosition(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002004b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_InPlace()
		{
			BOOL result;
			InvokeHelper(0x60020055, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		CString get_MergeCaption()
		{
			CString result;
			InvokeHelper(0x60020056, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_MergeCaption(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020056, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Icon()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020058, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void putref_Icon(LPDISPATCH newValue)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x60020058, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Shape()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002005a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_SelectedCell()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002005b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH NewWindow()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002005c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		unsigned long get_BackgroundColor()
		{
			unsigned long result;
			InvokeHelper(0x6002005d, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
			return result;
		}
		void put_BackgroundColor(unsigned long newValue)
		{
			static BYTE parms[] = VTS_UI4 ;
			InvokeHelper(0x6002005d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		unsigned long get_BackgroundColorGradient()
		{
			unsigned long result;
			InvokeHelper(0x6002005f, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
			return result;
		}
		void put_BackgroundColorGradient(unsigned long newValue)
		{
			static BYTE parms[] = VTS_UI4 ;
			InvokeHelper(0x6002005f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ShowPageOutline()
		{
			BOOL result;
			InvokeHelper(0x60020061, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ShowPageOutline(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020061, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ScrollLock()
		{
			BOOL result;
			InvokeHelper(0x60020063, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ScrollLock(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020063, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ZoomLock()
		{
			BOOL result;
			InvokeHelper(0x60020065, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ZoomLock(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020065, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_ZoomBehavior()
		{
			long result;
			InvokeHelper(0x60020067, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_ZoomBehavior(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020067, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		SAFEARRAY * get_SelectedMasters()
		{
			InvokeHelper(0x60020069, DISPATCH_PROPERTYGET, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_SelectedText()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002006a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_SelectedText(LPDISPATCH newValue)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x6002006a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ReviewerMarkupVisible(long ReviewerID)
		{
			BOOL result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002006c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, ReviewerID);
			return result;
		}
		void put_ReviewerMarkupVisible(long ReviewerID, BOOL newValue)
		{
			static BYTE parms[] = VTS_I4 VTS_BOOL ;
			InvokeHelper(0x6002006c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, ReviewerID, newValue);
		}
		void put_Selection(LPDISPATCH newValue)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_SelectedDataRecordset()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002006f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_SelectedDataRecordset(LPDISPATCH newValue)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x6002006f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_SelectedDataRowID()
		{
			long result;
			InvokeHelper(0x60020071, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_SelectedDataRowID(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020071, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_SelectionForDragCopy()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020073, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_SelectedValidationIssue(LPDISPATCH newValue)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x60020074, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_SelectedValidationIssue()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020074, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void CenterViewOnShape(LPDISPATCH SheetObject, long Flags)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_I4 ;
			InvokeHelper(0x60020076, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SheetObject, Flags);
		}

		// IVWindow 属性
	public:

	};

	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


	// CVWindows 包装类

	class CVWindows : public COleDispatchDriver
	{
	public:
		CVWindows(){} // 调用 COleDispatchDriver 默认构造函数
		CVWindows(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVWindows(const CVWindows& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVWindows 方法
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_ObjectType()
		{
			short result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(short Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I2 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		short get_Count()
		{
			short result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		void VoidArrange()
		{
			InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_EventList()
		{
			LPDISPATCH result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		short get_PersistsEvents()
		{
			short result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Add_WithoutMergeArgs(VARIANT& bstrCaption, VARIANT& nFlags, VARIANT& nType, VARIANT& nLeft, VARIANT& nTop, VARIANT& nWidth, VARIANT& nHeight)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &bstrCaption, &nFlags, &nType, &nLeft, &nTop, &nWidth, &nHeight);
			return result;
		}
		void Arrange(VARIANT& nArrangeFlags)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &nArrangeFlags);
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ItemFromID(long nID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, nID);
			return result;
		}
		LPDISPATCH Add(VARIANT& bstrCaption, VARIANT& nFlags, VARIANT& nType, VARIANT& nLeft, VARIANT& nTop, VARIANT& nWidth, VARIANT& nHeight, VARIANT& bstrMergeID, VARIANT& bstrMergeClass, VARIANT& nMergePosition)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x6002000b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &bstrCaption, &nFlags, &nType, &nLeft, &nTop, &nWidth, &nHeight, &bstrMergeID, &bstrMergeClass, &nMergePosition);
			return result;
		}
		LPDISPATCH get_ItemEx(VARIANT& CaptionOrIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &CaptionOrIndex);
			return result;
		}

		// IVWindows 属性
	public:

	};
}

#endif