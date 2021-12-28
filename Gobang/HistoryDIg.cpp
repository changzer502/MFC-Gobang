// HistoryDIg.cpp: 实现文件
//

#include "pch.h"
#include "Gobang.h"
#include "HistoryDIg.h"
#include "afxdialogex.h"
#include <mysql.h>
#include <iostream>

// HistoryDIg 对话框

IMPLEMENT_DYNAMIC(HistoryDIg, CDialogEx)

HistoryDIg::HistoryDIg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, history(_T(""))
{

}

HistoryDIg::~HistoryDIg()
{
}

void HistoryDIg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, history);
}


BEGIN_MESSAGE_MAP(HistoryDIg, CDialogEx)
	ON_BN_CLICKED(IDOK, &HistoryDIg::OnBnClickedOk)
END_MESSAGE_MAP()


// HistoryDIg 消息处理程序

BOOL HistoryDIg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作

	// TODO: 在此添加额外的初始化代码
	readData();


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void HistoryDIg::readData() {
	MYSQL m_sqlCon;
	mysql_init(&m_sqlCon);
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root", "2784247628", "gobang", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败！"));
		return;
	}
	else {

		//AfxMessageBox(_T("数据库连接成功!"));
		UpdateData(true);
		//设置数据库字符格式，解决中文乱码问题  
		mysql_query(&m_sqlCon, "set names 'gb2312'");

		char sqlstr[64] = "SELECT id, result, userId FROM g_result where userId = ";
		//声明标识
		USES_CONVERSION;
		//函数T2A和W2A均支持ATL和MFC中的字符
		char* loginId = T2A(id);
		strcat_s(sqlstr, "\"");
		strcat_s(sqlstr, loginId);
		strcat_s(sqlstr, "\"");
		MYSQL_RES* result = NULL;
		if (0 == mysql_query(&m_sqlCon, sqlstr)) {
			
			//一次性取得数据集
			result = mysql_store_result(&m_sqlCon);
			//取得并打印行数
			int rowcount = mysql_num_rows(result);
			
			//取得并打印各字段的名称
			int fieldcount = mysql_num_fields(result);
			MYSQL_FIELD* field = NULL;
			for (unsigned int i = 0; i < fieldcount; i++) {
				field = mysql_fetch_field_direct(result, i);
			}
			//打印各行
			CFont font;
			font.CreatePointFont(120, _T("楷体"));
			GetDlgItem(IDC_EDIT1)->SetFont(&font);
			MYSQL_ROW row = NULL;
			row = mysql_fetch_row(result);
			int count = 0;
			while (NULL != row) {
				CString resultData;
				for (int i = 0; i < fieldcount; i = i+3) {
					//if (CStringW(row[i + 2]) == id) {
						resultData += _T("第");
						count++;
						CString d;
						d.Format(_T("%d"), count);
						resultData += d;
						resultData += _T("回合   ");
						resultData += CStringW(row[i + 1]);
						resultData += _T("\r\n");
					//}
					
					
				}
				data += resultData;
				row = mysql_fetch_row(result);
			}
			history += data;
		}
		else {
			mysql_close(&m_sqlCon);
		}
	}
	if (history == "") {
		history += "还没有历史记录哦，\r\n快去下棋吧\r\n\r\n^.^";
	}
	UpdateData(false);
	mysql_close(&m_sqlCon);//关闭Mysql连接 
}

void HistoryDIg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
