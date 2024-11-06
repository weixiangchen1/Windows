#include <Windows.h>
#include <stdio.h>

LPCTSTR clsName = "MyWindowClass";
LPCTSTR msgName = "MyWindow";

LRESULT CALLBACK MyWinProc(
    HWND hwnd,                  // 窗口句柄
    UINT uMsg,                  // 消息类型
    WPARAM wParam,              // 其他消息
    LPARAM lParam               // 其他消息
);

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	/*
	 1.定义和配置窗口对象
     typedef struct tagWNDCLASS {
        UINT        style;              // 类样式
        WNDPROC     lpfnWndProc;        // 指向窗口过程的回调函数指针
        int         cbClsExtra;         // 要根据窗口类结构分配的额外字节数 系统将字节初始化为零
        int         cbWndExtra;         // 在窗口实例之后分配的额外字节数 系统将字节初始化为零
        HINSTANCE   hInstance;          // 实例的句柄，该实例包含类的窗口过程
        HICON       hIcon;              // 类图标的句柄
        HCURSOR     hCursor;            // 类游标的句柄 此成员必须是游标资源的句柄
        HBRUSH      hbrBackground;      // 类背景画笔的句柄
        LPCWSTR     lpszMenuName;       // 类菜单的资源名称
        LPCWSTR     lpszClassName;
    } 
    */
	WNDCLASS wndcls;
    wndcls.style = CS_HREDRAW | CS_VREDRAW;     // 如果窗口高度和宽度改变，重绘整个窗口
    wndcls.lpfnWndProc = MyWinProc;
    wndcls.cbClsExtra = NULL;
    wndcls.cbWndExtra = NULL;
    wndcls.hInstance = hInstance;
    wndcls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndcls.lpszMenuName = NULL;
    wndcls.lpszClassName = clsName;

    /*
    * 2. 注册窗口类
    */
    RegisterClass(&wndcls);

    /*
    * 3. 创建窗口
    * HWND CreateWindow(
         LPCWSTR   lpClassName,         // 上一次调用RegisterClass函数创建的类原子
         LPCWSTR   lpWindowName,        // 窗口名称
         DWORD     dwStyle,             // 正在创建的窗口的样式
         int       x,                   // 窗口的初始水平位置
         int       y,                   // 窗口的初始垂直位置
         int       nWidth,              // 窗口的宽度
         int       nHeight,             // 窗口的高度
         HWND      hWndParent,          // 正在创建的窗口的父窗口或所有者窗口的句柄
         HMENU     hMenu,               // 菜单的句柄或根据窗口样式指定子窗口标识符
         HINSTANCE hInstance,           // 要与窗口关联的模块实例的句柄
         LPVOID    lpParam              // 指向通过 CREATESTRUCT 结构（lpCreateParams 成员）指向的值的指针
);
    */
    HWND hwnd;
    hwnd = CreateWindow(clsName, msgName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    /*
    * 4. 显示和刷新窗口
    */
    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    /*
    * 5. 消息循环 
    *    GetMessage只有收到WM_QUIT消息才会返回0
    *    TranslateMessage 翻译消息
    */
    MSG msg;
    while (GetMessage(&msg, NULL, NULL, NULL))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}


LRESULT CALLBACK MyWinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int iRet;
    HDC hdc;
    switch (uMsg)
    {
    case WM_CHAR:
        char szMsg[20];
        sprintf_s(szMsg, "touch: %c", wParam);
        MessageBox(hwnd, szMsg, "char", NULL);
        break;

    case WM_PAINT:
        PAINTSTRUCT ps;
        hdc = BeginPaint(hwnd, &ps);
        TextOut(hdc, 0, 0, "www.bing.com", strlen("www.bing.com"));
        EndPaint(hwnd, &ps);
        MessageBox(hwnd, "paint", "msg", NULL);
        break;

    case WM_CLOSE:
        iRet = MessageBox(hwnd, "Really Close?", "msg", NULL);
        if (iRet == IDYES)
        {
            DestroyWindow(hwnd);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}