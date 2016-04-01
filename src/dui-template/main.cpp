#include "dui-template/common.h"
#include "dui-template/dlg/mainform.h"
#include <boost/smart_ptr.hpp>

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
    int retval = 0;
    do 
    {
        TRACE_CLEAR;
        TRACE_SEND_FORMAT("%s", "hello world!");
        TRACE_FlUSH;


        CPaintManagerUI::SetInstance(hInstance);
        CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin"));
        CPaintManagerUI::SetResourceZip(_T("360SafeRes.zip"));

        HRESULT Hr = ::CoInitialize(NULL);
        if( FAILED(Hr)) {
            retval = 0;
            break;
        }

        boost::scoped_ptr<C360SafeFrameWnd> pFrame(new C360SafeFrameWnd());
        if ( pFrame == NULL ) {
            retval = 0;
            break;
        }
           
        pFrame->Create((HWND)NULL, _T("360°²È«ÎÀÊ¿"), UI_WNDSTYLE_FRAME, NULL);
        pFrame->CenterWindow();
        ::ShowWindow(*pFrame, SW_SHOW);

        CPaintManagerUI::MessageLoop();

    } while (0);
    
    

    ::CoUninitialize();

	return retval;
}
