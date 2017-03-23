/*
Code by BoyceHong.
Time at 2016.07.19.
Any problem cantact solidman@msn.cn
*/

#include "Main.h"

#pragma comment(lib,"Winmm.lib")
using namespace std;


void Hint(void)
{
	printf("\n  ===========================================================\n");
	printf("                  ASUSTek ACPI SCI Detector\n");
	printf("  ===========================================================\n\n");
	printf("  NOTE:\n");
	printf("  [1] Make sure SCI supported in the running platform.\n");
	printf("  [2] Press Ctrl + Z to quit. If not,the log file will miss.\n");
	printf("  -----------------------------------------------------------\n\n");
}

/*
  Judge if there is EC component on target platform.
	Return TURE:  Support
	Return FALSE: Not Support
*/
BOOL isECSupport(void)
{
	UINT8 pBuffer[1000];
	UINT retVal = 0;

	retVal = GetSystemFirmwareTable('ACPI', 'TDCE', pBuffer, 1000);

	return retVal;
}

/*
  Get the GPE0 block registers and GPE0 block length from ACPI table.
*/
BOOL GetGPEParameter(UINT32 *GPE0_BLK, UINT8 *GPE0_BLK_LEN)
{
	ACPI_HDR AcpiHeader = { 0 };
	UINT8 * pBuffer = NULL;
	FACP_20 FACPTable_20 = { 0 };
	FACP_30 FACPTable_30 = { 0 };
	FACP_50 FACPTable_50 = { 0 };
	FACP_60 FACPTable_60 = { 0 };
	UINT retVal = 0;

	retVal = GetSystemFirmwareTable('ACPI', 'PCAF', &AcpiHeader, sizeof(AcpiHeader));
	if (retVal > sizeof(AcpiHeader)) {
		UINT bufferSize = 0;

		bufferSize = retVal;
		pBuffer = new UINT8[bufferSize];
		retVal = GetSystemFirmwareTable('ACPI', 'PCAF', pBuffer, bufferSize);
		AcpiHeader = *(ACPI_HDR *)pBuffer;
		delete(pBuffer);
	}
	if (!retVal) {
		return -1;
	}
	else {
		switch (AcpiHeader.Revision) {
		case 2: {
			retVal = GetSystemFirmwareTable('ACPI', 'PCAF', &FACPTable_20, sizeof(FACPTable_20));
			if (retVal < 95)
				return -1;
			(*GPE0_BLK) = FACPTable_20.GPE0_BLK;
			(*GPE0_BLK_LEN) = FACPTable_20.GPE0_BLK_LEN;
			break;
		}
		case 3: {
			retVal = GetSystemFirmwareTable('ACPI', 'PCAF', &FACPTable_30, sizeof(FACPTable_30));
			if (retVal < 95)
				return -1;
			(*GPE0_BLK) = FACPTable_30.GPE0_BLK;
			(*GPE0_BLK_LEN) = FACPTable_30.GPE0_BLK_LEN;
			break;
		}
		case 5: {
			retVal = GetSystemFirmwareTable('ACPI', 'PCAF', &FACPTable_50, sizeof(FACPTable_50));
			if (retVal < 95)
				return -1;
			(*GPE0_BLK) = FACPTable_50.GPE0_BLK;
			(*GPE0_BLK_LEN) = FACPTable_50.GPE0_BLK_LEN;
			break;
		}
		case 6: {
			retVal = GetSystemFirmwareTable('ACPI', 'PCAF', &FACPTable_60, sizeof(FACPTable_60));
			if (retVal < 95)
				return -1;
			(*GPE0_BLK) = FACPTable_60.GPE0_BLK;
			(*GPE0_BLK_LEN) = FACPTable_60.GPE0_BLK_LEN;
			break;
		}
		default: {
			printf("[SCI Detector Warning]  This tool only support ACPI FACP version 2/3/5/6 platform\n");
			printf("			Your Computer Platform ACPI FACP version:%d\n", AcpiHeader.Revision);
			return -1;
		}
		}
	}
	return 0;
}

/*
  Return the log2(arg).
*/
UINT8 log2(UINT32 value)
{
	if (1 == value)
		return 0;
	else
		return (1 + log2(value >> 1));
}

/*
  Get the Qxx from EC 0x60/0x64.
*/
UINT8 QueryCommand(LPVOID pDataPack)
{
	UINT8 Data = 0;

	while ((!(_inp(EC_SC) & 0x20)) && ((DATA_PACKET *)pDataPack)->isDetecting);
	if (!((DATA_PACKET *)pDataPack)->isDetecting)
		return 0;

	Data = _inp(EC_DATA);

	return Data;
}

