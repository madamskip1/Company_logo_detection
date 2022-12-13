#pragma once
#include <string>
#include <vector>

void calcMomentsRange(std::string imageName);

std::vector<double> calcMedians(std::vector<std::vector<double>>& hu_values);
std::vector<double> calcSTDs(std::vector<std::vector<double>>& hu_values, std::vector<double>& avgMomentsValue);
void printMomentsInfo(std::vector<double>& minHuValues, std::vector<double>& maxHuValues, std::vector<double>& avgHuValues, std::vector<double>& stdHuValues, std::vector<double>& medianHuValues);
void writeMomentsToFile(std::vector<std::vector<double>>& hu_values);