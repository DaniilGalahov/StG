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

#define DATA_FILE_PATH "..\\..\\files\\data.txt"
#define CARRIER_FILE_PATH "..\\..\\files\\carrier.png"
#define EMBMASK_FILE_PATH "..\\..\\files\\embedding mask.png"
#define STEGO_FILE_PATH "..\\..\\files\\stego.png"

#define EMBEDDING_BLOCK_SIZE 8
#define EMBEDDING_TRESHOLD 0.7

#define PASSWORD "People are like water - they will always find a way."
