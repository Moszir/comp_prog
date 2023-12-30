// region string_view_vector
#include <cstring>
#include <string>
#include <vector>
namespace moszir
{
class StringViewVector : public std::vector<std::string_view>
{
public:
    StringViewVector() = default;
    StringViewVector(const std::string& sourceString, const std::string& delimiters)
    {
        reserve(4);
        addTokens(sourceString, delimiters);
    }
    [[nodiscard]] int findIndex(const std::string& token, int from = 0) const
    {
        auto it = std::find(begin() + from, end(), token);
        return it == end() ? -1 : static_cast<int>(std::distance(begin(), it));
    }
    void addTokens(const std::string& sourceString, const char delimiter)
    {
        const char* sourcePos = sourceString.c_str();
        while (true)
        {
            const char* delimiterPos = std::strchr(sourcePos, delimiter);
            if (!delimiterPos)
            {
                delimiterPos = sourceString.c_str() + sourceString.length();
            }
            if (delimiterPos - sourcePos > 0)
            {
                push_back(std::string_view(sourcePos, static_cast<int>(delimiterPos - sourcePos)));
            }
            if (!*delimiterPos)
            {
                break;
            }
            sourcePos = delimiterPos + 1;
        }
    }
    void addTokens(const std::string& sourceString, const std::string& delimiters)
    {
        addTokens(sourceString, delimiters.c_str());
    }
    void addTokens(const std::string& sourceString, const char* delimiters)
    {
        const char* sourcePos = sourceString.c_str();
        while (true)
        {
            const char* delimiterPos = std::strpbrk(sourcePos, delimiters);
            if (!delimiterPos)
            {
                delimiterPos = sourceString.c_str() + sourceString.length();
            }
            if (delimiterPos - sourcePos > 0)
            {
                push_back(std::string_view(sourcePos, static_cast<int>(delimiterPos - sourcePos)));
            }
            if (!*delimiterPos)
            {
                break;
            }
            sourcePos = delimiterPos + 1;
        }
    }
};
}
// endregion string_view_vector
