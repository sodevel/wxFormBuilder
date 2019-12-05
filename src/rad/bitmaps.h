///////////////////////////////////////////////////////////////////////////////
//
// wxFormBuilder - A Visual Dialog Editor for wxWidgets.
// Copyright (C) 2005 José Antonio Hurtado
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
// Written by
//   José Antonio Hurtado - joseantonio.hurtado@gmail.com
//   Juan Antonio Ortega  - jortegalalmolda@gmail.com
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/wx.h>
#include <wx/image.h>

class AppBitmaps {
public:
	enum class Size {
		ANY = -1,
		TOOL = 22,
		ICON = 22,
		SMALLICON = 16,
		BIGICON = 32,
	};
	
	static wxBitmap GetBitmap(wxString iconname, Size size = Size::ANY);
	static void LoadBitmaps(wxString filepath, wxString iconpath);
	static wxSize GetScaled(Size size);
	static wxImage GetScaled(const wxImage& image, Size size);
};
