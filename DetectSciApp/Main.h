#pragma once

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
#include "ATSZLIB.h"
#include "QueueLib.h"

#if defined(_WIN64)
	#pragma comment(lib,"ATSZLIB64.lib")
#else
	#pragma comment(lib, "ATSZLIB.lib")
#endif

#define EC_SC     0x66
#define EC_DATA   0x62
#define GPE0_STATUS_BASE 0x1880

#pragma pack(push)
#pragma pack(1)


typedef struct _DATA_PACKET {
	BOOL        isECSupport;
	BOOL		isDetecting;
	UINT32		GPE0_BLK;
	UINT8		GPE0_BLK_LEN;
	UINT8       QueryLxxFreq;   //uint: ms
	UINT8       QueryQxxFreq;	//uint: ms
	HANDLE		gMutex;
	PQUEUE_NODE headPtr;
	PQUEUE_NODE tailPtr;
} DATA_PACKET, *PDATA_PACKET;

//======================================================
//  ACPI Tables header structure
//======================================================
typedef struct _ACPI_HDR {
	UINT32      Signature;
	UINT32      Length;
	UINT8       Revision;
	UINT8       Checksum;
	UINT8       OemId[6];
	UINT8       OemTblId[8];
	UINT32      OemRev;
	UINT32      CreatorId;
	UINT32      CreatorRev;
} ACPI_HDR, *PACPI_HDR;

//======================================================
//  GAS_20 Generic Address structure
//======================================================
typedef struct _GAS_20 {
	UINT8			AddrSpcID;          //The address space where the data structure or register exists.
										//Defined values are above                                            
	UINT8			RegBitWidth;		//The size in bits of the given register. 
										//When addressing a data structure, this field must be zero.
	UINT8			RegBitOffs;			//The bit offset of the given register at the given address.
										//When addressing a data structure, this field must be zero.
	UINT8			Reserved1;          //must be 0.
	UINT64			Address;            //The 64-bit address of the data structure or register in 
										//the given address space (relative to the processor).
} GAS_20, *PGAS_20;

//======================================================
//  GAS_30 Generic Address structure
//======================================================
typedef struct _GAS_30 {
	UINT8			AddrSpcID;          //The address space where the data structure or register exists.
										//Defined values are above                                            
	UINT8			RegBitWidth;		//The size in bits of the given register. 
										//When addressing a data structure, this field must be zero.
	UINT8			RegBitOffs;			//The bit offset of the given register at the given address.
										//When addressing a data structure, this field must be zero.
	UINT8			AccessSize;
	UINT64			Address;            //The 64-bit address of the data structure or register in 
										//the given address space (relative to the processor).
} GAS_30, *PGAS_30;

//======================================================
//  FADT Fixed ACPI Description Table 
//======================================================
typedef struct _FACP_20 {
	ACPI_HDR Header;              //0..35
	UINT32		FIRMWARE_CTRL;       //36  Phisical memory address (0-4G) of FACS
	UINT32		DSDT;                //40  Phisical memory address (0-4G) of DSDT
	UINT8		Reserved1;			 //44  (Was INT_MODEL 0 Dual PIC;1 Multipy APIC) 
									 //	   can be 0 or 1 for ACPI 1.0  
	UINT8  		PM_PPROF;			 //45  Preffered PM Profile (was Reserved)
	UINT16		SCI_INT;             //46  SCI int Pin should be Shareble/Level/Act Low

	UINT32		SMI_CMD;             //48  Port Addr of ACPI Command reg
	UINT8		ACPI_ENABLE_CMD;         //52  Value to write in SMI_CMD reg
	UINT8		ACPI_DISABLE_CMD;        //53  Value to write in SMI_CMD reg    
	UINT8		S4BIOS_REQ;          //54  Value to write in SMI_CMD reg
	UINT8		PSTATE_CNT;          //55  Was Reserved2 now 
									 //	   Value that OSPM writes in SCI_CMD to assume 
									 //	   Processor Perfomance State control responsibility
	UINT32		PM1a_EVT_BLK;        //56
	UINT32		PM1b_EVT_BLK;        //60
	UINT32		PM1a_CNT_BLK;        //64
	UINT32		PM1b_CNT_BLK;        //68
	UINT32		PM2_CNT_BLK;         //72
	UINT32		PM_TMR_BLK;          //76
	UINT32		GPE0_BLK;            //80
	UINT32		GPE1_BLK;            //84    
	UINT8		PM1_EVT_LEN;         //88
	UINT8		PM1_CNT_LEN;         //89
	UINT8		PM2_CNT_LEN;         //90
	UINT8		PM_TM_LEN;           //91
	UINT8		GPE0_BLK_LEN;        //92
	UINT8		GPE1_BLK_LEN;        //93
	UINT8		GPE1_BASE;           //94
	UINT8		CST_CNT;			 //95 Was Reserved3 
	UINT16		P_LVL2_LAT;          //96
	UINT16		P_LVL3_LAT;          //98
	UINT16		FLUSH_SIZE;          //100
	UINT16		FLUSH_STRIDE;        //102
	UINT8		DUTY_OFFSET;         //104
	UINT8		DUTY_WIDTH;          //105
	UINT8		DAY_ALRM;            //106
	UINT8		MON_ALRM;            //107
	UINT8		CENTURY;             //108
	UINT16		IAPC_BOOT_ARCH;      //109	
	UINT8		Reserved2;           //111    
	UINT32		FLAGS;               //112
/* That was 32 bit part of a FADT Here follows 64bit part */
#if defined(_WIN64)
	GAS_20			RESET_REG;			 //116
	UINT8		RESET_VAL;			 //128
	UINT8		Reserved[3];		 //129
	UINT64		X_FIRMWARE_CTRL;     //132  Phisical memory address (0-4G) of FACS
	UINT64		X_DSDT;              //140  Phisical memory address (0-4G) of DSDT
	GAS_20			X_PM1a_EVT_BLK;      //148
	GAS_20			X_PM1b_EVT_BLK;      //160
	GAS_20			X_PM1a_CNT_BLK;      //172
	GAS_20			X_PM1b_CNT_BLK;      //184
	GAS_20			X_PM2_CNT_BLK;       //196
	GAS_20			X_PM_TMR_BLK;        //208
	GAS_20			X_GPE0_BLK;          //220
	GAS_20			X_GPE1_BLK;          //232
#endif
}FACP_20, *PFACP_20;

