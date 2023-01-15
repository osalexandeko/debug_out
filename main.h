#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

/**
 * @enum - Each index error code.
 * @brief
 * NF_20221214_DPP_ERR_CODE
 */
  typedef enum {
	ALGO_CTRL_ERROR_CODE_WRONG_BYTE_SUM = 0,
	ALGO_CTRL_ERROR_CODE_CORRECT_BYTE_SUM = 1,
	ALGO_CTRL_ERROR_CODE_MISSED_CYCLES = 2,
	ALGO_CTRL_ERROR_CODE_INVALID_CYCLES = 3,
	ALGO_CTRL_ERROR_CODE_SUCCESS_CYCLES = 4,
	ALGO_CTRL_ERROR_CODE_INVALID_DPP_CMD = 5,
	ALGO_CTRL_ERROR_CODE_NA_BFFR = 6,
	ALGO_CTRL_ERROR_CODE_UNK_ALGO = 7,
	ALGO_CTRL_ERROR_CODE_INVALID_SZ = 8,
	ALGO_CTRL_MAX_ERROR_CODE
} DPP_Error_Code_Enum;


/**
 * @struct - DPP_vrsn_ctrl_t
 * @brief - it contains versions of dpp filters, and algorithm control.
 *
 */
typedef struct {
	uint8_t mjrl_nm; //major number.
	uint8_t mnr_nm;  //minor number.
	uint8_t y;       //year.
	uint8_t m;       //month.
	uint8_t d;       //day.
	uint8_t cmd_id; //algorithm number, commonf id.
	uint8_t spr[2];// spare.
}
DPP_vrsn_id_t;


#endif
