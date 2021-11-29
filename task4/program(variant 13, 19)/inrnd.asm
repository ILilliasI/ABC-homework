extern printf
extern rand

extern TREE
extern BUSH
extern FLOWER

;----------------------------------------------
; // Генерация рандомного числа в заданных пределах
%macro Random   1          
    xor     rax, rax    
    call    rand              ; Запуск генератора случайных чисел
    xor     rdx, rdx
    mov     rcx, %1
    idiv    qword [rcx]       ; Остаток от деления
    mov     rax, rdx
    add     rax, 1 
%endmacro


;----------------------------------------------
; // Генерация рандомного числа, определяющего длину имени
%macro RandomName   1          
    xor     rax, rax    
    call    rand              ; Запуск генератора случайных чисел
    xor     rdx, rdx
    mov     rcx, %1
    idiv    qword [rcx]       ; Остаток от деления
    mov     rax, rdx
%endmacro

; Генерация рандомного имени
global GenerateName
GenerateName:
section .data
    .count      dq    0
    .size       dq    0
    .name       dq    26
section .text
    mov     [.count], rdi
    mov     [.size], rsi
.loop:
    mov     rax, qword[.size]
    cmp     rax, qword[.count]
    je      .return
    ; Генерация рандомной латинской буквы
    RandomName  .name
    cmp     eax, 0
    je      .letter0
    cmp     eax, 1
    je       .letter1
    cmp     eax, 2
    je      .letter2
    cmp     eax, 3
    je      .letter3
    cmp     eax, 4
    je      .letter4
    cmp     eax, 5
    je      .letter5
    cmp     eax, 6
    je      .letter6
    cmp     eax, 7
    je      .letter7
    cmp     eax, 8
    je      .letter8
    cmp     eax, 9
    je      .letter9
    cmp     eax, 10
    je      .letter10
    cmp     eax, 11
    je      .letter11
    cmp     eax, 12
    je      .letter12
    cmp     eax, 13
    je      .letter13
    cmp     eax, 14
    je      .letter14
    cmp     eax, 15
    je      .letter15
    cmp     eax, 16
    je      .letter16
    cmp     eax, 17
    je      .letter17
    cmp     eax, 18
    je      .letter18
    cmp     eax, 19
    je      .letter19
    cmp     eax, 20
    je      .letter20
    cmp     eax, 21
    je       .letter21
    cmp     eax, 22
    je      .letter22
    cmp     eax, 23
    je      .letter23
    cmp     eax, 24
    je      .letter24
    cmp     eax, 25
    je      .letter25
.letter0:
    mov     byte[rbx], 97
    inc     qword[.count]
    add     rbx, 1
    jmp     .loop
.letter1:
    mov     byte[rbx], 98
    inc     qword[.count]
    add     rbx, 1
    jmp     .loop
.letter2:
    mov     byte[rbx], 99
    inc     qword[.count]
    add     rbx, 1
    jmp     .loop
.letter3:
    mov     byte[rbx], 100
    inc     qword[.count]
    add     rbx, 1
    jmp     .loop
.letter4:
    mov     byte[rbx], 101
    inc     qword[.count]
    add     rbx, 1
    jmp     .loop
.letter5:
    mov     byte[rbx], 102
    inc     qword[.count]
    add     rbx, 1
    jmp     .loop
.letter6:
    mov     byte[rbx], 103
    inc     qword[.count]
    add     rbx, 1
    jmp     .loop
.letter7:
    mov     byte[rbx], 104
    inc     qword[.count]
    add     rbx, 1
    jmp     .loop
.letter8:
    mov     byte[rbx], 105
    inc     qword[.count]
    add     rbx, 1
    jmp     .loop
.letter9:
    mov     byte[rbx], 106
    inc     qword[.count]
    add     rbx, 1
    jmp     .loop
.letter10:
    mov     byte[rbx], 107
    inc    qword[.count]
    add     rbx, 1
    jmp     .loop
.letter11:
    mov     byte[rbx], 108
    inc     qword[.count]
    add     rbx, 1
    jmp     .loop
.letter12:
    mov     byte[rbx], 109
    inc     qword[.count]
    add     rbx, 1
    jmp     .loop
.letter13:
    mov     byte[rbx], 110
    inc     qword[.count]
    add     rbx, 1
    jmp     .loop
.letter14:
    mov     byte[rbx], 111
    inc     qword[.count]
    add     rbx, 1
    jmp     .loop
.letter15:
    mov     byte[rbx], 112
    inc    qword[.count]
    add rbx, 1
    jmp .loop
.letter16:
    mov     byte[rbx], 113
    inc     qword[.count]
    add     rbx, 1
    jmp     .loop
.letter17:
    mov     byte[rbx], 114
    inc     qword[.count]
    add     rbx, 1
    jmp     .loop
.letter18:
    mov     byte[rbx], 115
    inc     qword[.count]
    add     rbx, 1
    jmp     .loop
.letter19:
    mov     byte[rbx], 116
    inc     qword[.count]
    add     rbx, 1
    jmp     .loop
