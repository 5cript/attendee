#include <attendee/sources/file_source.hpp>

namespace attendee
{
//#####################################################################################################################
    file_source::file_source(std::string const& filename)
        : reader_{filename, std::ios_base::binary}
    {
        if (!reader_.good())
            throw std::runtime_error("could not open file source.");
    }
//---------------------------------------------------------------------------------------------------------------------
    std::size_t file_source::fetch(char* buffer, std::size_t amount)
    {
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
