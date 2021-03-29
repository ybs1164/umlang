#include "include/um.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        printf("입력 파일 지정해주세요");
        return 1;
    }

    // 파일 컴파일 시작
    um_compile_file(argv[1]);

    return 0;
}