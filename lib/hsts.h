#ifndef HEADER_CURL_HSTS_H
#define HEADER_CURL_HSTS_H
/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 2020, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
#include "curl_setup.h"

#if !defined(CURL_DISABLE_HTTP) && defined(USE_HSTS)
#include <curl/curl.h>
#include "llist.h"

struct stsentry {
  struct Curl_llist_element node;
  const char *host;
  bool includeSubDomains;
  time_t expires; /* the timestamp of this entry's expiry */
};

/* The HSTS cache. Needs to be able to tailmatch host names. */
struct hsts {
  struct Curl_llist list;
};

struct hsts *Curl_hsts_init(void);
void Curl_hsts_cleanup(struct hsts **hp);
CURLcode Curl_hsts_parse(struct hsts *h, const char *hostname,
                         const char *sts);
struct stsentry *Curl_hsts(struct hsts *h, const char *hostname,
                           bool subdomain);
#else
#define Curl_hsts_cleanup(x)
#endif /* CURL_DISABLE_HTTP || USE_HSTS */
#endif /* HEADER_CURL_HSTS_H */