#pragma once

/*
cache.hpp

����������� ������ � ����/������ �� �����
*/
/*
Copyright � 2009 Far Group
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the authors may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

class CachedRead
{
public:
	CachedRead(File& file, DWORD buffer_size=0);
	~CachedRead();
	bool AdjustAlignment(); // file have to be opened already
	bool Read(LPVOID Data, DWORD DataSize, LPDWORD BytesRead);
	bool FillBuffer();
	bool Unread(DWORD BytesUnread);
	void Clear();

private:
	File& file;
	const DWORD DefaultBufferSize;
	DWORD ReadSize;
	DWORD BytesLeft;
	INT64 LastPtr;
	int Alignment;
	DWORD BufferSize; // = 2*k*Alignment (k >= 2)
	array_ptr<BYTE> Buffer;
};


class CachedWrite
{
public:
	CachedWrite(File& file);
	~CachedWrite();
	bool Write(LPCVOID Data, size_t DataSize);
	bool Flush();

private:
	File& file;
	const DWORD BufferSize;
	array_ptr<BYTE> Buffer;
	DWORD FreeSize;
	bool Flushed;
};
