/*
 * ETERFORCETEST
 *
 * Copyright 2008 Vitaly Lipatov, Etersoft
 * Copyright 2008 Ilya Shpigor, Etersoft
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

LRESULT CALLBACK msg_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

BOOL msg_RegisterWindowClasses(void)
{
    WNDCLASSA cls;

    cls.style = CS_DBLCLKS;
    cls.lpfnWndProc = msg_WndProc;
    cls.cbClsExtra = 0;
    cls.cbWndExtra = 0;
    cls.hInstance = GetModuleHandleA(0);
    cls.hIcon = 0;
    cls.hCursor = LoadCursorA(0, (LPSTR)IDC_ARROW);
    cls.hbrBackground = GetStockObject(WHITE_BRUSH);
    cls.lpszMenuName = NULL;
    cls.lpszClassName = "WinMsg";

    if(!RegisterClassA(&cls)) return FALSE;

    return TRUE;
}

void test_message()
{
    HWND hwnd;
    DWORD ok;

    printf("\n\n* * *  Message operations  * * *\n");

    if (!msg_RegisterWindowClasses()) return;

    hwnd = CreateWindowEx( 0, "WinMsg", "Test window",
                            WS_OVERLAPPED | WS_CAPTION,
                            100, 100, 100, 100,
                            0, 0, GetModuleHandle(0), NULL );

    ok = SendMessageA( hwnd, WM_QUERYOPEN, 0, 0 );
    MSTART(ok, "SendMessageA", 10) {
        SendMessageA( hwnd, WM_QUERYOPEN, 0, 0 );
    } MEND

    ok = SendMessageW( hwnd, WM_QUERYOPEN, 0, 0 );
    MSTART(ok, "SendMessageW", 10) {
        SendMessageW( hwnd, WM_QUERYOPEN, 0, 0 );
    } MEND

    DestroyWindow(hwnd);
}
