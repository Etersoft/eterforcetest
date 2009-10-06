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

#define _WIN32_WINNT 0X500

#include <windows.h>
#include "eterforcetest.h"

void test_font()
{
    HDC hdc;
    DWORD dwGlyphSize;
    GLYPHSET *pSet;
    HFONT hf, phf;
    LOGFONT lf = { -12, 0, 0, 0, 0, 0, 0, 0, ANSI_CHARSET,
                    0, 0, 0, 0, "Arial" };
    DWORD ok;

    printf("\n\n* * *  Font operations  * * *\n");


    hdc = CreateCompatibleDC(NULL);

    hf = CreateFontIndirect(&lf);
    phf = SelectObject(hdc, hf);
    dwGlyphSize = GetFontUnicodeRanges( hdc, NULL );
    pSet = HeapAlloc(GetProcessHeap(), 0, dwGlyphSize);
    if (!pSet) return;
    pSet->cbThis = dwGlyphSize;

    ok = (DWORD)GetFontUnicodeRanges( hdc, pSet);
    MSTART(ok, "GetFontUnicodeRanges (ANSI_CHARSET)", 500) {
        GetFontUnicodeRanges( hdc, pSet);
    } MEND

    HeapFree(GetProcessHeap(), 0, pSet);
    SelectObject(hdc, phf);
    DeleteObject(hf);

    lf.lfCharSet = SYMBOL_CHARSET;
    hf = CreateFontIndirect(&lf);
    phf = SelectObject(hdc, hf);
    dwGlyphSize = GetFontUnicodeRanges( hdc, NULL );
    pSet = HeapAlloc(GetProcessHeap(), 0, dwGlyphSize);
    if (!pSet) return;
    pSet->cbThis = dwGlyphSize;

    ok = (DWORD)GetFontUnicodeRanges( hdc, pSet);
    MSTART(ok, "GetFontUnicodeRanges (SYMBOL_CHARSET)", 500) {
        GetFontUnicodeRanges( hdc, pSet);
    } MEND

    HeapFree(GetProcessHeap(), 0, pSet);
    SelectObject(hdc, phf);
    DeleteObject(hf);

    DeleteDC(hdc);
}
