/*!
    \file    main.c
    \brief   PKCAU modular addition

    \version 2024-12-27, V1.2.0, demo for GD32F5xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32f5xx.h"
#include "systick.h"
#include <string.h>
#include "gd32f527i_eval.h"

#define MA_A_SIZE   (128)
#define MA_B_SIZE   (128)
#define MA_MOD_SIZE (128)
#define MA_RES_SIZE (128)

extern volatile uint8_t end_flag;

/* operand A */
uint8_t oprd_a[MA_A_SIZE]         = {0xc0, 0x22, 0xc6, 0x72, 0xe2, 0x51, 0xde, 0x2e, 0x4c, 0xf6, 0x54, 0xf2, 0x02, 0x08, 0xaa, 0x73,
                                     0x4b, 0x1c, 0x4c, 0x09, 0x9b, 0x38, 0xf4, 0x03, 0x21, 0x9e, 0xd0, 0x96, 0xb3, 0x4a, 0xac, 0xbf,
                                     0x1b, 0x8b, 0x7d, 0xc3, 0x2e, 0xe1, 0xe4, 0x7a, 0xb8, 0x33, 0x2f, 0x9b, 0x94, 0x10, 0x5f, 0x42,
                                     0xf8, 0xe8, 0xbd, 0xd5, 0xe8, 0x0a, 0x7d, 0x0d, 0x50, 0xc9, 0xb2, 0x51, 0xe5, 0x01, 0x8a, 0x41,
                                     0xb9, 0xa6, 0xc6, 0x12, 0x10, 0x1e, 0x5a, 0xfd, 0x48, 0x41, 0x18, 0x58, 0x5a, 0x5b, 0x6d, 0x1f,
                                     0x40, 0xae, 0xab, 0xbe, 0x32, 0x66, 0x80, 0xfb, 0xa4, 0x56, 0xb6, 0xf8, 0x0a, 0xd2, 0x3a, 0x0a,
                                     0x9c, 0x3d, 0x3e, 0x2b, 0xda, 0x62, 0x81, 0x91, 0x82, 0x5d, 0xb1, 0x4b, 0xc1, 0x8e, 0x0b, 0x3e,
                                     0x0b, 0xaf, 0xf5, 0xb9, 0x2f, 0x41, 0x5d, 0x6c, 0x08, 0x4a, 0x9c, 0x83, 0xef, 0x8b, 0xd9, 0xcf
                                    };
/* operand B */
uint8_t oprd_b[MA_B_SIZE]         = {0xd4, 0x4a, 0x19, 0x14, 0xbe, 0x8c, 0x31, 0x39, 0x8f, 0xd0, 0x53, 0xe5, 0x96, 0x0c, 0xcd, 0x0f,
                                     0x16, 0x8c, 0x60, 0xb8, 0xe8, 0x4b, 0x29, 0xc1, 0x4e, 0x0a, 0xa7, 0x8e, 0xb8, 0x75, 0x56, 0xcd,
                                     0xd2, 0x0f, 0x9b, 0x0a, 0x60, 0x01, 0xa9, 0x99, 0x90, 0x57, 0x11, 0xa4, 0x6e, 0x40, 0x7d, 0xc7,
                                     0x92, 0x16, 0x99, 0x97, 0x1b, 0x26, 0xd6, 0x78, 0x00, 0xac, 0x17, 0x5e, 0xa2, 0x4b, 0xbd, 0x81,
                                     0x2c, 0xaf, 0x8a, 0x2c, 0x3e, 0xb1, 0xc3, 0x75, 0x08, 0xa1, 0x20, 0xa5, 0x5a, 0x6f, 0xbf, 0xaf,
                                     0x61, 0x1a, 0xf7, 0x3b, 0x04, 0xf7, 0x88, 0xc9, 0x1b, 0x0a, 0x83, 0xf2, 0x10, 0xed, 0x57, 0xc9,
                                     0xd5, 0xf0, 0x08, 0x86, 0x8b, 0x48, 0x9b, 0x0c, 0x67, 0x22, 0x7d, 0x53, 0x16, 0xe7, 0x89, 0xc8,
                                     0x5e, 0xfc, 0x39, 0x4d, 0xbd, 0x76, 0x63, 0x65, 0x02, 0xdd, 0xc3, 0xd4, 0x4a, 0xa5, 0xfe, 0xd7
                                    };
