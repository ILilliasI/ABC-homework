extern printf
extern fscanf

extern TREE
extern BUSH
extern FLOWER

;----------------------------------------------
; // Ввод параметров дерева из файла
global InTree
InTree:
section .data
    .infmt  db     "%s%d",0
section .bss
    .FILE   resq    1   ; Временное хранение указателя на файл
    .ptree  resq    1   ; Адрес дерева
section .text
push    rbp
mov     rbp, rsp

    ; Сохранение принятых аргументов
    mov     [.ptree], rdi     
    mov     [.FILE], rsi

    ; Ввод куста из файла
    mov     rdi, [.FILE]
    mov     rsi, .infmt         
    mov     rdx, [.ptree]       
    mov     rcx, [.ptree]
    add     rcx, 21    
    mov     rax, 0        
    call    fscanf

leave
ret

; // Ввод параметров куста из файла
global InBush
InBush:
section .data
    .infmt  db     "%s%d",0
section .bss
    .FILE   resq    1    ; Временное хранение указателя на файл
    .bush   resq    1   ; Адрес куста
section .text
push    rbp
mov     rbp, rsp

    ; Сохранение принятых аргументов
    mov     [.bush], rdi
    mov     [.FILE], rsi

    ; Ввод куста из файла
    mov     rdi, [.FILE]
    mov     rsi, .infmt
    mov     rdx, [.bush]
    mov     rcx, [.bush]
    add     rcx, 21 
    mov     rax, 0
    call    fscanf

leave
ret

; // Ввод параметров цветка из файла
global InFlower
InFlower:
section .data
    .infmt  db     "%s%d",0
section .bss
    .FILE    resq    1   ; Временное хранение указателя на файл
    .flower  resq    1   ; Адрес цветка
section .text
push    rbp
mov     rbp, rsp

    ; Сохранение принятых аргументов
    mov     [.flower], rdi
    mov     [.FILE], rsi

    ; Ввод цветка из файла
    mov     rdi, [.FILE]
    mov     rsi, .infmt
    mov     rdx, [.flower]
    mov     rcx, [.flower]
    add     rcx, 21 
    mov     rax, 0
    call    fscanf

leave
ret

; // Ввод параметров обобщенного растения из файла
global InPlant
InPlant:
section .data
    .tagFormat   db     "%d",0
    .tagOutFmt   db     "Tag is: %d",10,0
section .bss
    .FILE       resq    1   ; Временное хранение указателя на файл
    .pplant     resq    1   ; Адрес растения
    .plantTag   resd    1   ; Признак растения
section .text
push    rbp
mov     rbp, rsp

    ; Сохранение принятых аргументов
    mov     [.pplant], rdi         
    mov     [.FILE], rsi

    ; Чтение признака куста и его обработка
    mov     rdi, [.FILE]
    mov     rsi, .tagFormat
    mov     rdx, [.pplant]
    xor     rax, rax
    call    fscanf

    mov     rcx, [.pplant]
    mov     eax, [rcx]
    cmp     eax, [TREE]
    je      .treeIn
    cmp     eax, [BUSH]
    je      .bushIn
    cmp     eax, [FLOWER]
    je      .flowerIn
    xor     eax, eax    ; Некорректный признак - обнуление кода возврата
    jmp     .return
.treeIn:
    ; Ввод дерева
    mov     rdi, [.pplant]
    add     rdi, 4
    mov     rsi, [.FILE]
    call    InTree
    mov     rax, 1      ; Код возврата - true
    jmp     .return
.bushIn:
    ; Ввод куста
    mov     rdi, [.pplant]
    add     rdi, 4
    mov     rsi, [.FILE]
    call    InBush
    mov     rax, 1      ; Код возврата - true
    jmp     .return
.flowerIn:
    ; Ввод цветка
    mov     rdi, [.pplant]
    add     rdi, 4
    mov     rsi, [.FILE]
    call    InFlower
    mov     rax, 1      ; Код возврата - true
.return:

leave
ret

; // Ввод содержимого контейнера из указанного файла
global InContainer
InContainer:
section .bss
    .pcont  resq    1   ; Адрес контейнера
    .plen   resq    1   ; Адрес для сохранения числа введенных элементов
    .FILE   resq    1   ; Указатель на файл
section .text
push    rbp
mov     rbp, rsp

    mov     [.pcont], rdi
    mov     [.plen], rsi
    mov     [.FILE], rdx
    xor     rbx, rbx        ; Число растений = 0
    mov     rsi, rdx        ; Перенос указателя на файл
.loop:
    push    rdi
    push    rbx

    mov     rsi, [.FILE]
    mov     rax, 0 
    call    InPlant         ; Ввод растения
    cmp     rax, 0          ; Проверка успешности ввода
    jle     .return         ; Выход, если признак меньше или равен 0

    pop     rbx
    inc     rbx

    pop     rdi
    add     rdi, 29         ; Адрес следующего растения

    jmp     .loop
.return:
    mov     rax, [.plen]    ; Перенос указателя на длину
    mov     [rax], ebx
leave
ret

