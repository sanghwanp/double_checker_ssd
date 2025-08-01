#pragma once

#define USING_COMMAND_BUFFER (1)

static constexpr char* STORAGE_FILE_NAME = "ssd_nand.txt";
static constexpr char* OUTPUT_FILE_NAME = "ssd_output.txt";

static constexpr unsigned int MAX_ERASE_SIZE = 10;
static constexpr unsigned int MAX_DATA_VALUE = 0xFFFFFFFF;
static constexpr int MAX_LBA_CNT = 100;
static constexpr int MAX_STORAGE_IDX = MAX_LBA_CNT;
static constexpr int MAX_STORAGE_SIZE = MAX_LBA_CNT * sizeof(int);
