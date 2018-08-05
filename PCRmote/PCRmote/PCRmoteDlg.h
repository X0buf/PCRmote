
// PCRmoteDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CPCRmoteDlg �Ի���
class CPCRmoteDlg : public CDialogEx
{
// ����
public:
	CPCRmoteDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PCRMOTE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CStatusBar m_wndStatusBar;	// status bar
	int iCount = 0;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_CList_Online;
	CListCtrl m_CList_Message;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	// init list
	int InitList(void);
	afx_msg void OnLvnItemchangedOnline(NMHDR *pNMHDR, LRESULT *pResult);
	void AddList(CString strIP, CString strAddr, CString strPCName, CString strOS, CString strCPU, CString strVideo, CString strPing);
	void AddList(CString strIP);
	// Show msg to msg list
	void ShowMessage(bool bIsOK, CString strMsg);
	void Test(void);
	afx_msg void OnNMRClickOnline(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnOnlineCmd();
	afx_msg void OnOnlineFile();
	afx_msg void OnOnlineHandle();
	afx_msg void OnOnlineMark();
	afx_msg void OnOnlineProcess();
	afx_msg void OnOnlineRegedit();
	afx_msg void OnOnlineServer();
	afx_msg void OnProxySocket();
	afx_msg void OnProxyHttp();
	afx_msg void OnOtherShutdown();
	afx_msg void OnOnlineVoice();
	afx_msg void OnOnlineVidio();
	afx_msg void OnOtherRestart();
	afx_msg void OnOnlineDelete();
	afx_msg void OnOtherScreenshot();
	afx_msg void OnLvnItemchangedMessage(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnFileExit();
	afx_msg void OnHelpAbout();
	afx_msg void OnSettingServer();
	afx_msg void OnSettingParameter();
	// create status bar
	void CreateStatusBar();
};
