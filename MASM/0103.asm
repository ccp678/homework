stack segment stack
dw 512 dup(?)
stack ends
data segment
stu dw 50 dup(20)
data ends
code segment 
assume cs:code,ds:data,ss:stack
start: mov ax,data
mov ds,ax

mov cx,50
mov ax,0
mov si,0
again:
add ax,stu[si]
add si,2
loop again
mov bl,50
div bl
mov bl,al
mov cl,4
shr bl,cl
and al,0fh

cmp bl,0ah
jnb next1
add bl,30h
jmp done1
next1:
sub bl,0ah
add bl,41h
done1:

cmp al,0ah
jnb next2
add al,30h
jmp done2
next2:
sub al,0ah
add al,41h
done2:

xchg al,bl
mov ah,02h
mov dl,al
int 21h  ;会改变al,bl
mov dl,bl
mov ah,02h
int 21h


mov ah,4ch
int 21h

code ends
end start