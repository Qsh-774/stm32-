#include <string.h>
#include <stdio.h>
#include "as608.h"
#include "manager.h"

u32 AS608Addr = 0XFFFFFFFF; //Ĭ��
char str2[6] = {0};
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
uint16_t  USART2_RX_STA = 0,IDM=0;
void delay_ms(u32 t)
{
	HAL_Delay(t);
}
//���ڷ���һ���ֽ�
static void MYUSART_SendData(u8 data)
{
	HAL_UART_Transmit(&huart2, &data,1,0xFFFF);
	//HAL_Delay(5);
}
//���Ͱ�ͷ
static void SendHead(void)
{
  MYUSART_SendData(0xEF);
  MYUSART_SendData(0x01);
}
//���͵�ַ
static void SendAddr(void)
{
  MYUSART_SendData(AS608Addr >> 24);
  MYUSART_SendData(AS608Addr >> 16);
  MYUSART_SendData(AS608Addr >> 8);
  MYUSART_SendData(AS608Addr);
}
//���Ͱ���ʶ,
static void SendFlag(u8 flag)
{
  MYUSART_SendData(flag);
}
//���Ͱ�����
static void SendLength(int length)
{
  MYUSART_SendData(length >> 8);
  MYUSART_SendData(length);
}
//����ָ����
static void Sendcmd(u8 cmd)
{
  MYUSART_SendData(cmd);
}
//����У���
static void SendCheck(u16 check)
{
  MYUSART_SendData(check >> 8);
  MYUSART_SendData(check);
}


////��֤���Ĭ������00000000H��
//unsigned char PS_VfyPwd()
//{
//	unsigned char querenma = 0xFF;		//����Ӧ�����ȷ����
//	unsigned char i;

//	//����ָ�����

//	/*��ͷ 2 bytes*/
//	SendByte(0xEF);
//	SendByte(0x01);

//	/*оƬ��ַ 4 bytes*/
//	SendByte(0xFF);
//	SendByte(0xFF);
//	SendByte(0xFF);
//	SendByte(0xFF);

//	/*����ʶ 1 byte*/
//	SendByte(0x01);

//	/*������ 2 bytes*/
//	SendByte(0x00);
//	SendByte(0x07);

//	/*ָ���� 1 byte*/
//	SendByte(0x13);

//	/*���� 4 bytes*/
//	SendByte(0x00);
//	SendByte(0x00);
//	SendByte(0x00);
//	SendByte(0x00);

//	/*У��� 2 bytes*/
//	SendByte(0x00);
//	SendByte(0x1B);

//	//����Ӧ�����

//	/*ǰ9λΪ��ͷ��оƬ��ַ������ʶ�������ȡ�Ϊ����Ҫ�Ĳ��֣������б���*/
//	for(i = 0; i <=9; i++)
//	{
//		HAL_UART_Receive_IT(&huart2,&querenma,1);
//	}

//	/*ȷ���� 1 byte*/
//	//querenma //= ReceiveByte();

//	/*У��� 2 bytes������Ҫ�������б���*/
//	uint8_t data;
//	HAL_UART_Receive(&huart2,&data,1,10);
//	HAL_UART_Receive(&huart2,&data,1,10);

//	return querenma;	//���ذ�Ϊȷ���� 	
//}

////¼��ָ��ͼ��
//unsigned char PS_GetImage()		
//{
//	unsigned char querenma = 0xFF;		//����Ӧ�����ȷ����
//	unsigned char i;

//	//����ָ�����

//	/*��ͷ 2 bytes*/
//	SendByte(0xEF);
//	SendByte(0x01);

//	/*оƬ��ַ 4 bytes*/
//	SendByte(0xFF);
//	SendByte(0xFF);
//	SendByte(0xFF);
//	SendByte(0xFF);

//	/*����ʶ 1 byte*/
//	SendByte(0x01);

//	/*������ 2 bytes*/
//	SendByte(0x00);
//	SendByte(0x03);

//	/*ָ���� 1 byte*/
//	SendByte(0x01);

//	/*У��� 2 bytes*/
//	SendByte(0x00);
//	SendByte(0x05);

//	//����Ӧ�����

//	/*ǰ9λΪ��ͷ��оƬ��ַ������ʶ�������ȡ�Ϊ����Ҫ�Ĳ��֣������б���*/
//	for(i = 0; i <=9; i++)
//	{
//		HAL_UART_Receive_IT(&huart2,&querenma,1);
//	}

