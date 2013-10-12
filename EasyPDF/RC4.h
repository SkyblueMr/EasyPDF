typedef struct rc4_key
{      
	unsigned char state[256];       
	unsigned char x;        
	unsigned char y;
}rc4_key;

class RC4
{
public:
	RC4(unsigned char *key_data_ptr,int nLen);//���ʼ��ʱ�����ִ�����ʼ��key
	void rc4_encode(unsigned char *buffer_ptr, int buffer_len);//�����밵��ʹ��ͬһ������ת��

private:
	rc4_key key;//����������õ���key����ʼ��ʱ����Ҫ��ֵ
	void prepare_key(unsigned char *key_data_ptr, int key_data_len);//��ʼ��key
	void swap_byte(unsigned char *a, unsigned char *b);//����

};