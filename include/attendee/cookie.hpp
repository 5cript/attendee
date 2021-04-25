#pragma once

#include <string>
#include <chrono>

namespace attendee
{
    struct cookie
    {
        cookie(std::string const& cookie_string);

        std::string domain;
        bool include_subdomains;
        std::string path;
        bool secure;
        std::chrono::seconds expiry_seconds;
        std::string name;
        std::string value;
    };
}
