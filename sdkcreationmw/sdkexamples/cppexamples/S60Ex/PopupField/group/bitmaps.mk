#
# Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
# All rights reserved.
# This component and the accompanying materials are made available
# under the terms of the License "Eclipse Public License v1.0"
# which accompanies this distribution, and is available
# at the URL "http://www.eclipse.org/legal/epl-v10.html".
#
# Initial Contributors:
# Nokia Corporation - initial contribution.
#
# Contributors:
#
# Description: 
#

ifeq (WINS,$(findstring WINS, $(PLATFORM)))
ZDIR=$(EPOCROOT)epoc32\release\$(PLATFORM)\$(CFG)\z
else
ZDIR=$(EPOCROOT)epoc32\data\z
endif

TARGETDIR=$(ZDIR)\private\E000022A
ICONTARGETFILENAME=$(TARGETDIR)\AknExPopField.mbm

HEADERDIR=$(EPOCROOT)epoc32\include
HEADERFILENAME=$(HEADERDIR)\AknExPopField.mbg

do_nothing :
		@rem do_nothing

MAKMAKE : do_nothing

BLD : do_nothing

CLEAN : do_nothing

LIB : do_nothing

CLEANLIB : do_nothing

RESOURCE :
		mifconv $(ICONTARGETFILENAME) /h$(HEADERFILENAME) \
            /c8 ..\gfx\30x40.bmp

FREEZE : do_nothing

SAVESPACE : do_nothing

RELEASABLES :
		@echo $(HEADERFILENAME)&& \
		@echo $(ICONTARGETFILENAME)

FINAL : do_nothing
