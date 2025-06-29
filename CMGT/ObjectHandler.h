#pragma once

#include <functional>
#include <algorithm>
#include <type_traits>
#include <unordered_map>
#include <string>

#include "Event.h"
#include "Object.h";


/// <summary>
/// ObjectHandler keeps track of all methods that should commonly be called during runtime
/// </summary>
class ObjectHandler : public Object
{
public:
    template<typename T>
    void Register(T* component);
    template<typename T>
    void Unregister(T* component);

    void StartAll();
    void FixedUpdateAll();
    void UpdateAll();
    void LateUpdateAll();
    void DrawGizmosAll();

private:
    std::unordered_map<std::string, std::function<void()>> _registeredDelegates = std::unordered_map<std::string, std::function<void()>>();

    Event<> onStart;
    Event<> onFixedUpdate;
    Event<> onUpdate;
    Event<> onLateUpdate;
    Event<> onDrawGizmos;
};


/* 
* A macro, basically a template for compile time methods. 
* 
* basically: 
* Initialize the macro DEFINE_HAS_METHOD, requiring a method name (not a string) as input
* 
* Create a new template class called Has_[MethodName]Method
* static assert if the class of tyep U has a method of name [MethodName]
* 
* Declare either a true_type or a false_type, and store it in value
* 
* I originally copy pasted this method 5 time 
* chat GPT suggested using macros for shorter code at the cost of a little readability
*/
#define DEFINE_HAS_METHOD(MethodName)                                   \
template<typename T>                                                    \
class has_##MethodName {                                                \
private:                                                                \
    template<typename U> static auto test(U* ptr)                       \
        -> decltype(ptr->MethodName(), std::true_type());               \
    template<typename> static std::false_type test(...);                \
public:                                                                 \
    static constexpr bool value = decltype(test<T>(nullptr))::value;    \
}


// Run the macro for each searched method, behaves similar to echo in php, it just plops the code exactly where you call the macro. 
DEFINE_HAS_METHOD(Awake);
DEFINE_HAS_METHOD(OnEnable);
DEFINE_HAS_METHOD(OnDisable);
DEFINE_HAS_METHOD(OnDestroy);

DEFINE_HAS_METHOD(Update);
DEFINE_HAS_METHOD(Start);
DEFINE_HAS_METHOD(FixedUpdate);
DEFINE_HAS_METHOD(LateUpdate);
DEFINE_HAS_METHOD(DrawGizmos);

/*
* A macro, uses Has_[MethodName] (initialized using the macro above)
* 
* It uses Has_[MethodName] to check if the component has the specified method,
* if so, it should add it to the list [listName]. 
*/
#define REGISTER_METHOD(MethodName, EventName)                           \
    if constexpr (has_##MethodName<T>::value) {                          \
        auto MethodName##_Delegate = [component](auto&&... args) {       \
            component->MethodName(std::forward<decltype(args)>(args)...);\
        };                                                               \
        EventName.AddListener(MethodName##_Delegate);                   \
        _registeredDelegates[#MethodName] = MethodName##_Delegate;      \
    }

#define UNREGISTER_METHOD(MethodName, EventName)                         \
    if constexpr (has_##MethodName<T>::value) {                          \
        EventName.RemoveListener(_registeredDelegates[#MethodName]);    \
        _registeredDelegates.erase(#MethodName);                         \
    }


// On register, check all methods and if it has a method, make sure it would be called during the next loop
// Uses the macro Register_Method (seen above)
template<typename T>
void ObjectHandler::Register(T* component)
{
    REGISTER_METHOD(Start, onStart);
    REGISTER_METHOD(FixedUpdate, onFixedUpdate);
    REGISTER_METHOD(Update, onUpdate);
    REGISTER_METHOD(LateUpdate, onLateUpdate);
    REGISTER_METHOD(DrawGizmos, onDrawGizmos);
}

// Unregister, remove all assigned methods from that component from the loop. 
template<typename T>
void ObjectHandler::Unregister(T* component)
{
    UNREGISTER_METHOD(Start, onStart);
    UNREGISTER_METHOD(FixedUpdate, onFixedUpdate);
    UNREGISTER_METHOD(Update, onUpdate);
    UNREGISTER_METHOD(LateUpdate, onLateUpdate);
    UNREGISTER_METHOD(DrawGizmos, onDrawGizmos);

}