//======================================================
//  FADT Fixed ACPI Description Table 
//======================================================
typedef struct _FACP_30 {
	ACPI_HDR Header;              //0..35
	UINT32		FIRMWARE_CTRL;       //36  Phisical memory address (0-4G) of FACS
	UINT32		DSDT;                //40  Phisical memory address (0-4G) of DSDT
	UINT8		Reserved1;			 //44  (Was INT_MODEL 0 Dual PIC;1 Multipy APIC) 
									 //	   can be 0 or 1 for ACPI 1.0  
	UINT8  		PM_PPROF;			 //45  Preffered PM Profile (was Reserved)
	UINT16		SCI_INT;             //46  SCI int Pin should be Shareble/Level/Act Low

	UINT32		SMI_CMD;             //48  Port Addr of ACPI Command reg
	UINT8		ACPI_ENABLE_CMD;         //52  Value to write in SMI_CMD reg
	UINT8		ACPI_DISABLE_CMD;        //53  Value to write in SMI_CMD reg    
	UINT8		S4BIOS_REQ;          //54  Value to write in SMI_CMD reg
	UINT8		PSTATE_CNT;          //55  Was Reserved2 now 
									 //	   Value that OSPM writes in SCI_CMD to assume 
									 //	   Processor Perfomance State control responsibility
	UINT32		PM1a_EVT_BLK;        //56
	UINT32		PM1b_EVT_BLK;        //60
	UINT32		PM1a_CNT_BLK;        //64
	UINT32		PM1b_CNT_BLK;        //68
	UINT32		PM2_CNT_BLK;         //72
	UINT32		PM_TMR_BLK;          //76
	UINT32		GPE0_BLK;            //80
	UINT32		GPE1_BLK;            //84    
	UINT8		PM1_EVT_LEN;         //88
	UINT8		PM1_CNT_LEN;         //89
	UINT8		PM2_CNT_LEN;         //90
	UINT8		PM_TM_LEN;           //91
	UINT8		GPE0_BLK_LEN;        //92
	UINT8		GPE1_BLK_LEN;        //93
	UINT8		GPE1_BASE;           //94
	UINT8		CST_CNT;			 //95 Was Reserved3 
	UINT16		P_LVL2_LAT;          //96
	UINT16		P_LVL3_LAT;          //98
	UINT16		FLUSH_SIZE;          //100
	UINT16		FLUSH_STRIDE;        //102
	UINT8		DUTY_OFFSET;         //104
	UINT8		DUTY_WIDTH;          //105
	UINT8		DAY_ALRM;            //106
	UINT8		MON_ALRM;            //107
	UINT8		CENTURY;             //108
	UINT16		IAPC_BOOT_ARCH;      //109	
	UINT8		Reserved2;           //111    
	UINT32		FLAGS;               //112
									 //That was 32 bit part of a FADT Here follows 64bit part
#if defined(_WIN64)
	GAS_30			RESET_REG;			 //116
	UINT8		RESET_VAL;			 //128
	UINT8		Reserved[3];		 //129
	UINT64		X_FIRMWARE_CTRL;     //132  Phisical memory address (0-4G) of FACS
	UINT64		X_DSDT;              //140  Phisical memory address (0-4G) of DSDT
	GAS_30			X_PM1a_EVT_BLK;      //148
	GAS_30			X_PM1b_EVT_BLK;      //160
	GAS_30			X_PM1a_CNT_BLK;      //172
	GAS_30			X_PM1b_CNT_BLK;      //184
	GAS_30			X_PM2_CNT_BLK;       //196
	GAS_30			X_PM_TMR_BLK;        //208
	GAS_30			X_GPE0_BLK;          //220
	GAS_30			X_GPE1_BLK;          //232
#endif
}FACP_30, *PFACP_30;

