//
// Created by ditto on 3/11/2023.
//

#ifndef LOTUS_BROWSERCLIENT_H
#define LOTUS_BROWSERCLIENT_H

#include <include/cef_client.h>

class RenderHandler;

// for manual render handler
class BrowserClient : public CefClient
{
public:
    BrowserClient(RenderHandler *renderHandler);

    virtual CefRefPtr<CefRenderHandler> GetRenderHandler() {
        return m_renderHandler;
    }

    CefRefPtr<CefRenderHandler> m_renderHandler;

IMPLEMENT_REFCOUNTING(BrowserClient);
};


#endif //LOTUS_BROWSERCLIENT_H