/* modulus value n */
uint8_t modulus_n[MA_MOD_SIZE]    = {0xec, 0x48, 0x1d, 0xae, 0xf6, 0x4a, 0x46, 0x96, 0x9a, 0xbf, 0xb9, 0x4b, 0xb6, 0xd4, 0xc9, 0x54,
                                     0xac, 0xe2, 0xf2, 0x3e, 0xe9, 0x70, 0xda, 0x39, 0xdd, 0x2d, 0x82, 0x89, 0x48, 0xc0, 0x12, 0x45,
                                     0x63, 0xbe, 0xca, 0x16, 0xb9, 0x27, 0x48, 0x63, 0x5b, 0x99, 0x0c, 0xa2, 0x44, 0x1a, 0x62, 0x43,
                                     0x9c, 0x7f, 0x14, 0xdb, 0x98, 0xdd, 0xc4, 0x7d, 0xbd, 0xb4, 0xa6, 0xa1, 0x4d, 0x6f, 0x84, 0x30,
                                     0x6c, 0xf5, 0x07, 0x20, 0x60, 0x71, 0x1d, 0x87, 0xea, 0x05, 0x14, 0xb0, 0xd3, 0xd8, 0xf0, 0x45,
                                     0xaa, 0xce, 0x50, 0xf3, 0x17, 0xe8, 0x46, 0x1b, 0x8d, 0x75, 0xc8, 0xc4, 0xa5, 0x18, 0xc1, 0x89,
                                     0x38, 0xf2, 0x6b, 0xa5, 0x0a, 0x54, 0xea, 0x84, 0xb2, 0xa1, 0x9b, 0x24, 0x03, 0xe8, 0x95, 0xb3,
                                     0x70, 0xfe, 0x63, 0x4e, 0x4a, 0x65, 0x5c, 0xb9, 0xa7, 0xef, 0x7a, 0xb3, 0xae, 0xaf, 0x19, 0x03
                                    };
/* expected result of modular addition */
uint8_t expected_res[MA_RES_SIZE] = {0xa8, 0x24, 0xc1, 0xd8, 0xaa, 0x93, 0xc8, 0xd1, 0x42, 0x06, 0xef, 0x8b, 0xe1, 0x40, 0xae, 0x2d,
                                     0xb4, 0xc5, 0xba, 0x83, 0x9a, 0x13, 0x43, 0x8a, 0x92, 0x7b, 0xf5, 0x9c, 0x22, 0xff, 0xf1, 0x47,
                                     0x89, 0xdc, 0x4e, 0xb6, 0xd5, 0xbc, 0x45, 0xb0, 0xec, 0xf1, 0x34, 0x9d, 0xbe, 0x36, 0x7a, 0xc6,
                                     0xee, 0x80, 0x42, 0x91, 0x6a, 0x53, 0x8f, 0x07, 0x93, 0xc1, 0x23, 0x0f, 0x39, 0xdd, 0xc3, 0x92,
                                     0x79, 0x61, 0x49, 0x1d, 0xee, 0x5f, 0x00, 0xea, 0x66, 0xdd, 0x24, 0x4c, 0xe0, 0xf2, 0x3c, 0x88,
                                     0xf6, 0xfb, 0x52, 0x06, 0x1f, 0x75, 0xc3, 0xa9, 0x31, 0xeb, 0x72, 0x25, 0x76, 0xa6, 0xd0, 0x4b,
                                     0x39, 0x3a, 0xdb, 0x0d, 0x5b, 0x56, 0x32, 0x19, 0x36, 0xde, 0x93, 0x7a, 0xd4, 0x8c, 0xff, 0x52,
                                     0xf9, 0xad, 0xcb, 0xb8, 0xa2, 0x52, 0x64, 0x17, 0x63, 0x38, 0xe5, 0xa4, 0x8b, 0x82, 0xbf, 0xa3
                                    };

