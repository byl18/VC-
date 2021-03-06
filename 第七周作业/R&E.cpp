#include <windows.h>
long WINAPI WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam);
BOOL InitWindowsClass(HINSTANCE hInstance);			//初始化窗口类声明
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);//初始化窗口声明
HWND hWndMain;							//定义全局窗口句柄
static RECT rect0;				//定义矩形结构体.记录了图形的信息
static RECT rect1;				//定义矩形结构体.记录了图形的信息
static int z=0;
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	MSG Message;
	if(!InitWindowsClass(hInstance))		//初始化窗口类
		return FALSE;
	if(!InitWindows(hInstance,nCmdShow))	//初始化窗口
		return FALSE;
	while(GetMessage(&Message,0,0,0))
	{
		TranslateMessage(&Message);			//消息循环
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

long WINAPI WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam)
{
	HDC hDC;				//定义设备环境句柄
	int x,y;				//定义鼠标的位置坐标
	static BOOL bCircle=FALSE,bRect=FALSE;	//设置绘制圆和矩形的标志变量
	static BOOL nH=FALSE,nE=FALSE,nU=FALSE,nD=FALSE,nP=FALSE,nR=FALSE;	//设置绘制圆和矩形的标志变量
	PAINTSTRUCT ps;			//定义绘图结构体变量
	x = LOWORD(lParam);		//得到鼠标的位置
	y = HIWORD(lParam);
	switch(iMessage)
	{

	case WM_KEYDOWN:
		{ 
			hDC = BeginPaint(hWnd,&ps);
			switch(wParam)
			{
			case VK_HOME:				
				nH=TRUE;
				break;
			case VK_END:			
				nE=TRUE;
				break;
            case VK_PRIOR:		
				nU=TRUE;
				break;
            case VK_NEXT:		
				nD=TRUE;
			
				break;
			case VK_UP:			
				nP=TRUE;
				break;
			case VK_RIGHT:			
				nR=TRUE;
				break;
			}
		}
		break;

		case WM_KEYUP:
			if(wParam==VK_HOME||wParam==VK_PRIOR||wParam==VK_NEXT||wParam==VK_RIGHT||wParam==VK_UP||wParam==VK_END)
				InvalidateRect(hWnd,NULL,TRUE);	//刷新用户区	
		break;
	
	case WM_LBUTTONDOWN:	//处理按下鼠标左键消息
		if(wParam&MK_CONTROL)	//同时按下Ctrl键时
		{
			bCircle = TRUE;			//画圆
			bRect = FALSE;
			
			rect0.left = x;			//圆的左上角坐标为当前鼠标位置
			rect0.top = y;
			rect1.left = x;		//图形的右下角坐标为当前鼠标位置
		    rect1.top = y;
		}
		else if(wParam&MK_SHIFT)	//同时按下shift键时
		{
			bRect = TRUE;				//画矩形
			bCircle = FALSE;
			
			rect0.left = x;			//矩形的左上角坐标为当前鼠标位置
			rect0.top = y;
			rect1.left= x;		//图形的右下角坐标为当前鼠标位置
		    rect1.top = y;
		}
		else
		{
			bRect = FALSE;
			bCircle = FALSE;
		}
		break;
	case WM_LBUTTONUP:			//当松开左键时.绘图标志为false
		bRect =FALSE;
		bCircle = FALSE;
		rect1.right = x;		//图形的右下角坐标为当前鼠标位置
		rect1.bottom = y;
		break;
	case WM_MOUSEMOVE:			//处理鼠标移动信息
		rect0.right = x;		//图形的右下角坐标为当前鼠标位置
		rect0.bottom = y;
		if(bRect == TRUE || bCircle == TRUE)
			InvalidateRect(hWnd,NULL,TRUE);	//发出重绘信息
		break;

	case WM_PAINT:
    hDC = BeginPaint(hWnd,&ps);
		if(bCircle == TRUE)	//绘制圆形
			{Ellipse(hDC,rect0.left,rect0.top,rect0.right,rect0.bottom);
		z=1;}
		if(bRect== TRUE)//绘制矩形
		{
			Rectangle(hDC,rect0.left,rect0.top,rect0.right,rect0.bottom);
		z=2;
		}
		if(z==1)
			{if(nH==TRUE)
				{
				Ellipse(hDC,rect1.left-10,rect1.top,rect1.right-10,rect1.bottom);
		         rect1.left-=10;
				 rect1.right-=10;
                 nH=FALSE;
		}
			if(nE==TRUE)
				{Ellipse(hDC,rect1.left+10,rect1.top,rect1.right+10,rect1.bottom);
			  rect1.left+=10;
			  rect1.right+=10;
			nE=FALSE;}
			if(nU==TRUE)
				{Ellipse(hDC,rect1.left,rect1.top-10,rect1.right,rect1.bottom-10);
			rect1.top-=10;
			rect1.bottom-=10;
			nU=FALSE;}
			if(nD==TRUE)
				{Ellipse(hDC,rect1.left,rect1.top+10,rect1.right,rect1.bottom+10);
			rect1.top+=10;
			rect1.bottom+=10;

			nD=FALSE;}
			if(nP==TRUE)
				{Ellipse(hDC,rect1.left,rect1.top-5,rect1.right,rect1.bottom+5);
			rect1.top-=5;
			rect1.bottom+=5;
			nP=FALSE;}
		if(nR==TRUE)
		{Ellipse(hDC,rect1.left-5,rect1.top,rect1.right+5,rect1.bottom);
		rect1.left-=5;
			  rect1.right+=5;
		nR=FALSE;}
		}
		else if(z==2)
			{if(nH==TRUE)
				{Rectangle(hDC,rect1.left-10,rect1.top,rect1.right-10,rect1.bottom);
		 rect1.left-=10;
		rect1.right-=10;
		 nH=FALSE;}
			if(nE==TRUE)
				{Rectangle(hDC,rect1.left+10,rect1.top,rect1.right+10,rect1.bottom);
			 rect1.left+=10;
			  rect1.right+=10;
			nE=FALSE;}
			if(nU==TRUE)
				{Rectangle(hDC,rect1.left,rect1.top-10,rect1.right,rect1.bottom-10);
			rect1.top-=10;
			rect1.bottom-=10;
			nU=FALSE;}
			if(nD==TRUE)
				{Rectangle(hDC,rect1.left,rect1.top+10,rect1.right,rect1.bottom+10);
				rect1.top+=10;
			rect1.bottom+=10;
			nD=FALSE;}
			if(nP==TRUE)
				{Rectangle(hDC,rect1.left,rect1.top-5,rect1.right,rect1.bottom+5);
			rect1.top-=5;
			rect1.bottom+=5;
			nP=FALSE;}
			if(nR==TRUE)
				{Rectangle(hDC,rect1.left-5,rect1.top,rect1.right+5,rect1.bottom);
				rect1.left-=5;
			  rect1.right+=5;
			nR=FALSE;}
			}
	EndPaint(hWnd,&ps);
	break;
	case WM_DESTROY:		//处理退出窗口信息
		PostQuitMessage(0);
		return 0;
	default:
		return(DefWindowProc(hWnd,iMessage,wParam,lParam));
	}
	return 0;
}

