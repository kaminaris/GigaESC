// Online C# Editor for free
// Write, Edit and Run your C# code using C# Online Compiler

using System;
using System.Reflection;

public class HelloWorld
{

     public static ushort CheckCrc16(byte[] inputbyte, byte start, byte len)
    {
      byte num1 = byte.MaxValue;
      byte maxValue = byte.MaxValue;
      byte[] numArray1 = new byte[256]
      {
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 1,
        (byte) 192,
        (byte) 128,
        (byte) 65,
        (byte) 0,
        (byte) 193,
        (byte) 129,
        (byte) 64
      };
      byte[] numArray2 = new byte[256]
      {
        (byte) 0,
        (byte) 192,
        (byte) 193,
        (byte) 1,
        (byte) 195,
        (byte) 3,
        (byte) 2,
        (byte) 194,
        (byte) 198,
        (byte) 6,
        (byte) 7,
        (byte) 199,
        (byte) 5,
        (byte) 197,
        (byte) 196,
        (byte) 4,
        (byte) 204,
        (byte) 12,
        (byte) 13,
        (byte) 205,
        (byte) 15,
        (byte) 207,
        (byte) 206,
        (byte) 14,
        (byte) 10,
        (byte) 202,
        (byte) 203,
        (byte) 11,
        (byte) 201,
        (byte) 9,
        (byte) 8,
        (byte) 200,
        (byte) 216,
        (byte) 24,
        (byte) 25,
        (byte) 217,
        (byte) 27,
        (byte) 219,
        (byte) 218,
        (byte) 26,
        (byte) 30,
        (byte) 222,
        (byte) 223,
        (byte) 31,
        (byte) 221,
        (byte) 29,
        (byte) 28,
        (byte) 220,
        (byte) 20,
        (byte) 212,
        (byte) 213,
        (byte) 21,
        (byte) 215,
        (byte) 23,
        (byte) 22,
        (byte) 214,
        (byte) 210,
        (byte) 18,
        (byte) 19,
        (byte) 211,
        (byte) 17,
        (byte) 209,
        (byte) 208,
        (byte) 16,
        (byte) 240,
        (byte) 48,
        (byte) 49,
        (byte) 241,
        (byte) 51,
        (byte) 243,
        (byte) 242,
        (byte) 50,
        (byte) 54,
        (byte) 246,
        (byte) 247,
        (byte) 55,
        (byte) 245,
        (byte) 53,
        (byte) 52,
        (byte) 244,
        (byte) 60,
        (byte) 252,
        (byte) 253,
        (byte) 61,
        byte.MaxValue,
        (byte) 63,
        (byte) 62,
        (byte) 254,
        (byte) 250,
        (byte) 58,
        (byte) 59,
        (byte) 251,
        (byte) 57,
        (byte) 249,
        (byte) 248,
        (byte) 56,
        (byte) 40,
        (byte) 232,
        (byte) 233,
        (byte) 41,
        (byte) 235,
        (byte) 43,
        (byte) 42,
        (byte) 234,
        (byte) 238,
        (byte) 46,
        (byte) 47,
        (byte) 239,
        (byte) 45,
        (byte) 237,
        (byte) 236,
        (byte) 44,
        (byte) 228,
        (byte) 36,
        (byte) 37,
        (byte) 229,
        (byte) 39,
        (byte) 231,
        (byte) 230,
        (byte) 38,
        (byte) 34,
        (byte) 226,
        (byte) 227,
        (byte) 35,
        (byte) 225,
        (byte) 33,
        (byte) 32,
        (byte) 224,
        (byte) 160,
        (byte) 96,
        (byte) 97,
        (byte) 161,
        (byte) 99,
        (byte) 163,
        (byte) 162,
        (byte) 98,
        (byte) 102,
        (byte) 166,
        (byte) 167,
        (byte) 103,
        (byte) 165,
        (byte) 101,
        (byte) 100,
        (byte) 164,
        (byte) 108,
        (byte) 172,
        (byte) 173,
        (byte) 109,
        (byte) 175,
        (byte) 111,
        (byte) 110,
        (byte) 174,
        (byte) 170,
        (byte) 106,
        (byte) 107,
        (byte) 171,
        (byte) 105,
        (byte) 169,
        (byte) 168,
        (byte) 104,
        (byte) 120,
        (byte) 184,
        (byte) 185,
        (byte) 121,
        (byte) 187,
        (byte) 123,
        (byte) 122,
        (byte) 186,
        (byte) 190,
        (byte) 126,
        (byte) 127,
        (byte) 191,
        (byte) 125,
        (byte) 189,
        (byte) 188,
        (byte) 124,
        (byte) 180,
        (byte) 116,
        (byte) 117,
        (byte) 181,
        (byte) 119,
        (byte) 183,
        (byte) 182,
        (byte) 118,
        (byte) 114,
        (byte) 178,
        (byte) 179,
        (byte) 115,
        (byte) 177,
        (byte) 113,
        (byte) 112,
        (byte) 176,
        (byte) 80,
        (byte) 144,
        (byte) 145,
        (byte) 81,
        (byte) 147,
        (byte) 83,
        (byte) 82,
        (byte) 146,
        (byte) 150,
        (byte) 86,
        (byte) 87,
        (byte) 151,
        (byte) 85,
        (byte) 149,
        (byte) 148,
        (byte) 84,
        (byte) 156,
        (byte) 92,
        (byte) 93,
        (byte) 157,
        (byte) 95,
        (byte) 159,
        (byte) 158,
        (byte) 94,
        (byte) 90,
        (byte) 154,
        (byte) 155,
        (byte) 91,
        (byte) 153,
        (byte) 89,
        (byte) 88,
        (byte) 152,
        (byte) 136,
        (byte) 72,
        (byte) 73,
        (byte) 137,
        (byte) 75,
        (byte) 139,
        (byte) 138,
        (byte) 74,
        (byte) 78,
        (byte) 142,
        (byte) 143,
        (byte) 79,
        (byte) 141,
        (byte) 77,
        (byte) 76,
        (byte) 140,
        (byte) 68,
        (byte) 132,
        (byte) 133,
        (byte) 69,
        (byte) 135,
        (byte) 71,
        (byte) 70,
        (byte) 134,
        (byte) 130,
        (byte) 66,
        (byte) 67,
        (byte) 131,
        (byte) 65,
        (byte) 129,
        (byte) 128,
        (byte) 64
      };
      byte num2 = 0;
      while (len-- > (byte) 0)
      {
        byte index = (byte) ((uint) num1 ^ (uint) inputbyte[(int) num2 + (int) start]);
        num1 = (byte) ((uint) maxValue ^ (uint) numArray1[(int) index]);
        maxValue = numArray2[(int) index];
        ++num2;
      }
      return (ushort) ((uint) num1 << 8 | (uint) maxValue);
    }

