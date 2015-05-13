/* C runtime initialization for AAP

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


/*! The code for AAP starts at location zero in code space.

    This function takes no arguments and never returns. */

	.section  text
	.global	_start
	.type	_start, function
_start:

	/* Stack falls from the top of memory.  For now we assume 64kB of
	   RAM. */

	mov	$r1, #0xffff

	/* Optionally clear BSS (for debugging) here. */

	/* Call init to set up constructors, and pass fini to atexit. */

	bal	init, $r0
	mov	$r2,#fini
	bal	atexit, $r0

	/* Call the main function, setting the args to zero. If it returns,
	   call _exit with the result. */

	mov	$r2, 0
	mov	$r3, 0
	mov	$r4, 0
	bal	main
	bal	_exit

	/* We should never get here, but just in case... */
1:
	bra	1b
	size	_start, .-_start
