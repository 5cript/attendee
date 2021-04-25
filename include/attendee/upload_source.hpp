#pragma once

#include <cstddef>

namespace attendee
{
    class upload_source
    {
    public:
        /**
         *  This function gets called when the upload requests more data.
         *  Read data from whatever source and write at maximum "amount" to "buffer".
         *  Return the amount of bytes that were actually written.
         */
        virtual std::size_t fetch(char* buffer, std::size_t amount) = 0;

        /**
         *  Returns the size of the entirety to upload.
         */
        virtual std::size_t size() = 0;

        virtual ~upload_source() = default;
    };
}
