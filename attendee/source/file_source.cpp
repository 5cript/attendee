#include "file_source.hpp"

namespace attendee
{
//#####################################################################################################################
    file_source::file_source(std::string const& filename)
        : reader_{filename, std::ios_base::binary}
    {
    }
//---------------------------------------------------------------------------------------------------------------------
    std::size_t file_source::fetch(char* buffer, std::size_t amount)
    {
        if (!reader_.good())
            return 0;

        reader_.read(buffer, amount);
        return reader_.gcount();
    }
//---------------------------------------------------------------------------------------------------------------------
    std::size_t file_source::size()
    {
        reader_.seekg(0, std::ios_base::end);
        auto size = reader_.tellg();
        reader_.seekg(0);
        return size;
    }
//#####################################################################################################################
}