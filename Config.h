#ifndef CONFIG_H
#define CONFIG_H

#include <string>

class Config
{
public:
    Config();
    explicit Config(const std::string& filePath);

    int getHitDuration() const;
    int getPaintBlobLimit() const;
    int getRockLowerBound() const;
    int getRockUpperBound() const;
    int getFogLowerBound() const;
    int getFogUpperBound() const;
    int getLongRangeLimit() const;

private:
    int m_hitDuration;
    int m_paintBlobLimit;
    int m_rockLowerBound;
    int m_rockUpperBound;
    int m_fogLowerBound;
    int m_fogUpperBound;
    int m_longRangeLimit;

    void setDefaults();
    void loadFromFile(const std::string& filePath);
};

#endif