/* configure parameters of modular addition */
void pkcau_modular_add_operation_interrupt(pkcau_mod_parameter_struct *mod_para, uint32_t mode, uint8_t *results);
/* read result from PKCAU RAM */
static void pkcau_memcpy_value(uint32_t offset, uint32_t value);
/* copy operand with EOS or ROS to PKCAU RAM */
static void pkcau_memcpy_operand(uint32_t offset, const uint8_t operand[], uint32_t size);
/* read result from PKCAU RAM */
static void pkcau_memread(uint32_t offset, uint8_t *buf, uint32_t size);

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
    uint8_t mod_add_res[MA_MOD_SIZE];
    /* modular parameter structure */
    pkcau_mod_parameter_struct pkcau_mod_parameter;

    /* initialize the PKCAU modular parameter structure */
    pkcau_mod_struct_para_init(&pkcau_mod_parameter);
    /* initialize the modular parameters */
    pkcau_mod_parameter.oprd_a        = (uint8_t *)oprd_a;
    pkcau_mod_parameter.oprd_a_len    = sizeof(oprd_a);
    pkcau_mod_parameter.oprd_b        = (uint8_t *)oprd_b;
    pkcau_mod_parameter.oprd_b_len    = sizeof(oprd_b);
    pkcau_mod_parameter.modulus_n     = (uint8_t *)modulus_n;
    pkcau_mod_parameter.modulus_n_len = MA_MOD_SIZE;

    /* initialize LED1 and LED2 */
    gd_eval_led_init(LED1);
    gd_eval_led_init(LED2);
    /* turn off LED1 and LED2 */
    gd_eval_led_off(LED1);
    gd_eval_led_off(LED2);
    /* enable PKCAU clock */
    rcu_periph_clock_enable(RCU_PKCAU);
    /* reset PKCAU */
    pkcau_deinit();
    /* enable PKCAU interrupt */
    nvic_irq_enable(PKCAU_IRQn, 0, 0);

    pkcau_modular_add_operation_interrupt(&pkcau_mod_parameter, PKCAU_MODE_MOD_ADD, mod_add_res);
    /* if success, LED1 is on */
    if(memcmp(mod_add_res, expected_res, MA_MOD_SIZE)) {
        gd_eval_led_on(LED2);
    } else {
        gd_eval_led_on(LED1);
    }

    while(1) {
    }
}

/*!
    \brief      execute modular operation, include modular addition, modular subtraction and montgomery multiplication
    \param[in]  mod_para: PKCAU modular parameter struct
                  oprd_a: operand A
                  oprd_a_len: operand A length in byte
                  oprd_b: operand B
                  oprd_b_len: operand B length in byte
                  modulus_n: modulus value n
                  modulus_n_len: modulus length in byte
    \param[in]  mode: modular operation mode
                only one parameter can be selected which is shown as below:
      \arg        PKCAU_MODE_MOD_ADD: modular addition
      \arg        PKCAU_MODE_MOD_SUB: modular subtraction
      \arg        PKCAU_MODE_MONT_MUL: Montgomery multiplication
    \param[out] results: output buffer
    \retval     none
*/
void pkcau_modular_add_operation_interrupt(pkcau_mod_parameter_struct *mod_para, uint32_t mode, uint8_t *results)
{
    /* enable PKCAU */
    pkcau_enable();
    /* wait for PKCAU busy flag to reset */
    while(RESET != pkcau_flag_get(PKCAU_FLAG_BUSY));
    /* clear end flag */
    pkcau_flag_clear(PKCAU_FLAG_END);

    /* enable PKCAU interrupt */
    pkcau_interrupt_enable(PKCAU_INT_END | PKCAU_INT_RAMERR | PKCAU_INT_ADDRERR);

    /* write the modulus length in bit to PKCAU RAM */
    pkcau_memcpy_value(0x00000404U, (mod_para->modulus_n_len << 3));

    /* write the operand A, operand B and modulus value n to PKCAU RAM */
    pkcau_memcpy_operand(0x000008B4U, mod_para->oprd_a, mod_para->oprd_a_len);
    pkcau_memcpy_operand(0x00000A44U, mod_para->oprd_b, mod_para->oprd_b_len);
    pkcau_memcpy_operand(0x00000D5CU, mod_para->modulus_n, mod_para->modulus_n_len);
    /* configure the operation mode */
    pkcau_mode_set(mode);
    /* start computation */
    pkcau_start();
    /* wait for PKCAU operation completed */
    while(1 != end_flag);
    /* read results from RAM address */
    pkcau_memread(0xBD0, (uint8_t *)results, mod_para->modulus_n_len);
    /* disable PKCAU */
    pkcau_disable();
}

