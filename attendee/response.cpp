#include "response.hpp"
#include "request.hpp"

namespace attendee
{
//#####################################################################################################################
    response::response(request* parent, CURLcode result)
        : parent_{parent}
        , result_{result}
        , set_cookies_{nullptr, [](curl_slist* list){curl_slist_free_all(list);}}
    {

    }
//---------------------------------------------------------------------------------------------------------------------
    cookie_proxy response::cookies()
    {
        curl_slist *cookies = nullptr;
        auto res = curl_easy_getinfo(parent_->handle(), CURLINFO_COOKIELIST, &cookies);
        if (res == CURLE_OK)
            set_cookies_.reset(cookies);
        return {this};
    }
//---------------------------------------------------------------------------------------------------------------------
    std::string response::redirect_url() const
    {
        char* url;
        auto res = curl_easy_getinfo(parent_->handle(), CURLINFO_REDIRECT_URL, &url);
        if (res == CURLE_OK && url)
            return {url};
        return {};
    }
//---------------------------------------------------------------------------------------------------------------------
    long long response::size_downloaded() const
    {
        curl_off_t dl;
        auto res = curl_easy_getinfo(parent_->handle(), CURLINFO_SIZE_DOWNLOAD_T, &dl);
        if (res == CURLE_OK)
            return static_cast <long long> (dl);
        return 0;
    }
//---------------------------------------------------------------------------------------------------------------------
    long long response::size_uploaded() const
    {
        curl_off_t ul;
        auto res = curl_easy_getinfo(parent_->handle(), CURLINFO_SIZE_UPLOAD_T, &ul);
        if (res == CURLE_OK)
            return static_cast <long long> (ul);
        return 0;
    }
//---------------------------------------------------------------------------------------------------------------------
    int response::code() const
    {
        int code;
        auto res = curl_easy_getinfo(parent_->handle(), CURLINFO_RESPONSE_CODE, &code);
        if (res == CURLE_OK)
            return code;
        return 0;
    }
//---------------------------------------------------------------------------------------------------------------------
    std::string response::url_decode(std::string const& url)
    {
        CURL *curl = curl_easy_init();
        std::string decoded;
        int actual = 0;
        auto* dec = curl_easy_unescape(curl, url.c_str(), url.length(), &actual);
        if (dec != nullptr)
        {
            decoded = std::string{dec, dec + actual};
            curl_free(dec);
        }
        curl_easy_cleanup(curl);
        return decoded;
    }
//---------------------------------------------------------------------------------------------------------------------
    CURLcode response::result() const
    {
        return result_;
    }
//#####################################################################################################################
}
