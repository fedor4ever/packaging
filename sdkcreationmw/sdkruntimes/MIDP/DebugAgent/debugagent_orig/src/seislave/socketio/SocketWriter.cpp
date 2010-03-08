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


#include "SocketWriter.h"

CSocketWriter* CSocketWriter::NewL(RSocket* aSocket)
	{
	CSocketWriter* object = new (ELeave) CSocketWriter(aSocket);
	CleanupStack::PushL(object);
	CActiveScheduler::Add(object);
	object->ConstructL();
	CleanupStack::Pop(object);
	return object;
	}

CSocketWriter::CSocketWriter(RSocket* aSocket)
: CActive(EPriorityStandard), iSocket( aSocket)
	{
	}

CSocketWriter::~CSocketWriter()
	{
	}

void CSocketWriter::ConstructL()
    {
    }

void CSocketWriter::WriteL(TUint8 aByte)
    {
    TPtr8 ptr(&aByte, 1, 1);
    iStatus = KRequestPending;
    iSocket->Write(ptr, iStatus);
    WaitForRequest();
    User::LeaveIfError(iStatus.Int());
    }

void CSocketWriter::WriteIntL(TInt aInt)
    {
    TInt swapped = (TInt)ByteOrder::Swap32((TUint32)aInt);
    TPtr8 ptr((TUint8*)(&swapped), 4, 4);
    iStatus = KRequestPending;
    iSocket->Write(ptr, iStatus);
    WaitForRequest();
    User::LeaveIfError(iStatus.Int());
    }

void CSocketWriter::WriteShortL(TInt16 aInt)
    {
    TInt16 swapped = (TInt16)ByteOrder::Swap16((TUint16)aInt);
    TPtr8 ptr((TUint8*)(&swapped), 2, 2);
    iStatus = KRequestPending;
    iSocket->Write(ptr, iStatus);
    WaitForRequest();
    User::LeaveIfError(iStatus.Int());
    }

void CSocketWriter::Write8L(TDes8& aBuff)
    {
    iStatus = KRequestPending;
    iSocket->Write(aBuff, iStatus);
    WaitForRequest();
    User::LeaveIfError(iStatus.Int());
    }

void CSocketWriter::WriteL(TDes& aBuff)
    {
    TPtr8 ptr((TUint8*)(aBuff.Ptr()), 2*aBuff.Length(), 2*aBuff.MaxLength());
    iStatus = KRequestPending;
    iSocket->Write(ptr, iStatus);
    WaitForRequest();
    User::LeaveIfError(iStatus.Int());
    }

void CSocketWriter::WriteUtf8L(TDes8& aBuff)
    {
    WriteShortL((TInt16)aBuff.Length());
    Write8L(aBuff);
    }

void CSocketWriter::WriteUtfL(TDes& aBuff)
    {
    TPtrC ptr (aBuff);
    WriteUtfL(ptr);
    }

void CSocketWriter::Write8L(TDesC8& aBuff)
    {
    iStatus = KRequestPending;
    iSocket->Write(aBuff, iStatus);
    WaitForRequest();
    User::LeaveIfError(iStatus.Int());
    }

void CSocketWriter::WriteL(TDesC& aBuff)
    {
    TPtr8 ptr((TUint8*)(aBuff.Ptr()), 2*aBuff.Length(), 2*aBuff.Length());
    iStatus = KRequestPending;
    iSocket->Write(ptr, iStatus);
    WaitForRequest();
    User::LeaveIfError(iStatus.Int());
    }

void CSocketWriter::WriteUtf8L(TDesC8& aBuff)
    {
    WriteShortL((TInt16)aBuff.Length());
    Write8L(aBuff);
    }

void CSocketWriter::WriteUtfL(TDesC& aBuff)
    {
    // convert to UTF8 
    HBufC8* buf = HBufC8::NewLC(2 * aBuff.Length());
    TPtr8 ptr = buf->Des();
    CnvUtfConverter::ConvertFromUnicodeToUtf8(ptr, aBuff);
    WriteShortL((TInt16)(ptr.Length()));
    Write8L(ptr);
    CleanupStack::PopAndDestroy(buf);
    }

void CSocketWriter::DoCancel()
    {
    iSocket->CancelWrite();
    iWait.AsyncStop();
    }

void CSocketWriter::RunL()
    {
    iWait.AsyncStop();
    }

void CSocketWriter::WaitForRequest()
    {
    if (iStatus == KRequestPending)
        {
        SetActive();
        iWait.Start();
        }
    else
        {
        // Seemingly useless assignment statement below performs very 
        // important function. It clears TRequestStatus::ERequestPending
        // bit in TRequestStatus::iFlags field, which otherwise panics
        // the scheduler. The next statement eats the signal.
        iStatus = iStatus.Int();
        User::WaitForRequest(iStatus);
        }
    }
