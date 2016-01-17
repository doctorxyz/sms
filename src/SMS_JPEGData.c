/*
#     ___  _ _      ___
#    |    | | |    |
# ___|    |   | ___|    PS2DEV Open Source Project.
#----------------------------------------------------------
# (c) 2005-2009 Eugene Plotnikov <e-plotnikov@operamail.com>
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
#
*/
#include "SMS.h"

static const unsigned char s_IDCT[] __attribute__(   (  aligned( 16 ), section( ".rodata" )  )   ) = {
 0x5D, 0x00, 0x00, 0x80, 0x00, 0xE0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x80,
 0x2C, 0xDD, 0xF9, 0x13, 0x65, 0xE8, 0x51, 0x03, 0x43, 0xC4, 0x17, 0x4A, 0x0B, 0x69, 0x9C, 0xC9,
 0xB6, 0xD9, 0x0A, 0x39, 0x68, 0x3F, 0x16, 0x8E, 0xBA, 0x93, 0xC0, 0xFD, 0x4C, 0x6C, 0x90, 0xD8,
 0xFC, 0x04, 0x36, 0xD7, 0xFD, 0x5C, 0x92, 0x94, 0xFE, 0x1F, 0x8A, 0xD8, 0x62, 0x78, 0xD9, 0xB9,
 0xBB, 0x67, 0x8B, 0xF2, 0xD0, 0xDD, 0x54, 0xB0, 0x26, 0x0C, 0xC4, 0x46, 0x7D, 0x86, 0x12, 0x81,
 0x82, 0x9E, 0x41, 0x7B, 0x19, 0x94, 0x27, 0x60, 0x00, 0x9D, 0x16, 0x30, 0x5B, 0xEC, 0x84, 0x31,
 0x76, 0x87, 0x68, 0x89, 0xA7, 0x6F, 0xAC, 0xDC, 0xCA, 0x80, 0x46, 0x3C, 0xBB, 0x30, 0x4A, 0x42,
 0x5C, 0x27, 0xF0, 0x9A, 0x93, 0x84, 0x3F, 0xFD, 0xA4, 0x3B, 0x36, 0xAE, 0x32, 0xB6, 0xF8, 0xBD,
 0x2B, 0x4F, 0xD1, 0xEE, 0x7B, 0xCA, 0xF3, 0xC7, 0x97, 0xED, 0xCF, 0x38, 0x77, 0x65, 0x81, 0x1E,
 0x98, 0x2C, 0x68, 0x8B, 0x61, 0x75, 0x5B, 0x9D, 0x7F, 0x7E, 0x9B, 0x8C, 0x4E, 0x67, 0x90, 0xBE,
 0xED, 0xB3, 0x15, 0x25, 0x15, 0xC6, 0x2F, 0xEC, 0xB2, 0x7B, 0xC4, 0xC9, 0x1B, 0xDE, 0x46, 0x58,
 0x3C, 0xBC, 0xC8, 0x04, 0xE8, 0x50, 0x0A, 0x12, 0x2F, 0x2E, 0x94, 0xD8, 0x53, 0x2C, 0x30, 0x5B,
 0x18, 0x8D, 0x93, 0x1C, 0x3A, 0xAF, 0x5B, 0x94, 0x7C, 0xF8, 0x28, 0x1D, 0x36, 0xD1, 0x27, 0xB1,
 0x8A, 0x33, 0x75, 0xD8, 0x64, 0x59, 0xCD, 0x56, 0x3F, 0xA9, 0xBF, 0x4A, 0x91, 0x6B, 0x15, 0xB2,
 0x5B, 0x63, 0x41, 0x12, 0x06, 0x0D, 0x1C, 0xEA, 0xE5, 0x5F, 0x83, 0x58, 0x4B, 0x3B, 0xF6, 0x03,
 0xB2, 0x41, 0x74, 0x6B, 0x43, 0xF1, 0xA2, 0x9F, 0x27, 0x24, 0x87, 0x5C, 0x56, 0x49, 0xF9, 0x7F,
 0xF4, 0x56, 0x19, 0x96, 0xEC, 0x2C, 0x29, 0xE2, 0xC8, 0x39, 0x15, 0x11, 0x16, 0x88, 0x16, 0x43,
 0x23, 0xBA, 0xDD, 0x56, 0x81, 0x58, 0x8D, 0xA3, 0xC9, 0xED, 0xFD, 0xB5, 0x4E, 0xBF, 0xAF, 0x76,
 0xB7, 0x18, 0x63, 0x22, 0x01, 0xD5, 0x92, 0xD0, 0x07, 0xAD, 0x9B, 0xBE, 0xBC, 0x6B, 0xAD, 0x2D,
 0xAC, 0xAE, 0x93, 0x56, 0x7D, 0x98, 0xF6, 0x22, 0xAF, 0xC7, 0xAA, 0x6B, 0x8A, 0xFD, 0xA0, 0x60,
 0x30, 0x49, 0xAE, 0xE0, 0x56, 0xBE, 0x35, 0xA7, 0xC4, 0xAA, 0x94, 0xE9, 0xBD, 0xED, 0x71, 0xF9,
 0x75, 0x35, 0x38, 0x77, 0x2F, 0x35, 0xA1, 0x61, 0x65, 0x90, 0x69, 0x62, 0x5C, 0x1D, 0xBC, 0x80,
 0x65, 0x79, 0x3E, 0x1F, 0x51, 0xE5, 0xBF, 0x84, 0x94, 0xA4, 0x62, 0x4E, 0x37, 0x03, 0x74, 0x0D,
 0x0B, 0xC9, 0x68, 0x1A, 0x23, 0x87, 0xA6, 0x89, 0x53, 0x76, 0x04, 0xAF, 0x70, 0x19, 0x37, 0xDE,
 0x34, 0xD9, 0xD5, 0xC5, 0x24, 0xC0, 0xC8, 0xFB, 0xF0, 0xD7, 0xD4, 0x78, 0xEE, 0xE9, 0x48, 0xA1,
 0x78, 0xEA, 0x78, 0x78, 0x30, 0x42, 0x42, 0xD0, 0xC7, 0xEC, 0x7C, 0x0D, 0x4C, 0x98, 0x8F, 0xBC,
 0xE6, 0x96, 0xCA, 0x3E, 0x1B, 0xEC, 0xC7, 0xB3, 0x28, 0x8B, 0x0D, 0x2B, 0xCC, 0x8C, 0xC5, 0xB0,
 0xAF, 0xF0, 0xB4, 0x83, 0xFE, 0xCC, 0x4C, 0x77, 0x35, 0xA2, 0x6F, 0x80, 0x91, 0x08, 0xCC, 0x0D,
 0x93, 0x33, 0x14, 0x80, 0xC3, 0x23, 0xDB, 0x39, 0xDB, 0xCE, 0x76, 0xA5, 0x7B, 0xD4, 0xFB, 0x0F,
 0xA0, 0x8B, 0x7F, 0x5B, 0x50, 0x08, 0x18, 0xDE, 0x4C, 0x84, 0x1C, 0x2A, 0x77, 0xA2, 0xA0, 0xC6,
 0xFA, 0xE3, 0x09, 0xCB, 0xBD, 0x9B, 0x4C, 0x25, 0x61, 0x43, 0x37, 0x34, 0xCF, 0x7D, 0x3D, 0x01,
 0xCD, 0x9C, 0x6E, 0x6B, 0x5F, 0x5A, 0x20, 0x4F, 0xB4, 0x2C, 0x6F, 0x52, 0x42, 0xD8, 0xA5, 0xF0,
 0x33, 0x48, 0xDA, 0x6E, 0x90, 0xBE, 0x59, 0x58, 0x03, 0xA6, 0xC3, 0x5D, 0x21, 0xF5, 0xA5, 0x5E,
 0x86, 0x7F, 0xB5, 0xDF, 0xF5, 0x70, 0xDC, 0xD4, 0x01, 0x86, 0x78, 0x38, 0x5E, 0xE6, 0x1D, 0x24,
 0xBF, 0xB3, 0x51, 0x0F, 0xDE, 0xEF, 0xCE, 0x2C, 0xA1, 0xBB, 0xC8, 0x57, 0x42, 0xA0, 0x2B, 0x97,
 0xB7, 0x17, 0x87, 0x70, 0x2D, 0xC5, 0xC9, 0xB4, 0xCF, 0x72, 0x0B, 0x7F, 0xE1, 0xC0, 0x58, 0xD3,
 0xC1, 0x29, 0xE5, 0xBB, 0x0C, 0xEA, 0xC9, 0x59, 0x9B, 0x0F, 0x56, 0xD0, 0x48, 0x0F, 0xF6, 0x1C,
 0x4D, 0x7B, 0x1E, 0x9F, 0x58, 0x12, 0xDF, 0xE1, 0x65, 0xB6, 0x10, 0xE4, 0x20, 0x36, 0xAF, 0x74,
 0x98, 0xD2, 0x94, 0x25, 0xC4, 0x9B, 0xB0, 0x7F, 0x31, 0x34, 0xEA, 0xE7, 0x46, 0xA4, 0x69, 0x83,
 0x60, 0x11, 0x77, 0x24, 0x4A, 0x17, 0xF3, 0x3A, 0x31, 0x7D, 0x67, 0xE2, 0x4F, 0x75, 0x7D, 0xEC,
 0x1F, 0x1C, 0xE6, 0x47, 0xC4, 0xC7, 0xE3, 0xE0, 0xCD, 0xBC, 0xFD, 0xA8, 0x91, 0x85, 0x6E, 0x8D,
 0x12, 0xFE, 0x19, 0x47, 0xCC, 0xBB, 0x36, 0xEF, 0x1F, 0x8E, 0xE7, 0x43, 0x08, 0xC7, 0x96, 0xE8,
 0x6E, 0x6B, 0xC0, 0xC5, 0xB0, 0x17, 0x5B, 0x1C, 0x38, 0xF2, 0x3E, 0x0F, 0x43, 0x49, 0x56, 0x7A,
 0x77, 0x6D, 0xA2, 0xA1, 0xDC, 0xBC, 0xE4, 0x43, 0x60, 0xE4, 0x39, 0xC5, 0x65, 0x0C, 0x6C, 0xD5,
 0xB7, 0x1B, 0x9B, 0x61, 0x8D, 0x52, 0x22, 0x08, 0x2E, 0x95, 0xEE, 0x20, 0x2E, 0xA3, 0x6F, 0x4C,
 0x7B, 0x5C, 0x74, 0x7E, 0x7F, 0xF4, 0x3E, 0xBC, 0x49, 0xDB, 0x52, 0xA8, 0xE2, 0x6B, 0x70, 0x59,
 0xE1, 0xF7, 0x92, 0x68, 0x7C, 0xD0, 0x25, 0xCC, 0xC1, 0x18, 0xE7, 0xC6, 0x13, 0x16, 0x48, 0x06,
 0x73, 0x44, 0x26, 0x51, 0x42, 0x39, 0x6A, 0xF7, 0xB3, 0x74, 0xD9, 0x2E, 0xC6, 0x49, 0x6E, 0xDA,
 0xBC, 0xBB, 0x9C, 0x18, 0x5D, 0xD3, 0x94, 0x1C, 0xBD, 0x5A, 0xE0, 0x7B, 0x5A, 0x10, 0x20, 0x0D,
 0xDB, 0x88, 0xBA, 0x33, 0xBE, 0x5D, 0x81, 0x5F, 0x4A, 0x03, 0x38, 0x2E, 0x72, 0x8A, 0x28, 0xF5,
 0x8B, 0x45, 0x9D, 0x90, 0x8C, 0xF5, 0xEC, 0x9F, 0xF1, 0x2B, 0xA2, 0xD3, 0x94, 0xDE, 0x59, 0x9C,
 0xC4, 0x56, 0xC3, 0xC4, 0xF7, 0x8C, 0x48, 0x27, 0x4A, 0xE4, 0x67, 0xA6, 0xEE, 0xEB, 0xD0, 0x55,
 0x31, 0xEF, 0xE4, 0x26, 0xEA, 0x72, 0x65, 0x9B, 0x58, 0x3C, 0xC2, 0x69, 0xAC, 0x6E, 0x17, 0xF7,
 0xFE, 0x37, 0x69, 0x91, 0xFB, 0xAD, 0xD8, 0x8D, 0x3E, 0xC7, 0x5C, 0xEA, 0x8F, 0xAF, 0xD1, 0xBE,
 0xCA, 0xA5, 0x91, 0x9E, 0x1F, 0x49, 0xF7, 0x97, 0xCE, 0xD8, 0xFD, 0x1D, 0x04, 0xB8, 0x2C, 0xD3,
 0x3E, 0xFE, 0x95
};