    public static ushort CalculateCRC16_Uni(byte[] data, int startIndex, int length, ushort polynomial)
    {
        ushort crc = 0xFFFF;

        for (int i = startIndex; i < startIndex + length; i++)
        {
            byte b = data[i];
            crc ^= (ushort)(b << 8);

            for (int j = 0; j < 8; j++)
            {
                if ((crc & 0x8000) != 0)
                    crc = (ushort)((crc << 1) ^ polynomial);
                else
                    crc <<= 1;
            }
        }

        return crc;
    }

    public static ushort CheckCrc16Modbus(byte[] inputbyte, byte start, byte len, ushort polynomial = 0x8408)
    {
        ushort crc = 0xFFFF;

        for (int i = start; i < start + len; i++)
        {
            crc ^= inputbyte[i];
            for (int j = 0; j < 8; j++)
            {
                if ((crc & 0x0001) != 0)
                {
                    crc >>= 1;
                    crc ^= polynomial;
                }
                else
                {
                    crc >>= 1;
                }
            }
        }

        return crc;
    }

    static public string ToReadableByteArray(byte[] bytes)
    {
        return string.Join(", ", bytes);
    }

    public static byte[] WriteData(ushort Address, byte Points, byte Fun, byte[] data)
    {
      byte[] inputbyte = new byte[10 + (int) Points];
      byte num1 = 0;
      byte[] numArray1 = inputbyte;
      int index1 = (int) num1;
      byte num2 = (byte) (index1 + 1);
      numArray1[index1] = (byte) 126;
      byte[] numArray2 = inputbyte;
      int index2 = (int) num2;
      byte num3 = (byte) (index2 + 1);
      numArray2[index2] = (byte) 161;
      byte[] numArray3 = inputbyte;
      int index3 = (int) num3;
      byte num4 = (byte) (index3 + 1);
      int num5 = (int) Fun;
      numArray3[index3] = (byte) num5;
      byte[] numArray4 = inputbyte;
      int index4 = (int) num4;
      byte num6 = (byte) (index4 + 1);
      int num7 = (int) (byte) Address;
      numArray4[index4] = (byte) num7;
      byte[] numArray5 = inputbyte;
      int index5 = (int) num6;
      byte num8 = (byte) (index5 + 1);
      int num9 = (int) (byte) ((uint) Address >> 8);
      numArray5[index5] = (byte) num9;
      byte[] numArray6 = inputbyte;
      int index6 = (int) num8;
      byte num10 = (byte) (index6 + 1);
      int num11 = (int) Points;
      numArray6[index6] = (byte) num11;

      for (byte index7 = 0; (int) index7 < (int) Points; ++index7)
        inputbyte[(int) num10++] = data[(int) index7];
      ushort num12 = CheckCrc16(inputbyte, (byte) 1, (byte) (5U + (uint) Points));

      byte[] numArray7 = inputbyte;
      int index8 = (int) num10;
      byte num13 = (byte) (index8 + 1);
      int num14 = (int) (byte) ((uint) num12 >> 8);
      numArray7[index8] = (byte) num14;
      byte[] numArray8 = inputbyte;
      int index9 = (int) num13;
      byte num15 = (byte) (index9 + 1);
      int num16 = (int) (byte) num12;
      numArray8[index9] = (byte) num16;
      byte[] numArray9 = inputbyte;
      int index10 = (int) num15;
      byte num17 = (byte) (index10 + 1);
      numArray9[index10] = (byte) 170;
      byte[] numArray10 = inputbyte;
      int index11 = (int) num17;
      byte num18 = (byte) (index11 + 1);
      numArray10[index11] = (byte) 85;
      return inputbyte;
    }

    public static byte[] WriteDataFix(ushort Address, byte Points, byte Fun, byte[] data)
    {
        byte[] inputbyte = new byte[10 + Points]; // Adjusted the array size

        inputbyte[0] = 126;
        inputbyte[1] = 161;
        inputbyte[2] = Fun;
        inputbyte[3] = (byte)Address;
        inputbyte[4] = (byte)(Address >> 8);
        inputbyte[5] = Points;

        Array.Copy(data, 0, inputbyte, 6, Points); // Using Array.Copy for efficiency

        ushort crc = Modbus(inputbyte, 1, (byte)(5 + Points)); // Changed index to start from 1

        inputbyte[6 + Points] = (byte)(crc >> 8);
        inputbyte[7 + Points] = (byte)crc;
        inputbyte[8 + Points] = 170;
        inputbyte[9 + Points] = 85;

        return inputbyte;
    }

    public static string ByteArrayToString(byte[] ba)
    {
      return "0x"+BitConverter.ToString(ba).Replace("-"," 0x");
    }

    public static ushort Modbus(byte[] buf, int start, int len)
    {
        ushort crc = 0xFFFF;

        for (int pos = start; pos < start+len; pos++)
        {
            crc ^= buf[pos];

            for (int i = 8; i != 0; i--)
            {
                if ((crc & 0x0001) != 0)
                {
                    crc >>= 1;
                    crc ^= 0xA001;
                }
                else
                    crc >>= 1;
            }
        }

        return (ushort)((crc >> 8) | (crc << 8));
    }

