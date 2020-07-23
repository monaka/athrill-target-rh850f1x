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
#include "cpu_dec/op_dec.h"

static int OpDecode1(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code);
static int OpDecode2(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code);
static int OpDecode3(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code);
static int OpDecode4(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code);
static int OpDecode5(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code);
static int OpDecode6(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code);
static int OpDecode7(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code);
static int OpDecode8(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code);
static int OpDecode9(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code);
static int OpDecode10(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code);
static int OpDecode11(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code);
static int OpDecode12(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code);
static int OpDecode13(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code);
static int OpDecode14(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code);
static int OpDecode_f(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code);
OpDecoderType OpDecoder[OP_CODE_FORMAT_NUM] = {
	{ OpDecode1 },
	{ OpDecode2 },
	{ OpDecode3 },
	{ OpDecode4 },
	{ OpDecode5 },
	{ OpDecode6 },
	{ OpDecode7 },
	{ OpDecode8 },
	{ OpDecode9 },
	{ OpDecode10 },
	{ OpDecode11 },
	{ OpDecode12 },
	{ OpDecode13 },
	{ OpDecode14 },
	{ OpDecode_f },
};

const uint32 OpFormatSize[OP_CODE_FORMAT_NUM] = {
		2U, /* 1 */
		2U, /* 2 */
		2U, /* 3 */
		2U, /* 4 */
		4U, /* 5 */
		4U, /* 6 */
		4U, /* 7 */
		4U, /* 8 */
		4U, /* 9 */
		4U, /* 10 */
		4U, /* 11 */
		4U, /* 12 */
		4U, /* 13 */
		6U, /* 14 */
		4U, /* f */
};

static int OpDecode1(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code)
{
	decoded_code->type1.opcode = ( (code[0] >> 5) & 0x003F );
	decoded_code->type1.reg1   = ( (code[0]) & 0x001F );
	decoded_code->type1.reg2   = ( (code[0] >> 11) & 0x001F );
	return 0;
}
static int OpDecode2(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code)
{
	decoded_code->type2.opcode = ( (code[0] >> 5) & 0x003F );
	decoded_code->type2.imm    = ( (code[0]) & 0x001F );
	decoded_code->type2.reg2   = ( (code[0] >> 11) & 0x001F );
	return 0;
}

static int OpDecode3(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code)
{
	uint32 tmp1 =  ( (code[0] >> 11) & 0x001F ); /* 5bits */
	uint32 tmp2 =  ( (code[0] >>  4) & 0x0007 ); /* 3bits */

	decoded_code->type3.opcode = ( (code[0] >> 7) & 0x000F );
	decoded_code->type3.disp   = ( (tmp1 << 3) | (tmp2) );
	decoded_code->type3.cond   = ( (code[0]) & 0x000F );
	return 0;
}

static int OpDecode4(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code)
{
	/* 4_1 */
	decoded_code->type4_1.opcode = ( (code[0] >> 7)  & 0x000F );
	decoded_code->type4_1.disp   = ( (code[0] >> 1)  & 0x3F );
	decoded_code->type4_1.reg2   = ( (code[0] >> 11) & 0x001F );
	decoded_code->type4_1.gen    = ( (code[0] >>  0) & 0x0001 );

	/* 4_2 */
	decoded_code->type4_2.opcode = ( (code[0] >> 4)  & 0x007F );
	decoded_code->type4_2.disp   = ( (sint8)(code[0] >> 0)  & 0x0F );
	decoded_code->type4_2.reg2   = ( (code[0] >> 11) & 0x001F );

	return 0;
}

static int OpDecode5(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code)
{
	uint32 tmp1 = ( (code[0] >> 0) & 0x003F ); /* 6bits */;
	uint32 tmp2 = ( (code[1] >> 0) & 0xFFFF );/* 16bits */;

	decoded_code->type5.opcode = ( (code[0] >> 6)  & 0x001F );
	decoded_code->type5.reg2   = ( (code[0] >> 11) & 0x001F );
	decoded_code->type5.disp = ( (tmp1 << 16) | tmp2 );
	return 0;
}

static int OpDecode6(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code)
{
	uint32 tmp2 = ( (code[1] >> 0) & 0xFFFF );/* 16bits */;

	decoded_code->type6.opcode = ( (code[0] >> 5)  & 0x003F );
	decoded_code->type6.reg2   = ( (code[0] >> 11) & 0x001F );
	decoded_code->type6.reg1   = ( code[0] & 0x001F );
	decoded_code->type6.imm   = tmp2;

	return 0;
}

