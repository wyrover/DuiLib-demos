#include "dui-template/dlg/mainform.h"
#include "dui-template/dlg/ControlEx.h"

C360SafeFrameWnd::C360SafeFrameWnd()
{

}

LPCTSTR C360SafeFrameWnd::GetWindowClassName() const
{
    return _T("UIMainFrame");
}

UINT C360SafeFrameWnd::GetClassStyle() const
{
    return CS_DBLCLKS;
}

void C360SafeFrameWnd::OnFinalMessage(HWND /*hWnd*/)
{
    delete this;
}

DuiLib::CDuiString C360SafeFrameWnd::GetSkinFolder()
{
    return L"skin";
}

DuiLib::CDuiString C360SafeFrameWnd::GetSkinFile()
{
    return L"skin.xml";
}

void C360SafeFrameWnd::Init()
{
    m_pCloseBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("closebtn")));
    m_pMaxBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("maxbtn")));
    m_pRestoreBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("restorebtn")));
    m_pMinBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("minbtn")));
}

void C360SafeFrameWnd::OnPrepare()
{

}

void C360SafeFrameWnd::Notify(TNotifyUI& msg)
{
    if( msg.sType == _T("windowinit") ) OnPrepare();
    else if( msg.sType == _T("click") ) {
        if( msg.pSender == m_pCloseBtn ) {
            PostQuitMessage(0);
            return; 
        }
        else if( msg.pSender == m_pMinBtn ) { 
            SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); return; }
        else if( msg.pSender == m_pMaxBtn ) { 
            SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0); return; }
        else if( msg.pSender == m_pRestoreBtn ) { 
            SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0); return; }
    }
    else if(msg.sType==_T("selectchanged"))
    {
        CDuiString name = msg.pSender->GetName();
        CTabLayoutUI* pControl = static_cast<CTabLayoutUI*>(m_pm.FindControl(_T("switch")));
        if(name==_T("examine"))
            pControl->SelectItem(0);
        else if(name==_T("trojan"))
            pControl->SelectItem(1);
        else if(name==_T("plugins"))
            pControl->SelectItem(2);
        else if(name==_T("vulnerability"))
            pControl->SelectItem(3);
        else if(name==_T("rubbish"))
            pControl->SelectItem(4);
        else if(name==_T("cleanup"))
            pControl->SelectItem(5);
        else if(name==_T("fix"))
            pControl->SelectItem(6);
        else if(name==_T("tool"))
            pControl->SelectItem(7);
    }
}

LRESULT C360SafeFrameWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
    styleValue &= ~WS_CAPTION;
    ::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

    m_pm.Init(m_hWnd);
    CDialogBuilder builder;
    CDialogBuilderCallbackEx cb;
    CControlUI* pRoot = builder.Create(_T("skin.xml"), (UINT)0,  &cb, &m_pm);
    ASSERT(pRoot && "Failed to parse XML");
    m_pm.AttachDialog(pRoot);
    m_pm.AddNotifier(this);

    Init();
    return 0;
}

LRESULT C360SafeFrameWnd::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    bHandled = FALSE;
    return 0;
}

LRESULT C360SafeFrameWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    ::PostQuitMessage(0L);

    bHandled = FALSE;
    return 0;
}

LRESULT C360SafeFrameWnd::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    if( ::IsIconic(*this) ) bHandled = FALSE;
    return (wParam == 0) ? TRUE : FALSE;
}

LRESULT C360SafeFrameWnd::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    return 0;
}

LRESULT C360SafeFrameWnd::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    return 0;
}

