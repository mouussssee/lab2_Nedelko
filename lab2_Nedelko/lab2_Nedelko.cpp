#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "pipe.h"
#include "cs.h"
#include <unordered_map>
#include <unordered_set>
#include "utils.h"
#include "redirect_output_wrapper.h"
#include <format>
#include <chrono>
using namespace std;

int main()
{
    redirect_output_wrapper cer_out(cerr);
    string time = std::format("{:%d_%m_%Y %H_%M_%OS}", chrono::system_clock::now());
    ofstream logfile("log_" + time);
    if (logfile)
    {
        cer_out.redirect(logfile);
    }
}