.letter20:
    mov     byte[rbx], 117
    inc     qword[.count]
    add     rbx, 1
    jmp     .loop
.letter21:
    mov     byte[rbx], 118
    inc     qword[.count]
    add     rbx, 1
    jmp     .loop
.letter22:
    mov     byte[rbx], 119
    inc     qword[.count]
    add     rbx, 1
    jmp     .loop
.letter23:
    mov     byte[rbx], 120
    inc     qword[.count]
    add     rbx, 1
    jmp     .loop
.letter24:
    mov     byte[rbx], 121
    inc     qword[.count]
    add     rbx, 1
    jmp     .loop
.letter25:
    mov     byte[rbx], 122
    inc     qword[.count]
    add     rbx, 1
    jmp     .loop
.return:
    mov     byte[rbx], 0x00
leave
ret

;----------------------------------------------
; // Случайный ввод параметров дерева
global InRndTree
InRndTree:
section .data
    .age        dq    10000
    .count      dq    0
    .namesize   dq    20
    .name       dq    26
    .size       dq    0
section .bss
    .ptree      resq  1   ; Адрес дерева
section .text
push    rbp
mov     rbp, rsp

    mov     [.ptree], rdi
    ; Генерация параметров дерева
    mov     rbx, [.ptree]
    Random  .age
    mov     [rbx+21], eax
    ; Генерация размера имени
    Random  .namesize
    mov     [.size], eax
    mov     qword[.count], 0
    ; Генерация имени
    mov     rdi, [.count]
    mov     rsi, [.size]
    call    GenerateName
leave
ret

global InRndBush
InRndBush:
section .data
    .count      dq    0
    .month      dq    12
    .namesize   dq    20
    .name       dq    26
    .size       dq    0
section .bss
    .pbush      resq  1   ; Адрес куста

section .text
push    rbp
mov     rbp, rsp

    mov     [.pbush], rdi
    ; Генерация параметров куста
    mov     rbx, [.pbush]
    Random  .month
    mov     [rbx+21], eax
    ; Генерация размера имени
    Random   .namesize
    mov     [.size], eax
    mov     qword[.count], 0
    ; Генерация имени
    mov     rdi, [.count]
    mov     rsi, [.size]
    call    GenerateName
leave
ret

global InRndFlower
InRndFlower:
section .data
    .type       dq    3
    .name       dw    26
    .count      dq    0
    .namesize   dq    20
    .size       dq    0
section .bss
    .pflower    resq  1   ; Адрес цветка
section .text
push    rbp
mov     rbp, rsp

    mov     [.pflower], rdi
    ; Генерация параметров цветка
    mov     rbx, [.pflower]
    Random  .type
    mov     [rbx+21], eax   
    ; Генерация размера имени
    Random  .namesize
    mov     [.size], eax
    mov     qword[.count], 0
    ; Генерация имени
    mov     rdi, [.count]
    mov     rsi, [.size]
    call    GenerateName
leave
ret

;----------------------------------------------
;// Случайный ввод обобщенного растения
global InRndPlant
InRndPlant:
section .data
    .type  db  3
section .bss
    .pplant  resq  1   ; Адрес растения
section .text
push    rbp
mov     rbp, rsp

    mov [.pplant], rdi
    ; Формирование признака растения
    mov     [.pplant], rdi
    Random   .type

    mov     rdi, [.pplant]
    mov     [rdi], eax
    cmp     eax, [TREE]
    je      .treeInrnd
    cmp     eax, [BUSH]
    je      .bushInRnd
    cmp     eax, [FLOWER]
    je      .flowerInRnd
    xor     eax, eax
    jmp     .return
.treeInrnd:
    ; Генерация дерева
    add     rdi, 4
    call    InRndTree
    mov     eax, 1 
    jmp     .return
.bushInRnd:
    ; Генерация куста
    add     rdi, 4
    call    InRndBush
    mov     eax, 1 
    jmp     .return
.flowerInRnd:
    ; Генерация цветка
    add     rdi, 4
    call    InRndFlower
    mov     eax, 1 
.return:
leave
ret

;----------------------------------------------
;// Случайный ввод содержимого контейнера
global InRndContainer
InRndContainer:
section .bss
    .pcont  resq    1   ; Адрес контейнера
    .plen   resq    1   ; Адрес для сохранения числа введенных элементов
    .psize  resd    1   ; Число порождаемых элементов
section .text
push    rbp
mov     rbp, rsp

    mov     [.pcont], rdi
    mov     [.plen], rsi
    mov     [.psize], edx
    xor     ebx, ebx       ; Число растений = 0
.loop:
    cmp     ebx, edx
    jge     .return
    ; Сохранение рабочих регистров
    push    rdi
    push    rbx
    push    rdx

    call    InRndPlant     ; Ввод растения
    cmp     rax, 0         ; Проверка успешности ввода
    jle     .return        ; Выход, если признак меньше или равен 0

    pop     rdx
    pop     rbx
    inc     rbx

    pop     rdi
    add     rdi, 29         ; Адрес следующего растения

    jmp     .loop
.return:
    mov     rax, [.plen]  
    mov     [rax], ebx 
leave
ret
