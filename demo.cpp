HINSTANCE g_hInstance = 0;  
//���ڴ�������  
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)  
{  
	switch (uMsg)  
	{  
	case WM_DESTROY:  
		PostQuitMessage(0);//����ʹGetMessage����0  
		break; 
	case  WM_CREATE:
	{
		CREATESTRUCT crt = *((CREATESTRUCT*)lParam);
		char buf[256] = {0};
		sprintf(buf,"�����Ĵ�����������%s������������%s",crt.lpszClass,crt.lpszName);
		MessageBox(NULL, buf, "��Ϣ����", MB_OK);
	}
	case WM_QUIT:
	{
		int param = (int)wParam;
		char buf[256];
		sprintf(buf, "�����˳����˳���:%d", param);
		MessageBox(NULL, buf, "��Ϣ����", MB_OK);
	}
	case WM_SYSCOMMAND:
	{
		if (wParam == SC_MAXIMIZE)
		{
			short x = LOWORD(lParam);
			short y = HIWORD(lParam);
			char buf[256];
			sprintf(buf, "������󻯣�x����:%d��y����:%d", x,y);
			MessageBox(NULL, buf, "��Ϣ����", MB_OK);
		}
	}
	case WM_SIZE:
	{
		if (wParam == SIZE_MAXIMIZED)
		{
			short width = LOWORD(lParam);
			short hight = HIWORD(lParam);
			char buf[256];
			sprintf(buf, "������󻯣��߶�:%d������:%d", hight, width);
			MessageBox(NULL, buf, "��Ϣ����", MB_OK);
		}
	}
	default:  
		break;  
	}  
	return DefWindowProc(hWnd, uMsg, wParam, lParam);  
}  
//ע�ᴰ����  
BOOL Register(LPSTR lpClassName, WNDPROC wndProc)  
{  
	WNDCLASSEX wce = { 0 };  
	wce.cbSize = sizeof(wce);  
	wce.cbClsExtra = 0;  
	wce.cbWndExtra = 0;  
	wce.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);  
	wce.hCursor = NULL;  
	wce.hIcon = NULL;  
	wce.hIconSm = NULL;  
	wce.hInstance = g_hInstance;  
	wce.lpfnWndProc = wndProc;  
	wce.lpszClassName = lpClassName;  
	wce.lpszMenuName = NULL;  
	wce.style = CS_HREDRAW | CS_VREDRAW;  
	ATOM nAtom = RegisterClassEx(&wce);  
	if (nAtom == 0)  
		return FALSE;  
	return true;  

}  
//����������  
HWND CreateMain(LPSTR lpClassName, LPSTR lpWndName)  
{  
	HWND hWnd = CreateWindowEx(0, lpClassName, lpWndName,  
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, g_hInstance, NULL);  
	return hWnd;  
}  
//��ʾ����  
void Display(HWND hWnd)  
{  
	ShowWindow(hWnd, SW_SHOW);  
	UpdateWindow(hWnd);  
}  
//��Ϣѭ��  
void Message()  
{  
	MSG nMsg = { 0 };  
	while (GetMessage(&nMsg, NULL, 0, 0))  
	{  
		TranslateMessage(&nMsg);  
		DispatchMessage(&nMsg);  
	}  
}  
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,  
	_In_opt_ HINSTANCE hPrevInstance,  
	_In_ LPWSTR    lpCmdLine,  
	_In_ int       nCmdShow)  
{  
	// TODO: Place code here.  

	g_hInstance = hInstance;  
	BOOL nRet = Register("Main", WndProc);  
	if (!nRet)  
	{  
		MessageBox(NULL, "ע��ʧ��", "Infor", MB_OK);  
		return 0;  
	}  
	HWND hWnd = CreateMain("Main", "window");  
	Display(hWnd);  
	Message();  
	return 0;  
}  