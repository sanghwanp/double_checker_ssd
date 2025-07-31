#pragma once

struct SSDConfig {
  static constexpr int kStorageSize = 100;
  static constexpr int kStorageInitValue = 0;
  static constexpr char* SSD_NAND_TXT_FILEPATH = "C:\\ssd_nand.txt";
  static constexpr char* SSD_OUTPUT_TXT_FILEPATH = "C:\\ssd_output.txt";
};

static constexpr char* STORAGE_FILE_NAME = "ssd_nand.txt";
static constexpr char* READ_OUTPUT_FILE_NAME = "output.txt";

static constexpr int MAX_LBA_CNT = 100;
static constexpr int MAX_STORAGE_IDX = MAX_LBA_CNT;
static constexpr int MAX_STORAGE_SIZE = MAX_LBA_CNT * sizeof(int);