//======================================================
//  FADT Fixed ACPI Description Table
//======================================================
typedef struct _FACP_50 {
	ACPI_HDR Header;              //0..35
	UINT32		FIRMWARE_CTRL;       //36  Phisical memory address (0-4G) of FACS
	UINT32		DSDT;                //40  Phisical memory address (0-4G) of DSDT
	UINT8		Reserved1;			 //44  (Was INT_MODEL 0 Dual PIC;1 Multipy APIC)
									 //	   can be 0 or 1 for ACPI 1.0
	UINT8  		PM_PPROF;			 //45  Preffered PM Profile (was Reserved)
	UINT16		SCI_INT;             //46  SCI int Pin should be Shareble/Level/Act Low

	UINT32		SMI_CMD;             //48  Port Addr of ACPI Command reg
	UINT8		ACPI_ENABLE_CMD;         //52  Value to write in SMI_CMD reg
	UINT8		ACPI_DISABLE_CMD;        //53  Value to write in SMI_CMD reg
	UINT8		S4BIOS_REQ;          //54  Value to write in SMI_CMD reg
	UINT8		PSTATE_CNT;          //55  Was Reserved2 now
									 //	   Value that OSPM writes in SCI_CMD to assume
									 //	   Processor Perfomance State control responsibility
	UINT32		PM1a_EVT_BLK;        //56
	UINT32		PM1b_EVT_BLK;        //60
	UINT32		PM1a_CNT_BLK;        //64
	UINT32		PM1b_CNT_BLK;        //68
	UINT32		PM2_CNT_BLK;         //72
	UINT32		PM_TMR_BLK;          //76
	UINT32		GPE0_BLK;            //80
	UINT32		GPE1_BLK;            //84
	UINT8		PM1_EVT_LEN;         //88
	UINT8		PM1_CNT_LEN;         //89
	UINT8		PM2_CNT_LEN;         //90
	UINT8		PM_TM_LEN;           //91
	UINT8		GPE0_BLK_LEN;        //92
	UINT8		GPE1_BLK_LEN;        //93
	UINT8		GPE1_BASE;           //94
	UINT8		CST_CNT;			 //95 Was Reserved3
	UINT16		P_LVL2_LAT;          //96
	UINT16		P_LVL3_LAT;          //98
	UINT16		FLUSH_SIZE;          //100
	UINT16		FLUSH_STRIDE;        //102
	UINT8		DUTY_OFFSET;         //104
	UINT8		DUTY_WIDTH;          //105
	UINT8		DAY_ALRM;            //106
	UINT8		MON_ALRM;            //107
	UINT8		CENTURY;             //108
	UINT16		IAPC_BOOT_ARCH;      //109
	UINT8		Reserved2;           //111
	UINT32		FLAGS;               //112
									 //That was 32 bit part of a FADT Here follows 64bit part
#if defined(_WIN64)
	GAS_30			RESET_REG;			 //116
	UINT8		RESET_VAL;			 //128
	UINT8		Reserved[3];		 //129
	UINT64		X_FIRMWARE_CTRL;     //132  Phisical memory address (0-4G) of FACS
	UINT64		X_DSDT;              //140  Phisical memory address (0-4G) of DSDT
	GAS_30	    X_PM1a_EVT_BLK;      //148
	GAS_30		X_PM1b_EVT_BLK;      //160
	GAS_30		X_PM1a_CNT_BLK;      //172
	GAS_30		X_PM1b_CNT_BLK;      //184
	GAS_30		X_PM2_CNT_BLK;       //196
	GAS_30		X_PM_TMR_BLK;        //208
	GAS_30		X_GPE0_BLK;          //220
	GAS_30		X_GPE1_BLK;          //232
	GAS_30		SLEEP_CONTROL_REG;   //244
	GAS_30		SLEEP_STATUS_REG;    //256
#endif
}FACP_50, *PFACP_50;

