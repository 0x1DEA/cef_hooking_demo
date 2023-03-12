//
// Created by ditto on 3/12/2023.
//

#ifndef LOTUS_WEBAPP_H
#define LOTUS_WEBAPP_H


#include "include/cef_app.h"

class WebApp: public CefApp {
public:
    void WebApp::OnBeforeCommandLineProcessing();

};


#endif //LOTUS_WEBAPP_H
