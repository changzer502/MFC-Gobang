#pragma once


// HistoryDIg 对话框

class HistoryDIg : public CDialogEx
{
	DECLARE_DYNAMIC(HistoryDIg)

public:
	HistoryDIg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~HistoryDIg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString data;
	CString history;
	CString name;
	CString id;
	void readData();
	afx_msg void OnBnClickedOk();
};
