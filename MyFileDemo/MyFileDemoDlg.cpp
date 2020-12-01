// MyFileDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyFileDemo.h"
#include "MyFileDemoDlg.h"

#include "shlwapi.h"//使用PathIsDirectory函数需要用到的头文件
#pragma comment(lib,"shlwapi.lib")//使用PathIsDirectory函数需要用到的头文件

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
	//@lsj注释：创建指定文件夹路径及文件名
	TCHAR   sDrive[_MAX_DRIVE]; 
	TCHAR   sDir[_MAX_DIR]; 
	TCHAR   sFilename[_MAX_FNAME],Filename[_MAX_FNAME]; 
	TCHAR   sExt[_MAX_EXT]; 
	TCHAR   szFilePath[MAX_PATH + 1]={0}; 
	GetModuleFileName(AfxGetInstanceHandle(), Filename, MAX_PATH);//@lsj:获取exe文件所在全路径名
	_tsplitpath(Filename,   sDrive,   sDir,   sFilename,   sExt);//切分Filename成盘符，中间路径，文件名，文件扩展后缀


	/*
	//测试:获取(Filename,   sDrive,   sDir,   sFilename,   sExt)含义
	AfxMessageBox(Filename);
	CString str1;
	str1.Format("%s%s,%s%s","sDrive==",sDrive,"sDir==",sDir);
	AfxMessageBox(str1);
	str1.Format("%s%s,%s%s","sFilename==",sFilename,"sExt==",sExt);
	AfxMessageBox(str1);
	*/


	/*
	//获取文件名
	//方式1：采用char * + strrchr()
	char *filename1;
	filename1=strrchr(Filename, '\\');
	filename1++;//消除寻找的字符
	AfxMessageBox(filename1);
	CString str2;
	str2.Format("%s",filename1);//将char *转换成CString类型
	AfxMessageBox(str2);
	//方式1：采用cstring + ReverseFind
	CString str3;
	str3=Filename;
	int i=str3.ReverseFind('\\');
	int j=str3.ReverseFind('.');
	int length=str3.GetLength();//通过debug,可知GetLength()函数计算字符串的长度包括了字符串结束终止符
	CString  filename2= str3.Mid(i+1,length);//length长度超过想要字符串的长度即可，因为遇到字符串结束终止符就停止截取字符串，不在乎字符串长度
	AfxMessageBox(str3);
	*/


	
	
	

	//创建.EXE所在文件夹的自定义兄弟文件夹
	//1.拼接自定义兄弟文件夹路径
	(strrchr(sDir, '\\'))[0] = 0;//将字符串右边第一个“/”替换成0，0为字符串结束标志符，即截断了sDir字符串
	(strrchr(sDir, '\\'))[0] = 0; //使用了两次strrchr，将原字符串（未被截断的字符串）右边第二个“/”替换成0，0为字符串结束标志符，即截断了sDir字符串
	CString  homeDir(CString(sDrive)  +  CString(sDir) );
	CString szFullFileName = homeDir + "\\MotionData";
	//2.创建该文件夹（使用CreateDirectory创建文件夹必须保证上一级文件夹存在）
	/*
	在创建新的目录之前，我们也可以先判断该目录是否已经存在，例如：
	
	  CString str = "D:\\一级文件夹";
	  if (!PathIsDirectory(str))
	  {
	  ::CreateDirectory(str, NULL);//创建目录,已有的话不影响
	  }
	  str += "\\二级文件夹";
	  if (!PathIsDirectory(str))
	  {
	  ::CreateDirectory(str, NULL);//创建目录,已有的话不影响
	  }
	  在调用PathIsDirectory()函数时，需要包含以下头文件与库函数
	  #include "shlwapi.h"
	  #pragma comment(lib,"shlwapi.lib")

	*/
	CreateDirectory(szFullFileName, NULL);
	CString m_szDataPathName = szFullFileName;
	CString str4;
	str4.Format("文件（路径）创建完毕，创建的文件路径为：%s",m_szDataPathName);
	AfxMessageBox(str4);
	
}

