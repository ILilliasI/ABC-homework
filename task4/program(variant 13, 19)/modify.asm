extern printf
extern fprintf
extern OutPlant

extern TREE
extern BUSH
extern FLOWER


; // Вывод содержимого контейнера в файл
global OutModifiedContainer
OutModifiedContainer:
section .data
    numFmt   db    "%d:",0
    fmt      db    "Average: %f", 10,0
    .len     dq    0
    .count   dq    0
    .c       dq    0
    .average dq    0.0
    .curr    dq    0.0
    .one     dq    1.0
section .bss
    .pcont  resq    1   ; Адрес контейнера
    .FILE   resq    1   ; Указатель на файл
section .text
push rbp
mov rbp, rsp

    mov     [.pcont], rdi
    mov     [.len],   esi
    mov     [.FILE],  rdx

    mov     qword[.c], 0
    pxor    xmm5, xmm5
   
.countSize:
    mov     rax, qword[.count]
    cmp     rax, qword[.len]
    je      .next
    
    inc     qword[.count]
    addsd   xmm5, [.one]
    
    jmp     .countSize
 
.next:
    ; Считаем среднее для признака
    mov     rdi, [.pcont]
    mov     rsi, [.len],   
    mov     rdx, [.FILE] 
    call    CalculateAverage
    movsd   xmm4, xmm1
    divsd   xmm4, xmm5
    movsd   [.average], xmm4
    
    mov     rdi, [.FILE]
    mov     rsi, fmt
    movsd   xmm0, [.average]
    add     rax, 1
    call    fprintf
    
    mov     rbx, [.len]         ; Число растений
    xor     ecx, ecx            ; Счетчик растений = 0
    mov     rsi, [.FILE]

.loop:
    cmp     ecx, ebx
    jge     .return        ; Перебрали все растения

    push    rbx
    push    rcx

        
    mov     rdi, [.pcont]
    call    CalculateRatioOfVowelsToAllLetters
    movsd   [.curr], xmm2

    movsd   xmm4, [.average]
    movsd   xmm2, [.curr]
    
    comisd  xmm2, xmm4
    jb      .donotprint

    ; Вывод номера растения 
    mov     rdi, [.FILE]
    mov     rsi, numFmt
    mov     edx, [.c]
    xor     rax, rax
    call    fprintf
    
    inc qword[.c]

    ; Вывод текущего растения
    mov     rdi, [.pcont]
    mov     rsi, [.FILE]
    call    OutPlant
    
    
.donotprint:
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

;----------------------------------------------
; Поиск частного от деления числам гласных букв в названии на общую длину названия.
global CalculateRatioOfVowelsToAllLetters
CalculateRatioOfVowelsToAllLetters:
section .data
    .vowels_count   dq    0
    .letters_count  dq    0
section .bss
    .pplant         resq  1     ; Адрес растения
section .text
push    rbp
mov     rbp, rsp

    mov     qword[.vowels_count],  0
    mov     qword[.letters_count], 0
    add     rdi, 4
    mov     [.pplant], rdi
.loop:
    mov     rax, [.pplant]
    add     rax, [.letters_count]
    cmp     byte [rax], 0x00
    je      .return
    
    inc     qword [.letters_count]
    cmp     byte [rax], 0x61
    je      .increase
    
    cmp     byte [rax], 0x65
    je      .increase
    
    cmp     byte [rax], 0x69
    je      .increase
    
    cmp     byte [rax], 0x6F
    je      .increase
    
    cmp     byte [rax], 0x75
    je      .increase
    
    jmp     .loop
.increase:
    inc     qword[.vowels_count]
    jmp     .loop
.return:  
    movsd   xmm2, [.vowels_count] 
    ; Если кол-во букв = 0
    cmp     qword[.letters_count], 0
    je      .leave
    divsd   xmm2, [.letters_count]

leave
ret

.leave:
    movsd   xmm2, qword[.letters_count]
     
leave
ret

;----------------------------------------------
; Вычисление среднего арифметического для всех элементов контейнера, полученное с
; использованием функции, общей для всех альтернатив.
global CalculateAverage
CalculateAverage:
section .data
    .zero   dq  0
    .fmt    db  "%f", 0
    .len    dq  0
    .spec   db  "--%f--", 0
    .sum    dq  0.0
section .bss
    .pcont  resq    1   ; Адрес контейнера
    .FILE   resq    1   ; Указатель на файл
section .text
push rbp
mov rbp, rsp

    pxor    xmm1, xmm1
    movsd   [.sum], xmm1
    mov     [.pcont], rdi
    mov     [.len],   rsi
    mov     [.FILE],  rdx

    mov     rbx, rsi            ; Число растений
    xor     ecx, ecx            ; Счетчик растений = 0
    mov     rsi, rdx
.loop:
    cmp     ecx, ebx
    jge     .return             ; Перебрали все растения

    push    rbx
    push    rcx

    mov     rdi, [.pcont]  
    call    CalculateRatioOfVowelsToAllLetters
    movsd   xmm1, [.sum]
    addsd   xmm1, xmm2
    movsd   [.sum], xmm1

    pop     rcx
    pop     rbx
    inc     ecx  

    mov     rax, [.pcont]
    add     rax, 29           ; Адрес следущего растения
    mov     [.pcont], rax
    jmp     .loop
.return:
    movsd   xmm1, [.sum]
    
leave
ret
