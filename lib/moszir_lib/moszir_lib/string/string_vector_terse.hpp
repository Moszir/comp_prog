#include <cstring>
#include <string>
#include <vector>
namespace moszir{class StringVector : public std::vector<std::string>{public:StringVector() = default;
StringVector(const std::string& sourceString,const std::string& delimiters,bool emptyFieldsAllowed =
 true);StringVector(std::istream& stream,const std::string& delimiters,bool emptyFieldsAllowed = true);
void fromString(const std::string& sourceString,const std::string& delimiters,bool emptyFieldsAllowed
 = true);[[nodiscard]] int findIndex(const std::string& token, int from = 0) const;};namespace{template<class
 T>void AddFields(T& container, const std::string& sourceString, const std::string& delimiters,const
 bool emptyFieldsAllowed){const char* sourcePos = sourceString.c_str();if (delimiters.length() > 1){while
 (true){const char* delimiterPos = strpbrk(sourcePos, delimiters.c_str());if (!delimiterPos){delimiterPos
 = sourceString.c_str() + sourceString.length();}if (emptyFieldsAllowed || delimiterPos - sourcePos >
 0){container.push_back(std::string(sourcePos, static_cast<int>(delimiterPos - sourcePos)));}if (!*delimiterPos)
{break;}sourcePos = delimiterPos + 1;}}else{const char delimiterChar = delimiters[0];while (true){const
 char* delimiterPos = strchr(sourcePos, delimiterChar);if (!delimiterPos){delimiterPos = sourceString.c_str()
 + sourceString.length();}if (emptyFieldsAllowed || delimiterPos - sourcePos > 0){container.push_back(std::string(sourcePos,
 static_cast<int>(delimiterPos - sourcePos)));}if (!*delimiterPos){break;}sourcePos = delimiterPos +
 1;}}}}StringVector::StringVector(const std::string& sourceString,const std::string& delimiters,const
 bool emptyFieldsAllowed){reserve(4);AddFields(*this, sourceString, delimiters, emptyFieldsAllowed);}
StringVector::StringVector(std::istream& stream, const std::string& delimiters, bool emptyFieldsAllowed)
{std::string s;std::getline(stream, s);reserve(4);AddFields(*this, s, delimiters, emptyFieldsAllowed);
}void StringVector::fromString(const std::string& sourceString,const std::string& delimiters,bool emptyFieldsAllowed)
{clear();reserve(4);AddFields(*this, sourceString, delimiters, emptyFieldsAllowed);}int StringVector::findIndex(const
 std::string& token, int from) const{for (int i = from, iEnd = static_cast<int>(size()); i < iEnd; ++i)
{if ((*this)[i] == token){return i;}}return -1;}}

