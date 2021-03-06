/*****************************************************
This program was produced by the
CodeWizardAVR V1.25.3 Standard
Automatic Program Generator
� Copyright 1998-2007 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Axum-UI-PCR
Version :
Date    : 08-july-2009
Author  : Anton Prins
Company : DR Electronica Weesp b.v.
Comments:


Chip type           : AT90CAN32
Program type        : Application
Clock frequency     : 16,000000 MHz
Memory model        : Small
External SRAM size  : 0
Data Stack size     : 512
*****************************************************/

#include <90can32.h>
#include <stdio.h>
#include <delay.h>
#include <math.h>
#include <stdlib.h>

// I2C Bus functions
//#asm
//   .equ __i2c_port=0x08
//   .equ __sda_bit=2
//   .equ __scl_bit=3
//#endasm
//#include <i2c.h>

#include "Axum-UI-PCR.h"
#include "CANTransportLayer.h"
#include "Axum-UI-PCR-MambaNet.h"

/**********************************/
// Timer 0 output compare interrupt service routine
interrupt [TIM0_COMP] void timer0_comp_isr(void)
{
   //every 100 useconds a pulse.
   cntTimer0++;
   if (cntTimer0 == 10)
   {  //1mS
      cntTimer0 = 0;
      cntMilliSecond++;
   }
}

