#include "request.hpp"

#include "exception.hpp"

namespace attendee
{
//#####################################################################################################################
    request::request()
        : instance_{curl_easy_init()}
    {
        if (instance_ == nullptr)
            BOOST_THROW_EXCEPTION(init_curl_error);
    }
//---------------------------------------------------------------------------------------------------------------------
    request::~request()
    {
        if (instance_)
            curl_easy_cleanup(instance_);
    }
//---------------------------------------------------------------------------------------------------------------------
    request& request::basic_auth(std::string const& name, std::string const& password)
    {
        curl_easy_setopt(instance_, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
        curl_easy_setopt(instance_, CURLOPT_USERNAME, name.c_str());
        curl_easy_setopt(instance_, CURLOPT_PASSWORD, password.c_str());

        return *this;
    }
//---------------------------------------------------------------------------------------------------------------------
    request& request::accept_encoding(std::string const& encoding)
    {
        curl_easy_setopt(instance_, CURLOPT_ACCEPT_ENCODING, encoding.c_str());
        return *this;
    }
//---------------------------------------------------------------------------------------------------------------------
    request& request::enable_auto_referer(bool referer)
    {
        curl_easy_setopt(instance_, CURLOPT_AUTOREFERER, referer ? 1l : 0l);
        return *this;
    }
//---------------------------------------------------------------------------------------------------------------------
    request& request::enable_transfer_encoding(bool transfer_encoding)
    {
        curl_easy_setopt(instance_, CURLOPT_TRANSFER_ENCODING, transfer_encoding ? 1l : 0l);
        return *this;
    }
//---------------------------------------------------------------------------------------------------------------------
    request& request::follow(bool follow)
    {
        curl_easy_setopt(instance_, CURLOPT_FOLLOWLOCATION, follow ? 1L : 0L);
        return *this;
    }
//---------------------------------------------------------------------------------------------------------------------
    request& max_redirects(long max)
    {
        curl_easy_setopt(instance_, CURLOPT_MAXREDIRS, max);
    }
//---------------------------------------------------------------------------------------------------------------------
    request& forward_auth(bool forward)
    {
        curl_easy_setopt(instance_, CURLOPT_UNRESTRICTED_AUTH, forward ? 1L : 0L);
    }
//---------------------------------------------------------------------------------------------------------------------
//#####################################################################################################################
}
