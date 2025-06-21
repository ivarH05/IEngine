#pragma once

#include <type_traits>
#include <stdexcept>
#include "PointerControlBlock.h"

class Object;

template<typename T>
class Pointer
{
    static_assert(std::is_base_of<Object, T>::value,
        "T must be derived from Object");

private:
    ControlBlock<T>* _controlBlock = nullptr;

public:
    Pointer()
    {
        T* obj = new T();
        _controlBlock = new ControlBlock<T>(obj);
        obj->_controlBlock = reinterpret_cast<ControlBlock<Object>*>(_controlBlock);
    }

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
            _controlBlock = p->_controlBlock;
            _controlBlock->AddRef();
        }
    }

    Pointer(const Pointer<T>& other)
        : _controlBlock(other._controlBlock)
    {
        if (_controlBlock)
            _controlBlock->AddRef();
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
        if (!_controlBlock || !_controlBlock->object)
            throw std::runtime_error("Object is null or has been destroyed");
        return _controlBlock->object;
    }

    bool operator==(const Pointer<T>& other) const
    {
        return _controlBlock == other._controlBlock;
    }

    T* Get() const
    {
        return (_controlBlock) ? _controlBlock->object : nullptr;
    }

    explicit operator bool() const
    {
        return _controlBlock && _controlBlock->object;
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
        if (_controlBlock)
        {
            _controlBlock->ReleaseRef();
            _controlBlock = nullptr;
        }
    }

    ~Pointer()
    {
        Reset();
    }
};
