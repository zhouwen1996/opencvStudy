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
#include "libswresample/swresample.h"//����ͷ�ļ�
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
	SwsContext *vsc = NULL;//BGRA2YUV ���ظ�ʽת��
	int ret;
	//nginx-rtmp ֱ��������rtmp����URL
	char *outUrl = "rtmp://192.168.27.128/live";

	avcodec_register_all();
	av_register_all();
	avformat_network_init();

	//������������
	AVCodecContext *vc = NULL;
	//rtmp flv ��װ��������
	AVFormatContext *ic = NULL;

	//1��opencv������ͷ
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

		//ת��������ڴ�����
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

		 //�ҵ�������
		AVCodec *codec  = avcodec_find_encoder(AV_CODEC_ID_H264);
		if (!codec)
		{
			throw exception("Can`t find h264 encoder!");
		}

		//����������������
		vc = avcodec_alloc_context3(codec);
		if (!vc)
		{
			throw exception("avcodec_alloc_context3 Fail!");
		}
		//���ñ���������
		//��ý��������ÿһ����һ��֮�䶼����sps��Щ��������֡����Ϣ
		vc->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;//ȫ�ֲ������������ý��û�е�ûʲô��ϵ�����������д���ļ����й�ϵ�ˣ�Ŀ�ľ��ǶԷ�һ�򿪾�֪������ļ���ʽ��
		vc->codec_id = codec->id;
		vc->thread_count = 8;//������߳����� ����ͨ����ȡcpu���̻߳�����

		vc->bit_rate = 50*1024*8;//ѹ����ÿ����Ƶ��bit��С Ҳ�������� �������Ƚ�С��ô���Ҫѹ����Сһ��
		vc->width = inWidht;
		vc->height = inHeight;
		vc->time_base = { 1, fps };//ÿ֡���ݼ�һ  ����pts��ʲô�����м��㣬ʱ��������ն��ỻ����룬
		vc->framerate = { fps, 1 };//֡��
		vc->gop_size = 50;//������Ĵ�С�����Ƕ��ٸ�һ���ؼ�֡ (һ�����ݾ���ͷ֡ΪI֡�����붼����Ҫ��I֡��ʼ)
		vc->max_b_frames = 0;//����b֡����Ϊ0 ��ôpts��bts���
		vc->pix_fmt = AV_PIX_FMT_YUV420P;

		//�򿪱�����������
		ret = avcodec_open2(vc, 0, 0);//���������������ﴫ��Ҳ��Ҳ������ָ��
		if (ret != 0)
		{
			char buf[1024] = { 0 };
			av_strerror(ret, buf, sizeof(buf)-1);
			throw exception(buf);
		}

		//�����װ������Ƶ������
		//���������װ����������
		ret = avformat_alloc_output_context2(&ic, 0, "flv", outUrl);
		if (ret != 0)
		{
			char buf[1024] = { 0 };
			av_strerror(ret, buf, sizeof(buf) - 1);
			throw exception(buf);
		}
		//�����Ƶ��
		AVStream *vs = avformat_new_stream(ic, NULL);
		if (!vs)
		{
			throw exception("avformat_new_stream Failed");
		}
		vs->codecpar->codec_tag = 0;//ָ�������ʽ
		//�ӱ��������Ʋ���
		avcodec_parameters_from_context(vs->codecpar, vc);
		av_dump_format(ic, 0, outUrl, 1);

		//��rtmp���������IO
		ret = avio_open(&ic->pb, outUrl, AVIO_FLAG_WRITE);
		if (ret != 0)
		{
			char buf[1024] = { 0 };
			av_strerror(ret, buf, sizeof(buf) - 1);
			throw exception(buf);
		}
		//д���װͷ  �����ý���ǿ��Բ���дβ�ģ������������ļ�������Ҫ��
		ret = avformat_write_header(ic, NULL); //ע����һ���ǻ���������úõ�timebase�޸ĵģ��������ʹ�õ�ʱ��Ҫֱ�Ӵ��������ȡ�����ǵ������õ�ֵ
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
			///��ȡrtsp��Ƶ֡��������Ƶ֡
			/*if (!cam.grab())
			{
				continue;
			}
			///yuvת��Ϊrgb  //����ѡ����֡����ȡ��֡ת��һ֡���ṩЧ��
			if (!cam.retrieve(Cameraframe))
			{
				continue;
			}*/
			cam.read(Cameraframe);
			//imshow("video", Cameraframe);
			//waitKey(100);

			//2��BGRA to yuv
			//sws_getCachedContext ֡�б仯��ʱ��Ż�����ͷ�֮ǰ�Ĵ����µ�
			vsc = sws_getCachedContext(vsc, inWidht, inHeight, AV_PIX_FMT_BGR24, inWidht, inHeight, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
			if (!vsc)
			{
				throw exception("sws_getCachedContext fail!");
			}
			//�������ݽṹ  ����ֱ��ʹ��opencv���������ڴ����sws_scale��ʱ������������
			//uint8_t *indata[AV_NUM_DATA_POINTERS] = { 0 };
			//�����ʽ���� indata��0�� bgrabgrabgra������һ��
			//ƽ���ʽ���� indata��0��bbbbb indata��1��gggggg indata��2��   rrrrr
			//indata[0] = Cameraframe.data;
			//һ��(��)���ݵ��ֽ���
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
			//3������H264
			pFrameYUV->pts = vpts++;
			ret = avcodec_send_frame(vc, pFrameYUV);//����֡��������
			if (ret != 0)
				continue;
			ret =  avcodec_receive_packet(vc, &avpkt);//�ӱ�������ȡ����õİ�
			if (ret != 0 || avpkt.size > 0)
			{

			}
			else
			{
				continue;
			}

			//4������
			//ʱ������� ԭʼ�İ�pts�ǻ���vc��timebase������Ӧ���޸�Ϊic vs��timebase
			avpkt.pts = av_rescale_q(avpkt.pts, vc->time_base, vs->time_base);
			avpkt.dts = av_rescale_q(avpkt.dts, vc->time_base, vs->time_base);
			ret = av_interleaved_write_frame(ic, &avpkt);//��������(��Ϊpts��dts��һ��)�Ĳ��һᱻpkg�����ڲ�������һ
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
			ic->pb = NULL;//Ҫע����ΪNULL
			avcodec_free_context(&vc);
		}
		cerr << ex.what() << endl;
	}
	system("pause");
	return 0;
}