void main(void)
{
   char cntByte;

   // Declare your local variables here

   // Crystal Oscillator division factor: 1
   #pragma optsize-
   CLKPR=0x80;
   CLKPR=0x00;
   #ifdef _OPTIMIZE_SIZE_
   #pragma optsize+
   #endif

   // Input/Output Ports initialization
   // Port A initialization
   // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
   // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
   PORTA=0x00;
   DDRA=0x00;

   // Port B initialization
   // Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=In Func0=Out
   // State7=1 State6=1 State5=1 State4=1 State3=1 State2=1 State1=T State0=1
   PORTB=0xFD;
   DDRB=0xFD;

   // Port C initialization
   // Func7=In Func6=In Func5=In Func4=Out Func3=Out Func2=In Func1=Out Func0=In
   // State7=T State6=T State5=T State4=0 State3=1 State2=T State1=1 State0=T
   PORTC=0x00;
   DDRC=0x00;

   // Port D initialization
   // Func7=Out Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
   // State7=0 State6=T State5=T State4=T State3=T State2=T State1=T State0=T
   PORTD=0x80;
   DDRD=0x80;

   // Port E initialization
   // Func7=In Func6=In Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=In
   // State7=T State6=T State5=0 State4=0 State3=0 State2=0 State1=0 State0=T
   PORTE=0xA0;
   DDRE=0xBE;

   // Port F initialization
   // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
   // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
   PORTF=0x0F;
   DDRF=0x0F;

   // Port G initialization
   // Func4=In Func3=In Func2=In Func1=In Func0=In
   // State4=T State3=T State2=T State1=T State0=T
   PORTG=0x00;
   DDRG=0x00;

   // Timer/Counter 0 initialization
   // Clock source: System Clock
   // Clock value: 1000,000 kHz
   // Mode: CTC top=OCR0
   // OC0 output: Disconnected
   TCCR0A=0x0A;
   TCNT0=0x00;
   OCR0A=((OSCILLATOR_FREQUENCY/8)*0.0001)-1; //((OSCILLATOR_FREQUENCY/8)*0.0001)-1 => 100uS

   // Timer/Counter 1 initialization
   // Clock source: System Clock
   // Clock value: Timer 1 Stopped
   // Mode: Normal top=FFFFh
   // OC1A output: Discon.
   // OC1B output: Discon.
   // OC1C output: Discon.
   // Noise Canceler: Off
   // Input Capture on Falling Edge
   // Timer 1 Overflow Interrupt: Off
   // Input Capture Interrupt: Off
   // Compare A Match Interrupt: Off
   // Compare B Match Interrupt: Off
   // Compare C Match Interrupt: Off
   TCCR1A=0x00;
   TCCR1B=0x00;
   TCNT1H=0x00;
   TCNT1L=0x00;
   ICR1H=0x00;
   ICR1L=0x00;
   OCR1AH=0x00;
   OCR1AL=0x00;
   OCR1BH=0x00;
   OCR1BL=0x00;
   OCR1CH=0x00;
   OCR1CL=0x00;

   // Timer/Counter 2 initialization
   // Clock source: System Clock
   // Clock value: Timer 2 Stopped
   // Mode: Normal top=FFh
   // OC2 output: Disconnected
   ASSR=0x00;
   TCCR2A=0x00;
   TCNT2=0x00;
   OCR2A=0x00;

   // Timer/Counter 3 initialization
   // Clock source: System Clock
   // Clock value: Timer 3 Stopped
   // Mode: Normal top=FFFFh
   // Noise Canceler: Off
   // Input Capture on Falling Edge
   // OC3A output: Discon.
   // OC3B output: Discon.
   // OC3C output: Discon.
   // Timer 3 Overflow Interrupt: Off
   // Input Capture Interrupt: Off
   // Compare A Match Interrupt: Off
   // Compare B Match Interrupt: Off
   // Compare C Match Interrupt: Off
   TCCR3A=0x00;
   TCCR3B=0x00;
   TCNT3H=0x00;
   TCNT3L=0x00;
   ICR3H=0x00;
   ICR3L=0x00;
   OCR3AH=0x00;
   OCR3AL=0x00;
   OCR3BH=0x00;
   OCR3BL=0x00;
   OCR3CH=0x00;
   OCR3CL=0x00;

   // External Interrupt(s) initialization
   // INT0: Off
   // INT1: Off
   // INT2: Off
   // INT3: Off
   // INT4: Off
   // INT5: Off
   // INT6: Off
   // INT7: Off
   EICRA=0x00;
   EICRB=0x00;
   EIMSK=0x00;

   // Timer/Counter 0 Interrupt(s) initialization
   TIMSK0=0x02;
   // Timer/Counter 1 Interrupt(s) initialization
   TIMSK1=0x00;
   // Timer/Counter 2 Interrupt(s) initialization
   TIMSK2=0x00;
   // Timer/Counter 3 Interrupt(s) initialization
   TIMSK3=0x00;

   // Analog Comparator initialization
   // Analog Comparator: Off
   // Analog Comparator Input Capture by Timer/Counter 1: Off
   ACSR=0x80;
   ADCSRB=0x00;

   // NO ADC initialization

   PORTF |= 0xF0;
   delay_us(100);
   HardwareMinorRevision = (PINF>>4)&0x0F;
   PORTA &= 0x0F;

   FPGAFirmwareMajorRevision = 0;
   FPGAFirmwareMinorRevision = 0;

   // CAN Controller initialization
   InitializeCAN();

   for (cntByte=0;cntByte<NR_OF_LOGIC_LEDS; cntByte++)
   {
     SwitchColorOn[cntByte] = 0x02;
     SwitchColorOff[cntByte] = 0x00;
   }

   delay_ms(1000);   //else error?

   for (cntByte=0; cntByte<NR_OF_LOGIC_LEDS; cntByte++)
   {
      LogicLEDData[cntByte] = 1;
   }
   SetLEDs();
   BLANK = 0;

   delay_ms(500);

   for (cntByte=0; cntByte<NR_OF_LOGIC_LEDS; cntByte++)
   {
      LogicLEDData[cntByte] = 0;
   }
   SetLEDs();

   for (cntByte=0; cntByte<NR_OF_LOGIC_SWITCHES; cntByte++)
   {
      SwitchState[cntByte] = 0;
   }

   PreviousEncoderABStatus = 0;

   TransmitCANMessageBufferLength = 0;
   cntTransmitCANMessageBuffer = 0;

   PreviousMilliSecond = 0;

   // Global enable interrupts
   #asm("sei")

   CheckUniqueIDPerProduct();

   while (1)
   {      // Place your code here
      ProcessCAN();

      if (cntMilliSecond - PreviousMilliSecondReservation > 1000)
      {
         PreviousMilliSecondReservation = cntMilliSecond;

         if (LocalCANAddress == 0x00000000)
         {
            SendCANReservationRequest();
         }
         else
         {
            SendMambaNetReservationInfo();
         }
      }

      if (cntMilliSecond - PreviousMilliSecond > 40)
      {  //Send track/relative information maximal 25 times per second.
         int cntEncoder;

         for (cntEncoder=0; cntEncoder<3; cntEncoder++)
         {
           if (PreviousEncoderPosition[cntEncoder] != EncoderPosition[cntEncoder])
           {
              unsigned char TransmitBuffer[1];
              int Difference;
              int EncoderObject;

              if (cntEncoder == 0)
              {
                EncoderObject = 1031;
              }
              else if (cntEncoder == 1)
              {
                EncoderObject = 1033;
              }
              else
              {
                EncoderObject = 1079;
              }

              Difference = EncoderPosition[cntEncoder]-PreviousEncoderPosition[cntEncoder];

              TransmitBuffer[0] = Difference&0xFF;

              SendSensorChangeToMambaNet(EncoderObject, SIGNED_INTEGER_DATATYPE, 1, TransmitBuffer);

              PreviousEncoderPosition[cntEncoder] = EncoderPosition[cntEncoder];
           }
         }
         PreviousMilliSecond = cntMilliSecond;
      }

      ReadEncoders();
      ReadSwitches();
   }
}

