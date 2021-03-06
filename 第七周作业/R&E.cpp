#include <windows.h>
long WINAPI WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam);
BOOL InitWindowsClass(HINSTANCE hInstance);			//��ʼ������������
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);//��ʼ����������
HWND hWndMain;							//����ȫ�ִ��ھ��
static RECT rect0;				//������νṹ��.��¼��ͼ�ε���Ϣ
static RECT rect1;				//������νṹ��.��¼��ͼ�ε���Ϣ
static int z=0;
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	MSG Message;
	if(!InitWindowsClass(hInstance))		//��ʼ��������
		return FALSE;
	if(!InitWindows(hInstance,nCmdShow))	//��ʼ������
		return FALSE;
	while(GetMessage(&Message,0,0,0))
	{
		TranslateMessage(&Message);			//��Ϣѭ��
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

long WINAPI WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam)
{
	HDC hDC;				//�����豸�������
	int x,y;				//��������λ������
	static BOOL bCircle=FALSE,bRect=FALSE;	//���û���Բ�;��εı�־����
	static BOOL nH=FALSE,nE=FALSE,nU=FALSE,nD=FALSE,nP=FALSE,nR=FALSE;	//���û���Բ�;��εı�־����
	PAINTSTRUCT ps;			//�����ͼ�ṹ�����
	x = LOWORD(lParam);		//�õ�����λ��
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
				InvalidateRect(hWnd,NULL,TRUE);	//ˢ���û���	
		break;
	
	case WM_LBUTTONDOWN:	//��������������Ϣ
		if(wParam&MK_CONTROL)	//ͬʱ����Ctrl��ʱ
		{
			bCircle = TRUE;			//��Բ
			bRect = FALSE;
			
			rect0.left = x;			//Բ�����Ͻ�����Ϊ��ǰ���λ��
			rect0.top = y;
			rect1.left = x;		//ͼ�ε����½�����Ϊ��ǰ���λ��
		    rect1.top = y;
		}
		else if(wParam&MK_SHIFT)	//ͬʱ����shift��ʱ
		{
			bRect = TRUE;				//������
			bCircle = FALSE;
			
			rect0.left = x;			//���ε����Ͻ�����Ϊ��ǰ���λ��
			rect0.top = y;
			rect1.left= x;		//ͼ�ε����½�����Ϊ��ǰ���λ��
		    rect1.top = y;
		}
		else
		{
			bRect = FALSE;
			bCircle = FALSE;
		}
		break;
	case WM_LBUTTONUP:			//���ɿ����ʱ.��ͼ��־Ϊfalse
		bRect =FALSE;
		bCircle = FALSE;
		rect1.right = x;		//ͼ�ε����½�����Ϊ��ǰ���λ��
		rect1.bottom = y;
		break;
	case WM_MOUSEMOVE:			//��������ƶ���Ϣ
		rect0.right = x;		//ͼ�ε����½�����Ϊ��ǰ���λ��
		rect0.bottom = y;
		if(bRect == TRUE || bCircle == TRUE)
			InvalidateRect(hWnd,NULL,TRUE);	//�����ػ���Ϣ
		break;

	case WM_PAINT:
    hDC = BeginPaint(hWnd,&ps);
		if(bCircle == TRUE)	//����Բ��
			{Ellipse(hDC,rect0.left,rect0.top,rect0.right,rect0.bottom);
		z=1;}
		if(bRect== TRUE)//���ƾ���
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
	case WM_DESTROY:		//�����˳�������Ϣ
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
	hWnd=CreateWindow("�����ϰ",				//����������
					"�����ʾʵ������",		 //����������
					WS_OVERLAPPEDWINDOW,	//������ʽ.�б������������С����ť
					CW_USEDEFAULT,			//�������Ͻ�����
					0,
					CW_USEDEFAULT,			//����ȱʡ�ĸ߶ȺͿ��
					0,
					NULL,					//�޸�����
					NULL,					//�޲˵�
					hInstance,				//��ǰӦ��ʵ�����
					NULL);					//ָ�򴫵ݸ����ڵĲ�����ָ��.����
	if(!hWnd)		//����ʧ��.
		return FALSE;
	hWndMain=hWnd;	//��ȫ�ִ��ھ����ֵ.
	ShowWindow(hWnd,nCmdShow);	//��ʾ����
	UpdateWindow(hWnd);			//ˢ���û���
	return TRUE;
}

BOOL InitWindowsClass(HINSTANCE hInstance)
{
	WNDCLASS WndClass;
	WndClass.cbClsExtra=0;			//�޴�������չ
	WndClass.cbWndExtra=0;			//�޴���ʵ����չ
	WndClass.hbrBackground=(HBRUSH)(GetStockObject(WHITE_BRUSH));//����Ϊ��ɫ
	WndClass.hCursor=LoadCursor(NULL,IDC_CROSS);	//���ΪΪ��ͷ
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);	//����ȱʡͼ��
	WndClass.hInstance=hInstance;			//��ǰʵ��
	WndClass.lpfnWndProc=WndProc;			//��Ϣ������
	WndClass.lpszClassName="�����ϰ";			//����������
	WndClass.lpszMenuName=NULL;				//�޲˵�
	WndClass.style=0;						//ȱʡ���ڷ��
	return RegisterClass(&WndClass);	//���ش���ע��ֵ
}