/************************************************************************
* File Description:	ATSZLIB.h                                                 
* CopyRight:		ASUSTeK
* Develop Time:		2008-12-22
*************************************************************************/
#include <windows.h>
#ifndef _ATSZLIB_
#define _ATSZLIB_
#define ATSZLIBVersion	0218;
typedef unsigned long long       QWORD,	*PQWORD;
#pragma pack(push,1)
typedef	struct {
	UINT32	_EAX;
	UINT32	_EBX;
	UINT32	_ECX;
	UINT32	_EDX;
	UINT32	_ESI;
	UINT32	_EDI;
	UINT32	_EBP;
} Registers;
#pragma pack(pop)
/************************************************************************
* Routine Name:			LoadATSZIoDriver
* Function Description:	Load ATSZ Io LIB Driver
* Parameters List:
*		None. 	
* Return value:			Return status of initial result
*************************************************************************/
BOOL _stdcall LoadATSZIoDriver();
/************************************************************************
* Routine Name:			LoadATSZIoDriver
* Function Description:	Load ATSZ Io LIB Driver
* Parameters List:
*		driverpath:		the driver path of atszio.sys and atszio64.sys 	
* Return value:			Return status of initial result
*************************************************************************/
BOOL _stdcall LoadATSZIoDriver(char * driverpath);
/************************************************************************
* Routine Name:			CloseATSZIoDriver
* Function Description:	Close handle and remove driver.
* Parameters List:
*		None. 	
* Return value:			Return status of initial result
*************************************************************************/
void _stdcall CloseATSZIoDriver();
/************************************************************************
* Routine Name:			InstallNTDriver
* Function Description:	Install NT Driver
* Parameters List:
*      PSTR: 			point to driver path 
*	   BOOL:			whether need to load	
* Return value:			Return status of initial result
*************************************************************************/
BOOL _stdcall InstallNTDriver(PSTR pszNTDriverPath, BOOL IsDemandLoaded);
/************************************************************************
* Routine Name:			RemoveNTDriver
* Function Description:	Remove NT Driver
* Parameters List:
*      None.	
* Return value:			Return status of initial result
*************************************************************************/
BOOL _stdcall RemoveNTDriver();
/************************************************************************
* Routine Name:			StartNTDriver
* Function Description:	Start NT Driver
* Parameters List:
*      None.	
* Return value:			Return status of initial result
*************************************************************************/
BOOL _stdcall StartNTDriver();
/************************************************************************
* Routine Name:			StopNTDriver
* Function Description:	Stop NT Driver
* Parameters List:
*      None.	
* Return value:			Return status of initial result
*************************************************************************/
BOOL _stdcall StopNTDriver();
/************************************************************************
* Routine Name:			Read_PCI_Byte
* Function Description:	Read a byte from configuration space of input PCI address.					
* Argument List:
*      In  dPCIAddress:	PCI configuration address(0x80000000|Bus number shl 16|Dev number shl 11|Fun number shl 8|Register offset) 		
*      Out pbValue:		Return the address of input buffer.
* Return value:			Return BOOL
*************************************************************************/
BOOL _stdcall Read_PCI_Byte(UINT32 dPCIAddress,PBYTE pbValue);
/************************************************************************
* Routine Name:			Read_PCI_Word
* Function Description:	Read a Word from configuration space of input PCI address.					
* Argument List:
*      In  dPCIAddress:	PCI configuration address(0x80000000|Bus number shl 16|Dev number shl 11|Fun number shl 8|Register offset) 		
*      Out pwValue:		Return the address of input buffer.
* Return value:			Return BOOL
*************************************************************************/
BOOL _stdcall Read_PCI_Word(UINT32 dPCIAddress,PWORD pwValue);
/************************************************************************
* Routine Name:			Read_PCI_Dword
* Function Description:	Read a Dword from configuration space of input PCI address.					
* Argument List:
*      In  dPCIAddress:	PCI configuration address(0x80000000|Bus number shl 16|Dev number shl 11|Fun number shl 8|Register offset) 		
*      Out pdValue:		Return the address of input buffer.
* Return value:			Return BOOL
*************************************************************************/
BOOL _stdcall Read_PCI_Dword(UINT32 dPCIAddress,PDWORD pdValue);
/************************************************************************
* Routine Name:			Write_PCI_Byte
* Function Description:	Write a byte to configuration space of input PCI address.					
* Argument List:
*      In  dPCIAddress:	PCI configuration address(0x80000000|Bus number shl 16|Dev number shl 11|Fun number shl 8|Register offset) 		
*      In  pbValue:		Point to the value should be written.
* Return value:			Return BOOL
*************************************************************************/
BOOL _stdcall Write_PCI_Byte(UINT32 dPCIAddress,PBYTE pbValue);
/************************************************************************
* Routine Name:			Write_PCI_Word
* Function Description:	Write a word to configuration space of input PCI address.					
* Argument List:
*      In  dPCIAddress:	PCI configuration address(0x80000000|Bus number shl 16|Dev number shl 11|Fun number shl 8|Register offset) 		
*      In  pwValue:		Point to the value should be written.
* Return value:			Return BOOL
*************************************************************************/
BOOL _stdcall Write_PCI_Word(UINT32 dPCIAddress,PWORD pwValue);
/************************************************************************
* Routine Name:			Write_PCI_Dword
* Function Description:	Write a dword to configuration space of input PCI address.					
* Argument List:
*      In  dPCIAddress:	PCI configuration address(0x80000000|Bus number shl 16|Dev number shl 11|Fun number shl 8|Register offset) 		
*      In  pdValue:		Point to the value should be written.
* Return value:			Return BOOL
*************************************************************************/
BOOL _stdcall Write_PCI_Dword(UINT32 dPCIAddress,PDWORD pdValue);
/************************************************************************
* Routine Name:			Read_PCI_Byte_Sync
* Function Description:	Read a byte from configuration space of input PCI address.					
* Argument List:
*      In  dPCIAddress:	PCI configuration address(0x80000000|Bus number shl 16|Dev number shl 11|Fun number shl 8|Register offset) 		
*      Out pbValue:		Return the address of input buffer.
* Return value:			Return BOOL
*************************************************************************/
BOOL _stdcall Read_PCI_Byte_Sync(UINT32 dPCIAddress,PBYTE pbValue);
/************************************************************************
* Routine Name:			Read_PCI_Word_Sync
* Function Description:	Read a Word from configuration space of input PCI address.					
* Argument List:
*      In  dPCIAddress:	PCI configuration address(0x80000000|Bus number shl 16|Dev number shl 11|Fun number shl 8|Register offset) 		
*      Out pwValue:		Return the address of input buffer.
* Return value:			Return BOOL
*************************************************************************/
BOOL _stdcall Read_PCI_Word_Sync(UINT32 dPCIAddress,PWORD pwValue);
/************************************************************************
* Routine Name:			Read_PCI_Dword
* Function Description:	Read a Dword from configuration space of input PCI address.					
* Argument List:
*      In  dPCIAddress:	PCI configuration address(0x80000000|Bus number shl 16|Dev number shl 11|Fun number shl 8|Register offset) 		
*      Out pdValue:		Return the address of input buffer.
* Return value:			Return BOOL
*************************************************************************/
BOOL _stdcall Read_PCI_Dword_Sync(UINT32 dPCIAddress,PDWORD pdValue);
/************************************************************************
* Routine Name:			Write_PCI_Byte_Sync
* Function Description:	Write a byte to configuration space of input PCI address.					
* Argument List:
*      In  dPCIAddress:	PCI configuration address(0x80000000|Bus number shl 16|Dev number shl 11|Fun number shl 8|Register offset) 		
*      In  pbValue:		Point to the value should be written.
* Return value:			Return BOOL
*************************************************************************/
BOOL _stdcall Write_PCI_Byte_Sync(UINT32 dPCIAddress,PBYTE pbValue);
/************************************************************************
* Routine Name:			Write_PCI_Word_Sync
* Function Description:	Write a word to configuration space of input PCI address.					
* Argument List:
*      In  dPCIAddress:	PCI configuration address(0x80000000|Bus number shl 16|Dev number shl 11|Fun number shl 8|Register offset) 		
*      In  pwValue:		Point to the value should be written.
* Return value:			Return BOOL
*************************************************************************/
BOOL _stdcall Write_PCI_Word_Sync(UINT32 dPCIAddress,PWORD pwValue);
/************************************************************************
* Routine Name:			Write_PCI_Dword_Sync
* Function Description:	Write a dword to configuration space of input PCI address.					
* Argument List:
*      In  dPCIAddress:	PCI configuration address(0x80000000|Bus number shl 16|Dev number shl 11|Fun number shl 8|Register offset) 		
*      In  pdValue:		Point to the value should be written.
* Return value:			Return BOOL
*************************************************************************/
BOOL _stdcall Write_PCI_Dword_Sync(UINT32 dPCIAddress,PDWORD pdValue);

