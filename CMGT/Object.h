#pragma once

template<typename T>
class Pointer;
template<typename T>
class ControlBlock;

class Object
{
private:
    /// <summary>
    /// Destroy the object, block other objects from referencing it
    /// </summary>
    void Destroy();

    /// <summary>
    /// Reference to the control_block keeping track of the pointers, avoids memory leaks when destroying an object
    /// </summary>
    ControlBlock<Object>* _controlBlock = nullptr;

    // Friend the Scene class to allow it to get the ref_count
    friend class Pointer<Object>;
    // Friend the Scene class to allow it to call Destroy()
    friend class Application;

protected:
    virtual void OnDestroy() {}

public:
    /// <summary>
    /// Destroy after the frame. 
    /// </summary>
    /// <param name="other"></param>
    void Destroy(Pointer<Object>);

};