//	/*ȷ���� 1 byte*/
//	//querenma //= ReceiveByte();

//	/*У��� 2 bytes������Ҫ�������б���*/
//	uint8_t data;
//	HAL_UART_Receive(&huart2,&data,1,10);
//	HAL_UART_Receive(&huart2,&data,1,10);
//	return querenma;	//���ذ�Ϊȷ���� 
//}	

////��������
//unsigned char PS_GenChar(unsigned char BufferID)
//{
//	unsigned char querenma = 0xFF;		//����Ӧ�����ȷ����
//	unsigned int summaf;		//16λУ���
//	unsigned char sum[2];			//2 * 8λУ���
//	unsigned char i;

//	//����ָ�����

//	/*��ͷ 2 bytes*/
//	SendByte(0xEF);
//	SendByte(0x01);

//	/*оƬ��ַ 4 bytes*/
//	SendByte(0xFF);
//	SendByte(0xFF);
//	SendByte(0xFF);
//	SendByte(0xFF);

//	/*����ʶ 1 byte*/
//	SendByte(0x01);

//	/*������ 2 bytes*/
//	SendByte(0x00);
//	SendByte(0x04);

//	/*ָ���� 1 byte*/
//	SendByte(0x02);

//	/*�������� 1 byte*/
//	SendByte(BufferID);

//	/*У��� 2 bytes*/
//	summaf = 0x07 + BufferID;		//����16λУ���
//	sum[0] = summaf;
//	sum[1] = summaf >> 8;	
//	SendByte(sum[1]);		//�ȷ��͸�8λ
//	SendByte(sum[0]);		//���͵�8λ

//	//����Ӧ���

//	/*ǰ9λΪ��ͷ��оƬ��ַ������ʶ�������ȡ�Ϊ����Ҫ�Ĳ��֣������б���*/
//	for(i = 0; i <=9; i++)
//	{
//		HAL_UART_Receive_IT(&huart2,&querenma,1);
//	}

//	/*ȷ���� 1 byte*/
//	//querenma //= ReceiveByte();

//	/*У��� 2 bytes������Ҫ�������б���*/
//	uint8_t data;
//	HAL_UART_Receive(&huart2,&data,1,10);
//	HAL_UART_Receive(&huart2,&data,1,10);
//	return querenma;	//���ذ�Ϊȷ���� 
//}

////�ϲ�����������ģ�壩
//unsigned char PS_RegModel()
//{
//	unsigned char querenma = 0xFF;		//����Ӧ�����ȷ����
//	unsigned char i;

//	//����ָ���

//	/*��ͷ 2 bytes*/
//	SendByte(0xEF);
//	SendByte(0x01);

//	/*оƬ��ַ 4 bytes*/
//	SendByte(0xFF);
//	SendByte(0xFF);
//	SendByte(0xFF);
//	SendByte(0xFF);

//	/*����ʶ 1 byte*/
//	SendByte(0x01);

//	/*������ 2 bytes*/
//	SendByte(0x00);
//	SendByte(0x03);
//	
//	/*ָ���� 1 byte*/
//	SendByte(0x05);

//	/*У��� 2 bytes*/
//	SendByte(0x00);
//	SendByte(0x09);

//	//����Ӧ���

//	/*ǰ9λΪ��ͷ��оƬ��ַ������ʶ�������ȡ�Ϊ����Ҫ�Ĳ��֣������б���*/
//	for(i = 0; i <=9; i++)
//	{
//		HAL_UART_Receive_IT(&huart2,&querenma,1);
//	}

//	/*ȷ���� 1 byte*/
//	//querenma //= ReceiveByte();

//	/*У��� 2 bytes������Ҫ�������б���*/
//	uint8_t data;
//	HAL_UART_Receive(&huart2,&data,1,10);
//	HAL_UART_Receive(&huart2,&data,1,10);

//	return querenma;	//���ذ�Ϊȷ���� 
//}

////����ģ��PS_StoreChar

//u8 PS_StoreChar(u8 BufferID,u16 PageID)
//{
//	unsigned char querenma = 0xFF;		//����Ӧ�����ȷ����
//	unsigned char page[2];		//2 * 8λλ�ú�
//	unsigned int summaf;		//16λУ���
//	unsigned char sum[2];			//2 * 8λУ���
//	unsigned char i;
//	
//	//����ָ�����

