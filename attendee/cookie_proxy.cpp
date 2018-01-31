#include "cookie_proxy.hpp"
#include "response.hpp"

namespace attendee
{
//#####################################################################################################################
    cookie_proxy::cookie_proxy(response* parent_)
        : parent_{parent_}
    {

    }
//---------------------------------------------------------------------------------------------------------------------
    cookie_iterator cookie_proxy::begin() const
    {
        if (parent_->set_cookies_)
            return cookie_iterator{parent_->set_cookies_.get()};
        else
            return end();
    }
//---------------------------------------------------------------------------------------------------------------------
    response& cookie_proxy::for_each(std::function <void(cookie)> each)
    {
        for (auto i = begin(); i != end(); ++i)
            each(*i);
        return *parent_;
    }
//---------------------------------------------------------------------------------------------------------------------
    cookie_iterator cookie_proxy::end() const
    {
        return cookie_iterator{nullptr};
    }
//#####################################################################################################################
}
