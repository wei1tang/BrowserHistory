
// BrowserHistoryDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BrowserHistory.h"
#include "BrowserHistoryDlg.h"
#include "afxdialogex.h"

//#include "stdafx.h"  
#include <vector>  
#include <iostream>  
#include "afxwin.h"  
#include "BrowserAlgorithm.h"
#include <fstream>  

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBrowserHistoryDlg 对话框



CBrowserHistoryDlg::CBrowserHistoryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BROWSERHISTORY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBrowserHistoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}

BEGIN_MESSAGE_MAP(CBrowserHistoryDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CBrowserHistoryDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CBrowserHistoryDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CBrowserHistoryDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CBrowserHistoryDlg 消息处理程序

BOOL CBrowserHistoryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	CRect rectTemp;
	GetDlgItem(IDC_LIST1)->GetWindowRect(rectTemp);
	int columnWidth = (rectTemp.right - rectTemp.left) / 3;

	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListCtrl.InsertColumn(0, _T("序号"), LVCFMT_LEFT, columnWidth);        // 插入第1列的列名  
	m_ListCtrl.InsertColumn(1, _T("网址"), LVCFMT_LEFT, columnWidth);        // 插入第2列的列名  
	m_ListCtrl.InsertColumn(2, _T("时间"), LVCFMT_LEFT, columnWidth);        // 插入第3列的列名  
	
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CBrowserHistoryDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBrowserHistoryDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBrowserHistoryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBrowserHistoryDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	BrowsHistory browseHistory;
	browseHistory.Init();
	while (!browseHistory.m_bStatus);//等待获取完成  
	std::vector<BrowsData> data = browseHistory.GetBrowsHistory();
	std::vector<BrowsData>::iterator it = data.begin();

	int orderNumber = 1;
	CString stringNumber;
	CString txt;
	CString tmpStr;
	CString time;
	CString year;
	CString month;
	CString day;
	CString hour;
	CString minute;
	CString second;

	
	CStdioFile File;
	File.Open(_T("E:\\out.txt"),CFile::modeReadWrite | CFile::modeNoTruncate | CFile::modeCreate);
	File.SetLength(0);
	File.SeekToEnd();
	
	for (; it<data.end(); ++it)
	{
		wprintf(_T("%s\n"), it->strURL);
		stringNumber.Format(_T("%d"), orderNumber);
		tmpStr = stringNumber + ' ' + ' ' + ' ' + it->strURL;
		year.Format(_T("%d"), it->year); 
		month.Format(_T("%d"), it->month);
		day.Format(_T("%d"), it->day);
		hour.Format(_T("%d"), it->hour);
		minute.Format(_T("%d"), it->minute);
		second.Format(_T("%d"), it->second);
		time = year + '/' + month + '/' + day + ' ' + hour + ':' + minute + ':' + second + ' ';
		txt = txt+ tmpStr + ' ' + ' ' + ' ' + ' ' + ' ' + ' ' + ' ' + ' ' + ' ' + time +'\r'+'\n' ;
		//SetDlgItemText(IDC_EDIT1, txt);

		m_ListCtrl.InsertItem(orderNumber-1, _T(""));                          // 插入行  
		m_ListCtrl.SetItemText(orderNumber-1, 0, stringNumber);                     // 设置第1列(序号)  
		m_ListCtrl.SetItemText(orderNumber-1, 1, it->strURL);                     // 设置第2列(网址)  
		m_ListCtrl.SetItemText(orderNumber-1, 2, time);                     // 设置第3列(时间)  

		orderNumber++;
	}

	File.WriteString(txt);
	File.Close();
}


void CBrowserHistoryDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
