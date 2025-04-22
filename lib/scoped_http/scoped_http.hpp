#pragma once

#include <HTTPClient.h>


class ScopedHTTPClient {
public:
    HTTPClient client;
    bool is_started = false;

    ScopedHTTPClient(const String& url);
    ~ScopedHTTPClient();
};