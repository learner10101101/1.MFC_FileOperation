// MyFileDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyFileDemo.h"
#include "MyFileDemoDlg.h"

#include "shlwapi.h"//ʹ��PathIsDirectory������Ҫ�õ���ͷ�ļ�
#pragma comment(lib,"shlwapi.lib")//ʹ��PathIsDirectory������Ҫ�õ���ͷ�ļ�

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyFileDemoDlg dialog

CMyFileDemoDlg::CMyFileDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyFileDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyFileDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyFileDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyFileDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyFileDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CMyFileDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_READFILEPATH, OnBtnReadfilepath)
	ON_BN_CLICKED(IDC_BTN_SELECTMOREFILE, OnBtnSelectmorefile)
	ON_BN_CLICKED(IDC_BTN_READCSVFILE, OnBtnReadcsvfile)
	ON_BN_CLICKED(IDC_BTN_WRITECSVFILE, OnBtnWritecsvfile)
	ON_BN_CLICKED(IDC_BTN_READCFGFILE, OnBtnReadcfgfile)
	ON_BN_CLICKED(IDC_BTN_WRITECFGFILE, OnBtnWritecfgfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyFileDemoDlg message handlers

BOOL CMyFileDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyFileDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyFileDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyFileDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMyFileDemoDlg::OnBtnReadfilepath() 
{
	// TODO: Add your control notification handler code here
	//@lsjע�ͣ�����ָ���ļ���·�����ļ���
	TCHAR   sDrive[_MAX_DRIVE]; 
	TCHAR   sDir[_MAX_DIR]; 
	TCHAR   sFilename[_MAX_FNAME],Filename[_MAX_FNAME]; 
	TCHAR   sExt[_MAX_EXT]; 
	TCHAR   szFilePath[MAX_PATH + 1]={0}; 
	GetModuleFileName(AfxGetInstanceHandle(), Filename, MAX_PATH);//@lsj:��ȡexe�ļ�����ȫ·����
	_tsplitpath(Filename,   sDrive,   sDir,   sFilename,   sExt);//�з�Filename���̷����м�·�����ļ������ļ���չ��׺


	/*
	//����:��ȡ(Filename,   sDrive,   sDir,   sFilename,   sExt)����
	AfxMessageBox(Filename);
	CString str1;
	str1.Format("%s%s,%s%s","sDrive==",sDrive,"sDir==",sDir);
	AfxMessageBox(str1);
	str1.Format("%s%s,%s%s","sFilename==",sFilename,"sExt==",sExt);
	AfxMessageBox(str1);
	*/


	/*
	//��ȡ�ļ���
	//��ʽ1������char * + strrchr()
	char *filename1;
	filename1=strrchr(Filename, '\\');
	filename1++;//����Ѱ�ҵ��ַ�
	AfxMessageBox(filename1);
	CString str2;
	str2.Format("%s",filename1);//��char *ת����CString����
	AfxMessageBox(str2);
	//��ʽ1������cstring + ReverseFind
	CString str3;
	str3=Filename;
	int i=str3.ReverseFind('\\');
	int j=str3.ReverseFind('.');
	int length=str3.GetLength();//ͨ��debug,��֪GetLength()���������ַ����ĳ��Ȱ������ַ���������ֹ��
	CString  filename2= str3.Mid(i+1,length);//length���ȳ�����Ҫ�ַ����ĳ��ȼ��ɣ���Ϊ�����ַ���������ֹ����ֹͣ��ȡ�ַ��������ں��ַ�������
	AfxMessageBox(str3);
	*/


	
	
	

	//����.EXE�����ļ��е��Զ����ֵ��ļ���
	//1.ƴ���Զ����ֵ��ļ���·��
	(strrchr(sDir, '\\'))[0] = 0;//���ַ����ұߵ�һ����/���滻��0��0Ϊ�ַ���������־�������ض���sDir�ַ���
	(strrchr(sDir, '\\'))[0] = 0; //ʹ��������strrchr����ԭ�ַ�����δ���ضϵ��ַ������ұߵڶ�����/���滻��0��0Ϊ�ַ���������־�������ض���sDir�ַ���
	CString  homeDir(CString(sDrive)  +  CString(sDir) );
	CString szFullFileName = homeDir + "\\MotionData";
	//2.�������ļ��У�ʹ��CreateDirectory�����ļ��б��뱣֤��һ���ļ��д��ڣ�
	/*
	�ڴ����µ�Ŀ¼֮ǰ������Ҳ�������жϸ�Ŀ¼�Ƿ��Ѿ����ڣ����磺
	
	  CString str = "D:\\һ���ļ���";
	  if (!PathIsDirectory(str))
	  {
	  ::CreateDirectory(str, NULL);//����Ŀ¼,���еĻ���Ӱ��
	  }
	  str += "\\�����ļ���";
	  if (!PathIsDirectory(str))
	  {
	  ::CreateDirectory(str, NULL);//����Ŀ¼,���еĻ���Ӱ��
	  }
	  �ڵ���PathIsDirectory()����ʱ����Ҫ��������ͷ�ļ���⺯��
	  #include "shlwapi.h"
	  #pragma comment(lib,"shlwapi.lib")

	*/
	CreateDirectory(szFullFileName, NULL);
	CString m_szDataPathName = szFullFileName;
	CString str4;
	str4.Format("�ļ���·����������ϣ��������ļ�·��Ϊ��%s",m_szDataPathName);
	AfxMessageBox(str4);
	
}

void CMyFileDemoDlg::OnBtnSelectmorefile() 
{
	// TODO: Add your control notification handler code here
	
	/*//����˵��
	CFileDialog	dlgChooseFile(FALSE,//  ��һ��������ʾ���챣��(FALSE)�Ի�����ߴ�(TURE)�Ի���
		"csv", //���ڶ������ļ���չ��
		(LPCTSTR)szTimeStamp,  //  �������ǳ�ʼ�ļ���
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,//�����ĸ������Կ�(ǰ��������ֻ������������ʾ�Ƿ񸲸�)
		"Data Files (*.csv)|*.csv||");  //  ��������ļ������������ϴ˸�ʽ���ļ��Ż�������ļ��б��� 
	*/

     
	//��ѡ�ļ�
	/*
	Ҫ�����û�ѡ�����ļ������ڵ���DoModal֮ǰ����OFN_ALLOWMULTISELECT��־�� 
	����Ҫ�ṩ�Լ����ļ��������������ɷ��صĶ���ļ����б� Ϊ�ˣ��ڹ���CFileDialog֮���ڵ���DoModal֮ǰ��
	��ָ��������Ļ�������ָ���滻m_ofn.lpstrFile��
	*/
	CFileDialog   dlg( TRUE, NULL, NULL, OFN_ALLOWMULTISELECT, NULL, NULL );
	DWORD MAXFILE = 2562; //2562 is the max//���Ķ�ѡ�ļ���
	TCHAR* pc = new TCHAR[MAXFILE * MAX_PATH];//���Ķ�ѡ�ļ�����ռ���ڴ��С(���������+1�޹ؽ�Ҫ����Ϊ������ַ�����ֹ���ĳ��ȼ���)
	pc[0] = NULL;//lpstrFile�ĵ�һ���ֽ�Ҫ��NULL��ע�͸��У����벻���������޷�����
	dlg.m_ofn.nMaxFile = MAXFILE * MAX_PATH;//nMaxFile���Ķ�ѡ�ļ�����ռ���ڴ�
	dlg.m_ofn.lpstrFile = pc;//lpstrFileָ�����Ķ�ѡ�ļ�����ռ���ڴ�
	
	int iReturn = dlg.DoModal();
	if(iReturn ==  IDOK)
	{
		int nCount = 0;
		POSITION pos = dlg.GetStartPosition();
		while (pos != NULL)
		{
			CString szPathName = dlg.GetNextPathName(pos);//��ѡ�ļ�ʱ���ļ�˳���ǰ��Ի�����ʾ��˳����ϵ�������ģ������ļ�λ�û�ȡ�ļ���
			TRACE( _T("%s\n"), szPathName);
			nCount++;
		}
		CString str;
		str.Format("Successfully opened %d files", nCount);
		AfxMessageBox(str);
	}
	else if(iReturn == IDCANCEL)
		AfxMessageBox("Cancel");
	
   delete []pc;
	
}

//д���csv�ļ��ġ�������ռ1���ֽڣ����ŷָ����͡�\n��(�ı���ʽд�룬�ᱻд�ɡ�\n\r��ռ2���ֽ�)���з�����Щ�ǲ��ɼ��ķ��ţ�������Excel��CSV�ļ�ʱ������ɾ���ɼ��ַ����հ�λ�ò�ռ�ֽڣ����޷�ɾ�����ɼ��ַ�
//CSV�ļ��еĿ��ַ�����file.ReadString(strRead)����ʱstrRead��ʱ���ᱻ��Ϊ���ַ�������xx,,(�����ܽ�,,���룬����Ϊ�����������š�\n��������)������δ��ֵ������ֵд��csv�ļ��ǣ���д��Ĭ�ϳ�ʼ��ֵ0.��ע�⣬debug��release��Ĭ�ϳ�ʼֵ��һ����debug����ֵ�������Ĭ�ϳ�ʼֵ��Ϊ�㣩
void CMyFileDemoDlg::OnBtnReadcsvfile()//��ȡcsv�ļ���ע���һ�б��������������Ʋ������ݣ����CSV�ļ�������һ�£�rowsindex��¼������������,colsindex�������� 
{
	// TODO: Add your control notification handler code here
	//���ļ��Ի���ѡ�񵥸���Ҫ��ȡ��csv�ļ�
   	CString szFullFileName;
	char* filters = _T("HJMC RT-Scope Files (*.csv)|*.csv||");
	
	CFileDialog fileDlg(true, "*csv", NULL, OFN_HIDEREADONLY | OFN_HIDEREADONLY, filters);
	
	if (fileDlg.DoModal() != IDOK) {
		return;
	}
	
	//��ȡѡ���ļ�ȫ·��������һ��CStdioFile������ֻ����ʽ���ļ�
	szFullFileName = fileDlg.GetPathName();
	CStdioFile file;	
	if (!file.Open(szFullFileName, CFile::modeRead | CFile::typeText))//����·����ֻ����ʽ���ļ�
	{
		AfxMessageBox(_T("�ļ���ʧ�ܣ������ļ��Ƿ��Ѿ�����!"));
		return;
	}
	
	
	//��ȡ�ļ����ݵ��㷨
	UINT FileRows=10000,FileCols=10000;//������ļ������ݵ���������������,���ļ���ʵ������������������Ϳ�����(FileRows=csv�����������-1(�����б���ռһ��)-1�������0��ʼ���㣩;FileCols=csv�����������-1�������0��ʼ���㣩)
	UINT SelectColumn1=0,SelectColumn2=1,SelectColumn3=2;//ѡ����Ҫ��ȡ��������
//	double Column1[10000], Column2[10000], Column3[10000];//��ȡ�����б��������(ʹ�ó�Ա����������д���ļ�ʱʹ��)
	int NumCount1 = 0, NumCount2 = 0,NumCount3=0;
	
	UINT fileLength = file.GetLength();//�ĵ����ܵ��ֽ���
	UINT curPos = 0;
	float  value = 0.0;
	CString strRead = _T("");
	
	UINT  rows = 0, cols = 0;
	UINT  rowsindex = 0, colsindex = 0;//��¼�ļ���������������������(�Ƴ����ú������棬��Ϊȫ�ֺ���������д�뺯������)
				
	BOOL IsEndBigWhile = FALSE;//@lsj20201201
	while (IsEndBigWhile == FALSE && curPos < fileLength)//���������׼ȷ��,���Ա�֤�������һ�����ݾͽ�����ȡ
	{
		file.ReadString(strRead);//���ж�ȡ���ݣ���Ϊ����д��ʱ����ʹ���ˡ�\n�����л��еģ�
		rowsindex++;//�����˵ڼ������ݣ�index==1��˵�������˵�һ������
		curPos += strRead.GetLength() + 2;//�ı��ļ�д�롰/n���󣬳���Ӳ��д�롰/n/r��ռ�������ֽڣ����������2�����Խ�����֤��
		
		strRead.TrimLeft(_T(" "));//����û�в���������µ���ʱ��TrimLeftɾ���ַ�����ߵĻ��з����ո��tab�ַ�������ֻ������ո��
		strRead.TrimRight(_T(" "));//����û�в���������µ���ʱ��TrimLeftɾ���ַ����ұߵĻ��з����ո��tab�ַ�������ֻ������ո��
		//TrimRight�����������ǣ����ַ�����߿������������г��ֵ��ַ���������ȫ����ȥ��ֱ�����ֵ�һ��������δ���ֵ��ַ�ʱֹͣ�س�����ʹ�����ֳ����˲������е��ַ�Ҳ�����ȥ�ˡ�
		strRead.TrimRight(_T(","));//TrimRight��TrimLeft�����������strRead���������õġ�,�����ţ����㴦�����ݣ�ʹ���������У�if (!strRead.IsEmpty() && -1 == strRead.Find(_T(",")))��

		
		if (strRead.IsEmpty())//�����������Ϊ�գ�����˵����û�����ݣ��Ͳ��ý�������while�����������ݳ��������
		{
			continue;
		}
		
		if (rowsindex > 1)//�˴�������������(��Ϊ��һ���������е����ƣ��������ݣ������һ��Ҳ�����ݣ���˴���Ҫ�޸ģ�)
		{
			//while����һ������
			BOOL LineOverFlag=FALSE;
			while (LineOverFlag == FALSE)//�жϸ����Ƿ������Ѿ�������(ֻ��-1 != strRead.Find(_T(","))һ���������жϸ������ݶ�ȡ��ϣ���һ��bug�����һ�������Ǳ����Եģ���Ϊ���һ������û�С�����������)
			{
				CString strTemp;
				//�ж��Ƿ�Ϊ���е����һ�У��������ݣ����һ�У��������ݵ�ֵ����ֱ�ӻ�ȡ
				if (!strRead.IsEmpty() && -1 == strRead.Find(_T(",")))//���ضϵ�strRead��Ϊ�գ����Ҳ�����������־����˵���������������һ��������(bug:��ad,cd,ef,gg,,,,���������������ʧЧ,�����ʽ��ʹ��	strRead.TrimRight(_T(","));����Ҳ�ġ�,�����ţ������ȡ���ַ�Ϊ��54,,,��,�����ó����䡰��)
				{
					LineOverFlag=TRUE;
					strTemp = strRead;
					value = atof(strRead);
				}
				
				else
				{
//					CString strTemp;
					UINT index1 = strRead.Find(_T(","));
					strTemp = strRead.Left(index1);//�����ݴ洢������strTemp��
					
					strRead = strRead.Right(strRead.GetLength() - strTemp.GetLength()-1);//��ȡ��û�б������������ݱ��浽strRead�����ض�strRead,-1��Ϊ��ɾ�������ġ�,��
					
					value = atof(strTemp);//��CString���ݾ�ת��Ϊfloat���͵�value������     CStringת��Ϊfloat��_tstof

				}
				
				
				if (rows <=FileRows && cols <= FileCols)//��ȡѡ��������б���������У�FileRows��FileCols����Ҫ��ǰ֪����ֻҪ��֤��Ҫ��ȡ���ļ�����������Ϳ����ˣ���FileRows��FileColsֵ���㹻�󼴿ɣ�
				{
					if (cols == SelectColumn1)//�Ը��е�����Ϊ��׼��ȡ����
					{
						
						if (strTemp=="")//@lsj20201201:���X�����ݶ����˵ף���CSV�ж����˿յ�Ԫ�񣩣���ʾ����XY���ݶ�ȡ����ˣ�����Y�Ƿ������ݣ����ԣ�X��������Ӧ��Y�����ݳ������������Y�Ŀյ�Ԫ�����ɿ��ַ�����ת������ֵΪ0��
						{
							LineOverFlag = TRUE;
							IsEndBigWhile = TRUE;
							rowsindex--;
							break;
							
						}
						Column1[NumCount1++] = value;
						TRACE("%f,",value);

					}
						
					
					else if(cols == SelectColumn2)	
					{
						Column2[NumCount2++] = value;
						TRACE("%f,",value);

					}
						
					else if(cols == SelectColumn3)	
					{
						Column3[NumCount3++] = value;
						TRACE("%f\n",value);

					}
											
					cols++;	

				}
			}
			
			rows++;//�ƽ�����
			if (cols>colsindex)
			{
				colsindex=cols;//��¼�ļ��������
			}
			
			cols = 0;//��������

			colsMax=colsindex;
			rowsMax=rowsindex;//ָ��X�����е��������������ļ�����������ˣ�
		}
	}



	CString ceshi;
	ceshi.Format("�ļ���ȡ��ϣ�rowsindex==%d,colsindex==%d",rowsindex,colsindex);
	AfxMessageBox(ceshi);
	
	file.Close();
	
}

void CMyFileDemoDlg::OnBtnWritecsvfile() //����ȡ�ļ���ť��ȡ���ļ����ݱ��������ColumnN[]д�뵽ָ���ļ���D:\\DebugInfo\\SweepAnalyzeResult\\%Y%m%d-%H%M%S.csv�ļ���
{
	// TODO: Add your control notification handler code here
	//ȷ���������ݵ��ļ�ȫ·������
	//1.ȷ��·��
	CString m_szDataPathName = "D:\\DebugInfo\\SweepAnalyzeResult\\";//@lsj20201010:���뱣֤���·���е��ļ��д��ڣ���������޷������ڸ�·���ϵ��ļ�
	//add by @lsj20201010:���û�д���D:\\DebugInfo\\SweepAnalyzeResult�ļ��У��򴴽����ڱ���prbs�Ľ������
	CString szFolder = "D:\\DebugInfo";//���һ���ļ��в����ڣ��򴴽�
	if (!PathIsDirectory(szFolder))
	{
		::CreateDirectory(szFolder, NULL);	
	}
	
	szFolder += "\\SweepAnalyzeResult";//��������ļ��в����ڣ��򴴽�
	if (!PathIsDirectory(szFolder))
	{
		::CreateDirectory(szFolder, NULL);	
	}
	
	//2.ȷ���ļ����ƣ���ʱ�����
	CTime tmStart = CTime::GetCurrentTime();
	m_szDataPathName += tmStart.Format("%Y%m%d-%H%M%S");
	m_szDataPathName += _T(".csv");
	
	//����ȫ·�����ƴ����ļ���д������
	CStdioFile  OutPutFile;
	
	if (!OutPutFile.Open(m_szDataPathName, CFile::modeCreate | CFile::modeWrite))
	{
		AfxMessageBox("���ļ�ʧ�ܣ�д���������ִ��");
		return;
	}
	
	//д���ݵ��ļ�������ʹ�ö��Ž����ݸ���������Ϊ���ļ�����ĸ�ʽ�Ƕ��ŷָ��ļ������Է���ת����Excel�ļ�����txt�ļ���
	//д��һ�е�CSV�ļ�����һ�������ݱ���
	CString strLine;
	strLine = _T("Hz");
	strLine += _T(",");
	strLine += _T("dB"); 
	strLine += _T(",");
	strLine += _T("Degree");
	strLine += '\n';
	OutPutFile.WriteString(strLine);
	
	
	//д���ݵ�CSV�ļ���һ��һ�е�д���˴�ֻд�����У�
	for (int i = 0; i < rowsMax-1; i++)
	{
		CString DataColumn1, DataColumn2,  DataColumn3;
		DataColumn1.Format(_T("%.4f"), Column1[i]);
		DataColumn2.Format(_T("%.4f"), Column2[i]);
		DataColumn3.Format(_T("%.4f"), Column3[i]);
		strLine = DataColumn1 + ',' + DataColumn2 + ',' + DataColumn3 + '\n';
		OutPutFile.WriteString(strLine);
	}
	
	
	AfxMessageBox("����д�����,�����ļ���·��Ϊ��D:\\DebugInfo\\SweepAnalyzeResult");
	
	OutPutFile.Close();
	
}


//��ȡ���������ļ�(��(or���)����=<��ֵ>)�ļ�ֵ
//1. ��һ��������һ�еļ�ֵ
BOOL  CMyFileDemoDlg::FileParaReadGivenFilePath1(CString sflag,double *ddata,CString szFilePathName)//��ȡMFSCFileNmPth�����ļ���sToFindflagDynAmp��������ȡ��ֵ<>�е����ݱ��浽&ddataDynX[0]�У��ú���ֻ��һ��������һ�еļ�ֵ��
{    
    CStdioFile fout;
    BOOL bRtn = fout.Open(szFilePathName, CFile::modeRead | CFile::typeText);
    if(!bRtn)
    {
        AfxMessageBox(_T("No this par file exist!"));    
        return     FALSE;
    }
    CString ss;//һ�е��ַ���
    CString LineData;
    int nbgn,nlgth;//
    int kk=0;
    int nIdxLine;
    int dd=0; //ddΪ�ļ���ȡ���ݵ�λ�ã���ʵ��û��ʲô��λ��ָʾ�����ã����Ǳ�ʾ�ҵ��˶��������Խ���if( dd!=0 )�Ĵ�����������ø�nsflagExistһ��
    int nsflagExist=0; //nsflagExist==1˵���ҵ��˽������߶�����sflag�� 
start:
    while(fout.ReadString(ss))//@lsjע��:ReadString��������һ�����з�ʱֹͣ��ȡ,��һ��ֻ��һ���ַ�����������һ���ַ���û��ʹ�û��з�����д��ȥ��
	{    
		if (ss.Find("#")==0 ) //bypass the line with '#' start
            goto start;////�����ԡ�#�����ſ�ʼ���� 
		if( dd!=0 )
		{       
			int nIdxData = ss.Find("<");
			int nDeliminator = ss.FindOneOf(","); // delimenator is comma, PHP; 
			int nEndCnter = ss.Find(">");
			nbgn =  nIdxData+1;
			nlgth=  nDeliminator-nIdxData-1;
			while ( nlgth != - 1 ) // if can find comma, will continue this loop;
			{
				ddata[kk] = atof( ss.Mid(nbgn,nlgth) ) ;
				kk=kk+1;
				LineData = ss.Mid(nbgn+nlgth+1, ss.Find(">") - (nbgn+ nlgth));//<>���еĽض�ʽȡ��ֵ       
				ss = LineData;
				
				//�ж��Ƿ������<>�е����һ��ֵnbgn=-1��˵�����������һ��ֵ������while ( nlgth != - 1 )ѭ��
				nbgn = 0;
				if ( ss.FindOneOf(",") !=-1 )
					nlgth = ss.FindOneOf(",") - nbgn ;
				else 
					nlgth = ss.Find(">") - nbgn; // the last value ��nlgth=-1-0=-1
			}
			
		}
		
		nIdxLine = ss.Find( sflag);
		
		if( nIdxLine==0){ //find the value;
			dd=fout.GetPosition(); //ddΪ�ļ���ȡ���ݵ�λ�ã���ʵ��û��ʲô��λ��ָʾ�����ã����Ǳ�ʾ�ҵ��˶��������Խ���if( dd!=0 )�Ĵ�����������ø�nsflagExistһ��
			nsflagExist = 1;//nsflagExist==1˵���ҵ��˽������߶�����sflag��
		}
		else dd=0; 
	}
    
    fout.Close();
    if(!nsflagExist)
    {
        AfxMessageBox(_T("string to read not exist in the par file!"));    
        return     FALSE;
    }    
    else return TRUE;
    
}


//2. ��������������еļ�ֵ
BOOL  CMyFileDemoDlg::FileParaReadGivenFilePath2(CString sflag,double *ddata,CString szFilePathName,UINT CycleNum)
{    
    CStdioFile fout;
    BOOL bRtn = fout.Open(szFilePathName, CFile::modeRead | CFile::typeText);
    if(!bRtn)
    {
        AfxMessageBox(_T("No this par file exist!"));    
        return     FALSE;
    }
    CString ss;
    CString LineData;
    int nbgn,nlgth;
    int kk=0;
    int nIdxLine;
    int dd=0; //must set to zero
    int nsflagExist=0;
    int ii;
start:
    while(fout.ReadString(ss))//һ��һ�еĶ������
    {    
        if (    ss.Find("#")==0 ) //bypass the line with '#' start
            goto start;
        if( dd!=0 )//dd!=0 ˵�������˼�������
        {        
            for (ii=0; ii<CycleNum; ii++) {//ѭ�����Σ�������<>����,���浽ddata[]��
				int nIdxData = ss.Find("<");
				int nDeliminator = ss.FindOneOf(","); // delimenator is comma
				int nEndCnter = ss.Find(">");
				nbgn =  nIdxData+1;
				nlgth=  nDeliminator-nIdxData-1;
				while ( nlgth != - 1 ) // if can find comma, will continue this loop;
				{
					ddata[kk] = atof( ss.Mid(nbgn,nlgth) ) ;  // atof() ���ڽ��ַ���ת��Ϊ˫���ȸ�����(double)
					kk=kk+1;
					LineData = ss.Mid(nbgn+nlgth+1, ss.Find(">") - (nbgn+ nlgth));
					ss = LineData;
					nbgn = 0;
					if ( ss.FindOneOf(",") !=-1 )
						nlgth = ss.FindOneOf(",") - nbgn ;
					else 
						nlgth = ss.Find(">") - nbgn; // the last value
				}
				fout.ReadString(ss);//�ٶ���һ���ַ��������зֽ��ȡ��ֵ
            }
			
        }
		
        nIdxLine = ss.Find( sflag);
        if( nIdxLine==0){ //find the value;
            dd=fout.GetPosition(); 
            nsflagExist = 1;
        }
        else dd=0; 
    }
    fout.Close();
    if(!nsflagExist)
    {
        AfxMessageBox(_T("string to read not exist in the par file!"));    
        return     FALSE;
    }    
    else return TRUE;
}




void CMyFileDemoDlg::OnBtnReadcfgfile()// �����ļ�(�����ļ�ʹ��ʲô��׺)ֻҪ����һ������д��ʽ(��(or���)����=<��ֵ>)�Ϳ���ʹ����������������ȡ��ֵ
{
	// TODO: Add your control notification handler code here

	//���ļ��Ի���ѡ�񵥸���Ҫ��ȡ��cfg�ļ�
   	CString szFullFileName;
	char* filters = _T("cfg Files (*.cfg)|*.cfg|par Files (*.par)|*.par|txt Files (*.txt)|*.txt||");//�����ļ�ֻҪ����һ������д��ʽ(��(or���)����=<��ֵ>)�Ϳ���ʹ����������������ȡ��ֵ
	
	CFileDialog fileDlg(true, "*cfg", NULL, OFN_HIDEREADONLY | OFN_HIDEREADONLY, filters);
	
	if (fileDlg.DoModal() != IDOK) {
		return;
	}

	
	//�βεĳ�ʼ��
	szFullFileName = fileDlg.GetPathName();//��ȡѡ���ļ�ȫ·��
	CString  sflag;
	sflag="[OPEN_LOOPX]";//����������˵�ǽ�����
	double ddata[30];
	UINT CycleNum=3;//CycleNum��������FileParaReadGivenFilePath2��ȡ�����еļ�ֵ
//	FileParaReadGivenFilePath1(sflag,ddata,szFullFileName);//1. ��һ��������һ�еļ�ֵ
	FileParaReadGivenFilePath2(sflag,ddata,szFullFileName,CycleNum);//2. ��������������еļ�ֵ��CycleNum����������ȡ�����еļ�ֵ������˵��ȡ���ٸ�����
	
}

void CMyFileDemoDlg::OnBtnWritecfgfile() //�޸�ĳ��������ĳ�����ļ�ֵ
{
	// TODO: Add your control notification handler code here
	//1.ͨ�������ͼ�����λ����Ҫ�޸ĵ���
	//2.�����ַ������ж���Ҫ�޸����ݵ�λ��
	//3.����Ҫ�޸ĵļ�ֵ�����ַ��滻����һ���������ģ�����Ҫ�滻�ַ��ĳ������滻�ַ��ĳ���һ�£������滻�޷����У�
	
}
