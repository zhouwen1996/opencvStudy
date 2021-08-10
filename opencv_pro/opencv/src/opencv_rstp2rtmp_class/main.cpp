#include "opencv2\core.hpp"
#include "opencv2\opencv.hpp"
#include <iostream>

#ifdef __cplusplus
extern "C"
{
#endif // !__cplusplus

#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
#include "libswresample/swresample.h"//包含头文件
#include "libavdevice/avdevice.h"
#include "libavutil/imgutils.h"
#include "libavutil/avutil.h"
#ifdef __cplusplus
}
#endif // !__cplusplus


#pragma comment(lib,"avcodec.lib")
#pragma comment(lib,"avdevice.lib")
#pragma comment(lib,"avfilter.lib")
#pragma comment(lib,"avformat.lib")
#pragma comment(lib,"avutil.lib")
#pragma comment(lib,"postproc.lib")
#pragma comment(lib,"swresample.lib")
#pragma comment(lib,"swscale.lib")


using namespace std;
using namespace cv;
int main()
{
	VideoCapture cam;
	Mat Cameraframe;
	SwsContext *vsc = NULL;//BGRA2YUV 像素格式转换
	int ret;
	//nginx-rtmp 直播服务器rtmp推流URL
	char *outUrl = "rtmp://192.168.27.128/live";

	avcodec_register_all();
	av_register_all();
	avformat_network_init();

	//编码器上下文
	AVCodecContext *vc = NULL;
	//rtmp flv 封装器上下文
	AVFormatContext *ic = NULL;

	//1、opencv打开摄像头
	try
	{
		cam.open(0);
		if (!cam.isOpened())
		{
			throw exception("cam open failed!");
		}
		int inWidht = cam.get(CAP_PROP_FRAME_WIDTH);
		int inHeight = cam.get(CAP_PROP_FRAME_HEIGHT);
		int fps = cam.get(CAP_PROP_FPS);

		//转换的输出内存申请
		AVFrame *pFrameYUV = NULL;
		uint8_t	*pYUVBuff = NULL;
		pFrameYUV = av_frame_alloc();
		pFrameYUV->format = AV_PIX_FMT_YUV420P;
		pFrameYUV->width = inWidht;
		pFrameYUV->height = inHeight;
		pFrameYUV->pts = 0;
		int nYUVNum = av_image_get_buffer_size(AV_PIX_FMT_YUV420P, pFrameYUV->width, pFrameYUV->height, 1);
		pYUVBuff = (uint8_t *)av_malloc(nYUVNum * sizeof(uint8_t));
		av_image_fill_arrays(pFrameYUV->data, pFrameYUV->linesize, pYUVBuff, AV_PIX_FMT_YUV420P, pFrameYUV->width, pFrameYUV->height, 1);
		AVFrame *pFrameBGR = NULL;
		uint8_t	*pBGRBuff = NULL;
		pFrameBGR = av_frame_alloc();
		pFrameBGR->format = AV_PIX_FMT_BGR24;
		pFrameBGR->width = inWidht;
		pFrameBGR->height = inHeight;
		pFrameBGR->pts = 0;
		int nBGRNum = av_image_get_buffer_size(AV_PIX_FMT_BGR24, pFrameBGR->width, pFrameBGR->height, 1);
		pBGRBuff = (uint8_t *)av_malloc(nBGRNum * sizeof(uint8_t));
		av_image_fill_arrays(pFrameBGR->data, pFrameBGR->linesize, pBGRBuff, AV_PIX_FMT_BGR24, pFrameBGR->width, pFrameBGR->height, 1);

		 //找到编码器
		AVCodec *codec  = avcodec_find_encoder(AV_CODEC_ID_H264);
		if (!codec)
		{
			throw exception("Can`t find h264 encoder!");
		}

		//创建编码器上下文
		vc = avcodec_alloc_context3(codec);
		if (!vc)
		{
			throw exception("avcodec_alloc_context3 Fail!");
		}
		//配置编码器参数
		//流媒体数据在每一段于一段之间都包含sps这些属性数据帧的信息
		vc->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;//全局参数，如果是流媒体没有倒没什么关系，但是如果是写入文件就有关系了（目的就是对方一打开就知道你的文件格式）
		vc->codec_id = codec->id;
		vc->thread_count = 8;//编码的线程数量 可以通过获取cpu的线程或设置

		vc->bit_rate = 50*1024*8;//压缩后每秒视频的bit大小 也就是码率 如果带宽比较小那么你就要压缩更小一点
		vc->width = inWidht;
		vc->height = inHeight;
		vc->time_base = { 1, fps };//每帧数据加一  就是pts以什么数进行计算，时间基数最终都会换算成秒，
		vc->framerate = { fps, 1 };//帧率
		vc->gop_size = 50;//画面组的大小，就是多少个一个关键帧 (一组数据就是头帧为I帧，解码都是需要从I帧开始)
		vc->max_b_frames = 0;//设置b帧数量为0 那么pts和bts相等
		vc->pix_fmt = AV_PIX_FMT_YUV420P;

		//打开编码器上下文
		ret = avcodec_open2(vc, 0, 0);//编码器可以在这里传入也可也在上面指定
		if (ret != 0)
		{
			char buf[1024] = { 0 };
			av_strerror(ret, buf, sizeof(buf)-1);
			throw exception(buf);
		}

		//输出封装器和视频流配置
		//创建输出封装器的上下文
		ret = avformat_alloc_output_context2(&ic, 0, "flv", outUrl);
		if (ret != 0)
		{
			char buf[1024] = { 0 };
			av_strerror(ret, buf, sizeof(buf) - 1);
			throw exception(buf);
		}
		//添加视频流
		AVStream *vs = avformat_new_stream(ic, NULL);
		if (!vs)
		{
			throw exception("avformat_new_stream Failed");
		}
		vs->codecpar->codec_tag = 0;//指定编码格式
		//从编码器复制参数
		avcodec_parameters_from_context(vs->codecpar, vc);
		av_dump_format(ic, 0, outUrl, 1);

		//打开rtmp的网络输出IO
		ret = avio_open(&ic->pb, outUrl, AVIO_FLAG_WRITE);
		if (ret != 0)
		{
			char buf[1024] = { 0 };
			av_strerror(ret, buf, sizeof(buf) - 1);
			throw exception(buf);
		}
		//写入封装头  针对流媒体是可以不用写尾的，而如果输出到文件就是需要的
		ret = avformat_write_header(ic, NULL); //注意这一步是会把我们设置好的timebase修改的，因此下面使用的时候要直接从流里面获取而不是当初设置的值
		if (ret != 0)
		{
			char buf[1024] = { 0 };
			av_strerror(ret, buf, sizeof(buf) - 1);
			throw exception(buf);
		}


		AVPacket avpkt;
		memset(&avpkt, 0, sizeof(avpkt));
		int vpts = 0;
		for (;;)
		{
			///读取rtsp视频帧，解码视频帧
			/*if (!cam.grab())
			{
				continue;
			}
			///yuv转换为rgb  //可以选择跳帧，读取两帧转换一帧来提供效率
			if (!cam.retrieve(Cameraframe))
			{
				continue;
			}*/
			cam.read(Cameraframe);
			//imshow("video", Cameraframe);
			//waitKey(100);

			//2、BGRA to yuv
			//sws_getCachedContext 帧有变化的时候才会调用释放之前的创建新的
			vsc = sws_getCachedContext(vsc, inWidht, inHeight, AV_PIX_FMT_BGR24, inWidht, inHeight, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
			if (!vsc)
			{
				throw exception("sws_getCachedContext fail!");
			}
			//输入数据结构  这种直接使用opencv传出来的内存进行sws_scale的时候会崩溃？？？
			//uint8_t *indata[AV_NUM_DATA_POINTERS] = { 0 };
			//打包格式就是 indata【0】 bgrabgrabgra都放在一起
			//平面格式就是 indata【0】bbbbb indata【1】gggggg indata【2】   rrrrr
			//indata[0] = Cameraframe.data;
			//一行(宽)数据的字节数
			//int insize[AV_NUM_DATA_POINTERS] = { 0 };
			//int size = Cameraframe.elemSize();
			//insize[0] = Cameraframe.cols*Cameraframe.rows * Cameraframe.elemSize();		
			memcpy(pBGRBuff, Cameraframe.data, Cameraframe.cols*Cameraframe.rows * Cameraframe.elemSize());

			if (vsc)
			{
				int h = sws_scale(vsc, pFrameBGR->data, pFrameBGR->linesize, 0, inHeight, pFrameYUV->data, pFrameYUV->linesize);
				//int h = sws_scale(vsc, (const uint8_t *const *)indata, insize, 0, inHeight, pFrameYUV->data, pFrameYUV->linesize);
				if (h < 0)
				{
					continue;
				}
				//cout << "h = " << h << endl << flush;
			}
			//3、编码H264
			pFrameYUV->pts = vpts++;
			ret = avcodec_send_frame(vc, pFrameYUV);//发送帧到编码器
			if (ret != 0)
				continue;
			ret =  avcodec_receive_packet(vc, &avpkt);//从编码器读取编码好的包
			if (ret != 0 || avpkt.size > 0)
			{

			}
			else
			{
				continue;
			}

			//4、推流
			//时间戳换算 原始的包pts是基于vc的timebase，现在应该修改为ic vs的timebase
			avpkt.pts = av_rescale_q(avpkt.pts, vc->time_base, vs->time_base);
			avpkt.dts = av_rescale_q(avpkt.dts, vc->time_base, vs->time_base);
			ret = av_interleaved_write_frame(ic, &avpkt);//缓冲排序(因为pts和dts不一致)的并且会被pkg会在内部索引减一
			if (ret == 0)
			{
				cout << "#" << flush;
			}
		}
	}
	catch (exception &ex)
	{
		if (cam.isOpened())
			cam.release();
		if (vsc)
		{
			sws_freeContext(vsc);
			vsc = NULL;
		}
		if (vc)
		{
			avio_closep(&ic->pb);
			ic->pb = NULL;//要注意置为NULL
			avcodec_free_context(&vc);
		}
		cerr << ex.what() << endl;
	}
	system("pause");
	return 0;
}