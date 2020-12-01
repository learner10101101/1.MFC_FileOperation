// MyFileDemoDlg.h : header file
//

#if !defined(AFX_MYFILEDEMODLG_H__A4C16902_62B6_44ED_B2D5_3EB502E21098__INCLUDED_)
#define AFX_MYFILEDEMODLG_H__A4C16902_62B6_44ED_B2D5_3EB502E21098__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyFileDemoDlg dialog

class CMyFileDemoDlg : public CDialog
{
// Construction
public:
	UINT  rowsMax , colsMax ;//记录文件真正的总行数和总列数
	double Column1[10000], Column2[10000], Column3[10000];


	BOOL  FileParaReadGivenFilePath1(CString sflag,double *ddata,CString szFilePathName);//读取MFSCFileNmPth配置文件中sToFindflagDynAmp节名，获取键值<>中的数据保存到&ddataDynX[0]中（该函数只读一个键，即一行的键值）
	BOOL  FileParaReadGivenFilePath2(CString sflag,double *ddata,CString szFilePathName,UINT CycleNum);


	CMyFileDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMyFileDemoDlg)
	enum { IDD = IDD_MYFILEDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyFileDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyFileDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnReadfilepath();
	afx_msg void OnBtnSelectmorefile();
	afx_msg void OnBtnReadcsvfile();
	afx_msg void OnBtnWritecsvfile();
	afx_msg void OnBtnReadcfgfile();
	afx_msg void OnBtnWritecfgfile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYFILEDEMODLG_H__A4C16902_62B6_44ED_B2D5_3EB502E21098__INCLUDED_)
