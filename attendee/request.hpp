#pragma once

#include "core.hpp"

#include <string>

namespace attendee
{
    class request
    {
    public:
        /**
         *  This constructor creates a request and initializes a curl easy instance.
         *  @warning Do not continue to use this class, if it caused an error (exception, if not disabled).
         */
        request();
        ~request();

        /**
         *  Adds a basic authentication header field.
         *
         *  @param name The username.
         *  @param password The password.
         *  @return *this.
         */
        request& basic_auth(std::string const& name, std::string const& password);

        /**
         *  Set the Accept-Encoding header. Curl will handle simple compressions automatically.
         *  @param encoding identity (non-compressed), deflate (zlib), gzip (gzip), "" (all supported by curl)
         */
        request& accept_encoding(std::string const& encoding);

        /**
         *  When enabled, libcurl will automatically set the Referer:
         *  header field in HTTP requests where it follows a Location: redirect.
         */
        request& enable_auto_referer(bool referer);

        /**
         *  Adds a request for compressed Transfer Encoding in the outgoing HTTP request
         *  @see CURLOPT_TRANSFER_ENCODING
         */
        request& enable_transfer_encoding(bool transfer_encoding);

        /**
         *  Allow curl to automatically follow redirections (3xx headers).
         */
        request& follow(bool follow = true);

        /**
         *  Set the maximum amount of redirections. Only relevant, if follow was called.
         */
        request& max_redirects(long max);

        /**
         *  Set the long gohead parameter to 1L to make libcurl continue to send authentication (user+password) credentials when following locations,
         *  even when hostname changed
         *  @warning Seriously... dont.
         */
        request& forward_auth(bool forward = true);

    private:
        CURL* instance_;
    };
}
