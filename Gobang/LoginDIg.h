#pragma once


// LoginDIg 对话框

class LoginDIg : public CDialogEx
{
	DECLARE_DYNAMIC(LoginDIg)

public:
	LoginDIg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~LoginDIg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString registName;
	void saveData();
	afx_msg void OnBnClickedOk();
};
