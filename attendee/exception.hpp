#pragma once

/**
 *  Disable exceptions with BOOST_EXCEPTION_DISABLE. If you disable exceptions, you probably also disable boost exceptions anyway.
 */

#include <boost/throw_exception.hpp>

#include <stdexcept>
#include <string>

namespace attendee
{
    #define ATTENDEE_MAKE_EXCEPTION(name) \
    struct name : public std::runtime_error \
    { \
        explicit name(const char* what_arg) \
            : runtime_error(what_arg) \
        { \
        } \
        explicit name(std::string const& what_arg) \
            : runtime_error(what_arg) \
        { \
        } \
    }

    ATTENDEE_MAKE_EXCEPTION(init_curl_error);
    ATTENDEE_MAKE_EXCEPTION(custom_curl_error);
}
