#pragma once

#include "../upload_source.hpp"

#include <string>

namespace attendee
{
    class string_source : public upload_source
    {
    public:
        string_source(std::string const& str);

        std::size_t fetch(char* buffer, std::size_t amount) override;

        std::size_t size() override;

    private:
        std::string data_;
        std::size_t pos_;
    };
}
