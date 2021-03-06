#ifndef MYSERVER_H
#define MYSERVER_H

#include "cpprest/json.h"
#include "cpprest/http_listener.h"
#include "cpprest/uri.h"
#include "cpprest/asyncrt_utils.h"

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

class MyServer
{
public:
    MyServer(){}
    MyServer(utility::string_t url);
    pplx::task<void> open(){return m_listener.open();}
    pplx::task<void> close(){return m_listener.close();}
private:
    void handle_get(http_request message);
    void handle_post(http_request message);
    void handle_patch(http_request message);
    http_listener m_listener;
};

#endif // MYSERVER_H
