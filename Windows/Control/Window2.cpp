// Windows/Control/Window2.cpp

#include "StdAfx.h"

#include "Windows/Control/Window2.h"

// extern HINSTANCE g_hInstance;

namespace NWindows {
namespace NControl {

static LRESULT CALLBACK WindowProcedure(HWND aHWND, UINT message, 
    WPARAM wParam, LPARAM lParam)
{
  CWindow tempWindow(aHWND);
  if (message == WM_NCCREATE)
    tempWindow.SetUserDataLongPtr(
        LONG_PTR(((LPCREATESTRUCT)lParam)->lpCreateParams));
  CWindow2 *window = (CWindow2*)(tempWindow.GetUserDataLongPtr());
  if (window == NULL)
    return FALSE;
  if (message == WM_NCCREATE)
    window->Attach(aHWND);
  if (window == 0)
    return DefWindowProc(aHWND, message, wParam, lParam);
  return window->OnMessage(message, wParam, lParam);
}

bool CWindow2::CreateEx(DWORD exStyle, LPCTSTR className, 
      LPCTSTR windowName, DWORD style,
      int x, int y, int width, int height,
      HWND parentWindow, HMENU idOrHMenu, 
      HINSTANCE instance)
{
  WNDCLASS windowClass;
  if(!::GetClassInfo(instance, className, &windowClass))
  {
    // windowClass.style          = CS_HREDRAW | CS_VREDRAW;
    windowClass.style          = 0;

    windowClass.lpfnWndProc    = WindowProcedure;
    windowClass.cbClsExtra     = NULL;
    windowClass.cbWndExtra     = NULL;
    windowClass.hInstance      = instance;
    windowClass.hIcon          = NULL;
    windowClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    windowClass.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    windowClass.lpszMenuName   = NULL;
    windowClass.lpszClassName  = className;
    if (::RegisterClass(&windowClass) == 0)
      return false;
  }
  return CWindow::CreateEx(exStyle, className, windowName,
      style, x, y, width, height, parentWindow, 
      idOrHMenu, instance, this);
}

LRESULT CWindow2::OnMessage(UINT message, UINT wParam, LPARAM lParam)
{
  LRESULT result;
  switch (message)
  {
    case WM_CREATE:
      if (!OnCreate((CREATESTRUCT *)lParam))
        return -1;
      break;
    case WM_COMMAND:
      if (OnCommand(wParam, lParam, result))
        return result;
      break;
    case WM_NOTIFY:
      if (OnNotify(wParam, (LPNMHDR) lParam, result))
        return result;
      break;
		case WM_DESTROY:
			OnDestroy();
      break;
    case WM_CLOSE:
      OnClose();
      return 0;
    case WM_SIZE:
      if (OnSize(wParam, LOWORD(lParam), HIWORD(lParam)))
        return 0;
  }
  return DefProc(message, wParam, lParam);
}

bool CWindow2::OnCommand(WPARAM wParam, LPARAM lParam, LRESULT &result) 
{ 
  return OnCommand(HIWORD(wParam), LOWORD(wParam), lParam, result);
}

bool CWindow2::OnCommand(int code, int itemID, LPARAM lParam, LRESULT &result)
{
  return false;
  // return DefProc(message, wParam, lParam);
  /*
  if (code == BN_CLICKED)
    return OnButtonClicked(itemID, (HWND)lParam);
  */
}

/*
bool CDialog::OnButtonClicked(int buttonID, HWND buttonHWND) 
{ 
  switch(aButtonID)
  {
    case IDOK:
      OnOK();
      break;
    case IDCANCEL:
      OnCancel();
      break;
    case IDHELP:
      OnHelp();
      break;
    default:
      return false;
  }
  return true;
}

*/

}}