/************************************************************************
* Routine Name:			Dump_PCI_Config
* Function Description:	Dump PCI configuration space of input PCI address.					
* Argument List:
*      In  dPCIAddress:		PCI configuration address(0x80000000|Bus number shl 16|Dev number shl 11|Fun number shl 8|Register offset). 		
*      In  dDumpDataSize:	How many bytes wanted.
*	   Out bDumpData[]:		Dump data returned.
* Return value:			Return BOOL
*************************************************************************/
BOOL _stdcall Dump_PCI_Config(UINT32 dPCIAddress,UINT8 bDumpData[],UINT16 dDumpDataSize);
/************************************************************************
* Routine Name:			Read_Io_Byte
* Function Description:	Read a byte from io port.					
* Argument List:
*      In  wPortAddress:Io Port Address.	 		
*      Out pbValue:		Return the address of input buffer.
* Return value:			Return BOOL
*************************************************************************/
BOOL _stdcall Read_Io_Byte(UINT16 wPortAddress,PBYTE pbValue);
/************************************************************************
* Routine Name:			Read_Io_Word
* Function Description:	Read a word from io port.					
* Argument List:
*      In  wPortAddress:Io Port Address.	 		
*      Out pwValue:		Return the address of input buffer.
* Return value:			Return BOOL
*************************************************************************/
BOOL _stdcall Read_Io_Word(UINT16 wPortAddress,PWORD pwValue);
/************************************************************************
* Routine Name:			Read_Io_Dword
* Function Description:	Read a dword from io port.					
* Argument List:
*      In  wPortAddress:Io Port Address.	 		
*      Out pdValue:		Return the address of input buffer.
* Return value:			Return BOOL
*************************************************************************/
BOOL _stdcall Read_Io_Dword(UINT16 wPortAddress,PDWORD pdValue);
/************************************************************************
* Routine Name:			Write_Io_Byte
* Function Description:	Write a byte to io port.					
* Argument List:
*      In  wPortAddress:Io Port Address.	 		
*      In  pbValue:		Point to the value should be written..
* Return value:			Return BOOL
*************************************************************************/
BOOL _stdcall Write_Io_Byte(UINT16 wPortAddress,PBYTE pbValue);
/************************************************************************
* Routine Name:			Write_Io_Word
* Function Description:	Write a word to io port.					
* Argument List:
*      In  wPortAddress:Io Port Address.	 		
*      In  pwValue:		Point to the value should be written.
* Return value:			Return BOOL
*************************************************************************/
BOOL _stdcall Write_Io_Word(UINT16 wPortAddress,PWORD pwValue);
/************************************************************************
* Routine Name:			Write_Io_Dword
* Function Description:	Write a dword to io port.					
* Argument List:
*      In  wPortAddress:Io Port Address.	 		
*      In  pdValue:		Point to the value should be written..
* Return value:			Return BOOL
*************************************************************************/
BOOL _stdcall Write_Io_Dword(UINT16 wPortAddress,PDWORD pdValue);
/************************************************************************
* Routine Name:			Dump_Io_Port
* Function Description:	Dump io port data of input io port address.					
* Argument List:
*      In  wPortAddress:	Io port address.	
*      In  dDumpDataSize:	How many bytes wanted.
*	   Out bDumpData[]:		Dump data returned.
* Return value:			Return BOOL
*************************************************************************/
BOOL _stdcall Dump_Io_Port(UINT16 wPortAddress,UINT8 bDumpData[],UINT16 dDumpDataSize);
/************************************************************************
* Routine Name:			Read_IndexIo_Byte
* Function Description:	Read a byte from index io port.					
* Argument List:
*      In  wPortAddress:	Io Port Address.	
*      In  bIndexIoAddress: Select register address.
*      Out  pbValue:		Return the address of input buffer.	
* Return value:			Return BOOL
*************************************************************************/
BOOL _stdcall Read_IndexIo_Byte(UINT16 wPortAddress,UINT8 bIndexIoAddress,PBYTE pbValue);
/************************************************************************
* Routine Name:			Write_IndexIo_Byte
* Function Description:	Write a byte to index io port.					
* Argument List:
*      In  wPortAddress:	Io Port Address.	
*      In  bIndexIoAddress: Select register address.
*      In  pbValue:			Point to the value should be written.
* Return value:			Return BOOL
*************************************************************************/
BOOL _stdcall Write_IndexIo_Byte(UINT16 wPortAddress,UINT8 bIndexIoAddress,PBYTE pbValue);
/************************************************************************
* Routine Name:			Dump_Index_Io
* Function Description:	Dump index io port data of input io port address.					
* Argument List:
*      In  wPortAddress:	Index Io port address.	
*      In  bIndexIoAddress: Select register address.
*      In  dDumpDataSize:	How many bytes wanted.
*	   Out bDumpData[]:		Dump data returned.
* Return value:			Return BOOL
*************************************************************************/
BOOL _stdcall Dump_Index_Io(UINT16 wPortAddress,UINT8 bIndexIoAddress,UINT8 bDumpData[],UINT16 dDumpDataSize);
/************************************************************************
* Routine Name:			Read_Mem_Byte
* Function Description:	Read a byte from specified physical memory address.					
* Argument List:
*	In  PhysAddress:	Physical memory address.
*	Out pbPhysVal:		Value of input physical memory.
* Return value:			Return BOOL.
*************************************************************************/
BOOL _stdcall Read_Mem_Byte(UINT64 PhysAddress, PBYTE pbPhysVal);
/************************************************************************
* Routine Name:			Read_Mem_Word
* Function Description:	Read a word from specified physical memory address.					
* Argument List:
*	In  PhysAddress:	Physical memory address.
*	Out pwPhysVal:		Value of input physical memory.
* Return value:			Return BOOL.
*************************************************************************/
BOOL _stdcall Read_Mem_Word(UINT64 PhysAddress, PWORD pwPhysVal);
/************************************************************************
* Routine Name:			Read_Mem_Dword
* Function Description:	Read a dword from specified physical memory address.					
* Argument List:
*	In  PhysAddress:	Physical memory address.
*	Out pdPhysVal:		Value of input physical memory.
* Return value:			Return BOOL.
*************************************************************************/
BOOL _stdcall Read_Mem_Dword(UINT64 PhysAddress, PDWORD pdPhysVal);
/************************************************************************
* Routine Name:			Write_Mem_Byte
* Function Description:	Write a byte to specified physical memory address.					
* Argument List:
*	In  PhysAddress:	Physical memory address.
*	In	bPhysVal:		Value of input physical memory.
* Return value:			Return BOOL.
*************************************************************************/
BOOL _stdcall Write_Mem_Byte(UINT64 PhysAddress, BYTE bPhysVal);
/************************************************************************
* Routine Name:			Write_Mem_Word
* Function Description:	Write a word to specified physical memory address.					
* Argument List:
*	In  PhysAddress:	Physical memory address.
*	In	wPhysVal:		Value of input physical memory.
* Return value:			Return BOOL.
*************************************************************************/
BOOL _stdcall Write_Mem_Word(UINT64 PhysAddress, WORD wPhysVal);
/************************************************************************
* Routine Name:			Write_Mem_Dword
* Function Description:	Write a dword to specified physical memory address.					
* Argument List:
*	In  PhysAddress:	Physical memory address.
*	In	dPhysVal:		Value of input physical memory.
* Return value:			Return BOOL.
*************************************************************************/
BOOL _stdcall Write_Mem_Dword(UINT64 PhysAddress, DWORD dPhysVal);
/************************************************************************
* Routine Name:			Dump_PhysMem
* Function Description:	Dump physcial memory.					
* Argument List:
*	In  PhysAddress:		Physical memory address.
*	In	PhysMemSizeInBytes:	How many bytes would be dumped(should below 4KB,for one page).
*	Out bDumpData[]:		Dump data returned.
* Return value:			Return BOOL.
*************************************************************************/
BOOL _stdcall Dump_PhysMem(ULONG PhysAddress,UINT8 bDumpData[],ULONG PhysMemSizeInBytes);
/************************************************************************
* Routine Name:			Allocate_Physical_Memory
* Function Description:	Allocate physcial memory.					
* Argument List:
*	In	PhysMemSizeInBytes:	How many bytes would be allocate.
*	Out PhysAddress:	Allocate physical memory address returned.
* Return value:			Return BOOL.
*************************************************************************/
BOOL _stdcall Allocate_Physical_Memory(ULONG PhysMemSizeInBytes,PDWORD PhysAddress,PQWORD pvPhysMemLin);
/************************************************************************
* Routine Name:			Free_Physical_Memory
* Function Description:	Free physcial memory.					
* Argument List:
*	In	pvPhysMemLin:	The Linear address to be free.
* Return value:			Return BOOL.
*************************************************************************/
BOOL _stdcall Free_Physical_Memory(VOID *POINTER_64 pvPhysMemLin);
/************************************************************************
* Routine Name:			Read_MSR
* Function Description:	Implement CPU RDMSR instruction.					
* Argument List:
*      In  dMsrAddress:	MSR address
*      Out *pdEdx:*pdEax	EDX:EAX.
* Return value:			Return BOOL
*************************************************************************/
BOOL _stdcall Read_MSR(UINT32 dMsrAddress,PDWORD pdEdx,PDWORD pdEax);
/************************************************************************
* Routine Name:			Write_MSR
* Function Description:	Implement CPU RDMSR instruction.					
* Argument List:
*      In  dMsrAddress:	MSR address
*      In  *pdEdx:*pdEax	EDX:EAX.
* Return value:			Return BOOL
*************************************************************************/
BOOL _stdcall Write_MSR(UINT32 dMsrAddress,PDWORD pdEdx,PDWORD pdEax);

