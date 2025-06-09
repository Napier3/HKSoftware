#pragma once


// CUIDeviceNodeTree

class CUIDeviceNodeTree : public CTreeCtrl
{
	DECLARE_DYNAMIC(CUIDeviceNodeTree)

public:
	CUIDeviceNodeTree();
	virtual ~CUIDeviceNodeTree();

	void ShowDevice(CPpDevice *pDevice);
	void InsertDeviceNode(CPpDeviceNode *pDeviceNode);
	CExBaseObject* GetCurrSelObject();

private:
	void InsertDvObject(CExBaseObject *pObj, HTREEITEM hParent);

protected:
	DECLARE_MESSAGE_MAP()
};


