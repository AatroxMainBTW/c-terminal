#include "FileSystem.h"

std::string currentFilePath;
bool docPrinted = false;
bool folderPrinted = false;


std::string formatSize(uintmax_t bytes) {
    if (bytes < 1024)
        return std::to_string(bytes) + " B";
    else if (bytes < 1024 * 1024)
        return std::to_string(bytes / 1024) + " KB";
    else if (bytes < 1024 * 1024 * 1024)
        return std::to_string(bytes / (1024 * 1024)) + " MB";
    else
        return std::to_string(bytes / (1024 * 1024 * 1024)) + " GB";
}

std::string file_type_to_string(std::filesystem::file_type type) {
	switch (type) {
	case std::filesystem::file_type::regular: return "regular file";
	case std::filesystem::file_type::directory: return "directory";
	case std::filesystem::file_type::symlink: return "symbolic link";
	case std::filesystem::file_type::block: return "block device";
	case std::filesystem::file_type::character: return "character device";
	case std::filesystem::file_type::fifo: return "FIFO/pipe";
	case std::filesystem::file_type::socket: return "socket";
	case std::filesystem::file_type::unknown: return "unknown";
	case std::filesystem::file_type::not_found: return "not found";
	default: return "unspecified";
	}
}


std::string getCurrentFilePath() {
	currentFilePath = std::filesystem::current_path().string();
	return currentFilePath;
}

/* Handle the command cd .. */
std::string goToParentPath() {
	if (std::filesystem::path(currentFilePath).has_parent_path()) {
		currentFilePath = std::filesystem::path(currentFilePath).parent_path().string();
		std::filesystem::current_path(currentFilePath);
	}
	return currentFilePath;
}


/* Handle full path as well as navigating in one folder */
std::string changeFilePath(std::string newPath) {
	if (std::filesystem::path(newPath).has_relative_path()) {
		currentFilePath = std::filesystem::path(newPath).string();
		std::filesystem::current_path(newPath);
	}	
	return currentFilePath;

}


void getFoldersAndDocumentsInCurrentPath() {
    const int COL1 = 10; // [FILE]/[DIR]
    const int COL2 = 40; // filename
    const int COL3 = 20; // file type

    for (const auto& entry : std::filesystem::directory_iterator(currentFilePath)) {
        if (!entry.is_directory()) {
            if (!docPrinted) std::cout << "[FILES] :" << std::endl;
            docPrinted = true;
            std::cout << "  "
                << std::left << std::setw(COL1) << "[FILE]"
                << std::left << std::setw(COL2) << entry.path().filename().string()
                << std::left << std::setw(COL3) << file_type_to_string(entry.status().type())
                << formatSize(entry.file_size()) << std::endl;
        }
        else {
            if (!folderPrinted) std::cout << "[DIRECTORIES] :" << std::endl;
            folderPrinted = true;
            setColor(BG_COLOR);
            std::cout << "  "
                << std::left << std::setw(COL1) << "[DIR]"
                << std::left << std::setw(COL2) << entry.path().filename().string()
                << std::left << std::setw(COL3) << file_type_to_string(entry.status().type());
            resetColor();         
            std::cout << std::endl;
        }
    }
   
    folderPrinted = false;
    docPrinted = false;
}