void SetTLC5921DAP()
{
    unsigned char cntBit;
    unsigned char cntByte;

    for (cntByte=NR_OF_LEDS/8; cntByte<=NR_OF_LEDS/8; cntByte--)
    {
        for (cntBit=7; cntBit<=7; cntBit--)
        {
            SIN = TLC5921DAPData[cntByte]&(0x01<<cntBit);
            SCLK = 1;
            SCLK = 0;
        }
    }
    XLAT = 1;
    XLAT = 0;
}

void selectRow(unsigned char Row)
{
   nROW1 = 1;
   nROW2 = 1;
   nROW3 = 1;
   nROW4 = 1;
   nROW5 = 1;
   nROW6 = 1;
   nROW7 = 1;
   nROW8 = 1;

   switch (Row)
   {
      case 0:
      {
         nROW1 = 0;
      }
      break;
      case 1:
      {
         nROW2 = 0;
      }
      break;
      case 2:
      {
         nROW3 = 0;
      }
      break;
      case 3:
      {
         nROW4 = 0;
      }
      break;
      case 4:
      {
         nROW5 = 0;
      }
      break;
      case 5:
      {
         nROW6 = 0;
      }
      break;
      case 6:
      {
         nROW7 = 0;
      }
      break;
      case 7:
      {
         nROW8 = 0;
      }
      break;
   }
}

char SwitchCheck(unsigned char cntRow, unsigned char SwitchNr, char SwitchReturn)
{
    char ReturnValue;
    ReturnValue = 0;

    if (SwitchReturn)
    {
        if (SwitchData[cntRow][SwitchNr] != SWITCHDELAY)
        {
            SwitchData[cntRow][SwitchNr]++;
            if (SwitchData[cntRow][SwitchNr]==SWITCHDELAY)
            {  //Unpressed
                ReturnValue = -1;
            }
        }
    }
    else
    {
        if (SwitchData[cntRow][SwitchNr])
        {
            SwitchData[cntRow][SwitchNr]--;
            if (SwitchData[cntRow][SwitchNr]==0)
            {  //Pressed
                ReturnValue = 1;
            }
        }
    }
    return ReturnValue;
}

