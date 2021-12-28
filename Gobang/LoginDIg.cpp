// LoginDIg.cpp: 实现文件
//

#include "pch.h"
#include "Gobang.h"
#include "LoginDIg.h"
#include "afxdialogex.h"
#include <mysql.h>


// LoginDIg 对话框

IMPLEMENT_DYNAMIC(LoginDIg, CDialogEx)

LoginDIg::LoginDIg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG5, pParent)
	, registName(_T(""))
{

}

LoginDIg::~LoginDIg()
{
}

void LoginDIg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, registName);
}


BEGIN_MESSAGE_MAP(LoginDIg, CDialogEx)
	ON_BN_CLICKED(IDOK, &LoginDIg::OnBnClickedOk)
END_MESSAGE_MAP()


 //LoginDIg 消息处理程序
void LoginDIg::saveData( ) {
	MYSQL m_sqlCon;
	mysql_init(&m_sqlCon);
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root", "2784247628", "gobang", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败！"));
		return;
	}
	else {

		//AfxMessageBox(_T("数据库连接成功!"));
		//设置数据库字符格式，解决中文乱码问题  
		mysql_query(&m_sqlCon, "set names 'gb2312'");
		bool sameFlag = false;
		char sqlstr[64] = "SELECT id, userName FROM g_user where userName = ";
		//声明标识
		USES_CONVERSION;
		//函数T2A和W2A均支持ATL和MFC中的字符
		char* name = T2A(registName);
		strcat_s(sqlstr, "\"");
		strcat_s(sqlstr, name);
		strcat_s(sqlstr, "\"");
		if (0 == mysql_query(&m_sqlCon, sqlstr)) {
			MYSQL_RES* result = NULL;
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
			if (NULL != row)  sameFlag = true;
		}

		if (!sameFlag) {
			char insert[64];
			sprintf_s(insert, "insert into g_user( userName ) values (\'%s\')",
				name);

			// 执行 sql 语句。    
			// mysql_query() 的返回值份很多情形， 进行判断使要注意。    
			if (mysql_query(&m_sqlCon, insert) == 0)
			{
				//AfxMessageBox(_T("插入数据成功!"));
			}
			else {
				AfxMessageBox(_T("插入数据失败!"));
			}
		}
		else {
			MessageBox(_T("该用户名已经存在了"));
		}

	}

	mysql_close(&m_sqlCon);//关闭Mysql连接  
}

void LoginDIg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	saveData();
	UpdateData(false);

	CDialogEx::OnOK();
}
