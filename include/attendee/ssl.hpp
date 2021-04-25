#pragma once

#include <attendee/forward.hpp>

namespace attendee
{
    class ssl_option_handler
    {
    public:
        ssl_option_handler(request* parent);

        // Non Copy, Non Move.
        ssl_option_handler(ssl_option_handler const&) = delete;
        ssl_option_handler(ssl_option_handler&&) = delete;
        ssl_option_handler& operator=(ssl_option_handler&&) = delete;
        ssl_option_handler& operator=(ssl_option_handler const&) = delete;



    private:
        request* parent_request_;
    };
}
