// region modular_integer
#include <string>
namespace moszir
{
template <typename T>
class Modular {
public:
    using Type = typename std::decay<decltype(T::value)>::type;
    constexpr static Type mod() { return T::value; }
    static_assert(std::is_signed<Type>::value, "T should be signed");
    static Type invert(Type a)
    {
        auto m = mod();
        Type u = 0, v = 1;
        while (a != 0)
        {
            Type t = m / a;
            m -= t * a;
            u -= t * v;
            std::swap(a, m);
            std::swap(u, v);
        }
        assert(m == 1);
        return u;
    }
    template<typename U> static Type normalize(const U& x)
    {
        auto v = (Type)((-mod() <= x && x < mod()) ? x : x % mod());
        return v < 0 ? v + mod() : v;
    }
    constexpr Modular() = default;
    template<typename U> Modular(const U& x) : value_(normalize(x)) {} 
    const Type& operator()() const { return value_; }
    template<typename U> explicit operator U() const { return static_cast<U>(value_); }
    Modular operator-() const { return Modular(-value_); }
    Modular& operator+=(const Modular& other) { if ((value_ += other.value_) >= mod()) value_ -= mod(); return *this; }
    friend Modular operator+(const Modular& lhs, const Modular& rhs) { return Modular(lhs) += rhs; }
    Modular& operator++() { return *this += 1; }
    Modular operator++(int) { Modular result(*this); operator++(); return result; }
    Modular& operator-=(const Modular& other) { if ((value_ -= other.value_) < 0) value_ += mod(); return *this; }
    friend Modular operator-(const Modular& lhs, const Modular& rhs) { return Modular(lhs) -= rhs; }
    Modular& operator--() { return *this -= 1; }
    Modular operator--(int) { Modular result(*this); operator--(); return result; }
    template<typename U=T>
    typename std::enable_if<std::is_same<typename Modular<U>::Type, int>::value, Modular>::type&
    operator*=(const Modular& rhs)
    {
        value_ = normalize(static_cast<int64_t>(value_) * static_cast<int64_t>(rhs.value_));
        return *this;
    }
    template<typename U=T>
    typename std::enable_if<std::is_same<typename Modular<U>::Type, int64_t>::value, Modular>::type&
    operator*=(const Modular& rhs)
    {
        auto q = static_cast<int64_t>(static_cast<long double>(value_) * rhs.value_ / mod());
        value_ = normalize(value_ * rhs.value_ - q * mod());
        return *this;
    }
    friend Modular operator*(const Modular& lhs, const Modular& rhs) { return Modular(lhs) *= rhs; }
    Modular& operator/=(const Modular& other) { return *this *= Modular(invert(other.value_)); }
    friend Modular operator/(const Modular& lhs, const Modular& rhs) { return Modular(lhs) /= rhs; }
    template<typename U>
    Modular power(U p) const
    {
        assert(p >= 0);
        Modular x = (*this);
        Modular res = 1;
        while (p > 0)
        {
            if (p & 1) res *= x;
            x *= x;
            p >>= 1;
        }
        return res;
    }
    auto operator<=>(const Modular& other) const = default;
    friend std::istream& operator>>(std::istream& stream, Modular& number)
    {
        typename std::common_type<typename Modular::Type, int64_t>::type x;
        stream >> x;
        number.value_ = Modular<T>::normalize(x);
        return stream;
    }
    friend std::ostream& operator<<(std::ostream& stream, const Modular& number) { return stream << number(); }
private:
    Type value_;
};
} 
//> constexpr int md = @@HERE@@;
//> using Mint = ::moszir::Modular<std::integral_constant<std::decay<decltype(md)>::type, md>>;
// endregion modular_integer
