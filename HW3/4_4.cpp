#include <windows.h>
#include <tchar.h>
#include <math.h>
BOOLEAN InitWindowClass(HINSTANCE hInstance,int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HFONT CreateMyFont(TCHAR *fontName,int height);		
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	MSG msg;									
    if(!InitWindowClass(hInstance,nCmdShow))
	{
		 MessageBox(NULL, L"创建窗口失败!",_T("创建窗口"),NULL);
		 return 1;
	}
    while (GetMessage(&msg, NULL, 0, 0))	
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int) msg.wParam;	
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	TEXTMETRIC tm;
	PAINTSTRUCT ps;
	HFONT font;  
	LPWSTR poem[5]={L"苔[清]袁枚",
				    L"白日不到处",
					L"青春恰自来",
				    L"苔花如米小",
					L"也学牡丹开"
						 };
	int X,Y=0,i=0,k=0,color;
	int fs[5];
	RECT clientDimension;
	GetClientRect(hWnd,&clientDimension);
	for(int j=0;j<5;j++)
		fs[j]=_tcsclen(poem[j]);
	
    switch (message)
    {
	case WM_SIZE:
		InvalidateRect(hWnd,NULL,true);
		break;
	case WM_PAINT:
		hDC=GetDC(hWnd);
		GetTextMetrics(hDC,&tm);
	
		hDC=BeginPaint(hWnd,&ps);
		for(k;k<5;k++)
		{
			 X=0;
			 color=0;
		for(i=0;i<fs[k];i++)
		{
			int H=8+i*32/fs[k];
			X+=2*tm.tmHeight;
			LPCWSTR outInfo=&poem[k][i];  			
			switch(k){
	        case 0:
				font=CreateMyFont(L"楷体",H); //创建字体
				break;
			case 1:
				font=CreateMyFont(L"黑体",H); //创建字体
				break;
			case 2:
				font=CreateMyFont(L"华文行楷",H); //创建字体
				break;
            case 3:
				font=CreateMyFont(L"微软雅黑",H); //创建字体
				break;
			case 4:
				font=CreateMyFont(L"仿宋",H); //创建字体
				break;
			default:
				return 0;
				break;
			}
			SelectObject(hDC,font);						//将创建的字体句柄选入设备环境
			color=i*255/fs[k];
			SetTextColor(hDC,RGB(color,color,color));
			TextOut(hDC,X,Y,outInfo,1);    	//输出文字
			//Sleep(4);						//输出一个文字暂停.4秒
			DeleteObject(font);
			
		}
			//Sleep(40);						//输出一个文字暂停.4秒
		SetBkColor(hDC,RGB(255,255,255));
		TextOut(hDC,0,Y,L"                            ",(clientDimension.right-clientDimension.left));
		Y+=(clientDimension.bottom-clientDimension.top)/5;
		}
		EndPaint(hWnd,&ps);  						//结束绘图
		break;
    case WM_DESTROY:
        PostQuitMessage(0);										//调用PostQuitMessage发出WM_QUIT消息
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);	//默认时采用系统消息默认处理函数
        break;
    }
    return 0;
}
HFONT CreateMyFont(TCHAR *fontName,int height)
{
	return CreateFont						//创建自定义字体
					(
						height,				//字体的高度
						0,					//由系统根据高宽比选取字体最佳宽度值
						0,				////倾斜度为lean，其值由调用时传过来
						0,					//字体的倾斜度为0
						FW_HEAVY,				//字体的粗度，FW_HEAVY为最粗
						0,					//非斜体字
						0,					//无下划线
						0,					//无删除线
						GB2312_CHARSET,		//表示所用的字符集为ANSI_CHARSET
						OUT_DEFAULT_PRECIS,	//输出精度为默认精度
						CLIP_DEFAULT_PRECIS,	//剪裁精度为默认精度
						DEFAULT_QUALITY,		//输出质量为默认值
						DEFAULT_PITCH|FF_DONTCARE,//字间距和字体系列使用默认值
						fontName				//字体名称
						);
}
BOOLEAN InitWindowClass(HINSTANCE hInstance,int nCmdShow)
{
	WNDCLASSEX wcex;
	HWND hWnd;
	TCHAR szWindowClass[] = L"窗口示例";
	TCHAR szTitle[] = L"字体及位置示例";
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style          = 0;		
	wcex.lpfnWndProc    = WndProc;	
	wcex.cbClsExtra     = 0;	
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = hInstance;
	wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);	
	wcex.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);	
	wcex.lpszMenuName   = NULL;	
	wcex.lpszClassName  = szWindowClass;	
	wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	if (!RegisterClassEx(&wcex))													
		return FALSE;
	hWnd = CreateWindow(
		szWindowClass,															
		szTitle,																
		WS_OVERLAPPEDWINDOW,													
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,	
		NULL
		);
    if (!hWnd)	
         return FALSE;
    ShowWindow(hWnd,nCmdShow);	
    UpdateWindow(hWnd);
	return TRUE;
}
