#pragma once
//ͷ�ļ��в�����ffmpegͷ�ļ� �Ӷ�������ʱ����˾Ϳ��Բ��ð���ffmpeg�⣬����ֱ�Ӱ�ffmpeg����뵽������
struct AVFrame;
struct AVPacket;
class AVCodecContext;
///����Ƶ����ӿ���
//���ɹ���ģʽ��Ҳ����˵����Ĵ��������û�������
class CMMediaEncode
{
public:
	int inWidht;
	int inHeight;
	AVFrame *pFrameYUV = 0;
	uint8_t	*pYUVBuff = 0;
	AVFrame *pFrameBGR = 0;
	uint8_t	*pBGRBuff = 0;
	
	//������������ ��ȡ����(�������ڲ�������) ��̬��
	static CMMediaEncode * Get(unsigned char index = 0);
	virtual ~CMMediaEncode();

	//��ʼ�� ��Ƶת������
	virtual bool InitScale() = 0;
	//��ʼ�� ��Ƶ������
	virtual bool InitVideoCodec() = 0;
	//rgb2yuv
	virtual AVFrame* RGBToYUV(char *rgb) = 0;//���崿�麯���Ͳ���Ҫ��ʵ��
	//��Ƶ����
	virtual AVPacket * EncodeVideo(AVFrame* frame) = 0;

protected:
	CMMediaEncode();//�����൱�������������򽫹��캯������protectedȨ��

private:

};
