/* sbrk system call

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


#include <errno.h>
#undef errno
extern int errno;


/*! Extend the heap

    The stack grows down from the end of RAM.  The heap grows up from the end
    of any pre-allocated data space.  Eventually these two things may colide
    and sbrk() won't even be able to return properly.

    Remember that this function is *not* reentrant, so no static state should
    be held.

    @todo  We break this rule with heap_ptr. This needs to be clean, so that a
           re-entrant call to sbrk (e.g. in an ISR) is certain to work.

    @param[in] nbytes  The number of bytes to be allocated.

    @return  The previous heap end on success, -1 on failure with an error
             code in errno. */

void *
_sbrk (int nbytes)
{
  /* Symbol defined by linker map */
  extern int  ___heap_start;		/* start of heap memory (as symbol) */
  extern int  ___heap_end;		/* end of heap memory (as symbol) */

  /* The statically held previous end of the heap, with its initialization. */
  static void *heap_ptr = (void *)&___heap_start;	/* Previous end */

  if ((heap_ptr + nbytes) < (void *)&___heap_end )
    {
      void *base  = heap_ptr;
      heap_ptr   += nbytes;

      return  base;
    }
  else
    {
      errno = ENOMEM;
      return  (void *) -1;
    }
}	/* _sbrk () */