void CMyFileDemoDlg::OnBtnSelectmorefile() 
{
	// TODO: Add your control notification handler code here
	
	/*//函数说明
	CFileDialog	dlgChooseFile(FALSE,//  第一个参数表示构造保存(FALSE)对话框或者打开(TURE)对话框
		"csv", //，第二个是文件扩展名
		(LPCTSTR)szTimeStamp,  //  第三个是初始文件名
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,//，第四个是属性框(前者是隐藏只读，后者是提示是否覆盖)
		"Data Files (*.csv)|*.csv||");  //  第五个是文件过滤器，符合此格式的文件才会出现在文件列表中 
	*/

     
	//多选文件
	/*
	要允许用户选择多个文件，请在调用DoModal之前设置OFN_ALLOWMULTISELECT标志。 
	您需要提供自己的文件名缓冲区以容纳返回的多个文件名列表。 为此，在构造CFileDialog之后但在调用DoModal之前，
	用指向您分配的缓冲区的指针替换m_ofn.lpstrFile。
	*/
	CFileDialog   dlg( TRUE, NULL, NULL, OFN_ALLOWMULTISELECT, NULL, NULL );
	DWORD MAXFILE = 2562; //2562 is the max//最大的多选文件数
	TCHAR* pc = new TCHAR[MAXFILE * MAX_PATH];//最大的多选文件数所占的内存大小(这里的两处+1无关紧要，认为是添加字符串终止符的长度即可)
	pc[0] = NULL;//lpstrFile的第一个字节要是NULL，注释该行，编译不报错，程序无法运行
	dlg.m_ofn.nMaxFile = MAXFILE * MAX_PATH;//nMaxFile最大的多选文件数所占的内存
	dlg.m_ofn.lpstrFile = pc;//lpstrFile指向最大的多选文件数所占的内存
	
	int iReturn = dlg.DoModal();
	if(iReturn ==  IDOK)
	{
		int nCount = 0;
		POSITION pos = dlg.GetStartPosition();
		while (pos != NULL)
		{
			CString szPathName = dlg.GetNextPathName(pos);//多选文件时，文件顺序是按对话框显示的顺序从上到下排序的，根据文件位置获取文件名
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

//写入的csv文件的“，”（占1个字节）逗号分隔符和“\n”(文本形式写入，会被写成“\n\r”占2个字节)换行符，这些是不可见的符号，而且用Excel打开CSV文件时，可以删除可见字符（空白位置不占字节），无法删除不可见字符
//CSV文件中的空字符串在file.ReadString(strRead)读入时strRead中时，会被认为无字符串，即xx,,(这里能将,,读入，是因为该行中隐藏着“\n”结束符)，当以未赋值的数组值写入csv文件是，会写入默认初始化值0.（注意，debug和release的默认初始值不一样，debug的数值型数组的默认初始值不为零）
void CMyFileDemoDlg::OnBtnReadcsvfile()//读取csv文件，注意第一行必须是数据列名称不是数据，如果CSV文件行数不一致，rowsindex记录的是最大的行数,colsindex最大的列数 
{
	// TODO: Add your control notification handler code here
	//打开文件对话框，选择单个需要读取的csv文件
   	CString szFullFileName;
	char* filters = _T("HJMC RT-Scope Files (*.csv)|*.csv||");
	
	CFileDialog fileDlg(true, "*csv", NULL, OFN_HIDEREADONLY | OFN_HIDEREADONLY, filters);
	
	if (fileDlg.DoModal() != IDOK) {
		return;
	}
	
	//获取选择文件全路径，建立一个CStdioFile对象以只读方式打开文件
	szFullFileName = fileDlg.GetPathName();
	CStdioFile file;	
	if (!file.Open(szFullFileName, CFile::modeRead | CFile::typeText))//根据路径以只读方式打开文件
	{
		AfxMessageBox(_T("文件打开失败，请检查文件是否已经被打开!"));
		return;
	}
	
	
	//读取文件数据的算法
	UINT FileRows=10000,FileCols=10000;//假设的文件中数据的总行数和总列数,比文件真实的总行数和总列数大就可以了(FileRows=csv数据最大行数-1(数据列标题占一行)-1（软件从0开始计算）;FileCols=csv数据最大列数-1（软件从0开始计算）)
	UINT SelectColumn1=0,SelectColumn2=1,SelectColumn3=2;//选择需要读取的数据列
//	double Column1[10000], Column2[10000], Column3[10000];//读取数据列保存的数组(使用成员变量，方便写入文件时使用)
	int NumCount1 = 0, NumCount2 = 0,NumCount3=0;
	
	UINT fileLength = file.GetLength();//文档的总的字节数
	UINT curPos = 0;
	float  value = 0.0;
	CString strRead = _T("");
	
	UINT  rows = 0, cols = 0;
	UINT  rowsindex = 0, colsindex = 0;//记录文件真正的总行数和总列数(移出到该函数外面，作为全局函数，方便写入函数调用)
				
	BOOL IsEndBigWhile = FALSE;//@lsj20201201
	while (IsEndBigWhile == FALSE && curPos < fileLength)//这个条件是准确的,可以保证读完最后一个数据就结束读取
	{
		file.ReadString(strRead);//以行读取数据（因为数据写的时候是使用了“\n”进行换行的）
		rowsindex++;//读到了第几行数据，index==1，说明读到了第一行数据
		curPos += strRead.GetLength() + 2;//文本文件写入“/n”后，程序硬性写入“/n/r”占了两个字节，所以这里加2（可以进行验证）
		
		strRead.TrimLeft(_T(" "));//当在没有参数的情况下调用时，TrimLeft删除字符串左边的换行符，空格和tab字符，这里只是清除空格符
		strRead.TrimRight(_T(" "));//当在没有参数的情况下调用时，TrimLeft删除字符串右边的换行符，空格和tab字符，这里只是清除空格符
		//TrimRight方法的意义是：从字符串左边看起，遇到括号中出现的字符（参数）全部截去，直到出现第一个括号中未出现的字符时停止截除，即使后面又出现了参数中有的字符也不会截去了。
		strRead.TrimRight(_T(","));//TrimRight和TrimLeft的作用是清除strRead右两侧无用的“,”符号，方便处理数据（使得条件可行：if (!strRead.IsEmpty() && -1 == strRead.Find(_T(",")))）

		
		if (strRead.IsEmpty())//如果该行数据为空，或者说该行没有数据，就不用进入下面while解析该行数据程序段中了
		{
			continue;
		}
		
		if (rowsindex > 1)//此处读到了数据了(因为第一行是数据列的名称，不是数据（如果第一行也是数据，则此处需要修改）)
		{
			//while解析一行数据
			BOOL LineOverFlag=FALSE;
			while (LineOverFlag == FALSE)//判断该行是否数据已经读完了(只有-1 != strRead.Find(_T(","))一个条件来判断该行数据读取完毕，有一个bug，最后一列数据是被忽略的，因为最后一列数据没有“，”符号了)
			{
				CString strTemp;
				//判断是否为该行的最后一列（个）数据，最后一列（个）数据的值可以直接获取
				if (!strRead.IsEmpty() && -1 == strRead.Find(_T(",")))//当截断的strRead不为空，且找不到“，”标志符，说明改行数据是最后一行数据了(bug:｛ad,cd,ef,gg,,,,｝此种情况该条件失效,解决方式：使用	strRead.TrimRight(_T(","));清除右侧的“,”符号，比如读取的字符为“54,,,”,经过该程序后变“”)
				{
					LineOverFlag=TRUE;
					strTemp = strRead;
					value = atof(strRead);
				}
				
				else
				{
//					CString strTemp;
					UINT index1 = strRead.Find(_T(","));
					strTemp = strRead.Left(index1);//把数据存储到变量strTemp中
					
					strRead = strRead.Right(strRead.GetLength() - strTemp.GetLength()-1);//截取还没有被读出来的数据保存到strRead，即截短strRead,-1是为了删除残留的“,”
					
					value = atof(strTemp);//把CString数据经转换为float类型到value变量中     CString转换为float用_tstof

				}
				
				
				if (rows <=FileRows && cols <= FileCols)//读取选择的数据列保存的数组中（FileRows和FileCols不需要提前知道，只要保证比要读取的文件的行列数大就可以了，将FileRows和FileCols值设足够大即可）
				{
					if (cols == SelectColumn1)//以该列的行数为基准读取数据
					{
						
						if (strTemp=="")//@lsj20201201:如果X的数据读到了底（在CSV中读到了空单元格），表示数据XY数据读取完毕了，不管Y是否还有数据（所以，X的数据理应比Y的数据长，这种情况，Y的空单元格读入成空字符串，转换成数值为0）
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
			
			rows++;//推进行数
			if (cols>colsindex)
			{
				colsindex=cols;//记录文件最大列数
			}
			
			cols = 0;//重置列数

			colsMax=colsindex;
			rowsMax=rowsindex;//指定X数据列的行数（不再是文件的最大行数了）
		}
	}



	CString ceshi;
	ceshi.Format("文件读取完毕：rowsindex==%d,colsindex==%d",rowsindex,colsindex);
	AfxMessageBox(ceshi);
	
	file.Close();
	
}

void CMyFileDemoDlg::OnBtnWritecsvfile() //将读取文件按钮读取的文件数据保存的数组ColumnN[]写入到指定文件夹D:\\DebugInfo\\SweepAnalyzeResult\\%Y%m%d-%H%M%S.csv文件中
{
	// TODO: Add your control notification handler code here
	//确定保存数据的文件全路径名称
	//1.确定路径
	CString m_szDataPathName = "D:\\DebugInfo\\SweepAnalyzeResult\\";//@lsj20201010:必须保证这个路径中的文件夹存在，否则后续无法创建在该路径上的文件
	//add by @lsj20201010:如果没有创建D:\\DebugInfo\\SweepAnalyzeResult文件夹，则创建用于保存prbs的解析结果
	CString szFolder = "D:\\DebugInfo";//如果一级文件夹不存在，则创建
	if (!PathIsDirectory(szFolder))
	{
		::CreateDirectory(szFolder, NULL);	
	}
	
	szFolder += "\\SweepAnalyzeResult";//如果二级文件夹不存在，则创建
	if (!PathIsDirectory(szFolder))
	{
		::CreateDirectory(szFolder, NULL);	
	}
	
	//2.确定文件名称（加时间戳）
	CTime tmStart = CTime::GetCurrentTime();
	m_szDataPathName += tmStart.Format("%Y%m%d-%H%M%S");
	m_szDataPathName += _T(".csv");
	
	//根据全路径名称创建文件并写入数据
	CStdioFile  OutPutFile;
	
	if (!OutPutFile.Open(m_szDataPathName, CFile::modeCreate | CFile::modeWrite))
	{
		AfxMessageBox("打开文件失败，写入操作不能执行");
		return;
	}
	
	//写数据到文件（这里使用逗号将数据隔开，是因为该文件保存的格式是逗号分隔文件，可以方便转换成Excel文件或者txt文件）
	//写第一行到CSV文件，第一行是数据标题
	CString strLine;
	strLine = _T("Hz");
	strLine += _T(",");
	strLine += _T("dB"); 
	strLine += _T(",");
	strLine += _T("Degree");
	strLine += '\n';
	OutPutFile.WriteString(strLine);
	
	
	//写数据到CSV文件，一行一行的写（此处只写了三行）
	for (int i = 0; i < rowsMax-1; i++)
	{
		CString DataColumn1, DataColumn2,  DataColumn3;
		DataColumn1.Format(_T("%.4f"), Column1[i]);
		DataColumn2.Format(_T("%.4f"), Column2[i]);
		DataColumn3.Format(_T("%.4f"), Column3[i]);
		strLine = DataColumn1 + ',' + DataColumn2 + ',' + DataColumn3 + '\n';
		OutPutFile.WriteString(strLine);
	}
	
	
	AfxMessageBox("数据写入完成,保存文件的路径为：D:\\DebugInfo\\SweepAnalyzeResult");
	
	OutPutFile.Close();
	
}


//读取给定配置文件(段(or标记)、键=<键值>)的键值
//1. 读一个键，即一行的键值
BOOL  CMyFileDemoDlg::FileParaReadGivenFilePath1(CString sflag,double *ddata,CString szFilePathName)//读取MFSCFileNmPth配置文件中sToFindflagDynAmp节名，获取键值<>中的数据保存到&ddataDynX[0]中（该函数只读一个键，即一行的键值）
{    
    CStdioFile fout;
    BOOL bRtn = fout.Open(szFilePathName, CFile::modeRead | CFile::typeText);
    if(!bRtn)
    {
        AfxMessageBox(_T("No this par file exist!"));    
        return     FALSE;
    }
    CString ss;//一行的字符串
    CString LineData;
    int nbgn,nlgth;//
    int kk=0;
    int nIdxLine;
    int dd=0; //dd为文件读取数据的位置，但实际没有什么起到位置指示的作用，而是表示找到了段名，可以进入if( dd!=0 )的处理程序，其作用跟nsflagExist一样
    int nsflagExist=0; //nsflagExist==1说明找到了节名或者段名（sflag） 
start:
    while(fout.ReadString(ss))//@lsj注释:ReadString在碰到第一个换行符时停止读取,即一般只读一行字符串（除非这一行字符串没有使用换行符继续写下去）
	{    
		if (ss.Find("#")==0 ) //bypass the line with '#' start
            goto start;////跳过以“#”符号开始的行 
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
				LineData = ss.Mid(nbgn+nlgth+1, ss.Find(">") - (nbgn+ nlgth));//<>行中的截断式取键值       
				ss = LineData;
				
				//判断是否读到了<>中的最后一个值nbgn=-1就说明读到了最后一个值，结束while ( nlgth != - 1 )循环
				nbgn = 0;
				if ( ss.FindOneOf(",") !=-1 )
					nlgth = ss.FindOneOf(",") - nbgn ;
				else 
					nlgth = ss.Find(">") - nbgn; // the last value ：nlgth=-1-0=-1
			}
			
		}
		
		nIdxLine = ss.Find( sflag);
		
		if( nIdxLine==0){ //find the value;
			dd=fout.GetPosition(); //dd为文件读取数据的位置，但实际没有什么起到位置指示的作用，而是表示找到了段名，可以进入if( dd!=0 )的处理程序，其作用跟nsflagExist一样
			nsflagExist = 1;//nsflagExist==1说明找到了节名或者段名（sflag）
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


//2. 读多个键，即多行的键值
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
    while(fout.ReadString(ss))//一行一行的读入分析
    {    
        if (    ss.Find("#")==0 ) //bypass the line with '#' start
            goto start;
        if( dd!=0 )//dd!=0 说明进入了键所在行
        {        
            for (ii=0; ii<CycleNum; ii++) {//循环三次，读三行<>数据,保存到ddata[]中
				int nIdxData = ss.Find("<");
				int nDeliminator = ss.FindOneOf(","); // delimenator is comma
				int nEndCnter = ss.Find(">");
				nbgn =  nIdxData+1;
				nlgth=  nDeliminator-nIdxData-1;
				while ( nlgth != - 1 ) // if can find comma, will continue this loop;
				{
					ddata[kk] = atof( ss.Mid(nbgn,nlgth) ) ;  // atof() 用于将字符串转换为双精度浮点数(double)
					kk=kk+1;
					LineData = ss.Mid(nbgn+nlgth+1, ss.Find(">") - (nbgn+ nlgth));
					ss = LineData;
					nbgn = 0;
					if ( ss.FindOneOf(",") !=-1 )
						nlgth = ss.FindOneOf(",") - nbgn ;
					else 
						nlgth = ss.Find(">") - nbgn; // the last value
				}
				fout.ReadString(ss);//再读入一行字符串，进行分解获取键值
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




void CMyFileDemoDlg::OnBtnReadcfgfile()// 配置文件(不管文件使用什么后缀)只要符合一定的书写格式(段(or标记)、键=<键值>)就可以使用下面两个函数读取键值
{
	// TODO: Add your control notification handler code here

	//打开文件对话框，选择单个需要读取的cfg文件
   	CString szFullFileName;
	char* filters = _T("cfg Files (*.cfg)|*.cfg|par Files (*.par)|*.par|txt Files (*.txt)|*.txt||");//配置文件只要符合一定的书写格式(段(or标记)、键=<键值>)就可以使用下面两个函数读取键值
	
	CFileDialog fileDlg(true, "*cfg", NULL, OFN_HIDEREADONLY | OFN_HIDEREADONLY, filters);
	
	if (fileDlg.DoModal() != IDOK) {
		return;
	}

	
	//形参的初始化
	szFullFileName = fileDlg.GetPathName();//获取选择文件全路径
	CString  sflag;
	sflag="[OPEN_LOOPX]";//段名（或者说是节名）
	double ddata[30];
	UINT CycleNum=3;//CycleNum决定函数FileParaReadGivenFilePath2读取多少行的键值
//	FileParaReadGivenFilePath1(sflag,ddata,szFullFileName);//1. 读一个键，即一行的键值
	FileParaReadGivenFilePath2(sflag,ddata,szFullFileName,CycleNum);//2. 读多个键，即多行的键值，CycleNum决定函数读取多少行的键值（或者说读取多少个键）
	
}

void CMyFileDemoDlg::OnBtnWritecfgfile() //修改某个节名中某个键的键值
{
	// TODO: Add your control notification handler code here
	//1.通过节名和键名定位到需要修改的行
	//2.在行字符串中判断需要修改数据的位置
	//3.将需要修改的键值进行字符替换（这一步不好做的，除非要替换字符的长度与替换字符的长度一致，否则，替换无法进行）
	
}
