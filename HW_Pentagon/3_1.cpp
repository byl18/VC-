#include <windows.h>
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInst,LPSTR lpszCmdLine,int nCmdShow)
{ 
	HWND hwnd;
	MSG Msg;
    WNDCLASS wndclass;
	TCHAR lpszClassName[] =L"My_Drawing";
	TCHAR lpszTitle[]=L"五边形";
	wndclass.style = 0;
	wndclass.lpfnWndProc = WndProc ;
	wndclass.cbClsExtra	= 0 ;
	wndclass.cbWndExtra	= 0 ;
	wndclass.hInstance = hInstance ;
	wndclass.hIcon = LoadIcon( NULL, IDI_APPLICATION) ;
	wndclass.hCursor = LoadCursor( NULL, IDC_ARROW) ;
	wndclass.hbrBackground =(HBRUSH) GetStockObject( WHITE_BRUSH) ;
	wndclass.lpszMenuName = NULL ;
	wndclass.lpszClassName =lpszClassName ;
	if( !RegisterClass( &wndclass))
	{
		MessageBeep(0) ;
		return FALSE ;
	}

hwnd = CreateWindow(
		lpszClassName,
		lpszTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);
ShowWindow(hwnd, nCmdShow);
UpdateWindow(hwnd);
while( GetMessage(&Msg, NULL, 0, 0))
{
	TranslateMessage(&Msg) ;
	DispatchMessage(&Msg) ;
}
return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM  wParam,LPARAM  lParam)
{	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hP;								//定义画笔句柄
	HBRUSH  hB;								//定义画刷句柄
	int nCount=5;
	POINT lpPoints[5]={100,100,100,200,195,231,254,150,195,69};
	POINT lpPoint1[3]={100,100,100,200,136,150};
	POINT lpPoint2[3]={159,181,100,200,136,150};
	POINT lpPoint3[3]={159,181,100,200,195,231};
	POINT lpPoint4[3]={159,181,195,169,195,231};
	POINT lpPoint5[3]={254,150,195,169,195,231};
	POINT lpPoint6[3]={254,150,195,169,195,131};
	POINT lpPoint7[3]={195,69,254,150,195,131};
	POINT lpPoint8[3]={195,69,159,119,195,131};
	POINT lpPoint9[3]={195,69,159,119,100,100};
	POINT lpPoint10[3]={159,119,136,150,100,100};

	POINT lpPoint11[5]={136,150,159,181,195,169,195,131,159,119};
	switch(message)
	{
	case WM_PAINT:							//通过响应WM_PAINT消息完成绘图工作
		hdc=BeginPaint(hwnd,&ps); 			//取得设备环境句柄
		SetMapMode(hdc,MM_TEXT);			//设置映射模式
		
			
		hB=CreateSolidBrush(RGB(128,64,0));	//自定义一个画刷
		SelectObject(hdc,hB);				//更新画刷为自定义画刷
		Polygon(hdc,lpPoint1,3);
		hB=CreateSolidBrush(RGB(64,128,0));	//自定义一个画刷
		SelectObject(hdc,hB);				//更新画刷为自定义画刷
		Polygon(hdc,lpPoint2,3);
		hB=CreateSolidBrush(RGB(0,64,128));	//自定义一个画刷
		SelectObject(hdc,hB);				//更新画刷为自定义画刷
		Polygon(hdc,lpPoint3,3);
		hB=CreateSolidBrush(RGB(128,64,128));	//自定义一个画刷
		SelectObject(hdc,hB);				//更新画刷为自定义画刷
		Polygon(hdc,lpPoint4,3);
		hB=CreateSolidBrush(RGB(64,128,128));	//自定义一个画刷
		SelectObject(hdc,hB);				//更新画刷为自定义画刷
		Polygon(hdc,lpPoint5,3);
		hB=CreateSolidBrush(RGB(128,128,64));	//自定义一个画刷
		SelectObject(hdc,hB);				//更新画刷为自定义画刷
		Polygon(hdc,lpPoint6,3);
		hB=CreateSolidBrush(RGB(64,64,128));	//自定义一个画刷
		SelectObject(hdc,hB);				//更新画刷为自定义画刷
		Polygon(hdc,lpPoint7,3);
		hB=CreateSolidBrush(RGB(64,128,64));	//自定义一个画刷
		SelectObject(hdc,hB);				//更新画刷为自定义画刷
		Polygon(hdc,lpPoint8,3);
		hB=CreateSolidBrush(RGB(128,64,64));	//自定义一个画刷
		SelectObject(hdc,hB);				//更新画刷为自定义画刷
		Polygon(hdc,lpPoint9,3);
		hB=CreateSolidBrush(RGB(64,64,64));	//自定义一个画刷
		SelectObject(hdc,hB);				//更新画刷为自定义画刷
		Polygon(hdc,lpPoint10,3);
		hB=CreateSolidBrush(RGB(128,128,128));	//自定义一个画刷
		SelectObject(hdc,hB);				//更新画刷为自定义画刷
		Polygon(hdc,lpPoint11,5);

		hB=(HBRUSH)GetStockObject(NULL_BRUSH);
		SelectObject(hdc,hB);	
		hP=CreatePen(PS_SOLID,1,RGB(255,0,0));	//宽度为1的红色画笔，画实线
		SelectObject(hdc,hP);				//更新画笔为自定义画笔
		Polygon(hdc,lpPoints, nCount);		//使用当前画笔绘制多边形并填充
		hP=CreatePen(PS_SOLID,1,RGB(0,0,255));
		SelectObject(hdc,hP);
		MoveToEx(hdc,100,100,NULL);
		LineTo(hdc,195,231);	
		hP=CreatePen(PS_SOLID,1,RGB(0,255,255));
		SelectObject(hdc,hP);
		LineTo(hdc,195,69);	
		hP=CreatePen(PS_SOLID,1,RGB(0,255,0));
		SelectObject(hdc,hP);
		LineTo(hdc,100,200);	
		hP=CreatePen(PS_SOLID,1,RGB(255,255,0));
		SelectObject(hdc,hP);
		LineTo(hdc,254,150);	
		hP=CreatePen(PS_SOLID,1,RGB(255,0,255));
		SelectObject(hdc,hP);
		LineTo(hdc,100,100);
	   
		EndPaint(hwnd,&ps);					//释放设备环境句柄
		DeleteObject(hP);					//删除画笔句柄
		DeleteObject(hB);					//删除画刷句柄
		break;
	case WM_DESTROY: 
		PostQuitMessage(0);
		break;
	default:
		return  DefWindowProc(hwnd,message,wParam,lParam);
	};
return 0;
}
