#ifndef __DEEPIN_MENU_ITEM__
#define __DEEPIN_MENU_ITEM__

#include "PlatformString.h"
#include <RefCounted.h>
#include <PassRefPtr.h>

namespace WebCore {
    class DeepinMenu;

    class DeepinMenuItem : public RefCounted<DeepinMenuItem> {
        public:
            static PassRefPtr<DeepinMenuItem> create(int type, unsigned short id, const String& title, DeepinMenu* data) {
                if (type == 0) {
                    return adoptRef(new DeepinMenuItem(title, id));
                } else {
                    return adoptRef(new DeepinMenuItem(title, data));
                }
            }

            const String& title() { return m_title; }
            void setTitle(const String& t) { m_title = t; }

            unsigned short id() { return m_id; }

            int type() { return m_type; }

            DeepinMenu* submenu() { return m_submenu; }
            ~DeepinMenuItem();

        private:
            DeepinMenuItem(const String& title, unsigned short id);
            DeepinMenuItem(const String& title, DeepinMenu* menu);

            String m_title;
            unsigned short m_id;
            int m_type;
            DeepinMenu *m_submenu;
    };
}


#endif
