#include <algorithm>
#include <filesystem>
#include <cstdlib>
#include <vector> //TODO MAKE MY OWN CONTAINER
#include <fstream>
#include <string>
#include <unordered_set>
#include <iostream>

#define GREEN_TEXT(text) ("\033[32m" + std::string(text) + "\033[0m")
namespace fs = std::filesystem;
std::string OLD_PROJ_NAME_BUF;
std::string NEW_PROJ_NAME_BUF;

void run_bash_script(const fs::path& script_path);
void replace_entries_in_file(const fs::path& file_path,const std::string& old_entry,const std::string& new_entry);
std::string extract_name(const std::string& input);

std::string to_lower(std::string s);
std::string to_upper(std::string s);
std::string capitalize(std::string s);

void print_green_message(std::string_view text) {
    std::cout << GREEN_TEXT(text) << "\n";
}

const fs::path HOME_DIR_PATH =   std::getenv("HOME");
const fs::path TEMP_MONO_PATH =  "";

const fs::path PROJ_PATH =       TEMP_MONO_PATH / "";
const fs::path TRANSLATES_PATH = TEMP_MONO_PATH / "";
const fs::path BASH_GEN_PATH =   TEMP_MONO_PATH / "";

fs::path PROJ_DIR_SOURCE_PATH = HOME_DIR_PATH / PROJ_PATH;


std::vector<std::string> get_directories(const fs::path& path) {
    std::vector<std::string> directories;

    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_directory()) {
            directories.push_back(entry.path().filename().string());
        }
    }

    return directories;
}

void draw_directories_menu(const std::vector<std::string>& dirs) {
    std::size_t count = 1;
    for (const auto& dir : dirs) {
        std::cout << count++ << ". " << dir << "\n";
    }
}

void copy_dir(const fs::path& base_path, const std::vector<std::string>& directories) {
    std::size_t choice = 0;
    std::string new_project_name;

    std::cout << "Choose project to clone (number): ";
    std::cin >> choice;

    if (choice == 0 || choice > directories.size()) {
        std::cerr << "Invalid choice!\n";
        return;
    }

    OLD_PROJ_NAME_BUF = directories[choice - 1];
    fs::path source_dir = base_path / directories[choice - 1];

    if (!fs::exists(source_dir)) {
        std::cerr << "Source directory doesn't exist!\n";
        return;
    }

    std::cout << "Enter new project name: ";
    std::cin >> new_project_name;
    NEW_PROJ_NAME_BUF = new_project_name;


     fs::path destination_dir = base_path / new_project_name;

     if (fs::exists(destination_dir)) {
         std::cerr << "Directory already exists: " << destination_dir << "\n";
         return;
     }

    fs::create_directory(destination_dir);
    fs::copy(source_dir, destination_dir, fs::copy_options::recursive);

    std::cout << "Project cloned to: " << destination_dir << "\n";
}

void add_to_kt_enums() {
    std::vector<fs::path> kotlin_pathes{
        (HOME_DIR_PATH / TEMP_MONO_PATH / ""),
        (HOME_DIR_PATH / TEMP_MONO_PATH / "")
    };
    std::string newEntrie;
    std::cout << "enter name, for kt enum like STARZBET_IN: ";
    std::cin >> newEntrie;

    for(const auto& filePath : kotlin_pathes) {
        std::ifstream file(filePath);
        if (!file) {
            std::cerr << "Failed to open file: " << filePath << "\n";
            continue;
        }

        std::string content(std::istreambuf_iterator<char>(file), {});
        file.close();

        size_t lastBrace = content.rfind(';');
        if (lastBrace == std::string::npos) {
            std::cerr << "Invalid enum file format: " << filePath << "\n";
            continue;
        }

        // Find the last semicolon before the closing brace
        size_t lastSemicolon = content.rfind(',', lastBrace);
        if (lastSemicolon == std::string::npos) {
            std::cerr << "No enum entries found in: " << filePath << "\n";
            continue;
        }

        std::string newContent = content.substr(0, lastSemicolon + 1) +
                               "\n    " + newEntrie + "\n    " +
                               content.substr(lastBrace);

        // Write changes back to file
        std::ofstream outFile(filePath);
        if (!outFile) {
            std::cerr << "Failed to write to file: " << filePath << "\n";
            continue;
        }
        outFile << newContent;
        outFile.close();
        std::cout << "Added new enum entry to: " << filePath << "\n";
    }
}

void copy_tranlates_and_replace_entries(const std::string& path) {
    auto oldName = extract_name(OLD_PROJ_NAME_BUF);
    auto newName = extract_name(NEW_PROJ_NAME_BUF);

    for (const auto& entry : fs::directory_iterator(path)) {
        const auto& filePath = entry.path();
        const auto& fileName = filePath.filename().string();

        if (fileName.substr(0, oldName.size()) == oldName) {
            std::string newFilename = newName + fileName.substr(oldName.size());

            fs::path destinationPath = filePath;
            destinationPath.replace_filename(newFilename);

            fs::copy(filePath, destinationPath);

            replace_entries_in_file(destinationPath, oldName, newName);

            std::cout << "Created: " << destinationPath << "\n";
        }
    }
}

