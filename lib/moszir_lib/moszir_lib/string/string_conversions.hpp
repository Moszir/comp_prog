#pragma once

#include <charconv>

namespace moszir
{

/**
 * @brief Converts an `std::string_view` to an `int`.
 */
int toInt(const std::string_view& sv)
{
    int number{};
    std::from_chars(sv.data(), sv.data() + sv.size(), number);
    return number;
}

} // namespace moszir
