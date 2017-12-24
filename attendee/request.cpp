#include "request.hpp"

#include "exception.hpp"

namespace attendee
{
//#####################################################################################################################
    size_t generic_write_funciton(char *ptr, size_t size, size_t nmemb, std::function <void(char*, std::size_t)>* sink)
    {
        (*sink)(ptr, size * nmemb);
        return size * nmemb;
    }
//---------------------------------------------------------------------------------------------------------------------
    static size_t generic_read_function(char* buffer, size_t size, size_t nmemb, upload_source* source)
    {
        return source->fetch(buffer, size * nmemb);
    }
//#####################################################################################################################
    request::request()
        : instance_{curl_easy_init()}
    {
        if (instance_ == nullptr)
            BOOST_THROW_EXCEPTION(init_curl_error{"initializing a curl instance failed."});
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
    request& request::max_redirects(long max)
    {
        curl_easy_setopt(instance_, CURLOPT_MAXREDIRS, max);
        return *this;
    }
//---------------------------------------------------------------------------------------------------------------------
    request& request::forward_auth(bool forward)
    {
        curl_easy_setopt(instance_, CURLOPT_UNRESTRICTED_AUTH, forward ? 1L : 0L);
        return *this;
    }
//---------------------------------------------------------------------------------------------------------------------
    request& request::get(std::string const& url)
    {
        set_url(url);
        return *this;
    }
//---------------------------------------------------------------------------------------------------------------------
    void request::set_url(std::string const& url)
    {
        curl_easy_setopt(instance_, CURLOPT_URL, url.c_str());
    }
//---------------------------------------------------------------------------------------------------------------------
    request& request::sink(std::function <void(char*, std::size_t)> const& sink_fn)
    {
        sink_ = sink_fn;
        curl_easy_setopt(instance_, CURLOPT_WRITEDATA, &sink_);
        curl_easy_setopt(instance_, CURLOPT_WRITEFUNCTION, generic_write_funciton);
        return *this;
    }
//---------------------------------------------------------------------------------------------------------------------
    request& request::cookie_string(std::string const& cookies)
    {
        curl_easy_setopt(instance_, CURLOPT_COOKIE, cookies.c_str());
        return *this;
    }
//---------------------------------------------------------------------------------------------------------------------
    request& request::cookies(std::string const& cookie_file)
    {
        curl_easy_setopt(instance_, CURLOPT_COOKIEFILE, cookie_file.c_str());
        return *this;
    }
//---------------------------------------------------------------------------------------------------------------------
    request& request::cookie_jar(std::string const& cookie_jar)
    {
        curl_easy_setopt(instance_, CURLOPT_COOKIEJAR, cookie_jar.c_str());
        return *this;
    }
//---------------------------------------------------------------------------------------------------------------------
    CURLcode request::perform()
    {
        return curl_easy_perform(instance_);
    }
//---------------------------------------------------------------------------------------------------------------------
    void request::set_source()
    {
        curl_easy_setopt(instance_, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(instance_, CURLOPT_READDATA, source_.get());
        curl_easy_setopt(instance_, CURLOPT_READFUNCTION, generic_read_function);
        curl_easy_setopt(instance_, CURLOPT_INFILESIZE_LARGE, source_->size());
    }
//---------------------------------------------------------------------------------------------------------------------
    request& request::put(std::string const& url)
    {
        curl_easy_setopt(instance_, CURLOPT_PUT, 1L);
        curl_easy_setopt(instance_, CURLOPT_URL, url.c_str());
        return *this;
    }
//---------------------------------------------------------------------------------------------------------------------
    request& request::throttle_download(unsigned long long bytes_per_second)
    {
        curl_easy_setopt(instance_, CURLOPT_MAX_RECV_SPEED_LARGE, bytes_per_second);
        return *this;
    }
//#####################################################################################################################
}