/************************************************************************
* Routine Name:			Get_MemLin
* Function Description:	Get_MemLin.					
* Argument List:
*	In	PhysMemSizeInBytes:		How many bytes would be allocate.
*	In  PhysAddress:			Physical memory address.
*	Out	pvPhysMemLin:			Point to allocate physical memory linear address.
*	Out	PhysicalMemoryHandle:	Point to  physical memory Handle.	
* Return value:			Return BOOL.
*************************************************************************/
BOOL _stdcall Get_MemLin(ULONG PhysAddress,ULONG PhysMemSizeInBytes,PVOID *ppPhysMemLin,HANDLE	*PhysicalMemoryHandle);

/************************************************************************
* Routine Name:			Free_MemLin
* Function Description:	Free_MemLin.					
* Argument List:
*	In	pvPhysMemLin:			Point to allocate physical memory linear address.
*	In	PhysicalMemoryHandle:	Point to  physical memory Handle,this handle get from Get_MemLin() function.	
* Return value:			Return BOOL.
*************************************************************************/
BOOL _stdcall Free_MemLin(PVOID pvPhysMemLin,HANDLE	PhysicalMemoryHandle);

/************************************************************************
* Routine Name:			ACPI_acquire_global_lock
* Function Description:	ACPI_acquire_global_lock.					
* Argument List:
*	none.
* Return value:			Return BOOL.
*************************************************************************/
BOOL _stdcall  ACPI_acquire_global_lock();

