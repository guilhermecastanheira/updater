#include "updatemanager.h"
#include <zip.h>
#include <cpr/cpr.h>
#include <filesystem>

/**
 * @brief Downloads the update file (*.zip) through a given URL.
 *        A simple HTTP GET request and saves the binary steam to disk.
 *
 * @param url The web adress of zip file.
 * @param outputFile The the local path where the zip will be saved.
 *
 * @return Success returns a std::string with the outputFile.
 *         Fail returns the UpdateError::NetworkFailure, if the HTTP status is not 200 or if the network connection fails.
 */
std::expected<std::string, UpdateError> UpdateManager::downloadUpdate(const std::string& url, const std::string& outputFile) {
    std::ofstream os(outputFile, std::ios::binary);
    cpr::Response r = cpr::Download(os, cpr::Url{url});
    if (r.status_code != 200) {
        return std::unexpected(UpdateError::NetworkFailure);
    }
    return outputFile;
}

/**
 * @brief Extract the zip file into the target directory.
 *
 * @param zipFile The dowloaded zip file.
 * @param targetDir The target diractory to extract the zip file.
 *
 * @return Success returns void
 */
std::expected<void, UpdateError> UpdateManager::extractUpdate(const std::string& zipFile, const std::string& targetDir) {
    if (!std::filesystem::exists(targetDir)) {
        return std::unexpected(UpdateError::InvalidDir);
    }

    int result = zip_extract(zipFile.c_str(), targetDir.c_str(), nullptr, nullptr);
    if (result < 0) {
        return std::unexpected(UpdateError::ExtractionFailure);
    }

    return {};
}
