#include <string>
namespace moszir{template <typename T>T inverse(T a, T m){T u = 0, v = 1;while (a != 0){T t = m / a;m
 -= t * a;std::swap(a, m);u -= t * v;std::swap(u, v);}assert(m == 1);return u;}template <typename T>class
 Modular {public:using Type = typename std::decay<decltype(T::value)>::type;constexpr Modular() : value_()
 {}template<typename U> Modular(const U& x) : value_(normalize(x)) {}template<typename U>static Type
 normalize(const U& x) {Type v;if (-mod() <= x && x < mod()) v = static_cast<Type>(x);else v = static_cast<Type>(x
 % mod());if (v < 0) v += mod();return v;}const Type& operator()() const { return value_; }template <typename
 U>explicit operator U() const { return static_cast<U>(value_); }constexpr static Type mod() { return
 T::value; }Modular operator-() const { return Modular(-value_); }Modular& operator+=(const Modular&
 other) { if ((value_ += other.value_) >= mod()) value_ -= mod(); return *this; }Modular& operator-=(const
 Modular& other) { if ((value_ -= other.value_) < 0) value_ += mod(); return *this; }template <typename
 U> Modular& operator+=(const U& other) { return *this += Modular(other); }template <typename U> Modular&
 operator-=(const U& other) { return *this -= Modular(other); }Modular& operator++() { return *this +=
 1; }Modular& operator--() { return *this -= 1; }Modular operator++(int) { Modular result(*this); operator++();
 return result; }Modular operator--(int) { Modular result(*this); operator--(); return result; }template
 <typename U = T>typename std::enable_if<std::is_same<typename Modular<U>::Type, int>::value, Modular>::type&
 operator*=(const Modular& rhs) {value_ = normalize(static_cast<int64_t>(value_) * static_cast<int64_t>(rhs.value_));
return *this;}template <typename U = T>typename std::enable_if<std::is_same<typename Modular<U>::Type,
 int64_t>::value, Modular>::type& operator*=(const Modular& rhs) {auto q = static_cast<int64_t>(static_cast<long
 double>(value_) * rhs.value_ / mod());value_ = normalize(value_ * rhs.value_ - q * mod());return *this;
}template <typename U = T>typename std::enable_if<!std::is_integral<typename Modular<U>::Type>::value,
 Modular>::type& operator*=(const Modular& rhs) {value_ = normalize(value_ * rhs.value_);return *this;
}Modular& operator/=(const Modular& other) { return *this *= Modular(inverse(other.value_, mod())); }
template <typename U>friend bool operator==(const Modular<U>& lhs, const Modular<U>& rhs);template <typename
 U>friend bool operator<(const Modular<U>& lhs, const Modular<U>& rhs);template <typename U>friend std::istream&
 operator>>(std::istream& stream, Modular<U>& number);private:Type value_;};template <typename T> bool
 operator==(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value_ == rhs.value_; }template
 <typename T, typename U> bool operator==(const Modular<T>& lhs, U rhs) { return lhs == Modular<T>(rhs);
 }template <typename T, typename U> bool operator==(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs)
 == rhs; }template <typename T> bool operator!=(const Modular<T>& lhs, const Modular<T>& rhs) { return
 !(lhs == rhs); }template <typename T, typename U> bool operator!=(const Modular<T>& lhs, U rhs) { return
 !(lhs == rhs); }template <typename T, typename U> bool operator!=(U lhs, const Modular<T>& rhs) { return
 !(lhs == rhs); }template <typename T> bool operator<(const Modular<T>& lhs, const Modular<T>& rhs) {
 return lhs.value_ < rhs.value_; }template <typename T> Modular<T> operator+(const Modular<T>& lhs, const
 Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }template <typename T, typename U> Modular<T> operator+(const
 Modular<T>& lhs, U rhs) { return Modular<T>(lhs) += rhs; }template <typename T, typename U> Modular<T>
 operator+(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }template <typename T> Modular<T>
 operator-(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }template <typename
 T, typename U> Modular<T> operator-(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) -= rhs; }template
 <typename T, typename U> Modular<T> operator-(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs)
 -= rhs; }template <typename T> Modular<T> operator*(const Modular<T>& lhs, const Modular<T>& rhs) {
 return Modular<T>(lhs) *= rhs; }template <typename T, typename U> Modular<T> operator*(const Modular<T>&
 lhs, U rhs) { return Modular<T>(lhs) *= rhs; }template <typename T, typename U> Modular<T> operator*(U
 lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }template <typename T> Modular<T> operator/(const
 Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }template <typename T, typename
 U> Modular<T> operator/(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) /= rhs; }template <typename
 T, typename U> Modular<T> operator/(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }
template<typename T, typename U>Modular<T> power(const Modular<T>& a, const U& b) {assert(b >= 0);Modular<T>
 x = a, res = 1;U p = b;while (p > 0) {if (p & 1) res *= x;x *= x;p >>= 1;}return res;}template <typename
 T>std::string to_string(const Modular<T>& number) {return to_string(number());}template <typename T>
std::ostream& operator<<(std::ostream& stream, const Modular<T>& number) {return stream << number();}
template <typename T>std::istream& operator>>(std::istream& stream, Modular<T>& number) {typename std::common_type<typename
 Modular<T>::Type, int64_t>::type x;stream >> x;number.value_ = Modular<T>::normalize(x);return stream;
}}
//> constexpr int md = @@HERE@@;
//> using Mint = ::moszir::Modular<std::integral_constant<std::decay<decltype(md)>::type, md>>;
