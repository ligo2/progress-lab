.global asmfile

.section asmfile, "ax"

.extern cFun

.global _start
_start:
    mov x0, #11
    mov x1, #22
    mov x2, #33
    bl cFun

.end