    public static RegisterData AntProtocol_RxBufFind(byte[] dataBuf)
    {
      RegisterData registerData1 = new RegisterData();
      byte num1 = dataBuf[13];
      if (dataBuf[2] == (byte) 17)
      {
        registerData1.MsgType = 1;
        byte num2 = 6;
        RegisterData registerData2 = registerData1;
        byte[] numArray1 = dataBuf;
        int index1 = (int) num2;
        byte num3 = (byte) (index1 + 1);
        int num4 = (int) numArray1[index1];
        registerData2.SysOperationAuth = (byte) num4;
        RegisterData registerData3 = registerData1;
        byte[] numArray2 = dataBuf;
        int index2 = (int) num3;
        byte num5 = (byte) (index2 + 1);
        int num6 = (int) numArray2[index2];
        registerData3.SystemState = (byte) num6;
        RegisterData registerData4 = registerData1;
        byte[] numArray3 = dataBuf;
        int index3 = (int) num5;
        byte num7 = (byte) (index3 + 1);
        int num8 = (int) numArray3[index3];
        registerData4.Temperature_Num = (byte) num8;
        RegisterData registerData5 = registerData1;
        byte[] numArray4 = dataBuf;
        int index4 = (int) num7;
        byte num9 = (byte) (index4 + 1);
        int num10 = (int) numArray4[index4];
        registerData5.PACK_Cell_Num = (byte) num10;
        byte[] numArray5 = dataBuf;
        int index5 = (int) num9;
        byte num11 = (byte) (index5 + 1);
        long num12 = (long) numArray5[index5];
        byte[] numArray6 = dataBuf;
        int index6 = (int) num11;
        byte num13 = (byte) (index6 + 1);
        long num14 = (long) numArray6[index6] << 8;
        long num15 = num12 | num14;
        byte[] numArray7 = dataBuf;
        int index7 = (int) num13;
        byte num16 = (byte) (index7 + 1);
        long num17 = (long) numArray7[index7] << 16;
        long num18 = num15 | num17;
        byte[] numArray8 = dataBuf;
        int index8 = (int) num16;
        byte num19 = (byte) (index8 + 1);
        long num20 = (long) numArray8[index8] << 24;
        long num21 = num18 | num20;
        byte[] numArray9 = dataBuf;
        int index9 = (int) num19;
        byte num22 = (byte) (index9 + 1);
        long num23 = (long) numArray9[index9] << 32;
        long num24 = num21 | num23;
        byte[] numArray10 = dataBuf;
        int index10 = (int) num22;
        byte num25 = (byte) (index10 + 1);
        long num26 = (long) numArray10[index10] << 40;
        long num27 = num24 | num26;
        byte[] numArray11 = dataBuf;
        int index11 = (int) num25;
        byte num28 = (byte) (index11 + 1);
        long num29 = (long) numArray11[index11] << 48;
        long num30 = num27 | num29;
        byte[] numArray12 = dataBuf;
        int index12 = (int) num28;
        byte num31 = (byte) (index12 + 1);
        long num32 = (long) numArray12[index12] << 56;
        ulong num33 = (ulong) (num30 | num32);
        registerData1.ProtectMack_Bit = num33;
        byte[] numArray13 = dataBuf;
        int index13 = (int) num31;
        byte num34 = (byte) (index13 + 1);
        long num35 = (long) numArray13[index13];
        byte[] numArray14 = dataBuf;
        int index14 = (int) num34;
        byte num36 = (byte) (index14 + 1);
        long num37 = (long) numArray14[index14] << 8;
        long num38 = num35 | num37;
        byte[] numArray15 = dataBuf;
        int index15 = (int) num36;
        byte num39 = (byte) (index15 + 1);
        long num40 = (long) numArray15[index15] << 16;
        long num41 = num38 | num40;
        byte[] numArray16 = dataBuf;
        int index16 = (int) num39;
        byte num42 = (byte) (index16 + 1);
        long num43 = (long) numArray16[index16] << 24;
        long num44 = num41 | num43;
        byte[] numArray17 = dataBuf;
        int index17 = (int) num42;
        byte num45 = (byte) (index17 + 1);
        long num46 = (long) numArray17[index17] << 32;
        long num47 = num44 | num46;
        byte[] numArray18 = dataBuf;
        int index18 = (int) num45;
        byte num48 = (byte) (index18 + 1);
        long num49 = (long) numArray18[index18] << 40;
        long num50 = num47 | num49;
        byte[] numArray19 = dataBuf;
        int index19 = (int) num48;
        byte num51 = (byte) (index19 + 1);
        long num52 = (long) numArray19[index19] << 48;
        long num53 = num50 | num52;
        byte[] numArray20 = dataBuf;
        int index20 = (int) num51;
        byte num54 = (byte) (index20 + 1);
        long num55 = (long) numArray20[index20] << 56;
        ulong num56 = (ulong) (num53 | num55);
        registerData1.WarningMack_Bit = num56;
        byte[] numArray21 = dataBuf;
        int index21 = (int) num54;
        byte num57 = (byte) (index21 + 1);
        long num58 = (long) numArray21[index21];
        byte[] numArray22 = dataBuf;
        int index22 = (int) num57;
        byte num59 = (byte) (index22 + 1);
        long num60 = (long) numArray22[index22] << 8;
        long num61 = num58 | num60;
        byte[] numArray23 = dataBuf;
        int index23 = (int) num59;
        byte num62 = (byte) (index23 + 1);
        long num63 = (long) numArray23[index23] << 16;
        long num64 = num61 | num63;
        byte[] numArray24 = dataBuf;
        int index24 = (int) num62;
        byte num65 = (byte) (index24 + 1);
        long num66 = (long) numArray24[index24] << 24;
        long num67 = num64 | num66;
        byte[] numArray25 = dataBuf;
        int index25 = (int) num65;
        byte num68 = (byte) (index25 + 1);
        long num69 = (long) numArray25[index25] << 32;
        long num70 = num67 | num69;
        byte[] numArray26 = dataBuf;
        int index26 = (int) num68;
        byte num71 = (byte) (index26 + 1);
        long num72 = (long) numArray26[index26] << 40;
        long num73 = num70 | num72;
        byte[] numArray27 = dataBuf;
        int index27 = (int) num71;
        byte num74 = (byte) (index27 + 1);
        long num75 = (long) numArray27[index27] << 48;
        long num76 = num73 | num75;
        byte[] numArray28 = dataBuf;
        int index28 = (int) num74;
        byte num77 = (byte) (index28 + 1);
        long num78 = (long) numArray28[index28] << 56;
        ulong num79 = (ulong) (num76 | num78);
        registerData1.PushMack_Bit = num79;
        for (byte index29 = 0; (int) index29 < (int) registerData1.PACK_Cell_Num; ++index29)
        {
          byte[] numArray29 = dataBuf;
          int index30 = (int) num77;
          byte num80 = (byte) (index30 + 1);
          int num81 = (int) (ushort) numArray29[index30];
          byte[] numArray30 = dataBuf;
          int index31 = (int) num80;
          num77 = (byte) (index31 + 1);
          int num82 = (int) (ushort) ((uint) numArray30[index31] << 8);
          ushort num83 = (ushort) (num81 | num82);
          registerData1.Voltage_Cell_Value[(int) index29] = num83;
        }
        for (byte index32 = 0; (int) index32 < (int) registerData1.Temperature_Num; ++index32)
        {
          byte[] numArray31 = dataBuf;
          int index33 = (int) num77;
          byte num84 = (byte) (index33 + 1);
          int num85 = (int) (short) numArray31[index33];
          byte[] numArray32 = dataBuf;
          int index34 = (int) num84;
          num77 = (byte) (index34 + 1);
          int num86 = (int) (short) ((int) numArray32[index34] << 8);
          short num87 = (short) (num85 | num86);
          registerData1.Temperature_Value[(int) index32] = num87;
        }
        byte[] numArray33 = dataBuf;
        int index35 = (int) num77;
        byte num88 = (byte) (index35 + 1);
        int num89 = (int) (short) numArray33[index35];
        byte[] numArray34 = dataBuf;
        int index36 = (int) num88;
        byte num90 = (byte) (index36 + 1);
        int num91 = (int) (short) ((int) numArray34[index36] << 8);
        short num92 = (short) (num89 | num91);
        registerData1.Temperature_MOS = num92;
        byte[] numArray35 = dataBuf;
        int index37 = (int) num90;
        byte num93 = (byte) (index37 + 1);
        int num94 = (int) (short) numArray35[index37];
        byte[] numArray36 = dataBuf;
        int index38 = (int) num93;
        byte num95 = (byte) (index38 + 1);
        int num96 = (int) (short) ((int) numArray36[index38] << 8);
        short num97 = (short) (num94 | num96);
        registerData1.Temperature_Balance = num97;
        byte[] numArray37 = dataBuf;
        int index39 = (int) num95;
        byte num98 = (byte) (index39 + 1);
        int num99 = (int) (ushort) numArray37[index39];
        byte[] numArray38 = dataBuf;
        int index40 = (int) num98;
        byte num100 = (byte) (index40 + 1);
        int num101 = (int) (ushort) ((uint) numArray38[index40] << 8);
        ushort num102 = (ushort) (num99 | num101);
        registerData1.Voltage_Pack = num102;
        byte[] numArray39 = dataBuf;
        int index41 = (int) num100;
        byte num103 = (byte) (index41 + 1);
        int num104 = (int) (short) numArray39[index41];
        byte[] numArray40 = dataBuf;
        int index42 = (int) num103;
        byte num105 = (byte) (index42 + 1);
        int num106 = (int) (short) ((int) numArray40[index42] << 8);
        short num107 = (short) (num104 | num106);
        registerData1.Current_Value = num107;
        byte[] numArray41 = dataBuf;
        int index43 = (int) num105;
        byte num108 = (byte) (index43 + 1);
        int num109 = (int) (ushort) numArray41[index43];
        byte[] numArray42 = dataBuf;
        int index44 = (int) num108;
        byte num110 = (byte) (index44 + 1);
        int num111 = (int) (ushort) ((uint) numArray42[index44] << 8);
        ushort num112 = (ushort) (num109 | num111);
        registerData1.Pack_SOC = num112;
        byte[] numArray43 = dataBuf;
        int index45 = (int) num110;
        byte num113 = (byte) (index45 + 1);
        int num114 = (int) (ushort) numArray43[index45];
        byte[] numArray44 = dataBuf;
        int index46 = (int) num113;
        byte num115 = (byte) (index46 + 1);
        int num116 = (int) (ushort) ((uint) numArray44[index46] << 8);
        ushort num117 = (ushort) (num114 | num116);
        registerData1.Pack_SOH = num117;
        RegisterData registerData6 = registerData1;
        byte[] numArray45 = dataBuf;
        int index47 = (int) num115;
        byte num118 = (byte) (index47 + 1);
        int num119 = (int) numArray45[index47];
        registerData6.DIS_MOS_State = (byte) num119;
        RegisterData registerData7 = registerData1;
        byte[] numArray46 = dataBuf;
        int index48 = (int) num118;
        byte num120 = (byte) (index48 + 1);
        int num121 = (int) numArray46[index48];
        registerData7.CH_MOS_State = (byte) num121;
        byte[] numArray47 = dataBuf;
        int index49 = (int) num120;
        byte num122 = (byte) (index49 + 1);
        long num123 = (long) numArray47[index49];
        byte[] numArray48 = dataBuf;
        int index50 = (int) num122;
        byte num124 = (byte) (index50 + 1);
        long num125 = (long) (ushort) ((uint) numArray48[index50] << 8);
        ulong num126 = (ulong) (num123 | num125);
        registerData1.Balance_State = num126;
        byte[] numArray49 = dataBuf;
        int index51 = (int) num124;
        byte num127 = (byte) (index51 + 1);
        int num128 = (int) numArray49[index51];
        byte[] numArray50 = dataBuf;
        int index52 = (int) num127;
        byte num129 = (byte) (index52 + 1);
        int num130 = (int) numArray50[index52] << 8;
        int num131 = num128 | num130;
        byte[] numArray51 = dataBuf;
        int index53 = (int) num129;
        byte num132 = (byte) (index53 + 1);
        int num133 = (int) numArray51[index53] << 16;
        int num134 = num131 | num133;
        byte[] numArray52 = dataBuf;
        int index54 = (int) num132;
        byte num135 = (byte) (index54 + 1);
        int num136 = (int) numArray52[index54] << 24;
        uint num137 = (uint) (num134 | num136);
        registerData1.Pack_Physics_AH = num137;
        byte[] numArray53 = dataBuf;
        int index55 = (int) num135;
        byte num138 = (byte) (index55 + 1);
        int num139 = (int) numArray53[index55];
        byte[] numArray54 = dataBuf;
        int index56 = (int) num138;
        byte num140 = (byte) (index56 + 1);
        int num141 = (int) numArray54[index56] << 8;
        int num142 = num139 | num141;
        byte[] numArray55 = dataBuf;
        int index57 = (int) num140;
        byte num143 = (byte) (index57 + 1);
        int num144 = (int) numArray55[index57] << 16;
        int num145 = num142 | num144;
        byte[] numArray56 = dataBuf;
        int index58 = (int) num143;
        byte num146 = (byte) (index58 + 1);
        int num147 = (int) numArray56[index58] << 24;
        uint num148 = (uint) (num145 | num147);
        registerData1.Pack_Remain_AH = num148;
        byte[] numArray57 = dataBuf;
        int index59 = (int) num146;
        byte num149 = (byte) (index59 + 1);
        int num150 = (int) numArray57[index59];
        byte[] numArray58 = dataBuf;
        int index60 = (int) num149;
        byte num151 = (byte) (index60 + 1);
        int num152 = (int) numArray58[index60] << 8;
        int num153 = num150 | num152;
        byte[] numArray59 = dataBuf;
        int index61 = (int) num151;
        byte num154 = (byte) (index61 + 1);
        int num155 = (int) numArray59[index61] << 16;
        int num156 = num153 | num155;
        byte[] numArray60 = dataBuf;
        int index62 = (int) num154;
        byte num157 = (byte) (index62 + 1);
        int num158 = (int) numArray60[index62] << 24;
        uint num159 = (uint) (num156 | num158);
        registerData1.Pack_All_AH = num159;
        byte[] numArray61 = dataBuf;
        int index63 = (int) num157;
        byte num160 = (byte) (index63 + 1);
        int num161 = (int) numArray61[index63];
        byte[] numArray62 = dataBuf;
        int index64 = (int) num160;
        byte num162 = (byte) (index64 + 1);
        int num163 = (int) numArray62[index64] << 8;
        int num164 = num161 | num163;
        byte[] numArray63 = dataBuf;
        int index65 = (int) num162;
        byte num165 = (byte) (index65 + 1);
        int num166 = (int) numArray63[index65] << 16;
        int num167 = num164 | num166;
        byte[] numArray64 = dataBuf;
        int index66 = (int) num165;
        byte num168 = (byte) (index66 + 1);
        int num169 = (int) numArray64[index66] << 24;
        int num170 = num167 | num169;
        registerData1.Pack_Power = num170;
        byte[] numArray65 = dataBuf;
        int index67 = (int) num168;
        byte num171 = (byte) (index67 + 1);
        long num172 = (long) numArray65[index67];
        byte[] numArray66 = dataBuf;
        int index68 = (int) num171;
        byte num173 = (byte) (index68 + 1);
        long num174 = (long) numArray66[index68] << 8;
        long num175 = num172 | num174;
        byte[] numArray67 = dataBuf;
        int index69 = (int) num173;
        byte num176 = (byte) (index69 + 1);
        long num177 = (long) numArray67[index69] << 16;
        long num178 = num175 | num177;
        byte[] numArray68 = dataBuf;
        int index70 = (int) num176;
        byte num179 = (byte) (index70 + 1);
        long num180 = (long) numArray68[index70] << 24;
        ulong num181 = (ulong) (num178 | num180);
        registerData1.All_Timer_ms = num181;
        byte[] numArray69 = dataBuf;
        int index71 = (int) num179;
        byte num182 = (byte) (index71 + 1);
        long num183 = (long) numArray69[index71];
        byte[] numArray70 = dataBuf;
        int index72 = (int) num182;
        byte num184 = (byte) (index72 + 1);
        long num185 = (long) numArray70[index72] << 8;
        long num186 = num183 | num185;
        byte[] numArray71 = dataBuf;
        int index73 = (int) num184;
        byte num187 = (byte) (index73 + 1);
        long num188 = (long) numArray71[index73] << 16;
        long num189 = num186 | num188;
        byte[] numArray72 = dataBuf;
        int index74 = (int) num187;
        byte num190 = (byte) (index74 + 1);
        long num191 = (long) numArray72[index74] << 24;
        ulong num192 = (ulong) (num189 | num191);
        registerData1.Balance_State_Bit = num192;
        byte[] numArray73 = dataBuf;
        int index75 = (int) num190;
        byte num193 = (byte) (index75 + 1);
        int num194 = (int) (ushort) numArray73[index75];
        byte[] numArray74 = dataBuf;
        int index76 = (int) num193;
        byte num195 = (byte) (index76 + 1);
        int num196 = (int) (ushort) ((uint) numArray74[index76] << 8);
        ushort num197 = (ushort) (num194 | num196);
        registerData1.Voltage_Cell_Max_Value = num197;
        byte[] numArray75 = dataBuf;
        int index77 = (int) num195;
        byte num198 = (byte) (index77 + 1);
        int num199 = (int) (ushort) numArray75[index77];
        byte[] numArray76 = dataBuf;
        int index78 = (int) num198;
        byte num200 = (byte) (index78 + 1);
        int num201 = (int) (ushort) ((uint) numArray76[index78] << 8);
        ushort num202 = (ushort) (num199 | num201);
        registerData1.Voltage_Cell_Max_Pos = num202;
        byte[] numArray77 = dataBuf;
        int index79 = (int) num200;
        byte num203 = (byte) (index79 + 1);
        int num204 = (int) (ushort) numArray77[index79];
        byte[] numArray78 = dataBuf;
        int index80 = (int) num203;
        byte num205 = (byte) (index80 + 1);
        int num206 = (int) (ushort) ((uint) numArray78[index80] << 8);
        ushort num207 = (ushort) (num204 | num206);
        registerData1.Voltage_Cell_Min_Value = num207;
        byte[] numArray79 = dataBuf;
        int index81 = (int) num205;
        byte num208 = (byte) (index81 + 1);
        int num209 = (int) (ushort) numArray79[index81];
        byte[] numArray80 = dataBuf;
        int index82 = (int) num208;
        byte num210 = (byte) (index82 + 1);
        int num211 = (int) (ushort) ((uint) numArray80[index82] << 8);
        ushort num212 = (ushort) (num209 | num211);
        registerData1.Voltage_Cell_Min_Pos = num212;
        byte[] numArray81 = dataBuf;
        int index83 = (int) num210;
        byte num213 = (byte) (index83 + 1);
        int num214 = (int) (ushort) numArray81[index83];
        byte[] numArray82 = dataBuf;
        int index84 = (int) num213;
        byte num215 = (byte) (index84 + 1);
        int num216 = (int) (ushort) ((uint) numArray82[index84] << 8);
        ushort num217 = (ushort) (num214 | num216);
        registerData1.Voltage_Cell_Difference = num217;
        byte[] numArray83 = dataBuf;
        int index85 = (int) num215;
        byte num218 = (byte) (index85 + 1);
        int num219 = (int) (ushort) numArray83[index85];
        byte[] numArray84 = dataBuf;
        int index86 = (int) num218;
        byte num220 = (byte) (index86 + 1);
        int num221 = (int) (ushort) ((uint) numArray84[index86] << 8);
        ushort num222 = (ushort) (num219 | num221);
        registerData1.Voltage_Cell_Average_Value = num222;
        byte[] numArray85 = dataBuf;
        int index87 = (int) num220;
        byte num223 = (byte) (index87 + 1);
        int num224 = (int) (short) numArray85[index87];
        byte[] numArray86 = dataBuf;
        int index88 = (int) num223;
        byte num225 = (byte) (index88 + 1);
        int num226 = (int) (short) ((int) numArray86[index88] << 8);
        short num227 = (short) (num224 | num226);
        registerData1.Voltage_DS_Value = num227;
        byte[] numArray87 = dataBuf;
        int index89 = (int) num225;
        byte num228 = (byte) (index89 + 1);
        int num229 = (int) (ushort) numArray87[index89];
        byte[] numArray88 = dataBuf;
        int index90 = (int) num228;
        byte num230 = (byte) (index90 + 1);
        int num231 = (int) (ushort) ((uint) numArray88[index90] << 8);
        ushort num232 = (ushort) (num229 | num231);
        registerData1.Voltage_DIS_MOS_Value = num232;
        byte[] numArray89 = dataBuf;
        int index91 = (int) num230;
        byte num233 = (byte) (index91 + 1);
        int num234 = (int) (ushort) numArray89[index91];
        byte[] numArray90 = dataBuf;
        int index92 = (int) num233;
        byte num235 = (byte) (index92 + 1);
        int num236 = (int) (ushort) ((uint) numArray90[index92] << 8);
        ushort num237 = (ushort) (num234 | num236);
        registerData1.Voltage_CH_MOS_Value = num237;
        byte[] numArray91 = dataBuf;
        int index93 = (int) num235;
        byte num238 = (byte) (index93 + 1);
        int num239 = (int) (ushort) numArray91[index93];
        byte[] numArray92 = dataBuf;
        int index94 = (int) num238;
        byte num240 = (byte) (index94 + 1);
        int num241 = (int) (ushort) ((uint) numArray92[index94] << 8);
        ushort num242 = (ushort) (num239 | num241);
        registerData1.Voltage_NH_MOS_Value = num242;
        byte[] numArray93 = dataBuf;
        int index95 = (int) num240;
        byte num243 = (byte) (index95 + 1);
        int num244 = (int) (ushort) numArray93[index95];
        byte[] numArray94 = dataBuf;
        int index96 = (int) num243;
        byte num245 = (byte) (index96 + 1);
        int num246 = (int) (ushort) ((uint) numArray94[index96] << 8);
        ushort num247 = (ushort) (num244 | num246);
        registerData1.PackCellType = num247;
        byte[] numArray95 = dataBuf;
        int index97 = (int) num245;
        byte num248 = (byte) (index97 + 1);
        int num249 = (int) numArray95[index97];
        byte[] numArray96 = dataBuf;
        int index98 = (int) num248;
        byte num250 = (byte) (index98 + 1);
        int num251 = (int) numArray96[index98] << 8;
        int num252 = num249 | num251;
        byte[] numArray97 = dataBuf;
        int index99 = (int) num250;
        byte num253 = (byte) (index99 + 1);
        int num254 = (int) numArray97[index99] << 16;
        int num255 = num252 | num254;
        byte[] numArray98 = dataBuf;
        int index100 = (int) num253;
        byte num256 = (byte) (index100 + 1);
        int num257 = (int) numArray98[index100] << 24;
        uint num258 = (uint) (num255 | num257);
        Console.WriteLine("Pack_All_DisAH");
        Console.WriteLine(index97);
        registerData1.Pack_All_DisAH = num258;
        byte[] numArray99 = dataBuf;
        int index101 = (int) num256;
        byte num259 = (byte) (index101 + 1);
        int num260 = (int) numArray99[index101];
        byte[] numArray100 = dataBuf;
        int index102 = (int) num259;
        byte num261 = (byte) (index102 + 1);
        int num262 = (int) numArray100[index102] << 8;
        int num263 = num260 | num262;
        byte[] numArray101 = dataBuf;
        int index103 = (int) num261;
        byte num264 = (byte) (index103 + 1);
        int num265 = (int) numArray101[index103] << 16;
        int num266 = num263 | num265;
        byte[] numArray102 = dataBuf;
        int index104 = (int) num264;
        byte num267 = (byte) (index104 + 1);
        int num268 = (int) numArray102[index104] << 24;
        uint num269 = (uint) (num266 | num268);
        registerData1.Pack_All_ChAH = num269;
        byte[] numArray103 = dataBuf;
        int index105 = (int) num267;
        byte num270 = (byte) (index105 + 1);
        int num271 = (int) numArray103[index105];
        byte[] numArray104 = dataBuf;
        int index106 = (int) num270;
        byte num272 = (byte) (index106 + 1);
        int num273 = (int) numArray104[index106] << 8;
        int num274 = num271 | num273;
        byte[] numArray105 = dataBuf;
        int index107 = (int) num272;
        byte num275 = (byte) (index107 + 1);
        int num276 = (int) numArray105[index107] << 16;
        int num277 = num274 | num276;
        byte[] numArray106 = dataBuf;
        int index108 = (int) num275;
        byte num278 = (byte) (index108 + 1);
        int num279 = (int) numArray106[index108] << 24;
        uint num280 = (uint) (num277 | num279);
        registerData1.All_DisTimer_s = num280;
        byte[] numArray107 = dataBuf;
        int index109 = (int) num278;
        byte num281 = (byte) (index109 + 1);
        int num282 = (int) numArray107[index109];
        byte[] numArray108 = dataBuf;
        int index110 = (int) num281;
        byte num283 = (byte) (index110 + 1);
        int num284 = (int) numArray108[index110] << 8;
        int num285 = num282 | num284;
        byte[] numArray109 = dataBuf;
        int index111 = (int) num283;
        byte num286 = (byte) (index111 + 1);
        int num287 = (int) numArray109[index111] << 16;
        int num288 = num285 | num287;
        byte[] numArray110 = dataBuf;
        int index112 = (int) num286;
        byte num289 = (byte) (index112 + 1);
        int num290 = (int) numArray110[index112] << 24;
        uint num291 = (uint) (num288 | num290);
        registerData1.All_ChTimer_s = num291;
        if ((int) dataBuf[5] > (int) registerData1.PACK_Cell_Num * 2 + (int) registerData1.Temperature_Num * 2 + 106)
        {
          byte[] numArray111 = dataBuf;
          int index113 = (int) num289;
          byte num292 = (byte) (index113 + 1);
          int num293 = (int) numArray111[index113];
          byte[] numArray112 = dataBuf;
          int index114 = (int) num292;
          byte num294 = (byte) (index114 + 1);
          int num295 = (int) numArray112[index114] << 8;
          int num296 = num293 | num295;
          byte[] numArray113 = dataBuf;
          int index115 = (int) num294;
          byte num297 = (byte) (index115 + 1);
          int num298 = (int) numArray113[index115] << 16;
          int num299 = num296 | num298;
          byte[] numArray114 = dataBuf;
          int index116 = (int) num297;
          byte num300 = (byte) (index116 + 1);
          int num301 = (int) numArray114[index116] << 24;
          uint num302 = (uint) (num299 | num301);
          registerData1.CHG_duration = num302;
          byte[] numArray115 = dataBuf;
          int index117 = (int) num300;
          byte num303 = (byte) (index117 + 1);
          int num304 = (int) numArray115[index117];
          byte[] numArray116 = dataBuf;
          int index118 = (int) num303;
          byte num305 = (byte) (index118 + 1);
          int num306 = (int) numArray116[index118] << 8;
          int num307 = num304 | num306;
          byte[] numArray117 = dataBuf;
          int index119 = (int) num305;
          byte num308 = (byte) (index119 + 1);
          int num309 = (int) numArray117[index119] << 16;
          int num310 = num307 | num309;
          byte[] numArray118 = dataBuf;
          int index120 = (int) num308;
          byte num311 = (byte) (index120 + 1);
          int num312 = (int) numArray118[index120] << 24;
          uint num313 = (uint) (num310 | num312);
          registerData1.CHG_interval = num313;
          byte[] numArray119 = dataBuf;
          int index121 = (int) num311;
          byte num314 = (byte) (index121 + 1);
          int num315 = (int) (ushort) numArray119[index121];
          byte[] numArray120 = dataBuf;
          int index122 = (int) num314;
          byte num316 = (byte) (index122 + 1);
          int num317 = (int) (ushort) ((uint) numArray120[index122] << 8);
          ushort num318 = (ushort) (num315 | num317);
          registerData1.CT_remaining = num318;
          byte[] numArray121 = dataBuf;
          int index123 = (int) num316;
          byte num319 = (byte) (index123 + 1);
          int num320 = (int) (ushort) numArray121[index123];
          byte[] numArray122 = dataBuf;
          int index124 = (int) num319;
          byte num321 = (byte) (index124 + 1);
          int num322 = (int) (ushort) ((uint) numArray122[index124] << 8);
          ushort num323 = (ushort) (num320 | num322);
          registerData1.RT_discharge = num323;
        }
      }
      else if (dataBuf[2] == (byte) 18 || dataBuf[2] == (byte) 66)
      {
        registerData1.MsgType = 2;
        byte[] numArray123 = new byte[16];
        byte num324 = dataBuf[2];
        ushort num325 = (ushort) (((uint) (ushort) dataBuf[4] << 8) + (uint) dataBuf[3]);
        byte num326 = dataBuf[5];
        ushort[] numArray124 = new ushort[256];
        for (int index = 0; index < (int) num326; index += 2)
        {
          ushort num327 = (ushort) ((uint) (ushort) ((uint) (ushort) dataBuf[index + 7] << 8) + (uint) dataBuf[index + 6]);
          numArray124[(index + (int) num325) / 2] = num327;
        }
        registerData1.MsgData = numArray124;
      }
      if (dataBuf[2] == byte.MaxValue)
      {
        ushort num328 = (ushort) (((uint) (ushort) dataBuf[11] << 8) + (uint) dataBuf[12]);
        byte[] numArray = new byte[16]
        {
          (byte) ((uint) dataBuf[2] >> 4),
          (byte) ((uint) dataBuf[2] & 15U),
          (byte) ((uint) dataBuf[3] >> 4),
          (byte) ((uint) dataBuf[3] & 15U),
          (byte) ((uint) dataBuf[4] >> 4),
          (byte) ((uint) dataBuf[4] & 15U),
          (byte) ((uint) dataBuf[5] >> 4),
          (byte) ((uint) dataBuf[5] & 15U),
          (byte) ((uint) dataBuf[6] >> 4),
          (byte) ((uint) dataBuf[6] & 15U),
          (byte) ((uint) dataBuf[7] >> 4),
          (byte) ((uint) dataBuf[7] & 15U),
          (byte) ((uint) dataBuf[8] >> 4),
          (byte) ((uint) dataBuf[8] & 15U),
          (byte) ((uint) dataBuf[9] >> 4),
          (byte) ((uint) dataBuf[9] & 15U)
        };
        registerData1.Warning = (int) num328;
      }
      return registerData1;
    }
    public class RegisterData
    {
        public byte SysOperationAuth;
        public byte SystemState;
        public byte PACK_Cell_Num;
        public byte Temperature_Num;
        public ulong ProtectMack_Bit;
        public ulong WarningMack_Bit;
        public ulong PushMack_Bit;
        public ushort[] Voltage_Cell_Value = new ushort[32];
        public short[] Temperature_Value = new short[4];
        public short Temperature_MOS;
        public short Temperature_Balance;
        public ushort Voltage_Pack;
        public short Current_Value;
        public ushort Pack_SOC;
        public ushort Pack_SOH;
        public byte DIS_MOS_State;
        public byte CH_MOS_State;
        public ulong Balance_State;
        public uint Pack_Physics_AH;
        public uint Pack_Remain_AH;
        public uint Pack_All_AH;
        public int Pack_Power;
        public ulong All_Timer_ms;
        public ulong Balance_State_Bit;
        public ushort Voltage_Cell_Max_Value;
        public ushort Voltage_Cell_Max_Pos;
        public ushort Voltage_Cell_Min_Value;
        public ushort Voltage_Cell_Min_Pos;
        public ushort Voltage_Cell_Difference;
        public ushort Voltage_Cell_Average_Value;
        public short Voltage_DS_Value;
        public ushort Voltage_DIS_MOS_Value;
        public ushort Voltage_CH_MOS_Value;
        public ushort Voltage_NH_MOS_Value;
        public ushort PackCellType;
        public uint Pack_All_DisAH;
        public uint Pack_All_ChAH;
        public uint All_DisTimer_s;
        public uint All_ChTimer_s;
        public uint CHG_duration;
        public uint CHG_interval;
        public ushort CT_remaining;
        public ushort RT_discharge;
        public int MsgType;
        public ushort[] MsgData;
        public int Warning;
    }