/*
  New thread to record log into local file.
*/
DWORD WINAPI RecordLog(LPVOID pDataPack)
{
	HANDLE gEvent = NULL;
	PDATA_PACKET pLocalDataPack = NULL;
	FILE *fp = NULL;

	pLocalDataPack = (DATA_PACKET *)pDataPack;

	gEvent = OpenEvent(SYNCHRONIZE, FALSE, L"TimerEvent");
	if (NULL != gEvent) {	
		fopen_s(&fp, "SciDetector.log", "w+");
		if (fp == NULL) {
			printf("[SCI Detector Warning]	Open log file failed\n");
			CloseHandle(gEvent);
			return -1;
		}

		fprintf(fp, "\n  ===========================================================\n");
		fprintf(fp, "                  ASUSTek ACPI SCI Detector\n");
		fprintf(fp, "  ===========================================================\n\n");
		fprintf(fp, "  NOTE:\n");
		fprintf(fp, "  [1] Make sure SCI supported in the running platform\n");
		fprintf(fp, "  [2] Press Ctrl + Z to quit. If not,the log file will miss.\n");
		fprintf(fp, "  -----------------------------------------------------------\n\n");

		while (pLocalDataPack->isDetecting) {
			WaitForSingleObject(gEvent, 100);
			ResetEvent(gEvent);

			if (!isEmpty(((DATA_PACKET *)pDataPack)->headPtr)) {
				fprintf(fp, "%s",dequeue(&(((DATA_PACKET *)pDataPack)->headPtr), &(((DATA_PACKET *)pDataPack)->tailPtr)));
			}
		}
	}

	while (!isEmpty(((DATA_PACKET *)pDataPack)->headPtr)) {
		fprintf(fp, "%s", dequeue(&(((DATA_PACKET *)pDataPack)->headPtr), &(((DATA_PACKET *)pDataPack)->tailPtr)));
	}

	printf("[SCI Detector]	Exit RecordLog Thread\n");
	fprintf(fp, "[SCI Detector]	Exit RecordLog Thread\n");

	fclose(fp);
	CloseHandle(gEvent);
	return 0;
}

/*
  New thread to query Lxx event from GPE0 block directly.
*/
DWORD WINAPI QueryLxx(LPVOID pDataPack)
{
	HANDLE gEvent = NULL;
	unsigned long GPE_Status = 0;
	UINT8 i, oldEventNumber, eventNumber = 0;
	BOOL isNoneKey = FALSE;
	DATA_PACKET dataPack = { 0 };
	UINT8       QueryFreq;
	CHAR  string[50];

	dataPack = (*(DATA_PACKET *)pDataPack);
	QueryFreq = dataPack.QueryLxxFreq;
	if (!QueryFreq)
		QueryFreq = 20;

	gEvent = OpenEvent(SYNCHRONIZE, FALSE, L"TimerEvent");
	if (NULL != gEvent) {
		while (((DATA_PACKET *)pDataPack)->isDetecting) {
			//WaitForSingleObject(((DATA_PACKET *)pDataPack)->gMutex, INFINITE);
			WaitForSingleObject(gEvent, QueryFreq);
			ResetEvent(gEvent);
			
			i = 0;
			while (!(GPE_Status = _inpd(dataPack.GPE0_BLK + 4 * i++))) {
				if ((dataPack.GPE0_BLK_LEN / 8) == i)
					break;
			}		
			if (GPE_Status) {		
				oldEventNumber = eventNumber;
				eventNumber = log2(GPE_Status) + (i - 1) * 32;
				if (eventNumber != oldEventNumber) {
					printf("[SCI Detector] _L%02x\n", eventNumber);
					memset(string, 0, 50);
					sprintf_s(string, 49, "[SCI Detector] _L%02x\n", eventNumber);
					enqueue(&(((DATA_PACKET *)pDataPack)->headPtr), &(((DATA_PACKET *)pDataPack)->tailPtr), string);
				}
				if (isNoneKey) {
					printf("[SCI Detector] _L%02x\n", eventNumber);
					memset(string, 0, 50);
					sprintf_s(string, 49, "[SCI Detector] _L%02x\n", eventNumber);
					enqueue(&(((DATA_PACKET *)pDataPack)->headPtr), &(((DATA_PACKET *)pDataPack)->tailPtr), string);
				}
					
				isNoneKey = FALSE;
			}
			else {
				isNoneKey = TRUE;
			}
			//ReleaseMutex(((DATA_PACKET *)pDataPack)->gMutex);
		}
	}
	printf("[SCI Detector]	Exit Detect Lxx Thread\n");
	memset(string, 0, 50);
	sprintf_s(string, 49, "[SCI Detector]	Exit Detect Lxx Thread\n");
	enqueue(&(((DATA_PACKET *)pDataPack)->headPtr), &(((DATA_PACKET *)pDataPack)->tailPtr), string);

	CloseHandle(gEvent);
	return 0;
}

