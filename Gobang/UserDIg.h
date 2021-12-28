#pragma once


// UserDIg 对话框

class UserDIg : public CDialogEx
{
	DECLARE_DYNAMIC(UserDIg)

public:
	UserDIg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~UserDIg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	bool readData();
	CString login;
	CString loginId;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
