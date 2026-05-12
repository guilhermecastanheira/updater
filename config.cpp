#include "config.h"
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::string Config::getUrl() const {
    return this->url;
}

std::string Config::getTargetDir() const {
    return this->targetDir;
}

std::string Config::getZipFilename() const {
    return this->zipName;
}

/**
 * @brief Load the Json file with all configurations.
 *        From now, the config.json file is static and should be into the targetDir.
 *
 * @param configFile Json configuration file
 * @return Success if all the configurations were readed
 *         Fails if Json file is wrong or did not exists.
 */
std::expected<void, ConfigError> Config::loadJsonConfig(const std::string& configFile) {
    if (!std::filesystem::exists(configFile)) {
        return std::unexpected(ConfigError::ConfigFileNotFound);
    }

    std::ifstream file(configFile);
    json data;

    try {
        //parsing file into json data
        file >> data;

        //defining config. variables
        this->url = data["update_url"];
        this->zipName = data["zip_filename"];
        this->targetDir = data["target_directory"];

        return {};
    }
    catch (const json::parse_error& e) {
        return std::unexpected(ConfigError::JsonParseError);
    }
    catch (const json::type_error& e) {
        return std::unexpected(ConfigError::JsonTypeError);
    }
    catch (...) {
        return std::unexpected(ConfigError::UndefinedError);
    }
}
