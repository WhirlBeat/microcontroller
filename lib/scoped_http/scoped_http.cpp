#include "scoped_http.hpp"


ScopedHTTPClient::ScopedHTTPClient(const String& url) {
    this->is_started = client.begin(url);
}

ScopedHTTPClient::~ScopedHTTPClient() {
    if (this->is_started) {
        client.end();
    }
}