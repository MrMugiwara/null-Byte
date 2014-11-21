/* 
 *	Copyright (C) 2009-2010 miaohua
 *	http://code.google.com/p/lrcshower/
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *   
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *   
 *  You should have received a copy of the GNU General Public License
 *  along with GNU Make; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA. 
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */
#include "StdAfx.h"
#include <Windows.h>
#include <string>
#include "HelperFunctions.h"
#include "FilterWinSetting.h"
using namespace std;

FilterWinSetting::FilterWinSetting(const tstring & RegPath)
{
     // Get register path
     m_RegPath = RegPath;
     // Load value from register 
	 if( !DeserializeFromReg() )
	     SetDefaultVal();
}

FilterWinSetting::~FilterWinSetting()
{
	 SerializeToReg();
}

bool FilterWinSetting::SerializeToReg()
{
     // Reg location
     const TCHAR * Path = m_RegPath.c_str();
     // Open the reg key
     DWORD Disp = REG_OPENED_EXISTING_KEY;
     HKEY FilterKey;
     if( RegCreateKeyEx(HKEY_LOCAL_MACHINE, Path, 0, NULL, REG_OPTION_NON_VOLATILE,
         KEY_WRITE, NULL, &FilterKey, &Disp) !=ERROR_SUCCESS )
	     return false;

     // Put key to realse helper
     RegKeyReleaseHelper AutoReleaseFilterKey(FilterKey);

     // Save karaoke mode value
     DWORD ModeBool = m_KaraokeMode;
     if( RegSetValueEx(FilterKey, _T("KaraokeMode") ,NULL, REG_DWORD, (const BYTE*)&ModeBool, sizeof(DWORD)) !=ERROR_SUCCESS )
         return false;

     // Save gradient mode value
     ModeBool = m_GradientMode;
     if( RegSetValueEx(FilterKey, _T("GradientMode") ,NULL, REG_DWORD, (const BYTE*)&ModeBool, sizeof(DWORD)) !=ERROR_SUCCESS )
         return false;

     // Save auto resize mode value
     ModeBool = m_AutoResizeMode;
     if( RegSetValueEx(FilterKey, _T("AutoResizeMode") ,NULL, REG_DWORD, (const BYTE*)&ModeBool, sizeof(DWORD)) !=ERROR_SUCCESS )
         return false;

     // Save window show mode value
     ModeBool = m_WinShow;
     if( RegSetValueEx(FilterKey, _T("WinShowMode") ,NULL, REG_DWORD, (const BYTE*)&ModeBool, sizeof(DWORD)) !=ERROR_SUCCESS )
         return false;

     // Save topmost mode value
     ModeBool = m_TopMostMode;
     if( RegSetValueEx(FilterKey, _T("TopMostMode") ,NULL, REG_DWORD, (const BYTE*)&ModeBool, sizeof(DWORD)) !=ERROR_SUCCESS )
         return false;

     // Save alignment value
     DWORD ModeValue = m_AlignmentOpt;
     if( RegSetValueEx(FilterKey, _T("AlignmentOpt") ,NULL, REG_DWORD, (const BYTE*)&ModeValue, sizeof(DWORD)) !=ERROR_SUCCESS )
         return false;

     // Save alignment value
     ModeValue = m_LrcLineInterval;
     if( RegSetValueEx(FilterKey, _T("LrcLineInterval") ,NULL, REG_DWORD, (const BYTE*)&ModeValue, sizeof(DWORD)) !=ERROR_SUCCESS )
         return false;

     // Save color values
     DWORD Clr = m_BgClr;
     if( RegSetValueEx(FilterKey, _T("BackgroudColor") ,NULL, REG_DWORD, (const BYTE*)&Clr, sizeof(DWORD)) !=ERROR_SUCCESS )
         return false;

     Clr = m_CommClr;
     if( RegSetValueEx(FilterKey, _T("CommLineColor") ,NULL, REG_DWORD, (const BYTE*)&Clr, sizeof(DWORD)) !=ERROR_SUCCESS )
         return false;
     	  		
     Clr = m_FocusClr;
     if( RegSetValueEx(FilterKey, _T("FocusLineColor") ,NULL, REG_DWORD, (const BYTE*)&Clr, sizeof(DWORD)) !=ERROR_SUCCESS )
         return false;

     // Create the font sub key
     Path = _T("LrcFont");
     HKEY FontKey;
     if( RegCreateKeyEx(FilterKey, Path, 0, NULL, REG_OPTION_NON_VOLATILE,
         KEY_WRITE, NULL, &FontKey, &Disp) !=ERROR_SUCCESS )
         return false;

     // Put key to realse helper
     RegKeyReleaseHelper AutoReleaseFontKey(FontKey);

     // Save font property
     DWORD FontProperty = m_LrcFont.lfHeight;
     if( RegSetValueEx(FontKey, _T("FontHeight") ,NULL, REG_DWORD, (const BYTE*)&FontProperty, sizeof(DWORD)) !=ERROR_SUCCESS )
         return false;

     FontProperty = m_LrcFont.lfWidth;
     if( RegSetValueEx(FontKey, _T("FontWidth") ,NULL, REG_DWORD, (const BYTE*)&FontProperty, sizeof(DWORD)) !=ERROR_SUCCESS )
         return false;

     FontProperty = m_LrcFont.lfEscapement;
     if( RegSetValueEx(FontKey, _T("FontEscapement") ,NULL, REG_DWORD, (const BYTE*)&FontProperty, sizeof(DWORD)) !=ERROR_SUCCESS )
         return false;               

     FontProperty = m_LrcFont.lfOrientation; 
     if( RegSetValueEx(FontKey, _T("FontOrientation") ,NULL, REG_DWORD, (const BYTE*)&FontProperty, sizeof(DWORD)) !=ERROR_SUCCESS )
         return false; 

     FontProperty = m_LrcFont.lfWeight; 
     if( RegSetValueEx(FontKey, _T("FontWeight") ,NULL, REG_DWORD, (const BYTE*)&FontProperty, sizeof(DWORD)) !=ERROR_SUCCESS )
         return false; 

     FontProperty = m_LrcFont.lfItalic; 
     if( RegSetValueEx(FontKey, _T("FontItalic") ,NULL, REG_DWORD, (const BYTE*)&FontProperty, sizeof(DWORD)) !=ERROR_SUCCESS )
	     return false; 

     FontProperty = m_LrcFont.lfUnderline; 
     if( RegSetValueEx(FontKey, _T("FontUnderline") ,NULL, REG_DWORD, (const BYTE*)&FontProperty, sizeof(DWORD)) !=ERROR_SUCCESS )
         return false; 

     FontProperty = m_LrcFont.lfStrikeOut; 
     if( RegSetValueEx(FontKey, _T("FontStrikeOut") ,NULL, REG_DWORD, (const BYTE*)&FontProperty, sizeof(DWORD)) !=ERROR_SUCCESS )
         return false; 

     FontProperty = m_LrcFont.lfCharSet; 
     if( RegSetValueEx(FontKey, _T("FontCharSet") ,NULL, REG_DWORD, (const BYTE*)&FontProperty, sizeof(DWORD)) !=ERROR_SUCCESS )
		 return false; 

     FontProperty = m_LrcFont.lfOutPrecision; 
     if( RegSetValueEx(FontKey, _T("FontOutPrecision") ,NULL, REG_DWORD, (const BYTE*)&FontProperty, sizeof(DWORD)) !=ERROR_SUCCESS )
		 return false; 

     FontProperty = m_LrcFont.lfClipPrecision; 
     if( RegSetValueEx(FontKey, _T("FontClipPrecision") ,NULL, REG_DWORD, (const BYTE*)&FontProperty, sizeof(DWORD)) !=ERROR_SUCCESS )
         return false; 

     FontProperty = m_LrcFont.lfQuality; 
     if( RegSetValueEx(FontKey, _T("FontQuality") ,NULL, REG_DWORD, (const BYTE*)&FontProperty, sizeof(DWORD)) !=ERROR_SUCCESS )
         return false; 

     FontProperty = m_LrcFont.lfPitchAndFamily; 
     if( RegSetValueEx(FontKey, _T("FontPitchAndFamily") ,NULL, REG_DWORD, (const BYTE*)&FontProperty, sizeof(DWORD)) !=ERROR_SUCCESS )
         return false; 
#ifdef UNICODE
     DWORD Size = WS2MB(m_LrcFont.lfFaceName).size() + 2;
#else
     DWORD Size = strlen(m_LrcFont.lfFaceName) + 1;
#endif
     if( RegSetValueEx(FontKey, _T("FontFaceName"), NULL, REG_SZ, (const BYTE*)(m_LrcFont.lfFaceName), Size) !=ERROR_SUCCESS )
         return false; 

     // Save reg key values
     RegFlushKey(FontKey);
     RegFlushKey(FilterKey);

     return true; 
}

