#include <iostream>
#include <fstream>
#include "include/cef_client.h"
#include "include/cef_app.h"

int main(int argc, char* argv[]) {
    CefMainArgs main_args(GetModuleHandle(nullptr));

    std::ofstream log;
    log.open("subproc.txt", std::ios::out | std::ios::app);
    for (int i = 0; i < argc; ++i) {
        log << "Argument " << i << ": " << argv[i] << std::endl;
    }
    log.close();

    //CefRefPtr<MyApp> app(new MyApp);

    return CefExecuteProcess(main_args, nullptr, nullptr);
}