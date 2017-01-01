#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unistd.h> /* getopt */
#include <cassert>

#define RUN_TEST

#include "rank_select.h"
#include "rb_tree.h"
#include "lookup_list.h"
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

#define SET_ARG(path) if (path.length()) {usage(argv[0]); } path = optarg

long long int clock_diff(const std::chrono::steady_clock::time_point &start,
                         const std::chrono::steady_clock::time_point &end) {
  return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

void quit(const char *message);
data *create_data(std::string &line, uint32_t word_size);
void usage(const char *prog_name);
void run_tests();

int main(int argc, char **argv) {

#ifdef RUN_TEST
  return run_tests(), 0;
#endif

  //--------------------------//
  // Read and check arguments //
  //--------------------------//

  std::string input_path;
  std::string output_path;
  std::string command_path;

  uint32_t word_size = 1024;

  bool show_stats = false;
  bool use_bitmask = false;
  bool use_rb = false;

  int ch;
  while ((ch = getopt(argc, argv, "o:c:w:sbt"))!=-1) {
    switch (ch) {
      case 'o': SET_ARG(output_path);
        break;
      case 'c': SET_ARG(command_path);
        break;
      case 'w': word_size = (uint32_t) std::stoi(optarg);
        break;
      case 's': show_stats = true;
        break;
      case 'b': use_bitmask = true;
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

  CREATE c;
  if (use_bitmask) {
    c = &bitmask_bitset::create;
    std::cerr << "Using bitset as bitmask (constant time rank/select)..." << std::endl;
  } else {
    c = &bitmask_vector::create;
    std::cerr << "Using vector of bools as bitmask (linear time rank/select)..." << std::endl;
  }
  bitmask::set_creator(c);

  //--------------------------//
  // Create nodes             //
  //--------------------------//

  auto create_nodes_start = std::chrono::steady_clock::now();

  std::string line, name, content;
  std::vector<data *> data_chunks;
  while (!data_in.eof()) {
    std::getline(data_in, line);
    if (!line.empty() && line[0]!='>' && line[0]!=';') { // Identifier marker
      content += line;

      while (content.length() >= word_size) {
        data_chunks.push_back(create_data(content, word_size));
      }
    }
  }
  if (content.length()) {
    data_chunks.push_back(create_data(content, word_size));
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
    t = new rb_tree(data_chunks, word_size);
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
#include "TargetConditionals.h"
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
            << "\n\t-w word_size     [default=1024, makes sense only with -b]"
            << "\n\t-s               [show statistics]"
            << "\n\t-b               [use bitmask instead of bool vector]"
            << "\n\t-t               [use red-black tree instead of lookup list]"
            << std::endl;
  exit(-1);
}

void quit(const char *message) {
  std::cerr << message << std::endl;
  exit(-1);
}

data *create_data(std::string &line, uint32_t word_size) {
  static std::unordered_map<char, uint32_t> counters;
  static std::string alphabet = "ACTG";

  uint32_t len = std::min(word_size, (uint32_t) line.length());
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

/* * * * * * * * * * * * * * * * * * * * * * * * *
 *                                               *
 *                   TESTS                       *
 *                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * */

void test_bitset() {
  bitset b(65);
  b[0] = 1;
  b[63] = 1;
  b[64] = 1;

  assert(b.binary_rank(0)==1);
  assert(b.binary_rank(1)==1);
  assert(b.binary_rank(5)==1);
  assert(b.binary_rank(63)==2);
  assert(b.binary_rank(64)==3);

  assert(b.binary_select(1, true)==0);
  assert(b.binary_select(2, true)==63);
  assert(b.binary_select(3, true)==64);
  try {
    b.binary_select(4, true);
    assert(false);
  } catch (const std::out_of_range &) {
    assert(true);
  }

  for (int i = 1; i <= 62; ++i) {
    assert(b.binary_select(i, false)==i);
  }

  try {
    b.binary_select(63, false);
    assert(false);
  } catch (const std::out_of_range &) {
    assert(true);
  }

  for (uint32_t i = 1; i <= 65; ++i) {
    try {
      assert(b.binary_rank(b.binary_select(i, true))==i);
    } catch (const std::out_of_range &) {
      break;
    }
  }
}

void test_bitmask() {
  const uint32_t size = 1025;
  bitmask *b = bitmask_bitset::create(size);
  bitmask *v = bitmask_vector::create(size);

  for (uint32_t i = 0; i < 256; i++) {
    auto idx = rand()%size;
    b->set(idx, true);
    v->set(idx, true);
  }

  for (uint32_t i = 0; i < size; i++) {
    assert(b->get(i)==v->get(i));
  }

  auto assert_select = [&](uint32_t idx, bool val) -> void {
    try {
      auto _b = b->select01(idx, val);
      // no exception, v must not throw exception
      try {
        auto _v = v->select01(idx, val);
        assert(_b==_v);
      } catch (const std::out_of_range &) {
        assert(false);
      }
    } catch (const std::out_of_range &) {
      // exception, expect exception too
      try {
        v->select01(idx, val);
        assert(false);
      } catch (const std::out_of_range &) {
        assert(true);
      }
    }
  };

  for (uint32_t j = 0; j < size; ++j) {
    assert(b->rank0(j)==v->rank0(j));
    assert(b->rank1(j)==v->rank1(j));
    assert_select(j, false);
    assert_select(j, true);
  }
}

void test_wavelet() {
  const uint32_t alpha_size = 10; // 1-26
  const uint32_t str_size = 500;

  // dont touch rest of this function

  std::string alpha;
  for (int i = 0; i < alpha_size; ++i) {
    alpha += ('A' + i);
  }

  std::string str;
  for (int i = 0; i < str_size; ++i) {
    str += alpha[rand()%alpha_size];
  }

  bitmask::set_creator(&bitmask_bitset::create);
  wavelet w(str, alpha);
  assert(w.length()==str.length());

  for (uint32_t i = 0; i < str_size; ++i) {
    assert(str[i]==w[i]);
  }

  auto _select = [&](char c, uint32_t idx) -> uint32_t {
    if (idx==0) { throw std::out_of_range("no elem"); }
    uint32_t ret = 0;
    for (auto _c : str) {
      if (c==_c) {
        if (--idx==0) {
          return ret;
        }
      }
      ret++;
    }
    throw std::out_of_range("no such elem");
  };

  auto _rank = [&](char c, uint32_t idx) -> uint32_t {
    if (idx >= str.length()) {
      throw std::out_of_range("no such idx");
    }
    auto it = str.begin();
    return (uint32_t) std::count(it, it + idx + 1, c);
  };

  auto assert_select = [&](char c, uint32_t idx) -> void {
    try {
      auto _b = w.select(c, idx);
      // no exception, v must not throw exception
      try {
        auto _v = _select(c, idx);
        assert(_b==_v);
      } catch (const std::out_of_range &) {
        assert(false);
      }
    } catch (const std::out_of_range &) {
      // exception, expect exception too
      try {
        _select(c, idx);
        assert(false);
      } catch (const std::out_of_range &) {
        assert(true);
      }
    }
  };

  for (auto c : alpha) {
    for (uint32_t i = 0; i < str_size; ++i) {
      assert_select(c, i);
      assert(_rank(c, i)==w.rank(c, i));
      try {
        auto s = w.select(c, i);
        assert(w.rank(c, s)==i);
      } catch (...) {
      }
    }
  }

}

void run_tests() {

  srand(420u);

  std::cerr << "Testing bitset... ";
  test_bitset();
  std::cerr << "Pass!" << std::endl;

  std::cerr << "Testing bitmasks... ";
  test_bitmask();
  std::cerr << "Pass!" << std::endl;

  std::cerr << "Testing wavelet... ";
  test_wavelet();
  std::cerr << "Pass!" << std::endl;
}