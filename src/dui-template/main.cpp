#include "dui-template/common.h"
#include "dui-template/dlg/mainform.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
    
    TRACE_CLEAR;
    TRACE_SEND_FORMAT("%s", "hello world!");
    TRACE_FlUSH;


    CPaintManagerUI::SetInstance(hInstance);
    CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin"));
    CPaintManagerUI::SetResourceZip(_T("360SafeRes.zip"));

    HRESULT Hr = ::CoInitialize(NULL);
    if( FAILED(Hr) ) return 0;

    C360SafeFrameWnd* pFrame = new C360SafeFrameWnd();
    if( pFrame == NULL ) return 0;
    pFrame->Create(NULL, _T("360°²È«ÎÀÊ¿"), UI_WNDSTYLE_FRAME, 0L, 0, 0, 800, 572);
    pFrame->CenterWindow();
    ::ShowWindow(*pFrame, SW_SHOW);

    CPaintManagerUI::MessageLoop();

    ::CoUninitialize();

	return TRUE;
}