static const unsigned char s_CSC1[] __attribute__(   (  aligned( 16 ), section( ".rodata" )  )   ) = {
 0x5D, 0x00, 0x00, 0x80, 0x00, 0xD0, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x00,
 0x2C, 0xE1, 0x00, 0xCA, 0x7A, 0x4C, 0x6C, 0x03, 0x8E, 0xCF, 0xF8, 0xA6, 0x81, 0x65, 0xB7, 0x0B,
 0xBA, 0x51, 0x2C, 0x45, 0x87, 0xC2, 0x80, 0x8E, 0x2B, 0x9D, 0x92, 0x42, 0x0F, 0xBB, 0x67, 0x26,
 0x32, 0x2A, 0xC8, 0xE0, 0xAF, 0xFC, 0xB4, 0x01, 0xA7, 0x86, 0x1D, 0x89, 0xDA, 0xB0, 0xE4, 0x2A,
 0xDE, 0x12, 0xDD, 0xE3, 0x5C, 0x3B, 0xD4, 0xA2, 0xCA, 0x18, 0xC8, 0xA0, 0x64, 0xFE, 0x49, 0xBB,
 0xFB, 0xD5, 0xBA, 0xA8, 0xDB, 0xB1, 0x1F, 0xC2, 0x2D, 0x8E, 0x14, 0x21, 0x42, 0x5D, 0x7E, 0x00,
 0xF9, 0x00, 0x31, 0xE1, 0x0E, 0xD5, 0xD1, 0xAB, 0x57, 0x3E, 0x7C, 0x26, 0xE6, 0x5B, 0x60, 0xAA,
 0xAB, 0x54, 0xD2, 0x4D, 0x6E, 0x73, 0x50, 0x00, 0x40, 0x16, 0x94, 0xA9, 0x24, 0x06, 0x70, 0xD2,
 0x3B, 0x85, 0xCB, 0x65, 0x05, 0xC0, 0xF9, 0x95, 0x76, 0xFB, 0x10, 0x99, 0x78, 0x6B, 0x0B, 0xDF,
 0x45, 0x90, 0xF5, 0x0A, 0x7F, 0x95, 0x44, 0x89, 0x32, 0x8C, 0x2D, 0x2E, 0xF2, 0x06, 0xF6, 0x1C,
 0xCD, 0xE3, 0x1E, 0x77, 0x6B, 0x54, 0xBD, 0x7E, 0xFF, 0x80, 0xA5, 0xC5, 0x5B, 0x9E, 0x54, 0x16,
 0x76, 0x92, 0xB9, 0x25, 0x32, 0x67, 0x22, 0x94, 0x88, 0x8A, 0x78, 0x04, 0x74, 0xF3, 0x0B, 0x0A,
 0x9A, 0x07, 0xE5, 0x26, 0xD5, 0x8E, 0x91, 0xA1, 0xAE, 0x8A, 0x47, 0x09, 0x68, 0x5D, 0x7A, 0xC6,
 0xB8, 0x62, 0x50, 0x4A, 0x58, 0x3B, 0xEF, 0x98, 0x87, 0xCB, 0x5F, 0xB4, 0x80, 0x22, 0xF2, 0xD4,
 0x5C, 0x92, 0xBE, 0xEA, 0xF9, 0xFE, 0xE1, 0x6C, 0xED, 0x39, 0x35, 0x8E, 0x3B, 0xE0, 0xC6, 0xC2,
 0x2F, 0x99, 0x6A, 0xA6, 0x10, 0x84, 0x13, 0x62, 0x19, 0x65, 0xF6, 0x1E, 0x53, 0xF7, 0x04, 0x15,
 0xDC, 0x02, 0x71, 0xE0, 0x65, 0xEC, 0x8A, 0xC4, 0xF2, 0xB4, 0x96, 0x2E, 0x3D, 0xF2, 0x82, 0xA2,
 0x77, 0x5A, 0xBD, 0x79, 0x4D, 0x8E, 0x76, 0xB4, 0xE1, 0x84, 0xBC, 0x3F, 0x76, 0xBD, 0x2F, 0xB5,
 0x52, 0x1E, 0x5C, 0xBA, 0xC8, 0xDA, 0xC5, 0xDA, 0xDC, 0xD0, 0xD1, 0xC6, 0x71, 0x03, 0xF2, 0x9E,
 0xE3, 0x88, 0x55, 0xA6, 0x0C, 0xB5, 0xC5, 0x73, 0x66, 0x39, 0xC5, 0x1A, 0x57, 0x72, 0xCA, 0x5E,
 0x32, 0xAA, 0xB2, 0xE2, 0x17, 0xDF, 0xFE, 0x0C, 0x70, 0xC3, 0xCA, 0x98, 0x75, 0xA7, 0x95, 0xFE,
 0xAB, 0x70, 0x0C, 0x05, 0x69, 0x3C, 0x3B, 0x75, 0x72, 0xDE, 0x1D, 0xB1, 0xFD, 0x4E, 0x28, 0x2C,
 0x0E, 0x33, 0x54, 0x0D, 0x6B, 0x80, 0xB6, 0x2C, 0x61, 0x5A, 0x95, 0xE3, 0x41, 0xF4, 0x1F, 0x21,
 0xE1, 0x26, 0x81, 0x41, 0xF0, 0x9C, 0x42, 0xEB, 0x6F, 0x82, 0x5B, 0x71, 0xCE, 0x8D, 0xD4, 0xCC,
 0xCB, 0x65, 0xBB, 0x61, 0x5E, 0x95, 0x2E, 0xAB, 0xE5, 0xC9, 0xAF, 0xF9, 0xA9, 0xDA, 0x0F, 0x87,
 0x43, 0x13, 0x35, 0x07, 0xE4, 0x6E, 0xA6, 0xD2, 0x15, 0x4A, 0x9D, 0xF2, 0x04, 0xE5, 0x03, 0x02,
 0xDE, 0x03, 0xB8, 0x52, 0xE0, 0x59, 0xE8, 0xC3, 0xF7, 0x47, 0x07, 0xDC, 0x2A, 0xFB, 0xD4, 0x70,
 0xEE, 0x61, 0x1D, 0xE5, 0x50, 0x73, 0x76, 0xEB, 0x24, 0xF6, 0x39, 0xAB, 0x6B, 0xDD, 0x39, 0x0B,
 0x60, 0x92, 0x30, 0xE3, 0x4B, 0xEF, 0x60, 0x1C, 0x24, 0x5D, 0x52, 0xCA, 0xBF, 0xD3, 0x5F, 0x39,
 0x80, 0x8D, 0x89, 0x08, 0x98, 0x95, 0x4F, 0xDC, 0x09, 0x88, 0xDC, 0xC5, 0x7D, 0x8E, 0x79, 0xD8,
 0xBF, 0xB7, 0x09, 0x12, 0x86, 0x60, 0xD8, 0xC0, 0xA7, 0x60, 0xF9, 0xBB, 0x87, 0x60, 0x12, 0x54,
 0x50, 0x7A, 0xF0, 0x7E, 0x19, 0x36, 0x67, 0x78, 0x1D, 0xC6, 0x2C, 0x05, 0xFE, 0xA7, 0xD2, 0x4C,
 0xEF, 0x0A, 0x90, 0x9E, 0xC1, 0x3B, 0x69, 0xD7, 0x72, 0x76, 0xC0, 0xD2, 0x90, 0xE2, 0x68, 0x31,
 0x73, 0xFC, 0xBB, 0xB2, 0x38, 0xD7, 0x1D, 0x4B, 0x53, 0xE7, 0x2D, 0xCE, 0x04, 0x50, 0xA8, 0xA8,
 0xE4, 0xC3, 0x54, 0xCD, 0x21, 0x82, 0xAE, 0xDB, 0x57, 0x64, 0xF0, 0xE7, 0x91, 0xB7, 0xE4, 0xE7,
 0x92, 0xA8, 0x6F, 0x4B, 0xC9, 0x42, 0xC3, 0x1F, 0xFE, 0xAC, 0x47, 0x03, 0x77, 0x0D, 0xBA, 0x65,
 0x78, 0x89, 0x55, 0x53, 0xC6, 0xAA, 0x6C, 0x79, 0xA3, 0x76, 0x57, 0x7E, 0x76, 0x50, 0xC4, 0x36,
 0x77, 0xF3, 0x5A, 0xD4, 0x4F, 0x31, 0x37, 0xE6, 0xAF, 0xC6, 0xCF, 0x17, 0xF1, 0x08, 0x59, 0x53,
 0x69, 0xDB, 0xEB, 0xD9, 0x00, 0x33, 0x2B, 0x14, 0x04, 0x2A, 0xF6
};

