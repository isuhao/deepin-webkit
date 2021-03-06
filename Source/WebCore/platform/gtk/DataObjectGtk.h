/*
 * Copyright (C) 2009, Martin Robinson
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef DataObjectGtk_h
#define DataObjectGtk_h

#include "FileList.h"
#include <GRefPtr.h>
#include "KURL.h"
#include "Range.h"
#include <wtf/RefCounted.h>
#include <wtf/text/CString.h>
#include <wtf/text/StringHash.h>

namespace WebCore {

class DataObjectGtk : public RefCounted<DataObjectGtk> {
public:
    static PassRefPtr<DataObjectGtk> create()
    {
        DataObjectGtk* d = new DataObjectGtk();
        d->m_has_xds = false;
        return adoptRef(d);
    }

    const KURL& url() const { return m_url; }
    const String& uriList() const { return m_uriList; }
    const Vector<String>& filenames() const { return m_filenames; }
    GdkPixbuf* image() const { return m_image.get(); }
    void setRange(PassRefPtr<Range> newRange) { m_range = newRange; }
    void setImage(GdkPixbuf* newImage) { m_image = newImage; }
    void setURL(const KURL&, const String&);
    bool hasCustom() const { return m_custom.size() != 0; }
    bool hasXDS() const { return m_has_xds; }
    bool hasText() const { return m_range || !m_text.isEmpty(); }
    bool hasMarkup() const { return m_range || !m_markup.isEmpty(); }
    bool hasURIList() const { return !m_uriList.isEmpty(); }
    bool hasURL() const { return !m_url.isEmpty() && m_url.isValid(); }
    bool hasFilenames() const { return !m_filenames.isEmpty(); }
    bool hasImage() const { return m_image; }
    void clearURIList() { m_uriList = ""; }
    void clearURL() { m_url = KURL(); }
    void clearImage() { m_image = 0; }

    String text() const;
    String markup() const;
    String XDS() const;
    void setCustoms(const String& data);
    String getCustoms() const;
    String getCustom(const String& k) const;
    //void setCustom(const String& v);
    void setCustom(const String& k, const String& v);
    void setXDS(const String&, bool internal=true);
    void setText(const String&);
    void setMarkup(const String&);
    void setURIList(const String&);
    String urlLabel() const;

    void clearAllExceptFilenames();
    void clearAll();
    void clearText();
    void clearMarkup();

    static DataObjectGtk* forClipboard(GtkClipboard*);

private:
    Vector<String> m_custom;
    String m_xds;
    bool m_has_xds;
    String m_text;
    String m_markup;
    KURL m_url;
    String m_uriList;
    Vector<String> m_filenames;
    GRefPtr<GdkPixbuf> m_image;
    RefPtr<Range> m_range;
};

}

#endif // DataObjectGtk_h