//	/*��ͷ 2 bytes*/
//	SendByte(0xEF);
//	SendByte(0x01);

//	/*оƬ��ַ 4 bytes*/
//	SendByte(0xFF);
//	SendByte(0xFF);
//	SendByte(0xFF);
//	SendByte(0xFF);

//	/*����ʶ 1 byte*/
//	SendByte(0x01);

//	/*������ 2 bytes*/
//	SendByte(0x00);
//	SendByte(0x06);

//	/*ָ���� 1 byte*/
//	SendByte(0x06);

//	/*�������� 1 byte*/
//	SendByte(BufferID);	

//	/*λ�ú� 2 bytes*/
//	page[0] = PageID;
//	page[1] = PageID >> 8;
//	SendByte(page[1]);
//	SendByte(page[0]);

//	/*У��� 2 bytes*/
//	summaf = (0x01 + 0x06 + 0x06 + BufferID + PageID);
//	sum[0] = summaf;
//	sum[1] = summaf >> 8;
//	SendByte(sum[1]);
//	SendByte(sum[0]); 

//	//����Ӧ���

//	/*ǰ9λΪ��ͷ��оƬ��ַ������ʶ�������ȡ�Ϊ����Ҫ�Ĳ��֣������б���*/
//	for(i = 0; i <=9; i++)
//	{
//		HAL_UART_Receive_IT(&huart2,&querenma,1);
//	}

//	/*ȷ���� 1 byte*/
//	//querenma //= ReceiveByte();

//	/*У��� 2 bytes������Ҫ�������б���*/
//	uint8_t data;
//	HAL_UART_Receive(&huart2,&data,1,10);
//	HAL_UART_Receive(&huart2,&data,1,10);

//	return querenma;	//���ذ�Ϊȷ����
//}

