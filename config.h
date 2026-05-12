#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <expected>

enum class ConfigError : uint8_t {
    ConfigFileNotFound = 0,
    JsonParseError,
    JsonTypeError,
    UndefinedError
};

class Config
{
public:
    Config() = default;
    ~Config() = default;

    std::expected<void, ConfigError> loadJsonConfig(const std::string& configFile);

    //getters
    std::string getUrl() const;
    std::string getTargetDir() const;
    std::string getZipFilename() const;

private:
    std::string url = "";
    std::string zipName = "";
    std::string targetDir = "";
};

#endif // CONFIG_H