    public static RegisterData AntProtocol_FixedParse(byte[] dataBuf)
    {
        RegisterData registerData = new RegisterData();

        registerData.MsgType = 1;
        registerData.SysOperationAuth = dataBuf[6];
        registerData.SystemState = dataBuf[7];
        registerData.Temperature_Num = dataBuf[8];
        registerData.PACK_Cell_Num = dataBuf[9];
        registerData.ProtectMack_Bit = BitConverter.ToUInt64(dataBuf, 10);
        registerData.WarningMack_Bit = BitConverter.ToUInt64(dataBuf, 18);
        registerData.PushMack_Bit = BitConverter.ToUInt64(dataBuf, 26);

        int index = 34; // Starting index
        for (byte i = 0; i < registerData.PACK_Cell_Num; ++i)
        {
            registerData.Voltage_Cell_Value[i] = BitConverter.ToUInt16(dataBuf, index);
            index += 2;
        }

        for (byte i = 0; i < registerData.Temperature_Num; ++i)
        {
            registerData.Temperature_Value[i] = BitConverter.ToInt16(dataBuf, index);
            index += 2;
        }

        registerData.Temperature_MOS = BitConverter.ToInt16(dataBuf, index); index += 2;
        registerData.Temperature_Balance = BitConverter.ToInt16(dataBuf, index); index += 2;
        registerData.Voltage_Pack = BitConverter.ToUInt16(dataBuf, index); index += 2;
        registerData.Current_Value = BitConverter.ToInt16(dataBuf, index); index += 2;
        registerData.Pack_SOC = BitConverter.ToUInt16(dataBuf, index); index += 2;
        registerData.Pack_SOH = BitConverter.ToUInt16(dataBuf, index); index += 2;
        registerData.DIS_MOS_State = dataBuf[index++];
        registerData.CH_MOS_State = dataBuf[index++];
        registerData.Balance_State = BitConverter.ToUInt16(dataBuf, index); index += 2;
        registerData.Pack_Physics_AH = BitConverter.ToUInt32(dataBuf, index); index += 4;
        registerData.Pack_Remain_AH = BitConverter.ToUInt32(dataBuf, index); index += 4;
        registerData.Pack_All_AH = BitConverter.ToUInt32(dataBuf, index); index += 4;
        registerData.Pack_Power = BitConverter.ToInt32(dataBuf, index); index += 4;
        registerData.All_Timer_ms = BitConverter.ToUInt32(dataBuf, index); index += 4;
        registerData.Balance_State_Bit = BitConverter.ToUInt32(dataBuf, index); index += 4;
        registerData.Voltage_Cell_Max_Value = BitConverter.ToUInt16(dataBuf, index); index += 2;
        registerData.Voltage_Cell_Max_Pos = BitConverter.ToUInt16(dataBuf, index); index += 2;
        registerData.Voltage_Cell_Min_Value = BitConverter.ToUInt16(dataBuf, index); index += 2;
        registerData.Voltage_Cell_Min_Pos = BitConverter.ToUInt16(dataBuf, index); index += 2;
        registerData.Voltage_Cell_Difference = BitConverter.ToUInt16(dataBuf, index); index += 2;
        registerData.Voltage_Cell_Average_Value = BitConverter.ToUInt16(dataBuf, index); index += 2;
        registerData.Voltage_DS_Value = BitConverter.ToInt16(dataBuf, index); index += 2;
        registerData.Voltage_DIS_MOS_Value = BitConverter.ToUInt16(dataBuf, index); index += 2;
        registerData.Voltage_CH_MOS_Value = BitConverter.ToUInt16(dataBuf, index); index += 2;
        registerData.Voltage_NH_MOS_Value = BitConverter.ToUInt16(dataBuf, index); index += 2;
        registerData.PackCellType = BitConverter.ToUInt16(dataBuf, index); index += 2;
        registerData.Pack_All_DisAH = BitConverter.ToUInt32(dataBuf, index); index += 4;
        registerData.Pack_All_ChAH = BitConverter.ToUInt32(dataBuf, index); index += 4;
        registerData.All_DisTimer_s = BitConverter.ToUInt32(dataBuf, index); index += 4;
        registerData.All_ChTimer_s = BitConverter.ToUInt32(dataBuf, index); index += 4;

        if (dataBuf[5] > registerData.PACK_Cell_Num * 2 + registerData.Temperature_Num * 2 + 106)
        {
            registerData.CHG_duration = BitConverter.ToUInt32(dataBuf, index); index += 4;
            registerData.CHG_interval = BitConverter.ToUInt32(dataBuf, index); index += 4;
            registerData.CT_remaining = BitConverter.ToUInt16(dataBuf, index); index += 2;
            registerData.RT_discharge = BitConverter.ToUInt16(dataBuf, index); index += 2;
        }
        else if (dataBuf[2] == 18 || dataBuf[2] == 66) {
            registerData.MsgType = 2;
            byte[] numArray123 = new byte[16];
            byte num324 = dataBuf[2];
            ushort num325 = (ushort) (((uint) (ushort) dataBuf[4] << 8) + (uint) dataBuf[3]);
            byte num326 = dataBuf[5];
            ushort[] numArray124 = new ushort[256];
            for (int newIndex = 0; newIndex < (int) num326; newIndex += 2)
            {
                ushort num327 = (ushort) ((uint) (ushort) ((uint) (ushort) dataBuf[newIndex + 7] << 8) + (uint) dataBuf[newIndex + 6]);
                numArray124[(newIndex + (int) num325) / 2] = num327;
            }
            registerData.MsgData = numArray124;
        }

        if (dataBuf[2] == byte.MaxValue) {
            ushort num328 = (ushort) (((uint) (ushort) dataBuf[11] << 8) + (uint) dataBuf[12]);
            byte[] numArray = new byte[16]
            {
                (byte) ((uint) dataBuf[2] >> 4),
                (byte) ((uint) dataBuf[2] & 15U),
                (byte) ((uint) dataBuf[3] >> 4),
                (byte) ((uint) dataBuf[3] & 15U),
                (byte) ((uint) dataBuf[4] >> 4),
                (byte) ((uint) dataBuf[4] & 15U),
                (byte) ((uint) dataBuf[5] >> 4),
                (byte) ((uint) dataBuf[5] & 15U),
                (byte) ((uint) dataBuf[6] >> 4),
                (byte) ((uint) dataBuf[6] & 15U),
                (byte) ((uint) dataBuf[7] >> 4),
                (byte) ((uint) dataBuf[7] & 15U),
                (byte) ((uint) dataBuf[8] >> 4),
                (byte) ((uint) dataBuf[8] & 15U),
                (byte) ((uint) dataBuf[9] >> 4),
                (byte) ((uint) dataBuf[9] & 15U)
            };
            registerData.Warning = (int) num328;
        }

        return registerData;
    }

