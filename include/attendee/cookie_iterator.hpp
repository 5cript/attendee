#pragma once

#include <attendee/core.hpp>
#include <attendee/cookie.hpp>

#include <memory>
#include <iterator>

namespace attendee
{
    class cookie_iterator
    {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = cookie;
        using pointer = curl_slist*;
        using reference = curl_slist&;
        using iterator_category = std::forward_iterator_tag;

    public:
        cookie_iterator(curl_slist* cookies);

        bool operator==(cookie_iterator const& other) const;
        bool operator!=(cookie_iterator const& other) const;
        cookie_iterator& operator++();
        cookie_iterator operator++(int);

        // CopyConstructible / MoveConstructible
        cookie_iterator(cookie_iterator const&) = default;
        cookie_iterator(cookie_iterator&&) = default;

        // CopyAssignable / MoveAssignable
        cookie_iterator& operator=(cookie_iterator const&) = default;
        cookie_iterator& operator=(cookie_iterator&&) = default;

        ~cookie_iterator() = default;

        cookie operator*();
        cookie operator*() const;

        cookie operator->();
        cookie operator->() const;

    public:
        void swap(cookie_iterator& other);

    private:
        curl_slist* cookies_;
    };

    void swap(cookie_iterator& lhs, cookie_iterator& rhs);
}
