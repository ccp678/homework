stack segment stack
dw 512 dup(?)
stack ends
data segment
X dw 2
Y dw 350
Z dw 20
V dw 2
data ends
code segment 
assume cs:code,ds:data,ss:stack
start: mov ax,data
mov ds,ax

mov ax,X
mov bx,Y
imul bx   ;x*y
mov bx,Z 
add ax,bx  ;x*y+Z
adc dx,0
sub ax,720 
sbb dx,0  ;x*y+Z-720
mov bx,ax
mov cx,dx
mov ax,V
cwd
sub ax,bx
sbb dx,cx ;(v-(x*y+Z-720))
mov bx,X
idiv bx   ;(v-(x*y+Z-720))/z

mov ah,4ch
int 21h

code ends
end start