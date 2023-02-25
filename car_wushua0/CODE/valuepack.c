#include "valuepack.h"

// �������ݰ����ֽڳ���
const unsigned short  TXPACK_BYTE_SIZE = ((TX_BOOL_NUM+7)>>3)+TX_BYTE_NUM+(TX_SHORT_NUM<<1)+(TX_INT_NUM<<2)+(TX_FLOAT_NUM<<2);

// �������ݰ����ֽڳ���
const unsigned short  RXPACK_BYTE_SIZE = ((RX_BOOL_NUM+7)>>3)+RX_BYTE_NUM+(RX_SHORT_NUM<<1)+(RX_INT_NUM<<2)+(RX_FLOAT_NUM<<2);

// �������ݰ���ԭ���ݼ��ϰ�ͷ��У��Ͱ�β ֮����ֽڳ���
//unsigned short rx_pack_length = RXPACK_BYTE_SIZE+3;

// ���ռ���-��¼��ǰ�����ݽ��ս���
// ���ռ���ÿ���洮�ڵĽ����жϺ� +1
long rxIndex=0;

// ��ȡ����-��¼��ǰ�����ݰ���ȡ���ȣ���ȡ������һֱ����ڽ��ռ���������ȡ��������ռ���֮����볬��һ���������ݰ��ĳ���ʱ��������һ�����ݰ��Ķ�ȡ��
// ��ȡ����ÿ���ڶ�ȡ���ݰ������� +(���ݰ�����)
long rdIndex=0;

// ���ڻ��λ����������飬���λ������Ĵ�С������.h�ļ��ж���VALUEPACK_BUFFER_SIZE
unsigned char vp_rxbuff[VALUEPACK_BUFFER_SIZE];

// �����ݴ淢�����ݵ�����
//unsigned char vp_txbuff[TXPACK_BYTE_SIZE+3];

// ��ʼ�����ݰ�  ʹ�õ���USART1 �����ʿ�����
void initValuePack(int baudrate)
{

}


// ���ݰ����λ���������
unsigned int vp_circle_rx_index;

// ���ڽ����ж� �������� ÿ�ν��յ����ݺ��ֽڴ��뻷�λ������У���ͷ�浽β����ν�Ļ��λ��������ǵ����ջ��λ������������ڵ��ڻ������Ĵ�Сʱ�������ݵ��ﻺ������β��ʱ��
// ���ݻ��ڻ�������ͷ�������洢�����ǵ���������ݡ�
void USART1_IRQHandler(void)
{

}


// ���ݶ�ȡ�漰���ı���
unsigned short rdi,rdii,idl,idi,bool_index,bool_bit;
// ������ַ
uint32  idc;
// ��¼��ȡ�Ĵ����ֽڵĴ���
unsigned int err=0;
// ���ں�У��
unsigned char sum=0;

// ������ݰ���ȡ�Ľ��
unsigned char isok;


//------------------------------------------------------------------------------------------------------------------------
// unsigned char readValuePack(RxPack *rx_pack_ptr)
// ���Դӻ������ж�ȡ���ݰ�
// ����   - RxPack *rx_pack_ptr�� ����������ݽṹ���ָ�룬�ӻ��λ������ж�ȡ�����ݰ��������������ݴ洢��rx_pack_ptrָ��Ľṹ����
// ����ֵ - ����ɹ���ȡ�����ݰ����򷵻�1�����򷵻�0
//

