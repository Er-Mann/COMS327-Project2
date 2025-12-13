#include "Config.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace
{
    void trim(std::string& s)
    {
        auto notSpace = [](int ch) { return !std::isspace(ch); };

        s.erase(s.begin(),
                std::find_if(s.begin(), s.end(), notSpace));

        s.erase(std::find_if(s.rbegin(), s.rend(), notSpace).base(),
                s.end());
    }

    std::string toUpper(const std::string& s)
    {
        std::string result = s;
        for (std::string::size_type i = 0; i < result.size(); ++i)
        {
            result[i] = static_cast<char>(
                std::toupper(static_cast<unsigned char>(result[i])));
        }
        return result;
    }

    int parseInt(const std::string& s)
    {
        std::istringstream iss(s);
        int value = 0;
        if (!(iss >> value))
        {
            throw std::runtime_error(
                "Invalid integer value in configuration file: '" + s + "'");
        }
        std::string rest;
        if (iss >> rest)
        {
            throw std::runtime_error(
                "Extra characters after integer in configuration file: '" + s + "'");
        }
        return value;
    }
}

void Config::setDefaults()
{
    m_hitDuration = 20;
    m_paintBlobLimit = 30;
    m_rockLowerBound = 10;
    m_rockUpperBound = 20;
    m_fogLowerBound = 5;
    m_fogUpperBound = 10;
    m_longRangeLimit = 30;
}

Config::Config()
{
    setDefaults();
}

Config::Config(const std::string& filePath)
{
    setDefaults();
    loadFromFile(filePath);
}

void Config::loadFromFile(const std::string& filePath)
{
    std::ifstream in(filePath.c_str());
    if (!in)
    {
        throw std::runtime_error("Unable to open configuration file: " + filePath);
    }

    std::string line;
    int lineNumber = 0;
    while (std::getline(in, line))
    {
        ++lineNumber;
        std::string originalLine = line;

        trim(line);

        if (line.empty())
        {
            continue;
        }

        if (!line.empty() && line[0] == '#')
        {
            continue;
        }

        std::string::size_type eqPos = line.find('=');
        if (eqPos == std::string::npos)
        {
            throw std::runtime_error(
                "Missing '=' on configuration line " +
                std::to_string(lineNumber) + ": '" + originalLine + "'");
        }

        std::string key = line.substr(0, eqPos);
        std::string value = line.substr(eqPos + 1);

        trim(key);
        trim(value);

        if (key.empty() || value.empty())
        {
            throw std::runtime_error(
                "Empty keyword or value on configuration line " +
                std::to_string(lineNumber) + ": '" + originalLine + "'");
        }

        std::string keyUpper = toUpper(key);

        int intValue = parseInt(value);

        if (keyUpper == "HIT_DURATION")
        {
            m_hitDuration = intValue;
        }
        else if (keyUpper == "PAINTBLOB_LIMIT")
        {
            m_paintBlobLimit = intValue;
        }
        else if (keyUpper == "ROCK_LOWER_BOUND")
        {
            m_rockLowerBound = intValue;
        }
        else if (keyUpper == "ROCK_UPPER_BOUND")
        {
            m_rockUpperBound = intValue;
        }
        else if (keyUpper == "FOG_LOWER_BOUND")
        {
            m_fogLowerBound = intValue;
        }
        else if (keyUpper == "FOG_UPPER_BOUND")
        {
            m_fogUpperBound = intValue;
        }
        else if (keyUpper == "LONG_RANGE_LIMIT")
        {
            m_longRangeLimit = intValue;
        }
        else
        {
            throw std::runtime_error(
                "Unknown configuration keyword '" + key +
                "' on line " + std::to_string(lineNumber));
        }
    }
}

int Config::getHitDuration() const
{
    return m_hitDuration;
}

int Config::getPaintBlobLimit() const
{
    return m_paintBlobLimit;
}

int Config::getRockLowerBound() const
{
    return m_rockLowerBound;
}

int Config::getRockUpperBound() const
{
    return m_rockUpperBound;
}

int Config::getFogLowerBound() const
{
    return m_fogLowerBound;
}

int Config::getFogUpperBound() const
{
    return m_fogUpperBound;
}

int Config::getLongRangeLimit() const
{
    return m_longRangeLimit;
}
