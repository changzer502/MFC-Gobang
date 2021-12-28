#pragma once
// SettingDIg 对话框

class SettingDIg : public CDialogEx
{
	DECLARE_DYNAMIC(SettingDIg)

public:
	SettingDIg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SettingDIg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	int choose;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedOk();
	CString str;
};
