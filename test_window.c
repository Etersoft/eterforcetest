/*
 * ETERFORCETEST
 *
 * Copyright 2008 Vitaly Lipatov, Etersoft
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include <windows.h>
#include "eterforcetest.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
 switch (message)
 {
    case WM_QUERYOPEN:
        return TRUE;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
 }

 return 0;
}

BOOL RegisterWindowClasses(void)
{
    WNDCLASSA cls;

    cls.style = CS_DBLCLKS;
    cls.lpfnWndProc = WndProc;
    cls.cbClsExtra = 0;
    cls.cbWndExtra = 0;
    cls.hInstance = GetModuleHandleA(0);
    cls.hIcon = 0;
    cls.hCursor = LoadCursorA(0, (LPSTR)IDC_ARROW);
    cls.hbrBackground = GetStockObject(WHITE_BRUSH);
    cls.lpszMenuName = NULL;
    cls.lpszClassName = "Win";

    if(!RegisterClassA(&cls)) return FALSE;

    return TRUE;
}

void test_window()
{
    HWND hwnd, child, child2;
    WNDPROC wndproc;
    RECT rc;
    DWORD ok;

    printf("\n\n* * *  Window operations  * * *\n");

    if (!RegisterWindowClasses()) return;

    hwnd = CreateWindowEx( 0, "Win", "Test window",
                            WS_OVERLAPPED | WS_CAPTION,
                            100, 100, 100, 100,
                            0, 0, GetModuleHandle(0), NULL );

    child = CreateWindowEx( 0, "Win", "Child window",
                            WS_CHILD,
                            100, 100, 100, 100,
                            hwnd, 0, GetModuleHandle(0), NULL );

    ok = (DWORD)GetParent( child );
    MSTART(ok, "GetParent", 6) {
        GetParent( hwnd );
    } MEND

    wndproc = (WNDPROC)GetWindowLongPtrA( hwnd, GWLP_WNDPROC );
    ok = CallWindowProcA( wndproc, hwnd, WM_QUERYOPEN, 0, 0 );
    MSTART(ok, "CallWindowProcA", 6) {
        CallWindowProcA( wndproc, hwnd, WM_QUERYOPEN, 0, 0 );
    } MEND

    child2 = CreateWindowEx( 0, "Win", "Child window",
                            WS_CHILD,
                            100, 100, 100, 100,
                            hwnd, 0, GetModuleHandle(0), NULL );

    /* Wine calls the GetWindow(hwnd, GW_CHILD) for GetTopWindow */
    ok = (DWORD)GetTopWindow( hwnd );
    MSTART(ok, "GetTopWindow", 20) {
        GetTopWindow( hwnd );
    } MEND

    ok = (DWORD)GetWindow( child, GW_HWNDNEXT );
    MSTART(ok, "GetWindow", 20) {
        GetWindow( child, GW_HWNDNEXT );
    } MEND

    ok = IsChild( hwnd, child2 );
    MSTART(ok, "IsChild", 10) {
        IsChild( hwnd, child2 );
    } MEND

    DestroyWindow( child2 );

    ok = GetWindowLongA( hwnd, GWL_STYLE );
    MSTART(ok, "GetWindowLongA", 10) {
        GetWindowLongA( hwnd, GWL_STYLE );
    } MEND

    ok = GetWindowLongW( hwnd, GWL_STYLE );
    MSTART(ok, "GetWindowLongW", 10) {
        GetWindowLongW( hwnd, GWL_STYLE );
    } MEND

    ShowWindow( hwnd, SW_SHOW );
    ok = (DWORD)GetFocus();
    MSTART(ok, "GetFocus", 20) {
        GetFocus();
    } MEND

    /* Wine calls the GetWindowLongW(hwnd, GWL_STYLE) for IsWindowVisible usually */
    ok = IsWindowVisible( hwnd );
    MSTART(ok, "IsWindowVisible", 20) {
        IsWindowVisible( hwnd );
    } MEND
    ShowWindow( hwnd, SW_HIDE );

    ok = IsWindow( hwnd );
    MSTART(ok, "IsWindow", 6) {
        IsWindow( hwnd );
    } MEND

    ok = GetClientRect( hwnd, &rc );
    MSTART(ok, "GetClientRect", 6) {
        GetClientRect( hwnd, &rc );
    } MEND

    ok = GetWindowRect( hwnd, &rc );
    MSTART(ok, "GetWindowRect", 6) {
        GetWindowRect( hwnd, &rc );
    } MEND

    DestroyWindow(child);
    DestroyWindow(hwnd);
}
