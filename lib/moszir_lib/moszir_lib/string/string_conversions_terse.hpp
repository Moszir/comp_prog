// region string_conversions
#include <charconv>
namespace moszir
{
int toInt(const std::string_view& sv)
{
    int number{};
    std::from_chars(sv.data(), sv.data() + sv.size(), number);
    return number;
}
} 
// endregion string_conversions
