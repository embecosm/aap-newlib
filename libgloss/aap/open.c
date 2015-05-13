/* open system call

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


/*! Open a file

    For now we support no file system (this may change in the future). So this
    function always fails.

    @param[in] name   The name of the file to open
    @param[in] flags  Flags detailing how the file is to be opened.
    @param[in] mode   Mode of opening.
    @return  -1 to indicate failure. */

int
_open (char *name  __attribute__ ((unused)),
       int   flags __attribute__ ((unused)),
       int   mode  __attribute__ ((unused)) )
{
  errno = ENOSYS;
  return -1;

}	/* _open () */
