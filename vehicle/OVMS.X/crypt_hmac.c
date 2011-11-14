/*
 * Copyright (c) 2007, Cameron Rich
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * * Neither the name of the axTLS project nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * HMAC implementation - This code was originally taken from RFC2104
 */

#include <string.h>
#include "crypt_md5.h"
#include "crypt_hmac.h"

#pragma udata
unsigned char k_ipad[64];
unsigned char k_opad[64];
MD5_CTX context;

/**
 * Perform HMAC-MD5
 */
void hmac_md5(const unsigned char *msg, int length, const unsigned char *key,
              int key_len, unsigned char *digest)
  {
  int i;

  memset(k_ipad, 0, sizeof k_ipad);
  memset(k_opad, 0, sizeof k_opad);
  memcpy(k_ipad, key, key_len);
  memcpy(k_opad, key, key_len);

  for (i = 0; i < 64; i++)
    {
    k_ipad[i] ^= 0x36;
    k_opad[i] ^= 0x5c;
    }

  MD5_Init(&context);
  MD5_Update(&context, k_ipad, 64);
  MD5_Update(&context, msg, length);
  MD5_Final(digest,&context);
  MD5_Init(&context);
  MD5_Update(&context, k_opad, 64);
  MD5_Update(&context, digest, 16);
  MD5_Final(digest,&context);
  }