void ReadSwitches()
{
   char cntRow;
   char ReturnValue;
   unsigned char LogicSwitchNr;

   //Switch Rows
   for (cntRow=0; cntRow<8; cntRow++)
   {
      selectRow(cntRow);

      ReturnValue = SwitchCheck(cntRow, 0, nSW1);
      LogicSwitchNr = SwitchNr2LogicSwitchNr[(unsigned char)((cntRow*8)+0)];
      DoSwitch(LogicSwitchNr, ReturnValue);

      ReturnValue = SwitchCheck(cntRow, 1, nSW2);
      LogicSwitchNr = SwitchNr2LogicSwitchNr[(unsigned char)((cntRow*8)+1)];
      DoSwitch(LogicSwitchNr, ReturnValue);

      ReturnValue = SwitchCheck(cntRow, 2, nSW3);
      LogicSwitchNr = SwitchNr2LogicSwitchNr[(unsigned char)((cntRow*8)+2)];
      DoSwitch(LogicSwitchNr, ReturnValue);

      ReturnValue = SwitchCheck(cntRow, 3, nSW4);
      LogicSwitchNr = SwitchNr2LogicSwitchNr[(unsigned char)((cntRow*8)+3)];
      DoSwitch(LogicSwitchNr, ReturnValue);

      ReturnValue = SwitchCheck(cntRow, 4, nSW5);
      LogicSwitchNr = SwitchNr2LogicSwitchNr[(unsigned char)((cntRow*8)+4)];
      DoSwitch(LogicSwitchNr, ReturnValue);

      ReturnValue = SwitchCheck(cntRow, 5, nSW6);
      LogicSwitchNr = SwitchNr2LogicSwitchNr[(unsigned char)((cntRow*8)+5)];
      DoSwitch(LogicSwitchNr, ReturnValue);

      ReturnValue = SwitchCheck(cntRow, 6, nSW7);
      LogicSwitchNr = SwitchNr2LogicSwitchNr[(unsigned char)((cntRow*8)+6)];
      DoSwitch(LogicSwitchNr, ReturnValue);

      ReturnValue = SwitchCheck(cntRow, 7, nSW8);
      LogicSwitchNr = SwitchNr2LogicSwitchNr[(unsigned char)((cntRow*8)+7)];
      DoSwitch(LogicSwitchNr, ReturnValue);
   }

   ReturnValue = SwitchCheck(8, 0, nSW_2C);
   LogicSwitchNr = 10;
   DoSwitch(LogicSwitchNr, ReturnValue);
}

void ChangeEncoder(unsigned char EncoderNr, unsigned char UpDown)
{
  unsigned int Difference;
  unsigned int Offset;

  Offset = 0;
  if (UpDown)
  {
    Difference = cntMilliSecond - EncoderPreviousUpTime[EncoderNr];
    EncoderPreviousUpTime[EncoderNr] = cntMilliSecond;
  }
  else
  {
    Difference = cntMilliSecond - EncoderPreviousDownTime[EncoderNr];
    EncoderPreviousDownTime[EncoderNr] = cntMilliSecond;
  }
  if (Difference < 50)
  {
    Offset=5;
  }
  else if (Difference < 100)
  {
    Offset=2;
  }
  else
  {
    Offset=1;
  }

  if (UpDown)
  {
    EncoderPosition[EncoderNr] += Offset;
  }
  else
  {
    EncoderPosition[EncoderNr] -= Offset;
  }
}

void ReadEncoders()
{
  unsigned char EncoderABStatusChanged;

  //Check Encoder
  EncoderABStatus = PINC;

  EncoderABStatusChanged = PreviousEncoderABStatus^EncoderABStatus;
  PreviousEncoderABStatus = EncoderABStatus;

  //SW3
  if (EncoderABStatusChanged&0x02)
  {     //Pulse Change
    if ((EncoderABStatus&0x01) != ((EncoderABStatus>>1)&0x01))
    {  //Up
      ChangeEncoder(2, 1);
    }
    else
    {  //Down
      ChangeEncoder(2, 0);
    }
  }
  //SW2
  if (EncoderABStatusChanged&0x10)
  {     //Pulse Change
    if ((EncoderABStatus&0x08) != ((EncoderABStatus>>1)&0x08))
    {  //Up
      ChangeEncoder(1, 1);
    }
    else
    {  //Down
      ChangeEncoder(1, 0);
    }
  }
  //SW1
  if (EncoderABStatusChanged&0x40)
  {     //Pulse Change
    if ((EncoderABStatus&0x20) != ((EncoderABStatus>>1)&0x20))
    {  //Up
      ChangeEncoder(0, 1);
    }
    else
    {  //Down
      ChangeEncoder(0, 0);
    }
  }
}

void DoSwitch(unsigned char LogicSwitchNr, int Event)
{
   if ((Event == 1) || (Event == -1))
   {
      unsigned char TransmitBuffer[1];
      unsigned int ObjectNr;

      ObjectNr = 1024+LogicSwitchNr;

      TransmitBuffer[0] = 0;
      if (Event == 1)
      {
         TransmitBuffer[0] = 1;
      }

      SwitchState[LogicSwitchNr] = TransmitBuffer[0];

      SendSensorChangeToMambaNet(ObjectNr, STATE_DATATYPE, 1, TransmitBuffer);
    }
}

