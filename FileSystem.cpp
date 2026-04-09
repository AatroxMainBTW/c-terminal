#include "FileSystem.h"

std::string currentFilePath;

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