static const unsigned char s_CSC2h[] __attribute__(   (  aligned( 16 ), section( ".rodata" )  )   ) = {
 0x5D, 0x00, 0x00, 0x80, 0x00, 0x50, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x00,
 0x2C, 0xE0, 0x00, 0xD1, 0x02, 0x5F, 0x68, 0x03, 0x8F, 0xAE, 0xCC, 0x87, 0x95, 0xEA, 0xBA, 0x40,
 0x47, 0x29, 0x93, 0x10, 0xA0, 0x5C, 0x52, 0x93, 0x58, 0x3A, 0x67, 0x8F, 0x0F, 0x02, 0xC5, 0x92,
 0xE5, 0xA2, 0x35, 0xF1, 0xAB, 0x48, 0x1A, 0x2A, 0x16, 0x6D, 0xA0, 0x7C, 0x4E, 0x6C, 0xD8, 0xFF,
 0x49, 0xCE, 0xC1, 0x2F, 0x43, 0x58, 0x6E, 0xF1, 0xC0, 0x18, 0xCD, 0x61, 0x90, 0x69, 0x13, 0xDD,
 0x09, 0x4D, 0x75, 0x9F, 0xB5, 0x28, 0xCB, 0x7F, 0xAD, 0x22, 0x9F, 0x7C, 0x63, 0x52, 0xF9, 0xEB,
 0x3A, 0x7B, 0xBD, 0x15, 0xC2, 0xFD, 0x78, 0x99, 0x38, 0x35, 0xE0, 0xBF, 0xEC, 0xB1, 0x79, 0xC7,
 0xFC, 0x66, 0xCE, 0xF9, 0xDF, 0x82, 0x3D, 0x41, 0xEB, 0x54, 0x89, 0xF4, 0xF5, 0xDA, 0xF7, 0xB3,
 0x01, 0x19, 0x12, 0x43, 0xA9, 0x28, 0x86, 0x03, 0xEA, 0x5F, 0x4E, 0x96, 0x87, 0xA3, 0x2C, 0xC2,
 0x20, 0x51, 0x4A, 0x81, 0x1F, 0x24, 0x1C, 0xE2, 0x04, 0x7F, 0x72, 0x13, 0xDA, 0x98, 0xF2, 0xA4,
 0xDC, 0xB2, 0x61, 0x25, 0xC3, 0x46, 0x78, 0x86, 0x28, 0x42, 0x7F, 0x3B, 0x77, 0x0D, 0xE2, 0xDA,
 0x63, 0x88, 0x61, 0x97, 0x41, 0xF6, 0x2E, 0xD5, 0xAD, 0x61, 0x7D, 0xBB, 0xEE, 0x15, 0xF1, 0xFA,
 0x40, 0x73, 0x6B, 0x1F, 0x15, 0x44, 0xCE, 0xB1, 0x5F, 0x53, 0x17, 0x34, 0x23, 0xAD, 0x48, 0x74,
 0x22, 0xEC, 0x52, 0xD8, 0xFA, 0x88, 0x96, 0x0C, 0x5A, 0x72, 0xE3, 0x28, 0x98, 0x68, 0x72, 0x01,
 0x76, 0x2F, 0xDD, 0x81, 0x96, 0x6D, 0x7E, 0xD9, 0xB2, 0x72, 0x93, 0xD9, 0xD5, 0xC0, 0xD0, 0x24,
 0xAB, 0x28, 0x4E, 0x86, 0xE2, 0xD3, 0x41, 0x23, 0xA6, 0x8F, 0x83, 0x92, 0x53, 0x94, 0x6C, 0x56,
 0xB2, 0x96, 0xED, 0x48, 0xD1, 0xD7, 0x02, 0x09, 0x3B, 0x54, 0x70, 0x92, 0xD6, 0xE9, 0x78, 0x3C,
 0x16, 0x3E, 0xA0, 0xA9, 0x04, 0x44, 0x32, 0x24, 0x95, 0x6A, 0x2E, 0x7D, 0x3B, 0xAF, 0xD4, 0x8B,
 0xC7, 0x15, 0xAB, 0xAA, 0xEA, 0xF0, 0x8D, 0xE2, 0xBC, 0x2B, 0x4A, 0x2B, 0x36, 0x42, 0x56, 0x8E,
 0x87, 0x57, 0x2F, 0x1B, 0x5E, 0xC8, 0xDD, 0x09, 0x8F, 0xF4, 0xDD, 0x00, 0x2D, 0xF4, 0xE0, 0x17,
 0x1C, 0x19, 0xC7, 0xB0, 0xDA, 0x5D, 0x65, 0x9A, 0xB2, 0x6E, 0x8D, 0x87, 0x4F, 0xC4, 0xD7, 0x93,
 0xA8, 0x40, 0xA0, 0x45, 0x54, 0xDA, 0x98, 0x45, 0x67, 0x74, 0x56, 0xCD, 0xF9, 0xA0, 0x3C, 0x91,
 0x3A, 0x86, 0x1B, 0x41, 0xD7, 0xFF, 0xC9, 0x30, 0xA2, 0x4E, 0x0E, 0xE3, 0x26, 0xD3, 0x97, 0x7F,
 0x25, 0x74, 0xAD, 0x45, 0x3D, 0x16, 0xD9, 0x4D, 0xD9, 0xD4, 0x36, 0x07, 0x19, 0xAB, 0xFC, 0x9C,
 0x9D, 0xC7, 0xE4, 0x2F, 0xF6, 0x6F, 0x49, 0x3A, 0xA3, 0x25, 0x37, 0xA9, 0x9F, 0x7C, 0xB8, 0x08,
 0xFC, 0x15, 0x7C, 0x37, 0x6E, 0x4E, 0xCC, 0x4C, 0x9C, 0x76, 0x8B, 0x60, 0x23, 0x95, 0x34, 0x58,
 0x35, 0x95, 0x49, 0xAF, 0xCB, 0xE0, 0x7D, 0xA7, 0xD5, 0xAE, 0x7A, 0xCA, 0xCC, 0xAA, 0x1C, 0xAF,
 0x44, 0xEC, 0xF9, 0x19, 0x7E, 0x1A, 0xFE, 0xE7, 0xB8, 0x5B, 0x47, 0x0E, 0xF9, 0xB0, 0x63, 0xC6,
 0x83, 0x66, 0xF8, 0x18, 0xC4, 0x6B, 0x21, 0x4A, 0x1F, 0xF9, 0xF7, 0x84, 0x8D, 0x77, 0xFD, 0x13,
 0x00, 0x93, 0xFB, 0x61, 0xE5, 0xCD, 0x68, 0xB7, 0x4E, 0xE5, 0x47, 0x4A, 0xFD, 0x0B, 0x5D, 0xE7,
 0xF0, 0xED, 0x7B, 0xEC, 0x43, 0xE2, 0xE9, 0x32, 0x06, 0x7C, 0x78, 0xC7, 0x97, 0x28, 0x98, 0x6F,
 0xAF, 0x79, 0xF6, 0xE0, 0xC2, 0x9C, 0x81, 0x67, 0x72, 0xCC, 0x6C, 0xB1, 0x58, 0x02, 0x7D, 0xA2,
 0x96, 0x7C, 0xA9, 0x20, 0x14, 0xE9, 0x12, 0xE5, 0x7C, 0x7B, 0x65, 0x36, 0x87, 0x44, 0x17, 0x63,
 0x79, 0xEC, 0x0D, 0xAA, 0x70, 0x3A, 0xE1, 0xEE, 0x20, 0xFB, 0x7D, 0x38, 0x13, 0xB1, 0xDE, 0xE9,
 0x1A, 0x1E, 0xDA, 0x91, 0x59, 0xDE, 0x3D, 0x71, 0x33, 0x8E, 0x0E, 0x48, 0xE6, 0x58, 0x08, 0xF8,
 0x5D, 0xAA, 0x62, 0x8E, 0x4C, 0xF9, 0xAC, 0x4F, 0x60, 0xFB, 0x31, 0x83, 0x59, 0x12, 0x82, 0x11,
 0x43, 0x42, 0xC7, 0xBE, 0x25, 0xAC, 0x37, 0xE6, 0x42, 0x2C, 0x0C, 0x7D, 0x7D, 0x82, 0xE6, 0x59,
 0xD4, 0x3A, 0xC6, 0x34, 0x0F, 0xDA, 0xAF, 0x6A, 0xB9, 0x5C, 0xC0, 0xC2, 0x15, 0x1E, 0xFB, 0xDD,
 0x1F, 0x7D, 0x5C, 0xB0, 0xBF, 0x52, 0x27, 0xA7, 0x13, 0x36, 0x3A, 0xE1, 0xA1, 0xE5, 0x7C, 0x67,
 0xF2, 0x4D, 0x18, 0x9B, 0xAA, 0x40, 0x3C, 0x01, 0x11, 0x97, 0x02, 0xE0, 0x9B, 0xA2, 0x4E, 0x60,
 0xCA, 0x51, 0x5F, 0x88, 0x3D, 0x9F, 0x7D, 0x99, 0xAA, 0x89, 0x39, 0x5C, 0x22, 0x3B, 0xB9, 0x58,
 0x7C, 0x08, 0x0B, 0xFC, 0xEB, 0x6B, 0x29, 0x14, 0xB0, 0x4F, 0xA2, 0x90, 0x4D, 0x22, 0xA3, 0xD5,
 0x01, 0x92, 0xA1, 0x36, 0x76, 0x06, 0xD4, 0x89, 0x2C, 0x53, 0xC3, 0x16, 0x70, 0x65, 0xD2, 0x5C,
 0x3D, 0x5D, 0xF4, 0xF2, 0x93, 0xA6, 0x20, 0xEC, 0x09, 0x72, 0x53, 0x4E, 0x90, 0xCC, 0x01, 0x5B,
 0xB0, 0xA7, 0x84, 0x7D, 0x21, 0xBC, 0xF3, 0x8C, 0xA4, 0x11, 0x94, 0xC0, 0x73, 0x75, 0xC4, 0x15,
 0x40, 0xD3, 0x6C, 0xBB, 0xE5, 0xA3, 0x11, 0x5F, 0x90, 0x52, 0x66, 0x41, 0x60, 0x18, 0xC6, 0xB0,
 0x4E, 0xC4, 0x32, 0x09, 0x7A, 0xE6, 0x21, 0x19, 0x3D, 0xB7, 0x13, 0xD9, 0x64, 0xE0, 0xF6, 0x37,
 0x13, 0xA6, 0x26, 0x96, 0x6F, 0x24, 0x17, 0xF6, 0xE6, 0xEE, 0x7D, 0x85, 0x74, 0x7D, 0xD2, 0x31,
 0x2A, 0x19, 0x61, 0x5D, 0xAC, 0xDB, 0x37, 0xD7, 0xB8, 0x41, 0xCB, 0x66, 0x8B, 0x8C, 0xFF, 0x98,
 0x51, 0x1A, 0x67, 0xCD, 0x86, 0x4D, 0xF6, 0x67, 0xA6, 0x2F, 0x1A, 0x2E, 0x66, 0xB1, 0xBC, 0x4D,
 0x31, 0x02, 0xB8, 0x5B, 0x09, 0x6B, 0xAA, 0x2D, 0x5A, 0x96, 0x79, 0xDC, 0x14, 0x3B, 0x76, 0xE4,
 0x9B, 0x6C, 0x31, 0xFD, 0x0D, 0x19, 0xCD, 0x9C, 0xD4, 0x19, 0x13, 0xE2, 0x06, 0xC0, 0x98, 0x0C,
 0xC0, 0x83, 0xDC, 0xB2, 0x51, 0x7A, 0xA5, 0x0E, 0x10, 0x0C, 0x77, 0x26, 0x45, 0x9B, 0x91, 0xE4,
 0xDD, 0x82, 0x10, 0x5A, 0x69, 0x86, 0xFE, 0xC7, 0xDD, 0x3B, 0xD6, 0x7E, 0xB1, 0x77, 0x40, 0x22,
 0x4C, 0x07, 0x02, 0x1A, 0x5D, 0x5E, 0x0B, 0x30, 0x84, 0x5E, 0x91, 0x44, 0x5F, 0x4A, 0xDB, 0x2F,
 0x21, 0x0B, 0xAD, 0xD8, 0xEA, 0x40, 0x4B, 0x58, 0x77, 0x63, 0x8C, 0xC7, 0xC0, 0x21, 0x20, 0x0F,
 0x96, 0x97, 0xE1, 0xEA, 0x2E, 0xB2, 0x5A, 0xF9, 0x30, 0xB3, 0xA1, 0xF6, 0xDE, 0x4F, 0x75, 0x4B,
 0xA2, 0xBA, 0x4D, 0x0B, 0x75, 0xFD, 0xF2, 0xA9, 0x66, 0x39, 0x21, 0x3C, 0xEE, 0x0E, 0xA9, 0x96,
 0xAC, 0x41, 0xF2, 0x33, 0x67, 0xD3, 0xF8, 0xE6, 0x2C, 0xCB, 0x5A, 0x32, 0xAF, 0xB4, 0xF7, 0xBC,
 0xD4, 0xBB, 0x3E, 0x4D, 0xE5, 0x07, 0x93, 0x26, 0xEE, 0xF5, 0x25, 0xC7, 0x93, 0x5C, 0xAF, 0x52,
 0x55, 0x86, 0x0E, 0x96, 0xB3, 0x8E, 0x3A, 0x8B, 0x7C, 0xBF, 0x21, 0x4C, 0xD3, 0x54, 0xC7, 0x0F,
 0x94, 0x6F, 0x62, 0xCA, 0x91, 0x4E, 0x58, 0x8F, 0x28, 0x3C, 0x76, 0xC4, 0x40, 0x66, 0xE3, 0xC2,
 0x5E, 0xC4, 0x43, 0x27, 0x1D, 0xAE, 0x77, 0x61, 0xA6, 0x93, 0x85, 0x75, 0x19, 0x0A, 0xFE, 0xDF,
 0x11, 0xC9, 0xA1, 0xEF, 0x8B, 0x9C, 0xC7, 0x32, 0x59, 0xB1, 0x28, 0xEE, 0x95, 0x48, 0x49, 0x52,
 0x81, 0xFA, 0x79, 0x84, 0xBE, 0x47, 0xED, 0xE2, 0x90, 0x4C, 0xCF, 0x8C, 0xD4, 0xA3, 0xD4, 0xE9,
 0x17, 0x3A, 0x55, 0xB6, 0x7E, 0x97, 0xDC, 0x8E, 0x0B, 0x90, 0x28, 0x2F, 0x2F, 0xAE, 0xE0, 0xF4
};

