#include <cstring>
#include <string>
#include <vector>


namespace moszir
{

class StringVector : public std::vector<std::string>
{
public:
    /**
     * @brief Creates an empty string vector.
     */
    StringVector() = default;

    /**
     * @brief Creates a string vector by chopping up the given string with the given delimiters.
     *
     * @param sourceString The given string
     * @param delimiters The delimiters
     * @param emptyFieldsAllowed Whether empty parts (e.g. between two delimiters or at the start/end) are allowed.
     */
    StringVector(
        const std::string& sourceString,
        const std::string& delimiters,
        bool emptyFieldsAllowed = true);

    /**
     * @brief Creates a string vector by reading a line from the stream, and chopping it up with the given delimiters.
     *
     * @param stream The stream to read from
     * @param delimiters The delimiters
     * @param emptyFieldsAllowed Whether empty parts (e.g. between two delimiters or at the start/end) are allowed.
     */
    StringVector(
        std::istream& stream,
        const std::string& delimiters,
        bool emptyFieldsAllowed = true);

    /**
     * Reuses this string vector as if its constructor was called again.
     *
     * @param sourceString The given string
     * @param delimiters The delimiters
     * @param emptyFieldsAllowed Whether empty parts (e.g. between two delimiters or at the start/end) are allowed.
     */
    void fromString(
        const std::string& sourceString,
        const std::string& delimiters,
        bool emptyFieldsAllowed = true);

    /**
     * Returns the index of the first occurrence of the given token. Returns -1 if not found.
     * @param token The token to find.
     * @param from The starting index to look from (default 0).
     */
    [[nodiscard]] int findIndex(const std::string& token, int from = 0) const;
};

namespace
{

template<class T>
void AddFields(T& container, const std::string& sourceString, const std::string& delimiters,
               const bool emptyFieldsAllowed)
{
    const char* sourcePos = sourceString.c_str();
    if (delimiters.length() > 1)
    {
        while (true)
        {
            const char* delimiterPos = strpbrk(sourcePos, delimiters.c_str());
            if (!delimiterPos)
            {
                delimiterPos = sourceString.c_str() + sourceString.length();
            }

            if (emptyFieldsAllowed || delimiterPos - sourcePos > 0)
            {
                container.push_back(std::string(sourcePos, static_cast<int>(delimiterPos - sourcePos)));
            }
            if (!*delimiterPos)
            {
                break;
            }
            sourcePos = delimiterPos + 1;
        }
    }
    else
    {
        const char delimiterChar = delimiters[0];
        while (true)
        {
            const char* delimiterPos = strchr(sourcePos, delimiterChar);
            if (!delimiterPos)
            {
                delimiterPos = sourceString.c_str() + sourceString.length();
            }
            if (emptyFieldsAllowed || delimiterPos - sourcePos > 0)
            {
                container.push_back(std::string(sourcePos, static_cast<int>(delimiterPos - sourcePos)));
            }
            if (!*delimiterPos)
            {
                break;
            }
            sourcePos = delimiterPos + 1;
        }
    }
}
} // anonymous namespace

StringVector::StringVector(
    const std::string& sourceString,
    const std::string& delimiters,
    const bool emptyFieldsAllowed)
{
    reserve(4);
    AddFields(*this, sourceString, delimiters, emptyFieldsAllowed);
}

StringVector::StringVector(std::istream& stream, const std::string& delimiters, bool emptyFieldsAllowed)
{
    std::string s;
    std::getline(stream, s);
    reserve(4);
    AddFields(*this, s, delimiters, emptyFieldsAllowed);
}

void StringVector::fromString(
    const std::string& sourceString,
    const std::string& delimiters,
    bool emptyFieldsAllowed)
{
    clear();
    reserve(4);
    AddFields(*this, sourceString, delimiters, emptyFieldsAllowed);
}

int StringVector::findIndex(const std::string& token, int from) const
{
    for (int i = from, iEnd = static_cast<int>(size()); i < iEnd; ++i)
    {
        if ((*this)[i] == token)
        {
            return i;
        }
    }
    return -1;
}

} // namespace moszir
