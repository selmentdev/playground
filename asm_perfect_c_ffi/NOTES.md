# Testing C to C++ function forwarding

## x86_64 - with omit frame pointer

| test case                       | result        |
|---------------------------------|---------------|
| C function to C++ free function | 8 byte spill  |
| C function to C++ method        | tail call     |

```S
Corydale__Drawing__Canvas__DrawRectangle_Free:
	pushq	%rax
	callq	Corydale::Drawing::DrawRectangle(Corydale::Drawing::Canvas&, int, int, int, int)
	xorl	%eax, %eax
	popq	%rcx
	retq

Corydale__Drawing__Canvas__DrawRectangle_Method:
	jmp	Corydale::Drawing::Canvas::DrawRectangle(int, int, int, int)
```

## x86_64 - with no omit frame pointer

| test case                       | result                      |
|---------------------------------|-----------------------------|
| C function to C++ free function | 8 byte spill                |
| C function to C++ method        | tail call with cdecl adjust |

```S
Corydale__Drawing__Canvas__DrawRectangle_Free:
	pushq	%rbp
	movq	%rsp, %rbp
	callq	Corydale::Drawing::DrawRectangle(Corydale::Drawing::Canvas&, int, int, int, int)
	xorl	%eax, %eax
	popq	%rbp
	retq

Corydale__Drawing__Canvas__DrawRectangle_Method:
	pushq	%rbp
	movq	%rsp, %rbp
	popq	%rbp
	jmp	Corydale::Drawing::Canvas::DrawRectangle(int, int, int, int) # TAILCALL
```

## aarch64 - with omit frame pointer

| test case                       | result        |
|---------------------------------|---------------|
| C function to C++ free function | 8 byte spill  |
| C function to C++ method        | tail call     |

```S
Corydale__Drawing__Canvas__DrawRectangle_Free:
	str	x30, [sp, #-16]!
	bl	Corydale::Drawing::DrawRectangle(Corydale::Drawing::Canvas&, int, int, int, int)
	mov	w0, wzr
	ldr	x30, [sp], #16
	ret

Corydale__Drawing__Canvas__DrawRectangle_Method:
	b	Corydale::Drawing::Canvas::DrawRectangle(int, int, int, int)
```

## aarch64 - with no omit frame pointer

| test case                       | result        |
|---------------------------------|---------------|
| C function to C++ free function | 8 byte spill  |
| C function to C++ method        | tail call     |

```S
Corydale__Drawing__Canvas__DrawRectangle_Free:
	stp	x29, x30, [sp, #-16]!
	mov	x29, sp
	bl	Corydale::Drawing::DrawRectangle(Corydale::Drawing::Canvas&, int, int, int, int)
	mov	w0, wzr
	ldp	x29, x30, [sp], #16
	ret

Corydale__Drawing__Canvas__DrawRectangle_Method:
	b	Corydale::Drawing::Canvas::DrawRectangle(int, int, int, int)
```


## riscv64 - with omit-frame-pointer

| test case                       | result        |
|---------------------------------|---------------|
| C function to C++ free function | adjust + call |
| C function to C++ method        | tail call     |

```S
Corydale__Drawing__Canvas__DrawRectangle_Free:
	addi	sp, sp, -16
	sd	ra, 8(sp)
	mv	a1, zero
	mv	a2, zero
	mv	a3, zero
	mv	a4, zero
	call	Corydale::Drawing::DrawRectangle(Corydale::Drawing::Canvas&, int, int, int, int)
	mv	a0, zero
	ld	ra, 8(sp)
	addi	sp, sp, 16
	ret

Corydale__Drawing__Canvas__DrawRectangle_Method:
	tail	Corydale::Drawing::Canvas::DrawRectangle(int, int, int, int)
```

## riscv64 - with no-omit-frame-pointer

| test case                       | result             |
|---------------------------------|--------------------|
| C function to C++ free function | adjust + call      |
| C function to C++ method        | adjust + tail call |

```S
Corydale__Drawing__Canvas__DrawRectangle_Free:
	addi	sp, sp, -16
	sd	ra, 8(sp)
	sd	s0, 0(sp)
	addi	s0, sp, 16
	mv	a1, zero
	mv	a2, zero
	mv	a3, zero
	mv	a4, zero
	call	Corydale::Drawing::DrawRectangle(Corydale::Drawing::Canvas&, int, int, int, int)
	mv	a0, zero
	ld	s0, 0(sp)
	ld	ra, 8(sp)
	addi	sp, sp, 16
	ret

Corydale__Drawing__Canvas__DrawRectangle_Method:
	addi	sp, sp, -16
	sd	ra, 8(sp)
	sd	s0, 0(sp)
	addi	s0, sp, 16
	ld	s0, 0(sp)
	ld	ra, 8(sp)
	addi	sp, sp, 16
	tail	Corydale::Drawing::Canvas::DrawRectangle(int, int, int, int)
```