/*
  New thread to query Qxx from EC.
*/
DWORD WINAPI QueryQxx(LPVOID pDataPack)
{
	HANDLE gEvent = NULL;
	unsigned long GPE_Status = 0;
	UINT8 eventNumber = 0;
	DATA_PACKET dataPack = { 0 };
	UINT8       QueryFreq;
	CHAR  string[50];

	dataPack = (*(DATA_PACKET *)pDataPack);
	QueryFreq = dataPack.QueryQxxFreq;
	if (!QueryFreq)
		QueryFreq = 70;

	gEvent = OpenEvent(SYNCHRONIZE, FALSE, L"TimerEvent");
	if (NULL != gEvent) {
		while (((DATA_PACKET *)pDataPack)->isDetecting) {
			WaitForSingleObject(((DATA_PACKET *)pDataPack)->gMutex, INFINITE);
			WaitForSingleObject(gEvent, QueryFreq);
			ResetEvent(gEvent);

			eventNumber = QueryCommand(pDataPack);
			if (eventNumber) {
				printf("[SCI Detector] _Q%02x\n", eventNumber);
				memset(string, 0, 50);
				sprintf_s(string, 49, "[SCI Detector] _Q%02x\n", eventNumber);
				enqueue(&(((DATA_PACKET *)pDataPack)->headPtr), &(((DATA_PACKET *)pDataPack)->tailPtr), string);
			}
				
			ReleaseMutex(((DATA_PACKET *)pDataPack)->gMutex);
		}
	}

	printf("[SCI Detector]	Exit Detect Qxx Thread\n");
	memset(string, 0, 50);
	sprintf_s(string, 49, "[SCI Detector]	Exit Detect Qxx Thread\n");
	enqueue(&(((DATA_PACKET *)pDataPack)->headPtr), &(((DATA_PACKET *)pDataPack)->tailPtr), string);

	CloseHandle(gEvent);
	return 0;
}

/*
  Main method.
*/
int _tmain(int argc, _TCHAR* argv[])
{
	LoadATSZIoDriver();

	int index = 0;
	HANDLE gEvent, hThread[3];
	HWND m_hWnd = NULL;
	BOOL ret = 0;
	DATA_PACKET dataPack = { 0 };

	Hint();
	dataPack.isECSupport = isECSupport();
	ret = GetGPEParameter(&(dataPack.GPE0_BLK), &(dataPack.GPE0_BLK_LEN));
	if (ret) {
		printf("[SCI Detector Warning]	Get ACPI FACP Table Failed\n");
		return -1;	
	}

	//printf("GPE0_BLK:0x%X  GPE0_BLK_LEN:%d(Bytes)\n", GPE0_BLK, GPE0_BLK_LEN);

	if (NULL == (gEvent = CreateEvent(NULL, TRUE, FALSE, L"TimerEvent"))) {
		printf("[SCI Detector Warning]	Creat Timer Event Failed\n");
		return -1;
	}

	dataPack.isDetecting = TRUE;
	dataPack.gMutex = CreateMutex(NULL, FALSE, NULL);
	dataPack.headPtr = NULL;
	dataPack.tailPtr = NULL;

	hThread[0] = CreateThread(NULL, 0, QueryLxx, (LPVOID)&dataPack, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, RecordLog, (LPVOID)&dataPack, 0, NULL);
	if (dataPack.isECSupport) {
		hThread[2] = CreateThread(NULL, 0, QueryQxx, (LPVOID)&dataPack, 0, NULL);
	}
	
	while(getchar() != EOF);
	dataPack.isDetecting = FALSE;

	if (dataPack.isECSupport) {
		WaitForMultipleObjects(3, hThread, TRUE, INFINITE);
		CloseHandle(hThread[0]);
		CloseHandle(hThread[1]);
		CloseHandle(hThread[2]);
	}
	else {
		WaitForMultipleObjects(3, hThread, FALSE, INFINITE);
		CloseHandle(hThread[0]);
		CloseHandle(hThread[1]);
	}


	CloseHandle(dataPack.gMutex);
	CloseHandle(gEvent);
	RemoveNTDriver();
	return 0;
}