static const unsigned char s_CSC2v[] __attribute__(   (  aligned( 16 ), section( ".rodata" )  )   ) = {
 0x5D, 0x00, 0x00, 0x80, 0x00, 0x60, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x32, 0x80,
 0x2C, 0xE0, 0x09, 0x0B, 0x11, 0x2C, 0x27, 0x04, 0xB1, 0x4C, 0xD4, 0xFC, 0xE3, 0xD7, 0x6A, 0x13,
 0xD6, 0xE9, 0xE1, 0x01, 0xBA, 0x64, 0xF8, 0x0A, 0x89, 0x10, 0x9B, 0x18, 0x2D, 0xB6, 0x63, 0xB4,
 0xEA, 0x25, 0x1C, 0x3F, 0x03, 0x7D, 0x92, 0x84, 0x16, 0xB5, 0x77, 0x93, 0xA3, 0xE0, 0xB3, 0xE2,
 0xD1, 0xAF, 0x3C, 0x6B, 0x6E, 0xF7, 0xD6, 0xB0, 0x7A, 0x90, 0xBB, 0xC4, 0x42, 0x1D, 0xF8, 0x02,
 0xD4, 0x36, 0xB4, 0xAA, 0x98, 0x9F, 0x19, 0x46, 0x9D, 0xFE, 0xC7, 0xCE, 0x51, 0x7A, 0xC6, 0x33,
 0x09, 0x19, 0xCE, 0x7F, 0xF8, 0x5B, 0xEC, 0x5C, 0xB8, 0x87, 0xA3, 0xD5, 0xF4, 0x4B, 0x5B, 0x01,
 0x99, 0xB2, 0xA7, 0xB6, 0x33, 0x48, 0x22, 0xD6, 0x16, 0xC8, 0x80, 0xFC, 0x95, 0x35, 0x21, 0x1E,
 0x27, 0x5E, 0xB7, 0xC9, 0x6C, 0x80, 0x63, 0x94, 0x75, 0x6D, 0xEE, 0x2D, 0xB2, 0xBE, 0xC5, 0x96,
 0x89, 0x1B, 0xAA, 0x72, 0x26, 0xE4, 0x0C, 0x1E, 0x38, 0x28, 0x79, 0x66, 0xEC, 0x5E, 0xC1, 0x3B,
 0x81, 0xD7, 0xD5, 0xFF, 0xF9, 0xA2, 0xD5, 0x66, 0x1E, 0x4F, 0xC9, 0x14, 0x2D, 0xFD, 0x79, 0xA1,
 0xF9, 0x88, 0x79, 0x19, 0x06, 0x0E, 0xD0, 0x26, 0x87, 0x9B, 0xE5, 0x9F, 0xF0, 0x21, 0x55, 0xD9,
 0xD9, 0xD5, 0x8E, 0xEF, 0x93, 0xC3, 0xC4, 0xB7, 0xDA, 0xC0, 0xD1, 0x9E, 0x8E, 0xA8, 0x49, 0x8A,
 0x0D, 0xD5, 0xDE, 0x5A, 0xDF, 0xA0, 0x0D, 0x42, 0x02, 0x01, 0xCF, 0x78, 0xCC, 0xEC, 0x1E, 0x9A,
 0x9D, 0x9F, 0x15, 0x08, 0xB7, 0x1D, 0xC0, 0x8D, 0x26, 0x94, 0xCA, 0xD6, 0x21, 0xE6, 0xE9, 0x08,
 0xA7, 0x25, 0x60, 0x65, 0x3B, 0x1C, 0x92, 0xF2, 0x4D, 0xBD, 0xBD, 0x2A, 0x38, 0x33, 0x7E, 0x26,
 0x01, 0xA9, 0x2A, 0xAA, 0x1E, 0xA3, 0xEA, 0x16, 0xBE, 0xC2, 0xE4, 0x77, 0x9D, 0xC4, 0x72, 0x30,
 0x6E, 0xCF, 0xD2, 0x39, 0xD2, 0x7C, 0x3A, 0x6C, 0x12, 0xA9, 0xE5, 0x28, 0x55, 0xBC, 0xF8, 0xA2,
 0x06, 0x9D, 0x57, 0xF4, 0x11, 0x21, 0x32, 0xCA, 0x78, 0x58, 0x3F, 0x68, 0xEF, 0x2D, 0x2A, 0x66,
 0x0C, 0xEA, 0xFD, 0xBC, 0x06, 0x93, 0x52, 0x7F, 0x9A, 0xC0, 0xB9, 0x14, 0x8B, 0x0B, 0x29, 0x65,
 0x44, 0x8B, 0xB7, 0x23, 0x74, 0x6A, 0x5C, 0x3D, 0x87, 0xC4, 0xE7, 0x77, 0xBC, 0xAA, 0x0D, 0xBA,
 0x61, 0xFD, 0xE4, 0xD3, 0x61, 0x41, 0x0F, 0x4A, 0x91, 0xB2, 0x4E, 0x5D, 0x99, 0x1B, 0x18, 0x78,
 0xA5, 0xE8, 0x87, 0x32, 0xCA, 0x61, 0x91, 0xC6, 0x4C, 0xCF, 0x1D, 0x77, 0x46, 0x49, 0xE5, 0x34,
 0x20, 0xE8, 0xE8, 0xEC, 0xEE, 0x87, 0xA6, 0x3D, 0xBB, 0xA9, 0xF5, 0xB6, 0x5A, 0xB6, 0x4B, 0x16,
 0x77, 0x8C, 0x66, 0xE8, 0xAF, 0xA4, 0xAF, 0xBB, 0x48, 0x69, 0x54, 0x66, 0x4A, 0xA9, 0x71, 0x47,
 0xA7, 0xFA, 0x53, 0x2B, 0xB5, 0xBA, 0x16, 0xAF, 0x5B, 0x9B, 0x8B, 0x5E, 0x9B, 0x9D, 0x40, 0x39,
 0x53, 0xE4, 0x0D, 0xEE, 0x7C, 0x3A, 0xEC, 0xD9, 0xB6, 0x37, 0xE0, 0x92, 0xE0, 0xBC, 0x48, 0xAC,
 0xE9, 0xF1, 0x61, 0xA4, 0x6C, 0xED, 0x93, 0xA3, 0xF5, 0xDD, 0x72, 0x96, 0x9D, 0x6A, 0x7C, 0x8E,
 0xC5, 0xF7, 0x01, 0xD9, 0x23, 0xF0, 0x9E, 0x82, 0x0F, 0x8B, 0x4F, 0x11, 0xB1, 0x7D, 0x26, 0x34,
 0x2C, 0x47, 0x58, 0xDB, 0xD4, 0x06, 0x63, 0xF2, 0xC6, 0x81, 0x8B, 0x09, 0xB5, 0x8B, 0x2B, 0xBF,
 0x51, 0x75, 0x11, 0xCA, 0x5C, 0xFD, 0x7A, 0x2B, 0xB7, 0x48, 0xC5, 0x17, 0xA6, 0xF0, 0x65, 0xF3,
 0xA4, 0x50, 0x55, 0x60, 0xAB, 0xC7, 0x54, 0xD6, 0x37, 0xAF, 0x86, 0x8B, 0x8E, 0x80, 0xF7, 0x5F,
 0x12, 0xA5, 0x9E, 0xE2, 0x1B, 0xD0, 0x7A, 0xD9, 0x58, 0xD1, 0x34, 0xB3, 0x7A, 0x71, 0x34, 0x99,
 0x55, 0x67, 0x90, 0x15, 0x3D, 0xBB, 0x50, 0x3D, 0x9C, 0x9A, 0x79, 0x40, 0x10, 0x12, 0x48, 0x7B,
 0x78, 0x5E, 0x59, 0x12, 0xAE, 0xC7, 0xF0, 0xB3, 0x57, 0x49, 0x7F, 0x59, 0xF3, 0x6D, 0x7E, 0x7D,
 0x64, 0xA6, 0xDD, 0x64, 0x3E, 0x60, 0x17, 0x4C, 0x09, 0x59, 0xD9, 0x7B, 0xC7, 0xB8, 0x6A, 0xB8,
 0x4B, 0xBD, 0xAB, 0xB1, 0x7F, 0xA7, 0x3C, 0x3E, 0x93, 0xD7, 0x85, 0x57, 0x91, 0x62, 0x58, 0xE9,
 0xCA, 0x39, 0x87, 0xC4, 0x73, 0x1C, 0x3E, 0x48, 0x5F, 0x00, 0xFB, 0x02, 0x37, 0x1E, 0xB3, 0x8E,
 0xAF, 0x45, 0x6A, 0x04, 0xED, 0xAF, 0x2F, 0x3D, 0x24, 0x8B, 0x75, 0xF0, 0x6A, 0x07, 0xA0, 0x8F,
 0x5E, 0xB6, 0x80, 0x02, 0xA9, 0xCC, 0xF2, 0xCD, 0x90, 0xDB, 0x26, 0xE0, 0x26, 0x08, 0x52, 0x63,
 0x20, 0x83, 0xE2, 0x83, 0x21, 0x66, 0x51, 0x21, 0x76, 0xF5, 0x56, 0x82, 0x8A, 0x1F, 0xF2, 0xFC,
 0x34, 0x8B, 0x03, 0xE5, 0xE4, 0x62, 0x73, 0x06, 0x4F, 0x12, 0xB7, 0xD8, 0x5D, 0x3F, 0xD7, 0x76,
 0x9F, 0x3F, 0x32, 0xFC, 0xA7, 0xEF, 0xE8, 0x4D, 0x21, 0x8C, 0x80, 0x3D, 0x8B, 0x29, 0xD8, 0xE5,
 0x9B, 0x0F, 0x07, 0x2E, 0x22, 0xF8, 0xA5, 0xB2, 0x7B, 0xF6, 0xFC, 0x61, 0x4D, 0x6E, 0x6B, 0xBA,
 0xA8, 0x16, 0x79, 0xD5, 0x63, 0x6F, 0x93, 0x55, 0x37, 0xE1, 0xC3, 0x59, 0xA9, 0x6B, 0x4F, 0x8D,
 0x7C, 0xC7, 0x01, 0xCF, 0xE8, 0xE9, 0x1B, 0x84, 0x55, 0x8A, 0x5A, 0x42, 0xE5, 0xC4, 0x5F, 0x98,
 0x64, 0xE8, 0xE0, 0x0C, 0xC2, 0x72, 0xA6, 0x9A, 0x41, 0x94, 0xC9, 0x66, 0x34, 0x91, 0x07, 0x5C,
 0x82, 0xB3, 0x20, 0x74, 0xAC, 0x9A, 0x28, 0x92, 0x07, 0x37, 0x9E, 0xBB, 0x4B, 0x86, 0x93, 0x28,
 0x33, 0xAD, 0x23, 0x62, 0xDF, 0xB9, 0x19, 0x7C, 0x2C, 0xA0, 0x48, 0xB3, 0x03, 0xB2, 0xC8, 0xC0,
 0x89, 0x5B, 0x3A, 0xF8, 0xCC, 0x45, 0x65, 0xCB, 0x06, 0x52, 0xFC, 0x4A, 0x90, 0x49, 0x01, 0xA9,
 0xCC, 0x4B, 0xDD, 0x75, 0x39, 0x6C, 0x05, 0xC3, 0x69, 0x01, 0xF7, 0x57, 0xB3, 0x50, 0xB2, 0x8C,
 0x07, 0x9E, 0xEC, 0x11, 0x61, 0x60, 0x22, 0xD7, 0x3D, 0xD1, 0xD2, 0x51, 0x5A, 0x20, 0xE0, 0xDE,
 0xA0, 0x53, 0x3E, 0x1E, 0x3C, 0xCF, 0x87, 0x67, 0xBE, 0x85, 0x39, 0x2F, 0xFD, 0x70, 0x6F, 0xF0,
 0xBC, 0x8C, 0x3E, 0xBF, 0x22
};

