#include <print>
#include "Config.h"
#include "UpdateManager.h"

int main() {
    Config config;
    UpdateManager update;

    std::println("Updating the software version...");
    auto load = config.loadJsonConfig("./config.json");
    if (!load) {
        std::println(stderr, "Error: {}", static_cast<unsigned int>(load.error()));
        return 1;
    }

    const std::string url = config.getUrl();
    const std::string targetDir = config.getTargetDir();
    const std::string zipFilename = config.getZipFilename();

    std::println("Downloading the update package...");
    auto download = update.downloadUpdate(url, zipFilename);
    if (!download) {
        std::println(stderr, "Error: {}", static_cast<unsigned int>(download.error()));
        return 2;
    }

    std::println("Extract zip file into {}...", targetDir);
    auto extract = update.extractUpdate(zipFilename, targetDir);
    if (!extract) {
        std::println(stderr, "Error: {}", static_cast<unsigned int>(extract.error()));
        return 3;
    }

    std::println("Atualização aplicada com sucesso em: {}", targetDir);

    return 0;
}