//�ж��жϽ��յ�������û��Ӧ���
//waittimeΪ�ȴ��жϽ������ݵ�ʱ�䣨��λ1ms��
//����ֵ�����ݰ��׵�ַ
char data[100];
static u8 *JudgeStr(u16 waittime)
{
  char now;
  u8 str[8];
  str[0] = 0xef;
  str[1] = 0x01;
  str[2] = AS608Addr >> 24;
  str[3] = AS608Addr >> 16;
  str[4] = AS608Addr >> 8;
  str[5] = AS608Addr;
  str[6] = 0x07;
  str[7] = '\0';

		
	HAL_UART_Receive(&huart2,(uint8_t *)data,9,0xFFFF);
	now=(data[7]<<8)+data[8];
	HAL_UART_Receive(&huart2,(uint8_t *)data,now,0xFFFF);
  return (uint8_t *)data;
}
//¼��ͼ�� PS_GetImage
//����:̽����ָ��̽�⵽��¼��ָ��ͼ�����ImageBuffer��
//ģ�鷵��ȷ����
u8 PS_GetImage(void)
{
  u16 temp;
  u8  ensure;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//�������ʶ
  SendLength(0x03);
  Sendcmd(0x01);
  temp =  0x01 + 0x03 + 0x01;
  SendCheck(temp);

  data = JudgeStr(2000);
  if(data)
    ensure = data[0];
  else
    ensure = 0xff;
  return ensure;
}
//�������� PS_GenChar
//����:��ImageBuffer�е�ԭʼͼ������ָ�������ļ�����CharBuffer1��CharBuffer2
//����:BufferID --> charBuffer1:0x01	charBuffer1:0x02
//ģ�鷵��ȷ����
u8 PS_GenChar(u8 BufferID)
{
  u16 temp;
  u8  ensure;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//�������ʶ
  SendLength(0x04);
  Sendcmd(0x02);
  MYUSART_SendData(BufferID);
  temp = 0x01 + 0x04 + 0x02 + BufferID;
  SendCheck(temp);
  data = JudgeStr(2000);
  if(data)
    ensure = data[0];
  else
    ensure = 0xff;
  return ensure;
}
//��ȷ�ȶ���öָ������ PS_Match
//����:��ȷ�ȶ�CharBuffer1 ��CharBuffer2 �е������ļ�
//ģ�鷵��ȷ����
u8 PS_Match(void)
{
  u16 temp;
  u8  ensure;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//�������ʶ
  SendLength(0x03);
  Sendcmd(0x03);
  temp = 0x01 + 0x03 + 0x03;
  SendCheck(temp);
  data = JudgeStr(2000);
  if(data)
    ensure = data[0];
  else
    ensure = 0xff;
  return ensure;
}
//����ָ�� PS_Search
//����:��CharBuffer1��CharBuffer2�е������ļ����������򲿷�ָ�ƿ�.�����������򷵻�ҳ�롣
//����:  BufferID @ref CharBuffer1	CharBuffer2
//˵��:  ģ�鷵��ȷ���֣�ҳ�루����ָ��ģ�壩
u8 PS_Search(u8 BufferID, u16 StartPage, u16 PageNum, SearchResult *p)
{
  u16 temp;
  u8  ensure;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//�������ʶ
  SendLength(0x08);
  Sendcmd(0x04);
  MYUSART_SendData(BufferID);
  MYUSART_SendData(StartPage >> 8);
  MYUSART_SendData(StartPage);
  MYUSART_SendData(PageNum >> 8);
  MYUSART_SendData(PageNum);
  temp = 0x01 + 0x08 + 0x04 + BufferID
         + (StartPage >> 8) + (u8)StartPage
         + (PageNum >> 8) + (u8)PageNum;
  SendCheck(temp);
  data = JudgeStr(2000);
  if(data)
  {
    ensure = data[0];
    p->pageID   = (data[1] << 8) + data[2];
    p->mathscore = (data[3] << 8) + data[4];
  }
  else
    ensure = 0xff;
  return ensure;
}
//�ϲ�����������ģ�壩PS_RegModel
//����:��CharBuffer1��CharBuffer2�е������ļ��ϲ����� ģ��,�������CharBuffer1��CharBuffer2
//˵��:  ģ�鷵��ȷ����
u8 PS_RegModel(void)
{
  u16 temp;
  u8  ensure;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//�������ʶ
  SendLength(0x03);
  Sendcmd(0x05);
  temp = 0x01 + 0x03 + 0x05;
  SendCheck(temp);
  data = JudgeStr(2000);
  if(data)
    ensure = data[0];
  else
    ensure = 0xff;
  return ensure;
}
//����ģ�� PS_StoreChar
//����:�� CharBuffer1 �� CharBuffer2 �е�ģ���ļ��浽 PageID ��flash���ݿ�λ�á�
//����:  BufferID @ref charBuffer1:0x01	charBuffer1:0x02
//       PageID��ָ�ƿ�λ�úţ�
//˵��:  ģ�鷵��ȷ����
u8 PS_StoreChar(u8 BufferID, u16 PageID)
{
  u16 temp;
  u8  ensure;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//�������ʶ
  SendLength(0x06);
  Sendcmd(0x06);
  MYUSART_SendData(BufferID);
  MYUSART_SendData(PageID >> 8);
  MYUSART_SendData(PageID);
  temp = 0x01 + 0x06 + 0x06 + BufferID
         + (PageID >> 8) + (u8)PageID;
  SendCheck(temp);
  data = JudgeStr(2000);
  if(data)
    ensure = data[0];
  else
    ensure = 0xff;
  return ensure;
}
//ɾ��ģ�� PS_DeletChar
//����:  ɾ��flash���ݿ���ָ��ID�ſ�ʼ��N��ָ��ģ��
//����:  PageID(ָ�ƿ�ģ���)��Nɾ����ģ�������
//˵��:  ģ�鷵��ȷ����
u8 PS_DeletChar(u16 PageID, u16 N)
{
  u16 temp;
  u8  ensure;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//�������ʶ
  SendLength(0x07);
  Sendcmd(0x0C);
  MYUSART_SendData(PageID >> 8);
  MYUSART_SendData(PageID);
  MYUSART_SendData(N >> 8);
  MYUSART_SendData(N);
  temp = 0x01 + 0x07 + 0x0C
         + (PageID >> 8) + (u8)PageID
         + (N >> 8) + (u8)N;
  SendCheck(temp);
  data = JudgeStr(2000);
  if(data)
    ensure = data[0];
  else
    ensure = 0xff;
  return ensure;
}
//���ָ�ƿ� PS_Empty
//����:  ɾ��flash���ݿ�������ָ��ģ��
//����:  ��
//˵��:  ģ�鷵��ȷ����
u8 PS_Empty(void)
{
  u16 temp;
  u8  ensure;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//�������ʶ
  SendLength(0x03);
  Sendcmd(0x0D);
  temp = 0x01 + 0x03 + 0x0D;
  SendCheck(temp);
  data = JudgeStr(2000);
  if(data)
    ensure = data[0];
  else
    ensure = 0xff;
  return ensure;
}
//дϵͳ�Ĵ��� PS_WriteReg
//����:  дģ��Ĵ���
//����:  �Ĵ������RegNum:4\5\6
//˵��:  ģ�鷵��ȷ����
u8 PS_WriteReg(u8 RegNum, u8 DATA)
{
  u16 temp;
  u8  ensure;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//�������ʶ
  SendLength(0x05);
  Sendcmd(0x0E);
  MYUSART_SendData(RegNum);
  MYUSART_SendData(DATA);
  temp = RegNum + DATA + 0x01 + 0x05 + 0x0E;
  SendCheck(temp);
  data = JudgeStr(2000);
  if(data)
    ensure = data[0];
  else
    ensure = 0xff;
  if(ensure == 0)
    printf("\r\n���ò����ɹ���");
  else
    printf("\r\n%s", EnsureMessage(ensure));
  return ensure;
}
//��ϵͳ�������� PS_ReadSysPara
//����:  ��ȡģ��Ļ��������������ʣ�����С��)
//����:  ��
//˵��:  ģ�鷵��ȷ���� + ����������16bytes��
u8 PS_ReadSysPara(SysPara *p)
{
  u16 temp;
  u8  ensure;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//�������ʶ
  SendLength(0x03);
  Sendcmd(0x0F);
  temp = 0x01 + 0x03 + 0x0F;
  SendCheck(temp);
  data = JudgeStr(1000);
  if(data)
  {
    ensure = data[0];
    p->PS_max = (data[5] << 8) + data[6];
    p->PS_level = data[8];
    p->PS_addr = (data[9] << 24) + (data[10] << 16) + (data[11] << 8) + data[12];
    p->PS_size = data[14];
    p->PS_N = data[16];
  }
  else
    ensure = 0xff;
  if(ensure == 0x00)
  {
    printf("\r\nģ�����ָ������=%d", p->PS_max);
    printf("\r\n�Աȵȼ�=%d", p->PS_level);
    printf("\r\n��ַ=%x", p->PS_addr);
    printf("\r\n������=%d", p->PS_N * 9600);
  }
  else
    printf("\r\n%s", EnsureMessage(ensure));
  return ensure;
}
//����ģ���ַ PS_SetAddr
//����:  ����ģ���ַ
//����:  PS_addr
//˵��:  ģ�鷵��ȷ����
u8 PS_SetAddr(u32 PS_addr)
{
  u16 temp;
  u8  ensure;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//�������ʶ
  SendLength(0x07);
  Sendcmd(0x15);
  MYUSART_SendData(PS_addr >> 24);
  MYUSART_SendData(PS_addr >> 16);
  MYUSART_SendData(PS_addr >> 8);
  MYUSART_SendData(PS_addr);
  temp = 0x01 + 0x07 + 0x15
         + (u8)(PS_addr >> 24) + (u8)(PS_addr >> 16)
         + (u8)(PS_addr >> 8) + (u8)PS_addr;
  SendCheck(temp);
  AS608Addr = PS_addr; //������ָ�������ַ
  data = JudgeStr(2000);
  if(data)
    ensure = data[0];
  else
    ensure = 0xff;
  AS608Addr = PS_addr;
  if(ensure == 0x00)
    printf("\r\n���õ�ַ�ɹ���");
  else
    printf("\r\n%s", EnsureMessage(ensure));
  return ensure;
}
//���ܣ� ģ���ڲ�Ϊ�û�������256bytes��FLASH�ռ����ڴ��û����±�,
//	�ü��±��߼��ϱ��ֳ� 16 ��ҳ��
//����:  NotePageNum(0~15),Byte32(Ҫд�����ݣ�32���ֽ�)
//˵��:  ģ�鷵��ȷ����
u8 PS_WriteNotepad(u8 NotePageNum, u8 *Byte32)
{
  u16 temp;
  u8  ensure, i;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//�������ʶ
  SendLength(36);
  Sendcmd(0x18);
  MYUSART_SendData(NotePageNum);
  for(i = 0; i < 32; i++)
  {
    MYUSART_SendData(Byte32[i]);
    temp += Byte32[i];
  }
  temp = 0x01 + 36 + 0x18 + NotePageNum + temp;
  SendCheck(temp);
  data = JudgeStr(2000);
  if(data)
    ensure = data[0];
  else
    ensure = 0xff;
  return ensure;
}
//������PS_ReadNotepad
//���ܣ�  ��ȡFLASH�û�����128bytes����
//����:  NotePageNum(0~15)
//˵��:  ģ�鷵��ȷ����+�û���Ϣ
u8 PS_ReadNotepad(u8 NotePageNum, u8 *Byte32)
{
  u16 temp;
  u8  ensure, i;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//�������ʶ
  SendLength(0x04);
  Sendcmd(0x19);
  MYUSART_SendData(NotePageNum);
  temp = 0x01 + 0x04 + 0x19 + NotePageNum;
  SendCheck(temp);
  data = JudgeStr(2000);
  if(data)
  {
    ensure = data[0];
    for(i = 0; i < 32; i++)
    {
      Byte32[i] = data[1 + i];
    }
  }
  else
    ensure = 0xff;
  return ensure;
}
//��������PS_HighSpeedSearch
//���ܣ��� CharBuffer1��CharBuffer2�е������ļ��������������򲿷�ָ�ƿ⡣
//		  �����������򷵻�ҳ��,��ָ����ڵ�ȷ������ָ�ƿ��� ���ҵ�¼ʱ����
//		  �ܺõ�ָ�ƣ���ܿ�������������
//����:  BufferID�� StartPage(��ʼҳ)��PageNum��ҳ����
//˵��:  ģ�鷵��ȷ����+ҳ�루����ָ��ģ�壩
u8 PS_HighSpeedSearch(u8 BufferID, u16 StartPage, u16 PageNum, SearchResult *p)
{
  u16 temp;
  u8  ensure;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//�������ʶ
  SendLength(0x08);
  Sendcmd(0x1b);
  MYUSART_SendData(BufferID);
  MYUSART_SendData(StartPage >> 8);
  MYUSART_SendData(StartPage);
  MYUSART_SendData(PageNum >> 8);
  MYUSART_SendData(PageNum);
  temp = 0x01 + 0x08 + 0x1b + BufferID
         + (StartPage >> 8) + (u8)StartPage
         + (PageNum >> 8) + (u8)PageNum;
  SendCheck(temp);
  data = JudgeStr(2000);
  if(data)
  {
    ensure = data[0];
    p->pageID 	= (data[1] << 8) + data[2];
    p->mathscore = (data[3] << 8) + data[4];
  }
  else
    ensure = 0xff;
  return ensure;
}
//����Чģ����� PS_ValidTempleteNum
//���ܣ�����Чģ�����
//����: ��
//˵��: ģ�鷵��ȷ����+��Чģ�����ValidN
u8 PS_ValidTempleteNum(u16 *ValidN)
{
  u16 temp;
  u8  ensure;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//�������ʶ
  SendLength(0x03);
  Sendcmd(0x1d);
  temp = 0x01 + 0x03 + 0x1d;
  SendCheck(temp);
  data = JudgeStr(2000);
  if(data)
  {
    ensure = data[0];
    *ValidN = (data[1] << 8) + data[2];
  }
  else
    ensure = 0xff;

  if(ensure == 0x00)
  {
    printf("\r\n��Чָ�Ƹ���=%d", (data[1] << 8) + data[2]);
  }
  else
    printf("\r\n%s", EnsureMessage(ensure));
  return ensure;
}
//��AS608���� PS_HandShake
//����: PS_Addr��ַָ��
//˵��: ģ�鷵�µ�ַ����ȷ��ַ��
u8 PS_HandShake(u32 *PS_Addr)
{
  u8  *data,now,*date;	
  SendHead();
  SendAddr();
  MYUSART_SendData(0X01);
  MYUSART_SendData(0X00);
  MYUSART_SendData(0X00);
  delay_ms(200);
  data = JudgeStr(2000);
	HAL_UART_Receive(&huart2,data,9,1000);
  HAL_UART_Receive(&huart2,date,(data[7]<<8)+data[8],1000);
    if(//�ж��ǲ���ģ�鷵�ص�Ӧ���
      data[0] == 0XEF
      && data[1] == 0X01
      && data[6] == 0X07
    )
    {
      *PS_Addr = (data[2] << 24) + (data[3] << 16)
                 + (data[4] << 8) + (data[5]);

      return 0;
    }

  return 1;
}
//ģ��Ӧ���ȷ������Ϣ����
//���ܣ�����ȷ���������Ϣ������Ϣ
//����: ensure
const char *EnsureMessage(u8 ensure)
{
  const char *p;
  switch(ensure)
  {
  case  0x00:
    p = "       OK       ";
    break;
  case  0x01:
    p = " ���ݰ����մ��� ";
    break;
  case  0x02:
    p = "��������û����ָ";
    break;
  case  0x03:
    p = "¼��ָ��ͼ��ʧ��";
    break;
  case  0x04:
    p = " ָ��̫�ɻ�̫�� ";
    break;
  case  0x05:
    p = " ָ��̫ʪ��̫�� ";
    break;
  case  0x06:
    p = "  ָ��ͼ��̫��  ";
    break;
  case  0x07:
    p = " ָ��������̫�� ";
    break;
  case  0x08:
    p = "  ָ�Ʋ�ƥ��    ";
    break;
  case  0x09:
    p = " û��������ָ�� ";
    break;
  case  0x0a:
    p = "   �����ϲ�ʧ�� ";
    break;
  case  0x0b:
    p = "��ַ��ų�����Χ";
  case  0x10:
    p = "  ɾ��ģ��ʧ��  ";
    break;
  case  0x11:
    p = " ���ָ�ƿ�ʧ�� ";
    break;
  case  0x15:
    p = "������������Чͼ";
    break;
  case  0x18:
    p = " ��дFLASH����  ";
    break;
  case  0x19:
    p = "   δ�������   ";
    break;
  case  0x1a:
    p = "  ��Ч�Ĵ�����  ";
    break;
  case  0x1b:
    p = " �Ĵ������ݴ��� ";
    break;
  case  0x1c:
    p = " ���±�ҳ����� ";
    break;
  case  0x1f:
    p = "    ָ�ƿ���    ";
    break;
  case  0x20:
    p = "    ��ַ����    ";
    break;
  default :
    p = " ����ȷ�������� ";
    break;
  }
  return p;
}

