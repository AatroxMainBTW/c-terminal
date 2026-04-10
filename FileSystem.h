#pragma once
#include <string>
#include <filesystem>
#include <vector>
#include <iostream>
#include <iomanip>
#include "Color.h"


std::string getCurrentFilePath();

std::string goToParentPath();

std::string changeFilePath(std::string newPath);

void getFoldersAndDocumentsInCurrentPath();