// MainGobang.cpp: 实现文件

#include "pch.h"
#include "Gobang.h"
#include "MainGobang.h"
#include "SettingDIg.h"
#include "afxdialogex.h"
#include "mmsystem.h"
#include <mysql.h>
#pragma comment(lib,"WINMM.LIB")
// MainGobang 对话框


IMPLEMENT_DYNAMIC(MainGobang, CDialogEx)

MainGobang::MainGobang(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

MainGobang::~MainGobang()
{
}

void MainGobang::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WAVE_DRAW, m_picDraw);
}


BEGIN_MESSAGE_MAP(MainGobang, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &MainGobang::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &MainGobang::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &MainGobang::OnBnClickedButton2)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_SETCURSOR()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_BUTTON7, &MainGobang::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &MainGobang::OnBnClickedButton8)
END_MESSAGE_MAP()


// MainGobang 消息处理程序

BOOL MainGobang::OnInitDialog()
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
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CString statcCon = _T("  你好！");
	statcCon += userName;
	statcCon += _T("~");
	GetDlgItem(IDC_STATIC_USER)->SetWindowText(statcCon);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void MainGobang::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}


void MainGobang::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		CRect rect;
		GetClientRect(&rect);
		CDC dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap   bmpBackground;
		CBitmap   bmp;
		bmp.LoadBitmap(IDB_BITMAP1);	//对话框的背景图片  

		BITMAP   bitmap;
		bmp.GetBitmap(&bitmap);
		CBitmap* pbmpOld = dcMem.SelectObject(&bmp);
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

		CRect rectPicture;
		// 获取绘图控件的客户区坐标   
		// （客户区坐标以窗口的左上角为原点，这区别于以屏幕左上角为原点的屏幕坐标）   
		m_picDraw.GetClientRect(&rectPicture);
		// 绘制图   
		if (choose == 1)
		{
			gobang.DrawMainTable(m_picDraw.GetDC(), rectPicture, 15);//标准棋盘
		}
		if (choose == 2)
		{
			gobang.DrawMainTable(m_picDraw.GetDC(), rectPicture, 17);//17*17棋盘
		}
		if (choose == 3)
		{
			gobang.DrawMainTable(m_picDraw.GetDC(), rectPicture, 19);//19*19棋盘
		}
		

		
		CDialogEx::OnPaint();
	}


}

//开始按钮
void MainGobang::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	bIsReady = true;
	OnPaint();//参数设置完成后 再绘制棋盘
	gobang.SetPieces();
	CButton* newGame = (CButton*)GetDlgItem(IDC_BUTTON3);
	newGame->EnableWindow(FALSE);//不可用
}

//悔棋按钮
void MainGobang::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	bool bBlack;

	CDC* pDC = m_picDraw.GetDC();//获取该控件的画布
	if (bIsReady) {
		if (gobang.ClearPieces(pDC, bBlack))//清除最近一步棋子
		{
			bWithdraw = false;//只允许悔一步棋
		}
		else
		{
			MessageBox(_T("您还没有下棋！"));
		}
	}
	else {
		MessageBox(_T("请开始新的对局"));
	}
	ReleaseDC(pDC);
}



//返回首页按钮
void MainGobang::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UINT i;
	i = MessageBox(TEXT("确认要返回首页吗？"), TEXT("温馨提示"), MB_YESNO | MB_ICONQUESTION);
	if (i == IDNO)
	{
		return;
	}
	CDialogEx::OnOK();
}

void MainGobang::saveData(int x) {
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

		char insert[64];
		char a[64];
		if (x%2 == 0) {
			strcpy_s(a, "白棋胜利");
		}
		else {
			strcpy_s(a, "黑棋胜利");
		}
		int i = _ttoi(userId);
		sprintf_s(insert, "insert into g_result( result, userId ) values (\'%s\',\'%d\')",
			a,i);

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

	mysql_close(&m_sqlCon);//关闭Mysql连接  
}
//点击鼠标左键
void MainGobang::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (!bIsReady)
	{
		MessageBox(_T("请先点击开始！"));
	}
	if (bIsReady)
	{
		CRect rect;
		GetDlgItem(IDC_WAVE_DRAW)->GetWindowRect(&rect);//获取控件屏幕坐标
		CPoint pt;
		GetCursorPos(&pt);//获取鼠标点击坐标(屏幕坐标坐标)
		//该位置判断前移至此函数中
		if (rect.PtInRect(pt)) //如果鼠标在这个范围之内
		{
			pt.x -= rect.left;//转化为控件中坐标
			pt.y -= rect.top;
			CDC* pDC = m_picDraw.GetDC();//获取该控件的画布
			gobang.DrawPieces(pDC, rect, pt);//绘制棋子
			if (gobang.Success())//执行胜利判断函数
			{
				//gobang.ReplayMark(pDC);
				bIsReady = false;
				bWithdraw = false;
				CButton* newGame = (CButton*)GetDlgItem(IDC_BUTTON3);
				newGame->EnableWindow(true);//可用
				saveData(gobang.iPieces);
			}
			ReleaseDC(pDC);
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}




//改变鼠标形状
BOOL MainGobang::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPoint pos;
	GetCursorPos(&pos);  //获取当前鼠标位置
	CRect rc;
	GetDlgItem(IDC_WAVE_DRAW)->GetWindowRect(&rc);
	if (rc.PtInRect(pos)) //如果鼠标在这个范围之内
	{
		SetCursor(LoadCursor(NULL, IDC_HAND)); //设置成手状
		return TRUE;
	}
	
	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}

//设置按钮
void MainGobang::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	SettingDIg setting;
	setting.choose = this->choose;
	setting.DoModal();//显示模态对话框
	this->choose = setting.choose;
}

void MainGobang::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码

	HistoryDIg historyDIg;
	historyDIg.data = "";
	historyDIg.name = userName;
	historyDIg.id = userId;
	historyDIg.DoModal();
}
