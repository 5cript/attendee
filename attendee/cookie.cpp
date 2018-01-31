#include "cookie.hpp"

namespace attendee
{
//#####################################################################################################################
    cookie::cookie(std::string const& cookie_string)
    {
        int auto_offset = 0;
        auto read_upto_tab = [&]() -> std::string
        {
            std::string result;
            std::size_t i = auto_offset;
            for (; i < cookie_string.length(); ++i)
            {
                auto& c = cookie_string[i];
                if (c == '\t')
                {
                    ++i;
                    break;
                }
                else
                    result.push_back(c);
            }
            auto_offset = i;
            return result;
        };

        domain = read_upto_tab();
        include_subdomains = (read_upto_tab() == "TRUE");
        path = read_upto_tab();
        secure = (read_upto_tab() == "TRUE");
        {
            auto seconds_str = read_upto_tab();
            if (!seconds_str.empty())
                expiry_seconds = std::chrono::seconds{std::stoll(seconds_str)};
        }
        name = read_upto_tab();
        value = read_upto_tab();
    }
//#####################################################################################################################
}
