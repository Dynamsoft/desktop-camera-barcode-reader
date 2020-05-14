#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
#include "DynamsoftBarcodeReader.h"
#include "BarcodeReaderConfig.h"

#if defined(LINUX) || defined(MACOS)
#include <sys/time.h>
#endif

using namespace cv;
using namespace std;
using std::cout; 
using std::cerr; 
using std::endl;

#define DBR_EXCEPTION(iRet) {                                       		\
		if (iRet != 0)												\
		{															\
			printf("%s\n", CBarcodeReader::GetErrorString(iRet));	\
			return -1;												\
		}															\
    }																\

void ToHexString(unsigned char* pSrc, int iLen, char* pDest)
{
	const char HEXCHARS[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

	int i;
	char* ptr = pDest;

	for (i = 0; i < iLen; ++i)
	{
		snprintf(ptr, 4, "%c%c ", HEXCHARS[(pSrc[i] & 0xF0) >> 4], HEXCHARS[(pSrc[i] & 0x0F) >> 0]);
		ptr += 3;
	}
}


void textResultCallback(int frameId, TextResultArray *pResults, void * pUser)
{
	char * pszTemp = NULL;
	char * pszTemp1 = NULL;
	char * pszTemp2 = NULL;
	pszTemp = (char*)malloc(4096);

	if (pResults->resultsCount == 0)
	{
		snprintf(pszTemp, 4096, "No barcode found.\r\n\r\n");
		printf(pszTemp);
		free(pszTemp);
		CBarcodeReader::FreeTextResults(&pResults);
		return;
	}

	snprintf(pszTemp, 4096, "\r\n\r\nframe = %d,Total barcode(s) found: %d.\n", frameId, pResults->resultsCount);
	printf(pszTemp);
	for (int iIndex = 0; iIndex < pResults->resultsCount; iIndex++)
	{
		snprintf(pszTemp, 4096, "Barcode %d:\r\n", iIndex + 1);
		printf(pszTemp);
		snprintf(pszTemp, 4096, "    Type: %s\r\n", pResults->results[iIndex]->barcodeFormatString);
		printf(pszTemp);
		snprintf(pszTemp, 4096, "    Value: %s\r\n", pResults->results[iIndex]->barcodeText);
		printf(pszTemp);

		pszTemp1 = (char*)malloc(pResults->results[iIndex]->barcodeBytesLength * 3 + 1);
		pszTemp2 = (char*)malloc(pResults->results[iIndex]->barcodeBytesLength*3 + 100);
		ToHexString(pResults->results[iIndex]->barcodeBytes, pResults->results[iIndex]->barcodeBytesLength, pszTemp1);
		snprintf(pszTemp2, pResults->results[iIndex]->barcodeBytesLength*3 + 100, "    Hex Data: %s\r\n", pszTemp1);
		printf(pszTemp2);
		free(pszTemp1);
		free(pszTemp2);
	}
	free(pszTemp);

	CBarcodeReader::FreeTextResults(&pResults);
}

void errorcb(int frameId, int errorCode, void * pUser)
{
	char * pszTemp = NULL;
	pszTemp = (char*)malloc(4096);
	if (errorCode != DBR_OK && errorCode != DBRERR_LICENSE_EXPIRED && errorCode != DBRERR_QR_LICENSE_INVALID &&
		errorCode != DBRERR_1D_LICENSE_INVALID && errorCode != DBRERR_PDF417_LICENSE_INVALID && errorCode != DBRERR_DATAMATRIX_LICENSE_INVALID)
	{
		snprintf(pszTemp, 4096, "Failed to read barcode: %s\r\n", CBarcodeReader::GetErrorString(errorCode));
		printf(pszTemp);
		free(pszTemp);
		return;
	}
	free(pszTemp);
}


int main()
{
	//getchar();
	Mat frame;
	cout << "Opening camera..." << endl;
	VideoCapture capture(0); // open the first camera
	if (!capture.isOpened())
	{
		cerr << "ERROR: Can't initialize camera capture" << endl;
		return 1;
	}
	 
	int iRet = -1;
	CBarcodeReader reader;
	iRet = reader.InitLicense("t0068NQAAAKNCY2jE+ejBfIcqyimfaH9+hLqkYHAf47zau3kRog9ZLssuVdB4V/3JyHVlQRmnf9UkOrMPmYJKGHziUOZeGJI=");
	if (iRet != 0)
	{
		printf("%s\n", CBarcodeReader::GetErrorString(iRet));
	}
	PublicRuntimeSettings runtimeSettings;
	char szErrorMsg[256];
	//Best coverage settings
	reader.InitRuntimeSettingsWithString("{\"ImageParameter\":{\"Name\":\"BestCoverage\",\"DeblurLevel\":9,\"ExpectedBarcodesCount\":512,\"ScaleDownThreshold\":100000,\"LocalizationModes\":[{\"Mode\":\"LM_CONNECTED_BLOCKS\"},{\"Mode\":\"LM_SCAN_DIRECTLY\"},{\"Mode\":\"LM_STATISTICS\"},{\"Mode\":\"LM_LINES\"},{\"Mode\":\"LM_STATISTICS_MARKS\"}],\"GrayscaleTransformationModes\":[{\"Mode\":\"GTM_ORIGINAL\"},{\"Mode\":\"GTM_INVERTED\"}]}}", CM_OVERWRITE, szErrorMsg, 256);
	//Best speed settings
	//reader.InitRuntimeSettingsWithString("{\"ImageParameter\":{\"Name\":\"BestSpeed\",\"DeblurLevel\":3,\"ExpectedBarcodesCount\":512,\"LocalizationModes\":[{\"Mode\":\"LM_SCAN_DIRECTLY\"}],\"TextFilterModes\":[{\"MinImageDimension\":262144,\"Mode\":\"TFM_GENERAL_CONTOUR\"}]}}",CM_OVERWRITE,szErrorMsg,256);
	//Balance settings
	//reader.InitRuntimeSettingsWithString("{\"ImageParameter\":{\"Name\":\"Balance\",\"DeblurLevel\":5,\"ExpectedBarcodesCount\":512,\"LocalizationModes\":[{\"Mode\":\"LM_CONNECTED_BLOCKS\"},{\"Mode\":\"LM_STATISTICS\"}]}}",CM_OVERWRITE,szErrorMsg,256);
	reader.GetRuntimeSettings(&runtimeSettings);
	runtimeSettings.barcodeFormatIds = BF_ALL;
	runtimeSettings.barcodeFormatIds_2 = BF2_POSTALCODE | BF2_DOTCODE;
	runtimeSettings.intermediateResultTypes = IRT_ORIGINAL_IMAGE;
	DBR_EXCEPTION(reader.UpdateRuntimeSettings(&runtimeSettings,szErrorMsg,256));
	DBR_EXCEPTION(reader.SetTextResultCallback(textResultCallback,NULL));
	DBR_EXCEPTION(reader.SetErrorCallback(errorcb, NULL));
	capture >> frame;
	int width = capture.get(CAP_PROP_FRAME_WIDTH);
	int height = capture.get(CAP_PROP_FRAME_HEIGHT);
	int format = capture.get(CAP_PROP_FORMAT);
	int t = frame.type();
	int depth = frame.depth();
	int chnnel = frame.channels();
	iRet = reader.StartFrameDecoding(30, 30, width, height, frame.step.p[0], IPF_RGB_888, "");
	if (iRet != 0)
	{
		printf("%s\n", CBarcodeReader::GetErrorString(iRet));
		return -1;
	}
	for (;;)
	{
		capture >> frame; // read the next frame from camera
		if (frame.empty())
		{
			cerr << "ERROR: Can't grab camera frame." << endl;
			break;
		}	
		reader.AppendFrame(frame.data);

		imshow("Frame", frame);
		int key = waitKey(1);
		if (key == 27/*ESC*/)
			break;
	}

	reader.StopFrameDecoding();
	
	return 0;
}