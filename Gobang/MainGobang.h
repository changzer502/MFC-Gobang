#pragma once
#include <afxdialogex.h>
#include "GobangHandle.h"
#include "HistoryDIg.h"
// MainGobang 对话框

class MainGobang : public CDialogEx
{
	DECLARE_DYNAMIC(MainGobang)

public:
	MainGobang(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MainGobang();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
public:
	CStdioFile file;
	int choose;
	CMainGobang gobang;
	CStatic m_picDraw1;		//画图控件
	bool bIsReady;			//可以开始
	bool bWithdraw;			//悔棋次数
	CStatic m_picDraw;
	CString userName;
	CString userId;
	void saveData(int x);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
};

