#ifndef GEN_RESULT_
#define GEN_RESULT_
#include <string>
#include "library.hpp"

std::string get_acc(std::string tmp);
std::string get_virus(std::string tmp);
std::string get_cds(std::string tmp);
void gen_result(int num_host_seq, inputParameter *input);
#endif // GEN_RESULT_
