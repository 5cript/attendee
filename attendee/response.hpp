#pragma once

#include "forward.hpp"
#include "cookie_proxy.hpp"

#include <memory>

namespace attendee
{
    class response
    {
    private:
        friend request;
        friend cookie_proxy;

        response(request* parent, CURLcode result);

    public:
        response& operator=(response const&) = delete;
        response& operator=(response&&) = default;

        response(response const&) = delete;
        response(response&&) = default;

        /**
         *  Returns the curl response code.
         */
        CURLcode result() const;

        /**
         *  Returns the url curl would have redirected to, if it were enabled
         */
        std::string redirect_url() const;

        /**
         *  Returns the amount of bytes downloaded
         */
        long long size_downloaded() const;

        /**
         *  Returns the amount of bytes uploaded
         */
        long long size_uploaded() const;

        /**
         *  Prepares cookie retrieval and returns range.
         */
        cookie_proxy cookies();

        /**
         *  Returns the server response code
         */
        int code() const;

        /**
         *  decodes a url.
         */
        static std::string url_decode(std::string const& url);

    public:
        ~response() = default;

    private:
        request* parent_;
        CURLcode result_;
        std::unique_ptr <curl_slist, void(*)(curl_slist*)> set_cookies_;
    };
}
