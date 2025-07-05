#pragma once

#include <type_traits>
#include <stdexcept>
#include "PointerControlBlock.h"

class Object;

template<typename T>
class Pointer;

template<typename To, typename From>
Pointer<To> static_pointer_cast(const Pointer<From>& from)
{
    static_assert(std::is_base_of<Object, From>::value, "From must derive from Object");
    static_assert(std::is_base_of<Object, To>::value, "To must derive from Object");

    if (!from)
        return Pointer<To>();

    To* castedPtr = static_cast<To*>(from.Get());

    Pointer<To> result;
    result._controlBlock = reinterpret_cast<ControlBlock<To>*>(from._controlBlock);
    result._controlBlock->AddRef();
    return result;
}

template<typename T>
class Pointer
{
private:
    template<typename To, typename From>
    friend Pointer<To> static_pointer_cast(const Pointer<From>& from);
    ControlBlock<T>* _controlBlock = nullptr;

public:
    Pointer()
    {
        T* obj = new T();
        _controlBlock = new ControlBlock<T>(obj);
        obj->_controlBlock = reinterpret_cast<ControlBlock<Object>*>(_controlBlock);
    }

    Pointer(std::nullptr_t) : _controlBlock(nullptr) { }

    explicit Pointer(T* p)
    {
        if (!p)
            return;

        if (!p->_controlBlock)
        {
            _controlBlock = new ControlBlock<T>(p);
            p->_controlBlock = reinterpret_cast<ControlBlock<Object>*>(_controlBlock);
        }
        else
        {
            _controlBlock = reinterpret_cast<ControlBlock<T>*>(p->_controlBlock);
            _controlBlock->AddRef();
        }
    }

    Pointer(const Pointer<T>& other)
    {
        if (other._controlBlock)
        {
            _controlBlock = other._controlBlock;
            _controlBlock->AddRef();
        }
    }

    Pointer(Pointer<T>&& other) noexcept
        : _controlBlock(other._controlBlock)
    {
        other._controlBlock = nullptr;
    }

    Pointer& operator=(const Pointer<T>& other)
    {
        if (this != &other)
        {
            if (_controlBlock)
                _controlBlock->ReleaseRef();

            _controlBlock = other._controlBlock;
            if (_controlBlock)
                _controlBlock->AddRef();
        }
        return *this;
    }

    Pointer& operator=(Pointer<T>&& other) noexcept
    {
        if (this != &other)
        {
            if (_controlBlock)
                _controlBlock->ReleaseRef();

            _controlBlock = other._controlBlock;
            other._controlBlock = nullptr;
        }
        return *this;
    }

    T& operator*() const
    {
        if (!_controlBlock || !_controlBlock->object)
            throw std::runtime_error("Object is null or has been destroyed");
        return *(_controlBlock->object);
    }

    T* operator->() const
    {
        if (_controlBlock == nullptr || _controlBlock->object == nullptr)
            throw std::runtime_error("Object is null or has been destroyed");

        return _controlBlock->object;
    }


    bool operator==(std::nullptr_t) const
    {
        if (_controlBlock == nullptr)
            return true;

        return _controlBlock->object == nullptr;
    }
    bool operator!=(std::nullptr_t) const
    {
        return !(*this == nullptr);
    }

    bool operator==(const Pointer<T>& other) const
    {
        return _controlBlock == other._controlBlock;
    }
    bool operator!=(const Pointer<T>& other) const
    {
        return !(*this == other);
    }

    T* Get() const
    {
        return (_controlBlock) ? _controlBlock->object : nullptr;
    }

    explicit operator bool() const
    {
        return _controlBlock && _controlBlock->object;
    }

    template<typename U>
    Pointer<U> Cast() const
    {
        return static_pointer_cast<U>(*this);
    }


    std::string ToString() const
    {
        std::ostringstream result;

        if (_controlBlock && _controlBlock->object)
            result << "Pointer, references: " << _controlBlock->ref_count << ", Object: " << _controlBlock->object;
        else
            result << "Pointer, NULL";

        return result.str();
    }

    void Reset()
    {
        if (_controlBlock != nullptr)
        {
            ControlBlock<T>* temp = _controlBlock;
            _controlBlock = nullptr;
            temp->ReleaseRef();
        }
    }

    ~Pointer()
    {
        Reset();
    }
};

template<typename T>
bool operator==(std::nullptr_t lhs, const Pointer<T>& rhs)
{
    return rhs == nullptr;
}

template<typename T>
bool operator!=(std::nullptr_t lhs, const Pointer<T>& rhs)
{
    return rhs != nullptr;
}