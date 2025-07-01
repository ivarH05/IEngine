#pragma once
#include <typeinfo>

#include "Object.h"
#include "JsonConverter.h"
#include "FOREACH.h"

#include <iostream>

/// Sub macro, serializes just one variable
#define SERIALIZEVARIABLE(name) \
        result += "\"" + std::string(#name) + "\": " + JsonConverter::Serialize(name) + ", ";

#define DESERIALIZEVARIABLE(name) \
    valueStr = JsonConverter::ExtractField(serializedData, #name); \
    std::cout << valueStr << "\n\n"; \
    if (!valueStr.empty()) { \
        name = JsonConverter::Deserialize<decltype(name)>(valueStr); \
    } \


/// Serialize the specified fields
#define SerializeFields(...) \
public: \
    std::string Serialize() const override { \
        std::string result = "{ \"Type\": " + std::string(typeid(*this).name()) + ", "; \
        FOREACH(SERIALIZEVARIABLE, __VA_ARGS__) \
        result += std::string(" }"); \
        return result; \
    } \
    void Deserialize(std::string serializedData) override { \
        std::string valueStr; \
        FOREACH(DESERIALIZEVARIABLE, __VA_ARGS__) \
    }


/// Create a new serialized object
#define SerializableObject(name, ...) \
class name : public __VA_ARGS__ \
{ \

class SerializableBehaviour : public Object
{
public:
    virtual std::string Serialize() const { return ""; };
    virtual void Deserialize(std::string serializedData) {};
};