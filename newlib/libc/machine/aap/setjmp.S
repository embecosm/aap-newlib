/* Implementations of setjmp and longjmp for AAP

   Copyright (c) 2015 Embecosm Limited <www.embecosm.com>
   All rights reserved.

   Contributor Jeremy Bennett <jeremy.bennett@embecosm.com>

   This code forms part of newlib for AAP

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

     * Redistributions of source code must retain the above copyright notice,
       this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
     * Neither the name of Embecosm nor the names of its contributors may be
       used to endorse or promote products derived from this software without
       specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS;
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE. */


/*! Set a jump point for a long jump in the future.

    Setjmp stores all its caller-saved registers in a buffer. The trouble is we
    don't know how many registers any particular implementation has. For now we
    deal with this by assuming the maximum.

    @note  For now this only works with 64Kw of code space.  We will need a
 	   version for long jump and return.

    @param $r2  Address of the buffer.
    @return  Zero always for this direct invocation. */

	.global setjmp
	.type   setjmp,@function
setjmp:
	stw	[$r2,0], $r0		/* Link register */
	stw	[$r2,2], $r1		/* Stack pointer */

	/* Skip argument/results registers R2 - R7 */
	/* Skip call clobbered registers in range R8 - R63 */

	stw	[$r2,4], $r10
	stw	[$r2,6], $r13
	stw	[$r2,8], $r16
	stw	[$r2,10], $r19
	stw	[$r2,12], $r22
	stw	[$r2,14], $r25
	stw	[$r2,16], $r28
	stw	[$r2,18], $r31
	stw	[$r2,20], $r33
	stw	[$r2,22], $r35
	stw	[$r2,24], $r37
	stw	[$r2,26], $r39
	stw	[$r2,28], $r41
	stw	[$r2,30], $r43
	stw	[$r2,32], $r45
	stw	[$r2,34], $r47
	stw	[$r2,36], $r49
	stw	[$r2,38], $r51
	stw	[$r2,40], $r53
	stw	[$r2,42], $r55
	stw	[$r2,44], $r57
	stw	[$r2,46], $r59
	stw	[$r2,48], $r61
	stw	[$r2,50], $r63

	/* Return 0 since we are calling setjmp directly. */

	movi	$r2, 0
	jmp	$r0
	.size	setjmp, .-setjmp


/*! Jump to a long jump point set earlier with setjmp

    Setjmp stores all its caller-saved registers in a buffer. The trouble is
    we don't know how many registers any particular implementation has. For
    now we deal with this by assuming the maximum.

    @param $r2  Address of the buffer.
    @param $r3  Value to be returned (0 is not permitted, will be changed
	        to 1). */

	.global longjmp
	.type   longjmp,@function
longjmp:

	/* Restore all the registers. */
1:
	ldw	$r0, [$r2,0]		/* Link register */
	ldw	$r1, [$r2,2]		/* Stack pointer */

	/* Skip argument/results registers R2 - R7 */
	/* Skip call clobbered registers in range R8 - R63 */

	ldw	$r10, [$r2,4]
	ldw	$r13, [$r2,6]
	ldw	$r16, [$r2,8]
	ldw	$r19, [$r2,10]
	ldw	$r22, [$r2,12]
	ldw	$r25, [$r2,14]
	ldw	$r28, [$r2,16]
	ldw	$r31, [$r2,18]
	ldw	$r33, [$r2,20]
	ldw	$r35, [$r2,22]
	ldw	$r37, [$r2,24]
	ldw	$r39, [$r2,26]
	ldw	$r41, [$r2,28]
	ldw	$r43, [$r2,30]
	ldw	$r45, [$r2,32]
	ldw	$r47, [$r2,34]
	ldw	$r49, [$r2,36]
	ldw	$r51, [$r2,38]
	ldw	$r53, [$r2,40]
	ldw	$r55, [$r2,42]
	ldw	$r57, [$r2,44]
	ldw	$r59, [$r2,46]
	ldw	$r61, [$r2,48]
	ldw	$r63, [$r2,50]

	/* If the second argument to longjmp is zero, set return address to 1,
	   otherwise set it to the value of the second argument.  We can reuse
	   R2 here, which will be useful in the future for versions dealing
	   with very small numbers of registers. */

	sub	$r2, $r2, $r2
	bne	1f, $r3, $r2
	mov	$r3, 1

	/* Set result and return */
1:
	mov	$r2, $r3
	jmp	$r0
	.size	setjmp, .-setjmp
