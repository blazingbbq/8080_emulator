#include <stdio.h>
#include <string.h>

#define ARG_INDENT 8

#define INSTR_BASE(name, size, format...)                           \
    int disasm_##name(unsigned char *codebuffer, unsigned int pc) { \
        unsigned char *codebyte = &codebuffer[pc];                  \
        printf(format);                                             \
        printf("\n");                                               \
        return size;                                                \
    }
#define INSTR(name) INSTR_BASE(name, 1, #name)
#define INSTR_R(name, r) \
    INSTR_BASE(name, 1, #name "%*s%s", ARG_INDENT - (int)strlen(#name), "", #r)
#define INSTR_R_R(name, r1, r2)                                             \
    INSTR_BASE(name, 1, #name "%*s%s, %s", ARG_INDENT - (int)strlen(#name), \
               "", #r1, #r2)
#define INSTR_R_D8(name, r)                    \
    INSTR_BASE(name, 2, #name "%*s%s, 0x%02x", \
               ARG_INDENT - (int)strlen(#name), "", #r, codebyte[1])
#define INSTR_R_D16(name, r)                                         \
    INSTR_BASE(name, 3, #name "%*s%s, 0x%02x%02x",                   \
               ARG_INDENT - (int)strlen(#name), "", #r, codebyte[2], \
               codebyte[1])
#define INSTR_D8(name)                                                      \
    INSTR_BASE(name, 2, #name "%*s0x%02x", ARG_INDENT - (int)strlen(#name), \
               "", codebyte[1])
#define INSTR_D16(name)                        \
    INSTR_BASE(name, 3, #name "%*s0x%02x%02x", \
               ARG_INDENT - (int)strlen(#name), "", codebyte[2], codebyte[1])
#define INSTR_ADDR(name)                       \
    INSTR_BASE(name, 3, #name "%*s0x%02x%02x", \
               ARG_INDENT - (int)strlen(#name), "", codebyte[2], codebyte[1])

INSTR_BASE(unimplemented, 1, "Unimplemented opcode <%02x> at addr: %08x",
           codebyte[0], pc)

/* --- 8080 Instructions --- */

INSTR(NOP)
INSTR_R_D16(LXI, B)
INSTR_R(STAX, B)
INSTR_R(INX, B)
INSTR_R(INR, B)
INSTR_R(DCR, B)
INSTR_R_D8(MVI, B)
INSTR(RLC)
// 0x08 --

INSTR_ADDR(JMP)

/*
 * disasm_handlers: Disassembly handler functions, indexed by opcode.
 *
 * Returns:
 *      Number of bytes to advance pc.
 */
int (*disasm_handlers[0x100])(unsigned char *codebuffer,
                              unsigned int pc) = {
    disasm_NOP,            // 0x00
    disasm_LXI,            // 0x01
    disasm_STAX,           // 0x02
    disasm_INX,            // 0x03
    disasm_INR,            // 0x04
    disasm_DCR,            // 0x05
    disasm_MVI,            // 0x06
    disasm_RLC,            // 0x07
    disasm_unimplemented,  // 0x08
    disasm_unimplemented,  // 0x09
    disasm_unimplemented,  // 0x0a
    disasm_unimplemented,  // 0x0b
    disasm_unimplemented,  // 0x0c
    disasm_unimplemented,  // 0x0d
    disasm_unimplemented,  // 0x0e
    disasm_unimplemented,  // 0x0f
    disasm_unimplemented,  // 0x10
    disasm_unimplemented,  // 0x11
    disasm_unimplemented,  // 0x12
    disasm_unimplemented,  // 0x13
    disasm_unimplemented,  // 0x14
    disasm_unimplemented,  // 0x15
    disasm_unimplemented,  // 0x16
    disasm_unimplemented,  // 0x17
    disasm_unimplemented,  // 0x18
    disasm_unimplemented,  // 0x19
    disasm_unimplemented,  // 0x1a
    disasm_unimplemented,  // 0x1b
    disasm_unimplemented,  // 0x1c
    disasm_unimplemented,  // 0x1d
    disasm_unimplemented,  // 0x1e
    disasm_unimplemented,  // 0x1f
    disasm_unimplemented,  // 0x20
    disasm_unimplemented,  // 0x21
    disasm_unimplemented,  // 0x22
    disasm_unimplemented,  // 0x23
    disasm_unimplemented,  // 0x24
    disasm_unimplemented,  // 0x25
    disasm_unimplemented,  // 0x26
    disasm_unimplemented,  // 0x27
    disasm_unimplemented,  // 0x28
    disasm_unimplemented,  // 0x29
    disasm_unimplemented,  // 0x2a
    disasm_unimplemented,  // 0x2b
    disasm_unimplemented,  // 0x2c
    disasm_unimplemented,  // 0x2d
    disasm_unimplemented,  // 0x2e
    disasm_unimplemented,  // 0x2f
    disasm_unimplemented,  // 0x30
    disasm_unimplemented,  // 0x31
    disasm_unimplemented,  // 0x32
    disasm_unimplemented,  // 0x33
    disasm_unimplemented,  // 0x34
    disasm_unimplemented,  // 0x35
    disasm_unimplemented,  // 0x36
    disasm_unimplemented,  // 0x37
    disasm_unimplemented,  // 0x38
    disasm_unimplemented,  // 0x39
    disasm_unimplemented,  // 0x3a
    disasm_unimplemented,  // 0x3b
    disasm_unimplemented,  // 0x3c
    disasm_unimplemented,  // 0x3d
    disasm_unimplemented,  // 0x3e
    disasm_unimplemented,  // 0x3f
    disasm_unimplemented,  // 0x40
    disasm_unimplemented,  // 0x41
    disasm_unimplemented,  // 0x42
    disasm_unimplemented,  // 0x43
    disasm_unimplemented,  // 0x44
    disasm_unimplemented,  // 0x45
    disasm_unimplemented,  // 0x46
    disasm_unimplemented,  // 0x47
    disasm_unimplemented,  // 0x48
    disasm_unimplemented,  // 0x49
    disasm_unimplemented,  // 0x4a
    disasm_unimplemented,  // 0x4b
    disasm_unimplemented,  // 0x4c
    disasm_unimplemented,  // 0x4d
    disasm_unimplemented,  // 0x4e
    disasm_unimplemented,  // 0x4f
    disasm_unimplemented,  // 0x50
    disasm_unimplemented,  // 0x51
    disasm_unimplemented,  // 0x52
    disasm_unimplemented,  // 0x53
    disasm_unimplemented,  // 0x54
    disasm_unimplemented,  // 0x55
    disasm_unimplemented,  // 0x56
    disasm_unimplemented,  // 0x57
    disasm_unimplemented,  // 0x58
    disasm_unimplemented,  // 0x59
    disasm_unimplemented,  // 0x5a
    disasm_unimplemented,  // 0x5b
    disasm_unimplemented,  // 0x5c
    disasm_unimplemented,  // 0x5d
    disasm_unimplemented,  // 0x5e
    disasm_unimplemented,  // 0x5f
    disasm_unimplemented,  // 0x60
    disasm_unimplemented,  // 0x61
    disasm_unimplemented,  // 0x62
    disasm_unimplemented,  // 0x63
    disasm_unimplemented,  // 0x64
    disasm_unimplemented,  // 0x65
    disasm_unimplemented,  // 0x66
    disasm_unimplemented,  // 0x67
    disasm_unimplemented,  // 0x68
    disasm_unimplemented,  // 0x69
    disasm_unimplemented,  // 0x6a
    disasm_unimplemented,  // 0x6b
    disasm_unimplemented,  // 0x6c
    disasm_unimplemented,  // 0x6d
    disasm_unimplemented,  // 0x6e
    disasm_unimplemented,  // 0x6f
    disasm_unimplemented,  // 0x70
    disasm_unimplemented,  // 0x71
    disasm_unimplemented,  // 0x72
    disasm_unimplemented,  // 0x73
    disasm_unimplemented,  // 0x74
    disasm_unimplemented,  // 0x75
    disasm_unimplemented,  // 0x76
    disasm_unimplemented,  // 0x77
    disasm_unimplemented,  // 0x78
    disasm_unimplemented,  // 0x79
    disasm_unimplemented,  // 0x7a
    disasm_unimplemented,  // 0x7b
    disasm_unimplemented,  // 0x7c
    disasm_unimplemented,  // 0x7d
    disasm_unimplemented,  // 0x7e
    disasm_unimplemented,  // 0x7f
    disasm_unimplemented,  // 0x80
    disasm_unimplemented,  // 0x81
    disasm_unimplemented,  // 0x82
    disasm_unimplemented,  // 0x83
    disasm_unimplemented,  // 0x84
    disasm_unimplemented,  // 0x85
    disasm_unimplemented,  // 0x86
    disasm_unimplemented,  // 0x87
    disasm_unimplemented,  // 0x88
    disasm_unimplemented,  // 0x89
    disasm_unimplemented,  // 0x8a
    disasm_unimplemented,  // 0x8b
    disasm_unimplemented,  // 0x8c
    disasm_unimplemented,  // 0x8d
    disasm_unimplemented,  // 0x8e
    disasm_unimplemented,  // 0x8f
    disasm_unimplemented,  // 0x90
    disasm_unimplemented,  // 0x91
    disasm_unimplemented,  // 0x92
    disasm_unimplemented,  // 0x93
    disasm_unimplemented,  // 0x94
    disasm_unimplemented,  // 0x95
    disasm_unimplemented,  // 0x96
    disasm_unimplemented,  // 0x97
    disasm_unimplemented,  // 0x98
    disasm_unimplemented,  // 0x99
    disasm_unimplemented,  // 0x9a
    disasm_unimplemented,  // 0x9b
    disasm_unimplemented,  // 0x9c
    disasm_unimplemented,  // 0x9d
    disasm_unimplemented,  // 0x9e
    disasm_unimplemented,  // 0x9f
    disasm_unimplemented,  // 0xa0
    disasm_unimplemented,  // 0xa1
    disasm_unimplemented,  // 0xa2
    disasm_unimplemented,  // 0xa3
    disasm_unimplemented,  // 0xa4
    disasm_unimplemented,  // 0xa5
    disasm_unimplemented,  // 0xa6
    disasm_unimplemented,  // 0xa7
    disasm_unimplemented,  // 0xa8
    disasm_unimplemented,  // 0xa9
    disasm_unimplemented,  // 0xaa
    disasm_unimplemented,  // 0xab
    disasm_unimplemented,  // 0xac
    disasm_unimplemented,  // 0xad
    disasm_unimplemented,  // 0xae
    disasm_unimplemented,  // 0xaf
    disasm_unimplemented,  // 0xb0
    disasm_unimplemented,  // 0xb1
    disasm_unimplemented,  // 0xb2
    disasm_unimplemented,  // 0xb3
    disasm_unimplemented,  // 0xb4
    disasm_unimplemented,  // 0xb5
    disasm_unimplemented,  // 0xb6
    disasm_unimplemented,  // 0xb7
    disasm_unimplemented,  // 0xb8
    disasm_unimplemented,  // 0xb9
    disasm_unimplemented,  // 0xba
    disasm_unimplemented,  // 0xbb
    disasm_unimplemented,  // 0xbc
    disasm_unimplemented,  // 0xbd
    disasm_unimplemented,  // 0xbe
    disasm_unimplemented,  // 0xbf
    disasm_unimplemented,  // 0xc0
    disasm_unimplemented,  // 0xc1
    disasm_unimplemented,  // 0xc2
    disasm_JMP,            // 0xc3
    disasm_unimplemented,  // 0xc4
    disasm_unimplemented,  // 0xc5
    disasm_unimplemented,  // 0xc6
    disasm_unimplemented,  // 0xc7
    disasm_unimplemented,  // 0xc8
    disasm_unimplemented,  // 0xc9
    disasm_unimplemented,  // 0xca
    disasm_unimplemented,  // 0xcb
    disasm_unimplemented,  // 0xcc
    disasm_unimplemented,  // 0xcd
    disasm_unimplemented,  // 0xce
    disasm_unimplemented,  // 0xcf
    disasm_unimplemented,  // 0xd0
    disasm_unimplemented,  // 0xd1
    disasm_unimplemented,  // 0xd2
    disasm_unimplemented,  // 0xd3
    disasm_unimplemented,  // 0xd4
    disasm_unimplemented,  // 0xd5
    disasm_unimplemented,  // 0xd6
    disasm_unimplemented,  // 0xd7
    disasm_unimplemented,  // 0xd8
    disasm_unimplemented,  // 0xd9
    disasm_unimplemented,  // 0xda
    disasm_unimplemented,  // 0xdb
    disasm_unimplemented,  // 0xdc
    disasm_unimplemented,  // 0xdd
    disasm_unimplemented,  // 0xde
    disasm_unimplemented,  // 0xdf
    disasm_unimplemented,  // 0xe0
    disasm_unimplemented,  // 0xe1
    disasm_unimplemented,  // 0xe2
    disasm_unimplemented,  // 0xe3
    disasm_unimplemented,  // 0xe4
    disasm_unimplemented,  // 0xe5
    disasm_unimplemented,  // 0xe6
    disasm_unimplemented,  // 0xe7
    disasm_unimplemented,  // 0xe8
    disasm_unimplemented,  // 0xe9
    disasm_unimplemented,  // 0xea
    disasm_unimplemented,  // 0xeb
    disasm_unimplemented,  // 0xec
    disasm_unimplemented,  // 0xed
    disasm_unimplemented,  // 0xee
    disasm_unimplemented,  // 0xef
    disasm_unimplemented,  // 0xf0
    disasm_unimplemented,  // 0xf1
    disasm_unimplemented,  // 0xf2
    disasm_unimplemented,  // 0xf3
    disasm_unimplemented,  // 0xf4
    disasm_unimplemented,  // 0xf5
    disasm_unimplemented,  // 0xf6
    disasm_unimplemented,  // 0xf7
    disasm_unimplemented,  // 0xf8
    disasm_unimplemented,  // 0xf9
    disasm_unimplemented,  // 0xfa
    disasm_unimplemented,  // 0xfb
    disasm_unimplemented,  // 0xfc
    disasm_unimplemented,  // 0xfd
    disasm_unimplemented,  // 0xfe
    disasm_unimplemented   // 0xff
};
