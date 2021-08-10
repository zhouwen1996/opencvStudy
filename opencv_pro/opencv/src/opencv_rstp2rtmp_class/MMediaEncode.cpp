#include "MMediaEncode.h"
extern "C"
{
#include <libswscale/swscale.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
#include "libavutil/imgutils.h"
}

#pragma comment(lib, "swscale.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avutil.lib")
#include <iostream>
using namespace std;

class CXMediaEncode : public CMMediaEncode
{
	bool InitScale() {
		//转换的输出内存申请
		pFrameYUV = av_frame_alloc();
		pFrameYUV->format = AV_PIX_FMT_YUV420P;
		pFrameYUV->width = inWidht;
		pFrameYUV->height = inHeight;
		pFrameYUV->pts = 0;
		int nYUVNum = av_image_get_buffer_size(AV_PIX_FMT_YUV420P, pFrameYUV->width, pFrameYUV->height, 1);
		pYUVBuff = (uint8_t *)av_malloc(nYUVNum * sizeof(uint8_t));
		av_image_fill_arrays(pFrameYUV->data, pFrameYUV->linesize, pYUVBuff, AV_PIX_FMT_YUV420P, pFrameYUV->width, pFrameYUV->height, 1);
		
		pFrameBGR = av_frame_alloc();
		pFrameBGR->format = AV_PIX_FMT_BGR24;
		pFrameBGR->width = inWidht;
		pFrameBGR->height = inHeight;
		pFrameBGR->pts = 0;
		int nBGRNum = av_image_get_buffer_size(AV_PIX_FMT_BGR24, pFrameBGR->width, pFrameBGR->height, 1);
		pBGRBuff = (uint8_t *)av_malloc(nBGRNum * sizeof(uint8_t));
		av_image_fill_arrays(pFrameBGR->data, pFrameBGR->linesize, pBGRBuff, AV_PIX_FMT_BGR24, pFrameBGR->width, pFrameBGR->height, 1);
	}
};



CMMediaEncode::CMMediaEncode()
{
}


CMMediaEncode::~CMMediaEncode()
{
}

CMMediaEncode * CMMediaEncode::Get(unsigned char index = 0)
{
	static bool isFirst = true;
	if (isFirst)
	{
		//注册所有的编解码器
		avcodec_register_all();
		isFirst = false;
	}

	static CXMediaEncode cxm[255];
	return &cxm[index];
}