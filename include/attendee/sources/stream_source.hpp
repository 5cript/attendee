#pragma once

#include <attendee/upload_source.hpp>

#include <istream>

namespace attendee
{
    class stream_source : upload_source
    {
    public:
        /**
         *  Pass some sort of istream.
         */
        stream_source(std::istream* stream);

        /**
         *  Write data from stream into buffers. Returns gcount.
         */
        std::size_t fetch(char* buffer, std::size_t amount) override;

        std::size_t size() override;

    private:
        std::istream* stream_;
    };
}
