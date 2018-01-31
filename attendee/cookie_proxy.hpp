#pragma once

#include "forward.hpp"
#include "cookie_iterator.hpp"

#include <functional>

namespace attendee
{
    class cookie_proxy
    {
    public:
        cookie_proxy(response* parent_);
        cookie_iterator begin() const;
        cookie_iterator end() const;

        response& for_each(std::function <void(cookie)> each);

    private:
        response* parent_;
    };
}