void SetLEDs()
{
   unsigned char cntLogicLED;
   unsigned char LEDValue;
   unsigned char LEDMask;
   unsigned char LEDByteNr;

   for (cntLogicLED=0; cntLogicLED<NR_OF_LOGIC_LEDS; cntLogicLED++)
   {
      if ((cntLogicLED>=0) && (cntLogicLED<3))
      { //dual color
        if (LogicLEDData[cntLogicLED])
        {
          LEDValue = SwitchColorOn[cntLogicLED];
        }
        else
        {
          LEDValue = SwitchColorOff[cntLogicLED];
        }
        LEDMask = 0x03<<(cntLogicLED*2);
        LEDValue <<= (cntLogicLED*2);
        LEDByteNr = 0;
      }
      else if ((cntLogicLED>=3) && (cntLogicLED<7))
      { //single color
        int LEDNr = 6+((int)cntLogicLED-3);

        LEDMask = 0x01<<(LEDNr&0x07);
        if (LogicLEDData[cntLogicLED])
        {
          LEDValue = 0x01<<(LEDNr&0x07);
        }
        else
        {
          LEDValue = 0x00;
        }
        LEDByteNr = LEDNr>>3;
      }
      else if ((cntLogicLED>=11) && (cntLogicLED<43))
      { //dual color
        int LEDNr = 10+(((int)cntLogicLED-11)*2);

        if (LogicLEDData[cntLogicLED])
        {
          LEDValue = SwitchColorOn[cntLogicLED];
        }
        else
        {
          LEDValue = SwitchColorOff[cntLogicLED];
        }
        LEDMask = 0x03<<(LEDNr&0x07);
        LEDValue <<= (LEDNr&0x07);
        LEDByteNr = LEDNr>>3;
      }
      else if ((cntLogicLED>=43) && (cntLogicLED<51))
      { //single color
        int LEDNr = 74+((int)cntLogicLED-43);

        LEDMask = 0x01<<(LEDNr&0x07);
        if (LogicLEDData[cntLogicLED])
        {
          LEDValue = 0x01<<(LEDNr&0x07);
        }
        else
        {
          LEDValue = 0x00;
        }
        LEDByteNr = LEDNr>>3;
      }
      else if ((cntLogicLED>=51) && (cntLogicLED<55))
      {
        LEDMask = 0x00;

        switch (cntLogicLED)
        {
          case 51:
          {
            nDL83 = !LogicLEDData[cntLogicLED];
          }
          break;
          case 52:
          {
            nDL84 = !LogicLEDData[cntLogicLED];
          }
          break;
          case 53:
          {
            nDL85 = !LogicLEDData[cntLogicLED];
          }
          break;
          case 54:
          {
            nDL86 = !LogicLEDData[cntLogicLED];
          }
          break;
        }
      }
      else if ((cntLogicLED>=57) && (cntLogicLED<65))
      { //single color
        int LEDNr = 86+((int)cntLogicLED-57)-4;

        LEDMask = 0x01<<(LEDNr&0x07);
        if (LogicLEDData[cntLogicLED])
        {
          LEDValue = 0x01<<(LEDNr&0x07);
        }
        else
        {
          LEDValue = 0x00;
        }
        LEDByteNr = LEDNr>>3;
      }
      else if ((cntLogicLED>=65) && (cntLogicLED<68))
      { //dual color
        int LEDNr = 94+(((int)cntLogicLED-65)*2)-4;

        if (LogicLEDData[cntLogicLED])
        {
          LEDValue = SwitchColorOn[cntLogicLED];
        }
        else
        {
          LEDValue = SwitchColorOff[cntLogicLED];
        }
        LEDMask = 0x03<<(LEDNr&0x07);
        LEDValue <<= (LEDNr&0x07);
        LEDByteNr = LEDNr>>3;
      }

      TLC5921DAPData[LEDByteNr] |= (LEDValue&LEDMask);
      TLC5921DAPData[LEDByteNr] &= (LEDValue|(LEDMask^0xFF));
   }
   SetTLC5921DAP();
}

