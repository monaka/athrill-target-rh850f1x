/*
 *  TOPPERS athrill
 *     Athrill is a CPU emulator. Athrill was developed to easily
 *     execute and debug embedded programs on virtual microcomputer.
 *
 *  Copyright (C) 2019 by Center for Embedded Computing Systems
 *                          Graduate School of Informatics, Nagoya Univ., JAPAN
 *  Copyright (C) 2019 by ESM, Inc.
 *
 *
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 *
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 *
 *  $Id$
 */
#include "../cpu_exec/op_exec_ops.h"
#include "cpu.h"
#include "bus.h"


/*
 * Format8
 */
int op_exec_tst1_8(TargetCoreType *cpu)
{
	uint32 reg1 = cpu->decoded_code->type8.reg1;
	sint32 disp16 = cpu->decoded_code->type8.disp;
	sint32 bit3 = cpu->decoded_code->type8.bit;
	uint32 addr;
	uint8 bit;
	Std_ReturnType err;

	if (reg1 >= CPU_GREG_NUM) {
		return -1;
	}

	addr = cpu->reg.r[reg1] + disp16;

	err = bus_get_data8(cpu->core_id, addr, &bit);
	if (err != STD_E_OK) {
		return -1;
	}


	if ((bit & (1 << bit3)) == (1 << bit3)) {
		CPU_CLR_Z(&cpu->reg);
	}
	else {
		CPU_SET_Z(&cpu->reg);
	}

	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(), "0x%x: TST1 bit#3(%d), disp16(%d),r%d(0x%x):psw=0x%x\n", cpu->reg.pc, bit3, disp16, reg1, cpu->reg.r[reg1], sys_get_cpu_base(&cpu->reg)->r[SYS_REG_PSW]));

	cpu->reg.pc += 4;

	return 0;
}
int op_exec_set1_8(TargetCoreType *cpu)
{
	uint32 reg1 = cpu->decoded_code->type8.reg1;
	sint32 disp16 = cpu->decoded_code->type8.disp;
	sint32 bit3 = cpu->decoded_code->type8.bit;
	uint32 addr;
	uint8 org_bit;
	uint8 bit;
	Std_ReturnType err;

	if (reg1 >= CPU_GREG_NUM) {
		return -1;
	}

	addr = cpu->reg.r[reg1] + disp16;

	err = bus_get_data8(cpu->core_id, addr, &bit);
	if (err != STD_E_OK) {
		return -1;
	}


	org_bit = bit;

	bit |= (1 << bit3);
	err = bus_put_data8(cpu->core_id, addr, bit);
	if (err != STD_E_OK) {
		return -1;
	}

	if (((org_bit) & (1 << bit3)) == (1 << bit3)) {
		CPU_CLR_Z(&cpu->reg);
	}
	else {
		CPU_SET_Z(&cpu->reg);
	}

	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(), "0x%x: SET1 bit#3(%d), disp16(%d), addr=0x%x r%d(0x%x):psw=0x%x, bit=0x%x\n", cpu->reg.pc, bit3, disp16, addr, reg1, cpu->reg.r[reg1], sys_get_cpu_base(&cpu->reg)->r[SYS_REG_PSW], bit));

	cpu->reg.pc += 4;

	return 0;
}