/************************************************************************
* Routine Name:			ACPI_release_global_lock
* Function Description:	ACPI_release_global_lock.					
* Argument List:
*	none.
* Return value:			Return BOOL.
*************************************************************************/
BOOL _stdcall  ACPI_release_global_lock();

/************************************************************************
* Routine Name:			Enable_Direct_Io
* Function Description:	Enable direct IO access in RING 3 for current proccess.					
* Argument List:
*      None
* Return value:			Return BOOL
*************************************************************************/
//BOOL _stdcall Enable_Direct_Io(void);

/************************************************************************
* Routine Name:			Disable_Direct_Io
* Function Description:	Disable direct IO access in RING 3 for current proccess.					
* Argument List:
*      None
* Return value:			Return BOOL
*************************************************************************/
//BOOL _stdcall Enable_Direct_Io(void);
 /************************************************************************
* Routine Name:			Set_Port_Val_Reg
* Function Description:	Set port and registers.
* Argument List:
*		WORD:			wPortAddr
*		DWORD			dwPortVal
*		BYTE			bSize
*		Registers		reg
* Return value:			Return BOOL
*************************************************************************/
 BOOL _stdcall Set_Port_Val_Reg(WORD wPortAddr, DWORD dwPortVal, BYTE bSize, Registers reg);

/************************************************************************
* Routine Name:			Set_Port_Val_Reg_Get_Reg
* Function Description:	Set port and registers and then get registers value.
* Argument List:
*		WORD:			wPortAddr
*		DWORD			dwPortVal
*		BYTE			bSize
*		Registers		reg
* Return value:			Return BOOL
NOTE:not Support ARM 
*************************************************************************/
BOOL _stdcall Set_Port_Val_Reg_Get_Reg(WORD wPortAddr, DWORD dwPortVal, BYTE bSize, Registers * reg);

 #endif
