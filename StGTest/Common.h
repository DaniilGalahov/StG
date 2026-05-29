#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <string>
#include <opencv2/opencv.hpp>

std::vector<uint8_t> LoadFromFile(std::string filePath);

void WriteToFile(std::vector<uint8_t> bytes, std::string filePath);

std::vector<uint8_t> ToBytes(std::string str);

bool AreEqual(const cv::Mat& a, const cv::Mat& b);