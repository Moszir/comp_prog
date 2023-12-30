#include "gtest/gtest.h"
#include "moszir_lib/string/string_conversions_terse.hpp"


TEST(stringConversions, stringViewToInt)
{
    const std::string src = "apple 123";
    std::string_view view(src.data() + 6, src.data() + 9);
    EXPECT_EQ(123, ::moszir::toInt(view));
}