LRESULT C360SafeFrameWnd::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
    ::ScreenToClient(*this, &pt);

    RECT rcClient;
    ::GetClientRect(*this, &rcClient);

    // 		if( !::IsZoomed(*this) ) {
    // 			RECT rcSizeBox = m_pm.GetSizeBox();
    // 			if( pt.y < rcClient.top + rcSizeBox.top ) {
    // 				if( pt.x < rcClient.left + rcSizeBox.left ) return HTTOPLEFT;
    // 				if( pt.x > rcClient.right - rcSizeBox.right ) return HTTOPRIGHT;
    // 				return HTTOP;
    // 			}
    // 			else if( pt.y > rcClient.bottom - rcSizeBox.bottom ) {
    // 				if( pt.x < rcClient.left + rcSizeBox.left ) return HTBOTTOMLEFT;
    // 				if( pt.x > rcClient.right - rcSizeBox.right ) return HTBOTTOMRIGHT;
    // 				return HTBOTTOM;
    // 			}
    // 			if( pt.x < rcClient.left + rcSizeBox.left ) return HTLEFT;
    // 			if( pt.x > rcClient.right - rcSizeBox.right ) return HTRIGHT;
    // 		}

    RECT rcCaption = m_pm.GetCaptionRect();
    if( pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
        && pt.y >= rcCaption.top && pt.y < rcCaption.bottom ) {
            CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));
            if( pControl && _tcscmp(pControl->GetClass(), DUI_CTR_BUTTON) != 0 && 
                _tcscmp(pControl->GetClass(), DUI_CTR_OPTION) != 0 &&
                _tcscmp(pControl->GetClass(), DUI_CTR_TEXT) != 0 )
                return HTCAPTION;
    }

    return HTCLIENT;
}

LRESULT C360SafeFrameWnd::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    SIZE szRoundCorner = m_pm.GetRoundCorner();
    if( !::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0) ) {
        CDuiRect rcWnd;
        ::GetWindowRect(*this, &rcWnd);
        rcWnd.Offset(-rcWnd.left, -rcWnd.top);
        rcWnd.right++; rcWnd.bottom++;
        HRGN hRgn = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom, szRoundCorner.cx, szRoundCorner.cy);
        ::SetWindowRgn(*this, hRgn, TRUE);
        ::DeleteObject(hRgn);
    }

    bHandled = FALSE;
    return 0;
}

LRESULT C360SafeFrameWnd::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    MONITORINFO oMonitor = {};
    oMonitor.cbSize = sizeof(oMonitor);
    ::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
    CDuiRect rcWork = oMonitor.rcWork;
    rcWork.Offset(-oMonitor.rcMonitor.left, -oMonitor.rcMonitor.top);

    LPMINMAXINFO lpMMI = (LPMINMAXINFO) lParam;
    lpMMI->ptMaxPosition.x	= rcWork.left;
    lpMMI->ptMaxPosition.y	= rcWork.top;
    lpMMI->ptMaxSize.x		= rcWork.right;
    lpMMI->ptMaxSize.y		= rcWork.bottom;

    bHandled = FALSE;
    return 0;
}

LRESULT C360SafeFrameWnd::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    // ��ʱ�����յ�WM_NCDESTROY���յ�wParamΪSC_CLOSE��WM_SYSCOMMAND
    if( wParam == SC_CLOSE ) {
        ::PostQuitMessage(0L);
        bHandled = TRUE;
        return 0;
    }
    BOOL bZoomed = ::IsZoomed(*this);
    LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
    if( ::IsZoomed(*this) != bZoomed ) {
        if( !bZoomed ) {
            CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("maxbtn")));
            if( pControl ) pControl->SetVisible(false);
            pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("restorebtn")));
            if( pControl ) pControl->SetVisible(true);
        }
        else {
            CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("maxbtn")));
            if( pControl ) pControl->SetVisible(true);
            pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("restorebtn")));
            if( pControl ) pControl->SetVisible(false);
        }
    }
    return lRes;
}

LRESULT C360SafeFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT lRes = 0;
    BOOL bHandled = TRUE;
    switch( uMsg ) {
    case WM_CREATE:        lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
    case WM_CLOSE:         lRes = OnClose(uMsg, wParam, lParam, bHandled); break;
    case WM_DESTROY:       lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
    case WM_NCACTIVATE:    lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
    case WM_NCCALCSIZE:    lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); break;
    case WM_NCPAINT:       lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); break;
    case WM_NCHITTEST:     lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
    case WM_SIZE:          lRes = OnSize(uMsg, wParam, lParam, bHandled); break;
    case WM_GETMINMAXINFO: lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled); break;
    case WM_SYSCOMMAND:    lRes = OnSysCommand(uMsg, wParam, lParam, bHandled); break;
    default:
        bHandled = FALSE;
    }
    if( bHandled ) return lRes;
    if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;
    return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}
