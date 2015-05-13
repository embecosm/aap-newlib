/* unlink system call

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


#include <unistd.h>
#include <errno.h>
#undef errno
extern int errno;


/*! Write bytes

    AAP supports just standard output and standard error, so for these streams
    we can do output, which we assume always succeeds.

    @param[in] file    File handle to write to.
    @param[in] buf     Bytes to write.
    @param[in] nbytes  Number of bytes to write
    @return  nbytes if writing to standard output or standard error, otherwise
             -1 to indicate failure. */

int
_write (int   file,
        char *ptr,
        int   len)
{
  int i;
  int nop_const;

  switch (file)
    {
    case STDOUT_FILENO:

      nop_const = 3;		/* Select the correct NOP const */
      break;

    case STDERR_FILENO:

      nop_const = 4;		/* Select the correct NOP const */
      break;

    default:

      /* We only handle standard output and standard error */

      errno = EBADF;
      return -1;
    }

  /* Output character at at time */

  for (i = 0; i < nbytes; i++)
    {
      __asm__ volatile ("\tnop\t%1,#%2" : : "r" (buf[i]) , "k" (nop_const));
    }

  return nbytes;

}	/* _write () */