int op_exec_clr1_8(TargetCoreType *cpu)
{
	uint32 reg1 = cpu->decoded_code->type8.reg1;
	sint32 disp16 = cpu->decoded_code->type8.disp;
	sint32 bit3 = cpu->decoded_code->type8.bit;
	uint32 addr;
	uint8 org_bit;
	uint8 bit;
	Std_ReturnType err;

	if (reg1 >= CPU_GREG_NUM) {
		return -1;
	}

	addr = cpu->reg.r[reg1] + disp16;
	err = bus_get_data8(cpu->core_id, addr, &bit);
	if (err != STD_E_OK) {
		return -1;
	}

	org_bit = bit;

	bit &= ~(1 << bit3);
	err = bus_put_data8(cpu->core_id, addr, bit);
	if (err != STD_E_OK) {
		return -1;
	}

	if (((org_bit) & (1 << bit3)) == (1 << bit3)) {
		CPU_CLR_Z(&cpu->reg);
	}
	else {
		CPU_SET_Z(&cpu->reg);
	}

	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(), "0x%x: CLR1 bit#3(%d), disp16(%d), addr=0x%x r%d(0x%x):psw=0x%x, bit=0x%x\n", cpu->reg.pc, bit3, disp16, addr, reg1, cpu->reg.r[reg1], sys_get_cpu_base(&cpu->reg)->r[SYS_REG_PSW], bit));

	cpu->reg.pc += 4;

	return 0;
}

int op_exec_not1_8(TargetCoreType *cpu)
{
	uint32 reg1 = cpu->decoded_code->type8.reg1;
	sint32 disp16 = cpu->decoded_code->type8.disp;
	sint32 bit3 = cpu->decoded_code->type8.bit;
	uint32 addr;
	uint8 org_bit;
	uint8 bit;
	Std_ReturnType err;

	if (reg1 >= CPU_GREG_NUM) {
		return -1;
	}

	addr = cpu->reg.r[reg1] + disp16;
	err = bus_get_data8(cpu->core_id, addr, &bit);
	if (err != STD_E_OK) {
		return -1;
	}

	org_bit = bit;


	if (((org_bit) & (1 << bit3)) == (1 << bit3)) {
		CPU_CLR_Z(&cpu->reg);
		bit &= ~(1 << bit3);
	}
	else {
		CPU_SET_Z(&cpu->reg);
		bit |= (1 << bit3);
	}
	err = bus_put_data8(cpu->core_id, addr, bit);
	if (err != STD_E_OK) {
		return -1;
	}

	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
			"0x%x: NOT1 bit#3(%d), disp16(%d), addr=0x%x r%d(0x%x):psw=0x%x, bit=0x%x\n",
			cpu->reg.pc, bit3, disp16, addr, reg1, cpu->reg.r[reg1], sys_get_cpu_base(&cpu->reg)->r[SYS_REG_PSW], bit));

	cpu->reg.pc += 4;

	return 0;
}


/*
 * Format9
 */