static int OpDecode7(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code)
{
	uint32 tmp2 = ( (code[1] >> 0) & 0xFFFF );/* 16bits */;

	decoded_code->type7.opcode = ( (code[0] >> 5)  & 0x003F );
	decoded_code->type7.reg2   = ( (code[0] >> 11) & 0x001F );
	decoded_code->type7.reg1   = ( code[0] & 0x001F );
	decoded_code->type7.disp   = ( (tmp2 >> 1) & 0x7FFF );
	decoded_code->type7.gen    = ( tmp2 & 0x0001 );

	return 0;
}

static int OpDecode8(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code)
{
	sint16 tmp2 = ( (code[1] >> 0) & 0xFFFF );/* 16bits */;

	decoded_code->type8.opcode = ( (code[0] >> 5)  & 0x003F );
	decoded_code->type8.sub   = ( (code[0] >> 14) & 0x0003 );
	decoded_code->type8.bit   = ( (code[0] >> 11) & 0x0007 );
	decoded_code->type8.reg1   = ( code[0] & 0x001F );
	decoded_code->type8.disp   = tmp2;

	return 0;
}

static int OpDecode9(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code)
{
	uint16 tmp1 = ( (code[0] >> 0) & 0xFFFF );/* 16bits */;
	uint16 tmp2 = ( (code[1] >> 0) & 0xFFFF );/* 16bits */;

	decoded_code->type9.opcode = ( (tmp1 >> 5)  & 0x003F );
	decoded_code->type9.reg2   = ( (tmp1 >> 11) & 0x001F );
	decoded_code->type9.gen    = ( tmp1 & 0x001F );
	decoded_code->type9.rfu1   = ( (tmp2 >>  1) & 0x000F );
	decoded_code->type9.rfu2   = ( (tmp2 >> 11) & 0x001F );
	decoded_code->type9.sub    = ( (tmp2 >>  5) & 0x003F );

	return 0;
}

static int OpDecode10(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code)
{
	uint32 tmp2 = ( (code[1] >> 0) & 0xFFFF );/* 16bits */;

	decoded_code->type10.opcode = ( (code[0] >> 5)  & 0x003F );
	decoded_code->type10.rfu1   = ( (code[0] >> 11) & 0x0003 );
	decoded_code->type10.gen1   = ( (code[0] >> 13) & 0x0007 );
	decoded_code->type10.gen2   = ( (code[0] >> 0)  & 0x001F );

	decoded_code->type10.rfu2   = ( (tmp2 >> 11) & 0x001F );
	decoded_code->type10.rfu3   = ( (tmp2 >>  1) & 0x000F );
	decoded_code->type10.sub    = ( (tmp2 >>  5) & 0x003F );

	return 0;
}

static int OpDecode11(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code)
{
	uint32 tmp2 = ( (code[1] >> 0) & 0xFFFF );/* 16bits */;

	decoded_code->type11.opcode = ( (code[0] >> 5)  & 0x003F );
	decoded_code->type11.reg2   = ( (code[0] >> 11) & 0x001F );
	decoded_code->type11.reg1   = ( (code[0] >>  0) & 0x001F );

	decoded_code->type11.rfu    = ( (tmp2 >>  2) & 0x0007 );
	decoded_code->type11.reg3   = ( (tmp2 >> 11) & 0x001F );
	decoded_code->type11.sub1   = ( (tmp2 >>  5) & 0x003F );
	decoded_code->type11.sub2   = ( (tmp2 >>  1) & 0x0001 );

	return 0;
}

static int OpDecode12(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code)
{
	uint32 tmp2 = ( (code[1] >> 0) & 0xFFFF );/* 16bits */;

	decoded_code->type12.opcode = ( (code[0] >> 5)  & 0x003F );
	decoded_code->type12.reg2   = ( (code[0] >> 11) & 0x001F );
	decoded_code->type12.imml    = ( (code[0] >>  0) & 0x001F );

	decoded_code->type12.reg3   = ( (tmp2 >> 11) & 0x001F );
	decoded_code->type12.sub1   = ( (tmp2 >>  7) & 0x000F );
	decoded_code->type12.sub2   = ( (tmp2 >>  1) & 0x0001 );
	decoded_code->type12.immh   = ( (tmp2 >>  2) & 0x001F );
	return 0;
}

