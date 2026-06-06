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

#define EMBEDDING_BLOCK_SIZE 2 //2 for small pictures (128x128), 8 for generic photos
#define EMBEDDING_TRESHOLD 0.35 //for test purposes only! Use at least 0.5 for practical applications

#define PASSWORD "People are like water - they will always find a way."