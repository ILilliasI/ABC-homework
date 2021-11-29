extern printf
extern fprintf

extern TREE
extern BUSH
extern FLOWER

;----------------------------------------------
;// Вывод параметров дерева в файл
global OutTree
OutTree:
section .data
     .count     dq   0
    .formatname db   "%c", 0
    .formatage  db   ", age = %ld", 10, 0
    .outfmt     db   "It is a tree: name = " , 0
    
section .bss
    .ptree  resq  1       ; Адрес дерева
    .FILE   resq  1       ; Временное хранение указателя на файл
section .text
push    rbp
mov     rbp, rsp

    ; Сохранение принятых аргументов
    mov     [.ptree], rdi
    mov     [.FILE], rsi

    ; Вывод информации о дереве в файл
    mov     rdi, [.FILE]
    mov     rsi, .outfmt
    call    fprintf
    mov     qword [.count], 0
.loop:
    mov     rax, [.ptree]
    add     rax, [.count]
    cmp     byte [rax], 0x00
    je      .return
    
    mov     rdi, [.FILE]
    mov     rsi, .formatname 
    mov     rax, [.ptree]  
    add     rax, [.count] 
    mov     edx, [rax]
    mov     rax, 0 
    call    fprintf
    inc     qword [.count]
    jmp     .loop
.return: 
    mov     rdi, [.FILE]
    mov     rsi, .formatage 
    mov     rax, [.ptree] 
    add     rax, 21
    mov     edx, [rax]   
    mov     rax, 0                  
    call    fprintf

leave
ret

;----------------------------------------------
; // Вывод параметров куста в файл
global OutBush
OutBush:
section .data
    .count      dq   0
    .formatname db   "%c", 0
    .formatage  db   ", flowering month = %d", 10, 0
    .form       db   "%d", 0
    .outfmt     db   "It is a bush: name = " , 0
section .bss
    .pbush  resq  1       ; Адрес куста
    .FILE   resq  1       ; Временное хранение указателя на файл
section .text
push    rbp
mov     rbp, rsp

    ; Сохранени принятых аргументов
    mov     [.pbush], rdi
    mov     [.FILE], rsi 

    ; Вывод информации о кусте в файл  
    mov     rdi, [.FILE]
    mov     rsi, .outfmt
    call    fprintf
    mov     qword [.count], 0
.loop:
    mov     rax, [.pbush]
    add     rax, [.count]
    cmp     byte [rax], 0x00
    je      .return
    
    mov     rdi, [.FILE]
    mov     rsi, .formatname 
    mov     rax, [.pbush]  
    add     rax, [.count] 
    mov     edx, [rax] 
    mov     rax, 0 
    call    fprintf
    inc     qword [.count]
    jmp     .loop
.return:  
    mov     rdi, [.FILE]
    mov     rsi, .formatage
    mov     rax, [.pbush] 
    add     rax, 21 
    mov     edx, [rax]   
    mov     rax, 0                  
    call    fprintf

leave
ret

;----------------------------------------------
; // Вывод параметров цветка в файл
global OutFlower
OutFlower:
section .data
    .count      dq   0
    .formatname db   "%c", 0
    .formatage  db   ", type = %d", 10, 0
    .form       db   "%d", 0
    .outfmt     db   "It is a flower: name = " , 0
section .bss
    .pflower  resq  1     ; Адрес цветка
    .FILE     resq  1       ; Временное хранение указателя на файл
section .text
push    rbp
mov     rbp, rsp

    ; Сохранение принятых аргументов
    mov     [.pflower], rdi
    mov     [.FILE], rsi 

    ; Вывод информации о цветке в файл  
    mov     rdi, [.FILE]
    mov     rsi, .outfmt
    call    fprintf
    mov qword [.count], 0
.loop:
    mov rax, [.pflower]
    add rax, [.count]
    cmp byte [rax], 0x00
    je .return
    
    mov     rdi, [.FILE]
    mov     rsi, .formatname 
    mov     rax, [.pflower]  
    add     rax, [.count] 
    mov     edx, [rax] 
    mov     rax, 0 
    call    fprintf
    inc     qword [.count]
    jmp     .loop
.return:  
    mov     rdi, [.FILE]
    mov     rsi, .formatage
    mov     rax, [.pflower] 
    add     rax, 21 
    mov     edx, [rax]   
    mov     rax, 0                  
    call    fprintf

leave
ret

;----------------------------------------------
; // Вывод параметров текущего растения в файл
global OutPlant
OutPlant:
section .data
    .erPlant db "Incorrect plant!",10,0
section .text
push    rbp
mov     rbp, rsp

    mov     eax, [rdi]
    cmp     eax, [TREE]
    je      treeOut
    cmp     eax, [BUSH]
    je      bushOut
    cmp     eax, [FLOWER]
    je      flowerOut
    mov     rdi, .erPlant
    mov     rax, 0
    call    fprintf
    jmp     return
treeOut:
    ; Вывод дерева
    add     rdi, 4
    call    OutTree
    jmp     return
bushOut:
    ; Вывод куста
    add     rdi, 4
    call    OutBush
    jmp     return
flowerOut:
    ; Вывод цветка
    add     rdi, 4
    call    OutFlower
return:
leave
ret

;----------------------------------------------
; // Вывод содержимого контейнера в файл
global OutContainer
OutContainer:
section .data
    numFmt  db  "%d: ",0
section .bss
    .pcont  resq    1   ; Адрес контейнера
    .len    resd    1   ; Адрес для сохранения числа введенных элементов
    .FILE   resq    1   ; Указатель на файл
section .text
push rbp
mov rbp, rsp

    mov     [.pcont], rdi
    mov     [.len],   esi
    mov     [.FILE],  rdx

    mov     rbx, rsi            ; Число растений
    xor     ecx, ecx            ; Счетчик растений = 0
    mov     rsi, rdx
.loop:
    cmp     ecx, ebx
    jge     .return             ; Перебрали все растения

    push    rbx
    push    rcx

    ; Вывод номера растения
    mov     rdi, [.FILE]
    mov     rsi, numFmt
    mov     edx, ecx 
    xor     rax, rax
    call    fprintf

    ; Вывод текущего растения
    mov     rdi, [.pcont]
    mov     rsi, [.FILE]
    call    OutPlant

    pop     rcx
    pop     rbx
    inc     ecx  

    mov     rax, [.pcont]
    add     rax, 29         ; Адрес следущего растения
    mov     [.pcont], rax
    jmp     .loop
.return:

leave
ret

