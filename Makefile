#
#  Copyright 2023 Ján Mach
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#

HARDISC_DIR         := $(shell bash -c 'pwd')
HARDISC_SIM         := $(HARDISC_DIR)/sim
RANDOM              := $(shell bash -c 'echo $$RANDOM')
SV_SEED             := ${RANDOM}
SEE_PROB            := 0
SEE_GROUP           := 0
LAT                 := 0
LOGGING             := 0
HOW                 := gui
SIM_TIMEOUT         := 900000000
TIME_STAMP          :=`date +%H%M%S`
TEST_DIR            := ${HARDISC_DIR}/example/hello_world
BENCHMARK_DIR       := ${HARDISC_DIR}/example/benchmarks
BINARY              := "${HARDISC_DIR}/example/hello_world/test.bin"
LD_SCRIPT           := ${HARDISC_DIR}/example/custom/link.ld
SYSCALLS            := ${HARDISC_DIR}/example/custom/syscalls.c
STARTUP             := ${HARDISC_DIR}/example/custom/crt0.S
VECTORS             := ${HARDISC_DIR}/example/custom/vectors.S
CFLAGS              := -static -O2 -mcmodel=medany -march=rv32imc_zicsr_zba_zbb_zbs_zbc -mabi=ilp32 -nostdlib
RISCV               := /opt/riscv
COREMARK            := ~/compile/coremark

SOURCE_DIR			:= ${HARDISC_DIR}/example/hello_world
SOURCES				:= ${SOURCE_DIR}/test.c
OUTPUT				:= test

hardiscSetup:
	vsim -c -do "project new $(HARDISC_SIM) the-hardisc; project addfolder rtl; project addfolder ver; project addfolder peripherals; exit"
	@for f in $(shell ls ${HARDISC_DIR}/rtl | grep \.sv$); do vsim -c -do "project open $(HARDISC_SIM)/the-hardisc.mpf; project addfile $(HARDISC_DIR)/rtl/$${f} SystemVerilog rtl; exit"; done
	@for f in $(shell ls ${HARDISC_DIR}/ver | grep \.sv$); do vsim -c -do "project open $(HARDISC_SIM)/the-hardisc.mpf; project addfile $(HARDISC_DIR)/ver/$${f} SystemVerilog ver; exit"; done
	@for f in $(shell ls ${HARDISC_DIR}/peripherals | grep \.sv$); do vsim -c -do "project open $(HARDISC_SIM)/the-hardisc.mpf; project addfile $(HARDISC_DIR)/peripherals/$${f} SystemVerilog peripherals; exit"; done

hardiscCompile:
	vsim -c -do "project open $(HARDISC_SIM)/the-hardisc.mpf; project calculateorder; project compileall; exit"
	
hardiscSim:
	vsim -${HOW} ${HARDISC_SIM}/work.tb_mh_wrapper +TIMEOUT=${SIM_TIMEOUT} +BIN=${BINARY} +LOGGING=${LOGGING} +SEE_PROB=${SEE_PROB} +SEE_GROUP=${SEE_GROUP} +LAT=${LAT} -sv_seed ${SV_SEED} +LFILE=$(HARDISC_DIR)/hardisc_${TIME_STAMP}.log -do "do ${HARDISC_DIR}/scripts/basic_waves_mh.do; run 100ms"

compileTest:
	riscv32-unknown-elf-gcc -o ${TEST_DIR}/test.o ${TEST_DIR}/test.c ${SYSCALLS} -T ${LD_SCRIPT} ${VECTORS} ${STARTUP} ${CFLAGS} -I ${RISCV}/include -L ${RISCV}/lib -lc -lm -lgcc
	riscv32-unknown-elf-objcopy -O binary ${TEST_DIR}/test.o ${TEST_DIR}/test.bin
	riscv32-unknown-elf-objdump --disassemble ${TEST_DIR}/test.o > ${TEST_DIR}/test.txt

compileCoremark:
	riscv32-unknown-elf-gcc -o ${BENCHMARK_DIR}/coremark.o ${COREMARK}/core_list_join.c ${COREMARK}/core_main.c ${COREMARK}/core_matrix.c ${COREMARK}/core_state.c ${COREMARK}/core_util.c ${COREMARK}/simple/core_portme.c ${COREMARK}/simple/core_portme.h ${COREMARK}/coremark.h ${SYSCALLS} -T ${LD_SCRIPT} ${VECTORS} ${STARTUP} ${CFLAGS} -DHAS_STDIO=1 -DHAS_PRINTF=1 -DUSE_CLOCK=1 -DITERATIONS=1 -I ${RISCV}/include -I ${COREMARK}/simple -I ${COREMARK} -L ${RISCV}/lib -lc -lm -lgcc
	riscv32-unknown-elf-objcopy -O binary ${BENCHMARK_DIR}/coremark.o ${BENCHMARK_DIR}/coremark.bin
	riscv32-unknown-elf-objdump --disassemble ${BENCHMARK_DIR}/coremark.o > ${BENCHMARK_DIR}/coremark.txt

compile:
	riscv32-unknown-elf-gcc -o ${SOURCE_DIR}/${OUTPUT}.o ${SOURCES} ${SYSCALLS} -T ${LD_SCRIPT} ${VECTORS} ${STARTUP} ${CFLAGS} -I ${RISCV}/include -L ${RISCV}/lib -lc -lm -lgcc
	riscv32-unknown-elf-objcopy -O binary ${SOURCE_DIR}/${OUTPUT}.o ${SOURCE_DIR}/${OUTPUT}.bin
	riscv32-unknown-elf-objdump --disassemble ${SOURCE_DIR}/${OUTPUT}.o > ${SOURCE_DIR}/${OUTPUT}.txt

