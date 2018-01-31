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
    CURLcode response::result() const
    {
        return result_;
    }
//#####################################################################################################################
}
