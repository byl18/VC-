
// Draw_starrynightDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CDraw_starrynightDlg �Ի���
class CDraw_starrynightDlg : public CDialogEx
{
// ����
public:
	CDraw_starrynightDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DRAW_STARRYNIGHT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CScrollBar m_scrollbar1;
	CEdit m_disinfo;
	int ChangeDisplayInfo(int pos);
//	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedButton5();
	CEdit m_disinfo2;
	CScrollBar m_scrollbar2;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	int ChangeDisplayInfo2(int pos2);
	CEdit m_disinfo3;
	int ChangeDisplayInfo3(int pos3);
	CScrollBar m_scrollbar3;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
