/*
 * Process Hacker Driver - 
 *   main header file
 * 
 * Copyright (C) 2009 wj32
 * 
 * This file is part of Process Hacker.
 * 
 * Process Hacker is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Process Hacker is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Process Hacker.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KPROCESSHACKER_H
#define KPROCESSHACKER_H

#include <ntifs.h>

#define KPH_TAG 'KPHT'
/* I like 0x9999. */
#define KPH_DEVICE_TYPE (0x9999)
#define KPH_DEVICE_NAME (L"\\Device\\KProcessHacker")
#define KPH_DEVICE_DOS_NAME (L"\\DosDevices\\KProcessHacker")

#define KPH_CTL_CODE(x) CTL_CODE(KPH_DEVICE_TYPE, 0x800 + x, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define KPH_READ KPH_CTL_CODE(0)
#define KPH_WRITE KPH_CTL_CODE(1)
#define KPH_GETFILEOBJECTNAME KPH_CTL_CODE(2)
#define KPH_OPENPROCESS KPH_CTL_CODE(3)
#define KPH_OPENTHREAD KPH_CTL_CODE(4)
#define KPH_OPENPROCESSTOKEN KPH_CTL_CODE(5)
#define KPH_GETPROCESSPROTECTED KPH_CTL_CODE(6)
#define KPH_SETPROCESSPROTECTED KPH_CTL_CODE(7)
#define KPH_TERMINATEPROCESS KPH_CTL_CODE(8)
#define KPH_SUSPENDPROCESS KPH_CTL_CODE(9)
#define KPH_RESUMEPROCESS KPH_CTL_CODE(10)
#define KPH_READVIRTUALMEMORY KPH_CTL_CODE(11)
#define KPH_WRITEVIRTUALMEMORY KPH_CTL_CODE(12)
#define KPH_SETPROCESSTOKEN KPH_CTL_CODE(13)
#define KPH_GETTHREADWIN32STARTADDRESS KPH_CTL_CODE(14)
#define KPH_GETOBJECTNAME KPH_CTL_CODE(15)
#define KPH_GETHANDLEOBJECTNAME KPH_CTL_CODE(16)
#define KPH_OPENPROCESSJOB KPH_CTL_CODE(17)
#define KPH_GETCONTEXTTHREAD KPH_CTL_CODE(18)
#define KPH_SETCONTEXTTHREAD KPH_CTL_CODE(19)
#define KPH_GETTHREADWIN32THREAD KPH_CTL_CODE(20)
#define KPH_DUPLICATEOBJECT KPH_CTL_CODE(21)
#define KPH_ZWQUERYOBJECT KPH_CTL_CODE(22)
#define KPH_GETPROCESSID KPH_CTL_CODE(23)
#define KPH_GETTHREADID KPH_CTL_CODE(24)

NTSTATUS KphCreate(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS KphClose(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS KphIoControl(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS KphRead(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS KphUnsupported(PDEVICE_OBJECT DeviceObject, PIRP Irp);

#endif