    public static void PrintPropertiesAndFields(object obj)
    {
        Type type = obj.GetType();

        Console.WriteLine("Properties of " + type.Name + ":");
        foreach (var property in type.GetProperties())
        {
            Console.WriteLine(property.Name + ": " + property.GetValue(obj));
        }

        Console.WriteLine("\nFields of " + type.Name + ":");
        foreach (var field in type.GetFields())
        {
            Console.Write(field.Name + ": ");
            object value = field.GetValue(obj);

            if (value != null && value.GetType().IsArray)
            {
                Array array = (Array)value;
                Console.Write("[ ");
                foreach (var item in array)
                {
                    Console.Write(item.ToString() + " ");
                }
                Console.WriteLine("]");
            }
            else
            {
                Console.WriteLine(value);
            }
        }
    }

    static string sData = "7E A1 11 00 00 B2 05 05 04 20 B1 00 00 02 00 00 00 00 00 00 00 80 00 00 00 00 00 00 00 00 00 00 00 00 87 0F 91 0F 8B 0F 8D 0F 8A 0F 8A 0F 8D 0F 90 0F 85 0F 8D 0F 22 01 1A 02 88 00 3D 02 9E 00 19 02 89 00 F6 01 87 00 CB 01 72 00 9D 01 67 00 6B 01 58 00 2D 01 4E 00 C6 00 33 00 5C 00 16 00 03 00 15 00 15 00 15 00 15 00 15 00 16 00 8B 0F 00 00 64 00 64 00 02 09 00 00 80 F0 FA 02 57 E8 FA 02 02 00 00 00 00 00 00 00 26 1B 00 00 00 00 00 00 91 0F 02 00 85 0F 09 00 0C 00 8B 0F 03 00 00 00 00 00 AA 02 F5 FA 02 00 00 00 02 00 00 00 00 00 00 00 00 00 00 00 DE FA AA 55";

