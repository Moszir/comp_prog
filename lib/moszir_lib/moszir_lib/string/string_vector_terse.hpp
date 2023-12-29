// region string_vector
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
namespace moszir
{
class StringVector : public std::vector<std::string>
{
public:
    StringVector() = default;
    StringVector(const std::string& sourceString, const std::string& delimiters)
    {
        reserve(4);
        addTokens(sourceString, delimiters);
    }
    StringVector(std::istream& stream, const std::string& delimiters)
    {
        reserve(4);
        std::string s;
        std::getline(stream, s);
        addTokens(s, delimiters);
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
                push_back(std::string(sourcePos, static_cast<int>(delimiterPos - sourcePos)));
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
                push_back(std::string(sourcePos, static_cast<int>(delimiterPos - sourcePos)));
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
// endregion string_vector