BOOL InitWindows(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd=CreateWindow("鼠标练习",				//窗口类名称
					"鼠标显示实例程序",		 //标题栏名称
					WS_OVERLAPPEDWINDOW,	//窗口样式.有标题栏和最大最小化按钮
					CW_USEDEFAULT,			//窗口左上角坐标
					0,
					CW_USEDEFAULT,			//采用缺省的高度和宽度
					0,
					NULL,					//无父窗口
					NULL,					//无菜单
					hInstance,				//当前应用实例句柄
					NULL);					//指向传递给窗口的参数的指针.不用
	if(!hWnd)		//创建失败.
		return FALSE;
	hWndMain=hWnd;	//给全局窗口句柄付值.
	ShowWindow(hWnd,nCmdShow);	//显示窗口
	UpdateWindow(hWnd);			//刷新用户区
	return TRUE;
}

BOOL InitWindowsClass(HINSTANCE hInstance)
{
	WNDCLASS WndClass;
	WndClass.cbClsExtra=0;			//无窗口类扩展
	WndClass.cbWndExtra=0;			//无窗口实例扩展
	WndClass.hbrBackground=(HBRUSH)(GetStockObject(WHITE_BRUSH));//背景为白色
	WndClass.hCursor=LoadCursor(NULL,IDC_CROSS);	//光标为为箭头
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);	//采用缺省图标
	WndClass.hInstance=hInstance;			//当前实例
	WndClass.lpfnWndProc=WndProc;			//消息处理函数
	WndClass.lpszClassName="鼠标练习";			//窗口类名称
	WndClass.lpszMenuName=NULL;				//无菜单
	WndClass.style=0;						//缺省窗口风格
	return RegisterClass(&WndClass);	//返回窗口注册值
}