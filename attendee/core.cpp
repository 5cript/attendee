#include "core.hpp"

namespace attendee
{
//#####################################################################################################################
    system_context::system_context(long curl_global_flags)
    {
        curl_global_init(curl_global_flags);
    }
//---------------------------------------------------------------------------------------------------------------------
    system_context::~system_context()
    {
        curl_global_cleanup();
    }
//#####################################################################################################################
}