/*
 * Copyright (C) 2011 Red Hat, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 *
 * Author: Daniel P. Berrange <berrange@redhat.com>
 */

#include <config.h>

#include <stdio.h>
#include "internal.h"

int main(int argc, char **argv)
{
    int i;
    int failConnect = 0; /* Exit -1, with no data on stdout, msg on stderr */
    int dieEarly = 0;    /* Exit -1, with partial data on stdout, msg on stderr */

    for (i = 1 ; i < argc ; i++) {
        if (STREQ(argv[i], "nosuchhost"))
            failConnect = 1;
        else if (STREQ(argv[i], "crashinghost"))
            dieEarly = 1;
    }

    if (failConnect) {
        fprintf(stderr, "%s", "Cannot connect to host nosuchhost\n");
        return -1;
    }

    if (dieEarly) {
        printf("%s\n", "Hello World");
        fprintf(stderr, "%s", "Hangup from host\n");
        return -1;
    }

    for (i = 1 ; i < argc ; i++)
        printf("%s%c", argv[i], i == (argc -1) ? '\n' : ' ');

    return 0;
}
