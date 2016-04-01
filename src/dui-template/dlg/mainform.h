#ifndef __CACTUS_MAINFORM_H__
#define __CACTUS_MAINFORM_H__

#include "dui-template/common.h"
#include <DuiLib/Utils/BaseWnd.h>

using namespace DuiLib;

// class C360SafeFrameWnd : public CWindowWnd, public INotifyUI
class C360SafeFrameWnd : public CBaseWnd
{
public:
    C360SafeFrameWnd();;
    LPCTSTR GetWindowClassName() const;;
    UINT GetClassStyle() const;;
    void OnFinalMessage(HWND /*hWnd*/);

    virtual CDuiString GetSkinFolder();
    virtual CDuiString GetSkinFile();

    void Init();

    void OnPrepare();

    void Notify(TNotifyUI& msg);

    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
    CPaintManagerUI m_pm;

private:
    CButtonUI* m_pCloseBtn;
    CButtonUI* m_pMaxBtn;
    CButtonUI* m_pRestoreBtn;
    CButtonUI* m_pMinBtn;
    //...
};

#endif // __CACTUS_MAINFORM_H__
