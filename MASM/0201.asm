stack segment stack
dw 512 dup(?)
stack ends
data segment
X dw 2
Y dw 2
data ends
code segment 
assume cs:code,ds:data,ss:stack
start: mov ax,data
mov ds,ax

mov ax,X
push ax
mov bx,Y
push bx
call f
add sp,4
mov cx,4
mov bx,ax
again:
rol bx,1
rol bx,1
rol bx,1
rol bx,1
mov dx,bx
and dx,000fh
cmp dl,0ah
jnb next1
add dl,30h
jmp next
next1:
sub dl,0ah
add dl,41h
next:
mov ah,02h
int 21h
loop again

mov ah,4ch
int 21h


f PROC
    push bp 
    mov bp,sp
    push bx
    push cx
    push dx
    mov ax,[bp+6]
    mov cx,ax
    mov bx,[bp+4]
    imul bx
    add ax,cx
    adc dx,0
    sub ax,bx
    sbb dx,0
    pop dx
    pop cx
    pop bx
    pop bp
    ret
f ENDP
code ends
end start