static int OpDecode13(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code)
{
	uint32 tmp2 = ( (code[1] >> 0) & 0xFFFF );/* 16bits */;
	uint16 t1 = ((code[0]) & 0x0001);
	uint16 t2 = ((code[1] >> 5) & 0x07FF);
	uint32 i;

	decoded_code->type13.opcode = ( (code[0] >> 6)  & 0x001F );
	decoded_code->type13.rfu    = ( (code[0] >> 11) & 0x001F );
	decoded_code->type13.imm    = ( (code[0] >>  1) & 0x001F );

	decoded_code->type13.gen   = ( (tmp2 >> 0) & 0x001F );


	for (i = 0; i < 32; i++) {
		decoded_code->type13.list[i] = 0;
	}
	decoded_code->type13.list[30] = (t1 != 0U) ? 1U : 0U;
	decoded_code->type13.list[31] = ((t2 & 0x0001) != 0) ? 1U : 0U; /* 21 */
	decoded_code->type13.list[29] = ((t2 & 0x0002) != 0) ? 1U : 0U; /* 22 */
	decoded_code->type13.list[28] = ((t2 & 0x0004) != 0) ? 1U : 0U; /* 23 */
	decoded_code->type13.list[23] = ((t2 & 0x0008) != 0) ? 1U : 0U; /* 24 */
	decoded_code->type13.list[22] = ((t2 & 0x0010) != 0) ? 1U : 0U; /* 25 */
	decoded_code->type13.list[21] = ((t2 & 0x0020) != 0) ? 1U : 0U; /* 26 */
	decoded_code->type13.list[20] = ((t2 & 0x0040) != 0) ? 1U : 0U; /* 27 */
	decoded_code->type13.list[27] = ((t2 & 0x0080) != 0) ? 1U : 0U; /* 28 */
	decoded_code->type13.list[26] = ((t2 & 0x0100) != 0) ? 1U : 0U; /* 29 */
	decoded_code->type13.list[25] = ((t2 & 0x0200) != 0) ? 1U : 0U; /* 30 */
	decoded_code->type13.list[24] = ((t2 & 0x0400) != 0) ? 1U : 0U; /* 31 */


	return 0;
}

static int OpDecode14(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code)
{
#if 0
	typedef struct {
		uint16 sub1;	/* 15-11 */
		uint16 opcode;	/* 10-5 */
		uint16 reg1;	/* 4-0 */
		uint16 reg3;	/* 31-27 */
		uint16 disp_low;	/* 26-20 */
		uint16 sub2;	/* 19-16 */
		uint16 disp_high;	/* 47-32 */
	} OpCodeFormatType14;
#endif
	decoded_code->type14.sub1		= ( (code[0] >> 11) & 0x001F );
	decoded_code->type14.opcode		= ( (code[0] >> 5)  & 0x003F );
	decoded_code->type14.reg1		= ( (code[0] >>  0) & 0x001F );
	decoded_code->type14.reg3		= ( (code[1] >> 11) & 0x001F );
	decoded_code->type14.disp_low	= ( (code[1] >>  4) & 0x007F );
	decoded_code->type14.sub2		= ( (code[1] >>  0) & 0x000F );
	decoded_code->type14.disp_high	= code[2];

	return 0;
}

static int OpDecode_f(uint16 code[OP_DECODE_MAX], OpDecodedCodeType *decoded_code)
{
#if 0
	typedef struct {
		uint16 reg2;		/* 15-11 */
		uint16 opcode;		/* 10-5 */
		uint16 reg1;		/* 4-0 */
		uint16 reg3;		/* 31-27 */
		uint32 subopcode;	/* 26-16 */
	} OpCodeFormatType_f;
#endif
	decoded_code->type_f.reg2		= ( (code[0] >> 11) & 0x001F );
	decoded_code->type_f.opcode		= ( (code[0] >> 5)  & 0x003F );
	decoded_code->type_f.reg1		= ( (code[0] >>  0) & 0x001F );
	decoded_code->type_f.reg3		= ( (code[1] >> 11) & 0x001F );
	decoded_code->type_f.subopcode	= ( (code[1] >>  0) & 0x03FF );

	return 0;
}