int op_exec_set1_9(TargetCoreType *cpu)
{
	uint32 reg1 = cpu->decoded_code->type9.gen;
	sint32 reg2 = cpu->decoded_code->type9.reg2;
	uint32 addr;
	uint8 org_bit;
	uint8 bit3;
	uint8 bit;
	Std_ReturnType err;

	if (reg1 >= CPU_GREG_NUM) {
		return -1;
	}
	if (reg2 >= CPU_GREG_NUM) {
		return -1;
	}
	/*
	 * （ 2） adr ← GR [reg1]
	 * Zフラグ ← Not (Load-memory-bit (adr, reg2) )
	 * Store-memory-bit (adr, reg2, 1)
	 */

	addr = cpu->reg.r[reg1];
	err = bus_get_data8(cpu->core_id, addr, &bit);
	if (err != STD_E_OK) {
		return -1;
	}

	org_bit = bit;

	bit3 = (cpu->reg.r[reg2] & 0x07);
	bit |= (1 << bit3);
	err = bus_put_data8(cpu->core_id, addr, bit);
	if (err != STD_E_OK) {
		return -1;
	}

	if (((org_bit) & (1 << bit3)) == (1 << bit3)) {
		CPU_CLR_Z(&cpu->reg);
	}
	else {
		CPU_SET_Z(&cpu->reg);
	}

	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
			"0x%x: SET1 bit#3(%d), addr=0x%x r%d(0x%x) r%d(0x%x):psw=0x%x, bit=0x%x\n",
			cpu->reg.pc,
			bit3, addr, reg1, cpu->reg.r[reg1], reg2, cpu->reg.r[reg2],sys_get_cpu_base(&cpu->reg)->r[SYS_REG_PSW], bit));

	cpu->reg.pc += 4;

	return 0;
}
int op_exec_clr1_9(TargetCoreType *cpu)
{
	uint32 reg1 = cpu->decoded_code->type9.gen;
	sint32 reg2 = cpu->decoded_code->type9.reg2;
	uint32 addr;
	uint8 bit;
	Std_ReturnType err;
	uint8 org_bit;
	uint8 bit3;

	if (reg1 >= CPU_GREG_NUM) {
		return -1;
	}
	if (reg2 >= CPU_GREG_NUM) {
		return -1;
	}
	/*
	 * （ 2） adr ← GR [reg1]
	 * Zフラグ ← Not (Load-memory-bit (adr, reg2) )
	 * Store-memory-bit (adr, reg2, 0)
	 */

	addr = cpu->reg.r[reg1];
	err = bus_get_data8(cpu->core_id, addr, &bit);
	if (err != STD_E_OK) {
		return -1;
	}
	org_bit = bit;

	bit3 = (cpu->reg.r[reg2] & 0x07);
	bit &= ~(1 << bit3);
	err = bus_put_data8(cpu->core_id, addr, bit);
	if (err != STD_E_OK) {
		return -1;
	}
	if (((org_bit) & (1 << bit3)) == (1 << bit3)) {
		CPU_CLR_Z(&cpu->reg);
	}
	else {
		CPU_SET_Z(&cpu->reg);
	}

	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
			"0x%x: CLR1 bit#3(%d), addr=0x%x r%d(0x%x) r%d(0x%x):psw=0x%x, bit=0x%x\n",
			cpu->reg.pc,
			bit3, addr, reg1, cpu->reg.r[reg1], reg2, cpu->reg.r[reg2],sys_get_cpu_base(&cpu->reg)->r[SYS_REG_PSW], bit));

	cpu->reg.pc += 4;

	return 0;
}

int op_exec_tst1_9(TargetCoreType *cpu)
{
	uint32 reg1 = cpu->decoded_code->type9.gen;
	sint32 reg2 = cpu->decoded_code->type9.reg2;
	uint32 addr;
	Std_ReturnType err;
	uint8 bit3;
	uint8 bit;


	if (reg1 >= CPU_GREG_NUM) {
		return -1;
	}
	if (reg2 >= CPU_GREG_NUM) {
		return -1;
	}
	addr = cpu->reg.r[reg1];

	err = bus_get_data8(cpu->core_id, addr, &bit);
	if (err != STD_E_OK) {
		return -1;
	}

	bit3 = (cpu->reg.r[reg2] & 0x07);

	if ((bit & (1 << bit3)) == (1 << bit3)) {
		CPU_CLR_Z(&cpu->reg);
	}
	else {
		CPU_SET_Z(&cpu->reg);
	}

	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
			"0x%x: TST1 bit#3(%d), r%d(0x%x),r%d(0x%x):psw=0x%x\n",
			cpu->reg.pc, bit3, reg1, cpu->reg.r[reg1], reg2, cpu->reg.r[reg2], sys_get_cpu_base(&cpu->reg)->r[SYS_REG_PSW]));

	cpu->reg.pc += 4;

	return 0;
}
int op_exec_not1_9(TargetCoreType *cpu)
{
	uint32 reg1 = cpu->decoded_code->type9.gen;
	sint32 reg2 = cpu->decoded_code->type9.reg2;
	uint32 addr;
	Std_ReturnType err;
	uint8 bit;
	uint8 org_bit;
	uint8 bit3;

	if (reg1 >= CPU_GREG_NUM) {
		return -1;
	}
	if (reg2 >= CPU_GREG_NUM) {
		return -1;
	}
	/*
	 * （ 2） adr ← GR [reg1]
	 * Zフラグ ← Not (Load-memory-bit (adr, reg2) )
	 * Store-memory-bit (adr, reg2, Zフラグ)
	 */
	addr = cpu->reg.r[reg1];
	err = bus_get_data8(cpu->core_id, addr, &bit);
	if (err != STD_E_OK) {
		return -1;
	}

	org_bit = bit;

	bit3 = (cpu->reg.r[reg2] & 0x07);

	if (((org_bit) & (1 << bit3)) == (1 << bit3)) {
		CPU_CLR_Z(&cpu->reg);
		bit &= ~(1 << bit3);
	}
	else {
		CPU_SET_Z(&cpu->reg);
		bit |= (1 << bit3);
	}
	err = bus_put_data8(cpu->core_id, addr, bit);
	if (err != STD_E_OK) {
		return -1;
	}

	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
			"0x%x: NOT1 bit#3(%d), addr=0x%x r%d(0x%x) r%d(0x%x):psw=0x%x, bit=0x%x\n",
			cpu->reg.pc,
			bit3, addr, reg1, cpu->reg.r[reg1], reg2, cpu->reg.r[reg2],sys_get_cpu_base(&cpu->reg)->r[SYS_REG_PSW], bit));

	cpu->reg.pc += 4;

	return 0;
}

