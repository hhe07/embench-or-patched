/* Copyright (C) 2019 Clemson University

   Contributor Ola Jeppsson <ola.jeppsson@gmail.com>

   This file is part of Embench.

   SPDX-License-Identifier: GPL-3.0-or-later */

#include <support.h>
#include <stdio.h>
#include <or1k-support.h>
#include <or1k-sprs.h>
#include <stdint.h>

uint32_t _or1k_board_uart_base = 0x90000000;
uint32_t _or1k_board_uart_baud = 9600;
uint32_t _or1k_board_clk_freq = 1e6;


uint32_t start = 0;
uint32_t end = 0;

void
initialise_board ()
{
   or1k_timer_init(1e6);
   or1k_timer_set_mode(0b11);
   printf("Finished init\n");
}

void __attribute__ ((noinline)) __attribute__ ((externally_visible))
start_trigger ()
{
   or1k_timer_enable();
   start = or1k_mfspr(OR1K_SPR_TICK_TTCR_ADDR);
}

void __attribute__ ((noinline)) __attribute__ ((externally_visible))
stop_trigger ()
{
   end = or1k_mfspr(OR1K_SPR_TICK_TTCR_ADDR);
   printf("\n End time %u\n", end - start);
}
