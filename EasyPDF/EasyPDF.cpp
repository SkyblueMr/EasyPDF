// EasyPDF.cpp : CEasyPDFApp �� DLL ע���ʵ�֡�

#include "stdafx.h"
#include "EasyPDF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CEasyPDFApp theApp;

const GUID CDECL _tlid = { 0x19901D3B, 0x6D4D, 0x4FE8, { 0x9B, 0x74, 0xC4, 0x8B, 0xF2, 0xE8, 0x5, 0x6A } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CEasyPDFApp::InitInstance - DLL ��ʼ��

BOOL CEasyPDFApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: �ڴ�������Լ���ģ���ʼ�����롣
	}

	return bInit;
}



// CEasyPDFApp::ExitInstance - DLL ��ֹ

int CEasyPDFApp::ExitInstance()
{
	// TODO: �ڴ�������Լ���ģ����ֹ���롣

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - ������ӵ�ϵͳע���

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - �����ϵͳע������Ƴ�

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
