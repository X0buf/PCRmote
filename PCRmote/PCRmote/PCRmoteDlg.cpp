
// PCRmoteDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PCRmote.h"
#include "PCRmoteDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

typedef struct
{
	char	*title;           //�б������
	int		nWidth;   //�б�Ŀ��
}COLUMNSTRUCT;

COLUMNSTRUCT g_Column_Online_Data[] =
{
	{ "IP",				148 },
	{ "Location",			150 },
	{ "Device Name",	160 },
	{ "Operating System",		128 },
	{ "CPU",			80 },
	{ "Camera",			81 },
	{ "PING",			81 }
};
int g_Column_Online_Count = 7; //�б�ĸ���
int g_Column_Online_Width = 0;  //���ܿ��

COLUMNSTRUCT g_Column_Message_Data[] =
{
	{ "Message",		68 },
	{ "Time",			100 },
	{ "Content",	    660 }
};
//��������
int g_Column_Message_Count = 3; //�б�ĸ���
int g_Column_Message_Width = 0;	//���ܿ��

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

														// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPCRmoteDlg �Ի���


CPCRmoteDlg::CPCRmoteDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPCRmoteDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPCRmoteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ONLINE, m_CList_Online);
	DDX_Control(pDX, IDC_MESSAGE, m_CList_Message);
}

BEGIN_MESSAGE_MAP(CPCRmoteDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_ONLINE, &CPCRmoteDlg::OnLvnItemchangedOnline)
	ON_NOTIFY(NM_RCLICK, IDC_ONLINE, &CPCRmoteDlg::OnNMRClickOnline)
	ON_COMMAND(IDM_ONLINE_CMD, &CPCRmoteDlg::OnOnlineCmd)
	ON_COMMAND(IDM_ONLINE_FILE, &CPCRmoteDlg::OnOnlineFile)
	ON_COMMAND(IDM_ONLINE_HANDLE, &CPCRmoteDlg::OnOnlineHandle)
	ON_COMMAND(IDM_ONLINE_MARK, &CPCRmoteDlg::OnOnlineMark)
	ON_COMMAND(IDM_ONLINE_PROCESS, &CPCRmoteDlg::OnOnlineProcess)
	ON_COMMAND(IDM_ONLINE_REGEDIT, &CPCRmoteDlg::OnOnlineRegedit)
	ON_COMMAND(IDM_ONLINE_SERVER, &CPCRmoteDlg::OnOnlineServer)
	ON_COMMAND(IDM_PROXY_SOCKET, &CPCRmoteDlg::OnProxySocket)
	ON_COMMAND(IDM_PROXY_HTTP, &CPCRmoteDlg::OnProxyHttp)
	ON_COMMAND(IDM_OTHER_SHUTDOWN, &CPCRmoteDlg::OnOtherShutdown)
	ON_COMMAND(IDM_ONLINE_VOICE, &CPCRmoteDlg::OnOnlineVoice)
	ON_COMMAND(IDM_ONLINE_VIDIO, &CPCRmoteDlg::OnOnlineVidio)
	ON_COMMAND(IDM_OTHER_RESTART, &CPCRmoteDlg::OnOtherRestart)
	ON_COMMAND(IDM_ONLINE_DELETE, &CPCRmoteDlg::OnOnlineDelete)
	ON_COMMAND(IDM_OTHER_SCREENSHOT, &CPCRmoteDlg::OnOtherScreenshot)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_MESSAGE, &CPCRmoteDlg::OnLvnItemchangedMessage)
	ON_COMMAND(ID_FILE_EXIT, &CPCRmoteDlg::OnFileExit)
	ON_COMMAND(ID_HELP_ABOUT, &CPCRmoteDlg::OnHelpAbout)
	ON_COMMAND(ID_SETTING_SERVER, &CPCRmoteDlg::OnSettingServer)
	ON_COMMAND(ID_SETTING_PARAMETER, &CPCRmoteDlg::OnSettingParameter)
END_MESSAGE_MAP()


// CPCRmoteDlg ��Ϣ�������

BOOL CPCRmoteDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	HMENU hmenu;
	hmenu = LoadMenu(NULL, MAKEINTRESOURCE(IDR_MENU_MAIN));  //����˵���Դ
	::SetMenu(this->GetSafeHwnd(), hmenu);                  //Ϊ�������ò˵�
	::DrawMenuBar(this->GetSafeHwnd());                    //��ʾ�˵�
									// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitList();  //init all list
	Test();

	CreateStatusBar();	//����״̬��

	CRect rect;
	GetWindowRect(&rect);
	rect.bottom += 20;
	MoveWindow(rect);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


void CPCRmoteDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPCRmoteDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPCRmoteDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPCRmoteDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	double dcx = cx;     //�Ի�����ܿ��
	if (m_CList_Online.m_hWnd != NULL)
	{
		CRect rc;
		rc.left = 1;       //�б��������
		rc.top = 80;       //�б��������
		rc.right = cx - 1;  //�б��������
		rc.bottom = cy - 160;  //�б��������
		m_CList_Online.MoveWindow(rc);

		for (int i = 0; i < g_Column_Online_Count; i++) {                   //����ÿһ����
			double dd = g_Column_Online_Data[i].nWidth;     //�õ���ǰ�еĿ��
			dd /= g_Column_Message_Width;                    //��һ����ǰ���ռ�ܳ��ȵļ���֮��
			dd *= dcx;                                      //��ԭ���ĳ��ȳ�����ռ�ļ���֮���õ���ǰ�Ŀ��
			int lenth = dd;                                   //ת��Ϊint ����
			m_CList_Online.SetColumnWidth(i, (lenth));        //���õ�ǰ�Ŀ��
		}
		double dcx = cx;     //�Ի�����ܿ��
	}
	if (m_CList_Message.m_hWnd != NULL)
	{
		CRect rc;
		rc.left = 1;        //�б��������
		rc.top = cy - 156;    //�б��������
		rc.right = cx - 1;    //�б��������
		rc.bottom = cy - 16;  //�б��������
		m_CList_Message.MoveWindow(rc);

		for (int i = 0; i < g_Column_Message_Count; i++) {                   //����ÿһ����
			double dd = g_Column_Message_Data[i].nWidth;     //�õ���ǰ�еĿ��
			dd /= g_Column_Message_Width;                    //��һ����ǰ���ռ�ܳ��ȵļ���֮��
			dd *= dcx;                                       //��ԭ���ĳ��ȳ�����ռ�ļ���֮���õ���ǰ�Ŀ��
			int lenth = dd;                                   //ת��Ϊint ����
			m_CList_Message.SetColumnWidth(i, (lenth));        //���õ�ǰ�Ŀ��
		}
	}


	if (m_wndStatusBar.m_hWnd != NULL) {    //���Ի����С�ı�ʱ ״̬����СҲ��֮�ı�
		CRect rc;
		rc.top = cy - 20;
		rc.left = 0;
		rc.right = cx;
		rc.bottom = cy;
		m_wndStatusBar.MoveWindow(rc);
		m_wndStatusBar.SetPaneInfo(0, m_wndStatusBar.GetItemID(0), SBPS_POPOUT, cx - 10);
	}

	// TODO: �ڴ˴������Ϣ����������
}

// init list   
int CPCRmoteDlg::InitList(void)
{
	// init online list
	m_CList_Online.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	for (int i = 0; i < g_Column_Online_Count; i++)
	{
		m_CList_Online.InsertColumn(i, g_Column_Online_Data[i].title, LVCFMT_CENTER, g_Column_Online_Data[i].nWidth);
		g_Column_Online_Width += g_Column_Online_Data[i].nWidth;        //�õ��ܿ��

	}
	m_CList_Message.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	for (int i = 0; i < g_Column_Message_Count; i++)
	{
		m_CList_Message.InsertColumn(i, g_Column_Message_Data[i].title, LVCFMT_CENTER, g_Column_Message_Data[i].nWidth);
		g_Column_Message_Width += g_Column_Message_Data[i].nWidth;

	}
	return 0;
}


