/*
   Copyright 2023 Ján Mach

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define GETMYTIME(_t) \
    uint32_t tmp1, tmp2, tmp3;\
    do {\
      __asm__ volatile ("csrr %0, mcycleh\n\tcsrr %1, mcycle\n\tcsrr %2, mcycleh" :  "=r"(tmp1), "=r"(tmp2), "=r"(tmp3) : );\
    } while (tmp1 != tmp3);\
    *_t = (uint64_t)tmp1 << 32 | (uint64_t)tmp2;

#define INSTRUCTION(_instr,_rd,_rs1,_rs2)\
    do {\
        uint32_t __rs1 = *_rs1;\
        uint32_t __rs2 = *_rs2;\
        uint32_t __rd;\
        __asm__ volatile (_instr " %0, %1, %2" : "=r" (__rd) : "r" (__rs1), "r"(__rs2));\
        *_rd = __rd; \
    }\
    while (0)

#define INSTRUCTION_IMM(_instr,_rd,_rs,_imm)\
    do {\
        uint32_t __rs = *_rs;\
        uint32_t __rd;\
        __asm__ volatile (_instr " %0, %1, " _imm : "=r" (__rd) : "r" (__rs));\
        *_rd = __rd; \
    }\
    while (0)

#define INSTRUCTION_SINGLE(_instr,_rd,_rs)\
    do {\
        uint32_t __rs = *_rs;\
        uint32_t __rd;\
        __asm__ volatile (_instr " %0, %1" : "=r" (__rd) : "r" (__rs));\
        *_rd = __rd; \
    }\
    while (0)

uint64_t cycles;

void get_cycles()
{
    GETMYTIME(&cycles);
}

void test_zba()
{
    uint32_t result, rs1, rs2;

    // 16x3 automatically generated tests
    // generated using python

    printf("sh1add TEST #1... ");
    rs1 = 0x8bfb2fcf;
    rs2 = 0x47b4370d;
    INSTRUCTION("sh1add", &result, &rs1, &rs2);
    if (result != 0x5faa96ab) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh1add rd, 0x8bfb2fcf, 0x47b4370d\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x5faa96ab, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh1add TEST #2... ");
    rs1 = 0x7f89b8c2;
    rs2 = 0xf3b83b29;
    INSTRUCTION("sh1add", &result, &rs1, &rs2);
    if (result != 0xf2cbacad) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh1add rd, 0x7f89b8c2, 0xf3b83b29\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xf2cbacad, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh1add TEST #3... ");
    rs1 = 0xd582b559;
    rs2 = 0x5392240;
    INSTRUCTION("sh1add", &result, &rs1, &rs2);
    if (result != 0xb03e8cf2) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh1add rd, 0xd582b559, 0x5392240\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xb03e8cf2, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh1add TEST #4... ");
    rs1 = 0x6f9e2874;
    rs2 = 0x7459a938;
    INSTRUCTION("sh1add", &result, &rs1, &rs2);
    if (result != 0x5395fa20) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh1add rd, 0x6f9e2874, 0x7459a938\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x5395fa20, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh1add TEST #5... ");
    rs1 = 0xcc34fbc0;
    rs2 = 0xb8c4f89;
    INSTRUCTION("sh1add", &result, &rs1, &rs2);
    if (result != 0xa3f64709) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh1add rd, 0xcc34fbc0, 0xb8c4f89\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xa3f64709, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh1add TEST #6... ");
    rs1 = 0x28e3549e;
    rs2 = 0x21d8cac9;
    INSTRUCTION("sh1add", &result, &rs1, &rs2);
    if (result != 0x739f7405) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh1add rd, 0x28e3549e, 0x21d8cac9\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x739f7405, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh1add TEST #7... ");
    rs1 = 0x4ce2446c;
    rs2 = 0x5fe469fd;
    INSTRUCTION("sh1add", &result, &rs1, &rs2);
    if (result != 0xf9a8f2d5) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh1add rd, 0x4ce2446c, 0x5fe469fd\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xf9a8f2d5, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh1add TEST #8... ");
    rs1 = 0x5951bd13;
    rs2 = 0xc6209aa5;
    INSTRUCTION("sh1add", &result, &rs1, &rs2);
    if (result != 0x78c414cb) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh1add rd, 0x5951bd13, 0xc6209aa5\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x78c414cb, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh1add TEST #9... ");
    rs1 = 0xddebc93e;
    rs2 = 0x733c8199;
    INSTRUCTION("sh1add", &result, &rs1, &rs2);
    if (result != 0x2f141415) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh1add rd, 0xddebc93e, 0x733c8199\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x2f141415, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh1add TEST #10... ");
    rs1 = 0x3ddc169d;
    rs2 = 0x2bba4c5c;
    INSTRUCTION("sh1add", &result, &rs1, &rs2);
    if (result != 0xa7727996) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh1add rd, 0x3ddc169d, 0x2bba4c5c\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xa7727996, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh1add TEST #11... ");
    rs1 = 0xf1fc7b63;
    rs2 = 0xe2bd81bc;
    INSTRUCTION("sh1add", &result, &rs1, &rs2);
    if (result != 0xc6b67882) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh1add rd, 0xf1fc7b63, 0xe2bd81bc\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xc6b67882, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh1add TEST #12... ");
    rs1 = 0xf3977952;
    rs2 = 0x98781c98;
    INSTRUCTION("sh1add", &result, &rs1, &rs2);
    if (result != 0x7fa70f3c) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh1add rd, 0xf3977952, 0x98781c98\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x7fa70f3c, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh1add TEST #13... ");
    rs1 = 0xa2ea469;
    rs2 = 0x212d2cf1;
    INSTRUCTION("sh1add", &result, &rs1, &rs2);
    if (result != 0x358a75c3) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh1add rd, 0xa2ea469, 0x212d2cf1\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x358a75c3, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh1add TEST #14... ");
    rs1 = 0xcf0b637d;
    rs2 = 0x94e6a4d;
    INSTRUCTION("sh1add", &result, &rs1, &rs2);
    if (result != 0xa7653147) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh1add rd, 0xcf0b637d, 0x94e6a4d\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xa7653147, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh1add TEST #15... ");
    rs1 = 0x380d82e7;
    rs2 = 0xad2da5fe;
    INSTRUCTION("sh1add", &result, &rs1, &rs2);
    if (result != 0x1d48abcc) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh1add rd, 0x380d82e7, 0xad2da5fe\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1d48abcc, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh1add TEST #16... ");
    rs1 = 0xa8ed904f;
    rs2 = 0xee862289;
    INSTRUCTION("sh1add", &result, &rs1, &rs2);
    if (result != 0x40614327) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh1add rd, 0xa8ed904f, 0xee862289\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x40614327, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh2add TEST #1... ");
    rs1 = 0x6a701eba;
    rs2 = 0xd714e5a7;
    INSTRUCTION("sh2add", &result, &rs1, &rs2);
    if (result != 0x80d5608f) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh2add rd, 0x6a701eba, 0xd714e5a7\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x80d5608f, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh2add TEST #2... ");
    rs1 = 0xa0a95327;
    rs2 = 0xe181a591;
    INSTRUCTION("sh2add", &result, &rs1, &rs2);
    if (result != 0x6426f22d) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh2add rd, 0xa0a95327, 0xe181a591\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x6426f22d, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh2add TEST #3... ");
    rs1 = 0xca21ff9e;
    rs2 = 0xfcfc0511;
    INSTRUCTION("sh2add", &result, &rs1, &rs2);
    if (result != 0x25840389) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh2add rd, 0xca21ff9e, 0xfcfc0511\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x25840389, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh2add TEST #4... ");
    rs1 = 0x52e196c4;
    rs2 = 0xa5a30648;
    INSTRUCTION("sh2add", &result, &rs1, &rs2);
    if (result != 0xf1296158) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh2add rd, 0x52e196c4, 0xa5a30648\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xf1296158, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh2add TEST #5... ");
    rs1 = 0x80db5daa;
    rs2 = 0xd894c9c0;
    INSTRUCTION("sh2add", &result, &rs1, &rs2);
    if (result != 0xdc024068) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh2add rd, 0x80db5daa, 0xd894c9c0\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xdc024068, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh2add TEST #6... ");
    rs1 = 0x95a6e127;
    rs2 = 0x20fd8c12;
    INSTRUCTION("sh2add", &result, &rs1, &rs2);
    if (result != 0x779910ae) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh2add rd, 0x95a6e127, 0x20fd8c12\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x779910ae, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh2add TEST #7... ");
    rs1 = 0x7ee146ba;
    rs2 = 0x5b1ef85;
    INSTRUCTION("sh2add", &result, &rs1, &rs2);
    if (result != 0x1370a6d) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh2add rd, 0x7ee146ba, 0x5b1ef85\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1370a6d, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh2add TEST #8... ");
    rs1 = 0x607ed801;
    rs2 = 0x5683c2;
    INSTRUCTION("sh2add", &result, &rs1, &rs2);
    if (result != 0x8251e3c6) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh2add rd, 0x607ed801, 0x5683c2\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x8251e3c6, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh2add TEST #9... ");
    rs1 = 0x26573b24;
    rs2 = 0x3ecd27c8;
    INSTRUCTION("sh2add", &result, &rs1, &rs2);
    if (result != 0xd82a1458) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh2add rd, 0x26573b24, 0x3ecd27c8\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xd82a1458, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh2add TEST #10... ");
    rs1 = 0x154fd78c;
    rs2 = 0xe0662fb7;
    INSTRUCTION("sh2add", &result, &rs1, &rs2);
    if (result != 0x35a58de7) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh2add rd, 0x154fd78c, 0xe0662fb7\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x35a58de7, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh2add TEST #11... ");
    rs1 = 0xbd2b357f;
    rs2 = 0xc978660d;
    INSTRUCTION("sh2add", &result, &rs1, &rs2);
    if (result != 0xbe253c09) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh2add rd, 0xbd2b357f, 0xc978660d\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xbe253c09, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh2add TEST #12... ");
    rs1 = 0xcc4f84cf;
    rs2 = 0x9cb61221;
    INSTRUCTION("sh2add", &result, &rs1, &rs2);
    if (result != 0xcdf4255d) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh2add rd, 0xcc4f84cf, 0x9cb61221\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xcdf4255d, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh2add TEST #13... ");
    rs1 = 0x44e2af0c;
    rs2 = 0xa4122f04;
    INSTRUCTION("sh2add", &result, &rs1, &rs2);
    if (result != 0xb79ceb34) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh2add rd, 0x44e2af0c, 0xa4122f04\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xb79ceb34, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh2add TEST #14... ");
    rs1 = 0x46a2f27;
    rs2 = 0xc67723ce;
    INSTRUCTION("sh2add", &result, &rs1, &rs2);
    if (result != 0xd81fe06a) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh2add rd, 0x46a2f27, 0xc67723ce\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xd81fe06a, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh2add TEST #15... ");
    rs1 = 0xc5f93133;
    rs2 = 0x6b303c74;
    INSTRUCTION("sh2add", &result, &rs1, &rs2);
    if (result != 0x83150140) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh2add rd, 0xc5f93133, 0x6b303c74\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x83150140, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh2add TEST #16... ");
    rs1 = 0x8f94f97c;
    rs2 = 0xc9904a94;
    INSTRUCTION("sh2add", &result, &rs1, &rs2);
    if (result != 0x7e43084) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh2add rd, 0x8f94f97c, 0xc9904a94\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x7e43084, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh3add TEST #1... ");
    rs1 = 0x8b98f2d8;
    rs2 = 0x8478be39;
    INSTRUCTION("sh3add", &result, &rs1, &rs2);
    if (result != 0xe14054f9) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh3add rd, 0x8b98f2d8, 0x8478be39\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xe14054f9, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh3add TEST #2... ");
    rs1 = 0xd8384c35;
    rs2 = 0xf4318e13;
    INSTRUCTION("sh3add", &result, &rs1, &rs2);
    if (result != 0xb5f3efbb) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh3add rd, 0xd8384c35, 0xf4318e13\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xb5f3efbb, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh3add TEST #3... ");
    rs1 = 0xc81a30e2;
    rs2 = 0xc0251fc8;
    INSTRUCTION("sh3add", &result, &rs1, &rs2);
    if (result != 0xf6a6d8) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh3add rd, 0xc81a30e2, 0xc0251fc8\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xf6a6d8, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh3add TEST #4... ");
    rs1 = 0x75643486;
    rs2 = 0x4a6398a2;
    INSTRUCTION("sh3add", &result, &rs1, &rs2);
    if (result != 0xf5853cd2) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh3add rd, 0x75643486, 0x4a6398a2\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xf5853cd2, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh3add TEST #5... ");
    rs1 = 0x45b83e8;
    rs2 = 0xe351fd3c;
    INSTRUCTION("sh3add", &result, &rs1, &rs2);
    if (result != 0x62e1c7c) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh3add rd, 0x45b83e8, 0xe351fd3c\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x62e1c7c, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh3add TEST #6... ");
    rs1 = 0xfb9137b7;
    rs2 = 0x6210f693;
    INSTRUCTION("sh3add", &result, &rs1, &rs2);
    if (result != 0x3e9ab44b) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh3add rd, 0xfb9137b7, 0x6210f693\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x3e9ab44b, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh3add TEST #7... ");
    rs1 = 0xee1998f6;
    rs2 = 0xe861f868;
    INSTRUCTION("sh3add", &result, &rs1, &rs2);
    if (result != 0x592ec018) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh3add rd, 0xee1998f6, 0xe861f868\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x592ec018, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh3add TEST #8... ");
    rs1 = 0x2226235e;
    rs2 = 0x3b2aebeb;
    INSTRUCTION("sh3add", &result, &rs1, &rs2);
    if (result != 0x4c5c06db) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh3add rd, 0x2226235e, 0x3b2aebeb\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x4c5c06db, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh3add TEST #9... ");
    rs1 = 0xaac042c1;
    rs2 = 0x95166ae5;
    INSTRUCTION("sh3add", &result, &rs1, &rs2);
    if (result != 0xeb1880ed) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh3add rd, 0xaac042c1, 0x95166ae5\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xeb1880ed, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh3add TEST #10... ");
    rs1 = 0x8ffea8b7;
    rs2 = 0xef3c3c54;
    INSTRUCTION("sh3add", &result, &rs1, &rs2);
    if (result != 0x6f31820c) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh3add rd, 0x8ffea8b7, 0xef3c3c54\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x6f31820c, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh3add TEST #11... ");
    rs1 = 0xa8258ac5;
    rs2 = 0x9a702a8d;
    INSTRUCTION("sh3add", &result, &rs1, &rs2);
    if (result != 0xdb9c80b5) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh3add rd, 0xa8258ac5, 0x9a702a8d\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xdb9c80b5, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh3add TEST #12... ");
    rs1 = 0x243e8221;
    rs2 = 0xebf6a032;
    INSTRUCTION("sh3add", &result, &rs1, &rs2);
    if (result != 0xdeab13a) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh3add rd, 0x243e8221, 0xebf6a032\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xdeab13a, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh3add TEST #13... ");
    rs1 = 0x26c9d24d;
    rs2 = 0xf295b993;
    INSTRUCTION("sh3add", &result, &rs1, &rs2);
    if (result != 0x28e44bfb) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh3add rd, 0x26c9d24d, 0xf295b993\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x28e44bfb, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh3add TEST #14... ");
    rs1 = 0x1b3106d0;
    rs2 = 0x8cb04d9d;
    INSTRUCTION("sh3add", &result, &rs1, &rs2);
    if (result != 0x6638841d) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh3add rd, 0x1b3106d0, 0x8cb04d9d\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x6638841d, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh3add TEST #15... ");
    rs1 = 0xb982bf51;
    rs2 = 0xe42b023b;
    INSTRUCTION("sh3add", &result, &rs1, &rs2);
    if (result != 0xb040fcc3) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh3add rd, 0xb982bf51, 0xe42b023b\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xb040fcc3, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sh3add TEST #16... ");
    rs1 = 0x7fe318c1;
    rs2 = 0xceda64ae;
    INSTRUCTION("sh3add", &result, &rs1, &rs2);
    if (result != 0xcdf32ab6) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sh3add rd, 0x7fe318c1, 0xceda64ae\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xcdf32ab6, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");

    printf("\n\n--------------\nZba extension successfully PASSED\n--------------\n\n");
}

void test_minmax()
{
    uint32_t result, rs1, rs2;

    // 16x4 automatically generated tests
    // generated using python
    printf("max TEST #0... ");
    rs1 = 0x9c1e5660;
    rs2 = 0x424f7815;
    INSTRUCTION("max", &result, &rs1, &rs2);
    if (result != 0x424f7815) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("max rd, 0x9c1e5660, 0x424f7815\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x424f7815, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("max TEST #1... ");
    rs1 = 0xbdd3392e;
    rs2 = 0x51f5a0a5;
    INSTRUCTION("max", &result, &rs1, &rs2);
    if (result != 0x51f5a0a5) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("max rd, 0xbdd3392e, 0x51f5a0a5\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x51f5a0a5, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("max TEST #2... ");
    rs1 = 0x7ebff687;
    rs2 = 0xaa9be9e;
    INSTRUCTION("max", &result, &rs1, &rs2);
    if (result != 0x7ebff687) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("max rd, 0x7ebff687, 0xaa9be9e\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x7ebff687, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("max TEST #3... ");
    rs1 = 0x36f688ab;
    rs2 = 0x49c2ac87;
    INSTRUCTION("max", &result, &rs1, &rs2);
    if (result != 0x49c2ac87) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("max rd, 0x36f688ab, 0x49c2ac87\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x49c2ac87, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("max TEST #4... ");
    rs1 = 0x6b4df7d9;
    rs2 = 0xc299f04c;
    INSTRUCTION("max", &result, &rs1, &rs2);
    if (result != 0x6b4df7d9) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("max rd, 0x6b4df7d9, 0xc299f04c\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x6b4df7d9, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("max TEST #5... ");
    rs1 = 0x6246a67c;
    rs2 = 0x97515a3;
    INSTRUCTION("max", &result, &rs1, &rs2);
    if (result != 0x6246a67c) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("max rd, 0x6246a67c, 0x97515a3\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x6246a67c, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("max TEST #6... ");
    rs1 = 0xfd9510f;
    rs2 = 0x74b18af7;
    INSTRUCTION("max", &result, &rs1, &rs2);
    if (result != 0x74b18af7) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("max rd, 0xfd9510f, 0x74b18af7\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x74b18af7, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("max TEST #7... ");
    rs1 = 0xfb255b6d;
    rs2 = 0x9c381831;
    INSTRUCTION("max", &result, &rs1, &rs2);
    if (result != 0xfb255b6d) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("max rd, 0xfb255b6d, 0x9c381831\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xfb255b6d, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("max TEST #8... ");
    rs1 = 0x9b321b18;
    rs2 = 0xaf67e904;
    INSTRUCTION("max", &result, &rs1, &rs2);
    if (result != 0xaf67e904) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("max rd, 0x9b321b18, 0xaf67e904\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xaf67e904, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("max TEST #9... ");
    rs1 = 0x1459fa1e;
    rs2 = 0x48b82d3e;
    INSTRUCTION("max", &result, &rs1, &rs2);
    if (result != 0x48b82d3e) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("max rd, 0x1459fa1e, 0x48b82d3e\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x48b82d3e, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("max TEST #10... ");
    rs1 = 0x245b3b70;
    rs2 = 0xc04b087a;
    INSTRUCTION("max", &result, &rs1, &rs2);
    if (result != 0x245b3b70) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("max rd, 0x245b3b70, 0xc04b087a\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x245b3b70, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("max TEST #11... ");
    rs1 = 0x2b9a7217;
    rs2 = 0xc5802342;
    INSTRUCTION("max", &result, &rs1, &rs2);
    if (result != 0x2b9a7217) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("max rd, 0x2b9a7217, 0xc5802342\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x2b9a7217, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("max TEST #12... ");
    rs1 = 0xd887cb59;
    rs2 = 0x14fd8856;
    INSTRUCTION("max", &result, &rs1, &rs2);
    if (result != 0x14fd8856) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("max rd, 0xd887cb59, 0x14fd8856\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x14fd8856, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("max TEST #13... ");
    rs1 = 0x1eb26110;
    rs2 = 0x11c81f02;
    INSTRUCTION("max", &result, &rs1, &rs2);
    if (result != 0x1eb26110) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("max rd, 0x1eb26110, 0x11c81f02\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1eb26110, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("max TEST #14... ");
    rs1 = 0xe9c49d91;
    rs2 = 0xdb7d36f1;
    INSTRUCTION("max", &result, &rs1, &rs2);
    if (result != 0xe9c49d91) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("max rd, 0xe9c49d91, 0xdb7d36f1\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xe9c49d91, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("max TEST #15... ");
    rs1 = 0x71b849df;
    rs2 = 0xe41b6913;
    INSTRUCTION("max", &result, &rs1, &rs2);
    if (result != 0x71b849df) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("max rd, 0x71b849df, 0xe41b6913\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x71b849df, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("maxu TEST #0... ");
    rs1 = 0x329b4c80;
    rs2 = 0x3749608c;
    INSTRUCTION("maxu", &result, &rs1, &rs2);
    if (result != 0x3749608c) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("maxu rd, 0x329b4c80, 0x3749608c\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x3749608c, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("maxu TEST #1... ");
    rs1 = 0x8d4ac0db;
    rs2 = 0x89d7858c;
    INSTRUCTION("maxu", &result, &rs1, &rs2);
    if (result != 0x8d4ac0db) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("maxu rd, 0x8d4ac0db, 0x89d7858c\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x8d4ac0db, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("maxu TEST #2... ");
    rs1 = 0xfb6212b0;
    rs2 = 0xb07d7e42;
    INSTRUCTION("maxu", &result, &rs1, &rs2);
    if (result != 0xfb6212b0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("maxu rd, 0xfb6212b0, 0xb07d7e42\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xfb6212b0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("maxu TEST #3... ");
    rs1 = 0x1b11f45d;
    rs2 = 0x774e92bf;
    INSTRUCTION("maxu", &result, &rs1, &rs2);
    if (result != 0x774e92bf) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("maxu rd, 0x1b11f45d, 0x774e92bf\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x774e92bf, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("maxu TEST #4... ");
    rs1 = 0x637b5a1;
    rs2 = 0x152918a6;
    INSTRUCTION("maxu", &result, &rs1, &rs2);
    if (result != 0x152918a6) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("maxu rd, 0x637b5a1, 0x152918a6\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x152918a6, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("maxu TEST #5... ");
    rs1 = 0x21f53298;
    rs2 = 0x900b7336;
    INSTRUCTION("maxu", &result, &rs1, &rs2);
    if (result != 0x900b7336) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("maxu rd, 0x21f53298, 0x900b7336\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x900b7336, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("maxu TEST #6... ");
    rs1 = 0xb64302cd;
    rs2 = 0x3140db0d;
    INSTRUCTION("maxu", &result, &rs1, &rs2);
    if (result != 0xb64302cd) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("maxu rd, 0xb64302cd, 0x3140db0d\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xb64302cd, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("maxu TEST #7... ");
    rs1 = 0x4da91c90;
    rs2 = 0x1a2963af;
    INSTRUCTION("maxu", &result, &rs1, &rs2);
    if (result != 0x4da91c90) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("maxu rd, 0x4da91c90, 0x1a2963af\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x4da91c90, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("maxu TEST #8... ");
    rs1 = 0x2a3d88ae;
    rs2 = 0x51a6b97a;
    INSTRUCTION("maxu", &result, &rs1, &rs2);
    if (result != 0x51a6b97a) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("maxu rd, 0x2a3d88ae, 0x51a6b97a\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x51a6b97a, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("maxu TEST #9... ");
    rs1 = 0x5224d0ae;
    rs2 = 0x8e1d0801;
    INSTRUCTION("maxu", &result, &rs1, &rs2);
    if (result != 0x8e1d0801) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("maxu rd, 0x5224d0ae, 0x8e1d0801\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x8e1d0801, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("maxu TEST #10... ");
    rs1 = 0x4986a1ac;
    rs2 = 0xa226860a;
    INSTRUCTION("maxu", &result, &rs1, &rs2);
    if (result != 0xa226860a) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("maxu rd, 0x4986a1ac, 0xa226860a\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xa226860a, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("maxu TEST #11... ");
    rs1 = 0xa9d4ece2;
    rs2 = 0x5072ac34;
    INSTRUCTION("maxu", &result, &rs1, &rs2);
    if (result != 0xa9d4ece2) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("maxu rd, 0xa9d4ece2, 0x5072ac34\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xa9d4ece2, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("maxu TEST #12... ");
    rs1 = 0xe03d06e7;
    rs2 = 0xe1f69279;
    INSTRUCTION("maxu", &result, &rs1, &rs2);
    if (result != 0xe1f69279) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("maxu rd, 0xe03d06e7, 0xe1f69279\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xe1f69279, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("maxu TEST #13... ");
    rs1 = 0xbb9517a1;
    rs2 = 0xd830bce1;
    INSTRUCTION("maxu", &result, &rs1, &rs2);
    if (result != 0xd830bce1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("maxu rd, 0xbb9517a1, 0xd830bce1\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xd830bce1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("maxu TEST #14... ");
    rs1 = 0xb3c6e936;
    rs2 = 0x36eefb53;
    INSTRUCTION("maxu", &result, &rs1, &rs2);
    if (result != 0xb3c6e936) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("maxu rd, 0xb3c6e936, 0x36eefb53\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xb3c6e936, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("maxu TEST #15... ");
    rs1 = 0x6cad7f6b;
    rs2 = 0x3cb2e107;
    INSTRUCTION("maxu", &result, &rs1, &rs2);
    if (result != 0x6cad7f6b) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("maxu rd, 0x6cad7f6b, 0x3cb2e107\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x6cad7f6b, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("min TEST #0... ");
    rs1 = 0x545c474a;
    rs2 = 0x17b2ea9d;
    INSTRUCTION("min", &result, &rs1, &rs2);
    if (result != 0x17b2ea9d) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("min rd, 0x545c474a, 0x17b2ea9d\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x17b2ea9d, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("min TEST #1... ");
    rs1 = 0x5a975163;
    rs2 = 0xb6eb04ee;
    INSTRUCTION("min", &result, &rs1, &rs2);
    if (result != 0xb6eb04ee) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("min rd, 0x5a975163, 0xb6eb04ee\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xb6eb04ee, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("min TEST #2... ");
    rs1 = 0xdc7d090b;
    rs2 = 0xd71519fb;
    INSTRUCTION("min", &result, &rs1, &rs2);
    if (result != 0xd71519fb) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("min rd, 0xdc7d090b, 0xd71519fb\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xd71519fb, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("min TEST #3... ");
    rs1 = 0x4f875e13;
    rs2 = 0x2526eb82;
    INSTRUCTION("min", &result, &rs1, &rs2);
    if (result != 0x2526eb82) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("min rd, 0x4f875e13, 0x2526eb82\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x2526eb82, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("min TEST #4... ");
    rs1 = 0x531bd419;
    rs2 = 0x824f755f;
    INSTRUCTION("min", &result, &rs1, &rs2);
    if (result != 0x824f755f) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("min rd, 0x531bd419, 0x824f755f\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x824f755f, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("min TEST #5... ");
    rs1 = 0x918e19da;
    rs2 = 0xb3fcbd55;
    INSTRUCTION("min", &result, &rs1, &rs2);
    if (result != 0x918e19da) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("min rd, 0x918e19da, 0xb3fcbd55\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x918e19da, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("min TEST #6... ");
    rs1 = 0xe605d753;
    rs2 = 0xa900732a;
    INSTRUCTION("min", &result, &rs1, &rs2);
    if (result != 0xa900732a) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("min rd, 0xe605d753, 0xa900732a\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xa900732a, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("min TEST #7... ");
    rs1 = 0x99234b71;
    rs2 = 0x3a148d01;
    INSTRUCTION("min", &result, &rs1, &rs2);
    if (result != 0x99234b71) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("min rd, 0x99234b71, 0x3a148d01\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x99234b71, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("min TEST #8... ");
    rs1 = 0xc14d72c4;
    rs2 = 0x91b1deb8;
    INSTRUCTION("min", &result, &rs1, &rs2);
    if (result != 0x91b1deb8) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("min rd, 0xc14d72c4, 0x91b1deb8\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x91b1deb8, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("min TEST #9... ");
    rs1 = 0xdbd317b5;
    rs2 = 0x4158804d;
    INSTRUCTION("min", &result, &rs1, &rs2);
    if (result != 0xdbd317b5) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("min rd, 0xdbd317b5, 0x4158804d\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xdbd317b5, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("min TEST #10... ");
    rs1 = 0xd94b561e;
    rs2 = 0xa931c6c4;
    INSTRUCTION("min", &result, &rs1, &rs2);
    if (result != 0xa931c6c4) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("min rd, 0xd94b561e, 0xa931c6c4\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xa931c6c4, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("min TEST #11... ");
    rs1 = 0x4884daf2;
    rs2 = 0x28cdd180;
    INSTRUCTION("min", &result, &rs1, &rs2);
    if (result != 0x28cdd180) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("min rd, 0x4884daf2, 0x28cdd180\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x28cdd180, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("min TEST #12... ");
    rs1 = 0xf3a3276e;
    rs2 = 0x8216473;
    INSTRUCTION("min", &result, &rs1, &rs2);
    if (result != 0xf3a3276e) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("min rd, 0xf3a3276e, 0x8216473\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xf3a3276e, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("min TEST #13... ");
    rs1 = 0xcebe57f9;
    rs2 = 0x615fa177;
    INSTRUCTION("min", &result, &rs1, &rs2);
    if (result != 0xcebe57f9) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("min rd, 0xcebe57f9, 0x615fa177\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xcebe57f9, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("min TEST #14... ");
    rs1 = 0x8cddf7ff;
    rs2 = 0x343bdb62;
    INSTRUCTION("min", &result, &rs1, &rs2);
    if (result != 0x8cddf7ff) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("min rd, 0x8cddf7ff, 0x343bdb62\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x8cddf7ff, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("min TEST #15... ");
    rs1 = 0xf8a9d054;
    rs2 = 0x1e56d0d;
    INSTRUCTION("min", &result, &rs1, &rs2);
    if (result != 0xf8a9d054) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("min rd, 0xf8a9d054, 0x1e56d0d\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xf8a9d054, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("minu TEST #0... ");
    rs1 = 0x3858a69b;
    rs2 = 0x66c61083;
    INSTRUCTION("minu", &result, &rs1, &rs2);
    if (result != 0x3858a69b) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("minu rd, 0x3858a69b, 0x66c61083\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x3858a69b, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("minu TEST #1... ");
    rs1 = 0xfc504165;
    rs2 = 0x63ce8ff2;
    INSTRUCTION("minu", &result, &rs1, &rs2);
    if (result != 0x63ce8ff2) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("minu rd, 0xfc504165, 0x63ce8ff2\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x63ce8ff2, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("minu TEST #2... ");
    rs1 = 0xf7bfdfca;
    rs2 = 0x34cd7365;
    INSTRUCTION("minu", &result, &rs1, &rs2);
    if (result != 0x34cd7365) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("minu rd, 0xf7bfdfca, 0x34cd7365\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x34cd7365, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("minu TEST #3... ");
    rs1 = 0xe536b890;
    rs2 = 0x67db06c8;
    INSTRUCTION("minu", &result, &rs1, &rs2);
    if (result != 0x67db06c8) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("minu rd, 0xe536b890, 0x67db06c8\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x67db06c8, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("minu TEST #4... ");
    rs1 = 0x330e949f;
    rs2 = 0x223949b6;
    INSTRUCTION("minu", &result, &rs1, &rs2);
    if (result != 0x223949b6) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("minu rd, 0x330e949f, 0x223949b6\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x223949b6, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("minu TEST #5... ");
    rs1 = 0x65ae97de;
    rs2 = 0x4561b016;
    INSTRUCTION("minu", &result, &rs1, &rs2);
    if (result != 0x4561b016) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("minu rd, 0x65ae97de, 0x4561b016\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x4561b016, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("minu TEST #6... ");
    rs1 = 0xddc622a6;
    rs2 = 0x8d44d5f4;
    INSTRUCTION("minu", &result, &rs1, &rs2);
    if (result != 0x8d44d5f4) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("minu rd, 0xddc622a6, 0x8d44d5f4\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x8d44d5f4, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("minu TEST #7... ");
    rs1 = 0x82318074;
    rs2 = 0x9dc3b29f;
    INSTRUCTION("minu", &result, &rs1, &rs2);
    if (result != 0x82318074) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("minu rd, 0x82318074, 0x9dc3b29f\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x82318074, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("minu TEST #8... ");
    rs1 = 0xd12a5fb1;
    rs2 = 0xef7ef0ea;
    INSTRUCTION("minu", &result, &rs1, &rs2);
    if (result != 0xd12a5fb1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("minu rd, 0xd12a5fb1, 0xef7ef0ea\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xd12a5fb1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("minu TEST #9... ");
    rs1 = 0x4c0c88e2;
    rs2 = 0xc2666520;
    INSTRUCTION("minu", &result, &rs1, &rs2);
    if (result != 0x4c0c88e2) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("minu rd, 0x4c0c88e2, 0xc2666520\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x4c0c88e2, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("minu TEST #10... ");
    rs1 = 0xf884a71d;
    rs2 = 0x86a590d5;
    INSTRUCTION("minu", &result, &rs1, &rs2);
    if (result != 0x86a590d5) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("minu rd, 0xf884a71d, 0x86a590d5\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x86a590d5, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("minu TEST #11... ");
    rs1 = 0x1819247e;
    rs2 = 0xc664692e;
    INSTRUCTION("minu", &result, &rs1, &rs2);
    if (result != 0x1819247e) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("minu rd, 0x1819247e, 0xc664692e\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1819247e, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("minu TEST #12... ");
    rs1 = 0x30463047;
    rs2 = 0x71cfdf72;
    INSTRUCTION("minu", &result, &rs1, &rs2);
    if (result != 0x30463047) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("minu rd, 0x30463047, 0x71cfdf72\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x30463047, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("minu TEST #13... ");
    rs1 = 0xd4780b11;
    rs2 = 0x6702def;
    INSTRUCTION("minu", &result, &rs1, &rs2);
    if (result != 0x6702def) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("minu rd, 0xd4780b11, 0x6702def\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x6702def, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("minu TEST #14... ");
    rs1 = 0xc302521;
    rs2 = 0xb451df99;
    INSTRUCTION("minu", &result, &rs1, &rs2);
    if (result != 0xc302521) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("minu rd, 0xc302521, 0xb451df99\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xc302521, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("minu TEST #15... ");
    rs1 = 0x50dc351c;
    rs2 = 0x84107f43;
    INSTRUCTION("minu", &result, &rs1, &rs2);
    if (result != 0x50dc351c) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("minu rd, 0x50dc351c, 0x84107f43\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x50dc351c, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");

    printf("\n\n--------------\nMinmax instructions successfully PASSED\n--------------\n\n");
}

void test_misc()
{
    uint32_t result, rs1, rs2;

    // 16x8 automatically generated tests
    // generated using python
    printf("sext.b TEST #0... ");
    rs1 = 0xd84f957c;
    INSTRUCTION_SINGLE("sext.b", &result, &rs1);
    if (result != 0x7c) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.b rd, 0xd84f957c\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x7c, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.b TEST #1... ");
    rs1 = 0x10efd90b;
    INSTRUCTION_SINGLE("sext.b", &result, &rs1);
    if (result != 0xb) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.b rd, 0x10efd90b\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xb, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.b TEST #2... ");
    rs1 = 0x394ed6a2;
    INSTRUCTION_SINGLE("sext.b", &result, &rs1);
    if (result != 0xffffffa2) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.b rd, 0x394ed6a2\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffffa2, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.b TEST #3... ");
    rs1 = 0x1e748a94;
    INSTRUCTION_SINGLE("sext.b", &result, &rs1);
    if (result != 0xffffff94) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.b rd, 0x1e748a94\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffff94, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.b TEST #4... ");
    rs1 = 0xd69ca456;
    INSTRUCTION_SINGLE("sext.b", &result, &rs1);
    if (result != 0x56) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.b rd, 0xd69ca456\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x56, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.b TEST #5... ");
    rs1 = 0xba9f2c0b;
    INSTRUCTION_SINGLE("sext.b", &result, &rs1);
    if (result != 0xb) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.b rd, 0xba9f2c0b\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xb, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.b TEST #6... ");
    rs1 = 0xd70d53c1;
    INSTRUCTION_SINGLE("sext.b", &result, &rs1);
    if (result != 0xffffffc1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.b rd, 0xd70d53c1\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffffc1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.b TEST #7... ");
    rs1 = 0xd76f2e96;
    INSTRUCTION_SINGLE("sext.b", &result, &rs1);
    if (result != 0xffffff96) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.b rd, 0xd76f2e96\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffff96, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.b TEST #8... ");
    rs1 = 0xc8494550;
    INSTRUCTION_SINGLE("sext.b", &result, &rs1);
    if (result != 0x50) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.b rd, 0xc8494550\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x50, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.b TEST #9... ");
    rs1 = 0x3b692f39;
    INSTRUCTION_SINGLE("sext.b", &result, &rs1);
    if (result != 0x39) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.b rd, 0x3b692f39\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x39, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.b TEST #10... ");
    rs1 = 0x3bc2affe;
    INSTRUCTION_SINGLE("sext.b", &result, &rs1);
    if (result != 0xfffffffe) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.b rd, 0x3bc2affe\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xfffffffe, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.b TEST #11... ");
    rs1 = 0xd0d7e6ce;
    INSTRUCTION_SINGLE("sext.b", &result, &rs1);
    if (result != 0xffffffce) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.b rd, 0xd0d7e6ce\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffffce, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.b TEST #12... ");
    rs1 = 0x44d2178d;
    INSTRUCTION_SINGLE("sext.b", &result, &rs1);
    if (result != 0xffffff8d) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.b rd, 0x44d2178d\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffff8d, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.b TEST #13... ");
    rs1 = 0xe1f2ff33;
    INSTRUCTION_SINGLE("sext.b", &result, &rs1);
    if (result != 0x33) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.b rd, 0xe1f2ff33\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x33, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.b TEST #14... ");
    rs1 = 0x7507c6f;
    INSTRUCTION_SINGLE("sext.b", &result, &rs1);
    if (result != 0x6f) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.b rd, 0x7507c6f\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x6f, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.b TEST #15... ");
    rs1 = 0x50e4564;
    INSTRUCTION_SINGLE("sext.b", &result, &rs1);
    if (result != 0x64) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.b rd, 0x50e4564\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x64, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.h TEST #0... ");
    rs1 = 0x7a46e1fe;
    INSTRUCTION_SINGLE("sext.h", &result, &rs1);
    if (result != 0xffffe1fe) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.h rd, 0x7a46e1fe\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffe1fe, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.h TEST #1... ");
    rs1 = 0xaf4661f4;
    INSTRUCTION_SINGLE("sext.h", &result, &rs1);
    if (result != 0x61f4) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.h rd, 0xaf4661f4\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x61f4, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.h TEST #2... ");
    rs1 = 0xfa56c292;
    INSTRUCTION_SINGLE("sext.h", &result, &rs1);
    if (result != 0xffffc292) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.h rd, 0xfa56c292\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffc292, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.h TEST #3... ");
    rs1 = 0x5b7bb5a6;
    INSTRUCTION_SINGLE("sext.h", &result, &rs1);
    if (result != 0xffffb5a6) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.h rd, 0x5b7bb5a6\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffb5a6, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.h TEST #4... ");
    rs1 = 0x9bdf5dd5;
    INSTRUCTION_SINGLE("sext.h", &result, &rs1);
    if (result != 0x5dd5) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.h rd, 0x9bdf5dd5\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x5dd5, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.h TEST #5... ");
    rs1 = 0x3b18cf3f;
    INSTRUCTION_SINGLE("sext.h", &result, &rs1);
    if (result != 0xffffcf3f) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.h rd, 0x3b18cf3f\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffcf3f, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.h TEST #6... ");
    rs1 = 0x4dd56466;
    INSTRUCTION_SINGLE("sext.h", &result, &rs1);
    if (result != 0x6466) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.h rd, 0x4dd56466\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x6466, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.h TEST #7... ");
    rs1 = 0xd8902ea5;
    INSTRUCTION_SINGLE("sext.h", &result, &rs1);
    if (result != 0x2ea5) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.h rd, 0xd8902ea5\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x2ea5, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.h TEST #8... ");
    rs1 = 0xc157e604;
    INSTRUCTION_SINGLE("sext.h", &result, &rs1);
    if (result != 0xffffe604) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.h rd, 0xc157e604\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffe604, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.h TEST #9... ");
    rs1 = 0xa5896b23;
    INSTRUCTION_SINGLE("sext.h", &result, &rs1);
    if (result != 0x6b23) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.h rd, 0xa5896b23\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x6b23, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.h TEST #10... ");
    rs1 = 0xb8ad1df3;
    INSTRUCTION_SINGLE("sext.h", &result, &rs1);
    if (result != 0x1df3) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.h rd, 0xb8ad1df3\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1df3, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.h TEST #11... ");
    rs1 = 0x3028670e;
    INSTRUCTION_SINGLE("sext.h", &result, &rs1);
    if (result != 0x670e) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.h rd, 0x3028670e\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x670e, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.h TEST #12... ");
    rs1 = 0x3f56573;
    INSTRUCTION_SINGLE("sext.h", &result, &rs1);
    if (result != 0x6573) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.h rd, 0x3f56573\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x6573, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.h TEST #13... ");
    rs1 = 0x4deebae6;
    INSTRUCTION_SINGLE("sext.h", &result, &rs1);
    if (result != 0xffffbae6) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.h rd, 0x4deebae6\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffbae6, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.h TEST #14... ");
    rs1 = 0xf0bc47ec;
    INSTRUCTION_SINGLE("sext.h", &result, &rs1);
    if (result != 0x47ec) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.h rd, 0xf0bc47ec\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x47ec, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("sext.h TEST #15... ");
    rs1 = 0xf7d7e641;
    INSTRUCTION_SINGLE("sext.h", &result, &rs1);
    if (result != 0xffffe641) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("sext.h rd, 0xf7d7e641\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffe641, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("zext.h TEST #0... ");
    rs1 = 0x1c21a485;
    INSTRUCTION_SINGLE("zext.h", &result, &rs1);
    if (result != 0xa485) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("zext.h rd, 0x1c21a485\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xa485, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("zext.h TEST #1... ");
    rs1 = 0xe0dd8f20;
    INSTRUCTION_SINGLE("zext.h", &result, &rs1);
    if (result != 0x8f20) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("zext.h rd, 0xe0dd8f20\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x8f20, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("zext.h TEST #2... ");
    rs1 = 0x7d27428e;
    INSTRUCTION_SINGLE("zext.h", &result, &rs1);
    if (result != 0x428e) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("zext.h rd, 0x7d27428e\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x428e, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("zext.h TEST #3... ");
    rs1 = 0x7f0c430f;
    INSTRUCTION_SINGLE("zext.h", &result, &rs1);
    if (result != 0x430f) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("zext.h rd, 0x7f0c430f\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x430f, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("zext.h TEST #4... ");
    rs1 = 0xf4fec1;
    INSTRUCTION_SINGLE("zext.h", &result, &rs1);
    if (result != 0xfec1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("zext.h rd, 0xf4fec1\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xfec1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("zext.h TEST #5... ");
    rs1 = 0xd0e4717b;
    INSTRUCTION_SINGLE("zext.h", &result, &rs1);
    if (result != 0x717b) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("zext.h rd, 0xd0e4717b\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x717b, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("zext.h TEST #6... ");
    rs1 = 0x31d44413;
    INSTRUCTION_SINGLE("zext.h", &result, &rs1);
    if (result != 0x4413) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("zext.h rd, 0x31d44413\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x4413, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("zext.h TEST #7... ");
    rs1 = 0xc241d417;
    INSTRUCTION_SINGLE("zext.h", &result, &rs1);
    if (result != 0xd417) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("zext.h rd, 0xc241d417\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xd417, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("zext.h TEST #8... ");
    rs1 = 0x49f8d61f;
    INSTRUCTION_SINGLE("zext.h", &result, &rs1);
    if (result != 0xd61f) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("zext.h rd, 0x49f8d61f\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xd61f, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("zext.h TEST #9... ");
    rs1 = 0xd8cf3f50;
    INSTRUCTION_SINGLE("zext.h", &result, &rs1);
    if (result != 0x3f50) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("zext.h rd, 0xd8cf3f50\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x3f50, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("zext.h TEST #10... ");
    rs1 = 0x73d4272c;
    INSTRUCTION_SINGLE("zext.h", &result, &rs1);
    if (result != 0x272c) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("zext.h rd, 0x73d4272c\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x272c, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("zext.h TEST #11... ");
    rs1 = 0x2203442e;
    INSTRUCTION_SINGLE("zext.h", &result, &rs1);
    if (result != 0x442e) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("zext.h rd, 0x2203442e\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x442e, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("zext.h TEST #12... ");
    rs1 = 0x707afd76;
    INSTRUCTION_SINGLE("zext.h", &result, &rs1);
    if (result != 0xfd76) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("zext.h rd, 0x707afd76\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xfd76, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("zext.h TEST #13... ");
    rs1 = 0xa7702f86;
    INSTRUCTION_SINGLE("zext.h", &result, &rs1);
    if (result != 0x2f86) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("zext.h rd, 0xa7702f86\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x2f86, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("zext.h TEST #14... ");
    rs1 = 0x2f0a4208;
    INSTRUCTION_SINGLE("zext.h", &result, &rs1);
    if (result != 0x4208) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("zext.h rd, 0x2f0a4208\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x4208, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("zext.h TEST #15... ");
    rs1 = 0xf101f170;
    INSTRUCTION_SINGLE("zext.h", &result, &rs1);
    if (result != 0xf170) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("zext.h rd, 0xf101f170\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xf170, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rev8 TEST #0... ");
    rs1 = 0xa3650f04;
    INSTRUCTION_SINGLE("rev8", &result, &rs1);
    if (result != 0x40f65a3) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rev8 rd, 0xa3650f04\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x40f65a3, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rev8 TEST #1... ");
    rs1 = 0x86b8bd5b;
    INSTRUCTION_SINGLE("rev8", &result, &rs1);
    if (result != 0x5bbdb886) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rev8 rd, 0x86b8bd5b\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x5bbdb886, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rev8 TEST #2... ");
    rs1 = 0xe7e2070c;
    INSTRUCTION_SINGLE("rev8", &result, &rs1);
    if (result != 0xc07e2e7) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rev8 rd, 0xe7e2070c\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xc07e2e7, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rev8 TEST #3... ");
    rs1 = 0x16ed24cb;
    INSTRUCTION_SINGLE("rev8", &result, &rs1);
    if (result != 0xcb24ed16) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rev8 rd, 0x16ed24cb\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xcb24ed16, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rev8 TEST #4... ");
    rs1 = 0xa0dbc3eb;
    INSTRUCTION_SINGLE("rev8", &result, &rs1);
    if (result != 0xebc3dba0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rev8 rd, 0xa0dbc3eb\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xebc3dba0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rev8 TEST #5... ");
    rs1 = 0x1e1864c3;
    INSTRUCTION_SINGLE("rev8", &result, &rs1);
    if (result != 0xc364181e) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rev8 rd, 0x1e1864c3\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xc364181e, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rev8 TEST #6... ");
    rs1 = 0x44a90443;
    INSTRUCTION_SINGLE("rev8", &result, &rs1);
    if (result != 0x4304a944) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rev8 rd, 0x44a90443\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x4304a944, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rev8 TEST #7... ");
    rs1 = 0x218f2b0d;
    INSTRUCTION_SINGLE("rev8", &result, &rs1);
    if (result != 0xd2b8f21) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rev8 rd, 0x218f2b0d\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xd2b8f21, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rev8 TEST #8... ");
    rs1 = 0x7093d620;
    INSTRUCTION_SINGLE("rev8", &result, &rs1);
    if (result != 0x20d69370) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rev8 rd, 0x7093d620\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x20d69370, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rev8 TEST #9... ");
    rs1 = 0x3b2234f7;
    INSTRUCTION_SINGLE("rev8", &result, &rs1);
    if (result != 0xf734223b) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rev8 rd, 0x3b2234f7\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xf734223b, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rev8 TEST #10... ");
    rs1 = 0xca1e16b;
    INSTRUCTION_SINGLE("rev8", &result, &rs1);
    if (result != 0x6be1a10c) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rev8 rd, 0xca1e16b\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x6be1a10c, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rev8 TEST #11... ");
    rs1 = 0x5c940739;
    INSTRUCTION_SINGLE("rev8", &result, &rs1);
    if (result != 0x3907945c) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rev8 rd, 0x5c940739\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x3907945c, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rev8 TEST #12... ");
    rs1 = 0xcd0b5863;
    INSTRUCTION_SINGLE("rev8", &result, &rs1);
    if (result != 0x63580bcd) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rev8 rd, 0xcd0b5863\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x63580bcd, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rev8 TEST #13... ");
    rs1 = 0x67c046b4;
    INSTRUCTION_SINGLE("rev8", &result, &rs1);
    if (result != 0xb446c067) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rev8 rd, 0x67c046b4\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xb446c067, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rev8 TEST #14... ");
    rs1 = 0xc5d7e82e;
    INSTRUCTION_SINGLE("rev8", &result, &rs1);
    if (result != 0x2ee8d7c5) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rev8 rd, 0xc5d7e82e\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x2ee8d7c5, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rev8 TEST #15... ");
    rs1 = 0xf6adca33;
    INSTRUCTION_SINGLE("rev8", &result, &rs1);
    if (result != 0x33caadf6) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rev8 rd, 0xf6adca33\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x33caadf6, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orc.b TEST #0... ");
    rs1 = 0xafab5a3a;
    INSTRUCTION_SINGLE("orc.b", &result, &rs1);
    if (result != 0xffffffff) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orc.b rd, 0xafab5a3a\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffffff, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orc.b TEST #1... ");
    rs1 = 0x866d4a77;
    INSTRUCTION_SINGLE("orc.b", &result, &rs1);
    if (result != 0xffffffff) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orc.b rd, 0x866d4a77\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffffff, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orc.b TEST #2... ");
    rs1 = 0x76c9b327;
    INSTRUCTION_SINGLE("orc.b", &result, &rs1);
    if (result != 0xffffffff) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orc.b rd, 0x76c9b327\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffffff, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orc.b TEST #3... ");
    rs1 = 0x8e3d7af;
    INSTRUCTION_SINGLE("orc.b", &result, &rs1);
    if (result != 0xffffffff) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orc.b rd, 0x8e3d7af\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffffff, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orc.b TEST #4... ");
    rs1 = 0x317194b8;
    INSTRUCTION_SINGLE("orc.b", &result, &rs1);
    if (result != 0xffffffff) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orc.b rd, 0x317194b8\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffffff, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orc.b TEST #5... ");
    rs1 = 0xc49cd7db;
    INSTRUCTION_SINGLE("orc.b", &result, &rs1);
    if (result != 0xffffffff) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orc.b rd, 0xc49cd7db\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffffff, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orc.b TEST #6... ");
    rs1 = 0xe04c63a5;
    INSTRUCTION_SINGLE("orc.b", &result, &rs1);
    if (result != 0xffffffff) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orc.b rd, 0xe04c63a5\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffffff, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orc.b TEST #7... ");
    rs1 = 0x20473731;
    INSTRUCTION_SINGLE("orc.b", &result, &rs1);
    if (result != 0xffffffff) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orc.b rd, 0x20473731\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffffff, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orc.b TEST #8... ");
    rs1 = 0xba909408;
    INSTRUCTION_SINGLE("orc.b", &result, &rs1);
    if (result != 0xffffffff) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orc.b rd, 0xba909408\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffffff, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orc.b TEST #9... ");
    rs1 = 0xe98948bf;
    INSTRUCTION_SINGLE("orc.b", &result, &rs1);
    if (result != 0xffffffff) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orc.b rd, 0xe98948bf\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffffff, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orc.b TEST #10... ");
    rs1 = 0x763d2af7;
    INSTRUCTION_SINGLE("orc.b", &result, &rs1);
    if (result != 0xffffffff) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orc.b rd, 0x763d2af7\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffffff, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orc.b TEST #11... ");
    rs1 = 0x5daaf0c4;
    INSTRUCTION_SINGLE("orc.b", &result, &rs1);
    if (result != 0xffffffff) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orc.b rd, 0x5daaf0c4\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffffff, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orc.b TEST #12... ");
    rs1 = 0x2cd63ae1;
    INSTRUCTION_SINGLE("orc.b", &result, &rs1);
    if (result != 0xffffffff) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orc.b rd, 0x2cd63ae1\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffffff, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orc.b TEST #13... ");
    rs1 = 0x264afe29;
    INSTRUCTION_SINGLE("orc.b", &result, &rs1);
    if (result != 0xffffffff) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orc.b rd, 0x264afe29\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffffff, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orc.b TEST #14... ");
    rs1 = 0x593ebda5;
    INSTRUCTION_SINGLE("orc.b", &result, &rs1);
    if (result != 0xffffffff) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orc.b rd, 0x593ebda5\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffffff, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orc.b TEST #15... ");
    rs1 = 0xda17dbf2;
    INSTRUCTION_SINGLE("orc.b", &result, &rs1);
    if (result != 0xffffffff) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orc.b rd, 0xda17dbf2\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xffffffff, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("clz TEST #0... ");
    rs1 = 0xca773b35;
    INSTRUCTION_SINGLE("clz", &result, &rs1);
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("clz rd, 0xca773b35\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("clz TEST #1... ");
    rs1 = 0xbd16f716;
    INSTRUCTION_SINGLE("clz", &result, &rs1);
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("clz rd, 0xbd16f716\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("clz TEST #2... ");
    rs1 = 0xe0ce5e35;
    INSTRUCTION_SINGLE("clz", &result, &rs1);
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("clz rd, 0xe0ce5e35\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("clz TEST #3... ");
    rs1 = 0xd361a178;
    INSTRUCTION_SINGLE("clz", &result, &rs1);
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("clz rd, 0xd361a178\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("clz TEST #4... ");
    rs1 = 0x8bda31bb;
    INSTRUCTION_SINGLE("clz", &result, &rs1);
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("clz rd, 0x8bda31bb\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("clz TEST #5... ");
    rs1 = 0x53871532;
    INSTRUCTION_SINGLE("clz", &result, &rs1);
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("clz rd, 0x53871532\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("clz TEST #6... ");
    rs1 = 0xf2b57d8f;
    INSTRUCTION_SINGLE("clz", &result, &rs1);
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("clz rd, 0xf2b57d8f\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("clz TEST #7... ");
    rs1 = 0x8858118e;
    INSTRUCTION_SINGLE("clz", &result, &rs1);
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("clz rd, 0x8858118e\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("clz TEST #8... ");
    rs1 = 0xc27472a2;
    INSTRUCTION_SINGLE("clz", &result, &rs1);
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("clz rd, 0xc27472a2\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("clz TEST #9... ");
    rs1 = 0x79cb2b63;
    INSTRUCTION_SINGLE("clz", &result, &rs1);
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("clz rd, 0x79cb2b63\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("clz TEST #10... ");
    rs1 = 0xebda8223;
    INSTRUCTION_SINGLE("clz", &result, &rs1);
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("clz rd, 0xebda8223\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("clz TEST #11... ");
    rs1 = 0xc438fc5;
    INSTRUCTION_SINGLE("clz", &result, &rs1);
    if (result != 0x4) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("clz rd, 0xc438fc5\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x4, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("clz TEST #12... ");
    rs1 = 0x4b43c8a0;
    INSTRUCTION_SINGLE("clz", &result, &rs1);
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("clz rd, 0x4b43c8a0\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("clz TEST #13... ");
    rs1 = 0x4a253fe8;
    INSTRUCTION_SINGLE("clz", &result, &rs1);
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("clz rd, 0x4a253fe8\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("clz TEST #14... ");
    rs1 = 0xee66fdb1;
    INSTRUCTION_SINGLE("clz", &result, &rs1);
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("clz rd, 0xee66fdb1\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("clz TEST #15... ");
    rs1 = 0xa377d933;
    INSTRUCTION_SINGLE("clz", &result, &rs1);
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("clz rd, 0xa377d933\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("cpop TEST #0... ");
    rs1 = 0x101714dd;
    INSTRUCTION_SINGLE("cpop", &result, &rs1);
    if (result != 0xd) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("cpop rd, 0x101714dd\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xd, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("cpop TEST #1... ");
    rs1 = 0xc9655dd0;
    INSTRUCTION_SINGLE("cpop", &result, &rs1);
    if (result != 0x10) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("cpop rd, 0xc9655dd0\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x10, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("cpop TEST #2... ");
    rs1 = 0xa9af5cca;
    INSTRUCTION_SINGLE("cpop", &result, &rs1);
    if (result != 0x12) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("cpop rd, 0xa9af5cca\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x12, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("cpop TEST #3... ");
    rs1 = 0xac457de9;
    INSTRUCTION_SINGLE("cpop", &result, &rs1);
    if (result != 0x12) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("cpop rd, 0xac457de9\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x12, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("cpop TEST #4... ");
    rs1 = 0x2b722aad;
    INSTRUCTION_SINGLE("cpop", &result, &rs1);
    if (result != 0x10) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("cpop rd, 0x2b722aad\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x10, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("cpop TEST #5... ");
    rs1 = 0x1bbafd4;
    INSTRUCTION_SINGLE("cpop", &result, &rs1);
    if (result != 0x11) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("cpop rd, 0x1bbafd4\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x11, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("cpop TEST #6... ");
    rs1 = 0xd837da4b;
    INSTRUCTION_SINGLE("cpop", &result, &rs1);
    if (result != 0x12) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("cpop rd, 0xd837da4b\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x12, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("cpop TEST #7... ");
    rs1 = 0x8f165d4b;
    INSTRUCTION_SINGLE("cpop", &result, &rs1);
    if (result != 0x11) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("cpop rd, 0x8f165d4b\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x11, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("cpop TEST #8... ");
    rs1 = 0xc76cad63;
    INSTRUCTION_SINGLE("cpop", &result, &rs1);
    if (result != 0x12) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("cpop rd, 0xc76cad63\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x12, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("cpop TEST #9... ");
    rs1 = 0x7815245f;
    INSTRUCTION_SINGLE("cpop", &result, &rs1);
    if (result != 0xf) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("cpop rd, 0x7815245f\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xf, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("cpop TEST #10... ");
    rs1 = 0xe93403ff;
    INSTRUCTION_SINGLE("cpop", &result, &rs1);
    if (result != 0x12) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("cpop rd, 0xe93403ff\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x12, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("cpop TEST #11... ");
    rs1 = 0x562a1675;
    INSTRUCTION_SINGLE("cpop", &result, &rs1);
    if (result != 0xf) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("cpop rd, 0x562a1675\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xf, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("cpop TEST #12... ");
    rs1 = 0x6ef37a8d;
    INSTRUCTION_SINGLE("cpop", &result, &rs1);
    if (result != 0x14) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("cpop rd, 0x6ef37a8d\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x14, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("cpop TEST #13... ");
    rs1 = 0x698be3bc;
    INSTRUCTION_SINGLE("cpop", &result, &rs1);
    if (result != 0x12) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("cpop rd, 0x698be3bc\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x12, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("cpop TEST #14... ");
    rs1 = 0x1070f18e;
    INSTRUCTION_SINGLE("cpop", &result, &rs1);
    if (result != 0xd) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("cpop rd, 0x1070f18e\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xd, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("cpop TEST #15... ");
    rs1 = 0x79fc093a;
    INSTRUCTION_SINGLE("cpop", &result, &rs1);
    if (result != 0x11) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("cpop rd, 0x79fc093a\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x11, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ctz TEST #0... ");
    rs1 = 0xbd745d8e;
    INSTRUCTION_SINGLE("ctz", &result, &rs1);
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ctz rd, 0xbd745d8e\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ctz TEST #1... ");
    rs1 = 0x31f49c0d;
    INSTRUCTION_SINGLE("ctz", &result, &rs1);
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ctz rd, 0x31f49c0d\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ctz TEST #2... ");
    rs1 = 0xa3ef5b03;
    INSTRUCTION_SINGLE("ctz", &result, &rs1);
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ctz rd, 0xa3ef5b03\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ctz TEST #3... ");
    rs1 = 0x1d6d557d;
    INSTRUCTION_SINGLE("ctz", &result, &rs1);
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ctz rd, 0x1d6d557d\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ctz TEST #4... ");
    rs1 = 0x7f992e14;
    INSTRUCTION_SINGLE("ctz", &result, &rs1);
    if (result != 0x2) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ctz rd, 0x7f992e14\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x2, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ctz TEST #5... ");
    rs1 = 0xd029150a;
    INSTRUCTION_SINGLE("ctz", &result, &rs1);
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ctz rd, 0xd029150a\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ctz TEST #6... ");
    rs1 = 0x266dc672;
    INSTRUCTION_SINGLE("ctz", &result, &rs1);
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ctz rd, 0x266dc672\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ctz TEST #7... ");
    rs1 = 0x2ee205e3;
    INSTRUCTION_SINGLE("ctz", &result, &rs1);
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ctz rd, 0x2ee205e3\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ctz TEST #8... ");
    rs1 = 0x4ccca12a;
    INSTRUCTION_SINGLE("ctz", &result, &rs1);
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ctz rd, 0x4ccca12a\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ctz TEST #9... ");
    rs1 = 0xea011715;
    INSTRUCTION_SINGLE("ctz", &result, &rs1);
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ctz rd, 0xea011715\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ctz TEST #10... ");
    rs1 = 0x306ad0e8;
    INSTRUCTION_SINGLE("ctz", &result, &rs1);
    if (result != 0x3) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ctz rd, 0x306ad0e8\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x3, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ctz TEST #11... ");
    rs1 = 0x269490;
    INSTRUCTION_SINGLE("ctz", &result, &rs1);
    if (result != 0x4) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ctz rd, 0x269490\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x4, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ctz TEST #12... ");
    rs1 = 0x3f2f5a82;
    INSTRUCTION_SINGLE("ctz", &result, &rs1);
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ctz rd, 0x3f2f5a82\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ctz TEST #13... ");
    rs1 = 0x226b6602;
    INSTRUCTION_SINGLE("ctz", &result, &rs1);
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ctz rd, 0x226b6602\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ctz TEST #14... ");
    rs1 = 0xb7d11c68;
    INSTRUCTION_SINGLE("ctz", &result, &rs1);
    if (result != 0x3) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ctz rd, 0xb7d11c68\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x3, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ctz TEST #15... ");
    rs1 = 0x972dabb8;
    INSTRUCTION_SINGLE("ctz", &result, &rs1);
    if (result != 0x3) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ctz rd, 0x972dabb8\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x3, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ror TEST #0... ");
    rs1 = 0x6f77eec5;
    rs2 = 0xe9a69971;
    INSTRUCTION("ror", &result, &rs1, &rs2);
    if (result != 0xf762b7bb) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ror rd, 0x6f77eec5, 0xe9a69971\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xf762b7bb, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ror TEST #1... ");
    rs1 = 0xe7d8b4b6;
    rs2 = 0x8a53a719;
    INSTRUCTION("ror", &result, &rs1, &rs2);
    if (result != 0xec5a5b73) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ror rd, 0xe7d8b4b6, 0x8a53a719\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xec5a5b73, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ror TEST #2... ");
    rs1 = 0xc450811a;
    rs2 = 0x721fddc0;
    INSTRUCTION("ror", &result, &rs1, &rs2);
    if (result != 0xc450811a) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ror rd, 0xc450811a, 0x721fddc0\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xc450811a, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ror TEST #3... ");
    rs1 = 0xc65a4c19;
    rs2 = 0x42d79085;
    INSTRUCTION("ror", &result, &rs1, &rs2);
    if (result != 0xce32d260) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ror rd, 0xc65a4c19, 0x42d79085\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xce32d260, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ror TEST #4... ");
    rs1 = 0xd2116a40;
    rs2 = 0x5669405a;
    INSTRUCTION("ror", &result, &rs1, &rs2);
    if (result != 0x845a9034) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ror rd, 0xd2116a40, 0x5669405a\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x845a9034, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ror TEST #5... ");
    rs1 = 0x37a1c19b;
    rs2 = 0x71cbf6f7;
    INSTRUCTION("ror", &result, &rs1, &rs2);
    if (result != 0x4383366f) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ror rd, 0x37a1c19b, 0x71cbf6f7\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x4383366f, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ror TEST #6... ");
    rs1 = 0xff015b78;
    rs2 = 0x8fc5df23;
    INSTRUCTION("ror", &result, &rs1, &rs2);
    if (result != 0x1fe02b6f) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ror rd, 0xff015b78, 0x8fc5df23\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1fe02b6f, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ror TEST #7... ");
    rs1 = 0x774655ae;
    rs2 = 0xa522fb22;
    INSTRUCTION("ror", &result, &rs1, &rs2);
    if (result != 0x9dd1956b) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ror rd, 0x774655ae, 0xa522fb22\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x9dd1956b, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ror TEST #8... ");
    rs1 = 0x5d06241c;
    rs2 = 0xe4f9371e;
    INSTRUCTION("ror", &result, &rs1, &rs2);
    if (result != 0x74189071) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ror rd, 0x5d06241c, 0xe4f9371e\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x74189071, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ror TEST #9... ");
    rs1 = 0x9ce17f3d;
    rs2 = 0x38f6ce80;
    INSTRUCTION("ror", &result, &rs1, &rs2);
    if (result != 0x9ce17f3d) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ror rd, 0x9ce17f3d, 0x38f6ce80\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x9ce17f3d, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ror TEST #10... ");
    rs1 = 0xa3996998;
    rs2 = 0x119800f6;
    INSTRUCTION("ror", &result, &rs1, &rs2);
    if (result != 0x65a6628e) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ror rd, 0xa3996998, 0x119800f6\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x65a6628e, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ror TEST #11... ");
    rs1 = 0xd0ced13c;
    rs2 = 0x9889a54f;
    INSTRUCTION("ror", &result, &rs1, &rs2);
    if (result != 0xa279a19d) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ror rd, 0xd0ced13c, 0x9889a54f\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xa279a19d, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ror TEST #12... ");
    rs1 = 0x42a8fa56;
    rs2 = 0x6d38db00;
    INSTRUCTION("ror", &result, &rs1, &rs2);
    if (result != 0x42a8fa56) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ror rd, 0x42a8fa56, 0x6d38db00\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x42a8fa56, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ror TEST #13... ");
    rs1 = 0xd5b343b6;
    rs2 = 0xde075941;
    INSTRUCTION("ror", &result, &rs1, &rs2);
    if (result != 0x6ad9a1db) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ror rd, 0xd5b343b6, 0xde075941\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x6ad9a1db, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ror TEST #14... ");
    rs1 = 0x4c7e6452;
    rs2 = 0xb1e70127;
    INSTRUCTION("ror", &result, &rs1, &rs2);
    if (result != 0xa498fcc8) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ror rd, 0x4c7e6452, 0xb1e70127\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xa498fcc8, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("ror TEST #15... ");
    rs1 = 0x90f31623;
    rs2 = 0x71e5292a;
    INSTRUCTION("ror", &result, &rs1, &rs2);
    if (result != 0x88e43cc5) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("ror rd, 0x90f31623, 0x71e5292a\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x88e43cc5, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rori TEST #0... ");
    rs1 = 0xabe7041e;
    INSTRUCTION_IMM("rori", &result, &rs1, "31");
    if (result != 0x57ce083d) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rori rd, 0xabe7041e, 0x1f\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x57ce083d, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rori TEST #1... ");
    rs1 = 0x9cea7000;
    INSTRUCTION_IMM("rori", &result, &rs1, "29");
    if (result != 0xe7538004) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rori rd, 0x9cea7000, 0x1d\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xe7538004, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rori TEST #2... ");
    rs1 = 0xbdd86dec;
    INSTRUCTION_IMM("rori", &result, &rs1, "20");
    if (result != 0x86decbdd) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rori rd, 0xbdd86dec, 0x14\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x86decbdd, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rori TEST #3... ");
    rs1 = 0x9ef409c7;
    INSTRUCTION_IMM("rori", &result, &rs1, "4");
    if (result != 0x79ef409c) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rori rd, 0x9ef409c7, 0x4\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x79ef409c, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rori TEST #4... ");
    rs1 = 0x3c223c9b;
    INSTRUCTION_IMM("rori", &result, &rs1, "29");
    if (result != 0xe111e4d9) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rori rd, 0x3c223c9b, 0x1d\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xe111e4d9, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rori TEST #5... ");
    rs1 = 0x907c1ca9;
    INSTRUCTION_IMM("rori", &result, &rs1, "30");
    if (result != 0x41f072a6) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rori rd, 0x907c1ca9, 0x1e\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x41f072a6, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rori TEST #6... ");
    rs1 = 0xf611ec4;
    INSTRUCTION_IMM("rori", &result, &rs1, "25");
    if (result != 0xb08f6207) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rori rd, 0xf611ec4, 0x19\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xb08f6207, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rori TEST #7... ");
    rs1 = 0x2cc963e7;
    INSTRUCTION_IMM("rori", &result, &rs1, "5");
    if (result != 0x39664b1f) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rori rd, 0x2cc963e7, 0x5\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x39664b1f, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rori TEST #8... ");
    rs1 = 0xeec22ab9;
    INSTRUCTION_IMM("rori", &result, &rs1, "19");
    if (result != 0x45573dd8) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rori rd, 0xeec22ab9, 0x13\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x45573dd8, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rori TEST #9... ");
    rs1 = 0xb5232697;
    INSTRUCTION_IMM("rori", &result, &rs1, "21");
    if (result != 0x1934bda9) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rori rd, 0xb5232697, 0x15\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1934bda9, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rori TEST #10... ");
    rs1 = 0xb6eb1fd5;
    INSTRUCTION_IMM("rori", &result, &rs1, "21");
    if (result != 0x58feadb7) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rori rd, 0xb6eb1fd5, 0x15\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x58feadb7, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rori TEST #11... ");
    rs1 = 0x35dd8f2f;
    INSTRUCTION_IMM("rori", &result, &rs1, "22");
    if (result != 0x763cbcd7) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rori rd, 0x35dd8f2f, 0x16\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x763cbcd7, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rori TEST #12... ");
    rs1 = 0x6f634fe6;
    INSTRUCTION_IMM("rori", &result, &rs1, "6");
    if (result != 0x99bd8d3f) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rori rd, 0x6f634fe6, 0x6\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x99bd8d3f, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rori TEST #13... ");
    rs1 = 0x8b342d23;
    INSTRUCTION_IMM("rori", &result, &rs1, "16");
    if (result != 0x2d238b34) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rori rd, 0x8b342d23, 0x10\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x2d238b34, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rori TEST #14... ");
    rs1 = 0xfc8d4913;
    INSTRUCTION_IMM("rori", &result, &rs1, "15");
    if (result != 0x9227f91a) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rori rd, 0xfc8d4913, 0xf\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x9227f91a, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rori TEST #15... ");
    rs1 = 0x88d90362;
    INSTRUCTION_IMM("rori", &result, &rs1, "12");
    if (result != 0x36288d90) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rori rd, 0x88d90362, 0xc\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x36288d90, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rol TEST #0... ");
    rs1 = 0xe873ddc5;
    rs2 = 0x97d77a7d;
    INSTRUCTION("rol", &result, &rs1, &rs2);
    if (result != 0xbd0e7bb8) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rol rd, 0xe873ddc5, 0x97d77a7d\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xbd0e7bb8, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rol TEST #1... ");
    rs1 = 0x19bb0406;
    rs2 = 0x78206e2c;
    INSTRUCTION("rol", &result, &rs1, &rs2);
    if (result != 0xb040619b) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rol rd, 0x19bb0406, 0x78206e2c\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xb040619b, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rol TEST #2... ");
    rs1 = 0x997d6e18;
    rs2 = 0x54909976;
    INSTRUCTION("rol", &result, &rs1, &rs2);
    if (result != 0x86265f5b) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rol rd, 0x997d6e18, 0x54909976\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x86265f5b, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rol TEST #3... ");
    rs1 = 0xf6058424;
    rs2 = 0xb4185664;
    INSTRUCTION("rol", &result, &rs1, &rs2);
    if (result != 0x6058424f) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rol rd, 0xf6058424, 0xb4185664\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x6058424f, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rol TEST #4... ");
    rs1 = 0x9defeedf;
    rs2 = 0x220874d3;
    INSTRUCTION("rol", &result, &rs1, &rs2);
    if (result != 0x76fcef7f) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rol rd, 0x9defeedf, 0x220874d3\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x76fcef7f, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rol TEST #5... ");
    rs1 = 0x5ef7c675;
    rs2 = 0xced7619d;
    INSTRUCTION("rol", &result, &rs1, &rs2);
    if (result != 0xabdef8ce) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rol rd, 0x5ef7c675, 0xced7619d\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xabdef8ce, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rol TEST #6... ");
    rs1 = 0x34042582;
    rs2 = 0xe65f0672;
    INSTRUCTION("rol", &result, &rs1, &rs2);
    if (result != 0x9608d010) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rol rd, 0x34042582, 0xe65f0672\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x9608d010, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rol TEST #7... ");
    rs1 = 0xb71bdda;
    rs2 = 0xdfcaebb6;
    INSTRUCTION("rol", &result, &rs1, &rs2);
    if (result != 0x7682dc6f) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rol rd, 0xb71bdda, 0xdfcaebb6\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x7682dc6f, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rol TEST #8... ");
    rs1 = 0x7bf39f43;
    rs2 = 0x120cee66;
    INSTRUCTION("rol", &result, &rs1, &rs2);
    if (result != 0xfce7d0de) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rol rd, 0x7bf39f43, 0x120cee66\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xfce7d0de, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rol TEST #9... ");
    rs1 = 0x6cf39be6;
    rs2 = 0x638be98;
    INSTRUCTION("rol", &result, &rs1, &rs2);
    if (result != 0xe66cf39b) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rol rd, 0x6cf39be6, 0x638be98\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xe66cf39b, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rol TEST #10... ");
    rs1 = 0x65746041;
    rs2 = 0x123b4662;
    INSTRUCTION("rol", &result, &rs1, &rs2);
    if (result != 0x95d18105) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rol rd, 0x65746041, 0x123b4662\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x95d18105, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rol TEST #11... ");
    rs1 = 0x7a8284c7;
    rs2 = 0x562ca1df;
    INSTRUCTION("rol", &result, &rs1, &rs2);
    if (result != 0xbd414263) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rol rd, 0x7a8284c7, 0x562ca1df\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xbd414263, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rol TEST #12... ");
    rs1 = 0x6e4c5cf0;
    rs2 = 0xebe7b63d;
    INSTRUCTION("rol", &result, &rs1, &rs2);
    if (result != 0xdc98b9e) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rol rd, 0x6e4c5cf0, 0xebe7b63d\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xdc98b9e, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rol TEST #13... ");
    rs1 = 0xa07f4fab;
    rs2 = 0xbd4c71b3;
    INSTRUCTION("rol", &result, &rs1, &rs2);
    if (result != 0x7d5d03fa) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rol rd, 0xa07f4fab, 0xbd4c71b3\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x7d5d03fa, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rol TEST #14... ");
    rs1 = 0xbf06de81;
    rs2 = 0x2539d6ed;
    INSTRUCTION("rol", &result, &rs1, &rs2);
    if (result != 0xdbd037e0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rol rd, 0xbf06de81, 0x2539d6ed\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xdbd037e0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("rol TEST #15... ");
    rs1 = 0xbe1d9a2e;
    rs2 = 0x545d1f46;
    INSTRUCTION("rol", &result, &rs1, &rs2);
    if (result != 0x87668baf) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("rol rd, 0xbe1d9a2e, 0x545d1f46\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x87668baf, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("xnor TEST #0... ");
    rs1 = 0xbaadb6fe;
    rs2 = 0xab7140a0;
    INSTRUCTION("xnor", &result, &rs1, &rs2);
    if (result != 0xee2309a1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("xnor rd, 0xbaadb6fe, 0xab7140a0\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xee2309a1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("xnor TEST #1... ");
    rs1 = 0xa5f37340;
    rs2 = 0x72866985;
    INSTRUCTION("xnor", &result, &rs1, &rs2);
    if (result != 0x288ae53a) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("xnor rd, 0xa5f37340, 0x72866985\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x288ae53a, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("xnor TEST #2... ");
    rs1 = 0x1bbb0154;
    rs2 = 0xd269dc83;
    INSTRUCTION("xnor", &result, &rs1, &rs2);
    if (result != 0x362d2228) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("xnor rd, 0x1bbb0154, 0xd269dc83\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x362d2228, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("xnor TEST #3... ");
    rs1 = 0x8fc23c66;
    rs2 = 0xb77065c2;
    INSTRUCTION("xnor", &result, &rs1, &rs2);
    if (result != 0xc74da65b) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("xnor rd, 0x8fc23c66, 0xb77065c2\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xc74da65b, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("xnor TEST #4... ");
    rs1 = 0xbef1d423;
    rs2 = 0x9a7ca5b0;
    INSTRUCTION("xnor", &result, &rs1, &rs2);
    if (result != 0xdb728e6c) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("xnor rd, 0xbef1d423, 0x9a7ca5b0\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xdb728e6c, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("xnor TEST #5... ");
    rs1 = 0xee20903c;
    rs2 = 0x48212176;
    INSTRUCTION("xnor", &result, &rs1, &rs2);
    if (result != 0x59fe4eb5) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("xnor rd, 0xee20903c, 0x48212176\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x59fe4eb5, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("xnor TEST #6... ");
    rs1 = 0x5392da12;
    rs2 = 0xe7b6d99c;
    INSTRUCTION("xnor", &result, &rs1, &rs2);
    if (result != 0x4bdbfc71) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("xnor rd, 0x5392da12, 0xe7b6d99c\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x4bdbfc71, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("xnor TEST #7... ");
    rs1 = 0xf8c64781;
    rs2 = 0xf3039bf2;
    INSTRUCTION("xnor", &result, &rs1, &rs2);
    if (result != 0xf43a238c) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("xnor rd, 0xf8c64781, 0xf3039bf2\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xf43a238c, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("xnor TEST #8... ");
    rs1 = 0x8cbb6344;
    rs2 = 0xd5c885bf;
    INSTRUCTION("xnor", &result, &rs1, &rs2);
    if (result != 0xa68c1904) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("xnor rd, 0x8cbb6344, 0xd5c885bf\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xa68c1904, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("xnor TEST #9... ");
    rs1 = 0x25919ba0;
    rs2 = 0xdfc5e5e6;
    INSTRUCTION("xnor", &result, &rs1, &rs2);
    if (result != 0x5ab81b9) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("xnor rd, 0x25919ba0, 0xdfc5e5e6\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x5ab81b9, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("xnor TEST #10... ");
    rs1 = 0x8261e919;
    rs2 = 0x9f2f5d63;
    INSTRUCTION("xnor", &result, &rs1, &rs2);
    if (result != 0xe2b14b85) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("xnor rd, 0x8261e919, 0x9f2f5d63\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xe2b14b85, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("xnor TEST #11... ");
    rs1 = 0x8ed9e35c;
    rs2 = 0x6fddddd1;
    INSTRUCTION("xnor", &result, &rs1, &rs2);
    if (result != 0x1efbc172) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("xnor rd, 0x8ed9e35c, 0x6fddddd1\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1efbc172, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("xnor TEST #12... ");
    rs1 = 0xad265faa;
    rs2 = 0xb20f98c5;
    INSTRUCTION("xnor", &result, &rs1, &rs2);
    if (result != 0xe0d63890) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("xnor rd, 0xad265faa, 0xb20f98c5\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xe0d63890, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("xnor TEST #13... ");
    rs1 = 0x852d6eb1;
    rs2 = 0xdec1c1aa;
    INSTRUCTION("xnor", &result, &rs1, &rs2);
    if (result != 0xa41350e4) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("xnor rd, 0x852d6eb1, 0xdec1c1aa\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xa41350e4, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("xnor TEST #14... ");
    rs1 = 0x66c8a8af;
    rs2 = 0x4c45f2da;
    INSTRUCTION("xnor", &result, &rs1, &rs2);
    if (result != 0xd572a58a) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("xnor rd, 0x66c8a8af, 0x4c45f2da\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xd572a58a, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("xnor TEST #15... ");
    rs1 = 0x3d264d16;
    rs2 = 0xcb46ebc4;
    INSTRUCTION("xnor", &result, &rs1, &rs2);
    if (result != 0x99f592d) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("xnor rd, 0x3d264d16, 0xcb46ebc4\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x99f592d, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("andn TEST #0... ");
    rs1 = 0x7298ed73;
    rs2 = 0xb4ac40e5;
    INSTRUCTION("andn", &result, &rs1, &rs2);
    if (result != 0x4210ad12) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("andn rd, 0x7298ed73, 0xb4ac40e5\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x4210ad12, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("andn TEST #1... ");
    rs1 = 0x4ebacae7;
    rs2 = 0xfb0cb6f0;
    INSTRUCTION("andn", &result, &rs1, &rs2);
    if (result != 0x4b24807) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("andn rd, 0x4ebacae7, 0xfb0cb6f0\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x4b24807, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("andn TEST #2... ");
    rs1 = 0x94c325fb;
    rs2 = 0x95d83608;
    INSTRUCTION("andn", &result, &rs1, &rs2);
    if (result != 0x301f3) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("andn rd, 0x94c325fb, 0x95d83608\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x301f3, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("andn TEST #3... ");
    rs1 = 0x6189bd84;
    rs2 = 0x66a3ed39;
    INSTRUCTION("andn", &result, &rs1, &rs2);
    if (result != 0x1081084) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("andn rd, 0x6189bd84, 0x66a3ed39\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1081084, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("andn TEST #4... ");
    rs1 = 0x28ebda71;
    rs2 = 0x623240be;
    INSTRUCTION("andn", &result, &rs1, &rs2);
    if (result != 0x8c99a41) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("andn rd, 0x28ebda71, 0x623240be\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x8c99a41, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("andn TEST #5... ");
    rs1 = 0x92968a95;
    rs2 = 0xb787ac82;
    INSTRUCTION("andn", &result, &rs1, &rs2);
    if (result != 0x100215) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("andn rd, 0x92968a95, 0xb787ac82\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x100215, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("andn TEST #6... ");
    rs1 = 0x3448b7a3;
    rs2 = 0xf3f880be;
    INSTRUCTION("andn", &result, &rs1, &rs2);
    if (result != 0x4003701) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("andn rd, 0x3448b7a3, 0xf3f880be\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x4003701, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("andn TEST #7... ");
    rs1 = 0xf896d6ae;
    rs2 = 0x4491db56;
    INSTRUCTION("andn", &result, &rs1, &rs2);
    if (result != 0xb80604a8) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("andn rd, 0xf896d6ae, 0x4491db56\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xb80604a8, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("andn TEST #8... ");
    rs1 = 0x6cbf5667;
    rs2 = 0xf4da0190;
    INSTRUCTION("andn", &result, &rs1, &rs2);
    if (result != 0x8255667) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("andn rd, 0x6cbf5667, 0xf4da0190\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x8255667, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("andn TEST #9... ");
    rs1 = 0xf97ad50b;
    rs2 = 0x833e8565;
    INSTRUCTION("andn", &result, &rs1, &rs2);
    if (result != 0x7840500a) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("andn rd, 0xf97ad50b, 0x833e8565\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x7840500a, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("andn TEST #10... ");
    rs1 = 0x6dc1976b;
    rs2 = 0x18464943;
    INSTRUCTION("andn", &result, &rs1, &rs2);
    if (result != 0x65819628) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("andn rd, 0x6dc1976b, 0x18464943\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x65819628, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("andn TEST #11... ");
    rs1 = 0x85981b05;
    rs2 = 0x2e76997c;
    INSTRUCTION("andn", &result, &rs1, &rs2);
    if (result != 0x81880201) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("andn rd, 0x85981b05, 0x2e76997c\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x81880201, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("andn TEST #12... ");
    rs1 = 0x26bf272c;
    rs2 = 0xebd9b525;
    INSTRUCTION("andn", &result, &rs1, &rs2);
    if (result != 0x4260208) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("andn rd, 0x26bf272c, 0xebd9b525\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x4260208, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("andn TEST #13... ");
    rs1 = 0x88cbbe20;
    rs2 = 0x5b282f0d;
    INSTRUCTION("andn", &result, &rs1, &rs2);
    if (result != 0x80c39020) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("andn rd, 0x88cbbe20, 0x5b282f0d\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x80c39020, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("andn TEST #14... ");
    rs1 = 0x83297a64;
    rs2 = 0x51370b7d;
    INSTRUCTION("andn", &result, &rs1, &rs2);
    if (result != 0x82087000) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("andn rd, 0x83297a64, 0x51370b7d\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x82087000, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("andn TEST #15... ");
    rs1 = 0x8ce39e46;
    rs2 = 0x8a1267d4;
    INSTRUCTION("andn", &result, &rs1, &rs2);
    if (result != 0x4e19802) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("andn rd, 0x8ce39e46, 0x8a1267d4\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x4e19802, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orn TEST #0... ");
    rs1 = 0x7c44eb17;
    rs2 = 0xfddcb876;
    INSTRUCTION("orn", &result, &rs1, &rs2);
    if (result != 0x7e67ef9f) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orn rd, 0x7c44eb17, 0xfddcb876\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x7e67ef9f, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orn TEST #1... ");
    rs1 = 0x733937e2;
    rs2 = 0xe6dacc50;
    INSTRUCTION("orn", &result, &rs1, &rs2);
    if (result != 0x7b3d37ef) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orn rd, 0x733937e2, 0xe6dacc50\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x7b3d37ef, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orn TEST #2... ");
    rs1 = 0x3a336a9d;
    rs2 = 0xd0f59374;
    INSTRUCTION("orn", &result, &rs1, &rs2);
    if (result != 0x3f3b6e9f) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orn rd, 0x3a336a9d, 0xd0f59374\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x3f3b6e9f, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orn TEST #3... ");
    rs1 = 0x401d6875;
    rs2 = 0xe5c1d30f;
    INSTRUCTION("orn", &result, &rs1, &rs2);
    if (result != 0x5a3f6cf5) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orn rd, 0x401d6875, 0xe5c1d30f\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x5a3f6cf5, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orn TEST #4... ");
    rs1 = 0xe52665c9;
    rs2 = 0x19333359;
    INSTRUCTION("orn", &result, &rs1, &rs2);
    if (result != 0xe7eeedef) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orn rd, 0xe52665c9, 0x19333359\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xe7eeedef, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orn TEST #5... ");
    rs1 = 0x58d9c2c;
    rs2 = 0xcc3bb197;
    INSTRUCTION("orn", &result, &rs1, &rs2);
    if (result != 0x37cdde6c) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orn rd, 0x58d9c2c, 0xcc3bb197\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x37cdde6c, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orn TEST #6... ");
    rs1 = 0xbf21064a;
    rs2 = 0xf5fa265a;
    INSTRUCTION("orn", &result, &rs1, &rs2);
    if (result != 0xbf25dfef) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orn rd, 0xbf21064a, 0xf5fa265a\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xbf25dfef, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orn TEST #7... ");
    rs1 = 0xf93673f0;
    rs2 = 0xa6212d27;
    INSTRUCTION("orn", &result, &rs1, &rs2);
    if (result != 0xf9fef3f8) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orn rd, 0xf93673f0, 0xa6212d27\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xf9fef3f8, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orn TEST #8... ");
    rs1 = 0xa6965975;
    rs2 = 0xa103fb0c;
    INSTRUCTION("orn", &result, &rs1, &rs2);
    if (result != 0xfefe5df7) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orn rd, 0xa6965975, 0xa103fb0c\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xfefe5df7, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orn TEST #9... ");
    rs1 = 0xd11eba79;
    rs2 = 0xcdf23c3b;
    INSTRUCTION("orn", &result, &rs1, &rs2);
    if (result != 0xf31ffbfd) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orn rd, 0xd11eba79, 0xcdf23c3b\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xf31ffbfd, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orn TEST #10... ");
    rs1 = 0x8d9fa53c;
    rs2 = 0x1043920e;
    INSTRUCTION("orn", &result, &rs1, &rs2);
    if (result != 0xefbfedfd) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orn rd, 0x8d9fa53c, 0x1043920e\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xefbfedfd, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orn TEST #11... ");
    rs1 = 0xca8bca9d;
    rs2 = 0x73e5b444;
    INSTRUCTION("orn", &result, &rs1, &rs2);
    if (result != 0xce9bcbbf) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orn rd, 0xca8bca9d, 0x73e5b444\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xce9bcbbf, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orn TEST #12... ");
    rs1 = 0x7065d82e;
    rs2 = 0x381d5043;
    INSTRUCTION("orn", &result, &rs1, &rs2);
    if (result != 0xf7e7ffbe) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orn rd, 0x7065d82e, 0x381d5043\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xf7e7ffbe, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orn TEST #13... ");
    rs1 = 0x32c3e2a0;
    rs2 = 0x5bcba4b6;
    INSTRUCTION("orn", &result, &rs1, &rs2);
    if (result != 0xb6f7fbe9) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orn rd, 0x32c3e2a0, 0x5bcba4b6\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xb6f7fbe9, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orn TEST #14... ");
    rs1 = 0x2282028c;
    rs2 = 0x558cfe56;
    INSTRUCTION("orn", &result, &rs1, &rs2);
    if (result != 0xaaf303ad) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orn rd, 0x2282028c, 0x558cfe56\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xaaf303ad, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("orn TEST #15... ");
    rs1 = 0x5aed2a5e;
    rs2 = 0x6f57da56;
    INSTRUCTION("orn", &result, &rs1, &rs2);
    if (result != 0xdaed2fff) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("orn rd, 0x5aed2a5e, 0x6f57da56\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xdaed2fff, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");

    printf("\n\n--------------\nMiscellaneous instructions successfully PASSED\n--------------\n\n");
}

void test_zbb()
{
    test_minmax();
    test_misc();
}

void test_zbs()
{
    uint32_t result, rs1, rs2;

    // 16x4x2 automatically generated tests
    // generated using python
    printf("bset TEST #0... ");
    rs1 = 0x5504a5dd;
    rs2 = 0x7096d20f;
    INSTRUCTION("bset", &result, &rs1, &rs2);
    if (result != 0x5504a5dd) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bset rd, 0x5504a5dd, 0x7096d20f\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x5504a5dd, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bset TEST #1... ");
    rs1 = 0xaca129eb;
    rs2 = 0xaa140462;
    INSTRUCTION("bset", &result, &rs1, &rs2);
    if (result != 0xaca129ef) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bset rd, 0xaca129eb, 0xaa140462\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xaca129ef, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bset TEST #2... ");
    rs1 = 0x9f4721be;
    rs2 = 0xa8d428d9;
    INSTRUCTION("bset", &result, &rs1, &rs2);
    if (result != 0x9f4721be) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bset rd, 0x9f4721be, 0xa8d428d9\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x9f4721be, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bset TEST #3... ");
    rs1 = 0x1dd71ec6;
    rs2 = 0x5bd520b9;
    INSTRUCTION("bset", &result, &rs1, &rs2);
    if (result != 0x1fd71ec6) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bset rd, 0x1dd71ec6, 0x5bd520b9\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1fd71ec6, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bset TEST #4... ");
    rs1 = 0x65f72336;
    rs2 = 0xbce6ce00;
    INSTRUCTION("bset", &result, &rs1, &rs2);
    if (result != 0x65f72337) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bset rd, 0x65f72336, 0xbce6ce00\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x65f72337, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bset TEST #5... ");
    rs1 = 0x65c474ad;
    rs2 = 0xd2d048bd;
    INSTRUCTION("bset", &result, &rs1, &rs2);
    if (result != 0x65c474ad) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bset rd, 0x65c474ad, 0xd2d048bd\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x65c474ad, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bset TEST #6... ");
    rs1 = 0x46c37c30;
    rs2 = 0x3012819f;
    INSTRUCTION("bset", &result, &rs1, &rs2);
    if (result != 0xc6c37c30) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bset rd, 0x46c37c30, 0x3012819f\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xc6c37c30, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bset TEST #7... ");
    rs1 = 0xd02c81c2;
    rs2 = 0x8bfaa9df;
    INSTRUCTION("bset", &result, &rs1, &rs2);
    if (result != 0xd02c81c2) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bset rd, 0xd02c81c2, 0x8bfaa9df\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xd02c81c2, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bset TEST #8... ");
    rs1 = 0x8e65551b;
    rs2 = 0x2667f9d8;
    INSTRUCTION("bset", &result, &rs1, &rs2);
    if (result != 0x8f65551b) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bset rd, 0x8e65551b, 0x2667f9d8\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x8f65551b, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bset TEST #9... ");
    rs1 = 0xc0995004;
    rs2 = 0xde7d8b00;
    INSTRUCTION("bset", &result, &rs1, &rs2);
    if (result != 0xc0995005) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bset rd, 0xc0995004, 0xde7d8b00\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xc0995005, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bset TEST #10... ");
    rs1 = 0x75204a8e;
    rs2 = 0x220dbf0;
    INSTRUCTION("bset", &result, &rs1, &rs2);
    if (result != 0x75214a8e) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bset rd, 0x75204a8e, 0x220dbf0\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x75214a8e, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bset TEST #11... ");
    rs1 = 0x13c01563;
    rs2 = 0xe9c3a19f;
    INSTRUCTION("bset", &result, &rs1, &rs2);
    if (result != 0x93c01563) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bset rd, 0x13c01563, 0xe9c3a19f\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x93c01563, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bset TEST #12... ");
    rs1 = 0xfc5cd7c7;
    rs2 = 0x51be2afc;
    INSTRUCTION("bset", &result, &rs1, &rs2);
    if (result != 0xfc5cd7c7) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bset rd, 0xfc5cd7c7, 0x51be2afc\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xfc5cd7c7, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bset TEST #13... ");
    rs1 = 0x45af7769;
    rs2 = 0x294d584;
    INSTRUCTION("bset", &result, &rs1, &rs2);
    if (result != 0x45af7779) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bset rd, 0x45af7769, 0x294d584\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x45af7779, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bset TEST #14... ");
    rs1 = 0xc8ff0c3c;
    rs2 = 0x3a2a1702;
    INSTRUCTION("bset", &result, &rs1, &rs2);
    if (result != 0xc8ff0c3c) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bset rd, 0xc8ff0c3c, 0x3a2a1702\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xc8ff0c3c, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bset TEST #15... ");
    rs1 = 0x288e8a6f;
    rs2 = 0x995961d9;
    INSTRUCTION("bset", &result, &rs1, &rs2);
    if (result != 0x2a8e8a6f) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bset rd, 0x288e8a6f, 0x995961d9\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x2a8e8a6f, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bseti TEST #0... ");
    rs1 = 0x858cbcd7;
    INSTRUCTION_IMM("bseti", &result, &rs1, "30");
    if (result != 0xc58cbcd7) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bseti rd, 0x858cbcd7, 0x1e\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xc58cbcd7, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bseti TEST #1... ");
    rs1 = 0x1fbf1050;
    INSTRUCTION_IMM("bseti", &result, &rs1, "2");
    if (result != 0x1fbf1054) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bseti rd, 0x1fbf1050, 0x2\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1fbf1054, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bseti TEST #2... ");
    rs1 = 0x42c6a14a;
    INSTRUCTION_IMM("bseti", &result, &rs1, "9");
    if (result != 0x42c6a34a) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bseti rd, 0x42c6a14a, 0x9\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x42c6a34a, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bseti TEST #3... ");
    rs1 = 0x5ae91c67;
    INSTRUCTION_IMM("bseti", &result, &rs1, "28");
    if (result != 0x5ae91c67) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bseti rd, 0x5ae91c67, 0x1c\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x5ae91c67, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bseti TEST #4... ");
    rs1 = 0x81421de7;
    INSTRUCTION_IMM("bseti", &result, &rs1, "29");
    if (result != 0xa1421de7) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bseti rd, 0x81421de7, 0x1d\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xa1421de7, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bseti TEST #5... ");
    rs1 = 0x20c0d7;
    INSTRUCTION_IMM("bseti", &result, &rs1, "22");
    if (result != 0x60c0d7) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bseti rd, 0x20c0d7, 0x16\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x60c0d7, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bseti TEST #6... ");
    rs1 = 0x1e434d0a;
    INSTRUCTION_IMM("bseti", &result, &rs1, "11");
    if (result != 0x1e434d0a) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bseti rd, 0x1e434d0a, 0xb\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1e434d0a, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bseti TEST #7... ");
    rs1 = 0x264a55ea;
    INSTRUCTION_IMM("bseti", &result, &rs1, "22");
    if (result != 0x264a55ea) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bseti rd, 0x264a55ea, 0x16\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x264a55ea, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bseti TEST #8... ");
    rs1 = 0x9d405dbf;
    INSTRUCTION_IMM("bseti", &result, &rs1, "22");
    if (result != 0x9d405dbf) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bseti rd, 0x9d405dbf, 0x16\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x9d405dbf, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bseti TEST #9... ");
    rs1 = 0x35fd6f0e;
    INSTRUCTION_IMM("bseti", &result, &rs1, "7");
    if (result != 0x35fd6f8e) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bseti rd, 0x35fd6f0e, 0x7\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x35fd6f8e, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bseti TEST #10... ");
    rs1 = 0x864465da;
    INSTRUCTION_IMM("bseti", &result, &rs1, "30");
    if (result != 0xc64465da) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bseti rd, 0x864465da, 0x1e\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xc64465da, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bseti TEST #11... ");
    rs1 = 0xc5c4bcca;
    INSTRUCTION_IMM("bseti", &result, &rs1, "24");
    if (result != 0xc5c4bcca) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bseti rd, 0xc5c4bcca, 0x18\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xc5c4bcca, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bseti TEST #12... ");
    rs1 = 0xbfedbc49;
    INSTRUCTION_IMM("bseti", &result, &rs1, "15");
    if (result != 0xbfedbc49) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bseti rd, 0xbfedbc49, 0xf\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xbfedbc49, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bseti TEST #13... ");
    rs1 = 0xc8c885e5;
    INSTRUCTION_IMM("bseti", &result, &rs1, "3");
    if (result != 0xc8c885ed) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bseti rd, 0xc8c885e5, 0x3\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xc8c885ed, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bseti TEST #14... ");
    rs1 = 0xb0bad091;
    INSTRUCTION_IMM("bseti", &result, &rs1, "27");
    if (result != 0xb8bad091) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bseti rd, 0xb0bad091, 0x1b\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xb8bad091, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bseti TEST #15... ");
    rs1 = 0xcdbd6638;
    INSTRUCTION_IMM("bseti", &result, &rs1, "22");
    if (result != 0xcdfd6638) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bseti rd, 0xcdbd6638, 0x16\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xcdfd6638, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bext TEST #0... ");
    rs1 = 0x9f0f5398;
    rs2 = 0x3c32cd2;
    INSTRUCTION("bext", &result, &rs1, &rs2);
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bext rd, 0x9f0f5398, 0x3c32cd2\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bext TEST #1... ");
    rs1 = 0xc563b144;
    rs2 = 0x6d911f9e;
    INSTRUCTION("bext", &result, &rs1, &rs2);
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bext rd, 0xc563b144, 0x6d911f9e\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bext TEST #2... ");
    rs1 = 0x1660258c;
    rs2 = 0xe1c99dd7;
    INSTRUCTION("bext", &result, &rs1, &rs2);
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bext rd, 0x1660258c, 0xe1c99dd7\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bext TEST #3... ");
    rs1 = 0x90f6760c;
    rs2 = 0x14f6e3e7;
    INSTRUCTION("bext", &result, &rs1, &rs2);
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bext rd, 0x90f6760c, 0x14f6e3e7\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bext TEST #4... ");
    rs1 = 0x64668280;
    rs2 = 0xe4010055;
    INSTRUCTION("bext", &result, &rs1, &rs2);
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bext rd, 0x64668280, 0xe4010055\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bext TEST #5... ");
    rs1 = 0x622d5892;
    rs2 = 0x49eaa6ec;
    INSTRUCTION("bext", &result, &rs1, &rs2);
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bext rd, 0x622d5892, 0x49eaa6ec\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bext TEST #6... ");
    rs1 = 0xbb8e9513;
    rs2 = 0x36e3d11e;
    INSTRUCTION("bext", &result, &rs1, &rs2);
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bext rd, 0xbb8e9513, 0x36e3d11e\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bext TEST #7... ");
    rs1 = 0xf5a04e35;
    rs2 = 0x14d00a4d;
    INSTRUCTION("bext", &result, &rs1, &rs2);
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bext rd, 0xf5a04e35, 0x14d00a4d\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bext TEST #8... ");
    rs1 = 0xe7cae8e;
    rs2 = 0x8e2ef654;
    INSTRUCTION("bext", &result, &rs1, &rs2);
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bext rd, 0xe7cae8e, 0x8e2ef654\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bext TEST #9... ");
    rs1 = 0xc1d30c0c;
    rs2 = 0x5c988896;
    INSTRUCTION("bext", &result, &rs1, &rs2);
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bext rd, 0xc1d30c0c, 0x5c988896\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bext TEST #10... ");
    rs1 = 0x689671bf;
    rs2 = 0xb0aa7112;
    INSTRUCTION("bext", &result, &rs1, &rs2);
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bext rd, 0x689671bf, 0xb0aa7112\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bext TEST #11... ");
    rs1 = 0x50f86ca8;
    rs2 = 0xcd88b583;
    INSTRUCTION("bext", &result, &rs1, &rs2);
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bext rd, 0x50f86ca8, 0xcd88b583\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bext TEST #12... ");
    rs1 = 0x6047277;
    rs2 = 0x69c28416;
    INSTRUCTION("bext", &result, &rs1, &rs2);
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bext rd, 0x6047277, 0x69c28416\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bext TEST #13... ");
    rs1 = 0xdbe14fc6;
    rs2 = 0x8fc90153;
    INSTRUCTION("bext", &result, &rs1, &rs2);
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bext rd, 0xdbe14fc6, 0x8fc90153\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bext TEST #14... ");
    rs1 = 0x8a4a4abc;
    rs2 = 0xf3bee2a3;
    INSTRUCTION("bext", &result, &rs1, &rs2);
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bext rd, 0x8a4a4abc, 0xf3bee2a3\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bext TEST #15... ");
    rs1 = 0x69659a4a;
    rs2 = 0xfd2a6956;
    INSTRUCTION("bext", &result, &rs1, &rs2);
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bext rd, 0x69659a4a, 0xfd2a6956\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bexti TEST #0... ");
    rs1 = 0x99afd688;
    INSTRUCTION_IMM("bexti", &result, &rs1, "28");
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bexti rd, 0x99afd688, 0x1c\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bexti TEST #1... ");
    rs1 = 0x419cb278;
    INSTRUCTION_IMM("bexti", &result, &rs1, "24");
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bexti rd, 0x419cb278, 0x18\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bexti TEST #2... ");
    rs1 = 0x42ef410b;
    INSTRUCTION_IMM("bexti", &result, &rs1, "9");
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bexti rd, 0x42ef410b, 0x9\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bexti TEST #3... ");
    rs1 = 0xa483fd3d;
    INSTRUCTION_IMM("bexti", &result, &rs1, "18");
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bexti rd, 0xa483fd3d, 0x12\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bexti TEST #4... ");
    rs1 = 0xc8f6550b;
    INSTRUCTION_IMM("bexti", &result, &rs1, "4");
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bexti rd, 0xc8f6550b, 0x4\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bexti TEST #5... ");
    rs1 = 0x348edf78;
    INSTRUCTION_IMM("bexti", &result, &rs1, "15");
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bexti rd, 0x348edf78, 0xf\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bexti TEST #6... ");
    rs1 = 0x412d058f;
    INSTRUCTION_IMM("bexti", &result, &rs1, "8");
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bexti rd, 0x412d058f, 0x8\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bexti TEST #7... ");
    rs1 = 0x3dc97699;
    INSTRUCTION_IMM("bexti", &result, &rs1, "26");
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bexti rd, 0x3dc97699, 0x1a\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bexti TEST #8... ");
    rs1 = 0xd9cccb7b;
    INSTRUCTION_IMM("bexti", &result, &rs1, "15");
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bexti rd, 0xd9cccb7b, 0xf\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bexti TEST #9... ");
    rs1 = 0xb15d7877;
    INSTRUCTION_IMM("bexti", &result, &rs1, "9");
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bexti rd, 0xb15d7877, 0x9\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bexti TEST #10... ");
    rs1 = 0x732bafd0;
    INSTRUCTION_IMM("bexti", &result, &rs1, "20");
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bexti rd, 0x732bafd0, 0x14\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bexti TEST #11... ");
    rs1 = 0x85812504;
    INSTRUCTION_IMM("bexti", &result, &rs1, "14");
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bexti rd, 0x85812504, 0xe\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bexti TEST #12... ");
    rs1 = 0x66e5ad68;
    INSTRUCTION_IMM("bexti", &result, &rs1, "2");
    if (result != 0x0) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bexti rd, 0x66e5ad68, 0x2\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x0, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bexti TEST #13... ");
    rs1 = 0x82260eb;
    INSTRUCTION_IMM("bexti", &result, &rs1, "3");
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bexti rd, 0x82260eb, 0x3\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bexti TEST #14... ");
    rs1 = 0x3ef73170;
    INSTRUCTION_IMM("bexti", &result, &rs1, "17");
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bexti rd, 0x3ef73170, 0x11\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bexti TEST #15... ");
    rs1 = 0x824ce140;
    INSTRUCTION_IMM("bexti", &result, &rs1, "31");
    if (result != 0x1) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bexti rd, 0x824ce140, 0x1f\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binv TEST #0... ");
    rs1 = 0x93ee3a1d;
    rs2 = 0xef75f1bf;
    INSTRUCTION("binv", &result, &rs1, &rs2);
    if (result != 0x13ee3a1d) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binv rd, 0x93ee3a1d, 0xef75f1bf\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x13ee3a1d, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binv TEST #1... ");
    rs1 = 0x2efa3840;
    rs2 = 0xa06e09eb;
    INSTRUCTION("binv", &result, &rs1, &rs2);
    if (result != 0x2efa3040) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binv rd, 0x2efa3840, 0xa06e09eb\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x2efa3040, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binv TEST #2... ");
    rs1 = 0x11bbce8a;
    rs2 = 0xa16ba4d8;
    INSTRUCTION("binv", &result, &rs1, &rs2);
    if (result != 0x10bbce8a) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binv rd, 0x11bbce8a, 0xa16ba4d8\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x10bbce8a, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binv TEST #3... ");
    rs1 = 0xfcfbb4e7;
    rs2 = 0x3f5a4a39;
    INSTRUCTION("binv", &result, &rs1, &rs2);
    if (result != 0xfefbb4e7) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binv rd, 0xfcfbb4e7, 0x3f5a4a39\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xfefbb4e7, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binv TEST #4... ");
    rs1 = 0x3e7b7147;
    rs2 = 0xec4ce03d;
    INSTRUCTION("binv", &result, &rs1, &rs2);
    if (result != 0x1e7b7147) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binv rd, 0x3e7b7147, 0xec4ce03d\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1e7b7147, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binv TEST #5... ");
    rs1 = 0xba3667c4;
    rs2 = 0xafdbe263;
    INSTRUCTION("binv", &result, &rs1, &rs2);
    if (result != 0xba3667cc) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binv rd, 0xba3667c4, 0xafdbe263\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xba3667cc, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binv TEST #6... ");
    rs1 = 0x72273c3a;
    rs2 = 0x1514622f;
    INSTRUCTION("binv", &result, &rs1, &rs2);
    if (result != 0x7227bc3a) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binv rd, 0x72273c3a, 0x1514622f\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x7227bc3a, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binv TEST #7... ");
    rs1 = 0x1921f3d5;
    rs2 = 0xf87272ab;
    INSTRUCTION("binv", &result, &rs1, &rs2);
    if (result != 0x1921fbd5) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binv rd, 0x1921f3d5, 0xf87272ab\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1921fbd5, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binv TEST #8... ");
    rs1 = 0xeebafc7f;
    rs2 = 0x43929ead;
    INSTRUCTION("binv", &result, &rs1, &rs2);
    if (result != 0xeebadc7f) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binv rd, 0xeebafc7f, 0x43929ead\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xeebadc7f, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binv TEST #9... ");
    rs1 = 0xfee04392;
    rs2 = 0x5cebe349;
    INSTRUCTION("binv", &result, &rs1, &rs2);
    if (result != 0xfee04192) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binv rd, 0xfee04392, 0x5cebe349\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xfee04192, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binv TEST #10... ");
    rs1 = 0xaf0143f9;
    rs2 = 0x5b180571;
    INSTRUCTION("binv", &result, &rs1, &rs2);
    if (result != 0xaf0343f9) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binv rd, 0xaf0143f9, 0x5b180571\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xaf0343f9, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binv TEST #11... ");
    rs1 = 0x2763522a;
    rs2 = 0xe4895fdb;
    INSTRUCTION("binv", &result, &rs1, &rs2);
    if (result != 0x2f63522a) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binv rd, 0x2763522a, 0xe4895fdb\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x2f63522a, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binv TEST #12... ");
    rs1 = 0x77828325;
    rs2 = 0xac61ecb2;
    INSTRUCTION("binv", &result, &rs1, &rs2);
    if (result != 0x77868325) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binv rd, 0x77828325, 0xac61ecb2\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x77868325, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binv TEST #13... ");
    rs1 = 0x50ae4f62;
    rs2 = 0x1dbabfc1;
    INSTRUCTION("binv", &result, &rs1, &rs2);
    if (result != 0x50ae4f60) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binv rd, 0x50ae4f62, 0x1dbabfc1\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x50ae4f60, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binv TEST #14... ");
    rs1 = 0x432b9a2e;
    rs2 = 0x8e105c55;
    INSTRUCTION("binv", &result, &rs1, &rs2);
    if (result != 0x430b9a2e) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binv rd, 0x432b9a2e, 0x8e105c55\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x430b9a2e, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binv TEST #15... ");
    rs1 = 0xa39de8df;
    rs2 = 0xca51fc06;
    INSTRUCTION("binv", &result, &rs1, &rs2);
    if (result != 0xa39de89f) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binv rd, 0xa39de8df, 0xca51fc06\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xa39de89f, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binvi TEST #0... ");
    rs1 = 0xb3ce24ad;
    INSTRUCTION_IMM("binvi", &result, &rs1, "13");
    if (result != 0xb3ce04ad) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binvi rd, 0xb3ce24ad, 0xd\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xb3ce04ad, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binvi TEST #1... ");
    rs1 = 0x35fa804a;
    INSTRUCTION_IMM("binvi", &result, &rs1, "18");
    if (result != 0x35fe804a) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binvi rd, 0x35fa804a, 0x12\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x35fe804a, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binvi TEST #2... ");
    rs1 = 0x6ab684a7;
    INSTRUCTION_IMM("binvi", &result, &rs1, "22");
    if (result != 0x6af684a7) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binvi rd, 0x6ab684a7, 0x16\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x6af684a7, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binvi TEST #3... ");
    rs1 = 0x61094e39;
    INSTRUCTION_IMM("binvi", &result, &rs1, "24");
    if (result != 0x60094e39) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binvi rd, 0x61094e39, 0x18\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x60094e39, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binvi TEST #4... ");
    rs1 = 0xb26ecfb;
    INSTRUCTION_IMM("binvi", &result, &rs1, "7");
    if (result != 0xb26ec7b) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binvi rd, 0xb26ecfb, 0x7\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xb26ec7b, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binvi TEST #5... ");
    rs1 = 0xb557fde;
    INSTRUCTION_IMM("binvi", &result, &rs1, "3");
    if (result != 0xb557fd6) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binvi rd, 0xb557fde, 0x3\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xb557fd6, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binvi TEST #6... ");
    rs1 = 0x518974e3;
    INSTRUCTION_IMM("binvi", &result, &rs1, "9");
    if (result != 0x518976e3) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binvi rd, 0x518974e3, 0x9\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x518976e3, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binvi TEST #7... ");
    rs1 = 0xb094e6ab;
    INSTRUCTION_IMM("binvi", &result, &rs1, "31");
    if (result != 0x3094e6ab) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binvi rd, 0xb094e6ab, 0x1f\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x3094e6ab, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binvi TEST #8... ");
    rs1 = 0x4066496c;
    INSTRUCTION_IMM("binvi", &result, &rs1, "1");
    if (result != 0x4066496e) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binvi rd, 0x4066496c, 0x1\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x4066496e, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binvi TEST #9... ");
    rs1 = 0xcbc20d51;
    INSTRUCTION_IMM("binvi", &result, &rs1, "17");
    if (result != 0xcbc00d51) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binvi rd, 0xcbc20d51, 0x11\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xcbc00d51, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binvi TEST #10... ");
    rs1 = 0x90e29d8c;
    INSTRUCTION_IMM("binvi", &result, &rs1, "19");
    if (result != 0x90ea9d8c) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binvi rd, 0x90e29d8c, 0x13\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x90ea9d8c, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binvi TEST #11... ");
    rs1 = 0xa7eca88d;
    INSTRUCTION_IMM("binvi", &result, &rs1, "10");
    if (result != 0xa7ecac8d) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binvi rd, 0xa7eca88d, 0xa\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xa7ecac8d, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binvi TEST #12... ");
    rs1 = 0x16a429c4;
    INSTRUCTION_IMM("binvi", &result, &rs1, "9");
    if (result != 0x16a42bc4) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binvi rd, 0x16a429c4, 0x9\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x16a42bc4, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binvi TEST #13... ");
    rs1 = 0x6e6ced36;
    INSTRUCTION_IMM("binvi", &result, &rs1, "10");
    if (result != 0x6e6ce936) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binvi rd, 0x6e6ced36, 0xa\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x6e6ce936, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binvi TEST #14... ");
    rs1 = 0x87c51cb9;
    INSTRUCTION_IMM("binvi", &result, &rs1, "12");
    if (result != 0x87c50cb9) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binvi rd, 0x87c51cb9, 0xc\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x87c50cb9, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("binvi TEST #15... ");
    rs1 = 0x90a8252a;
    INSTRUCTION_IMM("binvi", &result, &rs1, "4");
    if (result != 0x90a8253a) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("binvi rd, 0x90a8252a, 0x4\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x90a8253a, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclr TEST #0... ");
    rs1 = 0x56de29cf;
    rs2 = 0x7ed89ea6;
    INSTRUCTION("bclr", &result, &rs1, &rs2);
    if (result != 0x56de298f) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclr rd, 0x56de29cf, 0x7ed89ea6\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x56de298f, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclr TEST #1... ");
    rs1 = 0xfee01d9a;
    rs2 = 0x51a6e1be;
    INSTRUCTION("bclr", &result, &rs1, &rs2);
    if (result != 0xbee01d9a) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclr rd, 0xfee01d9a, 0x51a6e1be\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xbee01d9a, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclr TEST #2... ");
    rs1 = 0x12ea1817;
    rs2 = 0x127ef4f2;
    INSTRUCTION("bclr", &result, &rs1, &rs2);
    if (result != 0x12ea1817) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclr rd, 0x12ea1817, 0x127ef4f2\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x12ea1817, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclr TEST #3... ");
    rs1 = 0x3b889d2f;
    rs2 = 0x37657a7b;
    INSTRUCTION("bclr", &result, &rs1, &rs2);
    if (result != 0x33889d2f) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclr rd, 0x3b889d2f, 0x37657a7b\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x33889d2f, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclr TEST #4... ");
    rs1 = 0xd886937e;
    rs2 = 0xc6eff2de;
    INSTRUCTION("bclr", &result, &rs1, &rs2);
    if (result != 0x9886937e) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclr rd, 0xd886937e, 0xc6eff2de\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x9886937e, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclr TEST #5... ");
    rs1 = 0xf5acfa1a;
    rs2 = 0xd0f1c996;
    INSTRUCTION("bclr", &result, &rs1, &rs2);
    if (result != 0xf5acfa1a) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclr rd, 0xf5acfa1a, 0xd0f1c996\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xf5acfa1a, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclr TEST #6... ");
    rs1 = 0xc7c17c36;
    rs2 = 0x7bc4dc38;
    INSTRUCTION("bclr", &result, &rs1, &rs2);
    if (result != 0xc6c17c36) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclr rd, 0xc7c17c36, 0x7bc4dc38\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xc6c17c36, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclr TEST #7... ");
    rs1 = 0xd069cb4a;
    rs2 = 0x8dcaa020;
    INSTRUCTION("bclr", &result, &rs1, &rs2);
    if (result != 0xd069cb4a) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclr rd, 0xd069cb4a, 0x8dcaa020\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xd069cb4a, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclr TEST #8... ");
    rs1 = 0x6e49e5bc;
    rs2 = 0x52abcc62;
    INSTRUCTION("bclr", &result, &rs1, &rs2);
    if (result != 0x6e49e5b8) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclr rd, 0x6e49e5bc, 0x52abcc62\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x6e49e5b8, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclr TEST #9... ");
    rs1 = 0x27020f24;
    rs2 = 0xf3b57848;
    INSTRUCTION("bclr", &result, &rs1, &rs2);
    if (result != 0x27020e24) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclr rd, 0x27020f24, 0xf3b57848\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x27020e24, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclr TEST #10... ");
    rs1 = 0xd9432e00;
    rs2 = 0xd05ec44c;
    INSTRUCTION("bclr", &result, &rs1, &rs2);
    if (result != 0xd9432e00) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclr rd, 0xd9432e00, 0xd05ec44c\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xd9432e00, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclr TEST #11... ");
    rs1 = 0xed3c2dff;
    rs2 = 0xf50920c7;
    INSTRUCTION("bclr", &result, &rs1, &rs2);
    if (result != 0xed3c2d7f) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclr rd, 0xed3c2dff, 0xf50920c7\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xed3c2d7f, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclr TEST #12... ");
    rs1 = 0x34ba572b;
    rs2 = 0xcecffdca;
    INSTRUCTION("bclr", &result, &rs1, &rs2);
    if (result != 0x34ba532b) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclr rd, 0x34ba572b, 0xcecffdca\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x34ba532b, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclr TEST #13... ");
    rs1 = 0xbb3a4cf2;
    rs2 = 0xf762c72e;
    INSTRUCTION("bclr", &result, &rs1, &rs2);
    if (result != 0xbb3a0cf2) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclr rd, 0xbb3a4cf2, 0xf762c72e\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xbb3a0cf2, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclr TEST #14... ");
    rs1 = 0xee6b6f6e;
    rs2 = 0xdd91e03f;
    INSTRUCTION("bclr", &result, &rs1, &rs2);
    if (result != 0x6e6b6f6e) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclr rd, 0xee6b6f6e, 0xdd91e03f\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x6e6b6f6e, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclr TEST #15... ");
    rs1 = 0x12cb6641;
    rs2 = 0xe10c5b8e;
    INSTRUCTION("bclr", &result, &rs1, &rs2);
    if (result != 0x12cb2641) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclr rd, 0x12cb6641, 0xe10c5b8e\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x12cb2641, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclri TEST #0... ");
    rs1 = 0x3779e380;
    INSTRUCTION_IMM("bclri", &result, &rs1, "26");
    if (result != 0x3379e380) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclri rd, 0x3779e380, 0x1a\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x3379e380, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclri TEST #1... ");
    rs1 = 0xed0f6e15;
    INSTRUCTION_IMM("bclri", &result, &rs1, "0");
    if (result != 0xed0f6e14) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclri rd, 0xed0f6e15, 0x0\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xed0f6e14, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclri TEST #2... ");
    rs1 = 0x7faa723c;
    INSTRUCTION_IMM("bclri", &result, &rs1, "20");
    if (result != 0x7faa723c) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclri rd, 0x7faa723c, 0x14\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x7faa723c, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclri TEST #3... ");
    rs1 = 0xdd995314;
    INSTRUCTION_IMM("bclri", &result, &rs1, "20");
    if (result != 0xdd895314) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclri rd, 0xdd995314, 0x14\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xdd895314, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclri TEST #4... ");
    rs1 = 0x1a8da60b;
    INSTRUCTION_IMM("bclri", &result, &rs1, "13");
    if (result != 0x1a8d860b) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclri rd, 0x1a8da60b, 0xd\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x1a8d860b, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclri TEST #5... ");
    rs1 = 0x7bc064f7;
    INSTRUCTION_IMM("bclri", &result, &rs1, "17");
    if (result != 0x7bc064f7) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclri rd, 0x7bc064f7, 0x11\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x7bc064f7, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclri TEST #6... ");
    rs1 = 0xafca540f;
    INSTRUCTION_IMM("bclri", &result, &rs1, "10");
    if (result != 0xafca500f) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclri rd, 0xafca540f, 0xa\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xafca500f, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclri TEST #7... ");
    rs1 = 0xb5e18168;
    INSTRUCTION_IMM("bclri", &result, &rs1, "6");
    if (result != 0xb5e18128) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclri rd, 0xb5e18168, 0x6\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xb5e18128, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclri TEST #8... ");
    rs1 = 0x60c7b31f;
    INSTRUCTION_IMM("bclri", &result, &rs1, "17");
    if (result != 0x60c5b31f) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclri rd, 0x60c7b31f, 0x11\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x60c5b31f, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclri TEST #9... ");
    rs1 = 0xb8b5bc03;
    INSTRUCTION_IMM("bclri", &result, &rs1, "23");
    if (result != 0xb835bc03) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclri rd, 0xb8b5bc03, 0x17\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xb835bc03, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclri TEST #10... ");
    rs1 = 0x3cab0674;
    INSTRUCTION_IMM("bclri", &result, &rs1, "18");
    if (result != 0x3cab0674) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclri rd, 0x3cab0674, 0x12\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x3cab0674, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclri TEST #11... ");
    rs1 = 0x31650b6;
    INSTRUCTION_IMM("bclri", &result, &rs1, "12");
    if (result != 0x31640b6) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclri rd, 0x31650b6, 0xc\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x31640b6, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclri TEST #12... ");
    rs1 = 0xcd931fd2;
    INSTRUCTION_IMM("bclri", &result, &rs1, "28");
    if (result != 0xcd931fd2) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclri rd, 0xcd931fd2, 0x1c\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xcd931fd2, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclri TEST #13... ");
    rs1 = 0x8fdfbc8b;
    INSTRUCTION_IMM("bclri", &result, &rs1, "5");
    if (result != 0x8fdfbc8b) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclri rd, 0x8fdfbc8b, 0x5\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x8fdfbc8b, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclri TEST #14... ");
    rs1 = 0x182a3f5f;
    INSTRUCTION_IMM("bclri", &result, &rs1, "17");
    if (result != 0x18283f5f) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclri rd, 0x182a3f5f, 0x11\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0x18283f5f, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");


    printf("bclri TEST #15... ");
    rs1 = 0xf986cbba;
    INSTRUCTION_IMM("bclri", &result, &rs1, "12");
    if (result != 0xf986cbba) {
        printf("\nThe test has FAILED with the following instruction:\n");
        printf("bclri rd, 0xf986cbba, 0xc\n");
        printf("expected = 0x%x, actual = 0x%x\n", 0xf986cbba, result);
        printf("This is a critical error, exiting\n");
        return;
    }
    printf("PASSED\n");

    printf("\n\n--------------\nZbs extension successfully PASSED\n--------------\n\n");
}

int main(void)
{
    printf("Hello world!\n");
    test_zba();
    test_zbb();
    test_zbs();

    return 0;
}

