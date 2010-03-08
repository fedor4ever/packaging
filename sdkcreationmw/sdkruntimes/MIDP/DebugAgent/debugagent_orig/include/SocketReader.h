/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description: 
*
*/


#ifndef HEADER_SOCKET_READER
#define HEADER_SOCKET_READER

#include <e32base.h>

#include <es_sock.h>
#include <utf.h>
	
class CSocketReader : public CActive
	{
public:

	static CSocketReader* NewL(RSocket* aSocket);
	~CSocketReader();
	
	// all following methods are blocking

	/**
	* Read a byte from the socket.
	*
	* @return The byte value
    *
	* @leave  If read error occurs leaves with one of the Symbian OS 
	*         wide error codes.
	*/
	TUint8 ReadL(void);
	
	/**
	* Read a 16-bit int from the socket and return it.
	*
	* @return The int value
    *
	* @leave  If read error occurs leaves with one of the Symbian OS 
	*         wide error codes.
	* @leave  If he stream ends before the whole integer could be read
	*         this method leaves with KErrCorrupt
	*/
	TInt16 ReadShortL(void);

  	/**
	* Read an int from the socket and return it.
	*
	* @return The int value
    *
	* @leave  If read error occurs leaves with one of the Symbian OS 
	*         wide error codes.
	* @leave  If he stream ends before the whole integer could be read
	*         this method leaves with KErrCorrupt
	*/
	TInt ReadIntL(void);

	/**
	* Read bytes and store in aBuff. This method will attempt to
	* read until the aBuff is full or end of stream is reached.
	*
	* @param  aBuff A buffer to store read data
    *
	* @return The number of bytes actually read
    *
	* @leave  If read error occurs leaves with one of the Symbian OS 
	*         wide error codes.
	*/
	TInt Read8L(TDes8& aBuff);

	/**
	* Read UTF formatted 8 bit data. 
	* This method calls ReadShortL, allocates the aBuff and calls Read8L.
	* The allocated descriptor (aBuff) must be deallocated by the caller.
	*
	* @param  aBuff A reference to a HBufC8 that will be initialised
	*               in this method with enough space to accomodate
	*               the string being read.
	*				               
	* @return The number of bytes actually read
    *
	* @leave  If read error occurs leaves with one of the Symbian OS 
	*         wide error codes.
	*/
	TInt ReadUtf8L(HBufC8*& aBuff);

	/**
	* Read UTF formatted unicode (16 bit) data. 
	* This method calls ReadShortL, allocates the aBuff and calls ReadL.
	* The allocated descriptor (aBuff) must be deallocated by the caller.
	*
	* @param  aBuff A reference to a HBufC that will be initialised
	*               in this method with enough space to accomodate
	*               the string being read.
	*				               
	* @return The number of bytes actually read
    *
	* @leave  If read error occurs leaves with one of the Symbian OS 
	*         wide error codes.
	*/
	TInt ReadUtfL(HBufC*& aBuff);

protected:
	// CActive
	virtual void DoCancel();
	virtual void RunL();

private:
	CSocketReader(RSocket* aSocket);
	void ConstructL();
	void WaitForRequest();

    RSocket* iSocket;
	CActiveSchedulerWait iWait;
	};

#endif