bool FilterWinSetting::DeserializeFromReg()
{ 
     // Reg location
     const TCHAR * Path = m_RegPath.c_str();
     // Open the reg key
     HKEY FilterKey;
     if( RegOpenKeyEx(HKEY_LOCAL_MACHINE, Path, 0, KEY_READ, &FilterKey) !=ERROR_SUCCESS )
         return false;

     // Put key to realse helper
     RegKeyReleaseHelper AutoReleaseFilterKey(FilterKey);

     // Get karaoke mode value
     DWORD Value = 0, Size = sizeof(DWORD);
     if( RegQueryValueEx(FilterKey, _T("KaraokeMode") ,0, NULL, (BYTE*)&Value, &Size) !=ERROR_SUCCESS )
         return false;
     m_KaraokeMode = (Value != 0);

     // Get gradient mode value
     Value = 0, Size = sizeof(DWORD);
     if( RegQueryValueEx(FilterKey, _T("GradientMode") ,0, NULL, (BYTE*)&Value, &Size) !=ERROR_SUCCESS )
         return false;
      m_GradientMode = (Value != 0);

     // Get auto resize mode value
     Value = 0, Size = sizeof(DWORD);
     if( RegQueryValueEx(FilterKey, _T("AutoResizeMode") ,0, NULL, (BYTE*)&Value, &Size) !=ERROR_SUCCESS )
	     return false;
     m_AutoResizeMode = (Value != 0);

     // Get wether it is in window show mode
     Value = 0, Size = sizeof(DWORD);
     if( RegQueryValueEx(FilterKey, _T("WinShowMode") ,0, NULL, (BYTE*)&Value, &Size) !=ERROR_SUCCESS )
         return false;
     m_WinShow = (Value != 0);
 
     // Get topmost mode value
     Value = 0, Size = sizeof(DWORD);
     if( RegQueryValueEx(FilterKey, _T("TopMostMode") ,0, NULL, (BYTE*)&Value, &Size) !=ERROR_SUCCESS )
         return false;
     m_TopMostMode = (Value != 0);

     // Get alignment value
     Value = 0, Size = sizeof(DWORD);
     if( RegQueryValueEx(FilterKey, _T("AlignmentOpt") ,0, NULL, (BYTE*)&Value, &Size) !=ERROR_SUCCESS )
         return false;
     m_AlignmentOpt = Value;

     // Save alignment value
     Value = 0, Size = sizeof(DWORD);
     if( RegQueryValueEx(FilterKey, _T("LrcLineInterval") ,0, NULL, (BYTE*)&Value, &Size) !=ERROR_SUCCESS )
         return false;
     m_LrcLineInterval = Value;

     // Get color values
     Value = 0, Size = sizeof(DWORD);
     if( RegQueryValueEx(FilterKey, _T("BackgroudColor") ,0, NULL, (BYTE*)&Value, &Size) !=ERROR_SUCCESS )
         return false;
     m_BgClr = Value;

     Value = 0, Size = sizeof(DWORD);
     if( RegQueryValueEx(FilterKey, _T("CommLineColor") ,0, NULL, (BYTE*)&Value, &Size) !=ERROR_SUCCESS )
         return false;
     m_CommClr = Value;

     Value = 0, Size = sizeof(DWORD);
     if( RegQueryValueEx(FilterKey, _T("FocusLineColor") ,0, NULL, (BYTE*)&Value, &Size) !=ERROR_SUCCESS )
         return false;
     m_FocusClr = Value;
				  		
     //  Open the font sub key
     Path = _T("LrcFont");
     HKEY FontKey;
     if( RegOpenKeyEx(FilterKey, Path, 0, KEY_READ, &FontKey) !=ERROR_SUCCESS )
         return false;

     // Put key to realse helper
     RegKeyReleaseHelper AutoReleaseFontKey(FontKey);

     // Get font property
     Value = 0, Size = sizeof(DWORD);
     if( RegQueryValueEx(FontKey, _T("FontHeight") ,0, NULL, (BYTE*)&Value, &Size) !=ERROR_SUCCESS )
         return false;
     m_LrcFont.lfHeight = Value;

     Value = 0, Size = sizeof(DWORD);
     if( RegQueryValueEx(FontKey, _T("FontWidth") ,0, NULL, (BYTE*)&Value, &Size) !=ERROR_SUCCESS )
         return false;
     m_LrcFont.lfWidth = Value;

     Value = 0, Size = sizeof(DWORD);
     if( RegQueryValueEx(FontKey, _T("FontEscapement") ,0, NULL, (BYTE*)&Value, &Size) !=ERROR_SUCCESS )
         return false;
     m_LrcFont.lfEscapement = Value;

     Value = 0, Size = sizeof(DWORD);
     if( RegQueryValueEx(FontKey, _T("FontOrientation") ,0, NULL, (BYTE*)&Value, &Size) !=ERROR_SUCCESS )
         return false;
     m_LrcFont.lfOrientation = Value;

     Value = 0, Size = sizeof(DWORD);
     if( RegQueryValueEx(FontKey, _T("FontWeight") ,0, NULL, (BYTE*)&Value, &Size) !=ERROR_SUCCESS )
         return false;
     m_LrcFont.lfWeight = Value;

     Value = 0, Size = sizeof(DWORD);
     if( RegQueryValueEx(FontKey, _T("FontItalic") ,0, NULL, (BYTE*)&Value, &Size) !=ERROR_SUCCESS )
         return false;
     m_LrcFont.lfItalic = (BYTE)Value;

     Value = 0, Size = sizeof(DWORD);
     if( RegQueryValueEx(FontKey, _T("FontUnderline") ,0, NULL, (BYTE*)&Value, &Size) !=ERROR_SUCCESS )
         return false;
     m_LrcFont.lfUnderline = (BYTE)Value;

     Value = 0, Size = sizeof(DWORD);
     if( RegQueryValueEx(FontKey, _T("FontStrikeOut") ,0, NULL, (BYTE*)&Value, &Size) !=ERROR_SUCCESS )
         return false;
     m_LrcFont.lfStrikeOut = (BYTE)Value;

     Value = 0, Size = sizeof(DWORD);
     if( RegQueryValueEx(FontKey, _T("FontCharSet") ,0, NULL, (BYTE*)&Value, &Size) !=ERROR_SUCCESS )
         return false;
     m_LrcFont.lfCharSet = (BYTE)Value;

     Value = 0, Size = sizeof(DWORD);
     if( RegQueryValueEx(FontKey, _T("FontClipPrecision") ,0, NULL, (BYTE*)&Value, &Size) !=ERROR_SUCCESS )
         return false;
     m_LrcFont.lfClipPrecision = (BYTE)Value;

     Value = 0, Size = sizeof(DWORD);
     if( RegQueryValueEx(FontKey, _T("FontQuality") ,0, NULL, (BYTE*)&Value, &Size) !=ERROR_SUCCESS )
         return false;
     m_LrcFont.lfQuality = (BYTE)Value;		  

     Value = 0, Size = sizeof(DWORD);
     if( RegQueryValueEx(FontKey, _T("FontPitchAndFamily") ,0, NULL, (BYTE*)&Value, &Size) !=ERROR_SUCCESS )
         return false;
     m_LrcFont.lfPitchAndFamily = (BYTE)Value;

     Size = sizeof(m_LrcFont.lfFaceName);
     if( RegQueryValueEx(FontKey, _T("FontFaceName") ,0, NULL, (BYTE*)(m_LrcFont.lfFaceName), &Size) !=ERROR_SUCCESS )
         return false; 

	 return true; 
}

bool FilterWinSetting::SerializeToXML(){ return true; }
bool FilterWinSetting::DeserializeFromXML(){ return true; }
void FilterWinSetting::SetDefaultVal()
{
      m_KaraokeMode = true;
	  m_GradientMode = true;
	  m_AutoResizeMode = false;
      m_TopMostMode = false;
      m_WinShow = true;
	  m_AlignmentOpt = 0;
	  m_LrcLineInterval = 8;
	  m_BgClr = RGB(24,51,60);
	  m_CommClr = RGB(84,142,165);
	  m_FocusClr = RGB(212,245,255);
	  m_LrcShowWin = NULL;

	  HDC DeskDC = GetDC(NULL);
	  m_LrcFont.lfHeight = -MulDiv(10, GetDeviceCaps(DeskDC, LOGPIXELSY), 72);        //Ð¡Îå
	  _tcscpy_s(m_LrcFont.lfFaceName, _countof(m_LrcFont.lfFaceName), TEXT("ËÎÌå"));
      m_LrcFont.lfCharSet = GB2312_CHARSET; 	 
	  ReleaseDC(NULL, DeskDC);
}
