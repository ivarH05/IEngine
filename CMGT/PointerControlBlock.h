#pragma once

template<typename T>
class ControlBlock
{
public:
    T* object;
    int ref_count = 0;

    ControlBlock(T* obj) : object(obj), ref_count(1) {}

    void AddRef()
    {
        ++ref_count;
    }

    void ReleaseRef()
    {
        if (--ref_count <= 0)
        {
            if (object != nullptr)
            {
                T* temp = object;
                object = nullptr;
                delete(object);
            }
            delete(this);
        }
    }

    void OnObjectDestroyed()
    {
        object = nullptr;
    }

    ~ControlBlock()
    {
        OnObjectDestroyed();
        if (object != nullptr)
            delete(object);
    }
};