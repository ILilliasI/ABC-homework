;------------------------------------------------------------------------------
; main.asm - содержит главную функцию,
; обеспечивающую простое тестирование
;------------------------------------------------------------------------------
; main.asm

global  TREE
global  BUSH
global  FLOWER

%include "macros.mac"

section .data
    TREE        dd  1
    BUSH        dd  2
    FLOWER      dd  3
    oneDouble   dq  1.0
    erMsg1      db "Incorrect number of arguments = %d: ",10,0
    rndGen      db "-n",0
    fileGen     db "-f",0
    errMessage1 db  "incorrect command line!", 10,"  Waited:",10
                db  "     command -f infile outfile01 outfile02",10,"  Or:",10
                db  "     command -n number outfile01 outfile02",10,0
    errMessage2 db  "incorrect qualifier value!", 10,"  Waited:",10
                db  "     command -f infile outfile01 outfile02",10,"  Or:",10
                db  "     command -n number outfile01 outfile02",10,0
    len         dd  0           ; Количество элементов в массиве
section .bss
    argc        resd    1
    num         resd    1
    sum         resq    1
    start       resq    1       ; Начало отсчета времени
    delta       resq    1       ; Интервал отсчета времени
    startTime   resq    2       ; Начало отсчета времени
    endTime     resq    2       ; Конец отсчета времени
    deltaTime   resq    2       ; Интервал отсчета времени
    ifst        resq    1       ; Открываемый файл для чтения растений
    ofst1       resq    1       ; Открываемый файл для записи контейнера
    ofst2       resq    1       ; Открываемый файл для записи модифицированного контейнера
    cont        resb    290000  ; Массив используемый для хранения данных

section .text
    global main
main:
    mov rbp, rsp;
push rbp
mov rbp,rsp

    mov dword [argc], edi 
    mov r12, rdi 
    mov r13, rsi
    
.next1:
    PrintStrLn "Start", [stdout]
    mov rdi, rndGen
    mov rsi, [r13+8]    ; Второй аргумент командной строки
    call strcmp
    cmp rax, 0          ; Строки равны "-n"
    je .next2
    mov rdi, fileGen
    mov rsi, [r13+8]    ; Второй аргумент командной строки
    call strcmp
    cmp rax, 0          ; Строки равны "-f"
    je .next3
    PrintStrBuf errMessage2, [stdout]
    jmp .return
.next2:
    ; Генерация случайных фигур
    mov rdi, [r13+16]
    call atoi
    mov [num], eax
    PrintInt [num], [stdout]
    PrintStrLn "", [stdout]
    mov eax, [num]
    cmp eax, 1
    jl .fall1
    cmp eax, 10000
    jg .fall1
    ; Начальная установка генератора случайных чисел
    xor     rdi, rdi
    xor     rax, rax
    call    time
    mov     rdi, rax
    xor     rax, rax
    call    srand
    ; Заполнение контейнера случайными фигурами
    mov     rdi, cont
    mov     rsi, len
    mov     edx, [num] 
    call    InRndContainer
    jmp .task1

.next3:
    ; Получение растений из файла
    FileOpen [r13+16], "r", ifst
    ; Заполнение контейнера растениями из файла
    mov     rdi, cont           ; Адрес контейнера
    mov     rsi, len            ; Адрес для установки числа элементов
    mov     rdx, [ifst]         ; Указатель на файл
    xor     rax, rax
    call    InContainer         ; Ввод данных в контейнер
    FileClose [ifst]

.task1:
    ; Вычисление времени старта
    mov rax, 228  
    xor edi, edi 
    lea rsi, [startTime]
    syscall 
    
    FileOpen [r13+24], "w", ofst1
    PrintStrLn "Filled container:", [ofst1]
    PrintContainer cont, [len], [ofst1]
    FileClose [ofst1]
    
.task2:
    FileOpen [r13+32], "w", ofst2
    PrintStrLn "Modified container:", [ofst2]
    PrintModifiedContainer cont, [len], [ofst2]
    FileClose [ofst2]

    ; Вычисление времени завершения
    mov rax, 228
    xor edi, edi 
    lea rsi, [endTime]
    syscall

    ; Получение времени работы
    mov rax, [endTime]
    sub rax, [startTime]
    mov rbx, [endTime+8]
    mov rcx, [startTime+8]
    cmp rbx, rcx
    jge .subNanoOnly
    
    dec rax
    add rbx, 1000000000
.subNanoOnly:
    sub rbx, [startTime+8]
    mov [deltaTime], rax
    mov [deltaTime+8], rbx

    PrintStr "Calculaton time = ", [stdout]
    PrintLLUns [deltaTime], [stdout]
    PrintStr " sec, ", [stdout]
    PrintLLUns [deltaTime+8], [stdout]
    PrintStr " nsec", [stdout]
    PrintStr 10, [stdout]

    PrintStrLn "Stop", [stdout]
    jmp .return
.fall1:
    PrintStr "incorrect numer of plants = ", [stdout]
    PrintInt [num], [stdout]
    PrintStrLn ". Set 0 < number <= 10000", [stdout]
.return:
leave
ret
