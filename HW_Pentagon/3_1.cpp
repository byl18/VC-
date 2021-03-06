#include <windows.h>
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInst,LPSTR lpszCmdLine,int nCmdShow)
{ 
	HWND hwnd;
	MSG Msg;
    WNDCLASS wndclass;
	TCHAR lpszClassName[] =L"My_Drawing";
	TCHAR lpszTitle[]=L"�����";
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
	HPEN hP;								//���廭�ʾ��
	HBRUSH  hB;								//���廭ˢ���
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
	case WM_PAINT:							//ͨ����ӦWM_PAINT��Ϣ��ɻ�ͼ����
		hdc=BeginPaint(hwnd,&ps); 			//ȡ���豸�������
		SetMapMode(hdc,MM_TEXT);			//����ӳ��ģʽ
		
			
		hB=CreateSolidBrush(RGB(128,64,0));	//�Զ���һ����ˢ
		SelectObject(hdc,hB);				//���»�ˢΪ�Զ��廭ˢ
		Polygon(hdc,lpPoint1,3);
		hB=CreateSolidBrush(RGB(64,128,0));	//�Զ���һ����ˢ
		SelectObject(hdc,hB);				//���»�ˢΪ�Զ��廭ˢ
		Polygon(hdc,lpPoint2,3);
		hB=CreateSolidBrush(RGB(0,64,128));	//�Զ���һ����ˢ
		SelectObject(hdc,hB);				//���»�ˢΪ�Զ��廭ˢ
		Polygon(hdc,lpPoint3,3);
		hB=CreateSolidBrush(RGB(128,64,128));	//�Զ���һ����ˢ
		SelectObject(hdc,hB);				//���»�ˢΪ�Զ��廭ˢ
		Polygon(hdc,lpPoint4,3);
		hB=CreateSolidBrush(RGB(64,128,128));	//�Զ���һ����ˢ
		SelectObject(hdc,hB);				//���»�ˢΪ�Զ��廭ˢ
		Polygon(hdc,lpPoint5,3);
		hB=CreateSolidBrush(RGB(128,128,64));	//�Զ���һ����ˢ
		SelectObject(hdc,hB);				//���»�ˢΪ�Զ��廭ˢ
		Polygon(hdc,lpPoint6,3);
		hB=CreateSolidBrush(RGB(64,64,128));	//�Զ���һ����ˢ
		SelectObject(hdc,hB);				//���»�ˢΪ�Զ��廭ˢ
		Polygon(hdc,lpPoint7,3);
		hB=CreateSolidBrush(RGB(64,128,64));	//�Զ���һ����ˢ
		SelectObject(hdc,hB);				//���»�ˢΪ�Զ��廭ˢ
		Polygon(hdc,lpPoint8,3);
		hB=CreateSolidBrush(RGB(128,64,64));	//�Զ���һ����ˢ
		SelectObject(hdc,hB);				//���»�ˢΪ�Զ��廭ˢ
		Polygon(hdc,lpPoint9,3);
		hB=CreateSolidBrush(RGB(64,64,64));	//�Զ���һ����ˢ
		SelectObject(hdc,hB);				//���»�ˢΪ�Զ��廭ˢ
		Polygon(hdc,lpPoint10,3);
		hB=CreateSolidBrush(RGB(128,128,128));	//�Զ���һ����ˢ
		SelectObject(hdc,hB);				//���»�ˢΪ�Զ��廭ˢ
		Polygon(hdc,lpPoint11,5);

		hB=(HBRUSH)GetStockObject(NULL_BRUSH);
		SelectObject(hdc,hB);	
		hP=CreatePen(PS_SOLID,1,RGB(255,0,0));	//���Ϊ1�ĺ�ɫ���ʣ���ʵ��
		SelectObject(hdc,hP);				//���»���Ϊ�Զ��廭��
		Polygon(hdc,lpPoints, nCount);		//ʹ�õ�ǰ���ʻ��ƶ���β����
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
	   
		EndPaint(hwnd,&ps);					//�ͷ��豸�������
		DeleteObject(hP);					//ɾ�����ʾ��
		DeleteObject(hB);					//ɾ����ˢ���
		break;
	case WM_DESTROY: 
		PostQuitMessage(0);
		break;
	default:
		return  DefWindowProc(hwnd,message,wParam,lParam);
	};
return 0;
}