//��ʾȷ���������Ϣ
void ShowErrMessage(u8 ensure)
{
  //OLED_ShowCH(5,0,(u8*)EnsureMessage(ensure));
}

void OLED_ShowCH(uint8_t a,uint8_t b,char * str)
{
	HAL_UART_Transmit_IT(&huart1, (uint8_t *)str, strlen(str));
}
//¼ָ��
void Add_FR(void)
{
  u8 i, ensure, processnum = 0;
  u8 ID_NUM = 0;
  while(1)
  {
    switch (processnum)
    {
    case 0:
      i++;
      OLED_ShowCH(0, 2, "    �밴��ָ    \r\n");
      ensure = PS_GetImage();
      if(ensure == 0x00)
      {
        ensure = PS_GenChar(CharBuffer1); //��������
        if(ensure == 0x00)
        {
          OLED_ShowCH(0, 2, "    ָ������    \r\n");
          i = 0;
          processnum = 1; //�����ڶ���
        }
        else ShowErrMessage(ensure);
      }
      else ShowErrMessage(ensure);
      break;

    case 1:
      i++;
      OLED_ShowCH(0, 2, "   ���ٰ�һ��   \r\n");
      ensure = PS_GetImage();
      if(ensure == 0x00)
      {
        ensure = PS_GenChar(CharBuffer2); //��������
        if(ensure == 0x00)
        {
          OLED_ShowCH(0, 2, "    ָ������    \r\n");
          i = 0;
          processnum = 2; //����������
        }
        else ShowErrMessage(ensure);
      }
      else ShowErrMessage(ensure);
      break;

    case 2:
      OLED_ShowCH(0, 2, "  �Ա�����ָ��  \r\n");
      ensure = PS_Match();
      if(ensure == 0x00)
      {
        OLED_ShowCH(0, 2, "    �Աȳɹ�    \r\n");

        processnum = 3; //�������Ĳ�
      }
      else
      {
        OLED_ShowCH(0, 2, "    �Ա�ʧ��    \r\n");

        ShowErrMessage(ensure);
        i = 0;
        processnum = 0; //���ص�һ��
      }
      delay_ms(500);
      break;

    case 3:
      OLED_ShowCH(0, 2, "  ����ָ��ģ��  \r\n");
      delay_ms(500);
      ensure = PS_RegModel();
      if(ensure == 0x00)
      {
        OLED_ShowCH(0, 2, "����ָ��ģ��ɹ�\r\n");
        processnum = 4; //�������岽
      }
      else
      {
        processnum = 0;
        ShowErrMessage(ensure);
      }
      delay_ms(1000);
      break;

    case 4:

			IDM++;
			if(IDM ==100)IDM =1;
 //     key_num = 0;
      ensure = PS_StoreChar(CharBuffer2, IDM); //����ģ��
      if(ensure == 0x00)
      {
        OLED_ShowCH(0, 2, "  ¼��ָ�Ƴɹ�  \r\n");

        delay_ms(1500);
        OLED_ShowCH(0, 0, "ָ����֤\r\n");
        OLED_ShowCH(16, 2, "1���ָ��\r\n");
//        OLED_ShowCH(16, 4, "3ɾ��ָ��");
        OLED_ShowCH(16, 6, "2��ָ֤��\r\n");
        return ;
      }
      else
      {
        processnum = 0;
        ShowErrMessage(ensure);
      }
      break;
    }
    delay_ms(400);
    if(i == 10) //����5��û�а���ָ���˳�
    {
      break;
    }
  }
}

