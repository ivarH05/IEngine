#pragma once
#include <type_traits>

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
    virtual void OnFinalizeDestruction() {  };

    /// <summary>
    /// Cue the object for destruction, will be destroyed after this frame
    /// </summary>
    void CueForDestruction();

    // Friend the Scene class to allow it to call Destroy()
    friend class Application;

    /// <summary>
    /// Reference to the control_block keeping track of the pointers, avoids memory leaks when destroying an object
    /// </summary>
    ControlBlock<Object>* _controlBlock = nullptr;

    // Friend the Pointer class to allow it to get the ref_count
    template<typename T>
    friend class Pointer;


public:
    /// <summary>
    /// Add object to the destruction queue, will be destroyed after this frame
    /// </summary>
    /// <typeparam name="T">the object type</typeparam>
    /// <param name="other">the object</param>
    template<typename T>
    void Destroy(Pointer<T> other)
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
    void DestroyImmediate(Pointer<T> other)
    {
        static_assert(std::is_base_of<Object, T>::value, "Type must be an object");
        other->FinalizeDestruction();
    }
};

