#pragma once
#include <functional>
#include <string>
#include <stdexcept>
#include <type_traits>

template <typename T>
class GetSet
{
public:
    GetSet(std::function<T()> getter, std::function<void(const T&)> setter)
        : getMethod(getter), setMethod(setter)
    {
    }

    GetSet(std::function<T()> getter)
        : getMethod(getter),
        setMethod([](const T&)
            {
                throw std::runtime_error("Setting this value is not allowed");
            })
    {
    }

    bool operator==(const T& other) const { return getMethod() == other; }
    bool operator!=(const T& other) const { return !(*this == other); }

    auto operator->() const { return getMethod().operator->(); }

    T operator+(const T& other) const { return getMethod() + other; }
    T operator-(const T& other) const { return getMethod() - other; }
    T operator*(const T& other) const { return getMethod() * other; }
    T operator/(const T& other) const { return getMethod() / other; }

    GetSet& operator+=(const T& other)
    {
        T temp = getMethod();
        temp += other;
        setMethod(temp);
        return *this;
    }

    GetSet& operator-=(const T& other)
    {
        T temp = getMethod();
        temp -= other;
        setMethod(temp);
        return *this;
    }

    GetSet& operator*=(const T& other)
    {
        T temp = getMethod();
        temp *= other;
        setMethod(temp);
        return *this;
    }

    GetSet& operator/=(const T& other)
    {
        T temp = getMethod();
        temp /= other;
        setMethod(temp);
        return *this;
    }

    template <typename U = T>
    typename std::enable_if<std::is_pointer<U>::value, bool>::type
        operator==(std::nullptr_t) const
    {
        return getMethod() == nullptr;
    }

    template <typename U = T>
    typename std::enable_if<std::is_pointer<U>::value, bool>::type
        operator!=(std::nullptr_t) const
    {
        return getMethod() != nullptr;
    }

    operator T() const { return getMethod(); }

    operator std::string() const { return static_cast<std::string>(getMethod()); }

    T operator=(const T& other)
    {
        setMethod(other);
        return other;
    }

private:
    std::function<T()> getMethod;
    std::function<void(const T&)> setMethod;
};
