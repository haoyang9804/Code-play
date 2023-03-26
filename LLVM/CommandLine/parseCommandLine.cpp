#include <llvm/Support/CommandLine.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace llvm;

cl::OptionCategory IOCategory("IO", "IO option category");
cl::OptionCategory BoolCategory("Bool", "Bool option category");

// "cl::Positional" here means there is no specifier such as "-o".
// We only need to put the input file in the position.
// If cl::Required, then this inputfilename is required, though with cl::init
// If cl::Required does not exist, then cl::init("-") makes sure our command-line tool
// can work without inputfilename
cl::opt<std::basic_string<char>> InputFilename(cl::Positional, cl::desc("<input file>"), cl::Required, cl::cat(IOCategory), cl::init("-"));
// static cl::opt<int> randomNum(cl::desc("a random number"), cl::cat(MyCategory));

// "o" here means the command line is "-o"
cl::opt<std::basic_string<char>> OutputFilename("o", cl::desc("Specify output filename"), cl::value_desc("filename"), cl::cat(IOCategory));



cl::opt<bool> Force ("f", cl::desc("Enable binary output on terminals"), cl::cat(BoolCategory));
cl::opt<bool> Quiet ("quiet", cl::desc("Don't print informational messages"), cl::cat(BoolCategory));
cl::alias     QuietA("q", cl::desc("Alias for -quiet"), cl::aliasopt(Quiet), cl::Hidden);

int main(int argc, char** argv) {
  cl::ParseCommandLineOptions(argc, argv);
  // std::cout << "output file is " << OutputFilename.getValue() << std::endl;
  std::cout << "f is " << Force.getValue()<< std::endl;
}