void ProcessMambaNetMessageFromCAN_Imp(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength)
{
   unsigned char MessageDone;

   MessageDone = 0;


   if (MessageID)
   {
      Ack = 1;
   }

   switch (MessageType)
   {
      //MessageType = 0, handled in the stack
      case 1:
      {  //Object message
         unsigned int ObjectNr;
         unsigned char ObjectMessageAction;

         ObjectNr = ((unsigned int)Data[0]<<8) | Data[1];
         ObjectMessageAction = Data[2];

         switch (ObjectMessageAction)
         {
            //MAMBANET_OBJECT_ACTION_GET_INFORMATION, handled in the stack
            case  MAMBANET_OBJECT_ACTION_GET_SENSOR_DATA:
            {
               // if (ObjectNr<1024) is handled in the stack
               unsigned char TransmitBuffer[64];

               TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
               TransmitBuffer[1] = ObjectNr&0xFF;
               TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;

               if ((ObjectNr != 1031) && (ObjectNr != 1033) && (ObjectNr != 1079) && (ObjectNr>=1024) && (ObjectNr<1092))
               {  //Switches
                  char LogicSwitchNr = ObjectNr-1024;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = SwitchState[LogicSwitchNr];
                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr==1031) || (ObjectNr==1033) || (ObjectNr == 1079))
               {  //Encoder
                  TransmitBuffer[3] = SIGNED_INTEGER_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = 0;
                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }

               if (!MessageDone)
               {
                  TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                  TransmitBuffer[1] = ObjectNr&0xFF;
                  TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                  TransmitBuffer[3] = ERROR_DATATYPE;
                  TransmitBuffer[4] = 16;
                  TransmitBuffer[5] = 'N';
                  TransmitBuffer[6] = 'o';
                  TransmitBuffer[7] = ' ';
                  TransmitBuffer[8] = 's';
                  TransmitBuffer[9] = 'e';
                  TransmitBuffer[10] = 'n';
                  TransmitBuffer[11] = 's';
                  TransmitBuffer[12] = 'o';
                  TransmitBuffer[13] = 'r';
                  TransmitBuffer[14] = ' ';
                  TransmitBuffer[15] = 'o';
                  TransmitBuffer[16] = 'b';
                  TransmitBuffer[17] = 'j';
                  TransmitBuffer[18] = 'e';
                  TransmitBuffer[19] = 'c';
                  TransmitBuffer[20] = 't';

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 21);
               }
            }
            break;
            case  MAMBANET_OBJECT_ACTION_GET_ACTUATOR_DATA:
            {
               unsigned char TransmitBuffer[64];

               TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
               TransmitBuffer[1] = ObjectNr&0xFF;
               TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_ACTUATOR_DATA_RESPONSE;

               if ( ((ObjectNr>=1024) && (ObjectNr<1031)) ||
                    ((ObjectNr>=1035) && (ObjectNr<1079)) ||
                    ((ObjectNr>=1081) && (ObjectNr<1092)))
               {  //Switches with a LED
                  char LEDNr;

                  LEDNr = ObjectNr-1024;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = LogicLEDData[LEDNr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1092) && (ObjectNr<1130))
               {
                  char SeqNr = ObjectNr-1092;

                  char SwitchNr = 0;
                  if (SeqNr < 3)
                  {
                    SwitchNr = SeqNr;
                  }
                  else if (SeqNr < 35)
                  {
                    SwitchNr = SeqNr+8;
                  }
                  else
                  {
                    SwitchNr = SeqNr+30;
                  }

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = SwitchColorOn[SwitchNr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1130) && (ObjectNr<1168))
               {
                  char SeqNr = ObjectNr-1130;

                  char SwitchNr = 0;
                  if (SeqNr < 3)
                  {
                    SwitchNr = SeqNr;
                  }
                  else if (SeqNr < 35)
                  {
                    SwitchNr = SeqNr+8;
                  }
                  else
                  {
                    SwitchNr = SeqNr+30;
                  }

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = SwitchColorOff[SwitchNr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }

               if (!MessageDone)
               {
                  TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                  TransmitBuffer[1] = ObjectNr&0xFF;
                  TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_ACTUATOR_DATA_RESPONSE;
                  TransmitBuffer[3] = ERROR_DATATYPE;
                  TransmitBuffer[4] = 18;
                  TransmitBuffer[5] = 'N';
                  TransmitBuffer[6] = 'o';
                  TransmitBuffer[7] = ' ';
                  TransmitBuffer[8] = 'a';
                  TransmitBuffer[9] = 'c';
                  TransmitBuffer[10] = 't';
                  TransmitBuffer[11] = 'u';
                  TransmitBuffer[12] = 'a';
                  TransmitBuffer[13] = 't';
                  TransmitBuffer[14] = 'o';
                  TransmitBuffer[15] = 'r';
                  TransmitBuffer[16] = ' ';
                  TransmitBuffer[17] = 'o';
                  TransmitBuffer[18] = 'b';
                  TransmitBuffer[19] = 'j';
                  TransmitBuffer[20] = 'e';
                  TransmitBuffer[21] = 'c';
                  TransmitBuffer[22] = 't';

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 23);
               }
            }
            break;
            case  MAMBANET_OBJECT_ACTION_SET_ACTUATOR_DATA:
            {
               unsigned char DataType;
               unsigned char DataSize;
               unsigned char FormatError;

               FormatError = 1;

               DataType = Data[3];
               DataSize = Data[4];

               if ( ((ObjectNr>=1024) && (ObjectNr<1031)) ||
                    ((ObjectNr>=1035) && (ObjectNr<1079)) ||
                    ((ObjectNr>=1081) && (ObjectNr<1092)))
               {  //Switches with a single LED
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        char LEDNr;

                        LEDNr = ObjectNr-1024;

                        if (Data[5])
                        {
                           LogicLEDData[LEDNr] = 1;
                        }
                        else
                        {
                           LogicLEDData[LEDNr] = 0;
                        }
                        SetLEDs();

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr>=1092) && (ObjectNr<1130))
               {
                  char SeqNr = ObjectNr-1092;

                  char SwitchNr = 0;
                  if (SeqNr < 3)
                  {
                    SwitchNr = SeqNr;
                  }
                  else if (SeqNr < 35)
                  {
                    SwitchNr = SeqNr+8;
                  }
                  else
                  {
                    SwitchNr = SeqNr+30;
                  }

                  SwitchColorOn[SwitchNr] = Data[5]&0x03;
                  SetLEDs();

                  FormatError = 0;
                  MessageDone = 1;
               }
               else if ((ObjectNr>=1130) && (ObjectNr<1168))
               {
                  char SeqNr = ObjectNr-1130;

                  char SwitchNr = 0;
                  if (SeqNr < 3)
                  {
                    SwitchNr = SeqNr;
                  }
                  else if (SeqNr < 35)
                  {
                    SwitchNr = SeqNr+8;
                  }
                  else
                  {
                    SwitchNr = SeqNr+30;
                  }

                  SwitchColorOff[SwitchNr] = Data[5]&0x03;
                  SetLEDs();

                  FormatError = 0;
                  MessageDone = 1;
               }
               else
               {
                  FormatError = 0;
               }

               if (!MessageDone)
               {
                  unsigned char TransmitBuffer[23];

                  TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                  TransmitBuffer[1] = ObjectNr&0xFF;
                  TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_ACTUATOR_DATA_RESPONSE;
                  TransmitBuffer[3] = ERROR_DATATYPE;
                  if (FormatError)
                  {
                     TransmitBuffer[4] = 12;
                     sprintf(&TransmitBuffer[5], "Format error");
                  }
                  else
                  {
                     TransmitBuffer[4] = 18;
                     sprintf(&TransmitBuffer[5], "No actuator object");
                  }

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, TransmitBuffer[4]+5);
               }
               else
               {
                  if (MessageID)
                  {
                     unsigned char TransmitBuffer[16];

                     TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                     TransmitBuffer[1] = ObjectNr&0xFF;
                     TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_ACTUATOR_DATA_RESPONSE;
                     TransmitBuffer[3] = NO_DATA_DATATYPE;

                     SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 4);
                  }
               }
            }
            break;
         }
      }
      break;
   }
   return;
   ToAddress = 0;
   DataLength = 0;
}

void CanBussError()
{
   AddressValidated = 0;
   timerReservationInfo = 1;
}
