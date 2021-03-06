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
		 MessageBox(NULL, L"��������ʧ��!",_T("��������"),NULL);
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
	LPWSTR poem[5]={L"̦[��]Ԭö",
				    L"���ղ�����",
					L"�ഺǡ����",
				    L"̦������С",
					L"Ҳѧĵ����"
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
				font=CreateMyFont(L"����",H); //��������
				break;
			case 1:
				font=CreateMyFont(L"����",H); //��������
				break;
			case 2:
				font=CreateMyFont(L"�����п�",H); //��������
				break;
            case 3:
				font=CreateMyFont(L"΢���ź�",H); //��������
				break;
			case 4:
				font=CreateMyFont(L"����",H); //��������
				break;
			default:
				return 0;
				break;
			}
			SelectObject(hDC,font);						//��������������ѡ���豸����
			color=i*255/fs[k];
			SetTextColor(hDC,RGB(color,color,color));
			TextOut(hDC,X,Y,outInfo,1);    	//�������
			//Sleep(4);						//���һ��������ͣ.4��
			DeleteObject(font);
			
		}
			//Sleep(40);						//���һ��������ͣ.4��
		SetBkColor(hDC,RGB(255,255,255));
		TextOut(hDC,0,Y,L"                            ",(clientDimension.right-clientDimension.left));
		Y+=(clientDimension.bottom-clientDimension.top)/5;
		}
		EndPaint(hWnd,&ps);  						//������ͼ
		break;
    case WM_DESTROY:
        PostQuitMessage(0);										//����PostQuitMessage����WM_QUIT��Ϣ
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);	//Ĭ��ʱ����ϵͳ��ϢĬ�ϴ�����
        break;
    }
    return 0;
}
HFONT CreateMyFont(TCHAR *fontName,int height)
{
	return CreateFont						//�����Զ�������
					(
						height,				//����ĸ߶�
						0,					//��ϵͳ���ݸ߿��ѡȡ������ѿ��ֵ
						0,				////��б��Ϊlean����ֵ�ɵ���ʱ������
						0,					//�������б��Ϊ0
						FW_HEAVY,				//����Ĵֶȣ�FW_HEAVYΪ���
						0,					//��б����
						0,					//���»���
						0,					//��ɾ����
						GB2312_CHARSET,		//��ʾ���õ��ַ���ΪANSI_CHARSET
						OUT_DEFAULT_PRECIS,	//�������ΪĬ�Ͼ���
						CLIP_DEFAULT_PRECIS,	//���þ���ΪĬ�Ͼ���
						DEFAULT_QUALITY,		//�������ΪĬ��ֵ
						DEFAULT_PITCH|FF_DONTCARE,//�ּ�������ϵ��ʹ��Ĭ��ֵ
						fontName				//��������
						);
}
BOOLEAN InitWindowClass(HINSTANCE hInstance,int nCmdShow)
{
	WNDCLASSEX wcex;
	HWND hWnd;
	TCHAR szWindowClass[] = L"����ʾ��";
	TCHAR szTitle[] = L"���弰λ��ʾ��";
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
