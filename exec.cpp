
const char * const interp_argv[] = {"test_msdscript", "--interp"};
// const char * const print_argv[] = {"msdscript", "--print"};

// for(int i = 0; i < 100; i++) {
//     std::string in = random_expr_string();
//     std::cout << "Trying " << in << "\n";

//     ExecResult interp_result = exec_program(2, interp_argv, in);
//     // ExecResult print_result = exec_program(2, print_argv, in);

//     ExecResult interp_again_result = exec_program(2, interp_argv, in);
//     if(interp_again_result.out != interp_result.out) {
//         throw std::runtime_error("Different result for printed");
//     }
// }