SysPara AS608Para;//ָ��ģ��AS608����
//ˢָ��
void press_FR(void)
{
  SearchResult seach;
  u8 ensure;
  char str[20];
	HAL_Delay(20);
//	OLED_ShowCH(32, 2, "�밴��ָ\r\n");
//  while(1)
//  {
//    key_num = KEY_Scan(0);
    ensure = PS_GetImage();
    if(ensure == 0x00) //��ȡͼ��ɹ�
    {
      ensure = PS_GenChar(CharBuffer1);
      if(ensure == 0x00) //���������ɹ�
      {
        ensure = PS_HighSpeedSearch(CharBuffer1, 0, 99, &seach);
        if(ensure == 0x00) //�����ɹ�
        {
          OLED_ShowCH(0, 2, "  ָ����֤�ɹ�  \r\n");
					HAL_Delay(50);
          sprintf(str, " ID:%d �÷�:%d \r\n", seach.pageID, seach.mathscore);
          OLED_ShowCH(0, 4, (u8*)str);
          delay_ms(1000);
//          delay_ms(1500);
					PushEvent(EVENT_open);
        }
        else
        {
          OLED_ShowCH(32, 2, "��֤ʧ��\r\n");
          delay_ms(1500);
        }
				return ;//break;
      }
      else
			{};
      OLED_ShowCH(32, 2, "�밴��ָ\r\n");
    }
//  }
}

