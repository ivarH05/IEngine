#pragma once
#include <string>
#include <sstream>
#include <type_traits>

class SerializableBehaviour;

class JsonConverter
{
public:
    JsonConverter() = delete;

    template<typename T>
    static constexpr bool is_serialized_object = std::is_base_of<SerializableBehaviour, T>::value;

    template<typename T>
    static std::string Serialize(const T& value)
    {
        if constexpr (is_serialized_object<T>)
            return value.Serialize();
        else
            return ToString(value);
    }

    template<typename T>
    static T Deserialize(const std::string& str)
    {
        if constexpr (is_serialized_object<T>)
        {
            T obj;
            obj.Deserialize(str);
            return obj;
        }
        else
        {
            return FromString<T>(str);
        }
    }

    static std::string ExtractField(const std::string& json, const std::string& field)
    {
        std::string key = "\"" + field + "\"";
        size_t keyPos = json.find(key);
        if (keyPos == std::string::npos)
            return "";

        size_t colonPos = json.find(':', keyPos);
        if (colonPos == std::string::npos)
            return "";

        size_t valueStart = colonPos + 1;

        while (valueStart < json.size() && std::isspace(json[valueStart]))
            ++valueStart;

        if (json[valueStart] == '"')
        {
            size_t valueEnd = json.find('"', valueStart + 1);
            return json.substr(valueStart + 1, valueEnd - valueStart - 1);
        }

        if (json[valueStart] == '{')
        {
            int braceCount = 1;
            size_t i = valueStart + 1;
            while (i < json.size() && braceCount > 0)
            {
                if (json[i] == '{') braceCount++;
                else if (json[i] == '}') braceCount--;
                ++i;
            }
            return json.substr(valueStart, i - valueStart);
        }

        size_t valueEnd = valueStart;
        while (valueEnd < json.size() && json[valueEnd] != ',' && json[valueEnd] != '}')
            ++valueEnd;

        return json.substr(valueStart, valueEnd - valueStart);
    }

private:
    template<typename T>
    static std::enable_if_t<std::is_arithmetic_v<T>, std::string> ToString(const T& value)
    {
        return std::to_string(value);
    }

    static std::string ToString(const std::string& value) { return value; }
    static std::string ToString(const char* value) { return std::string(value); }

    template<typename T>
    static std::enable_if_t<!std::is_arithmetic_v<T> && !std::is_same_v<T, std::string> && !std::is_same_v<T, const char*>, std::string> ToString(const T& value)
    {
        static_assert( std::is_arithmetic_v<T> ||std::is_same_v<T, std::string> || std::is_same_v<T, const char*> ||is_serialized_object<T>,
            "ToString is not implemented for this type. Either make it a SerializedObject or add an explicit overload.");
    }

    template<typename T>
    static std::enable_if_t<std::is_arithmetic_v<T>, T>
        FromString(const std::string& str)
    {
        T value;
        std::istringstream iss(str);
        iss >> value;
        return value;
    }

    static std::string FromString(const std::string& str)
    {
        return str;
    }

    template<>
    static bool FromString<bool>(const std::string& str)
    {
        return str == "true" || str == "1";
    }
};