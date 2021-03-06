/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, alopex
*     All rights reserved.
*
* @file		LiveCoreThread.cpp
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2019-04-14
*/
#include "LiveCoreThread.h"
#include "LiveCore.h"

#pragma warning (disable:4996)

extern CLiveCore* g_pLiveCore;

extern CRITICAL_SECTION g_csDecode;
extern volatile bool g_bDecodeFlag;

//------------------------------------------------------------------
// @Function:	 CLiveCoreThread()
// @Purpose: CLiveCoreThread构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveCoreThread::CLiveCoreThread()
{
}

//------------------------------------------------------------------
// @Function:	 ~CLiveCoreThread()
// @Purpose: CLiveCoreThread析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveCoreThread::~CLiveCoreThread()
{
}

//------------------------------------------------------------------
// @Function:	 CLiveCoreThread()
// @Purpose: CLiveCoreThread线程运行
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void __stdcall CLiveCoreThread::PlumThreadRun()
{
	AVFormatContext* pFormatCtx;
	AVCodecContext* pCodecCtx;
	AVCodec* pCodec;
	AVFrame* pFrame;
	AVFrame* pFrameYUV;

	av_register_all();//注册所有组件
	avformat_network_init();//初始化网络播放
	pFormatCtx = avformat_alloc_context();//初始化一个AVFormatContext

	//打开输入的视频文件
	if (avformat_open_input(&pFormatCtx, g_pLiveCore->m_chLiveCoreVideoAddress, NULL, NULL) != 0)
	{
		MessageBox(g_hWnd, L"打开文件失败!", L"错误", MB_OK | MB_ICONERROR);
		EnterCriticalSection(&g_csDecode);
		CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Can not Open Video File.");
		LeaveCriticalSection(&g_csDecode);
		return;
	}

	EnterCriticalSection(&g_csDecode);
	CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Succeed Open Video File.");
	LeaveCriticalSection(&g_csDecode);

	//获取视频文件信息
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
	{
		MessageBox(g_hWnd, L"无法读取文件信息!", L"错误", MB_OK | MB_ICONERROR);
		EnterCriticalSection(&g_csDecode);
		CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Fail Read Video File.");
		LeaveCriticalSection(&g_csDecode);
		return;
	}

	EnterCriticalSection(&g_csDecode);
	CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Succeed Read Video File.");
	LeaveCriticalSection(&g_csDecode);

	int VideoIndex = -1;

	for (int i = 0; i < pFormatCtx->nb_streams; i++)
	{
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			VideoIndex = i;
			break;
		}
	}

	if (VideoIndex == -1)
	{
		MessageBox(g_hWnd, L"未读取到视频信息!", L"错误", MB_OK | MB_ICONERROR);
		EnterCriticalSection(&g_csDecode);
		CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Fail Read Video Info.");
		LeaveCriticalSection(&g_csDecode);
		return;
	}

	EnterCriticalSection(&g_csDecode);
	CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Succeed Read Video Info.");
	LeaveCriticalSection(&g_csDecode);

	pCodecCtx = pFormatCtx->streams[VideoIndex]->codec;

	//查找解码器
	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL)
	{
		MessageBox(g_hWnd, L"未查找到解码器!", L"错误", MB_OK | MB_ICONERROR);
		EnterCriticalSection(&g_csDecode);
		CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Fail Find Codec ID.");
		LeaveCriticalSection(&g_csDecode);
		return;
	}

	EnterCriticalSection(&g_csDecode);
	CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Succeed Find Codec ID.");
	LeaveCriticalSection(&g_csDecode);

	//打开解码器
	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
	{
		MessageBox(g_hWnd, L"无法打开解码器!", L"错误", MB_OK | MB_ICONERROR);
		EnterCriticalSection(&g_csDecode);
		CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Fail Open Codec.");
		LeaveCriticalSection(&g_csDecode);
		return;
	}

	EnterCriticalSection(&g_csDecode);
	CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Succeed Open Codec.");
	LeaveCriticalSection(&g_csDecode);

	uint8_t* OutBuffer;
	AVPacket* Packet;

	pFrame = av_frame_alloc();
	pFrameYUV = av_frame_alloc();

	OutBuffer = (uint8_t*)av_malloc(avpicture_get_size(AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height));
	avpicture_fill((AVPicture*)pFrameYUV, OutBuffer, AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height);
	Packet = (AVPacket*)av_malloc(sizeof(AVPacket));

	int nSize = pCodecCtx->width * pCodecCtx->height;

	g_pLiveCore->m_nVideoWidth = pCodecCtx->width;
	g_pLiveCore->m_nVideoHeight = pCodecCtx->height;

	g_pArrayY = new unsigned char[nSize];
	g_pArrayU = new unsigned char[nSize];
	g_pArrayV = new unsigned char[nSize];
	memset(g_pArrayY, 0, nSize);
	memset(g_pArrayU, 0, nSize);
	memset(g_pArrayV, 0, nSize);

	av_dump_format(pFormatCtx, 0, g_pLiveCore->m_chLiveCoreVideoAddress, 0);

	//读取一帧压缩数据
	int ret;
	int got_picture;
	int y_size;
	struct SwsContext* img_convert_ctx;

	img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);

	while (true)
	{

		while (av_read_frame(pFormatCtx, Packet) >= 0)
		{
			if (Packet->stream_index == VideoIndex)
			{
				ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, Packet);//解码一帧压缩数据
				if (ret < 0)
				{
					return;
				}
				if (got_picture)
				{
					sws_scale(img_convert_ctx, (const uint8_t * const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height, pFrameYUV->data, pFrameYUV->linesize);
					y_size = pCodecCtx->width * pCodecCtx->height;

					while (g_bDecodeFlag);

					EnterCriticalSection(&g_csDecode);
					memset(g_pArrayY, 0, nSize);
					memset(g_pArrayU, 0, nSize);
					memset(g_pArrayV, 0, nSize);
					memcpy_s(g_pArrayY, nSize, pFrameYUV->data[0], y_size);
					memcpy_s(g_pArrayU, nSize, pFrameYUV->data[1], y_size / 4);
					memcpy_s(g_pArrayV, nSize, pFrameYUV->data[2], y_size / 4);
					g_bDecodeFlag = true;

					if (g_pLiveCore->m_nLiveCoreLogProcess)
					{
						CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Decode One frame.\n");
					}

					LeaveCriticalSection(&g_csDecode);
				}
			}
			av_free_packet(Packet);
		}

		while (true)
		{
			ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, Packet);
			if (ret < 0)
			{
				break;
			}

			if (!got_picture)
			{
				break;
			}

			sws_scale(img_convert_ctx, (const uint8_t * const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height, pFrameYUV->data, pFrameYUV->linesize);
			y_size = pCodecCtx->width * pCodecCtx->height;

			while (g_bDecodeFlag);

			EnterCriticalSection(&g_csDecode);
			memset(g_pArrayY, 0, nSize);
			memset(g_pArrayU, 0, nSize);
			memset(g_pArrayV, 0, nSize);
			memcpy_s(g_pArrayY, nSize, pFrameYUV->data[0], y_size);
			memcpy_s(g_pArrayU, nSize, pFrameYUV->data[1], y_size / 4);
			memcpy_s(g_pArrayV, nSize, pFrameYUV->data[2], y_size / 4);
			g_bDecodeFlag = true;

			if (g_pLiveCore->m_nLiveCoreLogProcess)
			{
				CLiveCoreLog::LiveCoreLogExWriteLine(__FILE__, __LINE__, "Decode One frame.");
			}

			LeaveCriticalSection(&g_csDecode);
		}

		ret = av_seek_frame(pFormatCtx, VideoIndex, pFormatCtx->streams[VideoIndex]->start_time, 0);
		if (ret < 0)
		{
			break;
		}

		::PostMessageA((HWND)(g_pLiveCore->m_nLiveProjectWindowHandle), WM_USER + 2, (WPARAM)0, (LPARAM)0);

		avcodec_flush_buffers(pFormatCtx->streams[VideoIndex]->codec);
	}

	sws_freeContext(img_convert_ctx);

	av_frame_free(&pFrameYUV);
	av_frame_free(&pFrame);
	avcodec_close(pCodecCtx);
	avformat_close_input(&pFormatCtx);
}