static int op_exec_schlr_9(TargetCoreType *cpu, uint32 search_bitval, bool search_left)
{
	sint32 reg2 = cpu->decoded_code->type9.reg2;
	sint32 reg3 = cpu->decoded_code->type9.rfu2;
	uint32 reg2_data = cpu->reg.r[reg2];
	uint32 i;
	uint32 count = 0;
	bool isFound = FALSE;
	uint32 result;
	char *dir = NULL;

	if (search_left == TRUE) {
		dir = "L";
		for (i = 0; i < 32; i++) {
			if ((reg2_data & (1U << (31 - i))) == search_bitval) {
				isFound = TRUE;
				break;
			}
			else {
				count++;
			}
		}
	}
	else {
		dir = "R";
		for (i = 0; i < 32; i++) {
			if ((reg2_data & (1U << (i))) == search_bitval) {
				isFound = TRUE;
				break;
			}
			else {
				count++;
			}
		}
		DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
				"0x%x: SCH%dR r%d(0x%x) r%d(0x%x):%u\n",
				cpu->reg.pc,
				search_bitval,
				reg3, cpu->reg.r[reg2], reg3, cpu->reg.r[reg3],
				count + 1));
	}

	//CY 最後にビット（search_bitval）が見つかったとき 1，そうでないとき 0
	if (count == 31) {
		CPU_SET_CY(&cpu->reg);
	}
	else {
		CPU_SET_CY(&cpu->reg);
	}

	CPU_CLR_OV(&cpu->reg);
	CPU_CLR_S(&cpu->reg);

	//ビット（search_bitval）が見つからなかったとき 1，そうでないとき 0
	if (isFound == FALSE) {
		CPU_SET_Z(&cpu->reg);
		result = 0;
	}
	else {
		CPU_CLR_Z(&cpu->reg);
		result = count + 1;
	}
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
			"0x%x: SCH%d%s r%d(0x%x) r%d(0x%x):psw=0x%x, %u\n",
			cpu->reg.pc,
			search_bitval,
			dir,
			reg2, cpu->reg.r[reg2], reg3, cpu->reg.r[reg3],
			sys_get_cpu_base(&cpu->reg)->r[SYS_REG_PSW], result));

	cpu->reg.r[reg3] = result;
	cpu->reg.pc += 4;

	return 0;
}

/*
 * Format9
 */
int op_exec_sch0l_9(TargetCoreType *cpu)
{
	return op_exec_schlr_9(cpu, 0, TRUE);
}
int op_exec_sch1l_9(TargetCoreType *cpu)
{
	return op_exec_schlr_9(cpu, 1, TRUE);
}
int op_exec_sch0r_9(TargetCoreType *cpu)
{
	return op_exec_schlr_9(cpu, 0, FALSE);
}
int op_exec_sch1r_9(TargetCoreType *cpu)
{
	return op_exec_schlr_9(cpu, 1, FALSE);
}
