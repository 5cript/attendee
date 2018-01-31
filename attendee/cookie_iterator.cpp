#include "cookie_iterator.hpp"

namespace attendee
{
//#####################################################################################################################
    cookie_iterator::cookie_iterator(curl_slist* cookies)
        : cookies_{cookies}
    {

    }
//---------------------------------------------------------------------------------------------------------------------
    void swap(cookie_iterator& lhs, cookie_iterator& rhs)
    {
        lhs.swap(rhs);
    }
//---------------------------------------------------------------------------------------------------------------------
    void cookie_iterator::swap(cookie_iterator& other)
    {
        std::swap(cookies_, other.cookies_);
    }
//---------------------------------------------------------------------------------------------------------------------
    cookie cookie_iterator::operator*()
    {
        return {cookies_->data};
    }
//---------------------------------------------------------------------------------------------------------------------
    cookie cookie_iterator::operator*() const
    {
        return {cookies_->data};
    }
//---------------------------------------------------------------------------------------------------------------------
    cookie cookie_iterator::operator->()
    {
        return {cookies_->data};
    }
//---------------------------------------------------------------------------------------------------------------------
    cookie cookie_iterator::operator->() const
    {
        return {cookies_->data};
    }
//---------------------------------------------------------------------------------------------------------------------
    bool cookie_iterator::operator==(cookie_iterator const& other) const
    {
        return cookies_ == other.cookies_;
    }
//---------------------------------------------------------------------------------------------------------------------
    bool cookie_iterator::operator!=(cookie_iterator const& other) const
    {
        return cookies_ != other.cookies_;
    }
//---------------------------------------------------------------------------------------------------------------------
    cookie_iterator& cookie_iterator::operator++()
    {
        if (cookies_)
            cookies_ = cookies_->next;
        return *this;
    }
//---------------------------------------------------------------------------------------------------------------------
    cookie_iterator cookie_iterator::operator++(int)
    {
        auto cpy = *this;
        operator++();
        return cpy;
    }
//#####################################################################################################################
}
