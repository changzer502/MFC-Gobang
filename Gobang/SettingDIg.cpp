// SettingDIg.cpp: 实现文件
//

#include "pch.h"
#include "Gobang.h"
#include "SettingDIg.h"
#include "afxdialogex.h"
#include "mmsystem.h"
#include "MainGobang.h"
#pragma comment(lib,"WINMM.LIB")

// SettingDIg 对话框

IMPLEMENT_DYNAMIC(SettingDIg, CDialogEx)

SettingDIg::SettingDIg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	
}

SettingDIg::~SettingDIg()
{
}

void SettingDIg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SettingDIg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON5, &SettingDIg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &SettingDIg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON4, &SettingDIg::OnBnClickedButton4)
	ON_BN_CLICKED(IDOK, &SettingDIg::OnBnClickedOk)
END_MESSAGE_MAP()


// SettingDIg 消息处理程序
BOOL SettingDIg::OnInitDialog()
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

	

	// TODO: 在此添加额外的初始化代码
	CButton* radio1 = (CButton*)GetDlgItem(IDC_RADIO1);
	CButton* radio2 = (CButton*)GetDlgItem(IDC_RADIO2);
	CButton* radio3 = (CButton*)GetDlgItem(IDC_RADIO3);
	if (choose == 1) {
		radio1->SetCheck(1);
	}
	else if (choose == 2) {
		radio2->SetCheck(1);
	}
	else {
		radio3->SetCheck(1);
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void chooseSound(int x) {
	/*if (x == 0) PlaySound(LPWSTR(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP);
	else */
		
	if (x == 0) PlaySound(LPWSTR(IDR_WAVE2), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP);
	else if (x == 1) PlaySound(LPWSTR(IDR_WAVE3), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP);
	else if (x == 2) PlaySound(LPWSTR(IDR_WAVE4), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP);
	else if (x == 3) PlaySound(LPWSTR(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP);
}
int musicCounts = 0;
void SettingDIg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	musicCounts--;
	musicCounts = musicCounts % 4;
	chooseSound(musicCounts);
}


void SettingDIg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	musicCounts++;
	musicCounts = musicCounts % 4;
	chooseSound(musicCounts);
}

bool musicState = true;
void SettingDIg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	if (musicState) {
		PlaySound(NULL, NULL, NULL);
		CString start = _T("开启音乐");
		musicState = false;
		SetDlgItemText(IDC_BUTTON4, start);
	}
	else {
		PlaySound(LPWSTR(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP);
		CString close = _T("关闭音乐");
		musicState = true;
		SetDlgItemText(IDC_BUTTON4, close);
	}
}


void SettingDIg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码	
	
	CDialogEx::OnCancel();
	if (((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck())
	{
		choose = 1;//标准棋盘
	}
	if (((CButton*)GetDlgItem(IDC_RADIO2))->GetCheck())
	{
		choose = 2;//17*17棋盘
	}
	if (((CButton*)GetDlgItem(IDC_RADIO3))->GetCheck())
	{
		choose = 3;//19*19棋盘
	}
	str.Format(_T("%d"), choose);
	GetDlgItemText(IDD_DIALOG2, str);
	CDialogEx::OnOK();
}