unsigned char readValuePack(RxPack *rx_pack_ptr)
{
    // �������ݰ���ԭ���ݼ��ϰ�ͷ��У��Ͱ�β ֮����ֽڳ���
    unsigned short rx_pack_length = RXPACK_BYTE_SIZE+3;
    isok = 0;

    // ȷ����ȡ�����ͽ��ռ���֮��ľ���С��2�����ݰ��ĳ���
    while(rdIndex<(rxIndex-((rx_pack_length)*2)))
          rdIndex+=rx_pack_length;

    // �����ȡ��������ڽ��ռ������� 1�� ���ݰ��ĳ��ȣ����Զ�ȡ
    while(rdIndex<=(rxIndex-rx_pack_length))
    {
        rdi = rdIndex % VALUEPACK_BUFFER_SIZE;
        rdii=rdi+1;
        if( vp_rxbuff[rdi]==PACK_HEAD) // �Ƚϰ�ͷ
        {
            if(vp_rxbuff[(rdi+RXPACK_BYTE_SIZE+2)%VALUEPACK_BUFFER_SIZE]==PACK_TAIL) // �Ƚϰ�β ȷ����β���ټ���У���
            {
                //  ����У���
                sum=0;
                  for(short s=0;s<RXPACK_BYTE_SIZE;s++)
                {
                    rdi++;
                    if(rdi>=VALUEPACK_BUFFER_SIZE)
                      rdi -= VALUEPACK_BUFFER_SIZE;
                    sum += vp_rxbuff[rdi];
                }
                        rdi++;
                    if(rdi>=VALUEPACK_BUFFER_SIZE)
                      rdi -= VALUEPACK_BUFFER_SIZE;

                                if(sum==vp_rxbuff[rdi]) // У�����ȷ����ʼ���������е����ݶ�ȡ����
                {
                    //  ��ȡ���ݰ����� һ�����岽�� bool byte short int float
                    // 1. bool
                    #if  RX_BOOL_NUM>0

                      idc = (uint32)rx_pack_ptr->bools;
                      idl = (RX_BOOL_NUM+7)>>3;

                    bool_bit = 0;
                    for(bool_index=0;bool_index<RX_BOOL_NUM;bool_index++)
                    {
                        *((unsigned char *)(idc+bool_index)) = (vp_rxbuff[rdii]&(0x01<<bool_bit))?1:0;
                        bool_bit++;
                        if(bool_bit>=8)
                        {
                          bool_bit = 0;
                            rdii ++;
                        }
                    }
                    if(bool_bit)
                        rdii ++;

                        #endif
                    // 2.byte
                    #if RX_BYTE_NUM>0
                        idc = (uint32)(rx_pack_ptr->bytes);
                      idl = RX_BYTE_NUM;
                      for(idi=0;idi<idl;idi++)
                      {
                        if(rdii>=VALUEPACK_BUFFER_SIZE)
                          rdii -= VALUEPACK_BUFFER_SIZE;
                        (*((unsigned char *)idc))= vp_rxbuff[rdii];
                            rdii++;
                            idc++;
                      }
                        #endif
                    // 3.short
                    #if RX_SHORT_NUM>0
                        idc = (uint32)(rx_pack_ptr->shorts);
                      idl = RX_SHORT_NUM<<1;
                      for(idi=0;idi<idl;idi++)
                      {
                        if(rdii>=VALUEPACK_BUFFER_SIZE)
                          rdii -= VALUEPACK_BUFFER_SIZE;
                        (*((unsigned char *)idc))= vp_rxbuff[rdii];
                            rdii++;
                            idc++;
                      }
                        #endif
                    // 4.int
                    #if RX_INT_NUM>0
                        idc = (uint32)(&(rx_pack_ptr->integers[0]));
                      idl = RX_INT_NUM<<2;
                      for(idi=0;idi<idl;idi++)
                      {
                        if(rdii>=VALUEPACK_BUFFER_SIZE)
                          rdii -= VALUEPACK_BUFFER_SIZE;
                        (*((unsigned char *)idc))= vp_rxbuff[rdii];
                            rdii++;
                            idc++;
                      }
                        #endif
                    // 5.float
                    #if RX_FLOAT_NUM>0
                        idc = (uint32)(&(rx_pack_ptr->floats[0]));
                      idl = RX_FLOAT_NUM<<2;
                      for(idi=0;idi<idl;idi++)
                      {
                        if(rdii>=VALUEPACK_BUFFER_SIZE)
                          rdii -= VALUEPACK_BUFFER_SIZE;
                        (*((unsigned char *)idc))= vp_rxbuff[rdii];
                            rdii++;
                            idc++;
                      }
                  #endif

                        // ���¶�ȡ����
                    rdIndex+=rx_pack_length;
                    isok = 1;
                }else
                {
                // У��ֵ���� �� err+1 �� ���¶�ȡ����
                  rdIndex++;
                      err++;
                }
            }else
            {
                // ��β���� �� err+1 �� ���¶�ȡ����
                rdIndex++;
                err++;
            }
        }else
        {
            // ��ͷ���� �� err+1 �� ���¶�ȡ����
            rdIndex++;
            err++;
        }
    }
    return isok;
}

