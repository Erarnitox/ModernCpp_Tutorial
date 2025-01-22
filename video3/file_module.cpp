module;

#include <print>
#include <string>
#include <filesystem>

export module file_module;

export namespace file_module {

void bulk_rename(const std::string& path) {
    namespace fs = std::filesystem;

    for (const auto& file : fs::directory_iterator(path)) {
        if (file.is_regular_file()) {
            const auto& filePath = file.path();
            const auto& parentPath = filePath.parent_path();
            const auto& filename = filePath.stem();  // File name without extension
            const auto& extension = filePath.extension();

            auto newFilename = filename.string() + "_this_rocks!" + extension.string();
            fs::path newFilePath = parentPath / newFilename;
            fs::rename(filePath, newFilePath);
        }   
    }
}
}