#include <iostream>
#include <fstream>
#include <unordered_map>

#include "tree.h"
#include "rb_tree.h"
#include "balanced_tree.h"
#include "bitmask_bitset.h"
#include "bitmask_vector.h"

#ifdef __APPLE__
#include "TargetConditionals.h"
#if TARGET_OS_MAC
#include <mach/mach.h>
#endif
#elif __linux__
#include <cstdlib>
#include <cstdio>
#include <cstring>
int parseLine(char* line);
int getValue();
#endif

void quit(const char *message);
data *create_data(std::string &line, uint32_t chunk_size);

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
    if (strncmp(argv[i], "-i", 2)==0) {
      if (i < argc - 1) {
        input_path = argv[++i];
      } else {
        quit("Input path not provided");
      }
    } else if (strncmp(argv[i], "-o", 2)==0) {
      if (i < argc - 1) {
        output_path = argv[++i];
      } else {
        quit("Output path not provided");
      }
    } else if (strncmp(argv[i], "-cs", 3)==0) {
      if (i < argc - 1) {
        chunk_size = (uint32_t) std::stoi(argv[++i]);
      } else {
        quit("Chunk size not provided");
      }
    } else if (strncmp(argv[i], "-c", 2)==0) {
      if (i < argc - 1) {
        command_path = argv[++i];
      } else {
        quit("Command file path not provided");
      }
    } else if (strncmp(argv[i], "-s", 2)==0) {
      show_stats = true;
    } else if (strncmp(argv[i], "-b", 2)==0) {
      use_bitmask = true;
    } else if (strncmp(argv[i], "-t", 2)==0) {
      use_rb = true;
    } else {
      quit("Invalid argument provided");
    }
  }

  std::ifstream command_file(command_path);
  std::ofstream output_file(output_path);

  std::istream &cmd_in = command_path==nullptr ? std::cin : command_file;
  std::ostream &data_out = output_path==nullptr ? std::cout : output_file;

  if (input_path==nullptr) {
    quit("Input file path is required");
  }

  std::ifstream data_in(input_path);

  if (!data_in.good()) {
    quit("Given input file doesn't exist.");
  }
  if (!data_out.good()) {
    quit("Given output file can't be written to.");
  }
  if (!cmd_in.good()) {
    quit("Given command file doesn't exist.");
  }

  CREATE c;
  if (use_bitmask) {
    c = &bitmask_bitset::create;
  } else {
    c = &bitmask_vector::create;
  }
  bitmask::set_creator(c);

  //--------------------------//
  // Create nodes             //
  //--------------------------//

  std::string line, name, content;
  std::vector<data *> data_chunks;
  while (!data_in.eof()) {
    std::getline(data_in, line);
    if (!line.empty() && line[0]!='>' && line[0]!=';') { // Identifier marker
      content += line;

      while (content.length() >= chunk_size) {
        data_chunks.push_back(create_data(content, chunk_size));
      }
    }
  }
  if (content.length()) {
    data_chunks.push_back(create_data(content, chunk_size));
  }

  //--------------------------//
  // Create tree              //
  //--------------------------//

  tree *t;
//  if (use_rb) {
//    t = new rb_tree();
//  } else {
//    t = new balanced_tree(data_chunks);
//  }
  t = new balanced_tree(data_chunks);

  //--------------------------//
  // Execute commands         //
  //--------------------------//

  char command;
  char symbol;
  uint32_t index;

  uint32_t res;
  while (!cmd_in.eof()) {
    cmd_in >> command >> symbol >> index;
    if (tolower(command)=='r') {
      data_out << "Rank(" << symbol << "," << index << "): ";
      try {
        res = t->rank(symbol, index);
        data_out << res;
      } catch (...) {
        data_out << "index out of bounds";
      }
    } else if (tolower(command)=='s') {
      data_out << "Select(" << symbol << "," << index << "): ";
      try {
        res = t->select(symbol, index);
        data_out << res;
      } catch (...) {
        data_out << "index out of bounds";
      }
    } else {
      std::cerr << "Unknown command" << std::endl;
      continue;
    }
    data_out << std::endl;
  }

  if (show_stats) {
#ifdef __APPLE__
#include "TargetConditionals.h"
#if TARGET_OS_MAC
    struct task_basic_info t_info;
    mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

    if (KERN_SUCCESS!=task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t) &t_info, &t_info_count)) {
      return -1;
    }
    std::cout << "Memory used: " << t_info.resident_size/1024 << " KB" << std::endl;
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

data *create_data(std::string &line, uint32_t chunk_size) {
  static std::unordered_map<char, uint32_t> counters;
  static std::string alphabet = "ACTG";

  uint32_t len = std::min(chunk_size, (uint32_t) line.length());
  std::string chunk = line.substr(0, len);

  std::transform(chunk.begin(), chunk.end(), chunk.begin(), ::toupper);

  line = line.substr(len);

  std::unordered_map<char, uint32_t> chars;

  for (char c : chunk) {
    chars[c] = chars[c] + 1;
  }

  std::string reduced_alpha;

  std::transform(chars.begin(),
                 chars.end(),
                 std::back_inserter(reduced_alpha),
                 [](auto &x) -> char { return x.first; });

  wavelet *_wavelet = new wavelet(chunk, reduced_alpha);
  data *_data = new data(counters, _wavelet);

  for (auto it : chars) {
    counters[it.first] = counters[it.first] + it.second;
  }

  return _data;
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
