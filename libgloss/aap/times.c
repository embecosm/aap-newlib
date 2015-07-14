/* times system call

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


#include <sys/times.h>
#include <errno.h>
#undef errno
extern int errno;


/*! Provide process timing information

    AAP provides a NOP value to yield time in seconds and microseconds that
    the processor has been running.  This is both the processor and child
    time.  AAP uses a microsecond value for sysconf (_SC_CLK_TCK).  All time
    is deemed to be user time.

    @param[out]  buf  Structure for the time info.

    @return  Number of clock ticks since starting (truncated). */

clock_t
_times (struct tms *buf)
{
  struct aap_time {
    unsigned long  t_sec;
    unsigned long  t_usec;
  } aap_buf;
  struct aap_time *aap_buf_ptr = &aap_buf;

  asm volatile ("nop    %0,   5" : : "r" (aap_buf_ptr));

  buf->tms_utime  = aap_buf.t_sec * 1000000 + aap_buf.t_usec;
  buf->tms_stime  = 0;
  buf->tms_cutime = 0;
  buf->tms_cstime = 0;

  return buf->tms_utime;

}	/* _times () */
