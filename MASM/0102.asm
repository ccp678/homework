stack segment stack
dw 512 dup(?)
stack ends
data segment

msg0 db 'The 0 Bit is 1',0dh,0ah,'$'
msg1 db 'The 1 Bit is 1',0dh,0ah,'$'
msg2 db 'The 2 Bit is 1',0dh,0ah,'$'
msg3 db 'The 3 Bit is 1',0dh,0ah,'$'
msg4 db 'The 4 Bit is 1',0dh,0ah,'$'
msg5 db 'The 5 Bit is 1',0dh,0ah,'$'
msg6 db 'The 6 Bit is 1',0dh,0ah,'$'
msg7 db 'The 7 Bit is 1',0dh,0ah,'$'
table dw disp0,disp1,disp2,disp3,disp4,disp5,disp6,disp7

data ends
code segment 
assume cs:code,ds:data,ss:stack
start: mov ax,data
mov ds,ax

mov bl,01h
mov si,0
mov cx,8
again: 
shr bl,1
jnc next
jmp table[si]
start2:
mov ah,9
int 21h

next:
add si,2
loop again

mov ah,4ch
int 21h

disp0: mov dx,offset msg0
jmp start2
disp1: mov dx,offset msg1
jmp start2
disp2: mov dx,offset msg2
jmp start2
disp3: mov dx,offset msg3
jmp start2
disp4: mov dx,offset msg4
jmp start2
disp5: mov dx,offset msg5
jmp start2
disp6: mov dx,offset msg6
jmp start2
disp7: mov dx,offset msg7
jmp start2

code ends
end start