void CPCRmoteDlg::OnLvnItemchangedOnline(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

//add to online list
void CPCRmoteDlg::AddList(CString strIP, CString strAddr, CString strPCName, CString strOS, CString strCPU, CString strVideo, CString strPing)
{
	m_CList_Online.InsertItem(0, strIP);           //Ĭ��Ϊ0��  �������в�������ж���������
	m_CList_Online.SetItemText(0, ONLINELIST_ADDR, strAddr);      //�����е���ʾ�ַ�   ���� ONLINELIST_ADDR�� Ϊ�ڶ��ڿ��е�ö������ �������ķ���
	m_CList_Online.SetItemText(0, ONLINELIST_COMPUTER_NAME, strPCName); //������������Ժ���չʱ�ĳ�ͻ
	m_CList_Online.SetItemText(0, ONLINELIST_OS, strOS);
	m_CList_Online.SetItemText(0, ONLINELIST_CPU, strCPU);
	m_CList_Online.SetItemText(0, ONLINELIST_VIDEO, strVideo);
	m_CList_Online.SetItemText(0, ONLINELIST_PING, strPing);
}



// Show msg to msg list
void CPCRmoteDlg::ShowMessage(bool bIsOK, CString strMsg)
{
	CString strIsOK, strTime;
	CTime t = CTime::GetCurrentTime();
	strTime = t.Format("%H:%M:%S");
	if (bIsOK)
	{
		strIsOK = "ִ�гɹ�";
	}
	else {
		strIsOK = "ִ��ʧ��";
	}
	m_CList_Message.InsertItem(0, strIsOK);
	m_CList_Message.SetItemText(0, 1, strTime);
	m_CList_Message.SetItemText(0, 2, strMsg);
}

void CPCRmoteDlg::Test(void)
{
	AddList("192.168.0.1", "����������", "Lang", "Windows7", "2.2GHZ", "��", "123232");
	AddList("192.168.0.2", "����������", "Lang", "Windows7", "2.2GHZ", "��", "123232");
	AddList("192.168.0.3", "����������", "Lang", "Windows7", "2.2GHZ", "��", "123232");
	AddList("192.168.0.4", "����������", "Lang", "Windows7", "2.2GHZ", "��", "123232");
	AddList("192.168.0.5", "����������", "Lang", "Windows7", "2.2GHZ", "��", "123232");
	ShowMessage(true, "�����ʼ���ɹ�...");
}


void CPCRmoteDlg::OnNMRClickOnline(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	//MessageBox("ok");


	CMenu	popup;
	popup.LoadMenu(IDR_MENU1);
	CMenu*	pM = popup.GetSubMenu(0);
	CPoint	p;
	GetCursorPos(&p);
	int	count = pM->GetMenuItemCount();
	//if (m_CList_Online.GetSelectedCount() == 0)       //���û��ѡ��
	//{

		//for (int i = 0; i < count; i++)
		//{
		//	pM->EnableMenuItem(i, MF_BYPOSITION | MF_DISABLED | MF_GRAYED);          //�˵�ȫ�����
		//}

	//}
	pM->TrackPopupMenu(TPM_LEFTALIGN, p.x, p.y, this);
	*pResult = 0;
}



void CPCRmoteDlg::OnOnlineCmd()
{
	// TODO: Add your command handler code here
	MessageBox("Command");
}


void CPCRmoteDlg::OnOnlineFile()
{
	// TODO: Add your command handler code here
	MessageBox("File");
}


void CPCRmoteDlg::OnOnlineHandle()
{
	// TODO: Add your command handler code here
	MessageBox("Handle");
}



void CPCRmoteDlg::OnOnlineMark()
{
	// TODO: Add your command handler code here
	MessageBox("Mark");
}


void CPCRmoteDlg::OnOnlineProcess()
{
	// TODO: Add your command handler code here
	MessageBox("process");
}


void CPCRmoteDlg::OnOnlineRegedit()
{
	// TODO: Add your command handler code here
	MessageBox("Regedit");
}


void CPCRmoteDlg::OnOnlineServer()
{
	// TODO: Add your command handler code here
	MessageBox("Server");
}


void CPCRmoteDlg::OnProxySocket()
{
	// TODO: Add your command handler code here
	MessageBox("ProxySocket");
}


void CPCRmoteDlg::OnProxyHttp()
{
	// TODO: Add your command handler code here
	MessageBox("ProxyHttp");
}


void CPCRmoteDlg::OnOtherShutdown()
{
	// TODO: Add your command handler code here
	MessageBox("Shutdown");
}


void CPCRmoteDlg::OnOnlineVoice()
{
	// TODO: Add your command handler code here
	MessageBox("Voice");
}


void CPCRmoteDlg::OnOnlineVidio()
{
	// TODO: Add your command handler code here
	MessageBox("Vidio");
}



void CPCRmoteDlg::OnOtherRestart()
{
	// TODO: Add your command handler code here
	MessageBox("Restart");
}


void CPCRmoteDlg::OnOnlineDelete()
{
	// TODO: Add your command handler code here
	MessageBox("Delete");
	CString strIP;
	int iSelect = m_CList_Online.GetSelectionMark();
	strIP = m_CList_Online.GetItemText(iSelect, ONLINELIST_IP);
	m_CList_Online.DeleteItem(iSelect);
	strIP += "    server disconnect ";
	ShowMessage(true, strIP);
}


void CPCRmoteDlg::OnOtherScreenshot()
{
	// TODO: Add your command handler code here
	MessageBox("Screenshot");
}


void CPCRmoteDlg::OnLvnItemchangedMessage(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CPCRmoteDlg::OnFileExit()
{
	// TODO: Add your command handler code here
	//PostMessage(WM_CLOSE, 0, 0);
	::PostMessage(this->m_hWnd, WM_CLOSE, 0, 0);
}


void CPCRmoteDlg::OnHelpAbout()
{
	// TODO: Add your command handler code here
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CPCRmoteDlg::OnSettingServer()
{
	// TODO: Add your command handler code here
	MessageBox("Server");
}


void CPCRmoteDlg::OnSettingParameter()
{
	// TODO: Add your command handler code here
	MessageBox("Parameter");
}


static UINT indicators[] =
{
	IDS_STRINGBAR_STRING
};


// create status bar
void CPCRmoteDlg::CreateStatusBar(void)
{
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
			sizeof(indicators) / sizeof(UINT)))                    //����״̬���������ַ���Դ��ID
	{
		TRACE0("Failed to create status bar\n");
		return;      // fail to create
	}
	CRect rc;
	::GetWindowRect(m_wndStatusBar.m_hWnd, rc);
	m_wndStatusBar.MoveWindow(rc);
}
