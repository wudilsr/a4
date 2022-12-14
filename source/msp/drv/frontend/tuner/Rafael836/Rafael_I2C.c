#include "Rafael_I2C.h"

#include "drv_i2c_ext.h"
#include "hi_debug.h"

#include "drv_demod.h"

#define			RT_Success			1
#define			RT_Fail				0

HI_U32 g_r836_tuner_port = 0;
HI_U8 R836_data[51];

int Rafael_I2C_Write_Len(I2C_LEN_TYPE *I2C_Info)
{
    HI_S32 status = HI_SUCCESS;
    TUNER_I2C_DATA_S I2cDataStr;
    HI_U32 i=0;

    R836_data[0] = I2C_Info->RegAddr;
    for( i=1;i<=I2C_Info->Len;i++ )
        R836_data[i] = I2C_Info->Data[i-1];
    I2cDataStr.pu8ReceiveBuf = 0;
    I2cDataStr.u32ReceiveLength = 0;
    I2cDataStr.pu8SendBuf = R836_data;
    
    I2cDataStr.u32SendLength = I2C_Info->Len+1;
    
    hi3137_config_i2c_out(g_r836_tuner_port);
    
    status = tuner_i2c_send_data( g_stTunerOps[g_r836_tuner_port].enI2cChannel, g_stTunerOps[g_r836_tuner_port].u32TunerAddress, &I2cDataStr);

    if (HI_SUCCESS == status)
    {
        return RT_Success;
    }
    else
    {
        return RT_Fail;
    }
}



int Rafael_I2C_Read_Len(I2C_LEN_TYPE *I2C_Info)
{
    TUNER_I2C_DATA_S stDataStruct = {0};
    HI_S32 s32status = HI_SUCCESS;
    HI_U8 subaddress = 0;
    HI_S32 DataCunt = 0;
    
    stDataStruct.pu8ReceiveBuf = I2C_Info->Data;
    stDataStruct.u32ReceiveLength = I2C_Info->Len;
    stDataStruct.pu8SendBuf = &subaddress;
    stDataStruct.u32SendLength = 1;

	hi3137_config_i2c_out(g_r836_tuner_port);
    s32status = tuner_i2c_receive_data(g_stTunerOps[g_r836_tuner_port].enI2cChannel, g_stTunerOps[g_r836_tuner_port].u32TunerAddress, &stDataStruct);

    if(HI_SUCCESS != s32status)
    {
        HI_ERR_TUNER( "tuner_i2c_receive_data error s32status = 0x%x\n", s32status );
        return RT_Fail;
    }
    else
    {
        for(DataCunt = 0;DataCunt < I2C_Info->Len;DataCunt ++)
        {
            I2C_Info->Data[DataCunt] = Rafael_R828_Convert(I2C_Info->Data[DataCunt]);
        }

        return RT_Success;
    }
}



int Rafael_I2C_Write(I2C_TYPE *I2C_Info)
{
    HI_S32 status = HI_SUCCESS;
    TUNER_I2C_DATA_S I2cDataStr;

    R836_data[0] = I2C_Info->RegAddr;
    R836_data[1] = I2C_Info->Data;
    I2cDataStr.pu8ReceiveBuf = 0;
    I2cDataStr.u32ReceiveLength = 0;
    I2cDataStr.pu8SendBuf = R836_data;
    I2cDataStr.u32SendLength = 2;
    hi3137_config_i2c_out(g_r836_tuner_port);

    status = tuner_i2c_send_data( g_stTunerOps[g_r836_tuner_port].enI2cChannel, g_stTunerOps[g_r836_tuner_port].u32TunerAddress, &I2cDataStr );
    if (HI_SUCCESS == status)
    {
        return RT_Success;
    }
    else
    {
        HI_ERR_TUNER("<0>write_I2C error, 0x%x\n", status);
        return RT_Fail;
    }
}


int Rafael_R828_Convert(int InvertNum)
{
	int ReturnNum = 0;
	int AddNum    = 0x80;
	int BitNum    = 0x01;
	int CuntNum   = 0;

	for(CuntNum = 0;CuntNum < 8;CuntNum ++)
	{
		if(BitNum & InvertNum)
			ReturnNum += AddNum;

		AddNum /= 2;
		BitNum *= 2;
	}

	return ReturnNum;
	
}