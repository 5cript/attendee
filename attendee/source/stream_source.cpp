#include "stream_source.hpp"

namespace attendee
{
//#####################################################################################################################
    stream_source::stream_source(std::istream* stream)
        : stream_{stream}
    {
    }
//---------------------------------------------------------------------------------------------------------------------
    std::size_t stream_source::fetch(char* buffer, std::size_t amount)
    {
        stream_->read(buffer, amount);
        return stream_->gcount();
    }
//---------------------------------------------------------------------------------------------------------------------
    std::size_t stream_source::size()
    {
        stream_->seekg(0, std::ios_base::end);
        auto size = stream_->tellg();
        stream_->seekg(0);
        return size;
    }
//#####################################################################################################################
}
