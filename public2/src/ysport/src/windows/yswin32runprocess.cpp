/* ////////////////////////////////////////////////////////////

File Name: yswin32runprocess.cpp
Copyright (c) 2017 Soji Yamakawa.  All rights reserved.
http://www.ysflight.com

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, 
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation 
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS 
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

//////////////////////////////////////////////////////////// */

#include "../ysrunprocess.h"

#include <windows.h>

YSRESULT YsRunProcess::Run(const char cmdline[])
{
	STARTUPINFOA sui;
	sui.cb=sizeof(STARTUPINFO);
	sui.lpReserved=NULL;
	sui.lpDesktop=NULL;
	sui.lpTitle=NULL;
	sui.dwFlags=0;
	sui.cbReserved2=0;
	sui.lpReserved2=0;

	PROCESS_INFORMATION pi;
	HINSTANCE neoinst;
	BOOL err;

	err=CreateProcessA
	   (NULL,
	    (char *)cmdline,
	    NULL,
	    NULL,
	    FALSE,
	    CREATE_DEFAULT_ERROR_MODE,
	    NULL,
	    NULL,
	    &sui,
	    &pi);

	if(err!=TRUE)
	{
		neoinst=ShellExecuteA(NULL,NULL,cmdline,NULL,NULL,SW_SHOWNORMAL);
	}

	if(err!=TRUE && (long long int)(neoinst)<=32)
	{
		return YSERR;

		/* char errorMessage[4096];
		FormatMessage(
		    FORMAT_MESSAGE_FROM_SYSTEM,
		    NULL,
		    GetLastError(),
		    MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
		    errorMessage,
		    4096,
		    NULL);

		MessageBox(hWndMain,"Cannot Open Help File.","Error",MB_OK); */
	}

	return YSOK;
}