/*!
    \brief      copy normal 32-bit value to PKCAU RAM
    \param[in]  offset: RAM address offset to PKCAU base address
    \param[in]  value: the value needed to write into PKCAU RAM
    \param[out] none
    \retval     none
*/
static void pkcau_memcpy_value(uint32_t offset, uint32_t value)
{
    uint32_t *addr = (uint32_t *)((uint32_t)(PKCAU_BASE + offset));
    *addr = value;
}

/*!
    \brief      copy operand with EOS or ROS to PKCAU RAM
    \param[in]  offset: RAM address offset to PKCAU base address
    \param[in]  operand: the big endian operand vector, the left most byte of the value should be in the first element of the vector.
                If input data is little endian, please flip it in application code.
    \param[in]  size: operand vector length in byte
    \retval     none
*/
static void pkcau_memcpy_operand(uint32_t offset, const uint8_t operand[], uint32_t size)
{
    uint32_t data = 0U, i = 0U, j = 0U;

    while(4U <= size) {
        /* convert the big endian operand vector to little endian parameter to input to PKCAU RAM */
        data = (uint32_t)((uint32_t)operand[size - 1U] | ((uint32_t)operand[size - 2U] << 8U) | ((
                              uint32_t)operand[size - 3U] << 16U) | ((uint32_t)operand[size - 4U] << 24U));
        *(uint32_t *)((uint32_t)(PKCAU_BASE + offset + i)) = data;
        i = i + 4U;
        size -= 4U;
    }
    /* convert the big endian operand vector to little endian parameter to input to PKCAU RAM which is not a multiple of four */
    if(0U < size) {
        data = 0U;
        for(j = 0U; j < size; j++) {
            data = (uint32_t)((data << 8U) | (uint32_t)operand[j]);
        }
        *(uint32_t *)((uint32_t)(PKCAU_BASE + offset + i)) = data;
        i = i + 4U;
    }

    /* an additional word 0x00000000 is expected by the PKCAU */
    *(uint32_t *)((uint32_t)(PKCAU_BASE + offset + i)) = 0x00000000U;
}

/*!
    \brief      read result from PKCAU RAM
    \param[in]  offset: RAM address offset to PKCAU base address
    \param[out] buf: big endian result buffer, the left most byte from the PKCAU should be in the first element of buffer
                If need output data is little endian, please flip it in application code.
    \param[in]  size: number of byte to read
    \retval     none
*/
static void pkcau_memread(uint32_t offset, uint8_t *buf, uint32_t size)
{
    uint32_t  data = 0U, i = 0U, j = 0U;

    /* read data from PKCAU RAM */
    while(4U <= size) {
        data = *(uint32_t *)((uint32_t)(PKCAU_BASE + offset + i));
        i = i + 4U;

        /* data in PKCAU RAM is big endian */
        buf[size - 1U] = (uint8_t)(data & 0xffU);
        buf[size - 2U] = (uint8_t)((data >> 8U) & 0xffU);
        buf[size - 3U] = (uint8_t)((data >> 16U) & 0xffU);
        buf[size - 4U] = (uint8_t)((data >> 24U) & 0xffU);
        size -= 4U;
    }
    /* read data from PKCAU RAM which is not a multiple of four */
    if(0U < size) {
        data = *(uint32_t *)((uint32_t)(PKCAU_BASE + offset + i));
        for(j = 0U; j < size; j++) {
            buf[j] = (uint8_t)((data >> ((size - 1U - j) * 8U)) & 0xffU);
        }
    }
}
