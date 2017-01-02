#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unistd.h> /* getopt */
#include <vector>
#include <chrono>
#include "bitmask.h"
#include "bitmask_bitset.h"
#include "bitmask_vector.h"
#include "data.h"
#include "rank_select.h"
#include "lookup_list.h"
#include "rb_tree.h"

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

#define SET_ARG(path) if (path.length()) {usage(argv[0]); } path = optarg

int64_t clock_diff(const std::chrono::steady_clock::time_point &start,
                   const std::chrono::steady_clock::time_point &end) {
  return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

void quit(const char *message);
void usage(const char *prog_name);

int main(int argc, char **argv) {
  //--------------------------//
  // Read and check arguments //
  //--------------------------//

  std::string input_path;
  std::string output_path;
  std::string command_path;

  uint32_t word_size = 1024;

  bool show_stats = false;
  bool use_vector = false;
  bool use_rb = false;

  int ch;
  while ((ch = getopt(argc, argv, "o:c:w:svt"))!=-1) {
    switch (ch) {
      case 'o': SET_ARG(output_path);
        break;
      case 'c': SET_ARG(command_path);
        break;
      case 'w': word_size = (uint32_t) std::stoi(optarg);
        break;
      case 's': show_stats = true;
        break;
      case 'v': use_vector = true;
        break;
      case 't': use_rb = true;
        break;
      default:std::cerr << "Invalid argument " << ch << std::endl;
    }
  }

  if (argc - optind!=1) { usage(argv[0]); }
  input_path = argv[optind];

  std::ifstream command_file(command_path);
  std::ofstream output_file(output_path);

  std::istream &cmd_in = command_path.length() ? command_file : std::cin;
  std::ostream &data_out = output_path.length() ? output_file : std::cout;

  if (input_path.length()==0) {
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

  std::function<bitmask *(uint32_t)> c;
  if (!use_vector) {
    c = bitmask_bitset::create;
    std::cerr << "Using bitset as bitmask (constant time rank/select)..." << std::endl;
  } else {
    c = bitmask_vector::create;
    std::cerr << "Using vector of bools as bitmask (linear time rank/select)..." << std::endl;
  }
  bitmask::set_creator(c);

  //--------------------------//
  // Create nodes             //
  //--------------------------//

  auto create_nodes_start = std::chrono::steady_clock::now();

  std::string line, name, content;
  std::vector<data *> data_chunks;

  std::unordered_map<char, uint32_t> counters;

  while (!data_in.eof()) {
    std::getline(data_in, line);
    if (!line.empty() && line[0]!='>' && line[0]!=';') { // Identifier marker
      content += line;

      while (content.length() >= word_size) {
        data_chunks.push_back(data::create(content, word_size, counters));
      }
    }
  }
  if (content.length()) {
    data_chunks.push_back(data::create(content, word_size, counters));
  }

  auto create_nodes_end = std::chrono::steady_clock::now();

  if (show_stats) {
    std::cerr << "Creating nodes took: "
              << clock_diff(create_nodes_start, create_nodes_end)
              << " milliseconds"
              << std::endl;
  }

  //--------------------------//
  // Create tree              //
  //--------------------------//

  auto create_tree_start = std::chrono::steady_clock::now();

  rank_select *t;
  if (use_rb) {
    t = new rb_tree(data_chunks);
    std::cerr << "Using red black tree for lookup..." << std::endl;
  } else {
    t = new lookup_list(data_chunks);
    std::cerr << "Using zmedi tree for lookup..." << std::endl;
  }

  auto create_tree_end = std::chrono::steady_clock::now();

  if (show_stats) {
    std::cerr << "Creating tree took: "
              << clock_diff(create_tree_start, create_tree_end)
              << " milliseconds"
              << std::endl;
  }

  //--------------------------//
  // Execute commands         //
  //--------------------------//

  char command;
  char symbol;
  uint32_t index;

  auto cmd_exec_start = std::chrono::steady_clock::now();

  uint32_t res;
  uint32_t num_cmds = 0;
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
      num_cmds++;
    } else if (tolower(command)=='s') {
      data_out << "Select(" << symbol << "," << index << "): ";
      try {
        res = t->select(symbol, index);
        data_out << res;
      } catch (...) {
        data_out << "index out of bounds";
      }
      num_cmds++;
    } else {
      std::cerr << "Unknown command" << std::endl;
      continue;
    }
    data_out << std::endl;
  }

  auto cmd_exec_stop = std::chrono::steady_clock::now();

  if (show_stats) {
    auto millis = clock_diff(cmd_exec_start, cmd_exec_stop);
    std::cerr << "Executing " << num_cmds << " commands took: "
              << millis << " milliseconds " << std::endl
              << "Average time/command = " << (1.*millis/num_cmds) << " milliseconds" << std::endl;
  }

  if (show_stats) {
#ifdef __APPLE__
#if TARGET_OS_MAC
    struct task_basic_info t_info;
    mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

    if (KERN_SUCCESS!=task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t) &t_info, &t_info_count)) {
      return -1;
    }
    std::cerr << "Memory used: " << t_info.resident_size/1024 << " KB" << std::endl;
#else
    std::cerr << "Memory stats not supported on this OS" << std::endl;
#endif
#elif __linux__

    std::cerr << "Memory used: " << getValue() << " KB" << std::endl;
#endif
  }

  return 0;
}

void usage(const char *prog_name) {
  std::cerr << prog_name << " [options] input_file"
            << "\n\t-o output_file   [default=stdout]"
            << "\n\t-c commands_file [default=stdin]"
            << "\n\t-w word_size     [default=1024]"
            << "\n\t-s               [show statistics]"
            << "\n\t-v               [use bool vector instead of bitmask]"
            << "\n\t-t               [use red-black tree instead of lookup list]"
            << std::endl;
  exit(-1);
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

