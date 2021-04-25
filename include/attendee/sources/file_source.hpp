#pragma once

#include <attendee/upload_source.hpp>

#include <fstream>

namespace attendee
{
    class file_source : public upload_source
    {
    public:
        file_source(std::string const& filename);

        /**
         *  Write data from stream into buffers. Returns gcount.
         */
        std::size_t fetch(char* buffer, std::size_t amount) override;

        std::size_t size() override;

    private:
        std::ifstream reader_;
    };
}