void replace_entries_by_dir_path(const fs::path& path) {
    auto old_entry = extract_name(OLD_PROJ_NAME_BUF);
    auto new_entry = extract_name(NEW_PROJ_NAME_BUF);

    //TODO ENG DOC
    // для удобства поиска. будет медленнее и хуже вектора на таком количестве элементов. мб потом перепишу
    static const std::unordered_set<std::string> text_extensions = {
        ".ts", ".tsx", ".js", ".jsx", ".json", ".md", ".yml", ".yaml",
        ".html", ".mjs", ".cjs", ".txt"
    };

    static const std::unordered_set<std::string> binary_extensions = {
        ".png", ".jpg", ".jpeg", ".gif", ".ico", ".svg", ".woff", ".woff2",
        ".ttf", ".eot", ".mp4", ".webm", ".mp3", ".wav", ".pdf", ".zip"
    };

    try {
        for (const auto& entry : fs::recursive_directory_iterator(path)) {
            try {
                if (!entry.is_regular_file() || entry.is_symlink()) {
                    continue;
                }

                const auto& ext = entry.path().extension().string();

                if (binary_extensions.find(ext) != binary_extensions.end()) {
                    continue;
                }

                if (text_extensions.find(ext) != text_extensions.end() || ext.empty()) {
                    replace_entries_in_file(entry.path(), old_entry, new_entry);
                }
            } catch (const fs::filesystem_error& e) {
                std::cerr << "Error processing " << entry.path() << ": " << e.what() << std::endl;
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Directory error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "General error: " << e.what() << std::endl;
    }
}
/*
int main() {
    try {
        fs::path translates_dir_sorce = HOME_DIR_PATH / TRANSLATES_PATH;

         if (!fs::exists(PROJ_DIR_SOURCE_PATH)) {
             std::cerr << "Path does not exist: " << PROJ_DIR_SOURCE_PATH << "\n";
             return 1;
         }

         auto proj_directories = get_directories(PROJ_DIR_SOURCE_PATH);

         if (proj_directories.empty()) {
             std::cout << "No projects found.\n";
             return 0;
         }

         draw_directories_menu(proj_directories);

         copy_dir(PROJ_DIR_SOURCE_PATH, proj_directories);

         copy_tranlates_and_replace_entries( translates_dir_sorce);

         add_to_kt_enums();

         replace_entries_by_dir_path(PROJ_DIR_SOURCE_PATH / NEW_PROJ_NAME_BUF);

         // Run both scripts in sequence
         print_green_message("Running first script...");
         run_bash_script(HOME_DIR_PATH / BASH_GEN_PATH);

         print_green_message("Running second script...");
         run_bash_script(HOME_DIR_PATH / BASH_GEN_PATH);

         print_green_message("all is done, dont forget to fix cms theme in store & update fav icon + logo");

    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << "\n";
    } catch (...) {
        std::cerr << "Unknown error occurred.\n";
    }

    return 0;
}
 */

void run_bash_script(const fs::path& script_path) {
    if (!fs::exists(script_path)) {
        std::cerr << "Script file does not exist: " << script_path << "\n";
        return;
    }

    // Get absolute path of the script directory
    fs::path script_dir = fs::absolute(script_path.parent_path());

    // chaging dir path before run bash.
    std::string command = "cd \"" + script_dir.string() + "\" && bash \"" + script_path.string() + "\"";
    int result = std::system(command.c_str());

    if (result != 0) {
        std::cerr << "Error while running script: " << script_path << "\n";
        std::cerr << "Exit code: " << result << "\n";
    } else {
        std::cout << "Script completed successfully: " << script_path << "\n";
    }
}


void replace_entries_in_file(const fs::path& file_path,
                           const std::string& old_entry,
                           const std::string& new_entry) {
    // reading file
    std::ifstream file(file_path);
    if (!file) {
        std::cerr << "Failed to open file: " << file_path << std::endl;
        return;
    }

    std::string content((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());
    file.close();

    // Create variations of old and new entries
    std::vector<std::pair<std::string, std::string>> replacements = {
        {old_entry, new_entry},
        {to_lower(old_entry), to_lower(new_entry)},
        {to_upper(old_entry), to_upper(new_entry)},
        {capitalize(old_entry), capitalize(new_entry)}
    };

    // file modifying
    bool modified = false;
    for (const auto& [old, new_str] : replacements) {
        size_t pos = 0;
        while ((pos = content.find(old, pos)) != std::string::npos) {
            content.replace(pos, old.length(), new_str);
            pos += new_str.length();
            modified = true;
        }
    }

    if (modified) {
        fs::path temp_path = file_path.string() + ".tmp";
        {
            std::ofstream out_file(temp_path);
            if (!out_file) {
                std::cerr << "Failed to write to temp file: " << temp_path << std::endl;
                return;
            }
            out_file << content;
        }

        // Атомарная замена файла
        std::error_code ec;
        fs::rename(temp_path, file_path, ec);
        if (ec) {
            std::cerr << "Failed to replace file: " << ec.message() << std::endl;
            fs::remove(temp_path, ec);
            return;
        }

        print_green_message("Modified: " + file_path.string());
    }
}

std::string extract_name(const std::string& input) {
    //mb need exeptions
    size_t first_dash = input.find('-');
    size_t last_dash = input.rfind('-');

    return input.substr(first_dash + 1, last_dash - first_dash - 1);
}

std::string to_lower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

std::string to_upper(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}

std::string capitalize(std::string s) {
    if (!s.empty()) {
        s[0] = static_cast<char>(std::toupper(s[0])); // + 32 -> convert to str with validation
        std::transform(s.begin() + 1, s.end(), s.begin() + 1, ::tolower);
    }
    return s;
}