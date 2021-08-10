#pragma once
//头文件中不引入ffmpeg头文件 从而发布的时候别人就可以不用包含ffmpeg库，我们直接吧ffmpeg库编入到里面了
struct AVFrame;
struct AVPacket;
class AVCodecContext;
///音视频编码接口类
//做成工程模式，也就是说对象的创建会由用户来创建
class CMMediaEncode
{
public:
	int inWidht;
	int inHeight;
	AVFrame *pFrameYUV = 0;
	uint8_t	*pYUVBuff = 0;
	AVFrame *pFrameBGR = 0;
	uint8_t	*pBGRBuff = 0;
	
	//工厂生产方法 获取对象(对象由内部来创建) 静态的
	static CMMediaEncode * Get(unsigned char index = 0);
	virtual ~CMMediaEncode();

	//初始化 视频转换参数
	virtual bool InitScale() = 0;
	//初始化 视频编码器
	virtual bool InitVideoCodec() = 0;
	//rgb2yuv
	virtual AVFrame* RGBToYUV(char *rgb) = 0;//定义纯虚函数就不需要有实现
	//视频编码
	virtual AVPacket * EncodeVideo(AVFrame* frame) = 0;

protected:
	CMMediaEncode();//在子类当中来创建对象，则将构造函数放在protected权限

private:

};
