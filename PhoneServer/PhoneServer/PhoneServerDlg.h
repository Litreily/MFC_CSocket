
// PhoneServerDlg.h : ͷ�ļ�
//

#pragma once
#include "ServerSocket.h"
#include "afxwin.h"
class CServerSocket;
// CPhoneServerDlg �Ի���
class CPhoneServerDlg : public CDialogEx
{
// ����
public:
	CPhoneServerDlg(CWnd* pParent = NULL);	// ��׼���캯��
	CServerSocket* listenSocket;			// ���ڴ򿪷�����
	CPtrList m_clientList;					// �������ڴ洢�û�
	bool m_connect;							
	void AddClient();						// �����û�����Ӧ�û�����
	void RemoveClient(CServerSocket* pSocket);	// �Ƴ����ߵ��û�
	void RecvData(CServerSocket* pSocket);		// ��ȡ����
	void UpdateEvent(CString str);				// �����¼���־
	BOOL WChar2MByte(LPCWSTR srcBuff, LPSTR destBuff, int nlen);	//�ַ�ת��
	void SendMSG(CString str);					// ������Ϣ�������ͻ���
	void ControlPC(CString AndroidControl);		// �ֻ�����PC����Ӧ����
// �Ի�������
	enum { IDD = IDD_PHONESERVER_DIALOG };

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
	afx_msg void OnBnClickedStartserver();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	UINT m_port;
	CEdit m_event;
	UINT m_userCount;
	afx_msg void OnClose();
};
