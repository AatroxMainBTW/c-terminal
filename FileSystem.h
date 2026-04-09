#pragma once
#include <string>
#include <filesystem>
#include <iostream>


std::string getCurrentFilePath();

std::string goToParentPath();

std::string changeFilePath(std::string newPath);
