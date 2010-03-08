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


#ifndef HEADER_ADRIVER
#define HEADER_ADRIVER

#include <e32base.h>
#include <f32file.h>
	

_LIT(KProgName, "DebugAgent");
_LIT(KCRLF, "\r\n");
_LIT(KPrefsFile, "c:\\midp2\\jdebugagent\\agent.ini");
const TInt KSeiSlavePort = 11011;
const TInt KRandomPortStart = 21000;
const TInt KPCPort = 11012;
_LIT(KPCHost, "thehost");
class CAgentEngine;
class CTcpServerHandler;

class CDriver : public CBase
	{
public:
	CDriver();
	virtual ~CDriver();
public:
	virtual void InitL() = 0;
	virtual RFs& Fs() = 0;
	virtual CAgentEngine* Engine() = 0;
	virtual void Shutdown() = 0;
	virtual void SettingsChange(){};

	// Notifications from CTcpServerHandler:
	virtual void ClientConnected(CTcpServerHandler*){}
	virtual void ClientDisconnected(CTcpServerHandler*){}
	
	virtual void Log(const TDesC& aString) = 0;
	void Log(TDes8& aString, TBool aUnicode);
	void Log(TDes& aString);
	void Log(TDesC8& aString, TBool aUnicode);
	virtual void Message(const TDesC& aString) = 0;
	void Message(TDes8& aString, TBool aUnicode);
	void Message(TDes& aString);
	void Message(TDesC8& aString, TBool aUnicode);

	TBool IsAutoCleanEnabled();
	void SetAutoCleanEnabled(TBool);
	
	TInt GetAgentPort();
	void SetAgentPort(TInt );
	
	TInt GetPCPort();
	void SetPCPort(TInt aPort);
	HBufC* GetPCHost();
	void SetPCHostL(const TDesC& aHost);

	TBool IsFileLog();
	virtual void SetFileLog(TBool aFileLog );

	HBufC* GetPinCode();
	void SetPinCodeL(const TDesC& aPin);
	TBool IsUsePin();
	void SetUsePin(TBool aUsePin );

	TInt NextRandomPort();
	
	void LoadPrefsL();
	void SavePrefsL();

	/**
	* Done on startup for test purpose.
	* Pinging a server will open EPOC network interfaces and
	* get an IP from the DHCP server.
	*/
	TInt PingL(TDesC& aHost, TInt aPort);
private:
	void LogAllocL(TDesC8& aString);

private:
	TBool 		iAutoClean;
	TBool 		iUsePin;
	TBool 		iFileLog;
	TInt 		iPort;
	TInt 		iRandomPort;
	HBufC* 		iPinCode;
	TInt 		iPCPort;
	HBufC* 		iPCHost;
	};

#endif