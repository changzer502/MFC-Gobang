// UserDIg.cpp: 实现文件

#include "pch.h"
#include "Gobang.h"
#include "UserDIg.h"
#include "afxdialogex.h"
#include "MainGobang.h"
#include "LoginDIg.h"
#include <mysql.h>


// UserDIg 对话框

IMPLEMENT_DYNAMIC(UserDIg, CDialogEx)

UserDIg::UserDIg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

UserDIg::~UserDIg()
{
}

void UserDIg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, login);
}


BEGIN_MESSAGE_MAP(UserDIg, CDialogEx)
	ON_BN_CLICKED(IDOK, &UserDIg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &UserDIg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &UserDIg::OnBnClickedButton2)
END_MESSAGE_MAP()


// UserDIg 消息处理程序
bool UserDIg::readData() {
	MYSQL m_sqlCon;
	mysql_init(&m_sqlCon);
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root", "2784247628", "gobang", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败！"));
		return false;
	}
	else {

		//AfxMessageBox(_T("数据库连接成功!"));
		UpdateData(true);
		//设置数据库字符格式，解决中文乱码问题  
		mysql_query(&m_sqlCon, "set names 'gb2312'");

		char sqlstr[64] = "SELECT id, userName FROM g_user where userName = ";
		//声明标识
		USES_CONVERSION;
		//函数T2A和W2A均支持ATL和MFC中的字符
		login.Trim();
		char* loginName = T2A(login);
		strcat_s(sqlstr, "\"");
		strcat_s(sqlstr, loginName);
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
			MYSQL_ROW row = NULL;
			row = mysql_fetch_row(result);
			int count = 0;
			if (NULL == row) return false;
			while (NULL != row) {
				
				for (int i = 0; i < fieldcount; i = i + 2) {
					loginId = CStringW(row[i]);
				}
				
				row = mysql_fetch_row(result);
			}
		}
		else {
			mysql_close(&m_sqlCon);
			return false;
		}
	}
	UpdateData(false);
	mysql_close(&m_sqlCon);//关闭Mysql连接 
	return true;
}

void UserDIg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	//MessageBox(login);
	if (readData()) {
		this->ShowWindow(SW_HIDE);
		MainGobang mainGobang;//ShowUserDlg为对话框类，myshowursedlg为对话框类实体
		mainGobang.choose = 1;
		mainGobang.userName = login;
		mainGobang.userId = loginId;
		mainGobang.DoModal();//显示模态对话框
		this->ShowWindow(SW_SHOW);
	}
	else {
		MessageBox(_T("用户名不存在哦，请注册后再试"));
	}
	
}




void UserDIg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	LoginDIg loginDIg;
	loginDIg.DoModal();
}


void UserDIg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);
	MainGobang mainGobang;//ShowUserDlg为对话框类，myshowursedlg为对话框类实体
	mainGobang.choose = 1;
	mainGobang.userName = _T("游客");
	mainGobang.userId = _T("2");
	mainGobang.DoModal();//显示模态对话框
	this->ShowWindow(SW_SHOW);
}
