#pragma once
#include <type_traits>
#include <typeinfo>
#include "Debug.h"

template<typename T>
class ControlBlock;

template<typename T>
class Pointer;

class Object
{
private:
    /// <summary>
    /// Destroy the object, break Pointer<T> references
    /// </summary>
    void FinalizeDestruction();
    virtual void OnFinalizeDestruction() {};

    /// <summary>
    /// Cue the object for destruction, will be destroyed after this frame
    /// </summary>
    void CueForDestruction();

    // Friend the Scene class to allow it to call Destroy()
    friend class Application;


    // Friend the Pointer class to allow it to get the ref_count
    template<typename T>
    friend class Pointer;

    std::size_t id;
    static inline long globalIdCounter = 0;

public:
    Object() : id(++globalIdCounter) {}
    std::size_t GetID() const { return id; }
    /// <summary>
    /// Reference to the control_block keeping track of the pointers, avoids memory leaks when destroying an object
    /// </summary>
    ControlBlock<Object>* _controlBlock = nullptr;

    /// <summary>
    /// Add object to the destruction queue, will be destroyed after this frame
    /// </summary>
    /// <typeparam name="T">the object type</typeparam>
    /// <param name="other">the object</param>
    template<typename T>
    static void Destroy(Pointer<T> other)
    {
        static_assert(std::is_base_of<Object, T>::value, "Type must be an object");
        other->CueForDestruction();
    }

    /// <summary>
    /// Destroy an object immediately, not recommended for during playmode. 
    /// </summary>
    /// <typeparam name="T">the object type</typeparam>
    /// <param name="other">the object</param>
    template<typename T>
    static void DestroyImmediate(Pointer<T> other)
    {
        static_assert(std::is_base_of<Object, T>::value, "Type must be an object");
        other->FinalizeDestruction();
        delete other.Get();
    }
    virtual ~Object();
};

