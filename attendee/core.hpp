#pragma once

#include <curl/curl.h>

namespace attendee
{
    /**
     *  This class calls curl_global_init and curl_global_cleanup.
     *  If you really need curl_global_init_mem, ditch this class and call it yourself.
     */
    class system_context
    {
    public:
        system_context(long curl_global_flags = CURL_GLOBAL_DEFAULT);
        ~system_context();
    };
}
