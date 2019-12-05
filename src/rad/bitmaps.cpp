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

#include "bitmaps.h"

#include "../utils/stringutils.h"
#include "../utils/typeconv.h"
#include "../utils/wxfbexception.h"

#include <default.xpm>
#include <ticpp.h>
#include <wx/app.h>

static std::map<wxString, wxBitmap> m_bitmaps;

wxBitmap AppBitmaps::GetBitmap(wxString iconname, Size size) {
	std::map<wxString, wxBitmap>::iterator bitmap;
	bitmap = m_bitmaps.find(iconname);
	wxBitmap bmp;
	if (bitmap != m_bitmaps.end()) {
		bmp = m_bitmaps[iconname];
	} else {
		bmp = m_bitmaps[wxT("unknown")];
	}
	if (size != Size::ANY) {
		const auto scaled = GetScaled(size);
		if (bmp.GetSize() != scaled) {
			const auto image = bmp.ConvertToImage();
			bmp = image.Scale(scaled.GetWidth(), scaled.GetHeight());
		}
	}
	return bmp;
}

void AppBitmaps::LoadBitmaps(wxString filepath, wxString iconpath) {
	try {
		m_bitmaps[wxT("unknown")] = wxBitmap(default_xpm);

		ticpp::Document doc;
		XMLUtils::LoadXMLFile(doc, true, filepath);

		ticpp::Element* root = doc.FirstChildElement("icons");
		ticpp::Element* elem = root->FirstChildElement("icon", false);
		while (elem) {
			wxString name = _WXSTR(elem->GetAttribute("name"));
			wxString file = _WXSTR(elem->GetAttribute("file"));
			m_bitmaps[name] = wxBitmap(iconpath + file, wxBITMAP_TYPE_ANY);

			elem = elem->NextSiblingElement("icon", false);
		}
	} catch (ticpp::Exception& ex) {
		wxLogError(_("Error loading images: %s"), _WXSTR(ex.m_details).c_str());
	} catch (wxFBException& ex) {
		wxLogError(_("Error loading images: %s"), ex.what());
	}
}

wxSize AppBitmaps::GetScaled(Size size) {
	return wxWindow::FromDIP(wxSize(static_cast<int>(size), static_cast<int>(size)), wxTheApp->GetTopWindow());
}

wxImage AppBitmaps::GetScaled(const wxImage& image, Size size) {
	const auto scaled = GetScaled(size);
	if (image.GetSize() != scaled) {
		return image.Scale(scaled.GetWidth(), scaled.GetHeight());
	} else {
		return image;
	}
}


#if 0
// We consider 96 DPI to be the standard value, this is correct at least for
// MSW, but could conceivably need adjustment for the other platforms.
static const int BASELINE_DPI = 96;

static wxSize GetDPIHelper(const wxWindowBase* w) {
	wxSize dpi;

	if (w) dpi = w->GetDPI();
	if (!dpi.x || !dpi.y) dpi = wxScreenDC().GetPPI();
	if (!dpi.x || !dpi.y) dpi = wxSize(BASELINE_DPI, BASELINE_DPI);

	return dpi;
}

double wxWindowBase::GetContentScaleFactor() const {
	const wxSize dpi = GetDPIHelper(this);

	// We use just the vertical component of the DPI because it's the one
	// that counts most and, in practice, it's equal to the horizontal one
	// anyhow.
	return dpi.y / (double)BASELINE_DPI;
}

/* static */
wxSize wxWindowBase::FromDIP(const wxSize& sz, const wxWindowBase* w) {
	const wxSize dpi = GetDPIHelper(w);

	// Take care to not scale -1 because it has a special meaning of
	// "unspecified" which should be preserved.
	return wxSize(sz.x == -1 ? -1 : wxMulDivInt32(sz.x, dpi.x, BASELINE_DPI),
	              sz.y == -1 ? -1 : wxMulDivInt32(sz.y, dpi.y, BASELINE_DPI));
}

/* static */
wxSize wxWindowBase::ToDIP(const wxSize& sz, const wxWindowBase* w) {
	const wxSize dpi = GetDPIHelper(w);

	// Take care to not scale -1 because it has a special meaning of
	// "unspecified" which should be preserved.
	return wxSize(sz.x == -1 ? -1 : wxMulDivInt32(sz.x, BASELINE_DPI, dpi.x),
	              sz.y == -1 ? -1 : wxMulDivInt32(sz.y, BASELINE_DPI, dpi.y));
}
#endif
