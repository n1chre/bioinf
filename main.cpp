#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "tree.h"
#include "rb_tree.h"
#include "balanced_tree.h"

void quit(const char *message);

int main(int argc, char** argv) {

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
    } else {
      quit("Invalid argument provided");
    }
  }


  std::ifstream command_file(command_path);
  std::ofstream output_file(output_path);

  std::istream& cmd_in = command_path == nullptr ? std::cin : command_file;
  std::ostream& data_out = output_path == nullptr ? std::cout : output_file;

  if (input_path == nullptr) {
    quit("Input file path is required");
  }

  std::ifstream input_file(input_path);

  if (!input_file.good()) {
    quit("Given input file doesn't exist.");
  }
  if (!data_out.good()) {
    quit("Given output file can't be written to.");
  }
  if (!cmd_in.good()) {
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

  return 0;
}

void quit(const char *message) {
  std::cerr << message << std::endl;
  exit(-1);
}
