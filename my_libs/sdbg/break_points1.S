/***********************************************************************
 * CH32V103在线调试的HardFault_Handler中断函数
 * Copyright (C) 2022  Xu Ruijun
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
************************************************************************/
	.text
	.align 2
	.global HardFault_Handler
	.type   HardFault_Handler, %function
HardFault_Handler:
	sw     sp, 0(gp)
	la     sp, sdbg_regsave+4
	sw     ra, 0(sp)
	sw     gp, 8(sp)
	sw     tp, 12(sp)
	sw     t0, 16(sp)
	sw     t1, 20(sp)
	sw     t2, 24(sp)
	sw     s0, 28(sp)
	sw     s1, 32(sp)
	sw     a0, 36(sp)
	sw     a1, 40(sp)
	sw     a2, 44(sp)
	sw     a3, 48(sp)
	sw     a4, 52(sp)
	sw     a5, 56(sp)
	sw     a6, 60(sp)
	sw     a7, 64(sp)
	sw     s2, 68(sp)
	sw     s3, 72(sp)
	sw     s4, 76(sp)
	sw     s5, 80(sp)
	sw     s6, 84(sp)
	sw     s7, 88(sp)
	sw     s8, 92(sp)
	sw     s9, 96(sp)
	sw     s10, 100(sp)
	sw     s11, 104(sp)
	sw     t3, 108(sp)
	sw     t4, 112(sp)
	sw     t5, 116(sp)
	sw     t6, 120(sp)
	csrr   t0, mepc
	sw     t0, 124(sp)
	lw     t0, 0(gp)
	sw     t0, 4(sp)
	mv     sp, t0
	jal    ra, Breakpoint_Handler_C
	la     sp, sdbg_regsave+4
	lw     ra, 0(sp)
	lw     gp, 8(sp)
	lw     tp, 12(sp)
	lw     t1, 20(sp)
	lw     t2, 24(sp)
	lw     s0, 28(sp)
	lw     s1, 32(sp)
	lw     a0, 36(sp)
	lw     a1, 40(sp)
	lw     a2, 44(sp)
	lw     a3, 48(sp)
	lw     a4, 52(sp)
	lw     a5, 56(sp)
	lw     a6, 60(sp)
	lw     a7, 64(sp)
	lw     s2, 68(sp)
	lw     s3, 72(sp)
	lw     s4, 76(sp)
	lw     s5, 80(sp)
	lw     s6, 84(sp)
	lw     s7, 88(sp)
	lw     s8, 92(sp)
	lw     s9, 96(sp)
	lw     s10, 100(sp)
	lw     s11, 104(sp)
	lw     t3, 108(sp)
	lw     t4, 112(sp)
	lw     t5, 116(sp)
	lw     t6, 120(sp)
	lw     t0, 124(sp)
	csrw   mepc, t0
	lw     t0, 16(sp)
	lw     sp, 4(sp)
	mret