//ɾ��ָ��
//void Del_FR(void)
//{
//  u8  ensure;
//  u16 ID_NUM = 0;
//  OLED_ShowCH(0, 0, "K4�� K2�� K3ȷ��");
//  OLED_ShowCH(0, 2, "  K5���ָ�ƿ�  ");
//  OLED_ShowCH(0, 4, "K1���� 0=<ID<=99");
//  while(key_num != 3)
//  {
//    key_num = KEY_Scan(0);
//    if(key_num == 2)
//    {
//      key_num = 0;
//      if(ID_NUM > 0)
//        ID_NUM--;
//    }
//    if(key_num == 4)
//    {
//      key_num = 0;
//      if(ID_NUM < 99)
//        ID_NUM++;
//    }
//    if(key_num == 1)
//      goto MENU ; //������ҳ��
//    if(key_num == 5)
//    {
//      key_num = 0;
//      ensure = PS_Empty(); //���ָ�ƿ�
//      if(ensure == 0)
//      {
//        OLED_Clear();
//        OLED_ShowCH(0, 2, " ���ָ�ƿ�ɹ� ");
//      }
//      else
//        ShowErrMessage(ensure);
//      delay_ms(1500);
//      goto MENU ; //������ҳ��
//    }
//    OLED_ShowCH(40, 6, "ID=");
//    OLED_ShowNum(65, 6, ID_NUM, 2, 1);
//  }
//  ensure = PS_DeletChar(ID_NUM, 1); //ɾ������ָ��
//  if(ensure == 0)
//  {
//    OLED_Clear();
//    OLED_ShowCH(0, 2, "  ɾ��ָ�Ƴɹ�  ");
//  }
//  else
//    ShowErrMessage(ensure);
//  delay_ms(1500);
//MENU:
//  OLED_Clear();
//  OLED_ShowCH(0, 0, "ָ��ģ����Գ���");
//  OLED_ShowCH(16, 2, "K1�����ָ��");
//  OLED_ShowCH(16, 4, "K3��ɾ��ָ��");
//  OLED_ShowCH(16, 6, "K5����ָ֤��");
//  key_num = 0;
//}
