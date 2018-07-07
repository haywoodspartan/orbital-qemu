/*
 * QEMU HAXM support
 *
 * Copyright IBM, Corp. 2008
 *
 * Authors:
 *  Anthony Liguori   <aliguori@us.ibm.com>
 *
 * Copyright (c) 2011 Intel Corporation
 *  Written by:
 *  Jiang Yunhong<yunhong.jiang@intel.com>
 *  Xin Xiaohui<xiaohui.xin@intel.com>
 *  Zhang Xiantao<xiantao.zhang@intel.com>
 *
 * Copyright 2016 Google, Inc.
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 *
 */

#ifndef QEMU_HAX_H
#define QEMU_HAX_H

#include "qemu-common.h"

#ifdef NEED_CPU_H
#include "cpu.h"

struct hax_sw_breakpoint {
    target_ulong pc;
    target_ulong saved_insn;
    int use_count;
    QTAILQ_ENTRY(hax_sw_breakpoint) entry;
};

int hax_sync_vcpus(void);
int hax_init_vcpu(CPUState *cpu);
int hax_smp_cpu_exec(CPUState *cpu);
int hax_populate_ram(uint64_t va, uint64_t size);

void hax_cpu_synchronize_state(CPUState *cpu);
void hax_cpu_synchronize_post_reset(CPUState *cpu);
void hax_cpu_synchronize_post_init(CPUState *cpu);
void hax_cpu_synchronize_pre_loadvm(CPUState *cpu);

int hax_update_guest_debug(CPUState *cpu);
int hax_insert_breakpoint(CPUState *cpu, target_ulong addr,
                          target_ulong len, int type);
int hax_remove_breakpoint(CPUState *cpu, target_ulong addr,
                          target_ulong len, int type);
void hax_remove_all_breakpoints(CPUState *cpu);

#endif

#ifdef CONFIG_HAX

int hax_enabled(void);

#include "hw/hw.h"
#include "qemu/bitops.h"
#include "exec/memory.h"
int hax_vcpu_destroy(CPUState *cpu);
void hax_raise_event(CPUState *cpu);
void hax_reset_vcpu_state(void *opaque);
#include "target/i386/hax-interface.h"
#include "target/i386/hax-i386.h"

#else /* CONFIG_HAX */

#define hax_enabled() (0)

#endif /* CONFIG_HAX */

#endif /* QEMU_HAX_H */
