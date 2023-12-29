#include <string>

namespace moszir
{

/**
 * Modular integer.
 * @tparam T The type to represent the values.
 */
template <typename T>
class Modular {
public:
    using Type = typename std::decay<decltype(T::value)>::type;
    constexpr static Type mod() { return T::value; }

    // Some features do not work with unsigned types. Underflow and all that.
    static_assert(std::is_signed<Type>::value, "T should be signed");

    /**
     * @brief Solves the modular equation `a * x == 1 (m)` to get the "inverse" of `a`.
     *
     * This is used for "dividing" something by `a` in a modular sense.
     * The calculation is a special case of the Euclidean algorithm:
     * https://en.wikipedia.org/wiki/Modular_multiplicative_inverse#Extended_Euclidean_algorithm
     *
     * @note If the modulus is a prime, then the modular inverse always exists.
     * @warning If the inverse does not exist, an assertion will trigger.
     */
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

    /**
     * @brief Calculates the modular equivalent of `x` in `[0, mod)`.
     */
    template<typename U> static Type normalize(const U& x)
    {
        auto v = (Type)((-mod() <= x && x < mod()) ? x : x % mod());
        return v < 0 ? v + mod() : v;
    }

    constexpr Modular() = default;

    template<typename U> Modular(const U& x) : value_(normalize(x)) {} // NOLINT Intentionally not explicit

    /**
     * @brief Converts this object to the representative type.
     */
    const Type& operator()() const { return value_; }

    /**
     * @brief Converts this object to the requested type.
     */
    template<typename U> explicit operator U() const { return static_cast<U>(value_); }

    /// @name Mathematical operations
    /// @{

    /// @brief Unary minus.
    Modular operator-() const { return Modular(-value_); }

    /**
     * @brief Compound addition.
     * @note Also works with other types that can be implicitly converted to `Modular`.
     */
    Modular& operator+=(const Modular& other) { if ((value_ += other.value_) >= mod()) value_ -= mod(); return *this; }

    /**
     * @brief Addition operator.
     * @note Addition of a `Modular` and another type works too: implicit conversion + ADL.
     */
    friend Modular operator+(const Modular& lhs, const Modular& rhs) { return Modular(lhs) += rhs; }

    /// @brief Increment operator.
    Modular& operator++() { return *this += 1; }

    /// @brief Post-increment operator.
    Modular operator++(int) { Modular result(*this); operator++(); return result; }

    /**
     * @brief Compound subtraction.
     * @note Should work with other types (implicit conversion + ADL).
     */
    Modular& operator-=(const Modular& other) { if ((value_ -= other.value_) < 0) value_ += mod(); return *this; }

    /**
     * @brief Subtraction.
     * @note Should work with other types (implicit conversion + ADL).
     */
    friend Modular operator-(const Modular& lhs, const Modular& rhs) { return Modular(lhs) -= rhs; }

    /// @brief Decrement operator.
    Modular& operator--() { return *this -= 1; }

    /// @brief Post-decrement operator.
    Modular operator--(int) { Modular result(*this); operator--(); return result; }

    /**
     * @brief Compound multiplication if our type is `int`.
     *
     * Multiplication performed in `int64_t`.
     */
    template<typename U=T>
    typename std::enable_if<std::is_same<typename Modular<U>::Type, int>::value, Modular>::type&
    operator*=(const Modular& rhs)
    {
        value_ = normalize(static_cast<int64_t>(value_) * static_cast<int64_t>(rhs.value_));
        return *this;
    }

    /**
     * @brief Compound multiplication if our type is `int64_t`.
     * @note Works with implicit convertible types too.
     */
    template<typename U=T>
    typename std::enable_if<std::is_same<typename Modular<U>::Type, int64_t>::value, Modular>::type&
    operator*=(const Modular& rhs)
    {
        auto q = static_cast<int64_t>(static_cast<long double>(value_) * rhs.value_ / mod());
        value_ = normalize(value_ * rhs.value_ - q * mod());
        return *this;
    }

    /**
     * @brief Multiplication operator.
     * @note Works with implicit convertible types too.
     */
    friend Modular operator*(const Modular& lhs, const Modular& rhs) { return Modular(lhs) *= rhs; }

    /**
     * @brief Compound division operator.
     * @note Works with implicit convertible types too.
     */
    Modular& operator/=(const Modular& other) { return *this *= Modular(invert(other.value_)); }

    /**
     * @brief Division operator.
     * @note Works with implicit convertible types too.
     */
    friend Modular operator/(const Modular& lhs, const Modular& rhs) { return Modular(lhs) /= rhs; }

    /**
     * Calculate raising this number to the given power.
     */
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
    /// @}

    /// @brief Comparison operators
    auto operator<=>(const Modular& other) const = default;

    /// @brief Stream extraction operator.
    friend std::istream& operator>>(std::istream& stream, Modular& number)
    {
        typename std::common_type<typename Modular::Type, int64_t>::type x;
        stream >> x;
        number.value_ = Modular<T>::normalize(x);
        return stream;
    }

    /// @brief Stream insertion operator.
    friend std::ostream& operator<<(std::ostream& stream, const Modular& number) { return stream << number(); }

private:
    Type value_;
};

} // namespace moszir

//> constexpr int md = @@HERE@@;
//> using Mint = ::moszir::Modular<std::integral_constant<std::decay<decltype(md)>::type, md>>;
