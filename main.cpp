#include <iostream>
#include <fstream>

#include "tree.h"
#include "rb_tree.h"
#include "balanced_tree.h"

#ifdef __APPLE__
#include "TargetConditionals.h"
#if TARGET_OS_MAC
#include <mach/mach.h>
#endif
#elif __linux__
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int parseLine(char* line);
int getValue();
#endif

void quit(const char *message);

int main(int argc, char **argv) {

  //--------------------------//
  // Read and check arguments //
  //--------------------------//

  char *input_path = nullptr;
  char *output_path = nullptr;
  char *command_path = nullptr;

  uint32_t chunk_size = 1024;

  bool show_stats = false;
  bool use_bitmask = false;
  bool use_rb = false;

  for (int i = 1; i < argc; ++i) {
    if (strncmp(argv[i], "-i", 2) == 0) {
      if (i < argc - 1) {
        input_path = argv[++i];
      } else {
        quit("Input path not provided");
      }
    } else if (strncmp(argv[i], "-o", 2) == 0) {
      if (i < argc - 1) {
        output_path = argv[++i];
      } else {
        quit("Output path not provided");
      }
    } else if (strncmp(argv[i], "-cs", 3) == 0) {
      if (i < argc - 1) {
        chunk_size = (uint32_t) std::stoi(argv[++i]);
      } else {
        quit("Chunk size not provided");
      }
    } else if (strncmp(argv[i], "-c", 2) == 0) {
      if (i < argc - 1) {
        command_path = argv[++i];
      } else {
        quit("Command file path not provided");
      }
    } else if (strncmp(argv[i], "-s", 2) == 0) {
      show_stats = true;
    } else if (strncmp(argv[i], "-b", 2) == 0) {
      use_bitmask = true;
    } else if (strncmp(argv[i], "-t", 2) == 0) {
      use_rb = true;
    }
  }

  if (input_path == nullptr) {
    quit("Input file path is required");
  }
  if (output_path == nullptr) {
    quit("Output file path is required");
  }
  if (command_path == nullptr) {
    quit("Command file path is required");
  }

  std::ifstream input_file(input_path);
  if (!input_file.good()) {
    quit("Given input file doesn't exist.");
  }
  std::ifstream output_file(output_path);
  std::ifstream command_file(command_path);
  if (!command_file.good()) {
    quit("Given command file doesn't exist.");
  }

  //--------------------------//
  // Create nodes             //
  //--------------------------//



  //--------------------------//
  // Create tree              //
  //--------------------------//

  tree *t;
//  if (use_rb) {
//    t = new rb_tree();
//  } else {
//    t = new balanced_tree();
//  }

  //--------------------------//
  // Execute commands         //
  //--------------------------//

  char command;
  char symbol;
  uint32_t index;

  while (command_file >> command >> symbol >> index) {
    if (command == 'r') {
      t->rank(symbol, index);
    } else {
      t->select(symbol, index);
    }
  }

  if (show_stats) {
#ifdef __APPLE__
#include "TargetConditionals.h"
#if TARGET_OS_MAC
    struct task_basic_info t_info;
    mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

    if (KERN_SUCCESS != task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t) &t_info, &t_info_count)) {
      return -1;
    }
    std::cout << "Memory used: " << t_info.resident_size / 1024 << " KB" << std::endl;
#else
    std::cerr << "Memory stats not supported on this OS" << std::endl;
#endif
#elif __linux__

    std::cout << "Memory used: " << getValue() << " KB" << std::endl;
#endif
  }

  return 0;
}

void quit(const char *message) {
  std::cerr << message << std::endl;
  exit(-1);
}

#if __linux__
int parseLine(char* line) {
  int i = (int) strlen(line);
  const char* p = line;
  while (*p <'0' || *p > '9') p++;
  line[i-3] = '\0';
  i = atoi(p);
  return i;
}

int getValue() {
  FILE* file = fopen("/proc/self/status", "r");
  int result = -1;
  char line[128];

  while (fgets(line, 128, file) != NULL){
    if (strncmp(line, "VmSize:", 7) == 0){
      result = parseLine(line);
      break;
    }
  }
  fclose(file);
  return result;
}
#endif
