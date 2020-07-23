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
#include "cpu_exec/op_exec.h"

OpExecType op_exec_table[OP_EXEC_TABLE_NUM] = {
	{ 7, op_exec_absf_s_F },		/* OpCodeId_ABSF_S_F */
	{ 1, op_exec_add_1 },		/* OpCodeId_ADD_1 */
	{ 1, op_exec_add_2 },		/* OpCodeId_ADD_2 */
	{ 7, op_exec_addf_s_F },		/* OpCodeId_ADDF_S_F */
	{ 1, op_exec_addi_6 },		/* OpCodeId_ADDI_6 */
	{ 1, op_exec_adf_11 },		/* OpCodeId_ADF_11 */
	{ 1, op_exec_and_1 },		/* OpCodeId_AND_1 */
	{ 1, op_exec_andi_6 },		/* OpCodeId_ANDI_6 */
	{ 1, op_exec_bins_9 },		/* OpCodeId_BINS_9 */
	{ 1, op_exec_bsh_12 },		/* OpCodeId_BSH_12 */
	{ 1, op_exec_bsw_12 },		/* OpCodeId_BSW_12 */
	{ 4, op_exec_bcond_3 },		/* OpCodeId_Bcond_3 */
	{ 4, op_exec_bcond_7 },		/* OpCodeId_Bcond_7 */
	{ 10, op_exec_callt_2 },		/* OpCodeId_CALLT_2 */
	{ 4, op_exec_caxi_11 },		/* OpCodeId_CAXI_11 */
	{ 7, op_exec_ceilf_sl_F },		/* OpCodeId_CEILF_SL_F */
	{ 7, op_exec_ceilf_sul_F },		/* OpCodeId_CEILF_SUL_F */
	{ 7, op_exec_ceilf_suw_F },		/* OpCodeId_CEILF_SUW_F */
	{ 7, op_exec_ceilf_sw_F },		/* OpCodeId_CEILF_SW_F */
	{ 4, op_exec_clr1_8 },		/* OpCodeId_CLR1_8 */
	{ 4, op_exec_clr1_9 },		/* OpCodeId_CLR1_9 */
	{ 1, op_exec_cmov_12 },		/* OpCodeId_CMOV_12 */
	{ 1, op_exec_cmov_11 },		/* OpCodeId_CMOV_11 */
	{ 7, op_exec_cmovf_s_F },		/* OpCodeId_CMOVF_S_F */
	{ 1, op_exec_cmp_1 },		/* OpCodeId_CMP_1 */
	{ 1, op_exec_cmp_2 },		/* OpCodeId_CMP_2 */
	{ 7, op_exec_cmpf_s_F },		/* OpCodeId_CMPF_S_F */
	{ 7, op_exec_ctret_10 },		/* OpCodeId_CTRET_10 */
	{ 7, op_exec_cvtf_ds_F },		/* OpCodeId_CVTF_DS_F */
	{ 7, op_exec_cvtf_hs_F },		/* OpCodeId_CVTF_HS_F */
	{ 7, op_exec_cvtf_ls_F },		/* OpCodeId_CVTF_LS_F */
	{ 7, op_exec_cvtf_sd_F },		/* OpCodeId_CVTF_SD_F */
	{ 7, op_exec_cvtf_sh_F },		/* OpCodeId_CVTF_SH_F */
	{ 7, op_exec_cvtf_sl_F },		/* OpCodeId_CVTF_SL_F */
	{ 7, op_exec_cvtf_sul_F },		/* OpCodeId_CVTF_SUL_F */
	{ 7, op_exec_cvtf_suw_F },		/* OpCodeId_CVTF_SUW_F */
	{ 7, op_exec_cvtf_sw_F },		/* OpCodeId_CVTF_SW_F */
	{ 7, op_exec_cvtf_uls_F },		/* OpCodeId_CVTF_ULS_F */
	{ 7, op_exec_cvtf_uws_F },		/* OpCodeId_CVTF_UWS_F */
	{ 7, op_exec_cvtf_ws_F },		/* OpCodeId_CVTF_WS_F */
	{ 3, op_exec_dbtrap_1 },		/* OpCodeId_DBTRAP_1 */
	{ 3, op_exec_di_10 },		/* OpCodeId_DI_10 */
	{ 2, op_exec_dispose_13 },		/* OpCodeId_DISPOSE_13 */
	{ 19, op_exec_div_11 },		/* OpCodeId_DIV_11 */
	{ 20, op_exec_divf_s_F },		/* OpCodeId_DIVF_S_F */
	{ 36, op_exec_divh_1 },		/* OpCodeId_DIVH_1 */
	{ 19, op_exec_divh_11 },		/* OpCodeId_DIVH_11 */
	{ 19, op_exec_divhu_11 },		/* OpCodeId_DIVHU_11 */
	{ 19, op_exec_divq_11 },		/* OpCodeId_DIVQ_11 */
	{ 19, op_exec_divqu_11 },		/* OpCodeId_DIVQU_11 */
	{ 19, op_exec_divu_11 },		/* OpCodeId_DIVU_11 */
	{ 3, op_exec_ei_10 },		/* OpCodeId_EI_10 */
	{ 7, op_exec_eiret_10 },		/* OpCodeId_EIRET_10 */
	{ 7, op_exec_feret_10 },		/* OpCodeId_FERET_10 */
	{ 7, op_exec_fetrap_1 },		/* OpCodeId_FETRAP_1 */
	{ 7, op_exec_floorf_sl_F },		/* OpCodeId_FLOORF_SL_F */
	{ 7, op_exec_floorf_sul_F },		/* OpCodeId_FLOORF_SUL_F */
	{ 7, op_exec_floorf_suw_F },		/* OpCodeId_FLOORF_SUW_F */
	{ 7, op_exec_floorf_sw_F },		/* OpCodeId_FLOORF_SW_F */
	{ 7, op_exec_fmaf_s_F },		/* OpCodeId_FMAF_S_F */
	{ 7, op_exec_fmsf_s_F },		/* OpCodeId_FMSF_S_F */
	{ 7, op_exec_fnmaf_s_F },		/* OpCodeId_FNMAF_S_F */
	{ 7, op_exec_fnmsf_s_F },		/* OpCodeId_FNMSF_S_F */
	{ 1, op_exec_halt_10 },		/* OpCodeId_HALT_10 */
	{ 1, op_exec_hsh_12 },		/* OpCodeId_HSH_12 */
	{ 1, op_exec_hsw_12 },		/* OpCodeId_HSW_12 */
	{ 4, op_exec_jarl_6 },		/* OpCodeId_JARL_6 */
	{ 4, op_exec_jarl_5 },		/* OpCodeId_JARL_5 */
	{ 3, op_exec_jarl_11 },		/* OpCodeId_JARL_11 */
	{ 4, op_exec_jmp_1 },		/* OpCodeId_JMP_1 */
	{ 5, op_exec_jmp_6 },		/* OpCodeId_JMP_6 */
	{ 4, op_exec_jr_6 },		/* OpCodeId_JR_6 */
	{ 4, op_exec_jr_5 },		/* OpCodeId_JR_5 */
	{ 2, op_exec_ldl_w_7 },		/* OpCodeId_LDL_W_7 */
	{ 3, op_exec_ldsr_9 },		/* OpCodeId_LDSR_9 */
	{ 3, op_exec_ld_b_7 },		/* OpCodeId_LD_B_7 */
	{ 3, op_exec_ld_b_14 },		/* OpCodeId_LD_B_14 */
	{ 3, op_exec_ld_bu_7 },		/* OpCodeId_LD_BU_7 */
	{ 3, op_exec_ld_bu_14 },		/* OpCodeId_LD_BU_14 */
	{ 3, op_exec_ld_dw_14 },		/* OpCodeId_LD_DW_14 */
	{ 3, op_exec_ld_h_7 },		/* OpCodeId_LD_H_7 */
	{ 3, op_exec_ld_h_14 },		/* OpCodeId_LD_H_14 */
	{ 3, op_exec_ld_hu_14 },		/* OpCodeId_LD_HU_14 */
	{ 3, op_exec_ld_hu_7 },		/* OpCodeId_LD_HU_7 */
	{ 3, op_exec_ld_w_7 },		/* OpCodeId_LD_W_7 */
	{ 3, op_exec_ld_w_14 },		/* OpCodeId_LD_W_14 */
	{ 4, op_exec_loop_7 },		/* OpCodeId_LOOP_7 */
	{ 3, op_exec_mac_11 },		/* OpCodeId_MAC_11 */
	{ 3, op_exec_macu_11 },		/* OpCodeId_MACU_11 */
	{ 7, op_exec_maxf_s_F },		/* OpCodeId_MAXF_S_F */
	{ 7, op_exec_minf_s_F },		/* OpCodeId_MINF_S_F */
	{ 1, op_exec_mov_1 },		/* OpCodeId_MOV_1 */
	{ 1, op_exec_mov_2 },		/* OpCodeId_MOV_2 */
	{ 1, op_exec_mov_6 },		/* OpCodeId_MOV_6 */
	{ 1, op_exec_movea_6 },		/* OpCodeId_MOVEA_6 */
	{ 1, op_exec_movhi_6 },		/* OpCodeId_MOVHI_6 */
	{ 3, op_exec_mul_11 },		/* OpCodeId_MUL_11 */
	{ 3, op_exec_mul_12 },		/* OpCodeId_MUL_12 */
	{ 8, op_exec_mulf_d_F },		/* OpCodeId_MULF_D_F */
	{ 7, op_exec_mulf_s_F },		/* OpCodeId_MULF_S_F */
	{ 3, op_exec_mulh_1 },		/* OpCodeId_MULH_1 */
	{ 3, op_exec_mulh_2 },		/* OpCodeId_MULH_2 */
	{ 3, op_exec_mulhi_6 },		/* OpCodeId_MULHI_6 */
	{ 3, op_exec_mulu_11 },		/* OpCodeId_MULU_11 */
	{ 3, op_exec_mulu_12 },		/* OpCodeId_MULU_12 */
	{ 7, op_exec_negf_s_F },		/* OpCodeId_NEGF_S_F */
	{ 1, op_exec_nop_1 },		/* OpCodeId_NOP_1 */
	{ 1, op_exec_not_1 },		/* OpCodeId_NOT_1 */
	{ 4, op_exec_not1_8 },		/* OpCodeId_NOT1_8 */
	{ 4, op_exec_not1_9 },		/* OpCodeId_NOT1_9 */
	{ 1, op_exec_or_1 },		/* OpCodeId_OR_1 */
	{ 1, op_exec_ori_6 },		/* OpCodeId_ORI_6 */
	{ 2, op_exec_popsp_11 },		/* OpCodeId_POPSP_11 */
	{ 2, op_exec_prepare_13 },		/* OpCodeId_PREPARE_13 */
	{ 2, op_exec_pushsp_11 },		/* OpCodeId_PUSHSP_11 */
	{ 16, op_exec_recipf_s_F },		/* OpCodeId_RECIPF_S_F */
	{ 7, op_exec_reti_10 },		/* OpCodeId_RETI_10 */
	{ 7, op_exec_rie_1 },		/* OpCodeId_RIE_1 */
	{ 7, op_exec_rie_10 },		/* OpCodeId_RIE_10 */
	{ 1, op_exec_rotl_7 },		/* OpCodeId_ROTL_7 */
	{ 7, op_exec_roundf_sl_F },		/* OpCodeId_ROUNDF_SL_F */
	{ 7, op_exec_roundf_sul_F },		/* OpCodeId_ROUNDF_SUL_F */
	{ 7, op_exec_roundf_suw_F },		/* OpCodeId_ROUNDF_SUW_F */
	{ 7, op_exec_roundf_sw_F },		/* OpCodeId_ROUNDF_SW_F */
	{ 20, op_exec_rsqrtf_s_F },		/* OpCodeId_RSQRTF_S_F */
	{ 1, op_exec_sar_2 },		/* OpCodeId_SAR_2 */
	{ 1, op_exec_sar_9 },		/* OpCodeId_SAR_9 */
	{ 1, op_exec_sar_11 },		/* OpCodeId_SAR_11 */
	{ 1, op_exec_sasf_9 },		/* OpCodeId_SASF_9 */
	{ 1, op_exec_satadd_1 },		/* OpCodeId_SATADD_1 */
	{ 1, op_exec_satadd_2 },		/* OpCodeId_SATADD_2 */
	{ 1, op_exec_satadd_11 },		/* OpCodeId_SATADD_11 */
	{ 1, op_exec_satsub_1 },		/* OpCodeId_SATSUB_1 */
	{ 1, op_exec_satsub_11 },		/* OpCodeId_SATSUB_11 */
	{ 1, op_exec_satsubi_6 },		/* OpCodeId_SATSUBI_6 */
	{ 1, op_exec_satsubr_1 },		/* OpCodeId_SATSUBR_1 */
	{ 1, op_exec_sbf_11 },		/* OpCodeId_SBF_11 */
	{ 1, op_exec_sch0l_9 },		/* OpCodeId_SCH0L_9 */
	{ 1, op_exec_sch0r_9 },		/* OpCodeId_SCH0R_9 */
	{ 1, op_exec_sch1l_9 },		/* OpCodeId_SCH1L_9 */
	{ 1, op_exec_sch1r_9 },		/* OpCodeId_SCH1R_9 */
	{ 4, op_exec_set1_8 },		/* OpCodeId_SET1_8 */
	{ 4, op_exec_set1_9 },		/* OpCodeId_SET1_9 */
	{ 1, op_exec_setf_9 },		/* OpCodeId_SETF_9 */
	{ 1, op_exec_shl_2 },		/* OpCodeId_SHL_2 */
	{ 1, op_exec_shl_9 },		/* OpCodeId_SHL_9 */
	{ 1, op_exec_shl_11 },		/* OpCodeId_SHL_11 */
	{ 1, op_exec_shr_2 },		/* OpCodeId_SHR_2 */
	{ 1, op_exec_shr_9 },		/* OpCodeId_SHR_9 */
	{ 1, op_exec_shr_11 },		/* OpCodeId_SHR_11 */
	{ 3, op_exec_sld_b_4 },		/* OpCodeId_SLD_B_4 */
	{ 3, op_exec_sld_bu_4 },		/* OpCodeId_SLD_BU_4 */
	{ 3, op_exec_sld_h_4 },		/* OpCodeId_SLD_H_4 */
	{ 3, op_exec_sld_hu_4 },		/* OpCodeId_SLD_HU_4 */
	{ 3, op_exec_sld_w_4 },		/* OpCodeId_SLD_W_4 */
	{ 10, op_exec_snooze_10 },		/* OpCodeId_SNOOZE_10 */
	{ 20, op_exec_sqrtf_s_F },		/* OpCodeId_SQRTF_S_F */
	{ 1, op_exec_sst_b_4 },		/* OpCodeId_SST_B_4 */
	{ 1, op_exec_sst_h_4 },		/* OpCodeId_SST_H_4 */
	{ 1, op_exec_sst_w_4 },		/* OpCodeId_SST_W_4 */
	{ 2, op_exec_stc_w_7 },		/* OpCodeId_STC_W_7 */
	{ 1, op_exec_stsr_9 },		/* OpCodeId_STSR_9 */
	{ 1, op_exec_st_b_7 },		/* OpCodeId_ST_B_7 */
	{ 1, op_exec_st_b_14 },		/* OpCodeId_ST_B_14 */
	{ 1, op_exec_st_dw_14 },		/* OpCodeId_ST_DW_14 */
	{ 1, op_exec_st_h_7 },		/* OpCodeId_ST_H_7 */
	{ 1, op_exec_st_h_14 },		/* OpCodeId_ST_H_14 */
	{ 1, op_exec_st_w_7 },		/* OpCodeId_ST_W_7 */
	{ 1, op_exec_st_w_14 },		/* OpCodeId_ST_W_14 */
	{ 1, op_exec_sub_1 },		/* OpCodeId_SUB_1 */
	{ 7, op_exec_subf_s_F },		/* OpCodeId_SUBF_S_F */
	{ 1, op_exec_subr_1 },		/* OpCodeId_SUBR_1 */
	{ 8, op_exec_switch_1 },		/* OpCodeId_SWITCH_1 */
	{ 1, op_exec_sxb_1 },		/* OpCodeId_SXB_1 */
	{ 1, op_exec_sxh_1 },		/* OpCodeId_SXH_1 */
	{ 10, op_exec_synce_1 },		/* OpCodeId_SYNCE_1 */
	{ 10, op_exec_synci_1 },		/* OpCodeId_SYNCI_1 */
	{ 10, op_exec_syncm_1 },		/* OpCodeId_SYNCM_1 */
	{ 10, op_exec_syncp_1 },		/* OpCodeId_SYNCP_1 */
	{ 10, op_exec_syscall_10 },		/* OpCodeId_SYSCALL_10 */
	{ 7, op_exec_trap_10 },		/* OpCodeId_TRAP_10 */
	{ 1, op_exec_trfsr_F },		/* OpCodeId_TRFSR_F */
	{ 7, op_exec_trncf_sl_F },		/* OpCodeId_TRNCF_SL_F */
	{ 7, op_exec_trncf_sul_F },		/* OpCodeId_TRNCF_SUL_F */
	{ 7, op_exec_trncf_suw_F },		/* OpCodeId_TRNCF_SUW_F */
	{ 7, op_exec_trncf_sw_F },		/* OpCodeId_TRNCF_SW_F */
	{ 1, op_exec_tst_1 },		/* OpCodeId_TST_1 */
	{ 4, op_exec_tst1_8 },		/* OpCodeId_TST1_8 */
	{ 4, op_exec_tst1_9 },		/* OpCodeId_TST1_9 */
	{ 1, op_exec_xor_1 },		/* OpCodeId_XOR_1 */
	{ 1, op_exec_xori_6 },		/* OpCodeId_XORI_6 */
	{ 1, op_exec_zxb_1 },		/* OpCodeId_ZXB_1 */
	{ 1, op_exec_zxh_1 },		/* OpCodeId_ZXH_1 */
};