static const unsigned char s_CSC4[] __attribute__(   (  aligned( 16 ), section( ".rodata" )  )   ) = {
 0x5D, 0x00, 0x00, 0x80, 0x00, 0x50, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3A, 0x00,
 0x2C, 0xDD, 0xF9, 0x1C, 0x02, 0xC1, 0x63, 0x04, 0xFD, 0xB0, 0xDE, 0x47, 0x39, 0x4E, 0x39, 0x05,
 0xEB, 0xC0, 0xFA, 0x85, 0x11, 0xC2, 0x33, 0x57, 0x6C, 0xE0, 0xDF, 0x1C, 0x69, 0x1C, 0xE8, 0xE4,
 0x04, 0x2F, 0xC5, 0x6C, 0x88, 0x81, 0x11, 0xDC, 0x97, 0xAA, 0x08, 0x6C, 0x9E, 0x75, 0xC5, 0x28,
 0x1C, 0x0A, 0x24, 0x2D, 0x23, 0xFC, 0xC9, 0xB2, 0x42, 0x18, 0x73, 0xF7, 0x7F, 0x36, 0x4A, 0x43,
 0x8B, 0xBE, 0x95, 0x01, 0x7D, 0xA1, 0x15, 0x85, 0xBC, 0x6F, 0x43, 0xA7, 0x73, 0x08, 0x3C, 0x77,
 0x1C, 0xD9, 0xF8, 0x2E, 0x3F, 0x48, 0xA3, 0xD2, 0x0B, 0x62, 0x4D, 0xC6, 0x6F, 0x50, 0x1B, 0xE8,
 0x45, 0x43, 0x20, 0xD3, 0x70, 0x81, 0x72, 0x28, 0xB8, 0xA4, 0xF5, 0x04, 0x3F, 0x89, 0x0A, 0xA0,
 0x7B, 0x72, 0xF5, 0x24, 0x34, 0x1F, 0x12, 0x30, 0x20, 0x53, 0xE8, 0x45, 0x98, 0xFC, 0x99, 0x43,
 0x8E, 0x52, 0x37, 0xD1, 0x91, 0xBC, 0x4B, 0x90, 0x56, 0xBB, 0xA0, 0x0C, 0xF4, 0xAB, 0x87, 0x9C,
 0xE5, 0xBA, 0xCD, 0xC9, 0x1B, 0x3D, 0x2F, 0xA8, 0xDD, 0x3E, 0xF5, 0x6B, 0x3B, 0xDA, 0x34, 0xAF,
 0x46, 0x5B, 0x96, 0x0C, 0xE8, 0x6D, 0xC5, 0x57, 0x60, 0x38, 0x48, 0x5F, 0xB3, 0x67, 0xAE, 0x0B,
 0x4A, 0x4C, 0x96, 0x58, 0xF1, 0x8F, 0x59, 0x83, 0xD4, 0x9B, 0xA7, 0xC3, 0xA6, 0x0A, 0x3E, 0x6A,
 0x0E, 0xB4, 0x24, 0x01, 0x15, 0x0C, 0x81, 0x28, 0x63, 0xE8, 0x64, 0xEC, 0xBF, 0xBD, 0xE4, 0x5C,
 0x8E, 0x54, 0xA5, 0xE0, 0xC5, 0x68, 0x14, 0xA5, 0xBA, 0xC3, 0x23, 0xD9, 0xD4, 0x3E, 0x91, 0x15,
 0x4D, 0x12, 0xC3, 0x46, 0x1C, 0x7B, 0x67, 0x2D, 0xB6, 0x22, 0x29, 0xFD, 0x32, 0x2C, 0x80, 0x27,
 0x41, 0xC8, 0x47, 0xD8, 0xE8, 0x1A, 0x12, 0xE4, 0x93, 0x77, 0xA7, 0x45, 0xCB, 0x1C, 0xC0, 0xAB,
 0xC1, 0x7C, 0x45, 0x5F, 0x4E, 0x45, 0xA7, 0x87, 0x0F, 0x57, 0x73, 0xE7, 0x72, 0x1C, 0x7E, 0x7D,
 0x3C, 0x43, 0xA0, 0xA2, 0xA6, 0xA4, 0x11, 0x3E, 0x8C, 0xB9, 0x3B, 0x15, 0x15, 0x67, 0x7E, 0x0A,
 0x59, 0xDD, 0x9F, 0xF8, 0x7E, 0xEC, 0xA7, 0x59, 0x44, 0x82, 0x46, 0x2C, 0xC7, 0xAF, 0xF8, 0xEB,
 0x34, 0x6D, 0x9E, 0xD1, 0xCC, 0x08, 0xE6, 0x63, 0x3F, 0x15, 0x56, 0x55, 0x23, 0x13, 0x59, 0xBC,
 0x70, 0x2D, 0x7A, 0x43, 0xF6, 0x96, 0x81, 0xA1, 0xBA, 0xAC, 0x53, 0x78, 0x78, 0xEF, 0xDE, 0x11,
 0xB0, 0x49, 0xCB, 0x62, 0xB6, 0x58, 0xFD, 0x31, 0xA9, 0x77, 0x33, 0xB2, 0xFC, 0x44, 0xD4, 0x4F,
 0x10, 0xE4, 0x40, 0x10, 0x76, 0x09, 0xEA, 0xAC, 0x29, 0xA5, 0xC1, 0x50, 0xC7, 0x4F, 0x5E, 0xF0,
 0x85, 0x23, 0xC3, 0x4E, 0x09, 0xEA, 0xAA, 0xD9, 0x16, 0x9E, 0x86, 0xED, 0x5D, 0xC1, 0x9B, 0x20,
 0xFA, 0x13, 0x87, 0x2C, 0xA2, 0x5B, 0x88, 0x4F, 0x31, 0x33, 0x97, 0xD2, 0xAC, 0x60, 0xED, 0xF7,
 0xB8, 0xFD, 0xEA, 0x5A, 0x7E, 0xAF, 0xE4, 0x7A, 0xA3, 0x1A, 0xAE, 0x18, 0xB7, 0xCB, 0xF3, 0xAF,
 0x3D, 0xE2, 0x07, 0x0D, 0xDA, 0x40, 0x06, 0xC1, 0x5B, 0x0F, 0x52, 0x28, 0x1C, 0x45, 0x43, 0xD0,
 0xA7, 0x8E, 0xC5, 0x24, 0xE7, 0x21, 0xDE, 0xE6, 0x28, 0xA4, 0x5F, 0xB4, 0xEA, 0xF5, 0x95, 0xBB,
 0x1E, 0x5C, 0x03, 0x5F, 0x20, 0x52, 0xD7, 0x49, 0x65, 0xCB, 0x09, 0x89, 0xC4, 0x64, 0x38, 0xF4,
 0xF7, 0x49, 0x17, 0xD7, 0x88, 0xD5, 0x1E, 0x64, 0x03, 0xCF, 0x16, 0x91, 0xF4, 0xB9, 0x9B, 0x17,
 0xB3, 0x44, 0x77, 0xEF, 0xAE, 0xD9, 0x1E, 0x08, 0xEE, 0x26, 0xF2, 0x9C, 0xE0, 0xE9, 0x84, 0x02,
 0x0F, 0x1C, 0xAD, 0x91, 0x9B, 0x11, 0x56, 0xE2, 0x1A, 0x47, 0xE1, 0x1D, 0x63, 0xA3, 0x9B, 0x47,
 0x47, 0x6D, 0xF3, 0xD4, 0x12, 0xD8, 0x3A, 0xFC, 0xFA, 0x39, 0xEF, 0x96, 0x78, 0x88, 0xA7, 0x7C,
 0xA7, 0x14, 0x09, 0x77, 0xDC, 0x8A, 0xA1, 0x13, 0x08, 0x98, 0x35, 0xE3, 0x73, 0xF7, 0x77, 0x97,
 0x64, 0x12, 0xEB, 0x6A, 0xC8, 0x77, 0x39, 0xE0, 0x28, 0x20, 0xE6, 0xF1, 0xBA, 0x17, 0x27, 0xC5,
 0xCE, 0x3E, 0xDF, 0x40, 0x09, 0xB2, 0x97, 0x0F, 0x69, 0x04, 0xE4, 0x21, 0xB6, 0xF7, 0x30, 0xFE,
 0xB7, 0xF1, 0xFB, 0x6C, 0x5C, 0xC5, 0x5F, 0xAE, 0x5C, 0x51, 0x19, 0x6D, 0x28, 0x7C, 0x80, 0xB4,
 0x06, 0xEE, 0x4A, 0x40, 0xF8, 0x18, 0x7B, 0xD4, 0x0A, 0x58, 0xB0, 0xE3, 0x42, 0x3E, 0x7E, 0x8E,
 0x0E, 0x16, 0xC4, 0xA1, 0xB0, 0xA0, 0x66, 0xEC, 0x6B, 0xA7, 0x2A, 0x77, 0x83, 0xD3, 0x09, 0x13,
 0x97, 0xA8, 0xB9, 0x92, 0x67, 0xFB, 0x5F, 0x78, 0x7E, 0xBF, 0x45, 0x2B, 0x08, 0xDD, 0xA3, 0x65,
 0x5E, 0xBC, 0x91, 0xA4, 0x19, 0x1F, 0x86, 0x08, 0xBC, 0x86, 0x2E, 0xC2, 0xD1, 0xFB, 0x47, 0xAB,
 0x5C, 0xEB, 0x4F, 0x74, 0x8C, 0xE3, 0xBE, 0x71, 0xA6, 0x66, 0x51, 0x2B, 0x13, 0xBF, 0x58, 0x08,
 0xFE, 0x01, 0x0B, 0x58, 0x64, 0xA1, 0x55, 0x12, 0x0D, 0x6B, 0x4C, 0x74, 0x7E, 0xC9, 0x9A, 0xAB,
 0xA8, 0x91, 0x11, 0x4E, 0x2F, 0xDE, 0x0E, 0x1F, 0x6B, 0x3B, 0xCA, 0xC2, 0xC7, 0xA5, 0xE5, 0xA7,
 0x5B, 0x59, 0x16, 0xC6, 0x86, 0x52, 0x30, 0x7E, 0xF9, 0x8D, 0x9B, 0x1F, 0x30, 0xAF, 0x17, 0x93,
 0x56, 0x8C, 0xFB, 0xFF, 0x0E, 0xB9, 0xCA, 0x31, 0xAA, 0x62, 0xBC, 0xE4, 0x2F, 0x32, 0xDA, 0xA3,
 0x1F, 0x2F, 0x24, 0x45, 0x61, 0x52, 0x2B, 0x82, 0x19, 0x16, 0x67, 0x15, 0x8A, 0xB1, 0xD7, 0x8E,
 0xDB, 0x21, 0x4A, 0xBE, 0x37, 0x02, 0xDD, 0x67, 0xF9, 0x40, 0x31, 0x96, 0x71, 0xC7, 0xAA, 0x43,
 0x3C, 0xF4, 0xE2, 0xAC, 0x4A, 0x21, 0x12, 0xFC, 0x03, 0x9A, 0x07, 0x7F, 0x87, 0x3D, 0x76, 0x49,
 0x02, 0x3A, 0x42, 0x80, 0xC0, 0xE3, 0x63, 0xF2, 0xF9, 0xB1, 0xD4, 0x21, 0xE3, 0x32, 0x19, 0x28,
 0x50, 0xA2, 0x4E, 0x74, 0x44, 0x72, 0xAF, 0xED, 0xF2, 0x30, 0x08, 0xBD, 0xED, 0xBF, 0x34, 0xEC,
 0xBC, 0x87, 0x70, 0x67, 0xC5, 0x2E, 0x3D, 0x52, 0xF8, 0x88, 0xD0, 0xE3, 0x4E, 0xA2, 0x85, 0x0E,
 0x7E, 0x4D, 0xFE, 0x33, 0x4A, 0xE5, 0xEE, 0xD3, 0x0D, 0x05, 0xF9, 0xBD, 0x28, 0xCE, 0xC7, 0xB2,
 0x57, 0xBA, 0x70, 0xE8, 0x0C, 0xC2, 0x30, 0x92, 0x44, 0xF8, 0x43, 0x63, 0x4B, 0xA3, 0xA0, 0x70,
 0x97, 0xAB, 0x9A, 0x84, 0x46, 0x49, 0xD8, 0x10, 0x6A, 0xF7, 0x38, 0x95, 0xA0, 0xFF, 0x07, 0x9D,
 0x74, 0x14, 0xAF, 0x2B, 0x8D, 0xAD, 0x26, 0x0D, 0xE1, 0xD3, 0x54, 0x91, 0x85, 0x3B, 0x0A, 0xEF,
 0xA6, 0x06, 0xE5, 0x1D, 0xFF, 0x9B, 0x44, 0x76, 0x5F, 0x83, 0xFD, 0x3D, 0xDC, 0xBA, 0xA9, 0xAA,
 0x08
};

const SMS_LZMAData g_JPEGData[ 5 ] __attribute__(   (  section( ".rodata" )  )   ) = {
 { 2016, sizeof ( s_IDCT  ), s_IDCT  },
 { 1232, sizeof ( s_CSC1  ), s_CSC1  },
 { 2128, sizeof ( s_CSC2h ), s_CSC2h },
 { 1632, sizeof ( s_CSC2v ), s_CSC2v },
 { 1872, sizeof ( s_CSC4  ), s_CSC4  }
};
