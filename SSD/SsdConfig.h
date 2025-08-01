#pragma once

static constexpr char* STORAGE_FILE_NAME = "ssd_nand.txt";
static constexpr char* READ_OUTPUT_FILE_NAME = "output.txt";

static constexpr unsigned int MAX_DATA_VALUE = 0xFFFFFFFF;
static constexpr int MAX_LBA_CNT = 100;
static constexpr int MAX_STORAGE_IDX = MAX_LBA_CNT;
static constexpr int MAX_STORAGE_SIZE = MAX_LBA_CNT * sizeof(int);
