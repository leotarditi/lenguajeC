#include "recode57.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <stdbool.h>

enum encoding bom_to_encoding(uint8_t *bom) {

    if(bom[0] == 0xFF && bom[1] == 0xFE){

        if (bom [2] == 0x00 && bom[3] == 0x00) return UTF32LE;

        return UTF16LE;
    }
    else if(bom[0] == 0x00 && bom[1] == 0x00 && bom[2] == 0xFE && bom[3] == 0xFF) {
        return UTF32BE;
    }
    else if (bom[0] == 0xFE && bom[1] == 0xFF) {
        return UTF16BE;
    }

    // Si no tiene BOM, se asume UTF-8.
    return UTF8;
}

size_t write_bom(enum encoding enc, uint8_t *buf) {
    size_t b = 0;
    if (enc != UTF8){
        switch(enc){
            case UTF32LE:
                buf[b++] = 0xFF;
                buf[b++] = 0xFE;
                buf[b++] = 0x00;
                buf[b++] = 0x00;
                break;
            case UTF32BE:
                buf[b++] = 0x00;
                buf[b++] = 0x00;
                buf[b++] = 0xFE;
                buf[b++] = 0xFF;
                break;
             case UTF16BE:
                buf[b++] = 0xFE;
                buf[b++] = 0xFF;
                break;
             case UTF16LE:
                buf[b++] = 0xFF;
                buf[b++] = 0xFE;
                break;
        }
    }
    return b;
}

bool has_codepoint(enum encoding enc, uint8_t *buf, size_t n) {
    switch (enc) {
        case UTF32BE:
        case UTF32LE:
            return (n >= 4);
        case UTF16BE:
            return (n >= 4 || ( n >= 2 && ( (buf[0] < 0xD8) || (buf[0] > 0xDB) ) ));
        case UTF16LE:
            return (n >= 4 || ( n >= 2 && ( (buf[1] < 0xD8) || (buf[1] > 0xDB) ) ));
        case UTF8:
            return (n >= 4 || (n >= 3 && buf[0] <= 0xEF) ||
                    (n >= 2 && buf[0] <= 0xDF) || (n >= 1 && buf[0] <= 0x7F));
        default:
            return false;
    }
}

size_t read_codepoint(enum encoding enc, uint8_t *buf, size_t n, codepoint *dest) {
    size_t b = 0;
    if(has_codepoint(enc, &buf[b], n)) {
        uint32_t cp = 0;
        switch(enc){
            case UTF32LE:
                cp |= buf[b++];
                cp |= buf[b++] << 8;
                cp |= buf[b++] << 16;
                cp |= buf[b++] << 24;
                break;
            case UTF32BE:
                cp |= buf[b++] << 24;
                cp |= buf[b++] << 16;
                cp |= buf[b++] << 8;
                cp |= buf[b++];
                break;
            case UTF16LE:
                //Veo si es el high surrogate
                if(buf[b + 1] >> 2 != 0x36){
                    cp |= buf[b++];
                    cp |= buf[b++] << 8;
                } else {
                    cp |= buf[b++] << 10;
                    cp |= (buf[b++] & 0x3) << 18;
                    cp |= buf[b++];
                    cp |= (buf[b++] & 0x3) << 8;
                    cp += 0x10000;
                }
                break;
            case UTF16BE:
                if(buf[b] >> 2 != 0x36){
                    cp |= buf[b++] << 8;
                    cp |= buf[b++];
                } else {
                    cp |= (buf[b++] & 0x3) << 18;
                    cp |= buf[b++] << 10;
                    cp |= (buf[b++] & 0x3) << 8;
                    cp |= buf[b++];
                    cp += 0x10000;
                }
                break;
            case UTF8:
                if (buf[b] < 0x80){
                    cp |= buf[b++];
                }
                else if(buf[b] < 0xE0){
                    cp |= (buf[b++] & 0x1F) << 6;
                    cp |= buf[b++] & 0x3F;
                }
                else if(buf[b] < 0xF0){
                    cp |= (buf[b++] & 0x0F) << 12;
                    cp |= (buf[b++] & 0x3F) << 6;
                    cp |= buf[b++] & 0x3F;
                } else {
                    cp |= (buf[b++] & 0x7) << 18;
                    cp |= (buf[b++] & 0x3F) << 12;
                    cp |= (buf[b++] & 0x3F) << 6;
                    cp |= buf[b++] & 0x3F;
                }
                break;
        }
        *dest = cp;
    }
    return b;
}

size_t write_codepoint(enum encoding enc, codepoint cp, uint8_t *outbuf) {
        size_t b = 0;
        switch (enc) {
            case UTF32LE:
                outbuf[b++] = cp & 0xFF;
                outbuf[b++] = (cp >> 8) & 0xFF;
                outbuf[b++] = (cp >> 16) & 0xFF;
                outbuf[b++] = (cp >> 24) & 0xFF;
                break;
            case UTF32BE:
                outbuf[b++] = (cp >> 24) & 0xFF;
                outbuf[b++] = (cp >> 16) & 0xFF;
                outbuf[b++] = (cp >> 8) & 0xFF;
                outbuf[b++] = cp & 0xFF;
                break;
            case UTF16LE:
                if (cp <= 0xFFFF){
                    outbuf[b++] = cp & 0xFF;
                    outbuf[b++] = cp >> 8;
                } else {
                    uint32_t aux = cp - 0x10000;
                    outbuf[b++] = (aux >> 10) & 0xFF;
                    outbuf[b++] = 0xD8 | (aux >> 18);
                    outbuf[b++] = aux & 0xFF;
                    outbuf[b++] = 0xDC | ((aux >> 8) & 0x3);
                    }
                break;
            case UTF16BE:
                if (cp <= 0xFFFF) {
                    outbuf[b++] = cp >> 8;
                    outbuf[b++] = cp & 0xFF;
                } else {
                    uint32_t aux = cp - 0x10000;
                    outbuf[b++] = 0xD8 | (aux >> 18);
                    outbuf[b++] = (aux >> 10) & 0xFF;
                    outbuf[b++] = 0xDC | ((aux >> 8) & 0x3);
                    outbuf[b++] = aux & 0xFF;
                    }
                break;
            case UTF8:
                if(cp <= 0x7F) {
                    outbuf[b++] = cp;
                }
                else if(cp <= 0x7FF) {
                    outbuf[b++] = 0xC0 | (cp >> 6);
                    outbuf[b++] = 0x80 | (cp & 0x3F);
                }
                else if(cp <= 0xFFFF){
                    outbuf[b++] = 0xE0 | (cp >> 12);
                    outbuf[b++] = 0x80 | ((cp >> 6) & 0x3F);
                    outbuf[b++] = 0x80 | (cp & 0x3F);
                } else {
                    outbuf[b++] = 0xF0 | (cp >> 18);
                    outbuf[b++] = 0x80 | ((cp >> 12) & 0x3F);
                    outbuf[b++] = 0x80 | ((cp >> 6) & 0x3F);
                    outbuf[b++] = 0x80 | (cp & 0x3F);
                }
                break;
        }
        return b;
}