//======================================================
//  FADT Fixed ACPI Description Table
//======================================================
typedef struct _FACP_60 {
	ACPI_HDR Header;              //0..35
	UINT32		FIRMWARE_CTRL;       //36  Phisical memory address (0-4G) of FACS
	UINT32		DSDT;                //40  Phisical memory address (0-4G) of DSDT
	UINT8		Reserved1;			 //44  (Was INT_MODEL 0 Dual PIC;1 Multipy APIC)
									 //	   can be 0 or 1 for ACPI 1.0
	UINT8  		PM_PPROF;			 //45  Preffered PM Profile (was Reserved)
	UINT16		SCI_INT;             //46  SCI int Pin should be Shareble/Level/Act Low

	UINT32		SMI_CMD;             //48  Port Addr of ACPI Command reg
	UINT8		ACPI_ENABLE_CMD;         //52  Value to write in SMI_CMD reg
	UINT8		ACPI_DISABLE_CMD;        //53  Value to write in SMI_CMD reg
	UINT8		S4BIOS_REQ;          //54  Value to write in SMI_CMD reg
	UINT8		PSTATE_CNT;          //55  Was Reserved2 now
									 //	   Value that OSPM writes in SCI_CMD to assume
									 //	   Processor Perfomance State control responsibility
	UINT32		PM1a_EVT_BLK;        //56
	UINT32		PM1b_EVT_BLK;        //60
	UINT32		PM1a_CNT_BLK;        //64
	UINT32		PM1b_CNT_BLK;        //68
	UINT32		PM2_CNT_BLK;         //72
	UINT32		PM_TMR_BLK;          //76
	UINT32		GPE0_BLK;            //80
	UINT32		GPE1_BLK;            //84
	UINT8		PM1_EVT_LEN;         //88
	UINT8		PM1_CNT_LEN;         //89
	UINT8		PM2_CNT_LEN;         //90
	UINT8		PM_TM_LEN;           //91
	UINT8		GPE0_BLK_LEN;        //92
	UINT8		GPE1_BLK_LEN;        //93
	UINT8		GPE1_BASE;           //94
	UINT8		CST_CNT;			 //95 Was Reserved3
	UINT16		P_LVL2_LAT;          //96
	UINT16		P_LVL3_LAT;          //98
	UINT16		FLUSH_SIZE;          //100
	UINT16		FLUSH_STRIDE;        //102
	UINT8		DUTY_OFFSET;         //104
	UINT8		DUTY_WIDTH;          //105
	UINT8		DAY_ALRM;            //106
	UINT8		MON_ALRM;            //107
	UINT8		CENTURY;             //108
	UINT16		IAPC_BOOT_ARCH;      //109
	UINT8		Reserved2;           //111
	UINT32		FLAGS;               //112
									 //That was 32 bit part of a FADT Here follows 64bit part
#if defined(_WIN64)
	GAS_30		RESET_REG;			 //116
	UINT8		RESET_VAL;			 //128
	UINT16      ArmBootArch;         //129
	UINT8		MinorVersion;		 //131
	UINT64		X_FIRMWARE_CTRL;     //132  Phisical memory address (0-4G) of FACS
	UINT64		X_DSDT;              //140  Phisical memory address (0-4G) of DSDT
	GAS_30	    X_PM1a_EVT_BLK;      //148
	GAS_30		X_PM1b_EVT_BLK;      //160
	GAS_30		X_PM1a_CNT_BLK;      //172
	GAS_30		X_PM1b_CNT_BLK;      //184
	GAS_30		X_PM2_CNT_BLK;       //196
	GAS_30		X_PM_TMR_BLK;        //208
	GAS_30		X_GPE0_BLK;          //220
	GAS_30		X_GPE1_BLK;          //232
	GAS_30		SLEEP_CONTROL_REG;   //244
	GAS_30		SLEEP_STATUS_REG;    //256
	UINT64      HypervisorVendorIdentity; //268
#endif
}FACP_60, *PFACP_60;
#pragma pack(pop)

#ifndef _inp
	BYTE _inp(UINT16 wPortAddress)
	{
		BYTE value = 0;
		if (Read_Io_Byte(wPortAddress, &value))
			return value;
		else
			return 0;
	}
#endif

#ifndef _inpd
	DWORD _inpd(UINT16 wPortAddress)
	{
		DWORD value = 0;
		if (Read_Io_Dword(wPortAddress, (PDWORD)&value))
			return value;
		else
			return 0;
	}
#endif