//-------------------------------------------------------------------------------------------------------------------------
// void sendBuffer(unsigned char *p,unsigned short length)
// �������ݰ�
// ����ָ�� �� �ֽڳ���

void sendBuffer(unsigned char *p,unsigned short length)
{
      for(int i=0;i<length;i++)
   {
      uart_putchar(UART_0, *p++);
//     USART_SendData(USART1, *p++);
//      while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
//      {}
    }
}

// ���ݰ������漰�ı���
unsigned short loop;
unsigned char valuepack_tx_bit_index;
unsigned char valuepack_tx_index;

//---------------------------------------------------------------------------------------------------------
//  void sendValuePack(TxPack *tx_pack_ptr)
//  ���������ݽṹ���еı�������������ͳ�ȥ
//  �������- TxPack *tx_pack_ptr ���������ݰ���ָ��
//
//  �Ƚ����������ݰ��ṹ��ı���ת�Ƶ����������ݻ��������У�Ȼ�󽫷������ݻ������е����ݷ���
//

void sendValuePack(TxPack *tx_pack_ptr)
{
  int i;
  // �����ݴ淢�����ݵ�����
  unsigned char vp_txbuff[TXPACK_BYTE_SIZE+3];
  vp_txbuff[0]=0xa5;
  sum=0;
  //  ���ڽṹ���в�ͬ���͵ı������ڴ�ռ���Ų������ϸ����ģ��м�Ƕ����Ч�ֽڣ������Ҫ���⴦��
  valuepack_tx_bit_index = 0;
  valuepack_tx_index = 1;

    #if TX_BOOL_NUM>0
      for(loop=0;loop<TX_BOOL_NUM;loop++)
      {
          if(tx_pack_ptr->bools[loop])
            vp_txbuff[valuepack_tx_index] |= 0x01<<valuepack_tx_bit_index;
          else
            vp_txbuff[valuepack_tx_index] &= ~(0x01<<valuepack_tx_bit_index);
          valuepack_tx_bit_index++;

          if(valuepack_tx_bit_index>=8)
          {
              valuepack_tx_bit_index = 0;
              valuepack_tx_index++;
          }
      }
      if(valuepack_tx_bit_index!=0)
          valuepack_tx_index++;
    #endif
    #if TX_BYTE_NUM>0

      for(loop=0;loop<TX_BYTE_NUM;loop++)
      {
          vp_txbuff[valuepack_tx_index] = tx_pack_ptr->bytes[loop];
          valuepack_tx_index++;
      }
    #endif

    #if TX_SHORT_NUM>0
      for(loop=0;loop<TX_SHORT_NUM;loop++)
      {
          vp_txbuff[valuepack_tx_index] = tx_pack_ptr->shorts[loop]&0xff;
          vp_txbuff[valuepack_tx_index+1] = tx_pack_ptr->shorts[loop]>>8;
          valuepack_tx_index+=2;
      }
    #endif

    #if TX_INT_NUM>0
      for(loop=0;loop<TX_INT_NUM;loop++)
      {
          i = tx_pack_ptr->integers[loop];
          vp_txbuff[valuepack_tx_index] = i&0xff;
          vp_txbuff[valuepack_tx_index+1] = (i>>8)&0xff;
          vp_txbuff[valuepack_tx_index+2] =(i>>16)&0xff;
          vp_txbuff[valuepack_tx_index+3] = (i>>24)&0xff;
          valuepack_tx_index+=4;
        }
    #endif

    #if TX_FLOAT_NUM>0
      for(loop=0;loop<TX_FLOAT_NUM;loop++)
      {
          i = *(int *)(&(tx_pack_ptr->floats[loop]));
          vp_txbuff[valuepack_tx_index] = i&0xff;
          vp_txbuff[valuepack_tx_index+1] = (i>>8)&0xff;
          vp_txbuff[valuepack_tx_index+2] =(i>>16)&0xff;
          vp_txbuff[valuepack_tx_index+3] = (i>>24)&0xff;
          valuepack_tx_index+=4;
      }
    #endif

    for(unsigned short d=1;d<=TXPACK_BYTE_SIZE;d++)
        sum+=vp_txbuff[d];

    vp_txbuff[TXPACK_BYTE_SIZE+1] = sum;
    vp_txbuff[TXPACK_BYTE_SIZE+2] = 0x5a;
    sendBuffer(vp_txbuff,TXPACK_BYTE_SIZE+3);
}



