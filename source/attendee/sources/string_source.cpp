#include <attendee/sources/string_source.hpp>

#include <algorithm>

namespace attendee
{
//#####################################################################################################################
    string_source::string_source(std::string const& str)
        : data_{str}
        , pos_{0}
    {

    }
//---------------------------------------------------------------------------------------------------------------------
    std::size_t string_source::fetch(char* buffer, std::size_t amount)
    {
        if (pos_ >= data_.size())
            return 0;

        amount = std::min(amount, data_.size() - pos_);
        data_.substr(pos_, amount);
        std::copy(std::begin(data_) + pos_, std::begin(data_) + pos_ + amount, buffer);
        pos_ += amount;
        return amount;
    }
//---------------------------------------------------------------------------------------------------------------------
    std::size_t string_source::size()
    {
        return data_.size();
    }
//#####################################################################################################################
}
