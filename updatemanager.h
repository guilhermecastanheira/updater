#ifndef UPDATEMANAGER_H
#define UPDATEMANAGER_H

#include <string>
#include <expected>

enum class UpdateError : uint8_t {
    NetworkFailure = 0,
    ExtractionFailure,
    InvalidDir
};

class UpdateManager
{
public:
    UpdateManager() = default;
    ~UpdateManager() = default;

    std::expected<std::string, UpdateError> downloadUpdate(const std::string& url, const std::string& outputFile);
    std::expected<void, UpdateError> extractUpdate(const std::string& zipFile, const std::string& targetDir);
};

#endif // UPDATEMANAGER_H
