
// PhoneClientDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "ClientSocket.h"

// CPhoneClientDlg �Ի���
class CPhoneClientDlg : public CDialogEx
{
// ����
public:
	CPhoneClientDlg(CWnd* pParent = NULL);	// ��׼���캯��
	bool m_connect;
	CClientSocket* pSock;
// �Ի�������
	enum { IDD = IDD_PHONECLIENT_DIALOG };
	BOOL WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedConnect();
	CButton m_ConPC;
	afx_msg void OnBnClickedSend();
	CString m_DataSend;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
