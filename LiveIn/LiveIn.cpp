/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		LiveIn.cpp
* @brief	This Program is LiveIn Project.
* @author	alopex
* @version	v1.00a
* @date		2019-01-05
*/
#include "LiveIn.h"

// CLiveIn��

//----------------------------------------------
// @Function:	CLiveIn()
// @Purpose: CLiveIn���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
CLiveIn::CLiveIn()
{
	m_pDirectGraphicsMain = NULL;
	m_pDirectGraphics3DMain = NULL;
	m_pCerasusfpsMain = NULL;
}

//----------------------------------------------
// @Function:	~CLiveIn()
// @Purpose: CLiveIn��������
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
CLiveIn::~CLiveIn()
{
	SAFE_DELETE(m_pCerasusfpsMain);
	SAFE_DELETE(m_pDirectGraphics3DMain);
	SAFE_DELETE(m_pDirectGraphicsMain);
}

//----------------------------------------------
// @Function:	CLiveInInit()
// @Purpose: CLiveIn��ʼ��
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
BOOL CLiveIn::CLiveInInit()
{
	HRESULT hr;
	IDirect3DDevice9* pD3D9Device = NULL;

	// DirectGraphics ��ʼ��
	m_pDirectGraphicsMain = new DirectGraphics();
	hr = m_pDirectGraphicsMain->DirectGraphicsInit(g_hWnd, true, USER_WINDOWWIDTH, USER_WINDOWHEIGHT);
	if (FAILED(hr))
	{
		MessageBox(g_hWnd, _T("Direct3D��ʼ��ʧ��!"), _T("����"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	hr = m_pDirectGraphicsMain->DirectGraphicsFontInit(20);
	if (FAILED(hr))
	{
		MessageBox(g_hWnd, _T("DirectFont��ʼ��ʧ��!"), _T("����"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	pD3D9Device = m_pDirectGraphicsMain->DirectGraphicsGetDevice();		// DirectX�豸ָ��

	// DirectGraphics3D ��ʼ��
	m_pDirectGraphics3DMain = new DirectGraphics3D(pD3D9Device);
	hr = m_pDirectGraphics3DMain->DirectGraphics3DInitVertex3DBase(6);
	if (FAILED(hr))
	{
		MessageBox(g_hWnd, _T("DirectGraphics3D��ʼ��ʧ��!"), _T("����"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	// Cerasusfps ��ʼ��
	m_pCerasusfpsMain = new CCerasusfps(pD3D9Device);
	hr = m_pCerasusfpsMain->CCerasusfpsInit(20);
	if (FAILED(hr))
	{
		MessageBox(g_hWnd, _T("Cerasusfps��ʼ��ʧ��!"), _T("����"), MB_OK | MB_ICONERROR);
		return FALSE;
	}


	return TRUE;
}

//----------------------------------------------
// @Function:	CLiveInRelease()
// @Purpose: CLiveIn�ͷ�
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInRelease()
{
	SAFE_DELETE(m_pCerasusfpsMain);
	SAFE_DELETE(m_pDirectGraphics3DMain);
	SAFE_DELETE(m_pDirectGraphicsMain);
}

//----------------------------------------------
// @Function:	CLiveInUpdate()
// @Purpose: CLiveInˢ��
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInUpdate()
{
	HRESULT hr;
	IDirect3DSurface9* pD3D9Surface = NULL;

	// DirectGraphics �����豸Э������
	hr = m_pDirectGraphicsMain->DirectGraphicsTestCooperativeLevel();
	if (hr != S_OK)
	{
		if (hr == D3DERR_DEVICELOST)	// DirectX �豸��ʧ
		{
			return;
		}

		if (hr == D3DERR_DEVICENOTRESET)	// DirectX �豸����
		{
			// ��ʧ�豸
			m_pCerasusfpsMain->CCerasusfpsReset();
			m_pDirectGraphics3DMain->DirectGraphics3DReset();
			m_pDirectGraphicsMain->DirectGraphicsReset();

			// �����豸
			m_pDirectGraphics3DMain->DirectGraphics3DInitVertex3DBase(6);
		}

	}
}

//----------------------------------------------
// @Function:	CLiveInRender()
// @Purpose: CLiveIn��Ⱦ
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveInRender()
{
	IDirect3DDevice9* pD3D9Device = NULL;
	RECT Rect;

	GetClientRect(g_hWnd, &Rect);
	pD3D9Device = m_pDirectGraphicsMain->DirectGraphicsGetDevice();

	// DirectX ��ʼ����
	m_pDirectGraphicsMain->DirectGraphicsBegin();

	// ��Ⱦģʽ:Alpha�������
	pD3D9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);					// Alpha��Ͽ���

	// ��Ⱦģʽ:����������
	pD3D9Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DISABLE);

	m_pDirectGraphics3DMain->DirectGraphics3DRenderStateLightDisable();			// ��Ⱦ��Դ�ر�
	m_pDirectGraphics3DMain->DirectGraphics3DRenderStateSetting();				// ��Ⱦ״̬����
	m_pDirectGraphics3DMain->DirectGraphics3DRenderStateAlphaDisable();			// Alpha��Ϲر�

	CLiveDrawAdapter();			// �����Կ��ͺ�
	CLiveDrawfps();				// ����fps

	// DirectX ��������
	m_pDirectGraphicsMain->DirectGraphicsEnd();
}

//----------------------------------------------
// @Function:	CLiveDrawAdapter()
// @Purpose: CLiveIn�����Կ���Ϣ
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveDrawAdapter()
{
	RECT Rect;

	GetClientRect(g_hWnd, &Rect);

	// Direct3D �����Կ���Ϣ
	Rect.top += 0;
	m_pDirectGraphicsMain->DirectGraphicsFontDrawTextAdapterType(&Rect, DT_TOP | DT_LEFT, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));

	// Direct3D ������Ļ�ֱ���
	Rect.top += 20;
	m_pDirectGraphicsMain->DirectGraphicsFontDrawTextScreen(&Rect, DT_TOP | DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f));

	// Direct3D ���ƻ���ģ��
	Rect.top += 20;
	m_pDirectGraphicsMain->DirectGraphicsFontDrawTextFormat(&Rect, DT_TOP | DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f));
}

//----------------------------------------------
// @Function:	CLiveDrawfps()
// @Purpose: CLiveIn����fps
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------
void CLiveIn::CLiveDrawfps()
{
	m_pCerasusfpsMain->CCerasusfpsGetfps();				// Direct3D ���ƾ�̬��Ϣ
	m_pCerasusfpsMain->CCerasusfpsDrawfps(g_hWnd);		// Direct3D ����fps
}