    public static byte[] HexStringToByteArray(string hex)
    {
        hex = hex.Replace(" ", ""); // Remove any spaces from the input string
        int numberChars = hex.Length;
        byte[] bytes = new byte[numberChars / 2];
        for (int i = 0; i < numberChars; i += 2)
        {
            bytes[i / 2] = Convert.ToByte(hex.Substring(i, 2), 16);
        }
        return bytes;
    }

    public static void Main(string[] args)
    {
        var data = new byte[] { 126, 161, 81, 3, 0, 0, 0, 0, 0, 0 };
        Console.WriteLine(ByteArrayToString(data));
        var origResult  = CheckCrc16(data, 1, 5);

        Console.WriteLine("Orig Hex: {0:X}", origResult);
         var newResult  = Modbus(data, 1, 5);
        Console.WriteLine("New  Hex: {0:X}", newResult);

        var origSend = WriteData((ushort) 11, (byte) 0, (byte) 81, BitConverter.GetBytes((ushort) 0));
        // close bms
        var fixSend = WriteDataFix((ushort) 11, (byte) 0, (byte) 81, BitConverter.GetBytes((ushort) 0));
        Console.WriteLine(ByteArrayToString(origSend));
        Console.WriteLine(ByteArrayToString(fixSend));


        Console.WriteLine();
        Console.WriteLine ("Try programiz.pro");

        var testData = HexStringToByteArray(sData);
        var result = AntProtocol_RxBufFind(testData);
        var result2 = AntProtocol_FixedParse(testData);
        PrintPropertiesAndFields(result);
        PrintPropertiesAndFields(result2);
    }
}